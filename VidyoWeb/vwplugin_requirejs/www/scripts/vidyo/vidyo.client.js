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
  * @fileOverview This file defines the module for the VidyoClient wrapper object.
  * @author Vidyo Inc.
  * @version 1.1.1
  */

define(["./vidyo.client.messages"],
	function (vidyoClientMessages) {
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
			/** @private */ var plugin = null;
			/** @private */ var outEventCallbackObject = null;
			/** @private */ var defaultOutEventCallbackMethod = "";
			/** @private */ var logCallback = null;
			/** @private */ var useCallbackWithPlugin = true;

			// other private instance variables for created object
			/** @private */ var outEventCallbackMethods = {};

			// private helper functions
			/** @private */ var setConfig = function (config) {
				if (config && config.plugin !== undefined) {
					plugin = config.plugin;
				}
				if (config && config.outEventCallbackObject !== undefined) {
					outEventCallbackObject = config.outEventCallbackObject;
				}
				if (config && config.defaultOutEventCallbackMethod !== undefined) {
					defaultOutEventCallbackMethod = config.defaultOutEventCallbackMethod;
				}
				if (config && config.logCallback !== undefined) {
					logCallback = config.logCallback;
				}
				if (config && config.useCallbackWithPlugin !== undefined) {
					useCallbackWithPlugin = config.useCallbackWithPlugin;
				}
			};
			/** @private */ var log = function (message) {
				if (logCallback) {
					logCallback(message);
				}
			};

			/****************************************
			 * API accessor (getter/setter) functions
			 ****************************************/

			/**
			  * Returns list of MIME types for VidyoClient plug-in
			  * objects supported by the invoked VidyoClient wrapper
			  * object.
			  *
			  * @return {String[]} array of strings listing supported MIME types.
			  */
			var getSupportedPluginMimeTypes = function () {
				var retVal = [
					"application/x-vidyoweb-1.1.1.00075",
					"application/x-vidyoweb-1.1.1.99999"
				];
				return retVal;
			};

			/**
			  * Sets the VidyoClient plug-in object that will be used by
			  * the invoked VidyoClient wrapper object.
			  *
			  * @param {Object} pluginArg Reference to VidyoClient plug-in object.
			  * @return {Object} Reference to invoked VidyoClient wrapper object.
			  */
			var setPlugin = function (pluginArg) {
				plugin = pluginArg;
			};

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
			  * Sets whether the invoked VidyoClient wrapper object will use a
			  * callback for receiving out events from the VidyoClient plug-in
			  * object.  Default behavior is to use a callback.  Not using a
			  * callback will allow proper operation in IE on Windows platform,
			  * if VidyoClient plug-in object is instantiated with an object
			  * HTML tag created programmatically.
			  *
			  * @param {boolean} useCallbackWithPluginArg true if using callback,
			  *                                           false otherwise.
			  * @return {Object} Reference to invoked VidyoClient wrapper object.
			  */
			var setUseCallbackWithPlugin = function (useCallbackWithPluginArg) {
				useCallbackWithPlugin = useCallbackWithPluginArg;
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
				var retVal = false;
				setConfig(config);
				if (!plugin) {
					log("start() invoked without plugin!");
					return retVal;
				}
				/* DEBUG: retVal = true;*/
				try {
					if (useCallbackWithPlugin) {
						plugin.useCallbackForOutEvents = true;
						plugin.outEventCallbackObject = that;
						plugin.outEventCallbackMethod = "dispatchOutEvent";
					} else {
						plugin.useCallbackForOutEvents = false;
						if (plugin.attachEvent) {
							log("start() will call plugin.attachEvent()");
							plugin.attachEvent("onouteventcallback", dispatchOutEvent);
						} else if (plugin.addEventListener) {
							log("start() will call plugin.addEventListener()");
							plugin.addEventListener("outeventcallback", dispatchOutEvent, false);
						}
					}
					retVal = plugin.start();
				} catch (e) {
					log("plugin.start() threw an exception!");
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
				if (!plugin) {
					log("stop() invoked without plugin!");
					return retVal;
				}
				/* DEBUG: retVal = true;*/
				try {
					retVal = plugin.stop();
				} catch (e) {
					log("plugin.stop() threw an exception!");
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
				if (!plugin) {
					log("sendEvent() invoked without plugin!");
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
					retVal = plugin.sendEvent(event);
				} catch (e) {
					log("plugin.sendEvent() threw an exception!");
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
			  *                   "ErrorNoPlugin" if invoked without plugin<br/>
			  *                   "ErrorInvalidRequest" if request object not valid<br/>
			  *                   "ErrorRequestNoType" if no type property in request object<br/>
			  *                   "ErrorRequestTypeInvalid" if value of type property not known<br/>
			  *                   "ErrorRequestFailed" if VidyoClient returns failure for request<br/>
			  */
			var sendRequest = function (request) {
				var retVal = "Error";
				if (!plugin) {
					log("sendRequest() invoked without plugin!");
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
					retVal = plugin.sendRequest(request);
				} catch (e) {
					log("plugin.sendRequest() threw an exception!");
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
				if (!plugin) {
					log("isStarted() invoked without plugin!");
					return retVal;
				}
				/* DEBUG: retVal = true;*/
				try {
					retVal = plugin.isStarted();
				} catch (e) {
					log("plugin.isStarted() threw an exception!");
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
				if (!plugin) {
					log("isLoaded() invoked without plugin!");
					return false;
				}

				try {
					plugin.isStarted();
				} catch (e) {
					log("plugin.isLoaded() threw an exception!");
					return false;
				}

				return true;
			};

			// callback and/or event handling functions (only called/triggered by plug-in object)
			/** @private */ var dispatchOutEvent = function (event) {
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
			that.getSupportedPluginMimeTypes = getSupportedPluginMimeTypes;
			that.setPlugin = setPlugin;
			that.setOutEventCallbackObject = setOutEventCallbackObject;
			that.setDefaultOutEventCallbackMethod = setDefaultOutEventCallbackMethod;
			that.setLogCallback = setLogCallback;
			that.setUseCallbackWithPlugin = setUseCallbackWithPlugin;
			that.setOutEventCallbackMethod = setOutEventCallbackMethod;
			that.start = start;
			that.stop = stop;
			that.sendEvent = sendEvent;
			that.sendRequest = sendRequest;
			that.isStarted = isStarted;
			that.isLoaded = isLoaded;
			that.dispatchOutEvent = dispatchOutEvent;

			// return object created by this factory function
			return that;
		}

		return vidyoClient;
	}
);
