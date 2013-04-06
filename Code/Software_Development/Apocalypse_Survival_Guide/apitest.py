import json
import urllib
from bs4 import BeautifulSoup

#place/nearbysearch location=-33.8670522,151.1957362&radius=500

def test(address):
    geocode_url = "https://maps.googleapis.com/maps/api/geocode/json?address=%s&sensor=false"%(address)
    maps_request = urllib.urlopen(geocode_url)
    geo_results = json.loads(maps_request.read())
    print("\n google maps: ")
    print geo_results['results'][0]['formatted_address']
    print("\n")

a = "345 Chambers Street, New York"
test(a)


def test2():
    distance_url = "http://maps.googleapis.com/maps/api/distancematrix/json?origins=345+Chambers+Street+New+York+NY&destinations=Brooklyn+NY&sensor=false&mode=walking&units=imperial"
    maps_request = urllib.urlopen(distance_url)
    result = json.loads(maps_request.read())
    print("distance: ")
    print result['rows'][0]

key='AIzaSyCM_M56XMiApQyGP8gYGVafJmix15AcUng'
loc="40.714353,-74.005973"
radius="30000"
tag="park"

test2()


