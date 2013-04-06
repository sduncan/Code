var map;
var geocoder;
var directionDisplay;
var directionsService = new google.maps.DirectionsService();
var styles;
var minZoomLevel = 10;
var maxZoomLevel = 19;
var searchResults = [];
var user_loc;

var index = 0;
var text = "My name is Robert Neville. I am a survivor living in New York City. I am broadcasting on all AM frequencies. I will be at the South Street Seaport everyday at mid-day, when the sun is highest in the sky. If you are out there... if anyone is out there... I can provide food, I can provide shelter, I can provide security. If there's anybody out there... anybody... please. You are not alone.";

var strictBounds = new google.maps.LatLngBounds(
    new google.maps.LatLng(40.473069,-74.31015), 
    new google.maps.LatLng(40.922852,-73.693542)
);

$(document).ready(function(){
    $('#address').keydown(function(){
	if(event.keyCode == 13){
	    $.getJSON($SCRIPT_ROOT + "/get_Address", {
		a: $('#address').val()
	    }, function(data){
		$('#user_location').text(data.result);
		codeAddress(data.result);
		user_loc = data.result;
	    });
	    return false;
	}
    });
    $('#facilitychoose').change(function(){
	var str = $('#facilitychoose').val();
	$.getJSON($SCRIPT_ROOT + "/get_Nearby", {
	    r: 5000,
	    t: str,
	    o: user_loc
	}, function(data){
	    displayF(data.result);
	});
	return false;		
    });
    $('#faclist li').click(function(){
	var str = "#"+this.id+"em";
	codeAddress($(str).html());
    });
    $('#mylocurl').click(function(){
	$('#start').val(user_loc);
    });
    $("#trigger").click(function(){
	$("#panel").toggle("fast");
	return false;
    });
    $('#start, #end').keydown(function(){
	if(event.keyCode == 13){
	    calcRoute();
	}
	else
	    $('#directionsgmap').css('display','none');
    });   
    $('#mode').bind('change',function(){
	calcRoute();
    });
    $('#message').click(function(){
	codeAddress('South Street Seaport');
    });
    $('#bmessage').click(function(){
	type();
	$('#bmessage').html('<span class="icon medium darkgray" data-icon="9" style="display: inline-block"><span aria-hidden="true">9</span></span></span> (0) Incoming Message');
    });
    showModal();
});

//GOOGLE API
function initialize(){
    geocoder = new google.maps.Geocoder();
    directionsDisplay = new google.maps.DirectionsRenderer();
    var latlng = new google.maps.LatLng(40.720461,-74.013519);
    var mapOptions = {
	zoom: minZoomLevel,
	center: new google.maps.LatLng(40.720461,-74.013519),
	mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById('map_canvas'),
			      mapOptions);
    directionsDisplay.setMap(map);

    google.maps.event.addListener(map, 'zoom_changed', function() {
	if(map.zoom < minZoomLevel) map.setZoom(minZoomLevel);
	if(map.zoom > maxZoomLevel) map.setZoom(maxZoomLevel);
    });

    google.maps.event.addListener(map, 'dragend', function() {
	if (strictBounds.contains(map.getCenter())) return;
	var c = map.getCenter(),
        x = c.lng(),
        y = c.lat(),
        maxX = strictBounds.getNorthEast().lng(),
        maxY = strictBounds.getNorthEast().lat(),
        minX = strictBounds.getSouthWest().lng(),
        minY = strictBounds.getSouthWest().lat();
	
	if (x < minX) x = minX;
	if (x > maxX) x = maxX;
	if (y < minY) y = minY;
	if (y > maxY) y = maxY;
	
	map.setCenter(new google.maps.LatLng(y, x));
    });
    
    var input = document.getElementById('target');
    var searchBox = new google.maps.places.SearchBox(input);
    var markers = [];
    
    google.maps.event.addListener(searchBox, 'places_changed', function() {
        var places = searchBox.getPlaces();

        for (var i = 0, marker; marker = markers[i]; i++) {
            marker.setMap(null);
        }
	
        markers = [];
        var bounds = new google.maps.LatLngBounds();
	for (var i = 0, place; place = places[i]; i++) {
	    var temp = {"name": place.name,
			"address": place.formatted_address
		       };
	    searchResults.push(temp);
	    
	    var marker = new google.maps.Marker({
		map: map,
		title: place.name,
		animation: google.maps.Animation.DROP,
		position: place.geometry.location
            });
 
	    markers.push(marker);
	    
           bounds.extend(place.geometry.location);
        }
	
        map.fitBounds(bounds);
    });
    
   google.maps.event.addListener(map, 'bounds_changed', function() {
        var bounds = map.getBounds();
        searchBox.setBounds(bounds);
    });

}   

