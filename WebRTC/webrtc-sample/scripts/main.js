// <!-- hide script from old browsers

var vidyoClientObj = null;

// configuration of behavior for this code
var useConsoleForLogging = true;
var useAlertsForLogging = false;
var useWebRTC = true;

// var sessionManager = 'webrtcapi.vidyo.com'; * Deprecated *
var sessionManager = 'vwebrtc.vidyocloud.com';

if (useWebRTC) {
    var pluginType = 'VidyoWebRTC';
} else {
    var pluginType = 'VidyoWeb';
}
var willStartOnLoad = true;			// if true, will invoke start() on plug-in object from bodyLoaded()

// Toggle Icon code
var img_camera_array= new Array('./images/camera_privacy.png','./images/camera.png');
var img_mic_array= new Array('./images/mic_mute.png','./images/mic.png');
var img_speaker_array= new Array('./images/speaker_mute.png','./images/speaker.png');
var img_share_array= new Array('./images/unshare.png','./images/share.png');
var count_camera=-1;
var count_mic=-1;
var count_speaker=-1;
var count_share=-1;
var numberOfShares = 0;
var participantsCount;


function isChrome() {
    // This method returns true if the running browser is Google Chrome version 42+
    // if (navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
    // 	navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42) {
    if ((navigator.appVersion.indexOf("Win")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1) ||
          (navigator.appVersion.indexOf("Mac")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
           navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42)){
        return true;
    } else {
        return false;
    }
}

function toggle(div_id) {
	var el = document.getElementById(div_id);
	if ( el.style.display == 'none' ) {	el.style.display = 'block';}
	else {el.style.display = 'none';}
}



function getUrlVars() {
    var vars = {};
    var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
        vars[key] = value;
    });
    return vars;
}
	
