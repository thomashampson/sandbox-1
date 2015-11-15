# coding: utf-8
import json
import requests
jenkins_url = "http://builds.mantidproject.org"
slave_url = jenkins_url + "/computer/isis-mantidlx3"
json_api_url = slave_url + "/api/json"
payload = requests.get(json_api_url)
print payload
print payload.content
content = json.loads(payload.content)
content
content.keys()
print content['offline']
print content['temporarilyOffline']
#get_ipython().magic(u'save jenkins_slave_check.ipy 1-15')