function changeMS(str){
    if(str === 'zombies'){
	styles = [
	    {
		stylers: [
		    { "hue": "#ff2b00"},
		    { "saturation": -7 }
		]
	    }];
    }
    else if(str === 'aliens'){
	styles = [
	    {
		stylers: [
		    { "hue": "#08ff00"},
		    { "saturation": -52 }
		]
	    }];
    }
    else{
	styles = [];
    }
    map.setOptions({styles: styles});
}
function codeAddress(str) {
    if(str == null){
	var address = document.getElementById('address').value;
	geocoder.geocode( { 'address': address}, function(results, status) {
            if (status == google.maps.GeocoderStatus.OK) {
		map.setCenter(results[0].geometry.location);
		var marker = new google.maps.Marker({
		    animation: google.maps.Animation.DROP,
		    map: map,
                    position: results[0].geometry.location
		});
            } else {
		alert('Geocode was not successful for the following reason: ' + status);
            }
	});
    }
    else{
	var address = str;
	geocoder.geocode( { 'address': address}, function(results, status) {
            if (status == google.maps.GeocoderStatus.OK) {
		map.setCenter(results[0].geometry.location);
		var marker = new google.maps.Marker({
		    animation: google.maps.Animation.DROP,
                    map: map,
                    position: results[0].geometry.location
		});
            } else {
		alert('Geocode was not successful for the following reason: ' + status);
            }
	});
    }
    map.setZoom(15);
}

function calcRoute() {
    var start = document.getElementById('start').value;
    var end = document.getElementById('end').value;
    var selectedMode = document.getElementById('mode').value.toUpperCase();
    var request = {
        origin:start,
        destination:end,
        travelMode: google.maps.TravelMode[selectedMode]
    };
    directionsService.route(request, function(response, status) {
        if (status == google.maps.DirectionsStatus.OK) {
            directionsDisplay.setDirections(response);
        }
    });
    var tempurl = "https://maps.google.com/maps?q=from:"+start+"+to:"+end;
    $('#directionsgmap').attr('href',tempurl);
    $('#directionsgmap').css('display','inline');
    displayAPIvalues();
}
// END GOOGLE STUFF
function displayAPIvalues(){
    $.getJSON($SCRIPT_ROOT + "/distance_From", {
	o: $('#start').val(),
	d: $('#end').val(),
	m: $('#mode').val()
    }, function(data){
	var str = "Distance: "+data.result;
	$('#distFrom').text(str);
	$('#distFrom').css('display','inline');
    });
    $.getJSON($SCRIPT_ROOT + "/duration_To", {
	o: $('#start').val(),
	d: $('#end').val(),
	m: $('#mode').val(),
    }, function(data){
	var str = "Est Travel Time: "+data.result;
	$('#durTo').text(str);
	$('#durTo').css('display','inline');
    });
    return false;
}
function displayF(data){
    var len = data.length;
    if(len > 10)
	len = 10;
    for(i = 1; i <= len; i++){
	name = data[i-1]['name'];
	address = data[i-1]['address'];
	distance = data[i-1]['distance'];
	var str = "#" + i;
	var str1 = '<address><p>'+name+'<br /><em id="'+i+'em">'+address+'</em><br />'+distance+'</p></address>';
	$(str).html(str1);
    }
    $('#faclist').css('display','inline');
}
function showModal(){
    $('#myModal').modal('show');
}

function type(){
    document.getElementById('message').innerHTML += text.charAt(index);
    index += 1;
    var t = setTimeout('type()',50);
}

