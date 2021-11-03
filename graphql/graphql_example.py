# An example to get the remaining rate limit using the Github GraphQL API.
import os
import pandas as pd
import requests

GRAPHQL_ENDPOINT = "https://api.github.com/graphql"


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


def to_dataframe(pullrequests: dict) -> pd.DataFrame:
    records = dict(number=[],
                   state=[],
                   isDraft=[],
                   createdAt=[],
                   approvedAt=[],
                   mergedAt=[])

    for pr in pullrequests:
        # direct PullRequest fields
        for field, transform in (("number", int), ("state", str),
                                 ("isDraft", bool), ("createdAt",
                                                     pd.to_datetime),
                                 ("mergedAt", pd.to_datetime)):
            records[field].append(transform(pr[field]))
        # event fields
        reviews = pr["reviews"]["nodes"]
        approvedAt = None
        if len(reviews) > 0 and reviews[0]["state"] == "APPROVED":
            approvedAt = pd.to_datetime(reviews[0]["createdAt"])

        records["approvedAt"].append(approvedAt)

    df = pd.DataFrame.from_records(records,
                                   columns=[
                                       "number", "state", "isDraft",
                                       "createdAt", "approvedAt", "mergedAt"
                                   ])
    df["createdToApprovedDur"] = df["approvedAt"] - df["createdAt"]
    df["createdToMergedDur"] = df["mergedAt"] - df["createdAt"]
    return df


query = """
{{
  search(query: "is:pr repo:mantidproject/mantid", type: ISSUE, first: 100, after:{cursor}) {{
    nodes {{
      ... on PullRequest {{
        number
        state
        isDraft
        createdAt
        mergedAt
        reviews(last:1) {{
          nodes {{
            ... on PullRequestReview {{
              createdAt
              state
            }}
          }}
        }}
      }}
    }}
    pageInfo {{
      hasPreviousPage
      hasNextPage
      startCursor
      endCursor
    }}
  }}
}}
"""

all_results = None
cursor = "null"
max_results = 200
while True:
    query_results = graphql_query(query.format(cursor=cursor))
    search_response = query_results["data"]["search"]
    pullrequests = to_dataframe(search_response["nodes"])
    if all_results is not None:
        all_results = all_results.append(pullrequests, ignore_index=True)
    else:
        all_results = pullrequests
    if len(all_results) >= max_results:
        break
    page_info = search_response["pageInfo"]
    has_next_page = page_info["hasNextPage"]
    if has_next_page:
        cursor = f'"{page_info["endCursor"]}"'
    else:
        break

#print(all_results)
print(all_results.to_html())
