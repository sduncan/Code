var selected = ""; 
var current = "undefined";
var makertop;
var makerleft;
var active = false;
var out;
var setup = false;
var editing = "maker";
var zind = 0;
var currenttoo;
var temp = "";
var i;
var end = "";

function toElement(type) {
    return "<"+type+" class='inpage' id='current' readonly='readonly'></"+type+">";
}

function menuupdate(item) {
    if (item == "maker" && editing != "maker" && zind <= 0) {
	$(".removable").fadeOut();
	$(".removable").remove();
	$(".edit").removeClass("edit");
	editing = "maker";
	$("#colorimg").fadeIn();
	$("#colormap").fadeIn();
	$("#tohidetext").fadeIn();
	$("#backgroundcolor").change(function() {
	$("div#maker").css("background-color",$(this).val());
    });
    }
    if (item != "maker" && editing != item) {
	var alreadyremove = false;
	$("#colorimg").fadeOut();
	$("#colormap").fadeOut();
	$("#tohidetext").fadeOut();
	if ($(".removable").length > 0) {
	    alreadyremove = true;
	}
	editing = item;
	$(".edit").removeClass("edit");
	$(editing).addClass("edit");
	if (!alreadyremove) {setTimeout(function() {$("div#optionsmenu").append("<button id='itemremoval' class='removable' hidden>Remove</button>"); $("button#itemremoval").fadeIn();
	$("button#itemremoval").click(function() {
	    $('div#pagehtml textarea').text(function(index, text){
		tmp = editing.outerHTML
		i = text.indexOf(tmp);
		end = text.substring(i + tmp.length, text.length);
		return i; //text.substring(0, i);
	    });
	    $(".edit").remove();
	    menuupdate("maker");
	});},400);}		    
	zind = 1;
    }
    if ($(editing).context.outerHTML.indexOf("select") >= 0) {
	$("div#optionsmenu").append("<br>Add Options:<input type='text' id='addoption'><input type='submit' id='suboption'>");
	$("#suboption").click(function() {
	    newopt = $("#addoption").val();
	    console.log(newopt);
	    $(editing).append("<option value="+newopt+" selected>"+newopt+"</option>");
	    $("addoption").val("");
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
    $("#toolopen").click(function() {
	$(this).animate({width:'toggle'});
    });
    $("#toolopen").animate({width:'toggle'});
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
	    temp = current;
	    current = "undefined";
	    active = false;
	    $('div#pagehtml textarea').text(function(index, text){ 
		return (text.substring(0, text.length - 14).concat(temp.outerHTML) + "\n</body></html>");
	    });
	}
	else {
	    menuupdate("maker");
	}
    });
}
)