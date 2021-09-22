# An example to get the remaining rate limit using the Github GraphQL API.
import os
import pprint
import requests


def run_query(
    query, headers
):  # A simple function to use requests.post to make the API call. Note the json= section.
    request = requests.post('https://api.github.com/graphql',
                            json={'query': query},
                            headers=headers)
    if request.status_code == 200:
        return request.json()
    else:
        raise Exception(
            "Query failed to run by returning code of {}. {}".format(
                request.status_code, query))


query = """
{
  repository(owner:"martyngigg", name:"sandbox") {
    pullRequest(number:45) {
      mergeable
    }
  }
}
"""

headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
result = run_query(query, headers)  # Execute the query
pprint.pprint(result)
