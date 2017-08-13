/*! @file vidyo.client.messages.js
                @VidyoWeb API Library header.
                @copyright
                (c) 2012-2014 Vidyo, Inc.
                433 Hackensack Avenue, 7th Floor,
                Hackensack, NJ  07601.
                All rights reserved.
                The information contained herein is proprietary to Vidyo, Inc.
                and shall not be reproduced, copied (in whole or in part), adapted,
                modified, disseminated, transmitted, transcribed, stored in a retrieval
                system, or translated into any language in any form by any means
                without the express written consent of Vidyo, Inc.
*/
/**
  * @fileOverview This file defines the module for the public VidyoClient message objects.
  * @author Vidyo Inc.
  * @version 1.1.1
  */

define(["./vidyo.client.parameters"],
	function (vidyoClientParameters) {
		/**
		  * Creates a VidyoClientMessages object.
		  * @class Factories for VidyoClient messages and message types.
		  */
		var vidyoClientMessages = {
			/**
			  * Creates a VidyoClient message object.
			  *
			  * @name vidyoClientMessages.message
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @return {Object} Reference to created object.
			  */
			'message': function (type) {
				// object created by this factory function
				var that = {};

				// public properties for created object
				that.type = type;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient in event object, for event messages
			  * which flow into VidyoClient.
			  *
			  * @name vidyoClientMessages.inEvent
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @return {Object} Reference to created object.
			  */
			'inEvent': function (type) {
				// object created by this factory function
				var that = this.message(type);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient event object, for event messages
			  * which flow both into and out of VidyoClient.
			  *
			  * @name vidyoClientMessages.event
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @return {Object} Reference to created object.
			  */
			'event': function (type) {
				// object created by this factory function
				var that = this.message(type);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient request object, for request messages
			  * which flow into VidyoClient, and can return data.
			  *
			  * @name vidyoClientMessages.request
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @return {Object} Reference to created object.
			  */
			'request': function (type) {
				// object created by this factory function
				var that = this.message(type);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient sign-in in event object.
			  * Event used to perform endpoint registration.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - serverAddress<br/>
			  *  - serverPort<br/>
			  *  - userName<br/>
			  *  - portalAccessKey<br/>
			  *  - portalAddress<br/>
			  *  - portalVersion<br/>
			  *  - vmIdentity<br/>
			  *  - locationTag<br/>
			  *  - vidyoProxyAddress<br/>
			  *  - vidyoProxyPort<br/>
			  *  - emcpSecured<br/>
			  *  - guestLogin<br/>
			  *  - showDialpad<br/>
			  *  - showStartmeeting<br/>
			  *
			  * @name vidyoClientMessages.inEventSignIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSignIn': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSignIn");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.serverAddress = params && params.serverAddress || "";
				that.serverPort = params && params.serverPort || "";
				that.userName = params && params.userName || "";
				that.portalAccessKey = params && params.portalAccessKey || "";
				that.portalAddress = params && params.portalAddress || "";
				that.portalVersion = params && params.portalVersion || "";
				that.vmIdentity = params && params.vmIdentity || "";
				that.locationTag = params && params.locationTag || "";
				that.vidyoProxyAddress = params && params.vidyoProxyAddress || [""];
				that.vidyoProxyPort = params && params.vidyoProxyPort || [""];
				that.emcpSecured = params && params.emcpSecured || false;
				that.guestLogin = params && params.guestLogin || false;
				that.showDialpad = params && params.showDialpad || false;
				that.showStartmeeting = params && params.showStartmeeting || false;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient cancel in event object.
			  * Event used to cancel entering a conference.
			  *
			  * @name vidyoClientMessages.inEventCancel
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventCancel': function () {
				// object created by this factory function
				var that = this.inEvent("InEventCancel");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient leave in event object.
			  * Event used to leave a conference, already entered.
			  *
			  * @name vidyoClientMessages.inEventLeave
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventLeave': function () {
				// object created by this factory function
				var that = this.inEvent("InEventLeave");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient preview event object.
			  * Event used to change or acknowledge how own video shown in
			  * video layout.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - previewMode ("None", "PIP", "Dock")<br/>
			  *
			  * @name vidyoClientMessages.eventPreview
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'eventPreview': function (params) {
				// object created by this factory function
				var that = this.event("EventPreview");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.previewMode = params && params.previewMode || "None";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient mute in event object.
			  * Event used to change mute state of various media devices.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - willMute<br/>
			  *
			  * @name vidyoClientMessages.inEventMute
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventMute': function (type, params) {
				// object created by this factory function
				var that = this.inEvent(type);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.willMute = params && params.willMute || false;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient mute audio in in event object.
			  * Event used to change mute state of audio input (capture/microphone) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - willMute<br/>
			  *
			  * @name vidyoClientMessages.inEventMuteAudioIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventMuteAudioIn': function (params) {
				// object created by this factory function
				var that = this.inEventMute("InEventMuteAudioIn", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient mute audio out in event object.
			  * Event used to change mute state of audio output (playback/speaker) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - willMute<br/>
			  *
			  * @name vidyoClientMessages.inEventMuteAudioOut
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventMuteAudioOut': function (params) {
				// object created by this factory function
				var that = this.inEventMute("InEventMuteAudioOut", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient mute video in event object.
			  * Event used to change privacy state of video (capture/camera) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - willMute<br/>
			  *
			  * @name vidyoClientMessages.inEventMuteVideo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventMuteVideo': function (params) {
				// object created by this factory function
				var that = this.inEventMute("InEventMuteVideo", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient share in event object.
			  * Event used to share an application window or system desktop,
			  * during a conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - window<br/>
			  *
			  * @name vidyoClientMessages.inEventShare
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventShare': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventShare");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.window = params && params.window || "0x0000000000000000";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient unshare in event object.
			  * Event used to stop sharing an application window or system desktop,
			  * during a conference.
			  *
			  * @name vidyoClientMessages.inEventUnshare
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventUnshare': function () {
				// object created by this factory function
				var that = this.inEvent("InEventUnshare");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient participants limit in event object.
			  * Event used to change maximum number of participants to display in
			  * video layout.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - maxNumParticipants<br/>
			  *
			  * @name vidyoClientMessages.inEventParticipantsLimit
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventParticipantsLimit': function (params) {
				// object created by this factory function
				var that = this.inEventMute("InEventParticipantsLimit", params);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.maxNumParticipants = params && params.maxNumParticipants || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient layout in event object.
			  * Event used to change number of preferred participants displayed in
			  * video layout.  Preferred participants appear in larger tiles than
			  * and in different positions from participants that are not preferred.
			  * Participants are usually selected to be preferred based on whether
			  * they are in the loudest speaker history, according to speech energy.
			  * The current capability allows for either 0 or 1 preferred participants.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numPreferred<br/>
			  *
			  * @name vidyoClientMessages.inEventLayout
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventLayout': function (params) {
				// object created by this factory function
				var that = this.inEventMute("InEventLayout", params);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numPreferred = params && params.numPreferred || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient login in event object.
			  * Event used to log user in to VidyoPortal.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - portalUri<br/>
			  *  - userName<br/>
			  *  - userPass<br/>
			  *
			  * @name vidyoClientMessages.inEventLogin
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventLogin': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventLogin");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.portalUri = params && params.portalUri || "";
				that.userName = params && params.userName || "";
				that.userPass = params && params.userPass || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient login cancel in event object.
			  * Event used to cancel login of user to VidyoPortal.
			  *
			  * @name vidyoClientMessages.inEventLoginCancel
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventLoginCancel': function () {
				// object created by this factory function
				var that = this.inEvent("InEventLoginCancel");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient license in event object.
			  * Event used to initiate licensing activation with VidyoPortal.
			  *
			  * @name vidyoClientMessages.inEventLicense
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventLicense': function () {
				// object created by this factory function
				var that = this.inEvent("InEventLicense");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient signoff in event object.
			  * Event used to end connection with VidyoManager.
			  *
			  * @name vidyoClientMessages.inEventSignoff
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventSignoff': function () {
				// object created by this factory function
				var that = this.inEvent("InEventSignoff");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient toggle share in event object.
			  * Event used to toggle the displayed application window share.
			  *
			  * @name vidyoClientMessages.inEventToggleShare
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventToggleShare': function () {
				// object created by this factory function
				var that = this.inEvent("InEventToggleShare");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient call answer event object.
			  * Event used to accept incoming calls.
			  *
			  * @name vidyoClientMessages.inEventAnswer
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventAnswer': function () {
				// object created by this factory function
				var that = this.inEvent("InEventAnswer");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient call decline event object.
			  * Event used to reject incoming calls.
			  *
			  * @name vidyoClientMessages.inEventDecline
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventDecline': function () {
				// object created by this factory function
				var that = this.inEvent("InEventDecline");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient private chat event object.
			  * Event used to send a private message to a participant in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - message<br/>
			  *
			  * @name vidyoClientMessages.inEventPrivateChat
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventPrivateChat': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventPrivateChat");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri = params && params.uri || "";
				that.message = params && params.message || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient group chat event object.
			  * Event used to send a group message to all participants in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - message<br/>
			  *
			  * @name vidyoClientMessages.inEventGroupChat
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventGroupChat': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventGroupChat");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.message = params && params.message || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set display name event object.
			  * Event used to set an on-screen label to a participant in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - displayName<br/>
			  *
			  * @name vidyoClientMessages.inEventSetDisplayName
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetDisplayName': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetDisplayName");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri = params && params.uri || "";
				that.displayName = params && params.displayName || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient reset display name event object.
			  * Event used to reset an on-screen lable to a participant in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *
			  * @name vidyoClientMessages.inEventResetDisplayName
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventResetDisplayName': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventResetDisplayName");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri = params && params.uri || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient pinning event object.
			  * Event used to pin a participant in the conference to a layout.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - pinMode ("None", "PinHigh", "PinLow")<br/>
			  *
			  * @name vidyoClientMessages.inEventPinParticipant
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventPinParticipant': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventPinParticipant");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri = params && params.uri || "";
				that.pinMode = params && params.pinMode || "None";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient echo detection event object.
			  * Event used to enable or disable echo detection notifications.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - enable (true, false)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetEchoDetection
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetEchoDetection': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetEchoDetection");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.enable = params && (params.enable !== undefined) || true;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient echo cancellation event object.
			  * Event used to enable or disable echo cancellation.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - enable (true, false)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetEchoCancellation
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetEchoCancellation': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetEchoCancellation");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.enable = params && (params.enable !== undefined) || true;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient automatic gain control event object.
			  * Event used to enable or disable automatic gain control for microphone.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - enable (true, false)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetAGC
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetAGC': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetAGC");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.enable = params && (params.enable !== undefined) || true;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient remote camera control event object.
			  * Event used to control a remote cameta.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - cameraCommand ("PanRight", "PanLeft", "TiltUp", "TiltDown", "ZoomIn", "ZoomOut", "Position", "ViscaCommand", "ViscaResponse")<br/>
			  *  - commandId<br/>
			  *  - commandData<br/>
			  *  - preset<br/>
			  *
			  * @name vidyoClientMessages.inEventControlCamera
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventControlCamera': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventControlCamera");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri = params && params.uri || "";
				that.cameraCommand = params && params.cameraCommand || "";
				that.commandId = params && params.commandId || "";
				that.commandData = params && params.commandData || "";
				that.preset = params && params.preset || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set send badwidth event object.
			  * Event used to limit outgoing bandwidth.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - sendBandwidth(7 - 768Kbps,  1 - 1Mbps, 2 - 2Mbps, 3 - 3Mbps,
			  *                  4 - 4Mbps, 6 - 6Mbps)<br/>
			  *  - layers (1, 2, 3)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetSendBadwidthLimit
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetSendBadwidthLimit': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetSendBadwidthLimit");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.sendBandwidth = params && params.sendBandwidth || 2;
				that.layers = params && params.layers || 3;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set offline event object.
			  * Event used to set offline mode or reconnect to the VidyoManager.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - offline (true - go offline, false - reconnect to the VidyoManager)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetOffline
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetOffline': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetOffline");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.offline = params && (params.offline !== undefined) || true;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set freeze image event object.
			  * Event used to freeze currently capture frame and don't get new frames from the camera
			  * or start getting new frames from the camera again.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - freeze (true - freeze, false - unfreeze)<br/>
			  *
			  * @name vidyoClientMessages.inEventSetFreezeImage
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventSetFreezeImage': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventSetFreezeImage");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.freeze = params && (params.freeze !== undefined) || true;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a Control Conference Room Settings event object.
			  * Event used to do a control conference room settings.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - requestId<br/>
			  *  - roomType<br/>
			  *  - roomSettingId<br/>
			  *  - moderatorPin<br/>
			  *
			  * @name vidyoClientMessages.inEventControlConferenceRoomSettings
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventControlConferenceRoomSettings': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventControlConferenceRoomSettings");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.requestId = params && params.requestId || "";
				that.roomType = params && params.roomType || "";
				that.roomSettingId = params && params.roomSettingId || "";
				that.moderatorPin = params && params.moderatorPin || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a Pre-call Camera Test event object.
			  * Event used to to do a pre-call camera test.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - action<br/>
			  *
			  * @name vidyoClientMessages.inEventPrecallTestCamera
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventPrecallTestCamera': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventPrecallTestCamera");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.action = params && params.action || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a Pre-call Microphone Test event object.
			  * Event used to to do a pre-call microphone test.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - action<br/>
			  *
			  * @name vidyoClientMessages.inEventPrecallTestMicrophone
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventPrecallTestMicrophone': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventPrecallTestMicrophone");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.action = params && params.action || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a Pre-call Speaker Test Start event object.
			  * Event used to start a pre-call speaker test.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - soundFileName<br/>
			  *
			  * @name vidyoClientMessages.inEventStartPrecallTestSpeaker
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventStartPrecallTestSpeaker': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventStartPrecallTestSpeaker");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.soundFileName = params && params.soundFileName || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a Pre-call Speaker Test Stop event object.
			  * Event used to start a pre-call speaker test.
			  *
			  * @name vidyoClientMessages.inEventStopPrecallTestSpeaker
			  * @function
			  * @return {Object} Reference to created object.
			  */
			'inEventStopPrecallTestSpeaker': function (params) {
				// object created by this factory function
				var that = this.inEvent("InEventStopPrecallTestSpeaker");

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient send DTMF in event object.
			  * Event used to send or play a DTMF tone to conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - tone<br/>
			  *
			  * @name vidyoClientMessages.inEventPlayDtmfTone
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventPlayDtmfTone': function (type, params) {
				// object created by this factory function
				var that = this.inEvent(type);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.tone = params && params.tone || "";

				// return object created by this factory function
				return that;
			},

			
			


			/**
			  * Returns type of a VidyoClient user message out event object.
			  * Event used to display notification message in dialog box.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - messageType (too many to list)<br/>
			  *  - messageCode<br/>
			  *  - messageString<br/>
			  *
			  * @name vidyoClientMessages.outEventUserMessageType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventUserMessageType': function () {
				// return type of event
				return "OutEventUserMessage";
			},

			/**
			  * Returns type of a VidyoClient logic started out event object.
			  * Event used to signal completion of VidyoClient startup.
			  *
			  * @name vidyoClientMessages.outEventLogicStartedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventLogicStartedType': function () {
				// return type of event
				return "OutEventLogicStarted";
			},

			/**
			  * Returns type of a VidyoClient sign in out event object.
			  * Event used to signal that sign-in to server has been initiated.
			  * Reports if the endpoint ID is activated or not.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - activeEid<br/>
			  *  - guestLogin<br/>
			  *  - showDialpad<br/>
			  *  - showStartmeeting<br/>
			  *  - signinType ("Internal", "External", "Application")<br/>
			  *  - signinSecured<br/>
			  *
			  * @name vidyoClientMessages.outEventSignInType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventSignInType': function () {
				// return type of event
				return "OutEventSignIn";
			},

			/**
			  * Returns type of a VidyoClient sign out out event object.
			  * Event used to signal that sign-out from server has been completed.
			  *
			  * @name vidyoClientMessages.outEventSignOutType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventSignOutType': function () {
				// return type of event
				return "OutEventSignOut";
			},

			/**
			  * Returns type of a VidyoClient endpoint status out event object.
			  * Event used to signal status of connectivity with server.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - endPointStatus ("Inactive", "Registered", "Active")<br/>
			  *
			  * @name vidyoClientMessages.outEventEndpointStatusType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventEndpointStatusType': function () {
				// return type of event
				return "OutEventEndpointStatus";
			},

			/**
			  * Returns type of a VidyoClient device select out event object.
			  * Event used to signal the need to select a media device.
			  *
			  * @name vidyoClientMessages.outEventDeviceSelectType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventDeviceSelectType': function () {
				// return type of event
				return "OutEventDeviceSelect";
			},

			/**
			  * Returns type of a VidyoClient devices changed out event object.
			  * Event used to notify of change in list of attached devices for
			  * specified kind of media device.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - deviceType ("AudioOut", "AudioIn", "Video", "RingTone")<br/>
			  *
			  * @name vidyoClientMessages.outEventDevicesChangedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventDevicesChangedType': function () {
				// return type of event
				return "OutEventDevicesChanged";
			},

			/**
			  * Returns type of a VidyoClient device selection changed out event object.
			  * Event used to report newly selected media device when there is an
			  * automatic change in the selection.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - deviceType ("AudioOut", "AudioIn", "Video", "RingTone")<br/>
			  *  - changeType ("DeviceLost", "DeviceSelectionChanged")<br/>
			  *  - prevDeviceName<br/>
			  *  - newDeviceName<br/>
			  *
			  * @name vidyoClientMessages.outEventDeviceSelectionChangedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventDeviceSelectionChangedType': function () {
				// return type of event
				return "OutEventDeviceSelectionChanged";
			},

			/**
			  * Returns type of a VidyoClient joining out event object.
			  * Event used to display dialog box with progress bar for pending join operation.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - numProgressSteps<br/>
			  *  - caption<br/>
			  *
			  * @name vidyoClientMessages.outEventJoiningType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventJoiningType': function () {
				// return type of event
				return "OutEventJoining";
			},

			/**
			  * Returns type of a VidyoClient join progress out event object.
			  * Event used to advance progress bar for pending join operation.
			  *
			  * @name vidyoClientMessages.outEventJoinProgressType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventJoinProgressType': function () {
				// return type of event
				return "OutEventJoinProgress";
			},

			/**
			  * Returns type of a VidyoClient end processing out event object.
			  * Event used to indicate completion or cancellation of certain operations
			  * relating to state of entering and leaving conferences.
			  * Also used to dismiss dialog box with progress bar for certain pending
			  * operations.
			  *
			  * @name vidyoClientMessages.outEventEndProcessingType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventEndProcessingType': function () {
				// return type of event
				return "OutEventEndProcessing";
			},

			/**
			  * Returns type of a VidyoClient conference active out event object.
			  * Event used to signal that operation to join a conference is complete.
			  *
			  * @name vidyoClientMessages.outEventConferenceActiveType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventConferenceActiveType': function () {
				// return type of event
				return "OutEventConferenceActive";
			},

			/**
			  * Returns type of a VidyoClient conference ended out event object.
			  * Event used to signal that operation to leave a conference is complete.
			  *
			  * @name vidyoClientMessages.outEventConferenceEndedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventConferenceEndedType': function () {
				// return type of event
				return "OutEventConferenceEnded";
			},

			/**
			  * Returns type of a VidyoClient participants changed out event object.
			  * Event used to signal that a participant has joined or left the current
			  * conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - participantCount<br/>
			  *
			  * @name vidyoClientMessages.outEventParticipantsChangedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventParticipantsChangedType': function () {
				// return type of event
				return "OutEventParticipantsChanged";
			},

			/**
			  * Returns type of a VidyoClient muted audio in out event object.
			  * Event used to acknowledge change of mute state of audio input
			  * (capture/microphone) device.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - isMuted<br/>
			  *  - errorCode<br/>
			  *
			  * @name vidyoClientMessages.outEventMutedAudioInType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMutedAudioInType': function () {
				// return type of event
				return "OutEventMutedAudioIn";
			},

			/**
			  * Returns type of a VidyoClient muted audio out out event object.
			  * Event used to acknowledge change of mute state of audio output
			  * (playback/speaker) device.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - isMuted<br/>
			  *  - errorCode<br/>
			  *
			  * @name vidyoClientMessages.outEventMutedAudioOutType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMutedAudioOutType': function () {
				// return type of event
				return "OutEventMutedAudioOut";
			},

			/**
			  * Returns type of a VidyoClient muted video out event object.
			  * Event used to acknowledge change of privacy state of video
			  * (capture/camera) device.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - isMuted<br/>
			  *  - errorCode<br/>
			  *
			  * @name vidyoClientMessages.outEventMutedVideoType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMutedVideoType': function () {
				// return type of event
				return "OutEventMutedVideo";
			},

			/**
			  * Returns type of a VidyoClient muted server audio out event object.
			  * Event used to indicate change of mute state of audio input
			  * (capture/microphone) device, due to server.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - isMuted<br/>
			  *  - errorCode<br/>
			  *
			  * @name vidyoClientMessages.outEventMutedServerAudioInType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMutedServerAudioInType': function () {
				// return type of event
				return "OutEventMutedServerAudioIn";
			},

			/**
			  * Returns type of a VidyoClient muted server video out event object.
			  * Event used to indicate change of privacy state of video
			  * (capture/camera) device, due to server.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - isMuted<br/>
			  *  - errorCode<br/>
			  *
			  * @name vidyoClientMessages.outEventMutedServerVideoType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMutedServerVideoType': function () {
				// return type of event
				return "OutEventMutedServerVideo";
			},

			/**
			  * Returns type of a VidyoClient add share out event object.
			  * Event used to indicate remote application window share added.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - URI<br/>
			  *
			  * @name vidyoClientMessages.outEventAddShareType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventAddShareType': function () {
				// return type of event
				return "OutEventAddShare";
			},

			/**
			  * Returns type of a VidyoClient remove share out event object.
			  * Event used to indicate remote application window share removed.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - URI<br/>
			  *
			  * @name vidyoClientMessages.outEventRemoveShareType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRemoveShareType': function () {
				// return type of event
				return "OutEventRemoveShare";
			},

			/**
			  * Returns type of a VidyoClient keydown out event object.
			  * Event used to indicate beginning of a keypress,
			  * on the video layout while in a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - key<br/>
			  *  - count<br/>
			  *
			  * @name vidyoClientMessages.outEventKeydownType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventKeydownType': function () {
				// return type of event
				return "OutEventKeydown";
			},

			/**
			  * Returns type of a VidyoClient keyup out event object.
			  * Event used to indicate ending of a keypress,
			  * on the video layout while in a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - key<br/>
			  *  - count<br/>
			  *
			  * @name vidyoClientMessages.outEventKeyupType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventKeyupType': function () {
				// return type of event
				return "OutEventKeyup";
			},

			/**
			  * Returns type of a VidyoClient mouse down out event object.
			  * Event used to indicate beginning of a click on a mouse input
			  * device, on the video layout while in a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - button<br/>
			  *  - count<br/>
			  *  - xPos<br/>
			  *  - yPos<br/>
			  *  - shift<br/>
			  *  - ctrl<br/>
			  *  - alt<br/>
			  *  - command<br/>
			  *  - scrollDeltaX<br/>
			  *  - scrollDeltaY<br/>
			  *  - scrollDeltaZ<br/>
			  *
			  * @name vidyoClientMessages.outEventMouseDown
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMouseDown': function () {
				// return type of event
				return "OutEventMouseDown";
			},

			/**
			  * Returns type of a VidyoClient mouse up out event object.
			  * Event used to indicate ending of a click on a mouse input
			  * device, on the video layout while in a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - button<br/>
			  *  - count<br/>
			  *  - xPos<br/>
			  *  - yPos<br/>
			  *  - shift<br/>
			  *  - ctrl<br/>
			  *  - alt<br/>
			  *  - command<br/>
			  *  - scrollDeltaX<br/>
			  *  - scrollDeltaY<br/>
			  *  - scrollDeltaZ<br/>
			  *
			  * @name vidyoClientMessages.outEventMouseUp
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMouseUp': function () {
				// return type of event
				return "OutEventMouseUp";
			},

			/**
			  * Returns type of a VidyoClient mouse move out event object.
			  * Event used to indicate movement of a mouse input
			  * device, independent of click state, that would move the pointer
			  * on the video layout while in a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - button<br/>
			  *  - count<br/>
			  *  - xPos<br/>
			  *  - yPos<br/>
			  *  - shift<br/>
			  *  - ctrl<br/>
			  *  - alt<br/>
			  *  - command<br/>
			  *  - scrollDeltaX<br/>
			  *  - scrollDeltaY<br/>
			  *  - scrollDeltaZ<br/>
			  *
			  * @name vidyoClientMessages.outEventMouseMove
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMouseMove': function () {
				// return type of event
				return "OutEventMouseMove";
			},

			/**
			  * Returns type of a VidyoClient login out event object.
			  * Event used to report success or failure of login of user to VidyoPortal.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - error<br/>
			  *  - portalUri<br/>
			  *  - userName<br/>
			  *
			  * @name vidyoClientMessages.outEventLoginType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventLoginType': function () {
				// return type of event
				return "OutEventLogin";
			},

			/**
			  * Returns type of a VidyoClient license out event object.
			  * Event used to report success or failure of licensing activation
			  * with VidyoPortal.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - error<br/>
			  *  - vmConnectionPath<br/>
			  *  - outOfLicenses<br/>
			  *  - result<br/>
			  *    ("Failure", "Success", "NotLicensed", "SeatLicenseExpired",<br/>
			  *     "WrongPin", "ConferenceLocked", "RoomDisabled", "GeneralFault",<br/>
			  *     "InvalidArgumentFault", "MemberNotOnline", "NotOwnerOfRoom",<br/>
			  *     "UserNotFound", "UnexpectedSubelementInMessage", "EndPointNotFound",<br/>
			  *     "FailedPlaceDirectCall", "IpcJoinFailure", "AllLinesInUse")<br/>
			  *  - fault<br/>
			  *    ("None", "InvalidArgument", "NotLicensed", "General", "ConferenceLocked",<br/>
			  *     "LicenseExpired", "WrongPin")<br/>
			  *
			  * @name vidyoClientMessages.outEventLicenseType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventLicenseType': function () {
				// return type of event
				return "OutEventLicense";
			},

			/**
			  * Returns type of a VidyoClient linked out event object.
			  * Event used to report success or failure of linking of user
			  * via VidyoPortal.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - error<br/>
			  *
			  * @name vidyoClientMessages.outEventLinkedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventLinkedType': function () {
				// return type of event
				return "OutEventLinked";
			},

			/**
			  * Returns type of a VidyoClient signed in out event object.
			  * Event used to signal connection to VidyoManager with a user
			  * identity.
			  *
			  * @name vidyoClientMessages.outEventSignedInType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventSignedInType': function () {
				// return type of event
				return "OutEventSignedIn";
			},

			/**
			  * Returns type of a VidyoClient signed out out event object.
			  * Event used to signal disconnection from VidyoManager with a
			  * user identity, or any failure to connect with such an
			  * identity in the first place.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - cause ("UserSignedIn", "UserSignedOut", "ServerSignedOut")<br/>
			  *  - error<br/>
			  *
			  * @name vidyoClientMessages.outEventSignedOutType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventSignedOutType': function () {
				// return type of event
				return "OutEventSignedOut";
			},

			/**
			  * Returns type of a VidyoClient incoming call out event object.
			  * Event used to signal incoming call either from a user as direct call or from server as invite to a conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - invitingUser<br/>
			  *  - isDirectCall<br/>
			  *
			  * @name vidyoClientMessages.outEventIncomingCallType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventIncomingCallType': function () {
				// return type of event
				return "OutEventIncomingCall";
			},

			/**
			  * Returns type of a VidyoClient incoming call ended out event object.
			  * Event used to signal that incoming call is ended.
			  *
			  *
			  * @name vidyoClientMessages.outEventIncomingCallEndedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventIncomingCallEndedType': function () {
				// return type of event
				return "OutEventIncomingCallEnded";
			},

			/**
			  * Returns type of a VidyoClient private chat out event object.
			  * Event used to signal incoming chat message directed to the current user only.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - displayName<br/>
			  *  - message<br/>
			  *
			  * @name vidyoClientMessages.outEventPrivateChatType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventPrivateChatType': function () {
				// return type of event
				return "OutEventPrivateChat";
			},

			/**
			  * Returns type of a VidyoClient group chat out event object.
			  * Event used to signal incoming chat message to all participants in the conference.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - displayName<br/>
			  *  - message<br/>
			  *
			  * @name vidyoClientMessages.outEventGroupChatType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventGroupChatType': function () {
				// return type of event
				return "OutEventGroupChat";
			},

			/**
			  * Returns type of a VidyoClient conference info update out event object.
			  * Event used to signal webcasting or recording status.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - event ("Webcasting", "Recording")<br/>
			  *  - eventStatus (true - on, false - off)<br/>
			  *
			  * @name vidyoClientMessages.outEventConferenceInfoUpdateType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventConferenceInfoUpdateType': function () {
				// return type of event
				return "OutEventConferenceInfoUpdate";
			},

			/**
			  * Returns type of a VidyoClient pin participant done out event object.
			  * Event used to signal status on participant pin.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - pinMode ("None", "PinHigh", "PinLow")<br/>
			  *  - isSet<br/>
			  *
			  * @name vidyoClientMessages.outEventPinParticipantDoneType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventPinParticipantDoneType': function () {
				// return type of event
				return "OutEventPinParticipantDone";
			},

			/**
			  * Returns type of a VidyoClient call state out event object.
			  * Event used to signal call state change.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - callState ("Idle", "Ringing", "Calling", "Joining", "InConference", "Disconnecting")<br/>
			  *
			  * @name vidyoClientMessages.outEventCallStateType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventCallStateType': function () {
				// return type of event
				return "OutEventCallState";
			},

			/**
			  * Returns type of a VidyoClient ringing out event object.
			  * Event used to signal ringing operation.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - numProgressSteps<br/>
			  *  - caption<br/>
			  *
			  * @name vidyoClientMessages.outEventRingingType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRingingType': function () {
				// return type of event
				return "OutEventRinging";
			},


			/**
			  * Returns type of a VidyoClient ringing progress out event object.
			  * Event used to signal ringing progress step.
			  *
			  * @name vidyoClientMessages.outEventRingingProgressType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRingingProgressType': function () {
				// return type of event
				return "OutEventRingingProgress";
			},


			/**
			  * Returns type of a VidyoClient ringing ended out event object.
			  * Event used to signal that ringing is ended.
			  *
			  * @name vidyoClientMessages.outEventRingingEndedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRingingEndedType': function () {
				// return type of event
				return "OutEventRingingEnded";
			},

			/**
			  * Returns type of a VidyoClient calling out event object.
			  * Event used to signal calling operation.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - numProgressSteps<br/>
			  *  - caption<br/>
			  *
			  * @name vidyoClientMessages.outEventCallingType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventCallingType': function () {
				// return type of event
				return "OutEventCalling";
			},


			/**
			  * Returns type of a VidyoClient calling progress out event object.
			  * Event used to signal calling progress step.
			  *
			  * @name vidyoClientMessages.outEventCallingProgressType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventCallingProgressType': function () {
				// return type of event
				return "OutEventCallingProgress";
			},


			/**
			  * Returns type of a VidyoClient calling ended out event object.
			  * Event used to signal that calling is ended.
			  *
			  * @name vidyoClientMessages.outEventCallingEndedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventCallingEndedType': function () {
				// return type of event
				return "OutEventCallingEnded";
			},


			/**
			  * Returns type of a VidyoClient call retrying out event object.
			  * Event used to signal retrying to establish call using VidyoProxy.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - numProgressSteps<br/>
			  *  - caption<br/>
			  *
			  * @name vidyoClientMessages.outEventRetryingType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRetryingType': function () {
				// return type of event
				return "OutEventRetrying";
			},


			/**
			  * Returns type of a VidyoClient call retrying progress out event object.
			  * Event used to signal call retrying progress step.
			  *
			  * @name vidyoClientMessages.outEventRetryingProgressType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventRetryingProgressType': function () {
				// return type of event
				return "OutEventRetryingProgress";
			},


			/**
			  * Returns type of a VidyoClient participant limit out event object.
			  * Event used to signal a limitation in number of participants due to CPU and/or bandwidth.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - bandwidthLimited<br/>
			  *  - cpuLimited<br/>
			  *
			  * @name vidyoClientMessages.outEventParticipantLimitType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventParticipantLimitType': function () {
				// return type of event
				return "OutEventParticipantLimit";
			},


			/**
			  * Returns type of a VidyoClient echo detected out event object.
			  * Event used to signal that acoustic echo is detected.
			  *
			  * @name vidyoClientMessages.outEventEchoDetectedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventEchoDetectedType': function () {
				// return type of event
				return "OutEventEchoDetected";
			},


			/**
			  * Returns type of a VidyoClient remote presentation docking state out event object.
			  * Event used to signal remote presentation docking state.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - windowId<br/>
			  *
			  * @name vidyoClientMessages.outEventFloatingWindowType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventFloatingWindowType': function () {
				// return type of event
				return "OutEventFloatingWindow";
			},


			/**
			  * Returns type of a VidyoClient FECC list updated out event object.
			  * Event used to signal that FECC enable device list is updated.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - numberParticipants<br/>
			  *
			  * @name vidyoClientMessages.outEventFeccListUpdatedType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventFeccListUpdatedType': function () {
				// return type of event
				return "OutEventFeccListUpdated";
			},


			/**
			  * Returns type of a VidyoClient camera control out event object.
			  * Event used to signal incoming camera control event.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - cameraCommand ("PanRight", "PanLeft", "TiltUp", "TiltDown", "ZoomIn", "ZoomOut", "Position", "ViscaCommand", "ViscaResponse")<br/>
			  *  - commandId<br/>
			  *  - commandData<br/>
			  *
			  * @name vidyoClientMessages.outEventControlCameraType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventControlCameraType': function () {
				// return type of event
				return "OutEventControlCamera";
			},


			/**
			  * Returns type of a VidyoClient FECC status update out event object.
			  * Event used to signal currently controlled remote camera status is changed.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - statusCode ("UserLost", "UserInPrivacy")<br/>
			  *  - curFeccUri<br/>
			  *
			  * @name vidyoClientMessages.outEventFeccStatusUpdateType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventFeccStatusUpdateType': function () {
				// return type of event
				return "OutEventFeccStatusUpdate";
			},


			/**
			  * Returns type of a VidyoClient media control out event object.
			  * Event used to signal incoming media control message.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - mediaCommand ("Mute", "Unmute", "Silence")<br/>
			  *  - mediaType ("Video", "Application", "Audio", "Unknown")<br/>
			  *  - mediaSource ("Local", "Remote", "Calling", "Unknown")<br/>
			  *
			  * @name vidyoClientMessages.outEventMediaControlType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventMediaControlType': function () {
				// return type of event
				return "OutEventMediaControl";
			},


			/**
			  * Returns type of a VidyoClient call state out event object.
			  * Event used to signal call state change.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - state ("Init", "Logged", "Linked", "Joined")<br/>
			  *  - error</br>
			  *
			  * @name vidyoClientMessages.outEventGuestLinkType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventGuestLinkType': function () {
				// return type of event
				return "OutEventGuestLink";
			},

			/**
			  * Returns type of a VidyoClient Control Conference Room Settings out event object.
			  * Event used to signal result of in event Control Conference Room Settings.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - requestId<br/>
			  *  - roomSettingId</br>
			  *  - result</br>
			  *
			  * @name vidyoClientMessages.outEventControlConferenceRoomSettingsType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventControlConferenceRoomSettingsType': function () {
				// return type of event
				return "OutEventControlConferenceRoomSettings";
			},

			/**
			  * Returns type of a VidyoClient precall test device out event object.
			  * Event used to signal result for a pre-call test device in event.
			  *
			  * The event object can store the following
			  * properties:<br/>
			  *  - deviceType<br/>
			  *  - action</br>
			  *  - result</br>
			  *
			  * @name vidyoClientMessages.outEventPrecallTestDeviceType
			  * @function
			  * @return {String} String value for type.
			  */
			'outEventPrecallTestDeviceType': function () {
				// return type of event
				return "OutEventPrecallTestDevice";
			},

			/**
			  * Creates a VidyoClient request object to Set log levels and categories for the Client API library.
			  * Request used to set to change log levels and categories
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - levelsAndCategories<br/>
			  *
			  * @name vidyoClientMessages.RequestSetLogLevelsAndCategories
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'RequestSetLogLevelsAndCategories': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetLogLevelsAndCategories");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.levelsAndCategories = params && params.levelsAndCategories || "fatal error warning info@App info@LmiApp info@AppGui info@LmiH264SvcPace info@AppWebProxy";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient configuration request object.
			  * Request used to get/set various configuration parameters.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - microphones<br/>
			  *  - microphonePhyDeviceName<br/>   
			  *  - microphoneVoiceProcessingSupport<br/>
			  *  - numberMicrophones<br/>
			  *  - currentMicrophone<br/>
			  *  - speakers<br/>
 			  *  - speakerPhyDeviceName<br/>
			  *  - numberSpeakers<br/>
			  *  - currentSpeaker<br/>
			  *  - cameras<br/>
			  *  - numberCameras<br/>
			  *  - currentCamera<br/>
			  *  - enableFeccEndpoint<br/>
			  *  - enableFeccController<br/>
			  *  - vidyoProxies<br/>
			  *  - numberVidyoProxies<br/>
			  *  - currentVidyoProxy<br/>
			  *  - userID<br/>
			  *  - password<br/>
			  *  - serverAddress<br/>
			  *  - serverPort<br/>
			  *  - vidyoProxyAddress<br/>
			  *  - vidyoProxyPort<br/>
			  *  - webProxyAddress<br/>
			  *  - webProxyPort<br/>
			  *  - webProxyUsername<br/>
			  *  - webProxyPassword<br/>
			  *  - webProxyIeAddress<br/>
			  *  - webProxyIePort<br/>
			  *  - portalAddress<br/>
			  *  - ringtoneDeviceName<br/>
			  *  - verifyCertPortalAcct<br/>
			  *  - webProxyScriptUrl<br/>
			  *  - webProxyIeScriptUrl<br/>
			  *  - mediaLowPort<br/>
			  *  - mediaHighPort<br/>
			  *  - proxySettings<br/>
			  *  - videoPreferences ("BestQuality", "BestFramerate", "BestResolution", "LimitedBandwidth",<br/>
			  *                      "Advanced450p30", "Advanced720p15", "Advanced720p30")<br/>
			  *  - enableLogging<br/>
			  *  - enableAutoAnswer<br/>
			  *  - enableForceProxy<br/>
			  *  - enableLogWindow<br/>
			  *  - enableEntryTone<br/>
			  *  - enableEchoDetection<br/>
			  *  - enableEchoCancellation<br/>
			  *  - enableFullScreenVideo<br/>
			  *  - showToolbarInFullScreenVideo<br/>
			  *  - enableAudioAGC<br/>
			  *  - enableAutoStart<br/>
			  *  - enableShowConfParticipantName<br/>
			  *  - enableMuteMicrophoneOnJoin<br/>
			  *  - enableHideCameraOnJoin<br/>
			  *  - enableMuteSpeakerOnJoin<br/>
			  *  - enableEulaAgreed<br/>
			  *  - enableRendering<br/>
			  *  - enableBackgrounding<br/>
			  *  - enableFullDisplaySharing<br/>
			  *  - selfViewLoopbackPolicy<br/>
			  *
			  * @name vidyoClientMessages.requestConfiguration
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestConfiguration': function (type, params) {
				// object created by this factory function
				var that = this.request(type);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.microphones = params && params.microphones || [""];
				that.microphonePhyDeviceName = params && params.microphonePhyDeviceName || [""];
				that.microphoneVoiceProcessingSupport = params && params.microphoneVoiceProcessingSupport || [0];
				that.numberMicrophones = params && params.numberMicrophones || 0;
				that.currentMicrophone = params && params.currentMicrophone || 0;
				that.speakers = params && params.speakers || [""];
				that.numberSpeakers = params && params.numberSpeakers || 0;
				that.currentSpeaker = params && params.currentSpeaker || 0;
				that.cameras = params && params.cameras || [""];
				that.numberCameras = params && params.numberCameras || 0;
				that.currentCamera = params && params.currentCamera || 0;
				that.enableFeccEndpoint = params && params.enableFeccEndpoint || 0;
				that.enableFeccController = params && params.enableFeccController || 0;
				that.vidyoProxies = params && params.vidyoProxies || [""];
				that.numberVidyoProxies = params && params.numberVidyoProxies || 0;
				that.currentVidyoProxy = params && params.currentVidyoProxy || 0;
				that.userID = params && params.userID || "";
				that.password = params && params.password || "";
				that.serverAddress = params && params.serverAddress || "";
				that.serverPort = params && params.serverPort || "";
				that.vidyoProxyAddress = params && params.vidyoProxyAddress || "";
				that.vidyoProxyPort = params && params.vidyoProxyPort || "";
				that.webProxyAddress = params && params.webProxyAddress || "";
				that.webProxyPort = params && params.webProxyPort || "";
				that.webProxyUsername = params && params.webProxyUsername || "";
				that.webProxyPassword = params && params.webProxyPassword || "";
				that.webProxyIeAddress = params && params.webProxyIeAddress || "";
				that.webProxyIePort = params && params.webProxyIePort || "";
				that.portalAddress = params && params.portalAddress || "";
				that.ringtoneDeviceName = params && params.ringtoneDeviceName || "";
				that.verifyCertPortalAcct = params && params.verifyCertPortalAcct || "";
				that.webProxyScriptUrl = params && params.webProxyScriptUrl || "";
				that.webProxyIeScriptUrl = params && params.webProxyIeScriptUrl || "";
				that.mediaLowPort = params && params.mediaLowPort || 0;
				that.mediaHighPort = params && params.mediaHighPort || 0;
				that.proxySettings = params && params.proxySettings || 0;
				that.videoPreferences = params && params.videoPreferences || "BestQuality";
				that.enableLogging = params && params.enableLogging || 0;
				that.enableAutoAnswer = params && params.enableAutoAnswer || 0;
				that.enableForceProxy = params && params.enableForceProxy || 0;
				that.enableLogWindow = params && params.enableLogWindow || 0;
				that.enableEntryTone = params && params.enableEntryTone || 0;
				that.enableEchoDetection = params && params.enableEchoDetection || 0;
				that.enableEchoCancellation = params && params.enableEchoCancellation || 0;
				that.enableFullScreenVideo = params && params.enableFullScreenVideo || 0;
				that.showToolbarInFullScreenVideo = params && params.showToolbarInFullScreenVideo || 0;
				that.enableAudioAGC = params && params.enableAudioAGC || 0;
				that.enableAutoStart = params && params.enableAutoStart || 0;
				that.enableShowConfParticipantName = params && params.enableShowConfParticipantName || 0;
				that.enableMuteMicrophoneOnJoin = params && params.enableMuteMicrophoneOnJoin || 0;
				that.enableHideCameraOnJoin = params && params.enableHideCameraOnJoin || 0;
				that.enableMuteSpeakerOnJoin = params && params.enableMuteSpeakerOnJoin || 0;
				that.enableEulaAgreed = params && params.enableEulaAgreed || 0;
				that.enableRendering = params && params.enableRendering || 0;
				that.enableBackgrounding = params && params.enableBackgrounding || 0;
				that.enableFullDisplaySharing = params && params.enableFullDisplaySharing || 0;
				that.selfViewLoopbackPolicy = params && params.selfViewLoopbackPolicy || 2;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get configuration request object.
			  * Request used to get various configuration parameters.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - microphones<br/>
			  *  - microphonePhyDeviceName<br/>
			  *  - microphoneVoiceProcessingSupport<br/>
			  *  - numberMicrophones<br/>
			  *  - currentMicrophone<br/>
			  *  - speakers<br/>
 			  *  - speakerPhyDeviceName<br/>
			  *  - numberSpeakers<br/>
			  *  - currentSpeaker<br/>
			  *  - cameras<br/>
			  *  - numberCameras<br/>
			  *  - currentCamera<br/>
			  *  - enableFeccEndpoint<br/>
			  *  - enableFeccController<br/>
			  *  - vidyoProxies<br/>
			  *  - numberVidyoProxies<br/>
			  *  - currentVidyoProxy<br/>
			  *  - userID<br/>
			  *  - password<br/>
			  *  - serverAddress<br/>
			  *  - serverPort<br/>
			  *  - vidyoProxyAddress<br/>
			  *  - vidyoProxyPort<br/>
			  *  - webProxyAddress<br/>
			  *  - webProxyPort<br/>
			  *  - webProxyUsername<br/>
			  *  - webProxyPassword<br/>
			  *  - webProxyIeAddress<br/>
			  *  - webProxyIePort<br/>
			  *  - portalAddress<br/>
			  *  - ringtoneDeviceName<br/>
			  *  - verifyCertPortalAcct<br/>
			  *  - webProxyScriptUrl<br/>
			  *  - webProxyIeScriptUrl<br/>
			  *  - mediaLowPort<br/>
			  *  - mediaHighPort<br/>
			  *  - proxySettings<br/>
			  *  - videoPreferences ("BestQuality", "BestFramerate", "BestResolution", "LimitedBandwidth",<br/>
			  *                      "Advanced450p30", "Advanced720p15", "Advanced720p30")<br/>
			  *  - enableLogging<br/>
			  *  - enableAutoAnswer<br/>
			  *  - enableForceProxy<br/>
			  *  - enableLogWindow<br/>
			  *  - enableEntryTone<br/>
			  *  - enableEchoDetection<br/>
			  *  - enableEchoCancellation<br/>
			  *  - enableFullScreenVideo<br/>
			  *  - showToolbarInFullScreenVideo<br/>
			  *  - enableAudioAGC<br/>
			  *  - enableAutoStart<br/>
			  *  - enableShowConfParticipantName<br/>
			  *  - enableMuteMicrophoneOnJoin<br/>
			  *  - enableHideCameraOnJoin<br/>
			  *  - enableMuteSpeakerOnJoin<br/>
			  *  - enableEulaAgreed<br/>
			  *  - enableRendering<br/>
			  *  - enableBackgrounding<br/>
			  *  - enableFullDisplaySharing<br/>
			  *  - selfViewLoopbackPolicy<br/>
			  *
			  * @name vidyoClientMessages.requestGetConfiguration
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetConfiguration': function (params) {
				// object created by this factory function
				var that = this.requestConfiguration("RequestGetConfiguration", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set configuration request object.
			  * Request used to set various configuration parameters.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - microphones<br/>
			  *  - microphonePhyDeviceName<br/>
			  *  - microphoneVoiceProcessingSupport<br/>
			  *  - numberMicrophones<br/>
			  *  - currentMicrophone<br/>
			  *  - speakers<br/>
 			  *  - speakerPhyDeviceName<br/>
			  *  - numberSpeakers<br/>
			  *  - currentSpeaker<br/>
			  *  - cameras<br/>
			  *  - numberCameras<br/>
			  *  - currentCamera<br/>
			  *  - enableFeccEndpoint<br/>
			  *  - enableFeccController<br/>
			  *  - vidyoProxies<br/>
			  *  - numberVidyoProxies<br/>
			  *  - currentVidyoProxy<br/>
			  *  - userID<br/>
			  *  - password<br/>
			  *  - serverAddress<br/>
			  *  - serverPort<br/>
			  *  - vidyoProxyAddress<br/>
			  *  - vidyoProxyPort<br/>
			  *  - webProxyAddress<br/>
			  *  - webProxyPort<br/>
			  *  - webProxyUsername<br/>
			  *  - webProxyPassword<br/>
			  *  - webProxyIeAddress<br/>
			  *  - webProxyIePort<br/>
			  *  - portalAddress<br/>
			  *  - ringtoneDeviceName<br/>
			  *  - verifyCertPortalAcct<br/>
			  *  - webProxyScriptUrl<br/>
			  *  - webProxyIeScriptUrl<br/>
			  *  - mediaLowPort<br/>
			  *  - mediaHighPort<br/>
			  *  - proxySettings<br/>
			  *  - videoPreferences ("BestQuality", "BestFramerate", "BestResolution", "LimitedBandwidth",<br/>
			  *                      "Advanced450p30", "Advanced720p15", "Advanced720p30")<br/>
			  *  - enableLogging<br/>
			  *  - enableAutoAnswer<br/>
			  *  - enableForceProxy<br/>
			  *  - enableLogWindow<br/>
			  *  - enableEntryTone<br/>
			  *  - enableEchoDetection<br/>
			  *  - enableEchoCancellation<br/>
			  *  - enableFullScreenVideo<br/>
			  *  - showToolbarInFullScreenVideo<br/>
			  *  - enableAudioAGC<br/>
			  *  - enableAutoStart<br/>
			  *  - enableShowConfParticipantName<br/>
			  *  - enableMuteMicrophoneOnJoin<br/>
			  *  - enableHideCameraOnJoin<br/>
			  *  - enableMuteSpeakerOnJoin<br/>
			  *  - enableEulaAgreed<br/>
			  *  - enableRendering<br/>
			  *  - enableBackgrounding<br/>
			  *  - enableFullDisplaySharing<br/>
			  *  - selfViewLoopbackPolicy<br/>
			  *
			  * @name vidyoClientMessages.requestSetConfiguration
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetConfiguration': function (params) {
				// object created by this factory function
				var that = this.requestConfiguration("RequestSetConfiguration", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient volume audio request object.
			  * Request used to get/set volume of various media devices.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - volume<br/>
			  *
			  * @name vidyoClientMessages.requestVolumeAudio
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestVolumeAudio': function (type, params) {
				// object created by this factory function
				var that = this.request(type);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.volume = params && params.volume || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get volume audio in request object.
			  * Request used to get volume of audio input (capture/microphone) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - volume<br/>
			  *
			  * @name vidyoClientMessages.requestGetVolumeAudioIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetVolumeAudioIn': function (params) {
				// object created by this factory function
				var that = this.requestVolumeAudio("RequestGetVolumeAudioIn", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set volume audio in request object.
			  * Request used to set volume of audio input (capture/microphone) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - volume<br/>
			  *
			  * @name vidyoClientMessages.requestSetVolumeAudioIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetVolumeAudioIn': function (params) {
				// object created by this factory function
				var that = this.requestVolumeAudio("RequestSetVolumeAudioIn", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get volume audio out request object.
			  * Request used to get volume of audio output (playback/speaker) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - volume<br/>
			  *
			  * @name vidyoClientMessages.requestGetVolumeAudioOut
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetVolumeAudioOut': function (params) {
				// object created by this factory function
				var that = this.requestVolumeAudio("RequestGetVolumeAudioOut", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set volume audio out request object.
			  * Request used to set volume of audio output (playback/speaker) device.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - volume<br/>
			  *
			  * @name vidyoClientMessages.requestSetVolumeAudioOut
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetVolumeAudioOut': function (params) {
				// object created by this factory function
				var that = this.requestVolumeAudio("RequestSetVolumeAudioOut", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient window shares request object.
			  * Request used to get list of or manage viewing of remote window shares.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - requestType ("ListSharingWindows", "ChangeSharingWindow",
			  *                 "ToggleSharingWindow", "StopSharingWindow")<br/>
			  *  - remoteAppUri<br/>
			  *  - remoteAppName<br/>
			  *  - numApp<br/>
			  *  - currApp<br/>
			  *  - eventUri<br/>
			  *  - newApp<br/>
			  *
			  * @name vidyoClientMessages.requestWindowShares
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestWindowShares': function (type, params) {
				// object created by this factory function
				var that = this.request(type);

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.requestType = params && params.requestType || "";
				that.remoteAppUri = params && params.remoteAppUri || [""];
				that.remoteAppName = params && params.remoteAppName || [""];
				that.numApp = params && params.numApp || 0;
				that.currApp = params && params.currApp || 0;
				that.eventUri = params && params.eventUri || "";
				that.newApp = params && params.newApp || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get window shares request object.
			  * Request used to get list of remote window shares.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - requestType ("ListSharingWindows")<br/>
			  *  - remoteAppUri<br/>
			  *  - remoteAppName<br/>
			  *  - numApp<br/>
			  *  - currApp<br/>
			  *
			  * @name vidyoClientMessages.requestGetWindowShares
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetWindowShares': function (params) {
				// object created by this factory function
				var that = this.requestWindowShares("RequestGetWindowShares", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set window shares request object.
			  * Request used to manage viewing of remote window shares.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - requestType ("ChangeSharingWindow",
			  *                 "ToggleSharingWindow", "StopSharingWindow")<br/>
			  *  - remoteAppUri<br/>
			  *  - remoteAppName<br/>
			  *  - numApp<br/>
			  *  - currApp<br/>
			  *  - eventUri<br/>
			  *  - newApp<br/>
			  *
			  * @name vidyoClientMessages.requestSetWindowShares
			  * @function
			  * @param {String} type String value for specific type of message.
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetWindowShares': function (params) {
				// object created by this factory function
				var that = this.requestWindowShares("RequestSetWindowShares", params);

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get current session display info request object.
			  * Request used to get information that could be displayed to
			  * the user, relating to conference state.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - sessionDisplayContext ("Conf", "OutCall", "InCall", "Idle")<br/>
			  *  - sessionDisplayText<br/>
			  *
			  * @name vidyoClientMessages.requestGetCurrentSessionDisplayInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetCurrentSessionDisplayInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetCurrentSessionDisplayInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.sessionDisplayContext = params && params.sessionDisplayContext || "Conf";
				that.sessionDisplayText = params && params.sessionDisplayText || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get current Endpoint ID (EID) request object.
			  * Request used to get endpoint's unique identifier.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - EID <br/>
			  *
			  * @name vidyoClientMessages.requestGetEID
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetEID': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetEID");
				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.EID = params && params.EID || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get current long Endpoint ID (LID) request object.
			  * Request used to get endpoint's unique long identifier.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - LID <br/>
			  *
			  * @name vidyoClientMessages.requestGetLID
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetLID': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetLID");
				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.LID = params && params.LID || "";

				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates an object with VidyoClient request to activate installation license of an endpoint.
			  * Request used to activate installation license of an endpoint.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - lacKey <br/>
			  *
			  * @name vidyoClientMessages.requestActivateEID
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestActivateEID': function (params) {
				// object created by this factory function
				var that = this.request("RequestActivateEID");
				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.lacKey = params && params.lacKey || "";

				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient get current installation licence status request object.
			  * Request used to get endpoint's installation license status.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isLicensed <br/>
			  *
			  * @name vidyoClientMessages.requestGetLicensedStatus
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetLicensedStatus': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetLicensedStatus");
				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isLicensed = params && params.isLicensed || false;

				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient get audio energy request object.
			  * Request used to get audio energy level of audio devices.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - rendererEnergy <br/>
			  *  - capturerEnergy <br/>			  
			  *
			  * @name vidyoClientMessages.requestGetAudioEnergyInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetAudioEnergyInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetAudioEnergyInfo");
				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.rendererEnergy = params && params.rendererEnergy || 0;
				that.capturerEnergy = params && params.capturerEnergy || 0;
				
				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient get participants request object.
			  * Request used to get list of participants in current conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - name<br/>
			  *  - URI<br/>
			  *
			  * @name vidyoClientMessages.requestGetParticipants
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetParticipants': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetParticipants");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.name = params && params.name || [];

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get number of participants request object.
			  * Request used to get number of participants in current conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numParticipants<br/>
			  *
			  * @name vidyoClientMessages.requestGetNumParticipants
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetNumParticipants': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetNumParticipants");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numParticipants = params && params.numParticipants || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get participants name at request object.
			  * Request used to get name of participant at specified index.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numParticipants<br/>
			  *
			  * @name vidyoClientMessages.requestGetParticipantNameAt
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetParticipantNameAt': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetParticipantNameAt");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.index = params && params.index || 0;
				that.result = params && params.result || false;
				that.name = params && params.name || "";

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get participant statistics at request object.
			  * Request used to get statistics for the specified participant
			  * (by index value) in current conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - index<br/>
			  *  - result<br/>
			  *  - uri<br/>
			  *  - name<br/>
			  *  - videoResolution (containing following properties):<br/>
			  *    -- xPos<br/>
			  *    -- yPos<br/>
			  *    -- width<br/>
			  *    -- height<br/>
			  *  - videoKBitsPerSecRecv<br/>
			  *  - audioKBitsPerSecRecv<br/>
			  *  - firs<br/>
			  *  - nacks<br/>
			  *  - videoFrameRate<br/>
			  *  - videoDecodedFrameRate<br/>
			  *  - videoDisplayedFrameRate<br/>
			  *
			  * @name vidyoClientMessages.requestGetParticipantStatisticsAt
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetParticipantStatisticsAt': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetParticipantStatisticsAt");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.index = params && params.index || 0;
				that.result = params && params.result || false;
				that.uri = params && params.uri || "";
				that.name = params && params.name || "";
				that.videoResolution = params && params.videoResolution || {
						'xPos': 0,
						'yPos': 0,
						'width': 0,
						'height': 0
					};
				that.videoKBitsPerSecRecv = params && params.videoKBitsPerSecRecv || 0;
				that.audioKBitsPerSecRecv = params && params.audioKBitsPerSecRecv || 0;
				that.firs = params && params.firs || 0;
				that.nacks = params && params.nacks || 0;
				that.videoFrameRate = params && params.videoFrameRate || 0;
				that.videoDecodedFrameRate = params && params.videoDecodedFrameRate || 0;
				that.videoDisplayedFrameRate = params && params.videoDisplayedFrameRate || 0;

				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get windows and desktops request object.
			  * Request used to get list of open application windows and
			  * list of available system desktops.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numApplicationWindows<br/>
			  *  - appWindowName<br/>
			  *  - appWindowAppName<br/>
			  *  - appWindowId<br/>
			  *  - numSystemDesktops<br/>
			  *  - sysDesktopName<br/>
			  *  - sysDesktopId<br/>
			  *
			  * @name vidyoClientMessages.requestGetWindowsAndDesktops
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetWindowsAndDesktops': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetWindowsAndDesktops");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numApplicationWindows = params && params.numApplicationWindows || 0;
				that.appWindowName = params && params.appWindowName || [""];
				that.appWindowAppName = params && params.appWindowAppName || [""];
				that.appWindowId = params && params.appWindowId || ["0x0000000000000000"];
				that.numSystemDesktops = params && params.numSystemDesktops || 0;
				that.sysDesktopName = params && params.sysDesktopName || [""];
				that.sysDesktopId = params && params.sysDesktopId || ["0x0000000000000000"];

				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient get sharable window white list request object.
			  * Request is used to get list of windows names that are marked as white list
			  * and all those windows names matches with white list will be available
			  * in requestGetWindowsAndDesktops even if they are not visible or a tool
			  * window as per window style.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numWindows<br/>
			  *  - windowName<br/>
			  *
			  * @name vidyoClientMessages.RequestGetSharableWindowWhiteList
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'RequestGetSharableWindowWhiteList': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetSharableWindowWhiteList");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numWindows = params && params.numWindows || 0;
				that.windowName = params && params.windowName || [""];
				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient set sharable window white list request object.
			  * Request is used to set the list of windows names that has to be marked as white list.
			  * All those windows names matches with white list will be available
			  * in requestGetWindowsAndDesktops even if they are not visible or a tool
			  * window as per window style.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numWindows<br/>
			  *  - windowName<br/>
			  *
			  * @name vidyoClientMessages.RequestSetSharableWindowWhiteList
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'RequestSetSharableWindowWhiteList': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetSharableWindowWhiteList");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numWindows = params && params.numWindows || 0;
				that.windowName = params && params.windowName || [""];
				// return object created by this factory function
				return that;
			},
			
			/**
			  * Creates a VidyoClient get connectivity info request object.
			  * Request used to get information about connection to VidyoPortal
			  * and VidyoManager.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - serverAddress<br/>
			  *  - serverPort<br/>
			  *  - serverSecured (true, false)<br/>
			  *  - vmIdentity<br/>
			  *  - userName<br/>
			  *  - portalAddress<br/>
			  *  - portalVersion<br/>
			  *  - locationTag<br/>
			  *  - vidyoProxyAddress<br/>
			  *  - vidyoProxyPort<br/>
			  *  - guestLogin<br/>
			  *  - clientExternalIPAddress<br/>
			  *  - proxyType ("ProxyNone", "VidyoProxy", "ReverseProxy")<br/>
			  *  - reverseProxyAddress<br/>
			  *  - reverseProxyPort<br/>
			  *
			  * @name vidyoClientMessages.requestGetConnectivityInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetConnectivityInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetConnectivityInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.serverAddress           = params && params.serverAddress || "";
				that.serverPort              = params && params.serverPort || "";
				that.serverSecured           = params && params.serverSecured || false;
				that.vmIdentity              = params && params.vmIdentity || "";
				that.userName                = params && params.userName || "";
				that.portalAddress           = params && params.portalAddress || "";
				that.portalVersion           = params && params.portalVersion || "";
				that.locationTag             = params && params.locationTag || "";
				that.vidyoProxyAddress       = params && params.vidyoProxyAddress || "";
				that.vidyoProxyPort          = params && params.vidyoProxyPort || "";
				that.guestLogin              = params && params.guestLogin || false;
				that.clientExternalIPAddress = params && params.clientExternalIPAddress || "";
				that.proxyType               = params && params.proxyType || "";
				that.reverseProxyAddress     = params && params.reverseProxyAddress || "";
				that.reverseProxyPort        = params && params.reverseProxyPort || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get send maximum bandwidth request object.
			  * Request used to get information about maximum bandwidth used to send data.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - value<br/>
			  *
			  * @name vidyoClientMessages.requestGetSendMaxKbps
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetSendMaxKbps': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetSendMaxKbps");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.value = params && params.value || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set send maximum bandwidth request object.
			  * Request used to set maximum bandwidth used to send data.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - value<br/>
			  *
			  * @name vidyoClientMessages.requestSetSendMaxKbps
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetSendMaxKbps': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetSendMaxKbps");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.value = params && params.value || 10000;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get receive maximum bandwidth request object.
			  * Request used to get information about maximum bandwidth used to receive data.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - value<br/>
			  *
			  * @name vidyoClientMessages.requestGetReceiveMaxKbps
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetReceiveMaxKbps': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetReceiveMaxKbps");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.value = params && params.value || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set receive maximum bandwidth request object.
			  * Request used to set maximum bandwidth used to receive data.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - value<br/>
			  *
			  * @name vidyoClientMessages.requestSetReceiveMaxKbps
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetReceiveMaxKbps': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetReceiveMaxKbps");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.value = params && params.value || 10000;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set label request object.
			  * Request used to set current user display label for self view.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - labelType ("SelfView")<br/>
			  *  - labelText<br/>
			  *
			  * @name vidyoClientMessages.requestSetLabel
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetLabel': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetLabel");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.labelType = params && params.labelType || "SelfView";
				that.labelText = params && params.labelText || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get preview mode request object.
			  * Request used to get preview mode for self-view.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - previewMode ("None", "PIP", "Dock")<br/>
			  *
			  * @name vidyoClientMessages.requestGetPreviewMode
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetPreviewMode': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetPreviewMode");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.previewMode = params && params.previewMode || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get microphone mute state request object.
			  * Request used to get a local mute state of microphone.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isMuted (true, false)<br/>
			  *
			  * @name vidyoClientMessages.requestGetMutedAudioIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMutedAudioIn': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMutedAudioIn");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isMuted = params && params.isMuted || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get speaker mute state request object.
			  * Request used to get a local mute state of the speaker.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isMuted (true, false)<br/>
			  *
			  * @name vidyoClientMessages.requestGetMutedAudioOut
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMutedAudioOut': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMutedAudioOut");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isMuted = params && params.isMuted || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get camera mute state request object.
			  * Request used to get a local mute state of camera.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isMuted (true, false)<br/>
			  *
			  * @name vidyoClientMessages.requestGetMutedVideo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMutedVideo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMutedVideo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isMuted = params && params.isMuted || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get microphone mute state on server request object.
			  * Request used to get a server mute state of microphone.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isMuted (true, false)<br/>
			  *
			  * @name vidyoClientMessages.requestGetMutedServerAudioIn
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMutedServerAudioIn': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMutedServerAudioIn");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isMuted = params && params.isMuted || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get camera mute state on server request object.
			  * Request used to get a server mute state of camera.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isMuted (true, false)<br/>
			  *
			  * @name vidyoClientMessages.requestGetMutedServerVideo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMutedServerVideo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMutedServerVideo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isMuted = params && params.isMuted || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get echo cancellation recommendation request object.
			  * Request used to get an echo cancellation recommendation for a pair of microphone
			  * and speaker.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - speakerIndex<br/>
			  *  - micIndex<br/>
			  *  - disableEcho (true - do not enable echo cancellation, false - enable)<br/>
			  *
			  * @name vidyoClientMessages.requestGetEchoRecommendation
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetEchoRecommendation': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetEchoRecommendation");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.speakerIndex = params && params.speakerIndex || 0;
				that.micIndex     = params && params.micIndex || 0;
				that.disableEcho  = params && params.disableEcho || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient check device recommendation request object.
			  * Request used to check if device is recommended for video conferencing.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - deviceType ("AudioOut", "AudioIn", "Video", "RingTone")<br/>
			  *  - deviceIndex<br/>
			  *  - isRecommended (true - recommended, false - unknown/not recommended)<br/>
			  *
			  * @name vidyoClientMessages.requestCheckRecommended
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestCheckRecommended': function (params) {
				// object created by this factory function
				var that = this.request("RequestCheckRecommended");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.deviceType    = params && params.speakerIndex || "";
				that.deviceIndex   = params && params.deviceIndex || -1;
				that.isRecommended = params && params.isRecommended || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient check proxy settings request object.
			  * Request used to check if proxy setting is valid.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - isValid (true - valid, false - not valid)<br/>
			  *
			  * @name vidyoClientMessages.requestGetWebProxySettingsValid
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetWebProxySettingsValid': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetWebProxySettingsValid");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.isValid = params && params.isValid || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient set proxy credentials request object.
			  * Request used to set proxy credentials with possibility to persist data.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - persist (true - persist, false - use )<br/>
			  *  - username<br/>
			  *  - password<br/>
			  *
			  * @name vidyoClientMessages.requestSetWebProxyCredentials
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestSetWebProxyCredentials': function (params) {
				// object created by this factory function
				var that = this.request("RequestSetWebProxyCredentials");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.persist  = params && params.persist || false;
				that.username = params && params.username || "";
				that.password = params && params.password || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get current user information request object.
			  * Request used to get current user information.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - currentUserID<br/>
			  *  - currentUserDisplay<br/>
			  *
			  * @name vidyoClientMessages.requestGetCurrentUser
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetCurrentUser': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetCurrentUser");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.currentUserID      = params && params.currentUserID || "";
				that.currentUserDisplay = params && params.currentUserDisplay || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get participants limit request object.
			  * Request used to get participants number limit due to bandwidth, CPU or user settings.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - bandwidthLimited<br/>
			  *  - cpuLimited<br/>
			  *  - userLimited<br/>
			  *
			  * @name vidyoClientMessages.requestGetParticipantsLimit
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetParticipantsLimit': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetParticipantsLimit");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.bandwidthLimited = params && params.currentUserID || 0;
				that.cpuLimited       = params && params.cpuLimited || 0;
				that.userLimited      = params && params.userLimited || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get display name of the inviting user request object.
			  * Request used to get display name of the inviting user in the case of incoming call.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - invitingUser<br/>
			  *
			  * @name vidyoClientMessages.requestGetInvitingUser
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetInvitingUser': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetInvitingUser");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.invitingUser = params && params.invitingUser || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get VidyoRouter address request object.
			  * Request used to get VidyoRouter address while in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - routerAddress<br/>
			  *
			  * @name vidyoClientMessages.requestGetCurrentSessionVidyoRouter
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetCurrentSessionVidyoRouter': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetCurrentSessionVidyoRouter");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.routerAddress = params && params.routerAddress || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get FECC devices request object.
			  * Request used to get a list of FECC devices available in the conference.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - uri<br/>
			  *  - name<br/>
			  *  - privacyMode<br/>
			  *  - numberParticipants<br/>
			  *  - feccParticipantIndex<br/>
			  *
			  * @name vidyoClientMessages.requestGetFeccList
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetFeccList': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetFeccList");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.uri                  = params && params.uri || [""];
				that.name                 = params && params.name || [""];
				that.privacyMode          = params && params.privacyMode || [false];
				that.numberParticipants   = params && params.numberParticipants || 0;
				that.feccParticipantIndex = params && params.feccParticipantIndex || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get information about conference request object.
			  * Request used to get inforamation about conference activity like webcasting or recording.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - recording<br/>
			  *  - webcasting<br/>
			  *
			  * @name vidyoClientMessages.requestGetConferenceInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetConferenceInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetConferenceInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.recording  = params && params.recording || false;
				that.webcasting = params && params.webcasting || false;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get current call state request object.
			  * Request used to get current call state.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - callState ("Idle", "Ringing", "Calling", "Joining", "InConference", "Disconnecting")<br/>
			  *
			  * @name vidyoClientMessages.requestGetCallState
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetCallState': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetCallState");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.callState = params && params.callState || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get bandwidth info request object.
			  * Request used to get current bandwidth information.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - AvailSendBwVideo<br/>
			  *  - AvailSendBwAudio<br/>
			  *  - AvailSendBwApplication<br/>
			  *  - AvailSendBwMax<br/>
			  *  - ActualSendBwVideo<br/>
			  *  - ActualSendBwAudio<br/>
			  *  - ActualSendBwApplication<br/>
			  *  - ActualSendBwMax<br/>
			  *  - AvailRecvBwVideo<br/>
			  *  - AvailRecvBwAudio<br/>
			  *  - AvailRecvBwApplication<br/>
			  *  - AvailRecvBwMax<br/>
			  *  - ActualRecvBwVideo<br/>
			  *  - ActualRecvBwAudio<br/>
			  *  - ActualRecvBwApplication<br/>
			  *  - ActualRecvBwMax<br/>
			  *
			  * @name vidyoClientMessages.requestGetBandwidthInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetBandwidthInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetBandwidthInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.AvailSendBwVideo        = params && params.AvailSendBwVideo || 0;
				that.AvailSendBwAudio        = params && params.AvailSendBwAudio || 0;
				that.AvailSendBwApplication  = params && params.AvailSendBwApplication || 0;
				that.AvailSendBwMax          = params && params.AvailSendBwMax || 0;
				that.ActualSendBwVideo       = params && params.ActualSendBwVideo || 0;
				that.ActualSendBwAudio       = params && params.ActualSendBwAudio || 0;
				that.ActualSendBwApplication = params && params.ActualSendBwApplication || 0;
				that.ActualSendBwMax         = params && params.ActualSendBwMax || 0;
				that.AvailRecvBwVideo        = params && params.AvailRecvBwVideo || 0;
				that.AvailRecvBwAudio        = params && params.AvailRecvBwAudio || 0;
				that.AvailRecvBwApplication  = params && params.AvailRecvBwApplication || 0;
				that.AvailRecvBwMax          = params && params.AvailRecvBwMax || 0;
				that.ActualRecvBwVideo       = params && params.ActualRecvBwVideo || 0;
				that.ActualRecvBwAudio       = params && params.ActualRecvBwAudio || 0;
				that.ActualRecvBwApplication = params && params.ActualRecvBwApplication || 0;
				that.ActualRecvBwMax         = params && params.ActualRecvBwMax || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get video encoder resolution request object.
			  * Request used to get video encoder resolution.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - rect (containing following properties):<br/>
			  *    -- xPos<br/>
			  *    -- yPos<br/>
			  *    -- width<br/>
			  *    -- height<br/>
			  *
			  * @name vidyoClientMessages.requestGetEncodeResolution
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetEncodeResolution': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetEncodeResolution");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.rect = params && params.rect || {xPos:0,yPos:0,width:0,height:0};
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get video frame rate info request object.
			  * Request used to get video encoder frame rate info.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - captureFrameRate
			  *  - encodeFrameRate
			  *  - sendFrameRate
			  *
			  * @name vidyoClientMessages.requestGetVideoFrameRateInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetVideoFrameRateInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetVideoFrameRateInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.captureFrameRate	= params && params.captureFrameRate || 0;
				that.encodeFrameRate	= params && params.encodeFrameRate || 0;
				that.sendFrameRate	= params && params.sendFrameRate || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get media info request object.
			  * Request used to get information about media plane.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - numIFrames<br/>
			  *  - numFirs<br/>
			  *  - numNacks<br/>
			  *  - mediaRTT<br/>
			  *
			  * @name vidyoClientMessages.requestGetMediaInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetMediaInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetMediaInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.numIFrames = params && params.numIFrames || 0;
				that.numFirs    = params && params.numFirs || 0;
				that.numNacks   = params && params.numNacks || 0;
				that.mediaRTT   = params && params.mediaRTT || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get rate shaper request object.
			  * Request used to get advanced media/rate shaper statistics.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - delayVideoPriorytyNormal<br/>
			  *  - numPacketsVideoPriorytyNormal<br/>
			  *  - numFramesVideoPriorytyNormal<br/>
			  *  - numDroppedVideoPriorytyNormal<br/>
			  *  - delayVideoPriorutyRetransmit<br/>
			  *  - numPacketsVideoPriorutyRetransmit<br/>
			  *  - numFramesVideoPriorutyRetransmit<br/>
			  *  - numDroppedVideoPriorutyRetransmit<br/>
			  *  - delayAppPriorityNormal<br/>
			  *  - numFramesAppPriorityNormal<br/>
			  *  - numDroppedAppPriorityNormal<br/>
			  *  - delayAppPriorityRetransmit<br/>
			  *  - numPacketsAppPriorityRetransmit<br/>
			  *  - numFramesAppPriorityRetransmit<br/>
			  *  - numDroppedAppPriorityRetransmit<br/>
			  *
			  * @name vidyoClientMessages.requestGetRateShaperInfo
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetRateShaperInfo': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetRateShaperInfo");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.delayVideoPriorytyNormal          = params && params.delayVideoPriorytyNormal || 0;
				that.numPacketsVideoPriorytyNormal     = params && params.numPacketsVideoPriorytyNormal || 0;
				that.numFramesVideoPriorytyNormal      = params && params.numFramesVideoPriorytyNormal || 0;
				that.numDroppedVideoPriorytyNormal     = params && params.numDroppedVideoPriorytyNormal || 0;
				that.delayVideoPriorutyRetransmit      = params && params.delayVideoPriorutyRetransmit || 0;
				that.numPacketsVideoPriorutyRetransmit = params && params.numPacketsVideoPriorutyRetransmit || 0;
				that.numFramesVideoPriorutyRetransmit  = params && params.numFramesVideoPriorutyRetransmit || 0;
				that.numDroppedVideoPriorutyRetransmit = params && params.numDroppedVideoPriorutyRetransmit || 0;
				that.delayAppPriorityNormal            = params && params.delayAppPriorityNormal || 0;
				that.numFramesAppPriorityNormal        = params && params.numFramesAppPriorityNormal || 0;
				that.numDroppedAppPriorityNormal       = params && params.numDroppedAppPriorityNormal || 0;
				that.delayAppPriorityRetransmit        = params && params.delayAppPriorityRetransmit || 0;
				that.numPacketsAppPriorityRetransmit   = params && params.numPacketsAppPriorityRetransmit || 0;
				that.numFramesAppPriorityRetransmit    = params && params.numFramesAppPriorityRetransmit || 0;
				that.numDroppedAppPriorityRetransmit   = params && params.numDroppedAppPriorityRetransmit || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get CPU utilization request object.
			  * Request used to get CPU utilization.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - value<br/>
			  *
			  * @name vidyoClientMessages.requestGetCurrentCpuUtilization
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetCurrentCpuUtilization': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetCurrentCpuUtilization");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.value = params && params.value || 0;
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient get enpoint status request object.
			  * Request used to get enpoint status.
			  *
			  * The passed in parameter object can store the following
			  * properties:<br/>
			  *  - endpointStatus ("Inactive", "Registered", "Active")<br/>
			  *
			  * @name vidyoClientMessages.requestGetEndpointStatus
			  * @function
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'requestGetEndpointStatus': function (params) {
				// object created by this factory function
				var that = this.request("RequestGetEndpointStatus");

				// public properties for created object,
				// initial values of which are potentially passed
				// into this factory function
				that.endpointStatus = params && params.endpointStatus || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Creates a VidyoClient inEventGetWindowsExt  in event object.
			  * Used to get a full list of windows in the system
			  * This Event is only currently implemented and returned under windows
			  *
			  * The passed in parameter object can store the following properties:<BR/>
			  *	 - requestId a unique id for each message. this id is used in the responses.<BR/>
			  *
			  * @name vidyoClientMessages.inEventGetWindowsExt
			  * @function			 
			  * @param {Object} params Reference to parameter object.
			  * @return {Object} Reference to created object.
			  */
			'inEventGetWindowsExt': function (params) {
				// object created by this factory function
				var that = this.inEvent("inEventGetWindowsExt");
				that.requestId = params && params.requestId || "";
				// return object created by this factory function
				return that;
			},

			/**
			  * Returns type of a VidyoClient private Extended window list message
			  * Event is used to find special windows to share that are not listed by the regular apu
			  * This Event is only currently implemented and returned under windows
			  * The event object can store the following
			              * properties:
              *  - requestId<br/>
              *  - totalResponseMessages<br/>
              *  - thisMessageNumberInSequance<br/>
              *  - totalNumApplicationWindows<br/>
              *  - numOfRecordsInThisMessage<br/>
              *  - windowID<br/>
              *  - windowName<br/>
              *  - windowOwnerName<br/>
              *  - windowRect<br/>
              *  - win32.windowClassName<br/>
              *  - win32.parentHandle<br/>
              *  - win32.dwStyle<br/>
              *  - win32.dwExStyle<br/>

			  * @name vidyoClientMessages.OutEventGetWindowsExt
			  * @function
			  * @return {String} String value for type.
			  */
			'OutEventGetWindowsExt': function () {
				// return type of event
				return "OutEventGetWindowsExt";
			}			
		}

		return vidyoClientMessages;
	}
);
