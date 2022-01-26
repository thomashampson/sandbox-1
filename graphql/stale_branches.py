# An example to get the remaining rate limit using the Github GraphQL API.
import json
import os
import pathlib
import pandas as pd
import requests

GRAPHQL_ENDPOINT = "https://api.github.com/graphql"
QUERY = """
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
WHITELISTED_REFS = ["main", "release-next"]


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


def query_github() -> list:
    def flatten_response(refs_nodes):
        """Flatten the inner {'author': {'user': {'login': 'robertapplin'}} dict"""
        flattened = []
        for ref in refs_nodes:
            target = ref["target"]
            user = target["author"]["user"]
            login = user["login"] if user is not None else ""
            flattened.append(
                dict(name=ref["name"],
                     author=login,
                     committedDate=target["committedDate"]))

        return flattened

    branch_info = []
    cursor = "null"
    max_results = 500
    while True:
        query_results = graphql_query(QUERY.format(cursor=cursor))
        if "data" in query_results:
            refs = query_results["data"]["repository"]["refs"]
            branch_info.extend(flatten_response(refs["nodes"]))
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


def main() -> int:
    # If we have the file skip the query
    json_file_path = pathlib.Path(JSON_FILE_NAME)
    if json_file_path.exists():
        with open(json_file_path, "r") as fp:
            ref_info = json.load(fp)
    else:
        ref_info = query_github()
        with open(json_file_path, "w") as fp:
            json.dump(ref_info, fp)

    # allrefs has form
    # [{'name': 'branchname', 'author': 'username' ,
    #   'committedDate': '2019-05-09T21:28:42Z'}, ...]
    df = pd.DataFrame.from_dict(ref_info)
    print(df)


if __name__ == "__main__":
    main()
