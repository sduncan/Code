import json
import urllib
from bs4 import BeautifulSoup
#max radius = 50000
def getNearby(radius, types):
    searchNearby_url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=40.714623,-74.006605&radius=%s&types=%s&sensor=false&key=AIzaSyAi-0KQ7UfzdbVefQ-v5CVbfyCif25Pq-U"%(radius,types)
    searchNearby_request = urllib.urlopen(searchNearby_url)
    searchNearby_results = json.loads(searchNearby_request.read())
    counter = 0
    for item in searchNearby_results['results']:
        return searchNearby_results['results'][counter]['name']
        return searchNearby_results['results'][counter]['vicinity']
        counter+=1
       
"""
    counter = 0
    maxn = len(searchNearby_results['results'])
    for item in maxn:
        places.append(searchNearby_results['results'][maxn-1]['name'])
        counter+=1
    else:
        print places"""

getNearby("50","food")
