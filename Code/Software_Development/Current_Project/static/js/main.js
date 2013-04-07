var selected = ""; 
var current = "undefined";
var makertop;
var makerleft;
var active = false;
var out;
var setup = false;
var editing = "maker";
var zind;
var currenttoo;

function toElement(type) {
    return "<"+type+" class='inpage' id='current' readonly='readonly'></"+type+">";
}

function menuupdate(item) {
    if (item == "maker" && editing != "maker" && zind <= 0) {
	$("div#optionsmenu").empty();
	$(".edit").removeClass("edit");
	editing = "maker";
	$("div#optionsmenu").append("Select Background Color: <input type='color' id='backgroundcolor'  name='points' min='1' max='10'>");
	$("#backgroundcolor").change(function() {
	$("div#maker").css("background-color",$(this).val());
    });
    }
    if (item != "maker") {
	editing = item;
	$(".edit").removeClass("edit");
	$(editing).addClass("edit");
	$("div#optionsmenu").empty();
	$("div#optionsmenu").append("<button id='itemremoval'>Remove</button>")
	$("button#itemremoval").click(function() {
	    $(".edit").remove();
	    menuupdate("maker");
	});
	zind = 1;
    }
    console.log($(editing).context.outerHTML)
    if ($(editing).context.outerHTML.indexOf("select") >= 0) {
	$("div#optionsmenu").append("<input type='text' id='addoption'><input type='submit' id='suboption'>");
	$("#suboption").click(function() {
	    //stuff
	});
    }
}

$(window).ready(function() {
    makertop = $("div#maker").offset().top;
    makerleft = $("div#maker").offset().left;
    coords = {top:makertop,left:makerleft-115};
    $("div#maker").offset(coords);

    $("#TextArea").click(function() {
	selected = "Textarea";
	$("#current").attr("id","");
    });
    $("#Button").click(function() {
	selected = "Button";
	$("#current").attr("id","");
    });
    $("#Dropdown").click(function() {
	selected = "Select"
	$("#current").attr("id","");
    });
    $("#backgroundcolor").change(function() {
	$("div#maker").css("background-color",$(this).val());
    });
    $("div#maker").mouseenter(function(e) {
	$("div#maker").height($("div#maker").height());
	$("div#maker").width($("div#maker").width());
	if (active == false && selected != "" && !out) {
	    $("div#maker").prepend(toElement(selected));
	    current = document.getElementById("current");
	    currentcoords = {left:e.pageX,top:e.pageY};
	    $(current).offset(currentcoords);
	    current.style.zIndex = 0;
	    current.style.position = "absolute";
	    active = true;
	    $(current).height($(current).height())
	    $(current).width($(current).width())
	    selected = "";
	}
	else {
	    if (current != "undefined") {
		active = true;
	    }
	}
	
    });
    $("div#maker").mouseleave(function(e) {
	if (current != "undefined") {
	    active = false;
	    curh = $(current).css("height").replace("px","");
	    curh = parseInt(curh);
	    if (($("div#maker").offset().top+$("div#maker").height())-curh <= e.pageY) {
		$(current).offset({top:($("div#maker").offset().top+$("div#maker").height())-curh,left:e.pageX});
	    }
	    curw = $(current).css("width").replace("px","");
	    curw = parseInt(curw);
	    if (($("div#maker").offset().left+$("div#maker").width())-curw <= e.pageX) {
		$(current).offset({left:($("div#maker").offset().left+$("div#maker").width())-curw,top:e.pageY});
	    }
	}
    });
    $("div#maker").mousemove(function(e) {
	if (active != false && current != "undefined" && !out) {
	    $(current).offset({top:(e.pageY),left:(e.pageX)});
	    if (e.pageY-($("div#maker").offset().top-$(current).height()) >= $("div#maker").height()) {
		$(current).offset({top:e.pageY,left:$(current).offset().left});
		active = false;
		out = true;
	    }	    
	    if ($("div#maker").css("width")+$("div#maker").offset().left-$(current).css("width") >= e.pageX) {
		$(current).offset({left:e.pageX,top:$(current).offset().top});
		active = false;
		out = true;
	    }	    
	}
	if(current != "undefined") {
	    curh = $(current).css("height").replace("px","");
	    curh = parseInt(curh);
	    curw = $(current).css("width").replace("px","");
	    curw = parseInt(curw);
	    if (($("div#maker").height()+$("div#maker").offset().top-curh > e.pageY) && ($("div#maker").width()+$("div#maker").offset().left-curw > e.pageX)) {
		active = true;
		out = false;
	    }
	    else {
		curh = $(current).css("height").replace("px","");
		curh = parseInt(curh);
		if ($("div#maker").offset().top+-curh+$("div#maker").height() < e.pageY) {
		    $(current).offset({top:($("div#maker").offset().top+$("div#maker").height())-curh,left:e.pageX});
		}
		curw = $(current).css("width").replace("px","");
		curw = parseInt(curw);
		if ($("div#maker").offset().left-curw+$("div#maker").width() < e.pageX) {
		    $(current).offset({left:($("div#maker").offset().left+$("div#maker").width())-curw,top:e.pageY});
		}
	    }
	}
    });
    $("div#maker").click(function() {
	if (current != "undefined") {
	    current.style.zIndex = 2;
	    $(current).addClass("placed");
	    $(current).mousedown(function() {
		menuupdate(this);
	    });
	    $(current).mouseup(function(){
		setTimeout(function(){
		    zind = 0;	
		},50);
	    });
	    current = "undefined";
	    active = false;
	}
	else {
	    menuupdate("maker");
	}
    });
}
)