function toggleCameraIcon()
{
    count_camera++;
    document.getElementById("img_camera").src=img_camera_array[count_camera];
    if(count_camera==0)
        sendMuteCameraEvent();
    else
        sendUnmuteCameraEvent();
    if(count_camera==img_camera_array.length-1) {
        count_camera=-1;
    }
}

	function toggleMicIcon()
	{
    	count_mic++;
    	document.getElementById("img_mic").src=img_mic_array[count_mic];
    	if(count_mic==0)
    		sendMuteMicEvent();
    	else
    		sendUnmuteMicEvent();
    	if(count_mic==img_mic_array.length-1) {
   		count_mic=-1;
	    }
    }

	function toggleSpeakerIcon()
	{
    	count_speaker++;
    	document.getElementById("img_speaker").src=img_speaker_array[count_speaker];
    	if(count_speaker==0)
    		sendMuteSpeakerEvent();
    	else
    		sendUnmuteSpeakerEvent();
    	if(count_speaker==img_speaker_array.length-1) {
   		count_speaker=-1;
	    }
    }

	// helper function declarations
	var getVidyoClient = function () {
        return vidyoClientObj;
        //return document.getElementById('pluginObject');
	};
	var log = function (msg) {
		if (useConsoleForLogging) {
			console.log(msg);
		}
		if (useAlertsForLogging) {
			alert(msg);
		}
	};


    /**
     * Select remote share to see
     * @param  {Int} currApp ID of share to see
     * @return {Object} Currently available shares
     */
    var clientSharesGet = function () {
        var that = {};
        that.type = "RequestGetWindowShares";

        // public properties for created object,
        // initial values of which are potentially passed
        // into this factory function
        that.requestType ="";// params && params.requestType || "";
        that.remoteAppUri = [""];//params && params.remoteAppUri || [""];
        that.remoteAppName = [""];// params && params.remoteAppName || [""];
        that.numApp = 0;// params && params.numApp || 0;
        that.currApp = 0;// params && params.currApp || 0;
        that.eventUri = "";// params && params.eventUri || "";
        that.newApp =  0;//params && params.newApp || 0;
        
        var msg;
        if (getVidyoClient().sendRequest(that)) {
            msg = pluginType + " sent " + that.type + " request successfully";
        } else {
            msg = pluginType + " did not send " + that.type + " request successfully!";
        }
        return that;
    };

    
    /**
     * Select remote share to see
     * @param  {String} currApp ID of share to make watch
     * @return {Object} number of current shares
     */
    var clientSharesSetCurrent = function (newURI) {
        var request = clientSharesGet();
        var shares = request.numApp;
        if (newURI){
            for (i = 0; i < request.numApp; i++){
                if (request.remoteAppUri[i]==newURI){
                    request.newApp = i+1;
                    break;
                }
            }
        }else{
            request.newApp = request.numApp;
        }
        request.type = "RequestSetWindowShares";
        request.requestType = "ChangeSharingWindow";

        var msg;

        if (getVidyoClient().sendRequest(request)) {
            msg = pluginType + " sent " + request.type + " request successfully";
        } else {
            msg = pluginType + " did not send " + request.type + " request successfully!";
        }
        numberOfShares = request.newApp;
        if (numberOfShares > 0)
            adjustLayoutWithShare();
        else
            adjustLayout();

        return shares;
    };


	// declarations for functions, wired to plugin events
	var onOutEvent = function (event) {
        var log_mesg;
	event = event || {};
	var msg = "Received out event with type of " + event.type;
	//alert(msg);
	log(msg);
    if        (event.type == 'OutEventPluginConnectionSuccess'){
        if (willStartOnLoad) {
            sendGuestLogin();
        }
	} else if (event.type == 'OutEventSignIn'){
        if (parseInt(event.activeEid, 10) === 0){
            var licenseEvent = {
                'type': "InEventLicense" 
            };
            getVidyoClient().sendEvent(licenseEvent); 
        }
	} else if (event.type == 'OutEventConferenceActive'){
        document.getElementById("VidyoSplash").className = 'videoWrapperSmall';
        document.getElementById("VidyoArea").className = 'videoFull';
        toggle('VidyoSplash');
        toggle('Buttons');
    } else if (event.type == 'OutEventConferenceEnded'){
        document.getElementById("VidyoSplash").className = 'videoWrapperFull';
        document.getElementById("VidyoArea").className = 'videoWrapperSmall';
        toggle('VidyoSplash');
        toggle('loaderBar');
        toggle('Buttons');
        getVidyoClient().stop();
    } else if (event.type == 'OutEventJoinProgress'){
        //does not occur in WebRTC
    } else if (event.type == 'OutEventAddShare'){
        log_mesg = "Share added from URI: " + event.URI;
        log(log_mesg);
        var params;
        clientSharesSetCurrent(event.URI);
    }else if (event.type == 'OutEventRemoveShare'){
        var shares = clientSharesSetCurrent();
    }else if (event.type == 'OutEventVideoStreamsChanged'){
        participantsCount = event.streamCount;
        adjustLayout();
    }
    
    //log(event);
    /*var name;
    for (name in event) {
    log(name + ": " + event[name]);
    }*/
	};
	
	// declarations for functions, wired to lifecycle events
	var bodyLoaded = function () {
        if (!isChrome()){
            var query = window.location.search.substring(1);
            window.location.replace('https://vidyoweb.apps.vidyo.com/dual?' + query);
        }else{
            document.getElementById("VidyoSplash").className = 'videoWrapperFull';
            document.getElementById("VidyoSplash").style.display = 'block';

            vidyoClientObj = vidyoClient();
            vidyoClientObj.setDefaultOutEventCallbackMethod("onOutEvent");
            vidyoClientObj.setOutEventCallbackObject(this);
            vidyoClientObj.setLogCallback(log);
            vidyoClientObj.setSessionManager(sessionManager);
            start();
        }
	};

    // declarations for functions, wired to clicking of page hyperlinks
	var start = function ()	{
		var msg;
		if (getVidyoClient().start()) {
			msg = pluginType + 'started successfully';
		} else {
			msg = pluginType + 'did not start successfully!';
			alert(msg);
		}
		log(msg);
	}  
	
	var sendGuestLogin = function () {
        var portalUri = getUrlVars()["portalUri"];
        if (!portalUri){
            return 0;
        }
        var encoded = getUrlVars()["encoded"];
        if (!encoded || (parseInt(encoded,10)==0)){
            encoded = 0;
        }else{
            encoded = 1;
        }
        var portalRes;
        var roomKey;

        if (encoded){
            var temp = decodeURIComponent(portalUri);
            portalRes = temp.split("\/flex.html\?roomdirect.html&key=");
            portalUri = portalRes[0];
            roomKey = portalRes[1];
        }else{
            portalRes = portalUri.split("\/flex.html\?roomdirect.html");
            portalUri = portalRes[0];
            var roomKey = getUrlVars()["key"];
        }

        var joinPath = "\/join\/";
        /* Room key undefined. Check VidyoConnect room link type. */
        if (!roomKey && portalUri.search(joinPath) != -1) {
            portalRes = portalUri.split(joinPath);

            portalUri = portalRes[0];
            roomKey = portalRes[1];
        }

        var guestName = getUrlVars()["guestName"];
        if (!guestName){
            guestName = "Guest";

        }
        guestName = guestName.replace("+"," ");
        var roomPin = getUrlVars()["roomPin"];
        if (roomPin){
            var inEvent = {
                    'type': "PrivateInEventVcsoapGuestLink",
                    'typeRequest': "GuestLink",
                    'requestId': 1234,
                    'portalUri': portalUri,
                    'roomKey': roomKey,
                    'pin': roomPin,
                    'guestName': guestName
                };
        }else{
            var inEvent = {
                    'type': "PrivateInEventVcsoapGuestLink",
                    'typeRequest': "GuestLink",
                    'requestId': 1234,
                    'portalUri': portalUri,
                    'roomKey': roomKey,
                    'pin': '',
                    'guestName': guestName
                };
        }
        var msg;
        if (getVidyoClient().sendEvent(inEvent)) {
            msg = pluginType + " sent guest login event successfully";
        } else {
            msg = pluginType + " not sent guest login event successfully!";
            alert(msg);
        }
        log(msg);
    };
    
    var toggleShare = function () {
        var msg;
        var inEvent = {};
        
        count_share++;
        document.getElementById("img_share").src=img_share_array[count_share];
        if(count_share==0){
            inEvent.type = "InEventShare";
            inEvent.shareType = "DesktopWindow";
            inEvent.window = "1";
        }else{
            inEvent.type = "InEventUnshare";
        }
        if(count_share==img_share_array.length-1) {
            count_share=-1;
        }    

		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent " + inEvent.type + " successfully";
		} else {
			msg = pluginType + " not in a call!";
			alert(msg);
		}
		log(msg);
	};

    
	var sendLeaveEvent = function () {
		var inEvent = {
			'type': "InEventLeave"
		};
		var msg;
		// Make sure you reduce the size of the VidyoWeb Plugin renderer now, 
		// otherwise you will see artifacts related to OpenGL
		// document.getElementById("pluginObject").style.width="1px";
		// document.getElementById("pluginObject").style.height="1px";

		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent leave event successfully";
		} else {
			msg = pluginType + " not in a call!";
			alert(msg);
		}
		log(msg);
	};

	var sendMuteCameraEvent = function () {
		var inEvent = {
			'type': "InEventMuteVideo",
			'willMute': true
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Camera successfully";
		} else {
			msg = pluginType + " could not send Mute Camera successfully!";
			alert(msg);
		}
		log(msg);
	};

	var sendUnmuteCameraEvent = function () {
		var inEvent = {
			'type': "InEventMuteVideo",
			'willMute': false
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Camera successfully";
		} else {
			msg = pluginType + " could not send Mute Camera successfully!";
			alert(msg);
		}
		log(msg);
	};

	var sendMuteMicEvent = function () {
		var inEvent = {
			'type': "InEventMuteAudioIn",
			'willMute': true
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Mic successfully";
		} else {
			msg = pluginType + " could not send Mute Mic successfully!";
			alert(msg);
		}
		log(msg);
	};

	var sendUnmuteMicEvent = function () {
		var inEvent = {
			'type': "InEventMuteAudioIn",
			'willMute': false
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Mic successfully";
		} else {
			msg = pluginType + " could not send Mute Mic successfully!";
			alert(msg);
		}
		log(msg);
	};

	var sendMuteSpeakerEvent = function () {
		var inEvent = {
			'type': "InEventMuteAudioOut",
			'willMute': true
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Speaker successfully";
		} else {
			msg = pluginType + " could not send Speaker Mic successfully!";
			alert(msg);
		}
		log(msg);
	};

	var sendUnmuteSpeakerEvent = function () {
		var inEvent = {
			'type': "InEventMuteAudioOut",
			'willMute': false
		};
		var msg;
		if (getVidyoClient().sendEvent(inEvent)) {
			msg = pluginType + " sent Mute Speaker successfully";
		} else {
			msg = pluginType + " could not send Mute Speaker successfully!";
			alert(msg);
		}
		log(msg);
	};


    /* Function to resize the display layout,as follows. (Shivanand)
    1 participant - Full window.
    2 participants - 2 equally divided windows with top and bottom offset.
    3 participants - Grid layout having four boxes with one empty and 3 for participants
    4 participants - Grid layout having four boxes for 4 participants participants.
    More than 4 - Grid layout having four boxes for 4 participants and don't show remaining
   */
    var adjustLayout = function() {
        
        if (numberOfShares) {
            adjustLayoutWithShare();
        } else {
            
            //setParticipantStripVisibility();
            
            document.getElementById("shareVideoDiv").style.display = "none";
            
            var participantDiv0 = document.getElementById("participantDiv0");
            var participantDiv1 = document.getElementById("participantDiv1");
            var participantDiv2 = document.getElementById("participantDiv2");
            var participantDiv3 = document.getElementById("participantDiv3");
            var selfViewDiv     = document.getElementById("selfViewDiv");
            switch (participantsCount) {
                case 0:
                    selfViewDiv.style.width  = "25%";
                    selfViewDiv.style.height = "25%";
                    selfViewDiv.style.left   = "75%";
                    selfViewDiv.style.top    = "75%";
                    break;

                case 1:
                    participantDiv0.style.width = "100%";
                    participantDiv0.style.height = "100%";
                    participantDiv0.style.top = "0%";
                    participantDiv0.style.left = "0%";

                    selfViewDiv.style.width  = "25%";                        
                    selfViewDiv.style.height = "25%";
                    selfViewDiv.style.left   = "75%";
                    selfViewDiv.style.top    = "75%";

                    break;
                case 2:
                    participantDiv0.className = "participant-wrapper";
                    participantDiv0.style.top = "0%";
                    participantDiv0.style.left = "0%";
                    participantDiv0.style.width = "75%";
                    participantDiv0.style.height = "100%";
                    
                    participantDiv1.className = "participant-wrapper";
                    participantDiv1.style.top = "0%";
                    participantDiv1.style.left = "75%";
                    participantDiv1.style.width = "25%";
                    participantDiv1.style.height = "50%";

                    selfViewDiv.className = "local-participant-wrapper";
                    selfViewDiv.style.top = "50%";
                    selfViewDiv.style.left = "75%";
                    selfViewDiv.style.width = "25%";
                    selfViewDiv.style.height = "50%";
    
                    break;
                case 3:
                    participantDiv0.className = "participant-wrapper";
                    participantDiv0.style.top = "0%";
                    participantDiv0.style.left = "0%";
                    participantDiv0.style.width = "75%";
                    participantDiv0.style.height = "100%";
                    
                    participantDiv1.className = "participant-wrapper";
                    participantDiv1.style.top = "0%";
                    participantDiv1.style.left = "75%";
                    participantDiv1.style.width = "25%";
                    participantDiv1.style.height = "33%";

                    participantDiv2.className = "participant-wrapper";
                    participantDiv2.style.top = "33%";
                    participantDiv2.style.left = "75%";
                    participantDiv2.style.width = "25%";
                    participantDiv2.style.height = "33%";

                    selfViewDiv.className = "local-participant-wrapper";
                    selfViewDiv.style.top = "66%";
                    selfViewDiv.style.left = "75%";
                    selfViewDiv.style.width = "25%";
                    selfViewDiv.style.height = "33%";
    
                    break;
                case 4:
                default:
                    participantDiv0.className = "participant-wrapper";
                    participantDiv0.style.top = "0%";
                    participantDiv0.style.left = "0%";
                    participantDiv0.style.width = "75%";
                    participantDiv0.style.height = "100%";

                    participantDiv1.className = "participant-wrapper";
                    participantDiv1.style.top = "0%";
                    participantDiv1.style.left = "75%";
                    participantDiv1.style.width = "25%";
                    participantDiv1.style.height = "25%";

                    participantDiv2.className = "participant-wrapper";
                    participantDiv2.style.top = "25%";
                    participantDiv2.style.left = "75%";
                    participantDiv2.style.width = "25%";
                    participantDiv2.style.height = "25%";

                    participantDiv3.className = "participant-wrapper";
                    participantDiv3.style.top = "50%";
                    participantDiv3.style.left = "75%";
                    participantDiv3.style.width = "25%";
                    participantDiv3.style.height = "25%";

                    selfViewDiv.className = "local-participant-wrapper";
                    selfViewDiv.style.top = "75%";
                    selfViewDiv.style.left = "75%";
                    selfViewDiv.style.width = "25%";
                    selfViewDiv.style.height = "25%";

                    break;

            }
        }   
    }

    var adjustLayoutWithShare = function() {
        setParticipantStripVisibility();
        
        var participantDiv0 = document.getElementById("participantDiv0");
        var participantDiv1 = document.getElementById("participantDiv1");
        var participantDiv2 = document.getElementById("participantDiv2");
        var participantDiv3 = document.getElementById("participantDiv3");
        var shareVideoDiv   = document.getElementById("shareVideoDiv");
        var selfViewDiv     = document.getElementById("selfViewDiv");
        participantDiv3.style.display = "none";

        switch (participantsCount) {
            case 0:
                shareVideoDiv.style.width = "100%";
                shareVideoDiv.style.height = "100%";
                shareVideoDiv.style.top = "0%";
                shareVideoDiv.style.left = "0%";
                
                selfViewDiv.style.width  = "25%";                        
                selfViewDiv.style.height = "25%";
                selfViewDiv.style.left   = "75%";
                selfViewDiv.style.top    = "75%";
                
                break;

            case 1:
                shareVideoDiv.className = "participant-wrapper";
                shareVideoDiv.style.top = "0%";
                shareVideoDiv.style.left = "0%";
                shareVideoDiv.style.width = "75%";
                shareVideoDiv.style.height = "100%";
                
                participantDiv0.className = "participant-wrapper";
                participantDiv0.style.top = "0%";
                participantDiv0.style.left = "75%";
                participantDiv0.style.width = "25%";
                participantDiv0.style.height = "50%";
                
                selfViewDiv.className = "local-participant-wrapper";
                selfViewDiv.style.top = "50%";
                selfViewDiv.style.left = "75%";
                selfViewDiv.style.width = "25%";
                selfViewDiv.style.height = "50%";
                
                break;
            case 2:
                shareVideoDiv.className = "participant-wrapper";
                shareVideoDiv.style.top = "0%";
                shareVideoDiv.style.left = "0%";
                shareVideoDiv.style.width = "75%";
                shareVideoDiv.style.height = "100%";
                
                participantDiv0.className = "participant-wrapper";
                participantDiv0.style.top = "0%";
                participantDiv0.style.left = "75%";
                participantDiv0.style.width = "25%";
                participantDiv0.style.height = "33%";
                
                participantDiv1.className = "participant-wrapper";
                participantDiv1.style.top = "33%";
                participantDiv1.style.left = "75%";
                participantDiv1.style.width = "25%";
                participantDiv1.style.height = "33%";
                
                selfViewDiv.className = "local-participant-wrapper";
                selfViewDiv.style.top = "66%";
                selfViewDiv.style.left = "75%";
                selfViewDiv.style.width = "25%";
                selfViewDiv.style.height = "33%";
                
                break;
            case 3:
            default:
                shareVideoDiv.className = "participant-wrapper";
                shareVideoDiv.style.top = "0%";
                shareVideoDiv.style.left = "0%";
                shareVideoDiv.style.width = "75%";
                shareVideoDiv.style.height = "100%";
                
                participantDiv0.className = "participant-wrapper";
                participantDiv0.style.top = "0%";
                participantDiv0.style.left = "75%";
                participantDiv0.style.width = "25%";
                participantDiv0.style.height = "25%";
                
                participantDiv1.className = "participant-wrapper";
                participantDiv1.style.top = "25%";
                participantDiv1.style.left = "75%";
                participantDiv1.style.width = "25%";
                participantDiv1.style.height = "25%";

                participantDiv2.className = "participant-wrapper";
                participantDiv2.style.top = "50%";
                participantDiv2.style.left = "75%";
                participantDiv2.style.width = "25%";
                participantDiv2.style.height = "25%";
                
                selfViewDiv.className = "local-participant-wrapper";
                selfViewDiv.style.top = "75%";
                selfViewDiv.style.left = "75%";
                selfViewDiv.style.width = "25%";
                selfViewDiv.style.height = "25%";

                break;
        }   
        
        shareVideoDiv.style.display = "block";
    }
    
    function setParticipantStripVisibility() {
        /*
        // To set the visibility of the title background
        var elements = document
                       .getElementsByClassName("transparent-strip");
        $(".transparent-strip").css("visibility", "hidden");

        for ( var i = 0; i < participantsCount; i++) {
            elements[i].style.visibility = "visible";
        }
        */
        if (numberOfShares) {
            $("#share-video-transparent-strip").css(
                "visibility", "visible");
        } else {
            $("#share-video-transparent-strip").css(
                "visibility", "hidden");
        }
    }


	var stop = function ()	{
		var msg;
		if (getVidyoClient().stop()) {
			msg = pluginType + " stopped successfully";
		} else {
			msg = pluginType + " did not stop successfully!";
			alert(msg);
		}
		log(msg);
	};

    var openGoogleWebstore = function() {
      window.open('https://chrome.google.com/webstore/detail/vidyo-webrtc-screen-share/fadjebjcpiiklefiadeicakcnkhgbaoo', '_blank');
    };

// end hiding script from old browsers -->