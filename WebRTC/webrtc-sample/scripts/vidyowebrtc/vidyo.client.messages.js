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
  */

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
     * Creates a VidyoClient configuration request object.
     * Request used to get/set various configuration parameters.
     *
     * The passed in parameter object can store the following
     * properties:<br/>
     *  - microphones<br/>
     *  - numberMicrophones<br/>
     *  - currentMicrophone<br/>
     *  - speakers<br/>
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
     *  - numberMicrophones<br/>
     *  - currentMicrophone<br/>
     *  - speakers<br/>
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
     *  - numberMicrophones<br/>
     *  - currentMicrophone<br/>
     *  - speakers<br/>
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

}

