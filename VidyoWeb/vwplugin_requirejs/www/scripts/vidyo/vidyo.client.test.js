/*! @file vidyo.client.test.js
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
  * @fileOverview This file tests the module(s) for the VidyoClient wrapper object.
  * @author Vidyo Inc.
  * @version 1.1.1
  */

define(["./vidyo.client-1.1.1", "./vidyo.client.messages-1.1.1", "./vidyo.client.private.messages-1.1.1"],
	function (vidyoClient, vidyoClientMessages, vidyoClientPrivateMessages) {
		return {
			'config': {},

			'client': {},

			'logCallback': function (message) {
			},

			'log': function (message) {
				if (this.logCallback) {
					this.logCallback(message);
				}
			},

			'testCreateMessage': function () {
				var message;

				if (!vidyoClientMessages || !vidyoClientMessages.message) {
					this.that.log("testCreateMessage(): No wrapper, or no message factory!");
					return false;
				}
				message = vidyoClientMessages.message("test type");
				if (!message) {
					this.that.log("testCreateMessage(): Message object not created!");
					return false;
				}
				if (message.type !== "test type") {
					this.that.log("testCreateMessage(): Type of message object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateMessage() completed.");*/
				return true;
			},

			'testCreateInEvent': function () {
				var inEvent;

				if (!vidyoClientMessages || !vidyoClientMessages.inEvent) {
					this.that.log("testCreateInEvent(): No wrapper, or no in event factory!");
					return false;
				}
				inEvent = vidyoClientMessages.inEvent("test type");
				if (!inEvent) {
					this.that.log("testCreateInEvent(): In event object not created!");
					return false;
				}
				if (inEvent.type !== "test type") {
					this.that.log("testCreateInEvent(): Type of in event object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateInEvent() completed.");*/
				return true;
			},

			'testCreateEvent': function () {
				var event;

				if (!vidyoClientMessages || !vidyoClientMessages.event) {
					this.that.log("testCreateEvent(): No wrapper, or no event factory!");
					return false;
				}
				event = vidyoClientMessages.event("test type");
				if (!event) {
					this.that.log("testCreateEvent(): Event object not created!");
					return false;
				}
				if (event.type !== "test type") {
					this.that.log("testCreateEvent(): Type of event object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateEvent() completed.");*/
				return true;
			},

			'testCreateRequest': function () {
				var request;

				if (!vidyoClientMessages || !vidyoClientMessages.request) {
					this.that.log("testCreateRequest(): No wrapper, or no request factory!");
					return false;
				}
				request = vidyoClientMessages.request("test type");
				if (!request) {
					this.that.log("testCreateRequest(): Request object not created!");
					return false;
				}
				if (request.type !== "test type") {
					this.that.log("testCreateRequest(): Type of request object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateRequest() completed.");*/
				return true;
			},

			'testCreateInEventSignIn': function () {
				var inEventSignIn;

				if (!vidyoClientMessages || !vidyoClientMessages.inEventSignIn) {
					this.that.log("testCreateInEventSignIn(): No wrapper, or no factory!");
					return false;
				}
				inEventSignIn = vidyoClientMessages.inEventSignIn({});
				if (!inEventSignIn) {
					this.that.log("testCreateInEventSignIn(): Object not created!");
					return false;
				}
				if (inEventSignIn.type !== "InEventSignIn") {
					this.that.log("testCreateInEventSignIn(): Type of object not correct!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateInEventSignIn() completed.");*/
				return true;
			},

			'testOutEventUserMessageType': function () {
				if (!vidyoClientMessages || !vidyoClientMessages.outEventUserMessageType) {
					this.that.log("testOutEventUserMessageType(): No wrapper, or no function!");
					return false;
				}
				if (vidyoClientMessages.outEventUserMessageType() !== "OutEventUserMessage") {
					this.that.log("testOutEventUserMessageType(): Type returned not correct!");
					return false;
				}
				/* DEBUG: this.that.log("testOutEventUserMessageType() completed.");*/
				return true;
			},

			'testCreateRequestGetVolumeAudioOut': function () {
				var requestGetVolumeAudioOut;

				if (!vidyoClientMessages || !vidyoClientMessages.inEventSignIn) {
					this.that.log("testCreateRequestGetVolumeAudioOut(): No wrapper, or no factory!");
					return false;
				}
				requestGetVolumeAudioOut = vidyoClientMessages.requestGetVolumeAudioOut({});
				if (!requestGetVolumeAudioOut) {
					this.that.log("testCreateRequestGetVolumeAudioOut(): Object not created!");
					return false;
				}
				if (requestGetVolumeAudioOut.type !== "RequestGetVolumeAudioOut") {
					this.that.log("testCreateRequestGetVolumeAudioOut(): Type of object not correct!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateRequestGetVolumeAudioOut() completed.");*/
				return true;
			},

			'testCreatePrivateMessage': function () {
				var message;

				if (!vidyoClientPrivateMessages || !vidyoClientPrivateMessages.privateMessage) {
					this.that.log("testCreatePrivateMessage(): No wrapper, or no message factory!");
					return false;
				}
				message = vidyoClientPrivateMessages.privateMessage("test type");
				if (!message) {
					this.that.log("testCreatePrivateMessage(): Message object not created!");
					return false;
				}
				if (message.type !== "test type") {
					this.that.log("testCreatePrivateMessage(): Type of message object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreatePrivateMessage() completed.");*/
				return true;
			},

			'testCreatePrivateInEvent': function () {
				var inEvent;

				if (!vidyoClientPrivateMessages || !vidyoClientPrivateMessages.privateInEvent) {
					this.that.log("testCreatePrivateInEvent(): No wrapper, or no in event factory!");
					return false;
				}
				inEvent = vidyoClientPrivateMessages.privateInEvent("test type");
				if (!inEvent) {
					this.that.log("testCreatePrivateInEvent(): In event object not created!");
					return false;
				}
				if (inEvent.type !== "test type") {
					this.that.log("testCreatePrivateInEvent(): Type of in event object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreatePrivateInEvent() completed.");*/
				return true;
			},

			'testCreatePrivateEvent': function () {
				var event;

				if (!vidyoClientPrivateMessages || !vidyoClientPrivateMessages.privateEvent) {
					this.that.log("testCreatePrivateEvent(): No wrapper, or no event factory!");
					return false;
				}
				event = vidyoClientPrivateMessages.privateEvent("test type");
				if (!event) {
					this.that.log("testCreatePrivateEvent(): Event object not created!");
					return false;
				}
				if (event.type !== "test type") {
					this.that.log("testCreatePrivateEvent(): Type of event object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreatePrivateEvent() completed.");*/
				return true;
			},

			'testCreatePrivateRequest': function () {
				var request;

				if (!vidyoClientPrivateMessages || !vidyoClientPrivateMessages.privateRequest) {
					this.that.log("testCreatePrivateRequest(): No wrapper, or no request factory!");
					return false;
				}
				request = vidyoClientPrivateMessages.privateRequest("test type");
				if (!request) {
					this.that.log("testCreatePrivateRequest(): Request object not created!");
					return false;
				}
				if (request.type !== "test type") {
					this.that.log("testCreatePrivateRequest(): Type of request object not what created!");
					return false;
				}
				/* DEBUG: this.that.log("testCreatePrivateRequest() completed.");*/
				return true;
			},

			'testCreatePrivateInEventStartMyMeeting': function () {
				var inEventStartMyMeeting;

				if (!vidyoClientPrivateMessages || !vidyoClientPrivateMessages.privateInEventStartMyMeeting) {
					this.that.log("testCreatePrivateInEventStartMyMeeting(): No wrapper, or no factory!");
					return false;
				}
				inEventStartMyMeeting = vidyoClientPrivateMessages.privateInEventStartMyMeeting({});
				if (!inEventStartMyMeeting) {
					this.that.log("testCreatePrivateInEventStartMyMeeting(): Object not created!");
					return false;
				}
				if (inEventStartMyMeeting.type !== "PrivateInEventStartMyMeeting") {
					this.that.log("testCreatePrivateInEventStartMyMeeting(): Type of object not correct!");
					return false;
				}
				/* DEBUG: this.that.log("testCreatePrivateInEventStartMyMeeting() completed.");*/
				return true;
			},

			'createClientHelper': function (config) {
				if (!vidyoClient) {
					this.log("createClientHelper(): No wrapper factory!");
					return false;
				}
				this.client = vidyoClient(config);
				if (!this.client) {
					this.log("createClientHelper(): Wrapper object not created!");
					return false;
				}
				return true;
			},

			'testCreateClientNoConfig': function () {
				if (!this.that.createClientHelper()) {
					this.that.log("testCreateClientNoConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientNoConfig() completed.");*/
				return true;
			},

			'testCreateClientNullConfig': function () {
				var config = null;

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientNullConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientNullConfig() completed.");*/
				return true;
			},

			'testCreateClientEmptyStringConfig': function () {
				var config = "";

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientEmptyStringConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientEmptyStringConfig() completed.");*/
				return true;
			},

			'testCreateClientStringConfig': function () {
				var config = "test value";

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientStringConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientStringConfig() completed.");*/
				return true;
			},

			'testCreateClientEmptyArrayConfig': function () {
				var config = [];

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientEmptyArrayConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientEmptyArrayConfig() completed.");*/
				return true;
			},

			'testCreateClientArrayConfig': function () {
				var config = [0, 1, 2];

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientArrayConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientArrayConfig() completed.");*/
				return true;
			},

			'testCreateClientEmptyObjectConfig': function () {
				var config = {};

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientEmptyObjectConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientEmptyObjectConfig() completed.");*/
				return true;
			},

			'testCreateClientObjectNoneConfig': function () {
				var config = {'key': "value"};

				if (!this.that.createClientHelper(config)) {
					this.that.log("testCreateClientObjectNoneConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientObjectNoneConfig() completed.");*/
				return true;
			},

			'testCreateClientObjectAllConfig': function () {
				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testCreateClientObjectAllConfig(): createClientHelper() failed!");
					return false;
				}
				/* DEBUG: this.that.log("testCreateClientObjectAllConfig() completed.");*/
				return true;
			},

			'testSetPlugin': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(this.that.config.plugin);
				/* DEBUG: this.that.log("testSetPlugin() completed.");*/
				return true;
			},

			'testSetOutEventCallbackObject': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetOutEventCallbackObject(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setOutEventCallbackObject(this.that.config.outEventCallbackObject);
				/* DEBUG: this.that.log("testSetOutEventCallbackObject() completed.");*/
				return true;
			},

			'testSetDefaultOutEventCallbackMethod': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetDefaultOutEventCallbackMethod(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setDefaultOutEventCallbackMethod(this.that.config.defaultOutEventCallbackMethod);
				/* DEBUG: this.that.log("testSetDefaultOutEventCallbackMethod() completed.");*/
				return true;
			},

			'testSetLogCallback': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetLogCallback(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setLogCallback(this.that.config.logCallback);
				/* DEBUG: this.that.log("testSetLogCallback() completed.");*/
				return true;
			},

			'testSetUseCallbackWithPlugin': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetUseCallbackWithPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setUseCallbackWithPlugin(this.that.config.useCallbackWithPlugin);
				/* DEBUG: this.that.log("testSetUseCallbackWithPlugin() completed.");*/
				return true;
			},

			'testSetOutEventCallbackMethod': function () {
				if (!this.that.createClientHelper({})) {
					this.that.log("testSetOutEventCallbackMethod(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setOutEventCallbackMethod("TestType", "outEventCallback");
				/* DEBUG: this.that.log("testSetOutEventCallbackMethod() completed.");*/
				return true;
			},

			'createClientAndNoPluginHelper': function (config) {
				if (!this.createClientHelper(config)) {
					this.log("createClientAndNoPluginHelper(): Wrapper object not created!");
					return false;
				}
				this.client.setPlugin(null);
				return true;
			},

			'testStartNoPlugin': function () {
				if (!this.that.createClientAndNoPluginHelper(this.that.config)) {
					this.that.log("testStartNoPlugin(): createClientAndNoPluginHelper() failed!");
					return false;
				}
				if (this.that.client.start({})) {
					this.that.log("testStartNoPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartNoPlugin() completed.");*/
				return true;
			},

			'testIsStartedNoPlugin': function () {
				if (!this.that.createClientAndNoPluginHelper(this.that.config)) {
					this.that.log("testIsStartedNoPlugin(): createClientAndNoPluginHelper() failed!");
					return false;
				}
				if (this.that.client.isStarted()) {
					this.that.log("testIsStartedNoPlugin(): Wrapper is started!");
					return false;
				}
				/* DEBUG: this.that.log("testIsStartedNoPlugin() completed.");*/
				return true;
			},

			'testSendEventNoPlugin': function () {
				var event = {'type': "InEventLeave"};

				if (!this.that.createClientAndNoPluginHelper(this.that.config)) {
					this.that.log("testSendEventNoPlugin(): createClientAndNoPluginHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventNoPlugin(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventNoPlugin() completed.");*/
				return true;
			},

			'testSendRequestNoPlugin': function () {
				var request = {'type': "RequestGetConfiguration"};

				if (!this.that.createClientAndNoPluginHelper(this.that.config)) {
					this.that.log("testSendRequestNoPlugin(): createClientAndNoPluginHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) !== "ErrorNoPlugin") {
					this.that.log("testSendRequestNoPlugin(): Wrapper did not detect no plug-in!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestNoPlugin() completed.");*/
				return true;
			},

			'testStopNoPlugin': function () {
				if (!this.that.createClientAndNoPluginHelper(this.that.config)) {
					this.that.log("testStopNoPlugin(): createClientAndNoPluginHelper() failed!");
					return false;
				}
				if (this.that.client.stop()) {
					this.that.log("testStopNoPlugin(): Wrapper stopped!");
					return false;
				}
				/* DEBUG: this.that.log("testStopNoPlugin() completed.");*/
				return true;
			},

			'testStartEmptyStringPlugin': function () {
				var plugin = "";

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartEmptyStringPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartEmptyStringPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartEmptyStringPlugin() completed.");*/
				return true;
			},

			'testStartStringPlugin': function () {
				var plugin = "test value";

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartStringPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartStringPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartStringPlugin() completed.");*/
				return true;
			},

			'testStartEmptyArrayPlugin': function () {
				var plugin = [];

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartEmptyArrayPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartEmptyArrayPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartEmptyArrayPlugin() completed.");*/
				return true;
			},

			'testStartArrayPlugin': function () {
				var plugin = [0, 1, 2];

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartArrayPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartArrayPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartArrayPlugin() completed.");*/
				return true;
			},

			'testStartEmptyObjectPlugin': function () {
				var plugin = {};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartEmptyObjectPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartEmptyObjectPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartEmptyObjectPlugin() completed.");*/
				return true;
			},

			'testStartObjectNoStartPlugin': function () {
				var plugin = {'method': function () {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartObjectNoStartPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartObjectNoStartPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartObjectNoStartPlugin() completed.");*/
				return true;
			},

			'testStartObjectBadStartPlugin': function () {
				var plugin = {'start': {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartObjectBadStartPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.start({})) {
					this.that.log("testStartObjectBadStartPlugin(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartObjectBadStartPlugin() completed.");*/
				return true;
			},

			'testIsStartedNoIsStartedPlugin': function () {
				var plugin = {'method': function () {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testIsStartedNoIsStartedPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.isStarted()) {
					this.that.log("testIsStartedNoIsStartedPlugin(): Wrapper is started!");
					return false;
				}
				/* DEBUG: this.that.log("testIsStartedNoIsStartedPlugin() completed.");*/
				return true;
			},

			'testIsStartedBadIsStartedPlugin': function () {
				var plugin = {'isStarted': {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testIsStartedBadIsStartedPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.isStarted()) {
					this.that.log("testIsStartedBadIsStartedPlugin(): Wrapper is started!");
					return false;
				}
				/* DEBUG: this.that.log("testIsStartedBadIsStartedPlugin() completed.");*/
				return true;
			},

			'testSendEventNoSendEventPlugin': function () {
				var plugin = {'method': function () {}};
				var event = {'type': "InEventLeave"};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testSendEventNoSendEventPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventNoSendEventPlugin(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventNoSendEventPlugin() completed.");*/
				return true;
			},

			'testSendEventBadSendEventPlugin': function () {
				var plugin = {'sendEvent': {}};
				var event = {'type': "InEventLeave"};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testSendEventBadSendEventPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventBadSendEventPlugin(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventBadSendEventPlugin() completed.");*/
				return true;
			},

			'testSendRequestNoSendRequestPlugin': function () {
				var plugin = {'method': function () {}};
				var request = {'type': "RequestGetConfiguration"};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testSendRequestNoSendRequestPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.sendRequest(request) !== "ErrorInvalidPlugin") {
					this.that.log("testSendRequestNoSendRequestPlugin(): Wrapper did not detect invalid plug-in!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestNoSendRequestPlugin() completed.");*/
				return true;
			},

			'testSendRequestBadSendRequestPlugin': function () {
				var plugin = {'sendRequest': {}};
				var request = {'type': "RequestGetConfiguration"};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testSendRequestBadSendRequestPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.sendRequest(request) !== "ErrorInvalidPlugin") {
					this.that.log("testSendRequestBadSendRequestPlugin(): Wrapper did not detect invalid plug-in!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestBadSendRequestPlugin() completed.");*/
				return true;
			},

			'testStopNoStopPlugin': function () {
				var plugin = {'method': function () {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStopNoStopPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.stop()) {
					this.that.log("testStopNoStopPlugin(): Wrapper stopped!");
					return false;
				}
				/* DEBUG: this.that.log("testStopNoStopPlugin() completed.");*/
				return true;
			},

			'testStopBadStopPlugin': function () {
				var plugin = {'stop': {}};

				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStopBadStopPlugin(): createClientHelper() failed!");
					return false;
				}
				this.that.client.setPlugin(plugin);
				if (this.that.client.stop()) {
					this.that.log("testStopBadStopPlugin(): Wrapper stopped!");
					return false;
				}
				/* DEBUG: this.that.log("testStopBadStopPlugin() completed.");*/
				return true;
			},

			'createClientAndStopHelper': function (config) {
				if (!this.createClientHelper(config)) {
					this.log("createClientAndStopHelper(): Wrapper object not created!");
					return false;
				}
				this.client.stop();
				return true;
			},

			'testIsStartedNoStart': function () {
				if (!this.that.createClientAndStopHelper(this.that.config)) {
					this.that.log("testIsStartedNoStart(): createClientAndStopHelper() failed!");
					return false;
				}
				if (this.that.client.isStarted()) {
					this.that.log("testIsStartedNoStart(): Wrapper started!");
					return false;
				}
				/* DEBUG: this.that.log("testIsStartedNoStart() completed.");*/
				return true;
			},

			'testSendEventNoStart': function () {
				var event = {'type': "InEventLeave"};

				if (!this.that.createClientAndStopHelper(this.that.config)) {
					this.that.log("testSendEventNoStart(): createClientAndStopHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventNoStart(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventNoStart() completed.");*/
				return true;
			},

			'testSendRequestNoStart': function () {
				var request = {'type': "RequestGetConfiguration"};

				if (!this.that.createClientAndStopHelper(this.that.config)) {
					this.that.log("testSendRequestNoStart(): createClientAndStopHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestNoStart(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestNoStart() completed.");*/
				return true;
			},

			'testStopNoStart': function () {
				if (!this.that.createClientAndStopHelper(this.that.config)) {
					this.that.log("testStopNoStart(): createClientAndStopHelper() failed!");
					return false;
				}
				if (!this.that.client.stop()) {
					this.that.log("testStopNoStart(): Wrapper not stopped!");
					return false;
				}
				/* DEBUG: this.that.log("testStopNoStart() completed.");*/
				return true;
			},

			'testStartNoConfig': function () {
				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartNoConfig(): createClientHelper() failed!");
					return false;
				}
				if (!this.that.client.start()) {
					this.that.log("testStartNoConfig(): Wrapper not started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartNoConfig() completed.");*/
				return true;
			},

			'testStartNullConfig': function () {
				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartNullConfig(): createClientHelper() failed!");
					return false;
				}
				if (!this.that.client.start(null)) {
					this.that.log("testStartNullConfig(): Wrapper not started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartNullConfig() completed.");*/
				return true;
			},

			'testStartObjectAllConfig': function () {
				if (!this.that.createClientHelper(this.that.config)) {
					this.that.log("testStartObjectAllConfig(): createClientHelper() failed!");
					return false;
				}
				if (!this.that.client.start(this.that.config)) {
					this.that.log("testStartObjectAllConfig(): Wrapper not started!");
					return false;
				}
				/* DEBUG: this.that.log("testStartObjectAllConfig() completed.");*/
				return true;
			},

			'createClientAndStartHelper': function (config) {
				if (!this.createClientHelper(config)) {
					this.log("createClientAndStartHelper(): Wrapper object not created!");
					return false;
				}
				if (!this.client.start(config)) {
					this.log("createClientAndStartHelper(): Wrapper not started!");
					return false;
				}
				return true;
			},

			'testIsStartedPlugin': function () {
				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testIsStartedPlugin(): createClientAndStartHelper() failed!");
					return false;
				}
				if (!this.that.client.isStarted()) {
					this.that.log("testIsStartedPlugin(): Wrapper not started!");
					return false;
				}
				/* DEBUG: this.that.log("testIsStartedPlugin() completed.");*/
				return true;
			},

			'testSendEventNoEvent': function () {
				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventNoEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent()) {
					this.that.log("testSendEventNoEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventNoEvent() completed.");*/
				return true;
			},

			'testSendEventNullEvent': function () {
				var event = null;

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventNullEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventNullEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventNullEvent() completed.");*/
				return true;
			},

			'testSendEventEmptyStringEvent': function () {
				var event = "";

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventEmptyStringEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventEmptyStringEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventEmptyStringEvent() completed.");*/
				return true;
			},

			'testSendEventStringEvent': function () {
				var event = "test value";

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventStringEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventStringEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventStringEvent() completed.");*/
				return true;
			},

			'testSendEventEmptyArrayEvent': function () {
				var event = [];

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventEmptyArrayEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventEmptyArrayEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventEmptyArrayEvent() completed.");*/
				return true;
			},

			'testSendEventArrayEvent': function () {
				var event = [0, 1, 2];

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventArrayEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventArrayEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventArrayEvent() completed.");*/
				return true;
			},

			'testSendEventEmptyObjectEvent': function () {
				var event = {};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventEmptyObjectEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventEmptyObjectEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventEmptyObjectEvent() completed.");*/
				return true;
			},

			'testSendEventObjectNoTypeEvent': function () {
				var event = {'key': "value"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventObjectNoTypeEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventObjectNoTypeEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventObjectNoTypeEvent() completed.");*/
				return true;
			},

			'testSendEventObjectBadTypeEvent': function () {
				var event = {'type': "value"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventObjectBadTypeEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendEvent(event)) {
					this.that.log("testSendEventObjectBadTypeEvent(): Wrapper sent event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventObjectBadTypeEvent() completed.");*/
				return true;
			},

			'testSendEventObjectGoodTypeEvent': function () {
				var event = {'type': "InEventLeave"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendEventObjectGoodTypeEvent(): createClientAndStartHelper() failed!");
					return false;
				}
				if (!this.that.client.sendEvent(event)) {
					this.that.log("testSendEventObjectGoodTypeEvent(): Wrapper did not send event!");
					return false;
				}
				/* DEBUG: this.that.log("testSendEventObjectGoodTypeEvent() completed.");*/
				return true;
			},

			'testSendRequestNoRequest': function () {
				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestNoRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest() === "ErrorOk") {
					this.that.log("testSendRequestNoRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestNoRequest() completed.");*/
				return true;
			},

			'testSendRequestNullRequest': function () {
				var request = null;

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestNullRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestNullRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestNullRequest() completed.");*/
				return true;
			},

			'testSendRequestEmptyStringRequest': function () {
				var request = "";

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestEmptyStringRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestEmptyStringRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestEmptyStringRequest() completed.");*/
				return true;
			},

			'testSendRequestStringRequest': function () {
				var request = "test value";

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestStringRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestStringRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestStringRequest() completed.");*/
				return true;
			},

			'testSendRequestEmptyArrayRequest': function () {
				var request = [];

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestEmptyArrayRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestEmptyArrayRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestEmptyArrayRequest() completed.");*/
				return true;
			},

			'testSendRequestArrayRequest': function () {
				var request = [0, 1, 2];

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestArrayRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestArrayRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestArrayRequest() completed.");*/
				return true;
			},

			'testSendRequestEmptyObjectRequest': function () {
				var request = {};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestEmptyObjectRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestEmptyObjectRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestEmptyObjectRequest() completed.");*/
				return true;
			},

			'testSendRequestObjectNoTypeRequest': function () {
				var request = {'key': "value"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestObjectNoTypeRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestObjectNoTypeRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestObjectNoTypeRequest() completed.");*/
				return true;
			},

			'testSendRequestObjectBadTypeRequest': function () {
				var request = {'type': "value"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestObjectBadTypeRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) === "ErrorOk") {
					this.that.log("testSendRequestObjectBadTypeRequest(): Wrapper sent request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestObjectBadTypeRequest() completed.");*/
				return true;
			},

			'testSendRequestObjectGoodTypeRequest': function () {
				var request = {'type': "RequestGetConfiguration"};

				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testSendRequestObjectGoodTypeRequest(): createClientAndStartHelper() failed!");
					return false;
				}
				if (this.that.client.sendRequest(request) !== "ErrorOk") {
					this.that.log("testSendRequestObjectGoodTypeRequest(): Wrapper did not send request!");
					return false;
				}
				/* DEBUG: this.that.log("testSendRequestObjectGoodTypeRequest() completed.");*/
				return true;
			},

			'testStopPlugin': function () {
				if (!this.that.createClientAndStartHelper(this.that.config)) {
					this.that.log("testStopPlugin(): createClientAndStartHelper() failed!");
					return false;
				}
				if (!this.that.client.stop()) {
					this.that.log("testStopPlugin(): Wrapper not stopped!");
					return false;
				}
				/* DEBUG: this.that.log("testStopPlugin() completed.");*/
				return true;
			},

			'testGetSupportedPluginMimeTypes': function () {
				var retval;

				if (!this.that.createClientHelper()) {
					this.that.log("testGetSupportedPluginMimeTypes(): createClientHelper() failed!");
					return false;
				}
				retval = this.that.client.getSupportedPluginMimeTypes();
				if (!retval
					|| typeof retval !== 'object'
					|| typeof retval.length !== 'number'
					|| (retval.propertyIsEnumerable('length'))) {
					this.that.log("testGetSupportedPluginMimeTypes(): return type not array!");
					return false;
				}
				/* DEBUG: this.that.log("testGetSupportedPluginMimeTypes() completed.");*/
				return true;
			},

			'testFunctions': [],

			'initTestFunctions': function () {
				/* 01 */ this.testFunctions.push(this.testCreateMessage);
				/* 02 */ this.testFunctions.push(this.testCreateInEvent);
				/* 03 */ this.testFunctions.push(this.testCreateEvent);
				/* 04 */ this.testFunctions.push(this.testCreateRequest);
				/* 05 */ this.testFunctions.push(this.testCreateInEventSignIn);
				/* 06 */ this.testFunctions.push(this.testOutEventUserMessageType);
				/* 07 */ this.testFunctions.push(this.testCreateRequestGetVolumeAudioOut);
				/* 08 */ this.testFunctions.push(this.testCreatePrivateMessage);
				/* 09 */ this.testFunctions.push(this.testCreatePrivateInEvent);
				/* 10 */ this.testFunctions.push(this.testCreatePrivateEvent);
				/* 11 */ this.testFunctions.push(this.testCreatePrivateRequest);
				/* 12 */ this.testFunctions.push(this.testCreatePrivateInEventStartMyMeeting);
				/* 13 */ this.testFunctions.push(this.testCreateClientNoConfig);
				/* 14 */ this.testFunctions.push(this.testCreateClientNullConfig);
				/* 15 */ this.testFunctions.push(this.testCreateClientEmptyStringConfig);
				/* 16 */ this.testFunctions.push(this.testCreateClientStringConfig);
				/* 17 */ this.testFunctions.push(this.testCreateClientEmptyArrayConfig);
				/* 18 */ this.testFunctions.push(this.testCreateClientArrayConfig);
				/* 19 */ this.testFunctions.push(this.testCreateClientEmptyObjectConfig);
				/* 20 */ this.testFunctions.push(this.testCreateClientObjectNoneConfig);
				/* 21 */ this.testFunctions.push(this.testCreateClientObjectAllConfig);
				/* 22 */ this.testFunctions.push(this.testSetPlugin);
				/* 23 */ this.testFunctions.push(this.testSetOutEventCallbackObject);
				/* 24 */ this.testFunctions.push(this.testSetDefaultOutEventCallbackMethod);
				/* 25 */ this.testFunctions.push(this.testSetLogCallback);
				/* 26 */ this.testFunctions.push(this.testSetUseCallbackWithPlugin);
				/* 27 */ this.testFunctions.push(this.testSetOutEventCallbackMethod);
				/* 28 */ this.testFunctions.push(this.testStartNoPlugin);
				/* 29 */ this.testFunctions.push(this.testIsStartedNoPlugin);
				/* 30 */ this.testFunctions.push(this.testSendEventNoPlugin);
				/* 31 */ this.testFunctions.push(this.testSendRequestNoPlugin);
				/* 32 */ this.testFunctions.push(this.testStopNoPlugin);
				/* 33 */ this.testFunctions.push(this.testStartEmptyStringPlugin);
				/* 34 */ this.testFunctions.push(this.testStartStringPlugin);
				/* 35 */ this.testFunctions.push(this.testStartEmptyArrayPlugin);
				/* 36 */ this.testFunctions.push(this.testStartArrayPlugin);
				/* 37 */ this.testFunctions.push(this.testStartEmptyObjectPlugin);
				/* 38 */ this.testFunctions.push(this.testStartObjectNoStartPlugin);
				/* 39 */ this.testFunctions.push(this.testStartObjectBadStartPlugin);
				/* 40 */ this.testFunctions.push(this.testIsStartedNoIsStartedPlugin);
				/* 41 */ this.testFunctions.push(this.testIsStartedBadIsStartedPlugin);
				/* 42 */ this.testFunctions.push(this.testSendEventNoSendEventPlugin);
				/* 43 */ this.testFunctions.push(this.testSendEventBadSendEventPlugin);
				/* 44 */ this.testFunctions.push(this.testSendRequestNoSendRequestPlugin);
				/* 45 */ this.testFunctions.push(this.testSendRequestBadSendRequestPlugin);
				/* 46 */ this.testFunctions.push(this.testStopNoStopPlugin);
				/* 47 */ this.testFunctions.push(this.testStopBadStopPlugin);
				/* 48 */ this.testFunctions.push(this.testIsStartedNoStart);
				/* 49 */ this.testFunctions.push(this.testSendEventNoStart);
				/* 50 */ this.testFunctions.push(this.testSendRequestNoStart);
				/* 51 */ this.testFunctions.push(this.testStopNoStart);
				/* 52 */ this.testFunctions.push(this.testStartNoConfig);
				/* 53 */ this.testFunctions.push(this.testStartNullConfig);
				/* 54 */ this.testFunctions.push(this.testStartObjectAllConfig);
				/* 55 */ this.testFunctions.push(this.testIsStartedPlugin);
				/* 56 */ this.testFunctions.push(this.testSendEventNoEvent);
				/* 57 */ this.testFunctions.push(this.testSendEventNullEvent);
				/* 58 */ this.testFunctions.push(this.testSendEventEmptyStringEvent);
				/* 59 */ this.testFunctions.push(this.testSendEventStringEvent);
				/* 60 */ this.testFunctions.push(this.testSendEventEmptyArrayEvent);
				/* 61 */ this.testFunctions.push(this.testSendEventArrayEvent);
				/* 62 */ this.testFunctions.push(this.testSendEventEmptyObjectEvent);
				/* 63 */ this.testFunctions.push(this.testSendEventObjectNoTypeEvent);
				/* 64 */ this.testFunctions.push(this.testSendEventObjectBadTypeEvent);
				/* 65 */ this.testFunctions.push(this.testSendEventObjectGoodTypeEvent);
				/* 66 */ this.testFunctions.push(this.testSendRequestNoRequest);
				/* 67 */ this.testFunctions.push(this.testSendRequestNullRequest);
				/* 68 */ this.testFunctions.push(this.testSendRequestEmptyStringRequest);
				/* 69 */ this.testFunctions.push(this.testSendRequestStringRequest);
				/* 70 */ this.testFunctions.push(this.testSendRequestEmptyArrayRequest);
				/* 71 */ this.testFunctions.push(this.testSendRequestArrayRequest);
				/* 72 */ this.testFunctions.push(this.testSendRequestEmptyObjectRequest);
				/* 73 */ this.testFunctions.push(this.testSendRequestObjectNoTypeRequest);
				/* 74 */ this.testFunctions.push(this.testSendRequestObjectBadTypeRequest);
				/* 75 */ this.testFunctions.push(this.testSendRequestObjectGoodTypeRequest);
				/* 76 */ this.testFunctions.push(this.testStopPlugin);
				/* 77 */ this.testFunctions.push(this.testGetSupportedPluginMimeTypes);
				this.testFunctions['that'] = this;
			},

			'outEventCallback': function (event) {
				/* DEBUG:
				event = event || {};
				var msg = "Received out event callback " + event.type;
				//alert(msg);
				this.log(msg);
				*/
			},

			'runTests': function (log, plugin) {
				var i, j;
				var result;
				var success = 0;

				this.logCallback = log;
				this.config.plugin = plugin;
				this.config.outEventCallbackObject = this;
				this.config.defaultOutEventCallbackMethod = "outEventCallback";
				/* DEBUG: this.config.logCallback = log; */
				this.config.useCallbackWithPlugin = true;
				this.initTestFunctions();
				for (i = 0; i < /**/this.testFunctions.length/**//*20*/; i++) {
					result = this.testFunctions[i]();
					if (!result) {
						j = i + 1;
						log("Test " + j + " failed!");
					}
					else {
						success += 1;
					}
				}
				log("All tests completed, " + success + "/" + this.testFunctions.length + " passed.");
			}
		}
	}
);
