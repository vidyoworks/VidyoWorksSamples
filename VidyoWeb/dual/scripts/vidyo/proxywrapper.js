/*
A wrapper to make calls to VidyoWebProxy the same as calls to the plugin as much as possible.
Wrapper version 0.006
*/

var proxyWrapper = (function() {
	var versionString = 'None';
	var supportedVideoQualityLevels = [
		{ name: 'BestQuality', title: 'Best Quality (Recommended)', intValue: 0 },
		{ name: 'BestFramerate', title: 'Best Frame Rate', intValue: 1 },
		{ name: 'BestResolution', title: 'Best Resolution', intValue: 2 },
		{ name: 'LimitedBandwidth', title: 'Limited Bandwidth', intValue: 3 },
		{ name: 'Advanced450p30', title: 'Advanced: 450p30', intValue: 10 },
		{ name: 'Advanced720p15', title: 'Advanced: 720p15', intValue: 11 },
		{ name: 'Advanced720p30', title: 'Advanced: 720p30', intValue: 12 },
		{ name: '1080p30', title: '1080p30', intValue: 20 }
	];
	// !! Supported versions should be in descending order !!
	// The latest version should be on top and the oldest at the bottom.
	var supportedVersions = (function() {
		if (navigator.appVersion.indexOf('Windows') !== -1) {
			return [
				'1.3.21_0005'
			];
		} else {
			return [
				'1.3.21_0005'
			];
		}
	})();

	var videohandler = videoHandler();

	var dispatchFunction = null;

	var callbacks = {}, timeouts = {};
	var eventNames = {
			99:  'VIDYO_CLIENT_IN_EVENT_MIN',
			100: 'VIDYO_CLIENT_OUT_EVENT_USER_MESSAGE',
			200: 'VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED',
			300: 'VIDYO_CLIENT_OUT_EVENT_SIGN_IN',
			301: 'VIDYO_CLIENT_OUT_EVENT_SIGN_OUT',
			400: 'VIDYO_CLIENT_OUT_EVENT_SUBSCRIBING',
			500: 'VIDYO_CLIENT_OUT_EVENT_APP_EXIT',
			600: 'VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECT',
			601: 'VIDYO_CLIENT_OUT_EVENT_DEVICES_CHANGED',
			602: 'VIDYO_CLIENT_OUT_EVENT_DEVICE_SELECTION_CHANGED',
			603: 'VIDYO_CLIENT_OUT_EVENT_SELECTED_DEVICE_ON_OS_CHANGED',
			700: 'VIDYO_CLIENT_OUT_EVENT_RINGING',
			701: 'VIDYO_CLIENT_OUT_EVENT_RING_PROGRESS',
			702: 'VIDYO_CLIENT_OUT_EVENT_END_RINGING',
			800: 'VIDYO_CLIENT_OUT_EVENT_CALLING',
			801: 'VIDYO_CLIENT_OUT_EVENT_CALL_PROGRESS',
			802: 'VIDYO_CLIENT_OUT_EVENT_END_CALLING',
			900: 'VIDYO_CLIENT_OUT_EVENT_JOINING',
			901: 'VIDYO_CLIENT_OUT_EVENT_JOIN_PROGRESS',
			1000:'VIDYO_CLIENT_OUT_EVENT_RETRYING',
			1001:'VIDYO_CLIENT_OUT_EVENT_RETRY_PROGRESS',
			1100:'VIDYO_CLIENT_OUT_EVENT_END_PROCESSING',
			1200:'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE',
			1201:'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED',
			1202:'VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED',
			1203:'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CLEARED',
			1210:'VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_ADDED',
			1211:'VIDYO_CLIENT_OUT_EVENT_REMOTE_SOURCE_REMOVED',
			1300:'VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL',
			1301:'VIDYO_CLIENT_OUT_EVENT_END_INCOMING_CALL',
			1400:'VIDYO_CLIENT_OUT_EVENT_PREVIEW',
			1500:'VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_IN',
			1501:'VIDYO_CLIENT_OUT_EVENT_MUTED_AUDIO_OUT',
			1502:'VIDYO_CLIENT_OUT_EVENT_MUTED_VIDEO',
			1503:'VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_AUDIO_IN',
			1504:'VIDYO_CLIENT_OUT_EVENT_MUTED_SERVER_VIDEO',
			1600:'VIDYO_CLIENT_OUT_EVENT_ADD_SHARE',
			1601:'VIDYO_CLIENT_OUT_EVENT_REMOVE_SHARE',
			1602:'VIDYO_CLIENT_OUT_EVENT_SHARE_CLOSED',
			1700:'VIDYO_CLIENT_OUT_EVENT_RESIZE',
			1800:'VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_LIMIT',
			1900:'VIDYO_CLIENT_OUT_EVENT_ECHO_DETECTED',
			2000:'VIDYO_CLIENT_OUT_EVENT_KEYDOWN',
			2001:'VIDYO_CLIENT_OUT_EVENT_KEYUP',
			2002:'VIDYO_CLIENT_OUT_EVENT_MOUSE_DOWN',
			2003:'VIDYO_CLIENT_OUT_EVENT_MOUSE_UP',
			2004:'VIDYO_CLIENT_OUT_EVENT_MOUSE_MOVE',
			2005:'VIDYO_CLIENT_OUT_EVENT_MOUSE_SCROLL',
			2006:'VIDYO_CLIENT_OUT_EVENT_TOUCH',
			2007:'VIDYO_CLIENT_OUT_EVENT_FLOATING_WINDOW',
			2100:'VIDYO_CLIENT_OUT_EVENT_FECC_LIST_UPDATED',
			2101:'VIDYO_CLIENT_OUT_EVENT_CONTROL_CAMERA',
			2102:'VIDYO_CLIENT_OUT_EVENT_SET_PARTICIPANT_VIDEO_MODE_DONE',
			2103:'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_INFO_UPDATE',
			2104:'VIDYO_CLIENT_OUT_EVENT_FECC_STATUS_UPDATE',
			2105:'VIDYO_CLIENT_OUT_EVENT_PARTICIPANT_BUTTON_CLICK',
			2200:'VIDYO_CLIENT_OUT_EVENT_MEDIA_CONTROL',
			2300:'VIDYO_CLIENT_OUT_EVENT_LOGIN',
			2301:'VIDYO_CLIENT_OUT_EVENT_LICENSE',
			2302:'VIDYO_CLIENT_OUT_EVENT_LINKED',
			2303:'VIDYO_CLIENT_OUT_EVENT_SIGNED_IN',
			2304:'VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT',
			2305:'VIDYO_CLIENT_OUT_EVENT_ROOM_LINK',
			2306:'VIDYO_CLIENT_OUT_EVENT_CLIENT_VERSION_ON_SERVER',
			2400:'VIDYO_CLIENT_OUT_EVENT_ENABLED_STATUS_BAR',
			2401:'VIDYO_CLIENT_OUT_EVENT_ENABLED_BUTTON_BAR',
			2450:'VIDYO_CLIENT_OUT_EVENT_SELECTED_PARTICIPANTS_CHANGED',
			2500:'VIDYO_CLIENT_OUT_EVENT_CALL_STATE',
			2600:'VIDYO_CLIENT_OUT_EVENT_GROUP_CHAT',
			2601:'VIDYO_CLIENT_OUT_EVENT_PRIVATE_CHAT',
			2700:'VIDYO_CLIENT_OUT_EVENT_ALARMS_RAISED',
			2701:'VIDYO_CLIENT_OUT_EVENT_ALARMS_CLEARED',
			2710:'VIDYO_CLIENT_OUT_EVENT_PORTAL_PREFIX',
			2715:'VIDYO_CLIENT_OUT_EVENT_PORTAL_FEATURES',
			2720:'VIDYO_CLIENT_OUT_EVENT_CPU_USAGE_ACTIONS',
			2800:'VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_STAGE',
			2802:'VIDYO_CLIENT_OUT_EVENT_LECTURE_MODE_PRESENTER_CHANGED',
			2803:'VIDYO_CLIENT_OUT_EVENT_LECTURE_HAND_CLEARED',
			2810:'VIDYO_CLIENT_OUT_EVENT_AUDIO_FRAME_RECEIVED',
			2811:'VIDYO_CLIENT_OUT_EVENT_VIDEO_FRAME_RECEIVED',
			2812:'VIDYO_CLIENT_OUT_EVENT_SELF_VIEW_VIDEO_FRAME_RECEIVED',
			2820:'VIDYO_CLIENT_OUT_EVENT_CONTROL_CONFERENCE_ROOM_SETTINGS',
			2830:'VIDYO_CLIENT_OUT_EVENT_PRECALL_TEST_DEVICE',
			2850:'VIDYO_CLIENT_OUT_EVENT_SHARED_WINDOW_CLOSED',
			2851:'VIDYO_CLIENT_OUT_EVENT_SHARED_SCREEN_DISCONNECTED',
			2855:'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_CONTROL_ALL_PARTICIPANTS',
			2860:'VIDYO_CLIENT_OUT_EVENT_NETWORK_INTERFACE_CHANGED',
			3000:'VIDYO_CLIENT_OUT_EVENT_PORTAL_SERVICE',
			3100:'VIDYO_CLIENT_OUT_EVENT_LOG',
			99999:'VIDYO_CLIENT_OUT_EVENT_MAX'
		};

		var privateEventNames = {
			200100: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_MIN',
			200200: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_SHARED_APP_ADD',
			200201: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_SHARED_APP_REM',
			200300: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_ALARMS_RAISED',
			200301: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_ALARMS_CLEARED',
			200400: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PARTICIPANTS_LIMIT_BANDW',
			200401: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PARTICIPANTS_LIMIT_SAFE',
			200600: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PARTICIPANTS_CHANGED', // Use VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED instead of this
			200700: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_ALLOW_UPGRADE',
			200800: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_GET_CONFIGURATION_RESPONSE',
			200900: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_VCSOAP',
			201000: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_DATA_CACHE', // all OUT events related to caching portal data and operations on cache
			201100: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PLAY_SOUND_DONE', //inform the user that a sound buffer finished playing , using VidyoClientInEventPlaySound structure
			201200: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_WEBPROXY_UPDATE_NEEDED',	// Inform listener (Android app. for example) to run the Web Proxy PAC script
			201300: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_GUEST_CONFERENCE_ENDED',	// Inform listener that a guest conference has just ended
			201400: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_RESET_EMCP_AFTER_GUEST_FAILED',	// Inform listener that a reset emcp after guest conference has just failed. client is now in a logout state.
			201700: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_GUEST_CONFERENCE_BEGIN_PROMPT',  // guest link notification
			//201810: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_CONFERENCE_CLEARED',
			/*!
			Report the status of communication with Portal. This out event is used
			report the portal communication status for searching contact, add or remove contacts,
			control meeting etc.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventPortalCommunicationStatus
			*/
			201900: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PORTAL_COMMUNICATION_STATUS',
			/*!
			Report the changes in signin flow. Example of changes are retry to secure portal,
			redirecting to secure portal.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventSignInUpdate
			*/
			202000: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_SIGNIN_UPDATE',
			/*!
			Report that user login using external (e.g. browser) or Report that automatic login
			using previously provided credntial is started.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventLoginStarted
			*/
			202001: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_LOGIN_STARTED',
			/*!
			Report that credential required to login are not present or client is working again older
			portal and manual sign-in required.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventNoLoginCredential
			*/
			202002: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_NO_LOGIN_CREDENTIAL',
			/*!
			Report the status change Kiosk device.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventKioskDeviceStateChanged
			*/
			202100: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_KIOSK_DEVICE_STATE_CHANGED',
			/*!
			Report the low master volume indication for a audio device.

			@see Corresponding parameter structure #VidyoClientPrivateOutEventLowMasterVolume
			*/
			202110: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_LOW_MASTER_VOLUME',

			// /* Start of messages for VidyoRoom only */
			// 250000: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_VISCA',
			// 250001: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_SWB',
			// 250002: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_USB_CAPTURE',
			// 250003: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_CHANGE_FOCUS',
			// 250004: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_NETWORK_CONTROL',
			// 250005: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_CHANGE_CAMERA_MODE',
			// 250006: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_FRAMEWORK_DONE',
			// 250007: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_ADJUST_MONITORS',
			// 250008: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_SET_VISCA',
			// /* End of messages for VidyoRoom only */

			// /* Start of messages used by Android (currently) */
			// /*!
			// Report that a Remote source is added or removed.  Android needs to know when remote
			// sources are added and removed so that if the menu bar is visible it can be updated
			// appropriately.
			// */
			// 260000: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_REMOTE_SOURCE_ADD',
			// 260001: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_REMOTE_SOURCE_REM',
			// /* End of messages used by Android (currently) */
			260002: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_RENDERER_DOCS_CHANGED',

			/* Start of messages used by VidyoWeb ONLY */
			270000: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PLUGIN_CONNECTION_SUCCESS',
			270001: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_PLUGIN_CONNECTION_FAILURE',
			270002: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_GET_WINDOWS_EXT',
			/* Below private out event is for declaration only, as its been sent by the VidyoWeb plugin */
			270003: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_GET_JOIN_APPROVAL',
			/* End of messages used by VidyoWeb */

			299999: 'VIDYO_CLIENT_PRIVATE_OUT_EVENT_MAX',


			300500: 'EXTENSION_MSG_CLIENT_CLOSED',
			300501: 'EXTENSION_MSG_CLIENT_STARTING',
			300502: 'EXTENSION_MSG_REQUEST_SET_CHROME_ARCH'
		}


	var proxywrapper = {
		isChrome: (function() { // This method returns true if the running browser is Google Chrome version 42+
			// if (navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
			// 	navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42) {
			if ((navigator.appVersion.indexOf("Win")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1) ||
				(navigator.appVersion.indexOf("Mac")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
					navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42)){
				return true;
			} else {
				return false;
			}
		})(),

		started: false,
		starting: false,

		connect: function() {
			window.addEventListener("message", receivedEvent, false);
		},
		disconnect: function() {
			window.removeEventListener("message");
		},
		setOutEventDispatchMethod: function(method) {
			dispatchFunction = method;
		},
		useVideoElem: function(videoElement, callback) {
			videohandler.start(videoElement, callback);
		},
		getVersionString: function(callback) { // get proxyserver version
			proxyWrapper.sendRequest({type: 'RequestGetVersion'}, function(response) {
				if (callback) {
					callback(response.version || 'None');
				}
			});
		},

		supportedVersions: supportedVersions,

		isSupportedVersion: function(callback) { // check if proxyserver version is present in supported versions
			proxyWrapper.sendRequest({type: 'RequestGetVersion'}, function(response) {
				var result = false;
				var version = null;
				if (response.version) {
					// version = response.version.split('_')[0];
					version = response.version;
				}
				if (supportedVersions.indexOf(version) !== -1) {
					result = true;
				} else if(version > supportedVersions[0]){
					result = true;
				} else {
					console.log('Current proxy version:', response.version);
				}
				if (callback) {
					callback(result, response.version);
				}
			});
		},

		isUpdatedVersion: function(version) { // check if proxyserver version is present in supported versions
			return (supportedVersions.indexOf(version) === 0 || version > supportedVersions[0]);
		},

		detectExtension: function(extensionId, callback) {
			var img;
			img = new Image();
			img.src = 'chrome-extension://' + extensionId + '/icons/128x128.png';
			img.onload = function() {
				console.log('Chrome Extension detected');
				callback(true);
			};
			img.onerror = function() {
				console.log('Chrome Extension not detected');
				callback(false);
			};
		},

		// start/stop the proxyserver
		start: function(callback, timeout) {
			proxywrapper.starting = true;
			proxywrapper.sendEvent({type: 'InEventStart'}, function(request) {
				proxywrapper.starting = false;
				console.log(request);
				if (request.error) {
					if (request.error == 'VidyoClient already started') {
						proxywrapper.startDisallowed = true;
						dispatch({type:'OutEventPluginConnectionFailure'});
					}
					else {
						dispatch({type:'OutEventPluginError', error: request.error});
					}
				} else {
					proxywrapper.sendEvent({type: 'ActiveTab'}, null);
					proxywrapper.started = true;
					dispatch({type:'OutEventPluginConnectionSuccess'});
				}
				if (callback) {
					callback(request);
				}
			});
		},

		stop: function(callback, timeout) {
			console.log('started:', proxyWrapper.started, 'disalowed:', proxyWrapper.startDisallowed, 'starting:', proxyWrapper.starting);
			if ((proxywrapper.started && !proxywrapper.startDisallowed) || proxywrapper.starting) {
				proxywrapper.sendEvent({type: 'InEventStop'}, function(request) {
					proxywrapper.started = false;
					if (!request.error) {
					}
					if (callback) {
						callback(request);
					}
				});
			}
		},

		stopPlayback: function() {
			videohandler.stop();
		},

		sendRequest: sendEvent,
		sendEvent: sendEvent

	};

	function sendEvent(obj, callback) {

		obj._id = Math.floor(Math.random() * 1000000);
		callbacks[obj._id] = callback;
		clearTimeout(timeouts[obj._id]);
		timeouts[obj._id] = setTimeout(function() {
			console.log('timeout:', obj.type);
			obj.error = 'connection timeout';
			if (callbacks[obj._id] && timeouts[obj._id]) {
				callbacks[obj._id](obj);
			}
		}, 2000);

		obj._direction = 1;

		console.log('snd to ext:', JSON.stringify(obj));
		window.postMessage(obj, "*");
	}

	function dispatch(object) {
		if (dispatchFunction) {
			dispatchFunction(object);
		}
	}

	function receivedEvent(event){
		message = event.data;
		if (message.type === 'log') {
			console.debug('rcv from ext:', JSON.stringify(message));
		} else {
			console.log('rcv from ext:', JSON.stringify(message));
		}
		if (message._direction == 2) {

			// Handle Requests and InEvents
			if (message.type) {
				if (message.type.indexOf('OUT_EVENT') == -1) {
					if (callbacks[message._id] && timeouts[message._id]) {
						clearTimeout(timeouts[message._id]);
						delete timeouts[message._id];
						callbacks[message._id](message);
						delete callbacks[message._id];
					}
					return;
				}
			}

			//Handle OutEvents
			var evtCode = message['code'];
			var evtParams = message['params'];

			var evt = {};
			// create an object to dispatch
			if (eventNames[evtCode] !== undefined) {
				evt.type = eventNames[evtCode];
			}
			else if (privateEventNames[evtCode] !== undefined) {
				evt.type = privateEventNames[evtCode];
			}
			else {
				evt.type = null;
			}

			for (var param in evtParams) {
				if (evtParams.hasOwnProperty(param)) {
					evt[param] = evtParams[param];
				}
			}
			switch(evt.type) {
				case 'VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED':
//					dispatch({type:'OutEventPluginConnectionSuccess'});
					break;
				case 'VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED':
					videohandler.stop();
					break;
				case 'EXTENSION_MSG_CLIENT_CLOSED':
//					proxywrapper.started = false;
					proxywrapper.starting = false;
					if (evt.message == 'Specified native messaging host not found.' && navigator.appVersion.indexOf('Mac') !== -1) {
						localStorage.setItem('shouldRestartChrome', true);
					}
					break;
				default:
					break;
			}

			if (evt.type) {
				if (evtCode != 200900/*VIDYO_CLIENT_PRIVATE_OUT_EVENT_VCSOAP*/) {
					evt.type = evt.type.toLowerCase();
					evt.type = evt.type.replace(/(_([a-zA-Z]{1}))/g, function($1) { return $1.toUpperCase(); });
					evt.type = evt.type.replace(/_/g, '');
					if (evtCode != 300500 && evtCode != 300501 && evtCode != 300502) {
						evt.type = evt.type.substring(11);
					}
				}
				dispatch(evt);
			} else {
				console.log('event without type', message);
			}
		}
	};

	return proxywrapper;



	function videoHandler() {
		//Browser compatibility
		navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
		window.URL = window.URL || window.webkitURL;

		var inited = false,
			userMediaStream = null,
			video = null,
			vidSize = {w: 0, h: 0},
			vidCamId = null,
			tempCallback = null,
			callbackCalled = false;

		// Interval to check size of the video element
		var interval = setInterval(function() {
			if (video) {
				//Check Video size
				if (vidSize.w !== video.offsetWidth || vidSize.h !== video.offsetHeight) {
					vidSize.w = video.offsetWidth;
					vidSize.h = video.offsetHeight;
					console.log('video resized to', video.offsetWidth, video.offsetHeight);
					proxyWrapper.sendEvent({type: 'InEventResize', x: 0, y: 0, width: video.offsetWidth, height: video.offsetHeight}, function(request) {
						console.log(request);
					});
				}
			}
		}, 200);

		var streamCount = 0,
			streamsChecked = 0,
			cameraCheckTimeout = null;

		var videohandler = {
			origCallback : null,
			start: function(videoElement, callback) {
				if (!cameraCheckTimeout) {
					cameraCheckTimeout = setTimeout(function() {
						cameraCheckTimeout = null;
					}, 45 * 1000);
				}
				video = videoElement;
				if (!video) {
					console.log('Init the videoHandler before calling this method');
					return;
				}
				if (!videohandler.origCallback) {
					videohandler.origCallback = callback;
				}
				streamCount = 0;
				streamsChecked = 0;
				callbackCalled = false;
				tempCallback = function(message, permissionDeniedError) {
					if (!callbackCalled) {
						callbackCalled = true;
						callback(message, permissionDeniedError);
					}
				};
				usermediaMessage = document.getElementById('lbl_usermedia');

				function displayVideoDimensions() {
					if (!video.videoWidth || video.videoWidth < 100) {
						setTimeout(displayVideoDimensions, 500);
						return;
					}
					if (navigator.appVersion.indexOf('Windows') !== -1) {
						proxywrapper.sendRequest({type: 'RequestSetCameraResolution', width: video.videoWidth, height: video.videoHeight});
						console.log('ProxyWrapper', 'Windows Video Width: ', video.videoWidth, ' Video Height: ', video.videoHeight);
					} else {
						proxywrapper.sendRequest({type: 'RequestSetCameraResolution', width: 1920, height: 1080});
						console.log('ProxyWrapper', 'MAC forcing Video Width: 1920 Video Height: 1080');
					}
				}
				video.onloadedmetadata = displayVideoDimensions;

				// //Check if the user media is supported

				var getSourcesCallback = function(sourceInfos) {
					var videoSources =[];
					var virtualCameraSource = null;

					sourceInfos.forEach(function(source){
						if (source.kind === 'video' || source.kind === 'videoinput' ){
							videoSources[streamCount]= source;
							streamCount++;
							if(source.label === 'WebPluginVirtualCamera'){
								virtualCameraSource = source;
							}
						}
					});

					var getInitialConstraints = function() {
						var videoConstraints;
						if (navigator.appVersion.indexOf('Windows') !== -1) {
							videoConstraints = {deviceId: virtualCameraSource ? {exact: virtualCameraSource.deviceId} : undefined, width: {exact: 1920}, height: {exact: 1080}};
						} else {
							videoConstraints = {deviceId: virtualCameraSource ? {exact: virtualCameraSource.deviceId} : undefined, video: {width: {exact: 1920}, height: {exact: 1080}}};
						}

						return {
							audio: false,
							video: videoConstraints
						};
					};

					navigator.mediaDevices.getUserMedia(getInitialConstraints())
						.then(onStreamSuccess)
						.catch(onStreamErrors);
				}

				if(!navigator.mediaDevices) {
					return tempCallback('This browser does not support MediaDevices');
				} else {
					// First we call this function in order to get access to the devices labels
					navigator.mediaDevices.getUserMedia({video: true})
						.then(function(stream) {
							stream.getTracks().forEach(function(track) {
								track.stop();
							});
							return navigator.mediaDevices.enumerateDevices();
						})
						.then(getSourcesCallback)
						.catch(onStreamErrors);
				}

			},
			stop: function() {
				if (!video) {
					console.log('Init the videoHandler before calling this method');
					return;
				}
				video.pause();
				video.src = '';
				if (userMediaStream) {
					userMediaStream.getTracks()[0].stop();
				}
			}
		}

		function onStreamSuccess(stream) {
			var track = stream.getVideoTracks()[0];
			console.log('ProxyWrapper', 'Source id: ' + track.id);
			console.log('ProxyWrapper', 'Source label: ' + track.label);

			if (track.label.indexOf('WebPluginVirtualCamera') >= 0) {
				console.log('WebPluginVirtualCamera found');
				//Play the media stream in the video element
				userMediaStream = stream;
				video.src = window.URL.createObjectURL(stream);
				video.play();
				tempCallback(null, false);
				clearTimeout(cameraCheckTimeout);
				cameraCheckTimeout = null;
			} else {
				stream.getTracks()[0].stop();
				streamsChecked++;
				if (streamsChecked >= streamCount) {
					console.log('ProxyWrapper','WebPluginVirtualCamera not found. Cameradriver is not installed or not recognized');
					// tempCallback('You are missing the cameradriver', false);
					setTimeout(function(){
						console.log('Reattempting GetUserMedia');
						if (cameraCheckTimeout) {
							videohandler.start(video, videohandler.origCallback);
						} else {
							tempCallback('cameraTimeout', false);
						}
					},1000);
				}else{

				}
			}
		}
		function onStreamErrors(error) {
			streamsChecked++;
			if (streamsChecked >= streamCount) {
				//Handle the permission denied error in Chrome and 'Starting video failed' error in Firefox
				if (error.name === 'PermissionDeniedError' || error === 'Starting video failed') {
					tempCallback('Media might already be in use', true);
					console.log('ProxyWrapper', 'Media might already be in use');
				} else { //Handle all other errors
					tempCallback('Something went wrong while getting the video', false);
					console.log('ProxyWrapper', 'Error: ', JSON.stringify(error));
				}
			}
		}

		return videohandler;
	};
})();