function changeBGC(str){
    if(str==='aliens'){
	$('#timedate').css('display','none');
	$('#nhc').css('display','none');
	$('#about_text').html('<p> An Alien is simply any denizen of the universe that isn’t native to planet Earth. Aliens come in many shapes and sizes, but they all have a deeply profound (and totally not personal, they promise) need to extinguish the human race, born from years of deep, calculated and logical though which cumulated in the decision that another hyperspace bypass was in order (which of course requires that the planet remain intact, but that all life forms on it be destroyed).</p>');
	$('#helpful_tips_text').html("<ul><li>Do not pet or feed the aliens</li><li>Identify what you are dealing with and determine whether or not you should be panicking</li><li>Different aliens have different weaknesses, so try to take advantage of that (the worst you can do is make it mad)</li></ul><h6>In case all life forms on Earth face extinction:<ul><li>Grab your towel</li><li>Grab your copy of the Guide</li><li>Hitch a ride to the nearest spaceship (yes, even if they are Vogons)</li></ul>");
	$('#radiomessage').css('display','none');
	$('#disaster').text('Alien Invasion');
	$('#wheel').css('display','inline');
	$('#wheel').carousel('cycle');
	$('body,html,#map_canvas').css('background','-webkit-linear-gradient(-45deg, #aebcbf 0%,#6e7774 50%,#0a0e0a 51%,#0a0809 100%)');
	changeMS('aliens');
    }
    else if(str==='fire'){
	$('#timedate').css('display','inline');
	$('#nhc').css('display','none');
	$('#radiomessage').css('display','none');
	$('#wheel').css('display','none');
	$('body,html,#map_canvas').css('background','-webkit-linear-gradient(-45deg, #fceabb 0%,#fccd4d 50%,#f8b500 51%,#fbdf93 100%)');
	changeMS('fire');
    }
    else if(str==='hurricane'){
	$('#timedate').css('display','none');
	$('#nhc').css('display','inline');
	$('#about_text').html('<p>A Hurricane is a large storm comprised of clouds, thunder, lightning, wind, and rain. It typically has an eye, but it is blind. Calling yourself &#8217Nobody&#8217 will not save you from a Hurricane however, as they tend to disregard this sort of thing. Hurricanes are born when the spirits of angry drowned marching-band brass players get together and decide to ruin everyone else&#8217s parade. Typically, Apocalyptic Hurricanes occur when the spirits of rival marching bands run into each other and try to outdo the other&#8217s Hurricane which really just results in one big mess much to the distress of those still living.</p>');
	$('#helpful_tips_text').html('<ul><li>Don&#8217t go outside. Seriously, you might get knocked off by all manner of objects caught in the wind: branches, bricks, or even turkeys. And turkeys are not a nice way to go.</li><li>Stock up on foodstuffs. In the days after the hurricane has died down, you can use the food as leverage to get valuable commodities such as year-long subscriptions to WoW.</li><li>Keep cleaning supplies handy. You never know when the Johnsons might visit.</li><li> In case your house/hovel/cardboard box is destroyed by the Hurricane, immediately find another shelter. No, umbrellas do not count. Unless Rihanna is holding one, in which case you are probably inside a mansion somewhere anyways.</li></ul>');
	$('#radiomessage').css('display','none');
	$('#wheel').css('display','none');
	$('#disaster').text('Hurricane');
	$('body,html,#map_canvas').css('background','-webkit-linear-gradient(-45deg, #6db3f2 0%,#54a3ee 50%,#3690f0 51%,#1e69de 100%)');
	changeMS('hurricane');
    }
    else if(str==='home'){
	$('#timedate').css('display','none');
	$('#nhc').css('display','none');
	$('#radiomessage').css('display','none');
	$('#wheel').css('display','none');
	$('#disaster').text('Home');
	$('body,html,#map_canvas').css('background','-webkit-linear-gradient(-45deg, #6db3f2 0%,#54a3ee 50%,#3690f0 51%,#1e69de 100%)');
	changeMS('home');
    }
	
    else{
	$('#timedate').css('display','none');
	$('#nhc').css('display','none');
	$('#about_text').html('<p>The Zombie is an animated corpse. It is a member of the elitist &#8217Undead&#8217 club, along with the vampires (sparkly and non-sparkly) and average DMV workers. The Zombie enjoys eating human brains, which is why it often goes to great lengths to get its favorite treat. If a Zombie bites a living human being, than that human being first loses fine motor controls, then the ability to play mahjong, and finally the capacity to distinguish between country rock and heavy metal, at which point the transformation is complete. A Zombie Apocalypse involves lots of Zombies getting together and ridding the world of Beliebers. Unfortunately, Zombies can’t really tell the difference between Beliebers and normal humans.</p>');
	$('#helpful_tips_text').html("<ul><li>Don&#8217t start singing that song by Neil Diamond, &#8217Believer&#8217 and &#8217Belieber&#8217 sound waaaaay too similar.</li><li>Get yourself some weapons to fight the Zombies off. They&#8217re scared of Fire and simple magic tricks.</li><li>If you find yourself surrounded with no where to run than you should play Dead. The Grateful Dead, that is; preferably on a massive boom box with tricked-out subwoofers.</li></ul>");
	$('#radiomessage').css('display','inline');
	$('#wheel').css('display','none');
	$('#disaster').text('Zombie Apocalypse');
	$('body,html,#map_canvas').css('background','-webkit-linear-gradient(-45deg, #bfd255 0%,#8eb92a 50%,#72aa00 51%,#9ecb2d 100%)');
	changeMS('zombies');
    }
}