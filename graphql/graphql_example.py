# An example to get the remaining rate limit using the Github GraphQL API.
import os
import pprint
import requests

GRAPHQL_ENDPOINT = "https://api.github.com/graphql"


def graphql_query(query):
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    request = requests.post(GRAPHQL_ENDPOINT, json={"query": query}, headers=headers)
    if request.status_code == 200:
        return request.json()
    else:
        raise RuntimeError(
            f"Query failed to run by returning code of {request.status_code}. {query}"
        )


query = """
{{
  search(query: "is:pr repo:mantidproject/mantid", type: ISSUE, last: 100, before:{cursor}) {{
    nodes {{
      ... on PullRequest {{
        number
        state
      }}
    }}
    pageInfo {{
      hasPreviousPage
      startCursor
    }}
  }}
}}
"""

all_results = {}
cursor = "null"
max_results = 1000
while True:
    query_results = graphql_query(query.format(cursor=cursor))
    search_data = query_results["data"]["search"]
    all_results.update(query_results)
    if len(search_data["nodes"]) >= max_results:
        break
    page_info = search_data["pageInfo"]
    has_next_page = page_info["hasPreviousPage"]
    if has_next_page:
        cursor = f'"{page_info["startCursor"]}"'
    else:
        break

pprint.pprint(query_results)
