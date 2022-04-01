# An example to get the remaining rate limit using the Github GraphQL API.
import datetime as dt
import os
import pandas as pd
from pathlib import Path
import requests

GRAPHQL_ENDPOINT = "https://api.github.com/graphql"
REST_API_ROOT = "https://api.github.com"
BRANCHES_INFO_QUERY = """
{{
    repository(name: "mantid", owner: "mantidproject") {{
        refs(first: 100, refPrefix: "refs/heads/", after:{cursor}) {{
        nodes {{
            name
            target {{
            ... on Commit {{
                author {{ user {{ login }} }}
                committedDate
            }}
            }}
        }}
        pageInfo {{
            hasNextPage
            endCursor
        }}
        }}
    }}
}}
"""
PULL_REQUEST_HEADS_QUERY = """
{{
    repository(name: "mantid", owner: "mantidproject") {{
      pullRequests(first: 100, states: [CLOSED], after:{cursor}) {{
      nodes {{
        headRefName
        number
      }}
      pageInfo {{
        hasNextPage
        endCursor
      }}
      }}
    }}
}}
"""

JSON_FILE_NAME = "mantid-stale-branches.json"
GH_ORG = "mantidproject"
GH_REPO = "mantid"
GH_MAIN_BRANCH = "main"
NEVER_STALE_BRANCHES = ("main", "release-next", "ornl", "ornl-next", "ornl-qa",
                        "ill-next")
STALE_AFTER_MONTHS = 4


def graphql_query(query) -> dict:
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    response = requests.post(GRAPHQL_ENDPOINT,
                             json={"query": query},
                             headers=headers)
    if response.status_code == 200:
        return response.json()
    else:
        raise RuntimeError(
            f"Query failed to run by returning code of {response.status_code}. {query}"
        )


def all_github_branches() -> dict:
    branch_info = dict()
    cursor = "null"
    max_results = 500
    while True:
        query_results = graphql_query(
            BRANCHES_INFO_QUERY.format(cursor=cursor))
        if "data" in query_results:
            refs = query_results["data"]["repository"]["refs"]
            branch_info.update(create_ref_info(refs["nodes"]))
            if len(branch_info) > max_results:
                break
            page_info = refs["pageInfo"]
            has_next_page = page_info["hasNextPage"]
            if has_next_page:
                cursor = f'"{page_info["endCursor"]}"'
            else:
                break
        else:
            break

    return branch_info


def create_ref_info(refs_nodes):
    """Flatten the inner {'author': {'user': {'login': 'loginname'}} dict"""
    info = dict()
    for ref in refs_nodes:
        name = ref["name"]
        target = ref["target"]
        user = target["author"]["user"]
        login = user["login"] if user is not None else ""
        info[name] = [
            name, login, target["committedDate"]
            # branch_ahead_by(GH_MAIN_BRANCH, name),
        ]

    return info


def branch_ahead_by(base: str, head: str) -> int:
    """Compute the number of commits ahead head is of base"""
    # Comparison is only possible with the rest api
    endpoint = f"{REST_API_ROOT}/repos/{GH_ORG}/{GH_REPO}/compare/{base}...{head}"
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    response = requests.get(endpoint, headers=headers)
    return response.json()["ahead_by"]


def pull_request_head_refs() -> list:
    """Return the head refs of all pull requests
    """
    pr_head_refs = dict()
    cursor = "null"
    max_results = 10000
    while True:
        query_results = graphql_query(
            PULL_REQUEST_HEADS_QUERY.format(cursor=cursor))
        if "data" in query_results:
            pulls = query_results["data"]["repository"]["pullRequests"]
            for record in pulls["nodes"]:
                pr_head_refs[record["headRefName"]] = record["number"]
            if len(pr_head_refs) > max_results:
                break
            page_info = pulls["pageInfo"]
            has_next_page = page_info["hasNextPage"]
            if has_next_page:
                cursor = f'"{page_info["endCursor"]}"'
            else:
                break
        else:
            break

    return pr_head_refs


def main() -> int:
    json_cache_filename = Path(JSON_FILE_NAME)
    if json_cache_filename.exists():
        df = pd.read_json(json_cache_filename)
    else:
        ref_info = all_github_branches()
        df = pd.DataFrame.from_dict(
            ref_info,
            orient='index',
            columns=['name', 'author', 'committedDate'])
        df.reset_index(inplace=True)
        # Remove anything never considered stale
        df = df[~df["name"].isin(NEVER_STALE_BRANCHES)]
        df.to_json(json_cache_filename)

    # Convert datetime column
    df["committedDate"] = pd.to_datetime(df["committedDate"])
    # Branches greater than stale threshold months old
    stale_horizon = dt.datetime.today() - pd.DateOffset(
        months=STALE_AFTER_MONTHS)
    df = df[df["committedDate"].dt.date < stale_horizon.date()]

    # Dump to csv
    df.to_csv('mantid-stale-branches.csv', index=False)

    # Format a markdown document of authors branches
    preamble = """This issue collates information on stale branches in this repository.
For this purpose a stale branch is defined as a branch that has had no activity within the last 4 months.

Below are sections arranged by the author of the last commit to the branch.
Please take the time to review the list under your GitHub username and for each:

- if the branch should be kept then please either resurrect the work and open a pull request
  or copy the branch to a fork (https://docs.github.com/en/get-started/quickstart/fork-a-repo)
  to back it up under your own account.
- if the branch is no longer required then do nothing and it will be removed in 7 days.

"""
    markdown_lines = [preamble]
    authors = pd.unique(df["author"])
    deletable = []
    for author in authors:
        branches_by_author = df.query(f'author == "{author}"')['name']
        markdown_lines.append(f"### @{author}")
        for branchname in branches_by_author:
            markdown_lines.append(
                f"  - [{branchname}](https://github.com/mantidproject/mantid/compare/main...{branchname})"
            )
            deletable.append(branchname)
        markdown_lines.append("\n")

    with open('issue_body.md', 'w') as fp:
        fp.write("\n".join(markdown_lines) + "\n")

    print(f"Found {len(deletable)} branches to delete")
    deletable_df = pd.DataFrame(deletable)
    deletable_df.to_json("deletable.json", orient='records')
    print(f"DataFrame has {len(deletable_df.index)} rows")

    # Dump information on branches to delete
    # authors_to_remove = [
    #     "TWJubb", "TTitcombe", "srikanthravipati", "ThomasLohnert", "yxqd", "",
    #     "AntonPiccardoSelg", "brandonhewer", "ciaranightingale", "clayton-tom",
    #     "dtasev", "ewancook", "FedeMPouzols", "giovannidisiena", "ianbush",
    #     "igudich", "joseph-torsney", "keeeto", "louisemccann", "mantid-roman",
    #     "Matt-Cumber", "Matthew-Andrew", "matthew-d-jones", "NickDraper",
    #     "OwenArnold", "PranavBahuguna", "ricleal", "SamJenkins1",
    #     "samueljackson92", "tolu28-coder", "VickieLynch"
    # ]

    # deletable = df[df["author"].isin(authors_to_remove)]["name"]


if __name__ == "__main__":
    main()
