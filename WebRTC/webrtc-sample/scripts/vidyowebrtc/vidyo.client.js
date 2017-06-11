/*! @file vidyo.client.js
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
  * @fileOverview This file defines the module for the VidyoClient object.
  * @author Vidyo Inc.
  */

/**
  * Creates a VidyoClient object.
  * @class Wrapper for VidyoClient.
  *
  * @param {Object} config Reference to configuration object.
  * @return {Object} Reference to created VidyoClient wrapper object.
*/
var vidyoClient = function (config) {
    // object created by this factory function
    /** @private */ var that = {};

    // private instance variables for created object,
    // initial values of which are potentially passed
    // into this factory function
    /** @private */ 
    var webrtcPlugin = null;

    /** @private */
    var outEventCallbackObject = null;

    /** @private */ 
    var defaultOutEventCallbackMethod = "";

    /** @private */ 
    var logCallback = null;

    /** @private */ 
    var sessionManager = null;

    // other private instance variables for created object
    /** @private */ 
    var outEventCallbackMethods = {};

    // private helper functions
    /** @private */ 
    var setConfig = function (config) {
        if (config && config.outEventCallbackObject !== undefined) {
            outEventCallbackObject = config.outEventCallbackObject;
        }
        if (config && config.defaultOutEventCallbackMethod !== undefined) {
            defaultOutEventCallbackMethod = config.defaultOutEventCallbackMethod;
        }
        if (config && config.logCallback !== undefined) {
            logCallback = config.logCallback;
        }
        if (config && config.sessionManager !== undefined) {
            sessionManager = config.sessionManager;
        }
    };

    /** @private */ 
    var log = function (message) {
        if (logCallback) {
            logCallback(message);
        }
    };

    /****************************************
     * API accessor (getter/setter) functions
     ****************************************/

    /**
     * Sets the callback object that will be used by the invoked
     * VidyoClient wrapper object, for any out event callbacks.
     * Will only be used if the callback method to be invoked was set
     * to a non-function value type.
     *
     * @param {Object} outEventCallbackObjectArg Reference to out event
     *                                           callback object.
     * @return {Object} Reference to invoked VidyoClient wrapper object.
     */
    var setOutEventCallbackObject = function (outEventCallbackObjectArg) {
        outEventCallbackObject = outEventCallbackObjectArg;
    };

    /**
     * Sets the callback method that will be used by the invoked
     * VidyoClient wrapper object, for any out event type by default.
     * If method is specified using a string value type, it will be
     * invoked with variable 'this' set to the value set as the callback
     * object.
     * If method is specified using a function value type, it will be
     * invoked with variable 'this' set to the wrapper object.
     *
     * @param {Object} defaultOutEventCallbackMethodArg Default out event
     *                                                  callback method name
     *                                                  (when String) or
     *                                                  function object.
     * @return {Object} Reference to invoked VidyoClient wrapper object.
     */
    var setDefaultOutEventCallbackMethod = function (defaultOutEventCallbackMethodArg) {
        defaultOutEventCallbackMethod = defaultOutEventCallbackMethodArg;
    };

    /**
     * Sets the callback function that will be used by the invoked
     * VidyoClient wrapper object, for logging.
     *
     * @param {Function} logCallbackArg Reference to logging callback
     *                                  function object.
     * @return {Object} Reference to invoked VidyoClient wrapper object.
     */
    var setLogCallback = function (logCallbackArg) {
        logCallback = logCallbackArg;
    };

    /**
     * Sets the sessionManager address that will be used by the invoked
     * VidyoClient wrapper object, for making call to
     *
     * @param {String} sessionManagerArg address of session manager
     * @return {Object} Reference to invoked VidyoClient wrapper object.
     */
    var setSessionManager = function (sessionManagerArg) {
        sessionManager = sessionManagerArg;
    };

    /**
     * Sets the callback method that will be used by the invoked
     * VidyoClient wrapper object, for the specified out event type.
     * If method is specified using a string value type, it will be
     * invoked with variable 'this' set to the value set as the callback
     * object.
     * If method is specified using a function value type, it will be
     * invoked with variable 'this' set to the wrapper object.
     *
     * @param {String} outEventType String value for specific type of
     *                              out event.
     * @param {Object} callbackMethod Callback method name (when String)
     *                                or function object.
     * @return {Object} Reference to invoked VidyoClient wrapper object.
     */
    var setOutEventCallbackMethod = function (outEventType, callbackMethod) {
        outEventCallbackMethods[outEventType] = callbackMethod;
    };


    /**
     * Helper function to get a webrtc media server from session manager
     *
     * @param {String} session manager address
     * @param {Object} callback callback to be invoked with the webrtc server address
     */
    var getWebRTCServer = function(sessionManager, callback) {
        var url = window.location.protocol + "//" + sessionManager + "/zincadmin/service/getinstance.htm";
        var webRTCServer = "";
        var oReq = new XMLHttpRequest();
        oReq.open("get", url, true);
        oReq.onload = function() {
            var resp = JSON.parse(oReq.responseText);
            webRTCServer = resp.ip;
            callback(webRTCServer);
        };

        oReq.onerror = function(e) {
            callback("");
        };

        oReq.send();
    };

    var loadPlugin = function(webrtcServer, callback) {
        var adapterLoaded = false;
        if (window.attachMediaStream) {
            adapterLoaded = true;
        }
        var pluginLoaded = false;
        if (window.plugin) {
            pluginLoaded = true;
        }

        if (adapterLoaded && pluginLoaded) {
            callback(true);
        }

        if (!adapterLoaded) {
            var adapterjs = document.createElement('script');

            adapterjs.onload = function() {
                log("adapterjs loaded");
                adapterLoaded = true;
                if (pluginLoaded) {
                    callback(true);
                }
            };


            adapterjs.onerror = function(e) {
                log("adapterjs load failed");
                log(e);
                callback(false);
            };

            adapterjs.setAttribute('src', window.location.protocol + '//' + webrtcServer + '/web/scripts/vidyowebrtc/adapter.js');
            document.getElementsByTagName("head")[0].appendChild(adapterjs);
        }

        if (!pluginLoaded) {
            var pluginjs = document.createElement('script');
            pluginjs.onload = function() {
                log("pluginjs loaded");
                pluginLoaded = true;
                if (adapterLoaded) {
                    callback(true);
                }
            };
    
            pluginjs.onerror = function(e) {
                log("pluginJs load failed");
                callback(false);
            };
    
            pluginjs.setAttribute('src', window.location.protocol + '//' + webrtcServer + '/web/scripts/vidyowebrtc/plugin.js');
            document.getElementsByTagName("head")[0].appendChild(pluginjs);
        }

    };

    /****************************************
     * API general functions
     ****************************************/

    /**
     * Starts VidyoClient library, which only needs to be done
     * before use or stopping of the VidyoClent plug-in object.
     * If this function is invoked more than once, without an
     * intervening call to stop(), there will be no
     * side effects, and the value returned will not change.
     * If this function is never invoked, invocation of other
     * functions to send events or requests or stop the library
     * will return an indication of failure.
     *
     * The passed in configuration object can store the following
     * properties:
     *
     * @param {Object} config Reference to configuration object.
     * @return {boolean} true if starting successful, false otherwise.
     */
    var start = function (config) {
        var retVal = true;
        setConfig(config);
        if (!sessionManager) {
            log("start() invoked without sessionManager!");
            return false;
        }

        try {
            getWebRTCServer(sessionManager, function(webrtcServer) {
                log("start(): getWebRtcServer: sessionManager = " + sessionManager + " webrtcServer = " + webrtcServer);
                loadPlugin(webrtcServer, function(status) {
                    if (!status) {
                        log("start(): loadPlugin failed");
                        return;
                    }

                    webrtcPlugin = new plugin(vidyoClientMessages, webrtcServer);
                    dispatchOutEvent({type: "OutEventLogicStarted"});
                    webrtcPlugin.useCallbackForOutEvents = true;
                    webrtcPlugin.outEventCallbackObject = that;
                    webrtcPlugin.outEventCallbackMethod = "dispatchOutEvent";
                    retVal = webrtcPlugin.start();
                });
            });
        } catch (e) {
            log("start() threw an exception!");
            log(e);
            return retVal;
        }
        if (retVal) {
            log("start() called plug-in with successful return.");
        } else {
            log("start() called plug-in with return of error!");
        }
        return retVal;
    };

    /**
     * Stops VidyoClient library, which only needs to be done
     * after all use or before restart of the VidyoClent plug-in object.
     * If this function is invoked without a prior invocation of
     * start(), this function will do nothing.
     * If this function is invoked more than once, without an
     * intervening call to start(), there will be no
     * side effects, and the value returned will not change.
     * If this function is never invoked, resources may be
     * leaked at the level of the underlying platform.
     *
     * @return {boolean} true if stopping successful, false otherwise.
     */
    var stop = function () {
        var retVal = false;
        if (!webrtcPlugin) {
            log("stop() invoked without start!");
            return retVal;
        }
        /* DEBUG: retVal = true;*/
        try {
            retVal = webrtcPlugin.stop();
        } catch (e) {
            log("stop() threw an exception!");
            log(e);
            return retVal;
        }
        if (retVal) {
            log("stop() called plug-in with successful return.");
        } else {
            log("stop() called plug-in with return of error!");
        }
        return retVal;
    };

    /**
     * Sends passed in event object to VidyoClient library.
     * If this function is invoked without a prior invocation of
     * start(), this function will do nothing and return an
     * indication of failure.
     * Event object passed to this function should be an in
     * event, and not an out event.
     * Event processing is performed on another thread internal
     * to VidyoClient.
     *
     * @param {Object} event Reference to event object to send.
     * @return {boolean} true if successful, false otherwise.
     */
    var sendEvent = function (event) {
        var retVal = false;
        if (!webrtcPlugin) {
            log("sendEvent() invoked without start!");
            return retVal;
        }
        if (!event || typeof event !== 'object') {
            log("sendEvent() invoked without valid event object!");
            return retVal;
        }
        if (typeof event.length === 'number' && !(event.propertyIsEnumerable('length'))) {
            log("sendEvent() invoked without valid event object!");
            return retVal;
        }
        /* DEBUG: retVal = true;*/
        try {
            retVal = webrtcPlugin.sendEvent(event);
        } catch (e) {
            log("sendEvent() threw an exception!");
            log(e);
            return retVal;
        }
        if (retVal) {
            log("sendEvent() called plug-in with successful return.");
        } else {
            log("sendEvent() called plug-in with return of error!");
        }
        return retVal;
    };

    /**
     * Sends passed in request object to VidyoClient library.
     * If this function is invoked without a prior invocation of
     * start(), this function will do nothing and return an
     * indication of failure.
     * Request object passed to this function will be modified
     * for any output parameters of the request.
     * Request processing is performed on the same thread as
     * the caller.
     *
     * @param {Object} request Reference to request object to send.
     * @return {String} "ErrorOK" if successful, error string otherwise:<br/>
     *                   "ErrorInvalidRequest" if request object not valid<br/>
     *                   "ErrorRequestNoType" if no type property in request object<br/>
     *                   "ErrorRequestTypeInvalid" if value of type property not known<br/>
     *                   "ErrorRequestFailed" if VidyoClient returns failure for request<br/>
     */
    var sendRequest = function (request) {
        var retVal = "Error";
        if (!webrtcPlugin) {
            log("sendRequest() invoked without start");
            return "ErrorNoPlugin";
        }
        if (!request || typeof request !== 'object') {
            log("sendRequest() invoked without valid request object!");
            return "ErrorInvalidRequest";
        }
        if (typeof request.length === 'number' && !(request.propertyIsEnumerable('length'))) {
            log("sendRequest() invoked without valid request object!");
            return "ErrorInvalidRequest";
        }
        /* DEBUG: retVal = true;*/
        try {
            retVal = webrtcPlugin.sendRequest(request);
        } catch (e) {
            log("sendRequest() threw an exception!");
            log(e);
            return "ErrorInvalidPlugin";
        }
        if (retVal === "ErrorOk") {
            log("sendRequest() called plug-in with successful return.");
        } else {
            log("sendRequest() called plug-in with return of " + retVal + "!");
        }
        return retVal;
    };

    /**
     * Indicates if VidyoClient library has been started,
     * meaning that a prior invocation of start() returned an
     * indication of success.
     *
     * @return {boolean} true if VidyoClient started, false otherwise.
     */
    var isStarted = function () {
        var retVal = false;
        if (!webrtcPlugin) {
            log("isStarted() invoked without start!");
            return retVal;
        }
        /* DEBUG: retVal = true;*/
        try {
            retVal = webrtcPlugin.isStarted();
        } catch (e) {
            log("isStarted() threw an exception!");
            log(e);
            return retVal;
        }
        log("isStarted() called plug-in.");
        return retVal;
    };

    /**
     * Indicates if VidyoClient plug-in object (as known to this
     * wrapper object) is valid, meaning that it should be safe to
     * invoke the wrapper general API.
     *
     * @return {boolean} true if plug-in object valid, false otherwise.
     */
    var isLoaded = function () {
        if (!webrtcPlugin) {
            log("isLoaded() invoked without start");
            return false;
        }

        try {
            webrtcPlugin.isStarted();
        } catch (e) {
            log("isLoaded() threw an exception!");
            return false;
        }

        return true;
    };

    // callback and/or event handling functions (only called/triggered by plug-in object)
    /** @private */ 
    var dispatchOutEvent = function (event) {
        if (outEventCallbackObject) {
            if (event && outEventCallbackMethods[event.type]) {
                if (typeof outEventCallbackMethods[event.type] === 'function') {
                    // if method is of function type, just invoke it with default this
                    outEventCallbackMethods[event.type].call(outEventCallbackObject||this, event);
                } else {
                    // otherwise, assume method is of string type, invoke it with object as this
                    outEventCallbackObject[outEventCallbackMethods[event.type]](event);
                }
                log("dispatchOutEvent() invoked specific out event callback method.");
            }
            else if (defaultOutEventCallbackMethod) {
                if (typeof defaultOutEventCallbackMethod === 'function') {
                    // if method is of function type, just invoke it with default this
                    defaultOutEventCallbackMethod.call(outEventCallbackObject||this, event);
                } else {
                    // otherwise, assume method is of string type, invoke it with object as this
                    outEventCallbackObject[defaultOutEventCallbackMethod](event);
                }
                log("dispatchOutEvent() invoked default out event callback method.");
            }
        }
    };

    // set private instance variables for created object,
    // to initial values potentially passed into this
    // factory function
    setConfig(config);

    // bind private functions as methods of created object
    that.setOutEventCallbackObject = setOutEventCallbackObject;
    that.setDefaultOutEventCallbackMethod = setDefaultOutEventCallbackMethod;
    that.setLogCallback = setLogCallback;
    that.setOutEventCallbackMethod = setOutEventCallbackMethod;
    that.setSessionManager = setSessionManager;
    that.start = start;
    that.stop = stop;
    that.sendEvent = sendEvent;
    that.sendRequest = sendRequest;
    that.isStarted = isStarted;
    that.isLoaded = isLoaded;
    that.dispatchOutEvent = dispatchOutEvent;

    // return object created by this factory function
    return that;
};

