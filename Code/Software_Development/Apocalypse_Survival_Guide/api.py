import json
import urllib
from operator import itemgetter
from bs4 import BeautifulSoup

#place/nearbysearch location=-33.8670522,151.1957362&radius=500

#subject to usage limits. shouldnt be a problem for this project, but we should note it in the readme

def getAddress(query):
    textsearch_url = "https://maps.googleapis.com/maps/api/place/textsearch/json?query=%s&sensor=false&key=AIzaSyAi-0KQ7UfzdbVefQ-v5CVbfyCif25Pq-U"%(query)
    textsearch_request = urllib.urlopen(textsearch_url)
    textsearch_results = json.loads(textsearch_request.read())
    return textsearch_results['results'][0]['formatted_address']

def getLatLong(address):
    geocode_url = "https://maps.googleapis.com/maps/api/geocode/json?address=%s&sensor=false"%(address)
    maps_request = urllib.urlopen(geocode_url)
    geo_results = json.loads(maps_request.read())
    ans = {'lat':geo_results['results'][0]['geometry']['location']['lat'],
           'long':geo_results['results'][0]['geometry']['location']['lng']
           }
    return ans

def distanceFrom(origins, destinations, mode): 
    distance_url = "http://maps.googleapis.com/maps/api/distancematrix/json?origins=%s&destinations=%s&sensor=false&mode=%s&units=imperial"%(origins, destinations, mode)
    maps_request = urllib.urlopen(distance_url)
    result = json.loads(maps_request.read())
    #print "\n The distance between %s and %s is" % (original, destination)
    return result['rows'][0]['elements'][0]['distance']['text']

def durationTo(origins, destinations, mode): 
    distance_url = "http://maps.googleapis.com/maps/api/distancematrix/json?origins=%s&destinations=%s&sensor=false&mode=%s&units=imperial"%(origins, destinations, mode)
    maps_request = urllib.urlopen(distance_url)
    result = json.loads(maps_request.read())
    #print "\n The time it takes to travel  between %s and %s is" % (original, destination)
    return result['rows'][0]['elements'][0]['duration']['text']

def isPOI(origins):
    geocode_url = "https://maps.googleapis.com/maps/api/geocode/json?address=%s&sensor=false"%(origins)
    maps_request = urllib.urlopen(geocode_url)
    geo_results = json.loads(maps_request.read())
    if(geo_results['results'][0]['types'].count('point_of_interest') == 1):
        return "Yes"
    else:
        return "No"

def getFacilityList(origin, category, mode, key, sensor): 
    facilityList_url = "http://www.nyc.gov/portal/apps/311_contentapi/facilities/%s.json"%(category)
    facilityList_request = urllib.urlopen(facilityList_url)
    facilityList_results = json.loads(facilityList_request.read())
    facilities = [] 
    fac_in_order = []
    dist_in_order = []
    for item in facilityList_results:
        facilities.append(item["facility_name"])
    facilities.sort()
    return facilities
"""
    for facility in facilities:
        print "\n", facility
        #fac_add = getAddress(facility, key, sensor)
        #dist = 
        #print distanceFrom(origin, fac_add, mode)
        dist_in_order.append(dist)
        if len(fac_in_order) == 0: 
            fac_in_order.append(facility)
        else:
            if getattr(facility,dist) > getattr(fac_in_order[0],dist):
                fac_in_order.append(facility)
            else:
                for a in fac_in_order:
                    if getattr(facility,dist) <= getattr(a,dist):
                        fac_in_order.insert((fac_in_order.index(a)), facility)
        dist_in_order.sort()
        print fac_in_order
        print dist_in_order
"""
#max radius = 50000
#returns dict of nearby results sorted by dist
# keys: 'name', 'address', 'distance'
def getNearby(radius, types, orig):
    latlong = getLatLong(orig)
    lat = latlong['lat']
    lng = latlong['long']
    searchNearby_url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location="+str(lat)+","+str(lng)+"&radius=%s&types=%s&sensor=false&key=AIzaSyAi-0KQ7UfzdbVefQ-v5CVbfyCif25Pq-U"%(radius,types)
    searchNearby_request = urllib.urlopen(searchNearby_url)
    searchNearby_results = json.loads(searchNearby_request.read())
    ans = []
    counter = 0;
    for item in searchNearby_results['results']:
        name = searchNearby_results['results'][counter]['name']
        address = searchNearby_results['results'][counter]['vicinity']
        dist = distanceFrom(orig,address,'driving')
        temp = {'name':name,
                        'address':address,
                        'distance':dist
                        }
        ans.append(temp)
        counter+=1
    ans = sorted(ans, key=lambda k: k['distance']) 
    return ans

key = "AIzaSyAi-0KQ7UfzdbVefQ-v5CVbfyCif25Pq-U"
destination = "97 Warren Street"
m = "TRANSIT" 
original = "345 Chambers Street, New York, NY, United States"
