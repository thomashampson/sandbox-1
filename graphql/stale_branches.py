# An example to get the remaining rate limit using the Github GraphQL API.
import json
import os
import pandas as pd
import pathlib
import re
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
JSON_FILE_NAME = "mantid-stale-branches.json"
GH_ORG = "mantidproject"
GH_REPO = "mantid"
GH_MAIN_BRANCH = "main"
BRANCHES_TO_KEEP = map(re.compile, ("main", "release-next", "ornl.*", "ill.*"))


def graphql_query(query) -> dict:
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    response = requests.post(GRAPHQL_ENDPOINT, json={"query": query}, headers=headers)
    if response.status_code == 200:
        return response.json()
    else:
        raise RuntimeError(
            f"Query failed to run by returning code of {response.status_code}. {query}"
        )


def query_github() -> list:
    branch_info = []
    cursor = "null"
    max_results = 500
    while True:
        query_results = graphql_query(BRANCHES_INFO_QUERY.format(cursor=cursor))
        if "data" in query_results:
            refs = query_results["data"]["repository"]["refs"]
            branch_info.extend(create_ref_info(refs["nodes"]))
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
    flattened = []
    for ref in refs_nodes:
        name = ref["name"]
        if any(map(lambda x: x.match(name) is not None, BRANCHES_TO_KEEP)):
            continue

        target = ref["target"]
        user = target["author"]["user"]
        login = user["login"] if user is not None else ""
        flattened.append(
            dict(
                name=name,
                author=login,
                committedDate=target["committedDate"],
                aheadBy=branch_ahead_by(GH_MAIN_BRANCH, name),
            )
        )

    return flattened


def branch_ahead_by(base: str, head: str) -> int:
    """Compute the number of commits ahead head is of base"""
    # Comparison is only possible with the rest api
    endpoint = f"{REST_API_ROOT}/repos/{GH_ORG}/{GH_REPO}/compare/{base}...{head}"
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    response = requests.get(endpoint, headers=headers)
    return response.json()["ahead_by"]


def main() -> int:
    ref_info = query_github()

    # allrefs has form
    # [{'name': 'branchname', 'author': 'username' ,
    #   'committedDate': '2019-05-09T21:28:42Z'}, ...]
    df = pd.DataFrame.from_dict(ref_info)
    df.to_json("./branch-info.json")


if __name__ == "__main__":
    main()
