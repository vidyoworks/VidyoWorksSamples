/**
 * @fileOverview This is main VidyoWeb Sample API file.
 * @author Vidyo Inc.
 * @version 1.0.0
 */

/*jslint browser: true, indent : 4, nomen : true, vars: true, bitwise: true, maxerr : 100 */
/*global requirejs: false, console: false, bootstrap: false, handlebars: false, define: false, jquery: false, jQuery: false, handlebars: false, ActiveXObject: false */

(function () {
    'use strict';
    /* Configure non-requireJS libraries */
    requirejs.config({
        appDir: ".",
        baseUrl: "scripts",
        paths: {
            /* Load common libraries from CDN and fallback to local versions. */
            'jquery': ["//ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min", "libs/jquery.1.11.0.min"],
            'bootstrap': ['//netdna.bootstrapcdn.com/twitter-bootstrap/2.3.2/js/bootstrap.min', 'libs/bootstrap.min.2.3.2'],
            'handlebars': ['//cdnjs.cloudflare.com/ajax/libs/handlebars.js/1.3.0/handlebars.amd.min', 'libs/handlebars.amd.min.1.3.0'],
            'jquery.html5storage': ["libs/jquery.html5storage.min.1.0"],
            'jquery.typewatch': ["libs/jquery.typewatch.2.2"],
            'bootstrap.notify': ["libs/bootstrap-notify.1.0"],
            'domReady': ["libs/domReady.2.0.1"]
        },
        shim: {
            /* Set bootstrap dependencies (just jQuery) */
            'bootstrap': ['jquery'],
            /* Set storage lib dependencies */
            'jquery.html5storage': ['jquery'],
            'jquery.typewatch': ['jquery'],
            'bootstrap.notify': ["bootstrap"]
        },
        waitSeconds: 15
    });

    /* Handle RequireJS error */
    requirejs.onError = function (err) {
        console.warn("error", "applcation", "requirejs::onError - ", err);

        document.getElementById("splash").style.display = "none";
        document.getElementById("errorWrapper").className =
            document.getElementById("errorWrapper").className.replace(/\bhide\b/, '');
        document.getElementById("errorWrapper").innerHTML = "<h4>Something went wrong</h4><p>What happened: <code>" + err.requireType + "</code>.</p><p>What to try: <a href='#' onclick='location.reload();'>reload</a></p>";
        throw err;
    };

    require([
            "jquery",
            "utils/soap-proxy",
            "utils/logger",
            "domReady",
            "vidyo/vidyo.client",
            "vidyo/vidyo.client.messages",
            "vidyo/vidyo.client.private.messages",
            "main.config",
            "handlebars",
            "bootstrap",
            "jquery.html5storage",
            "jquery.typewatch",
            "bootstrap.notify"
        ],
        function (
            $,
            soapProxy,
            logger,
            domReady,
            vidyoClient,
            vidyoClientMessages,
            vidyoClientPrivateMessages,
            config,
            handlebars
        ) {

            /**
             * Main application module
             * @param  {Object} config Configuration (main.config)
             * @return {Object}        Application representation
             */
            var application = function (config) {
                /**
                 * Predefine functions for faster JS execution
                 */
                var applicationBuildCache, applicationBuildTemplates, applicationAddPlugin, applicationCallCleanup, applicationCheckForDeveloper, applicationBuildSubscribeEvents, applicationBindVidyoCallbacks, applicationBindSubscribeEvents, applicationBindUIEvents, applicationLoadCacheFromPersistentStore, applicationBindEvents, applicationClientInfoPrint, clientConferenceLeave, clientConferenceStateGet, clientConfigurationBootstrap, clientConfigurationGet, clientConfigurationSet, clientCurrentUserGet, clientEndpointIDGet, clientGroupChatSend, clientGuestLoginAndJoin, clientIncomingCallAccept, clientIncomingCallReject, clientLayoutSet, clientLayoutToggle, clientLocalMediaInfo, clientLocalSharesGet, clientLocalShareStart, clientLocalShareStop, clientLogLevelsAndCategoriesSet, clientMicrophoneMute, clientParticipantPin, clientParticipantsGet, clientParticipantsSetLimit, clientPreviewModeSet, clientPreviewModeToggle, clientPrivateChatSend, clientRecordAndWebcastStateGet, clientSessionGetInfo, clientSharesGet, clientSharesSetCurrent, clientSpeakerMute, clientUserLogin, clientUserLogout, clientVideoMute, helperConferenceUpdateTimerStart, helperConferenceUpdateTimerStop, helperPersistentStorageGetValue, helperPersistentStorageSetValue, helperPortalUsersStatusUpdateTimerStart, helperPortalUsersStatusUpdateTimerStop, helperRingtonePlay, helperRingtoneStop, helperSoapPromiseToGetMyAccount, helperSoapPromiseToSearch, helperSoapPromiseToSearchMyContacts, helperSoapPromiseToSendUserRequest, portalParticipantsPromiseToGet, portalRecordGetProfiles, portalRecordStart, portalRecordStop, portalRoomInfoPromiseToGet, portalRoomPromiseToLock, portalUserCallDirect, portalUserCancelSearchRequest, portalUserFavoritePromiseToAdd, portalUserFavoritePromiseToRemove, portalUserInviteToConference, portalUserJoinConference, portalUserSearchBothFavAndUsers, uiChatUpdateView, uiChatViewMinimize, uiChatViewScrollToPosition, uiChatViewTabCreateIfNotExists, uiChatViewTabNotifyStart, uiChatViewTabNotifyStop, uiChatViewTabSwitch, uiConfigurationUpdateWithData, uiDesktopNotification, uiDesktopNotificationRequestPermission, uiFullscreenCancel, uiFullscreenSet, uiGenericNotify, uiInCallShow, uiIncomingCallMissedCallNotify, uiIncomingCallNotificationDismiss, uiJoinConferencePinDialogShow, uiReportJoinConferencePinError, uiLocalShareReset, uiLocalSharesUpdateWithData, uiParticipantEnableInvite, uiParticipantsPromiseToSlide, uiParticipantStatusNotify, uiParticipantsUpdateWithData, uiPrecallMenuShow, uiPromiseToEndSplashScreen, uiCallCleanup ,uiPromiseToShowMenu, uiReportError, uiReportGuestLoginError, uiReportInfo, uiReportCloseEngage, uiReportInfoDismiss, uiReportUserLoginError, uiSearchProgressShow,
uiSetMicMuted, uiSetSpeakerMuted, uiSetVideoMuted, uiShareSelect, uiSharesUpdateWithData, uiShowInCallContainerMinimizedAndWithPlugin, uiStart, uiStartPluginDetection, uiUpdateGuestLoginProgress, uiUpdateJoinProgress, uiUpdateUserLoginProgress, uiUserFavoriteAdd, uiUserFavoriteRemove, uiUserNavigationUpdateWithData, uiVidyoPluginShow, uiVidyoPluginIsShown, vidyoPluginConfigurationPrepare, vidyoPluginInitAndStart, vidyoPluginIsLoaded, vidyoPluginIsInstalled, vidyoPluginIsStarted, vidyoPluginLoad, vidyoPluginStart, vidyoPluginStop;
                /**
                 * Application representation module
                 * @type {Object}
                 */
                var self = {};

                /**
                 * Application configuration
                 * @type {Object}
                 */
                self.config = config;

                /**
                 * Vidyo library specific configuration
                 * @type {Object}
                 */
                self.config.vidyoLib = {};
                /**
                 * Holds caches DOM
                 * @type {Object}
                 */
                self.cache = {};

                /**
                 * Holds cached events
                 * @type {Object}
                 */
                self.events = {};
                /**
                 * Data about user login parameters
                 * @type {Object}
                 */
                self.loginInfo = {};

                /**
                 * Data about guest login parameters
                 * @type {Object}
                 */
                self.guestLoginInfo = {};

                /**
                 * Map of handlebars templates
                 * @type {Object}
                 */
                self.templates = {};

                /**
                 * Guest login request sequencer
                 * @type {Number}
                 */
                self.currentRequestId = 1;

                /**
                 * Holds information about contacts and searches users
                 * @type {Object}
                 */
                self.users = {
                    favNum: "",
                    fav: [],
                    userNum: "",
                    user: []
                };
                /**
                 * Hold last users variable so we can revert in case
                 * when search is canceled
                 * @type {Object}
                 */
                self.lastUsers = self.users;

                /**
                 * Holds value for search refresh timer
                 * so we can cancel it later on.
                 * @type {[type]}
                 */
                self.searchUserRefreshTimer = undefined;

                /**
                 * True if current login process is for guest
                 * False if current login process is for user
                 * @type {Boolean}
                 */
                self.isGuestLogin = false;

                /**
                 * Current preview mode. On application start it will be propagated from
                 * persistent storage
                 * @type {String}
                 */
                self.currentPreviewMode = self.config.defaultPreviewMode;

                /**
                 * Current mute state of microphone
                 * @type {Boolean}
                 */
                self.isMutedMic = false;

                /**
                 * Current mute state of speaker
                 * @type {Boolean}
                 */
                self.isMutedSpeaker = false;

                /**
                 * Current mute state of video
                 * @type {Boolean}
                 */
                self.isMutedVideo = false;

                /**
                 * True if in fullscreen mode,
                 * False otherwise
                 * @type {Boolean}
                 */
                self.isFullscreen = false;

                self.numPreferred = 0;

                /**
                 * Holds current search SOAP request to the VidyoPortal
                 * in case we need to cancel it
                 * @type {Object}
                 */
                self.currentSearchRequest = undefined;

                /**
                 * Holds information about current user on a portal.
                 * Response to myAccount SOAP request to the portal.
                 * @type {Object}
                 */
                self.myAccount = undefined;

                /**
                 * Currently shared application id
                 * @type {String}
                 */
                self.currentShareId = undefined;

                /**
                 * Conference status
                 * @type {Boolean}
                 */
                self.inConference = false;

                /**
                 * Is in joining state
                 * @type {Boolean}
                 */
                 self.isJoining = false;

                /**
                 * Status of participant list show
                 * @type {Boolean}
                 */
                self.isShowingParticipantList = true;

                /**
                 * List of participants
                 * @type {Object}
                 */
                self.currentParticipants = [];

                /**
                 * Last invitee
                 * @type {String}
                 */
                self.invitee = "";

                /* Configuration of log */
                self.logConfig = {};

                /* IE 8 tweek for array */
                if (!Array.prototype.indexOf) {
                    Array.prototype.indexOf = function (val) {
                        var i;
                        for (i = 0; i < this.length; i++) {
                            if (this[i] === val) {
                                return i;
                            }
                        }
                        return -1;
                    };
                }

                logger.log('debug', 'application', 'Loaded main');
                logger.log('debug', 'application', 'Browser supports: ', $.support);

                /**
                 * Cache jQuery DOM objects for performance
                 * @return {Object} application object
                 */
                applicationBuildCache = function () {
                    logger.log('log', 'application','applicationBuildCache()');

                    self.cache.$configurationContainer = $(self.config.configurationContainer);
                    self.cache.$errorWrapper = $(self.config.errorWrapper);
                    self.cache.$infoWrapper = $(self.config.infoWrapper);
                    self.cache.$guestLoginButton = $(self.config.guestLoginButton);
                    self.cache.$guestLoginError = $(self.config.guestLoginError);
                    self.cache.$guestLoginErrorWrapper = $(self.config.guestLoginErrorWrapper);
                    self.cache.$guestLoginInputs = $(self.config.guestLoginInputs);
                    self.cache.$guestLoginPopup = $(self.config.guestLoginPopup);
                    self.cache.$guestName = $(self.config.guestName);
                    self.cache.$guestPIN = $(self.config.guestPIN);
                    self.cache.$guestProgressBar = $(self.config.guestProgressBar);
                    self.cache.$guestProgressBarContainer = $(self.config.guestProgressBarContainer);
                    self.cache.$guestURL = $(self.config.guestURL);
                    self.cache.$inCallButtonDisconnect = $(self.config.inCallButtonDisconnect);
                    self.cache.$inCallButtonFullscreen = $(self.config.inCallButtonFullscreen);
                    self.cache.$inCallButtonMuteMicrophone = $(self.config.inCallButtonMuteMicrophone);
                    self.cache.$inCallButtonMuteSpeaker = $(self.config.inCallButtonMuteSpeaker);
                    self.cache.$inCallButtonMuteVideo = $(self.config.inCallButtonMuteVideo);
                    self.cache.$inCallButtonPanel = $(self.config.inCallButtonPanel);
                    self.cache.$inCallButtonParticipants = $(self.config.inCallButtonParticipants);
                    self.cache.$inCallButtonParticipantsBadge = $(self.config.inCallButtonParticipantsBadge);
                    self.cache.$inCallButtonShare = $(self.config.inCallButtonShare);
                    self.cache.$inCallButtonLocalShare = $(self.config.inCallButtonLocalShare);
                    self.cache.$inCallButtonShareBadge = $(self.config.inCallButtonShareBadge);
                    self.cache.$inCallButtonToggleConfig = $(self.config.inCallButtonToggleConfig);
                    self.cache.$inCallButtonToggleLayout = $(self.config.inCallButtonToggleLayout);
                    self.cache.$inCallButtonTogglePreview = $(self.config.inCallButtonTogglePreview);
                    self.cache.$inCallContainer = $(self.config.inCallContainer);
                    self.cache.$inCallParticipantsList = $(self.config.inCallParticipantsList);
                    self.cache.$inCallParticipantsPanel = $(self.config.inCallParticipantsPanel);
                    self.cache.$inCallParticipantHeaderName = $(self.config.inCallParticipantHeaderName);
                    self.cache.$inCallPluginAndControls = $(self.config.inCallPluginAndControls);
                    self.cache.$inCallLocalShareList = $(self.config.inCallLocalShareList);
                    self.cache.$inCallShareList = $(self.config.inCallShareList);
                    self.cache.$inCallChatContainer = $(self.config.inCallChatContainer);
                    self.cache.$inCallChatTabs = $(self.config.inCallChatTabs);
                    self.cache.$inCallChatPanes = $(self.config.inCallChatPanes);
                    self.cache.$inCallChatMinimizeLink = $(self.config.inCallChatMinimizeLink);
                    self.cache.$inCallChatGroupTabLink = $(self.config.inCallChatGroupTabLink);
                    self.cache.$inCallChatForm = $(self.config.inCallChatForm);
                    self.cache.$inCallChatTextField = $(self.config.inCallChatTextField);
                    self.cache.$inCallChatTextSend = $(self.config.inCallChatTextSend);
                    self.cache.$inCallChatGroupPane = $(self.config.inCallChatGroupPane);
                    self.cache.$inCallChatGroupTab = $(self.config.inCallChatGroupTab);
                    self.cache.$notificationContainer = $(self.config.notificationContainer);
                    self.cache.$mainMenu = $(self.config.mainMenu);
                    self.cache.$pluginAndChatContainer = $(self.config.pluginAndChatContainer);
                    self.cache.$pluginContainer = $(self.config.pluginContainer);
                    self.cache.$plugin = $(self.config.pluginContainer).children(":first"); //Firefox quirk
                    self.cache.$preCallContainer = $(self.config.preCallContainer);
                    self.cache.$preCallJoinAsUserPopup = $(self.config.preCallJoinAsUserPopup);
                    self.cache.$preCallJoinMyRoomButton = $(self.config.preCallJoinMyRoomButton);
                    self.cache.$preCallJoinProgressBar = $(self.config.preCallJoinProgressBar);
                    self.cache.$preCallJoinProgressBarContainer = $(self.config.preCallJoinProgressBarContainer);
                    self.cache.$preCallLogoutButton = $(self.config.preCallLogoutButton);
                    self.cache.$preCallUserDisplayName = $(self.config.preCallUserDisplayName);
                    self.cache.$preCallPortalName = $(self.config.preCallPortalName);
                    self.cache.$preCallSearchField = $(self.config.preCallSearchField);
                    self.cache.$preCallSearchNavigationList = $(self.config.preCallSearchNavigationList);
                    self.cache.$preCallIntitePopup = $(self.config.preCallIntitePopup);
                    self.cache.$preCallIntitePopupInvitee = $(self.config.preCallIntitePopupInvitee);
                    self.cache.$preCallIntitePopupButtonAccept = $(self.config.preCallIntitePopupButtonAccept);
                    self.cache.$preCallIntitePopupButtonReject = $(self.config.preCallIntitePopupButtonReject);
                    self.cache.$preCallSearchUserClass = $(self.config.preCallSearchUserClass);
                    self.cache.$preCallJoinConferencePinDialog = $(self.config.preCallJoinConferencePinDialog);
                    self.cache.$preCallJoinConferencePinDialogPIN = $(self.config.preCallJoinConferencePinDialogPIN);
                    self.cache.$preCallJoinConferencePinDialogButton = $(self.config.preCallJoinConferencePinDialogButton);
                    self.cache.$preCallJoinConferencePinDialogErrorWrapper = $(self.config.preCallJoinConferencePinDialogErrorWrapper);
                    self.cache.$preCallJoinConferencePinDialogError = $(self.config.preCallJoinConferencePinDialogError);
                    self.cache.$splash = $(self.config.splash);
                    self.cache.$userLoginButton = $(self.config.userLoginButton);
                    self.cache.$userLoginError = $(self.config.userLoginError);
                    self.cache.$userLoginErrorWrapper = $(self.config.userLoginErrorWrapper);
                    self.cache.$userLoginInputs = $(self.config.userLoginInputs);
                    self.cache.$userLoginPassword = $(self.config.userLoginPassword);
                    self.cache.$userLoginPopup = $(self.config.userLoginPopup);
                    self.cache.$userLoginPortal = $(self.config.userLoginPortal);
                    self.cache.$userLoginProgressBar = $(self.config.userLoginProgressBar);
                    self.cache.$userLoginProgressContainer = $(self.config.userLoginProgressContainer);
                    self.cache.$userLoginUsername = $(self.config.userLoginUsername);
                    return self;
                };

                /**
                 * Prints out some important user information for debugging purposes
                 * @return None
                 */
                applicationClientInfoPrint = function() {
                    var $window = $(window);

                    logger.log('debug', 'application', "Supported operations:");
                    $.each($.support, function(i, obj) {
                        logger.log('debug', 'application', "    " + i + "->" + obj);
                    });
                    logger.log('debug', 'application', "Screen resolution: ", window.screen.width, window.screen.height);
                    logger.log('debug', 'application', "Window resulution: ", $window.width(), $window.height());
                    logger.log('debug', 'application', "User agent: ", navigator.userAgent);
                };
                /**
                 * Creates a Handlebar helper to print a user in search view
                 * @return None
                 */
                var templateHelperUser = function () {
                    handlebars['default'].registerHelper('printUserNoButtons', function () {
                        var ret = "";
                        var message = "";
                        if (this.isOnline) {
                            if (this.isBusy) {
                                ret += '<i class="icon-torso preCallSearchListUserIcon" style="color: red;" title="Busy"></i>';
                            } else {
                                ret += '<i class="icon-torso preCallSearchListUserIcon" style="color: green;" title="Available"></i>';
                            }
                        } else {
                            ret += '<i class="icon-torso preCallSearchListUserIcon" style="color: grey;" title="Offline"></i>';
                        }
                        ret += '<span>';
                        if (this.isLocked) {
                            ret += '<i class="icon-lock" title="Room is locked"></i>&nbsp;';
                        }
                        if (this.isOccupied) {
                            ret += '<i class="icon-th-large" title="Room is occupied"></i>&nbsp;';
                        }
                        if (this.isRoomFull) {
                            ret += '<i class="icon-remove" title="Room is full"></i>&nbsp;';
                            message = 'full';
                        }
                        if (this.isLocked) {
                            message = 'locked';
                        }
                        if (this.isLocked || this.isRoomFull) {
                            ret += '&nbsp;' + this.name;
                        } else {
                            ret += '&nbsp;<a href="#" data-owner="' + this.ownerId + '" data-type="join" data-haspin="' + String(this.hasPin)+ '" data-id="' + this.id + '" title="Go to the room of ' + this.name + '">' + this.name + '</a>';
                        }
                        if (this.emailAddress) {
                            ret += '&nbsp;(' + this.emailAddress + ')';
                        }
                        return new handlebars['default'].SafeString(ret);
                    });

                    handlebars['default'].registerHelper('printUser', function () {
                        var ret = "";
                        ret += '<div class="userName pull-left">';
                        ret += handlebars['default'].helpers.printUserNoButtons.apply(this);
                        ret += '</div>';
                        ret += '<div class="btn-toolbar pull-right hide">';

                        ret += '<div class="btn-group">';
                        var occupiedClass = this.isOccupied ? ' ' + self.config.btnChangingClass : '';
                        if (this.isLocked) {
                            ret += '<a href="#" role="button" class="btn btn-small preCallSearchListUserButtonRoom disabled' + occupiedClass + '" data-owner="' + this.ownerId + '" data-type="join" data-haspin="' + String(this.hasPin)+ '" data-id="' + this.id + '" title="Room of ' + this.name + ' if locked"><i class="icon-home"></i></a>';
                        } else if (this.isRoomFull) {
                            ret += '<a href="#" role="button" class="btn btn-small preCallSearchListUserButtonRoom disabled' + occupiedClass + '" data-owner="' + this.ownerId + '" data-type="join" data-haspin="' + String(this.hasPin)+ '" data-id="' + this.id + '" title="Room of ' + this.name + ' if full"><i class="icon-home"></i></a>';
                        } else {
                            ret += '<a href="#" role="button" class="btn btn-small preCallSearchListUserButtonRoom' + occupiedClass + '" data-owner="' + this.ownerId + '" data-type="join" data-haspin="' + String(this.hasPin)+ '" data-id="' + this.id + '" title="Go to the room of ' + this.name + '"><i class="icon-home"></i></a>';
                        }
                        if (this.canCallDirect) {
                            ret += '<a href="#" role="button" class="btn btn-small preCallSearchListUserButtonDirect" data-type="direct" data-id="' + this.id + '" title="Call ' + this.name + ' directly"><i class="icon-user"></i></a>';
                        } else {
                            ret += '<a href="#" role="button" class="btn btn-small preCallSearchListUserButtonDirect disabled" data-type="direct" data-id="' + this.id + '" title="Direct call is not available"><i class="icon-user"></i></a>';
                        }
                        if (this.inFav) {
                            ret += '<a href="#" role="button" class="btn btn-small ' + self.config.btnOffClass + ' preCallSearchListUserButtonFav" data-type="remove" data-id="' + this.id + '" title="Remove from favorites"><i class="icon-remove-circle"></i></a>';
                        } else {
                            ret += '<a href="#" role="button" class="btn btn-small ' + self.config.btnOnClass + ' preCallSearchListUserButtonFav" data-type="add" data-id="' + this.id + '" title="Add to favorites"><i class="icon-star"></i></a>';
                        }
                        ret += '</div>';

                        ret += '</div>';
                        return new handlebars['default'].SafeString(ret);
                    });

                };

                /**
                 * Build handlebars templates
                 * @return {Object} Application object
                 */
                applicationBuildTemplates = function () {
                    self.templates.pluginTemplate = handlebars['default'].compile(self.config.pluginTemplate);
                    self.templates.configurationTemplate = handlebars['default'].compile(self.config.configurationTemplate);
                    self.templates.errorTemplate = handlebars['default'].compile(self.config.errorTemplate);
                    self.templates.infoTemplate = handlebars['default'].compile(self.config.infoTemplate);
                    self.templates.inCallParticipantsTemplate = handlebars['default'].compile(self.config.inCallParticipantsTemplate);
                    self.templates.inCallParticipantTemplate = handlebars['default'].compile(self.config.inCallParticipantTemplate);
                    self.templates.inCallSharesTemplate = handlebars['default'].compile(self.config.inCallSharesTemplate);
                    self.templates.inCallLocalSharesTemplate = handlebars['default'].compile(self.config.inCallLocalSharesTemplate);
                    self.templates.preCallSearchProgressTemplate = handlebars['default'].compile(self.config.preCallSearchProgressTemplate);
                    self.templates.preCallMyRoomTemplate = handlebars['default'].compile(self.config.preCallMyRoomTemplate);
                    self.templates.preCallSearchTemplate = handlebars['default'].compile(self.config.preCallSearchTemplate);
                    self.templates.preCallSearchUserTemplate = handlebars['default'].compile(self.config.preCallSearchUserTemplate);
                    self.templates.preCallSearchJustUserTemplate = handlebars['default'].compile(self.config.preCallSearchJustUserTemplate);
                    self.templates.pluginInstallInstructionsTemplate = handlebars['default'].compile(self.config.pluginInstallInstructionsTemplate);
                    self.templates.pluginEnableInstructionsTemplate = handlebars['default'].compile(self.config.pluginEnableInstructionsTemplate);
                    self.templates.inCallChatTabTemplate = handlebars['default'].compile(self.config.inCallChatTabTemplate);
                    self.templates.inCallChatPaneTemplate = handlebars['default'].compile(self.config.inCallChatPaneTemplate);
                    self.templates.inCallChatPaneMessageTemplate = handlebars['default'].compile(self.config.inCallChatPaneMessageTemplate);
                    self.templates.inCallParticipantInfoTemplate = handlebars['default'].compile(self.config.inCallParticipantInfoTemplate);
                    self.templates.preCallInvitingDialogTemplate = handlebars['default'].compile(self.config.preCallInvitingDialogTemplate);

                    /* Register helpers */
                    templateHelperUser();

                    return self;
                };

                /**
                 * Add plugin object to DOM
                 * @return {Object} application object
                 */
                applicationAddPlugin = function () {
                    logger.log('log', 'application', 'applicationAddPlugin()');
                    var pluginContainer = $(self.config.pluginContainer);

                    var htmlData = self.templates.pluginTemplate({
                        id: self.config.pluginIdName,
                        mimeType: self.config.pluginMimeType
                    });

                    pluginContainer.html(htmlData);
                    return self;
                };

                /**
                 * Provide developer with information.
                 * @return {Object} Application object
                 */
                applicationCheckForDeveloper = function () {
                    if (!self.config.developerEdition) {
                        return;
                    }
                    if (self.config.soapProxyURL === "http://stunusa.vidyo.com/sp/soap_proxy.php" || self.config.soapProxyURL === "http://vidyoweb.apps.vidyo.com/sp/soap_proxy.php") {
                        alert("Dear developer. Please install SOAP proxy on your server and change soapProxyURL in the main.config.js to your server's location.");
                    }
                };

                /**
                 * Update application state to disconnected.
                 * @return {Object} Application object
                 */
                applicationCallCleanup = function() {
                    logger.log('log', 'application', 'applicationCallCleanup()');
                    helperConferenceUpdateTimerStop();
                    self.inConference = false;
                    self.isJoining = false;
                    return self;
                };

                /**
                 * Build subscription events
                 * @return {Object} Application object
                 */
                applicationBuildSubscribeEvents = function () {
                    /* Build subscription events.
                     * They are used to notify application about events from Vidyo
                     * library so it can update UI state.
                     */

                    /* Plugin life-cycle */

                    /*
                     * Plugin preload happens only once and we may need to delay
                     * actions associated with it so use jQuery defer for that instead of regular trigger/on events.
                     */
                    self.events.pluginPreloadEvent = $.Deferred();
                    self.events.pluginLoadedEvent = $({
                        type: "pluginLoadedEvent"
                    });

                    self.events.configurationUpdateEvent = $({
                        type: "configurationUpdateEvent"
                    });

                    /* Login state control */
                    self.events.loginEvent = $({
                        type: "loginEvent"
                    });
                    self.events.logoutEvent = $({
                        type: "logoutEvent"
                    });

                    /* Pre-call */
                    self.events.searchUpdateEvent = $({
                        type: "searchUpdateEvent"
                    });
                    self.events.incomingCallEvent = $({
                        type: "incomingCallEvent"
                    });

                    /* Call state control */
                    self.events.disconnectEvent = $({
                        type: "disconnectEvent"
                    });
                    self.events.connectEvent = $({
                        type: "connectEvent"
                    });

                    /* In call events */
                    self.events.participantUpdateEvent = $({
                        type: "participantUpdateEvent"
                    });
                    self.events.participantPinDoneEvent = $({
                        type: "participantPinDoneEvent"
                    });
                    self.events.shareUpdateEvent = $({
                        type: "shareUpdateEvent"
                    });
                    self.events.muteUpdateEvent = $({
                        type: "muteUpdateEvent"
                    });
                    self.events.chatUpdateEvent = $({
                        type: "chatUpdateEvent"
                    });

                    /* Conference control events */
                    self.events.recorderEvent = $({
                        type: "recorderEvent"
                    });
                    self.events.portalParticipantUpdateEvent = $({
                        type: "portalParticipantUpdateEvent"
                    });
                    self.events.roomLockEvent = $({
                        type: "roomLockEvent"
                    });
                    /* Fullscreen */
                    self.events.fullscreenEvent = $({
                        type: "fullscreenEvent"
                    });

                    return self;
                };

                /**
                 * Bind Vidyo plugin callbacks.
                 * No direct access to UI/cache should be used in Vidyo callbacks.
                 * See Vidyo.client.messages JavaScript file for details about events.
                 * @return {Object} Application object
                 */
                applicationBindVidyoCallbacks = function () {
                    /*  Vidyo Library raw Callbacks.
                        Will be translated to defers if needed.
                     */
                    logger.log('log', 'application', 'applicationBindVidyoCallbacks()');

                    self.callbacks = {
                        /**
                         * Notification about log coming from Vidyo library
                         * @param {Object} event Logging message details
                         */
                        PrivateOutEventLog: function (event) {
                            if (self.logConfig.enableVidyoClientLogs) {
                                logger.log('debug', 'plugin', event);
                            }
                        },
                        /**
                         * Login process
                         * @param {Object} event Login parameters used
                         */
                        OutEventLogin: function (event) {
                            logger.log('info', 'callback', "OutEventLogin(", event, ")");
                            if (event.error === 0) {
                                if (self.isGuestLogin) {
                                    self.guestLoginInfo.portalUri = event.portalUri.split('/services/')[0];
                                    helperPersistentStorageSetValue('guestLoginInfo', self.guestLoginInfo);
                                } else {
                                    self.loginInfo.portalUri = event.portalUri.split('/services/')[0];
                                    helperPersistentStorageSetValue('loginInfo', self.loginInfo);
                                }
                            }
                        },
                        /**
                         * Called when sign in process is in progress.
                         * Used to initiate licensing procedure if needed.
                         * @param {Object} e Event details
                         */
                        OutEventSignIn: function (e) {
                            logger.log('info', 'callback', "OutEventSignIn()");

                            /* SignIn is a part of connect process for guest only. */
                            if (self.isGuestLogin) {
                                self.events.connectEvent.trigger('progress');
                            } else {
                                self.events.loginEvent.trigger('progress');
                            }

                            if (e.activeEid === 0) {
                                logger.log('debug', 'callback', "OutEventSignIn(): will start license procedure");

                                var inEvent = vidyoClientMessages.inEventLicense();
                                self.client.sendEvent(inEvent);
                            }
                        },
                        /**
                         * Reports joining progress.
                         * Good place to notify user about conference joining progress.
                         */
                        OutEventJoinProgress: function () {
                            logger.log('info', 'callback', "OutEventJoinProgress()");

                            /* Update progress bar */
                            self.events.connectEvent.trigger('progress');
                        },
                        /**
                         * At this stage user is logged in into VidyoPortal.
                         */
                        OutEventSignedIn: function () {
                            logger.log('info', 'callback', "OutEventSignedIn()");

                            /*  Will continue connecting when guest;
                                Will be done login in when registered user.
                             */
                            if (self.isGuestLogin) {
                                self.events.connectEvent.trigger('progress');
                            } else {
                                self.events.loginEvent.trigger('done');
                            }
                        },
                        /**
                         * Vidyo library is successfully started.
                         */
                        OutEventLogicStarted: function () {
                            logger.log('info', 'callback', "OutEventLogicStarted()");

                            var conf = clientConfigurationGet();

                            /* Update configuration with defaults */
                            var updatedConf = clientConfigurationBootstrap(conf);
                            self.events.configurationUpdateEvent.trigger("done", updatedConf);
                        },
                        /**
                         * At this stage user is connected to the conference
                         */
                        OutEventConferenceActive: function () {
                            logger.log('info', 'callback', "OutEventConferenceActive()");

                            /* Enforce preview mode to current */
                            clientPreviewModeSet(self.currentPreviewMode);
                            /* Query for participants */
                            self.sessionInfo = clientSessionGetInfo();
                            self.events.connectEvent.trigger('done');
                        },
                        /**
                         * Started to connect to a conference
                         */
                        OutEventJoining: function () {
                            logger.log('info', 'callback', "OutEventJoining()");

                        },
                        /**
                         * Notifies about connecting as guest progress
                         * @param {Object} e Event details
                         */
                        PrivateOutEventVcsoapGuestLink: function (e) {
                            logger.log('info', 'callback', "PrivateOutEventVcsoapGuestLink(", e, ")");

                            if (e.result === "Failure") {
                                self.events.connectEvent.trigger('fail', {error: "Failed to link endpoint"});
                            }
                        },
                        /**
                         * Microphone mute state changed
                         * @param {Object} e Event details
                         */
                        OutEventMutedAudioIn: function (e) {
                            logger.log('info', 'callback', "OutEventMutedAudioIn()", e);

                            self.events.muteUpdateEvent.trigger("done", {
                                device: "microphone",
                                mute: e.isMuted
                            });
                            self.isMutedMic = e.isMuted;
                        },
                        /**
                         * Speaker mute state changed
                         * @param {Object} e Event details
                         */
                        OutEventMutedAudioOut: function (e) {
                            logger.log('info', 'callback', "OutEventMutedAudioOut()", e);

                            self.events.muteUpdateEvent.trigger("done", {
                                device: "speaker",
                                mute: e.isMuted
                            });

                            self.isMutedSpeaker = e.isMuted;
                        },
                        /**
                         * Video privacy (mute) state changed
                         * @param {Object} e Event details
                         */
                        OutEventMutedVideo: function (e) {
                            logger.log('info', 'callback', "OutEventMutedVideo()", e);

                            self.events.muteUpdateEvent.trigger("done", {
                                device: "video",
                                mute: e.isMuted
                            });
                            self.isMutedVideo = e.isMuted;
                        },
                        // /**
                        //  * Mouse movement events
                        //  * @param {Object} e Event details
                        //  */
                        // OutEventMouseMove: function (e) {},
                        // /**
                        //  * Mouse button is released
                        //  * @param {Object} e Event details
                        //  */
                        // OutEventMouseUp: function (e) {},
                        /**
                         * Mouse button is pressed
                         * @param {Object} e Event details
                         */
                        OutEventMouseDown: function (e) {
                            /* Exit fullscreen on double click */
                            if (e.count === 2) {
                                if (self.isFullscreen) {
                                    uiFullscreenCancel();
                                } else {
                                    uiFullscreenCancel();
                                }
                            }
                        },
                        /**
                         * New share was added to the conference
                         * @param {Object} e Event details
                         */
                        OutEventAddShare: function (e) {
                            logger.log('info', 'callback', "OutEventAddShare()", e);

                            var shares = clientSharesGet();
                            self.events.shareUpdateEvent.trigger('done', shares);
                        },
                        /**
                         * Share was removed from the conference
                         * @param {Object} e Event details
                         */
                        OutEventRemoveShare: function (e) {
                            logger.log('info', 'callback', "OutEventRemoveShare()", e);

                            var shares = clientSharesGet();
                            self.events.shareUpdateEvent.trigger('done', shares);
                        },
                        /**
                         * User logged out from the VidyoPortal
                         * @param {Object} e Event details
                         */
                        OutEventSignedOut: function (e) {
                            logger.log('info', 'callback', "OutEventSignedOut()", e);

                            if (e.error) {
                                if (!self.isGuestLogin) {
                                    if (e.cause === "UserSignedIn") { // Means login error
                                        if (e.error === 401) {
                                            self.events.loginEvent.trigger("fail", "Invalid credentials");
                                        } else {
                                            self.events.loginEvent.trigger("fail", "Login error " + e.error);
                                        }
                                    } else {
                                        self.events.logoutEvent.trigger("fail", e.cause);
                                    }
                                }
                                else {
                                    self.events.connectEvent.trigger("fail", {error:"Error " + e.error});
                                }
                            } else {
                                if (clientConferenceStateGet().callState !== "Idle") {
                                    clientConferenceLeave();
                                }
                                self.events.logoutEvent.trigger("done");
                            }
                        },
                        /**
                         * Number of participants changed
                         * @param {Object} e Event details
                         */
                        OutEventParticipantsChanged: function (e) {
                            logger.log('info', 'callback', "OutEventParticipantsChanged()", e);
                            var participants = clientParticipantsGet();
                            self.events.participantUpdateEvent.trigger('done', [participants]);
                        },
                        /**
                         * Current conference was ended
                         * @param {Object} e Event details
                         */
                        OutEventConferenceEnded: function (e) {
                            logger.log('info', 'callback', "OutEventConferenceEnded()", e);
                            /* Remote disconnect */
                            // if (self.inConference) {
                            //     self.events.disconnectEvent.trigger('done');
                            //     uiGenericNotify("Disconnected remotely", "error");
                            // }
                        },
                        OutEventCallState: function (e) {
                            logger.log('info', 'callback', "OutEventCallState()", e);
                            /* Remote disconnect */
                            if (e.callState === "Idle") {
                                /* Failed to connect */
                                if (self.isJoining && !self.isDirectCall) {
                                    self.events.connectEvent.trigger('fail', {error: "Disconnected by server"});
                                } else if (self.isJoining && self.isDirectCall) {
                                    self.events.connectEvent.trigger('fail', {error: "Remote user did not answer"});
                                } else {
                                    self.events.disconnectEvent.trigger('done');
                                    /* Disconnected by the server */
                                    if (self.inConference) {
                                        uiGenericNotify("Disconnected remotely", "error");
                                    }
                                }
                            }
                        },
                        OutEventIncomingCall: function (e) {
                            logger.log('info', 'callback', "OutEventIncomingCall()", e);
                            self.events.incomingCallEvent.trigger("start", e);

                        },
                        OutEventIncomingCallEnded: function (e) {
                            logger.log('info', 'callback', "OutEventIncomingCallEnded()", e);
                            self.events.incomingCallEvent.trigger("end", e);
                        },
                        OutEventPinParticipantDone: function (e) {
                            logger.log('info', 'callback', "OutEventPinParticipantDone()", e);
                            self.events.participantPinDoneEvent.trigger("done", e);
                        },
                        OutEventGroupChat: function (e) {
                            logger.log('info', 'callback', "OutEventGroupChat()", e);
                            if (self.config.enableChat) {
                                e.isGroup = true;
                                e.isOutgoing = false;
                                self.events.chatUpdateEvent.trigger("done", e);
                            }
                        },
                        OutEventPrivateChat: function (e) {
                            logger.log('info', 'callback', "OutEventPrivateChat()", e);
                            if (self.config.enableChat) {
                                e.isGroup = false;
                                e.isOutgoing = false;
                                self.events.chatUpdateEvent.trigger("done", e);
                            }
                        },
                        OutEventConferenceInfoUpdate: function (e) {
                            logger.log('info', 'callback', "OutEventConferenceInfoUpdate()", e);
                            if (e.event === "Recording") {
                                if (e.eventStatus === true) {
                                    self.events.recorderEvent.trigger("start");
                                } else {
                                    self.events.recorderEvent.trigger("stop");
                                }
                            }
                        },
                        OutEventDevicesChanged: function (e) {
                            logger.log('info', 'callback', "OutEventDevicesChanged()", e);
                            var conf = clientConfigurationGet();
                            /* Update configuration with new values */
                            self.events.configurationUpdateEvent.trigger("done", conf);
                        }

                    };


                    return self;
                };

                /**
                 * Binds application events.
                 * UI is updated here.
                 * @return {Object} Application object
                 */
                applicationBindSubscribeEvents = function () {
                    /* Subscription events */
                    logger.log('info', 'application', 'applicationBindSubscribeEvents()');

                    /* Triggered on incoming chat message */
                    self.events.chatUpdateEvent
                        .on('done', function (event, e) {
                            logger.log('info', 'application', 'chatUpdateEvent::done - ', event, e);


                            uiChatUpdateView(e);
                            if (e.isOutgoing === false) {
                                var participants = clientParticipantsGet();
                                var participantName;
                                var i;
                                /*  Get corresponding participant's name for a message.
                                 */
                                for (i = 0; i < participants.length; i++) {
                                    if (e.uri === participants[i].uri) {
                                        participantName = participants[i].name;
                                        break;
                                    }
                                }
                                var header = e.isGroup ? "Group message from " : "Private message from ";

                                uiGenericNotify(header + "<strong>" + participantName + "</strong>" + "<br>" + "<em style='color:black;'>" + e.message + "</em>", self.config.notificationUserStatusTimeout);
                                /* Send desktop notification only when not in focus*/
                                if (document.hasFocus && !document.hasFocus()) {
                                    uiDesktopNotification(
                                        "VidyoWeb - " + header + participantName,
                                        e.message + " (click to respond)",
                                        self.config.notificationUserStatusTimeout,
                                        function () {
                                            if (e.isGroup) {
                                                uiChatViewTabSwitch("group");
                                            } else {
                                                uiChatViewTabSwitch(e.uri);
                                            }
                                        });
                                }
                            }
                        });
                    /* Triggered when participant pinning response received */
                    self.events.participantPinDoneEvent
                        .on('done', function (event, e) {
                            logger.log('info', 'application', 'chatUpdateEvent::done', event, e);
                            window.setTimeout(function () {
                                /* Remove temporary warning mode */
                                var i;
                                var views, $view;
                                views = self.cache.$inCallParticipantsList.find("." + self.config.btnChangingClass);
                                for (i = 0; i < views.length; i++) {
                                    $view = $(views[i]);
                                    if ($view.data("uri") === e.uri) {
                                        $view.removeClass(self.config.btnChangingClass);
                                    }
                                }
                                if (e.isSet) {
                                    var viewParticipants = self.cache.$inCallParticipantsList.find(self.config.inCallParticipantsClass);
                                    var $participant, button, pin;
                                    for (i = 0; i < viewParticipants.length; i++) {
                                        $participant = viewParticipants[i] ? $(viewParticipants[i]) : undefined;
                                        button = $($participant.find(self.config.inCallParticipantPinButtonClass)[0]);

                                        if ($participant.data("uri") === e.uri) {
                                            pin = button.data("pinned") ? false : true;
                                            button.data("pinned", pin);
                                            if (pin) {
                                                button.addClass(self.config.btnPrimaryClass);
                                            } else {
                                                button.removeClass(self.config.btnPrimaryClass);
                                            }
                                        } else { // we can have only one person pinned at a time so remove marking of pinned participant
                                            button.removeClass(self.config.btnPrimaryClass);
                                        }
                                    }
                                }
                            }, 300);

                        });
                    /* Occurred when plugin is really ready  */
                    self.events.pluginLoadedEvent
                        .on('done', function () {
                            logger.log('info', 'plugin', 'pluginLoadedEvent::done');
                            uiReportInfoDismiss();
                            uiPromiseToEndSplashScreen()
                                .done(function () {
                                    uiPromiseToShowMenu(true);
                                });
                        })
                        .on('fail', function (event, error) {
                            logger.log('warning', 'plugin', 'pluginLoadedEvent::fail', event, error);
                            uiPromiseToEndSplashScreen()
                                .done(function () {
                                    uiReportError('Vidyo Plugin error', error);
                                });
                        })
                        .on('info', function (event, message) {
                            logger.log('info', 'plugin', 'pluginLoadedEvent::info', event, message);
                            uiPromiseToEndSplashScreen()
                                .done(function () {
                                    uiReportInfo(message.message, message.details);
                                });
                        });
                    /* Occurs when Vidyo library configuration is updated */
                    self.events.configurationUpdateEvent
                        .on('done', function (event, newConfig) {
                            logger.log('info', 'configuration', 'configurationUpdateEvent::done', event);
                            var data = {
                                camera: [],
                                speaker: [],
                                microphone: []
                            };

                            $.each(newConfig.cameras, function (i, name) {
                                data.camera.push({
                                    name: name,
                                    id: i,
                                    isSelected: (i === newConfig.currentCamera)
                                });
                            });


                            $.each(newConfig.speakers, function (i, name) {
                                data.speaker.push({
                                    name: name,
                                    id: i,
                                    isSelected: (i === newConfig.currentSpeaker)
                                });
                            });

                            $.each(newConfig.microphones, function (i, name) {
                                data.microphone.push({
                                    name: name,
                                    id: i,
                                    isSelected: (i === newConfig.currentMicrophone)
                                });
                            });

                            data.selfViewLoopbackPolicy = [{
                                name: "Show",
                                value: 0,
                                isSelected: newConfig.selfViewLoopbackPolicy === 0
                            }, {
                                name: "Hide",
                                value: 1,
                                isSelected: newConfig.selfViewLoopbackPolicy === 1
                            }, {
                                name: "Show when only participant",
                                value: 2,
                                isSelected: newConfig.selfViewLoopbackPolicy === 2
                            }];
                            /* From VidyoClientParameters.h */
                            var PROXY_VIDYO_FORCE = 1,
                                PROXY_WEB_ENABLE = (1 << 3),
                                PROXY_WEB_IE = (1 << 4);

                            data.alwaysProxy = !! (newConfig.proxySettings & PROXY_VIDYO_FORCE);
                            data.useWebProxy = ( !! (newConfig.proxySettings & PROXY_WEB_ENABLE) && !! (newConfig.proxySettings & PROXY_WEB_IE));

                            data.hideParticipants = !newConfig.enableShowConfParticipantName;
                            data.muteMicrophone = !! newConfig.enableMuteMicrophoneOnJoin;
                            data.hideCamera = !! newConfig.enableHideCameraOnJoin;
                            data.echoCancel = !! newConfig.enableEchoCancellation;
                            data.autoGain = !! newConfig.enableAudioAGC;

                            data.logsApplication = self.logConfig.enableAppLogs;
                            data.logsJS = self.logConfig.enableVidyoPluginLogs;
                            data.logsClient = self.logConfig.enableVidyoClientLogs;
                            data.logLevelsAndCategories = self.logConfig.logLevelsAndCategories;

                            logger.log('debug', 'configuration', 'configurationUpdateEvent::done - Devices detected', data);

                            uiConfigurationUpdateWithData(data);
                            if (!self.inConference) {
                                self.cache.$configurationContainer.slideDown();
                            }

                        });
                    /* Incoming call */
                    self.events.incomingCallEvent
                        .on('start', function (e, data) {
                            logger.log('info', 'call', 'incomingCallEvent::start', e);
                            var htmlData = self.templates.preCallInvitingDialogTemplate({
                                user: data.invitingUser,
                                isDirect: data.isDirectCall
                            });

                            self.cache.$preCallIntitePopupInvitee.html(htmlData);
                            // self.cache.$preCallIntitePopup.modal({
                            //     keyboard: false,
                            //     backdrop: "static"
                            // });
                            self.cache.$preCallIntitePopup.data('hide', false);
                            self.cache.$preCallIntitePopup.modal('show');
                            self.invitee = data.invitingUser;
                            helperRingtonePlay();

                            /* Use desktop notifications if not focused*/
                            if (document.hasFocus && !document.hasFocus()) {
                                self.incomingCallNotification = uiDesktopNotification("VidyoWeb - incoming call", "Incoming call from " + data.invitingUser + ". Click to show.", 0);
                            }

                        })
                        .on('end', function (e) {
                            logger.log('info', 'call', 'incomingCallEvent::end', e);
                            uiGenericNotify("<em>" + (new Date()).toLocaleTimeString() + "</em>" + "<br>Missed call from " + "<strong>" + self.invitee + "</strong>", "error", 0);
                            uiIncomingCallNotificationDismiss();
                            uiIncomingCallMissedCallNotify();
                        });
                    /* New user information */
                    self.events.searchUpdateEvent
                        .on('done', function (e, data) {
                            logger.log('info', 'user', 'searchUpdateEvent::done - ', e, data);

                            uiUserNavigationUpdateWithData(data);

                            /**
                             * First search after login is for user's favorites,
                             * so update and hide user login popup and enable
                             * pre-call menu.
                             */
                            if (self.cache.$userLoginPopup.is(":visible")) {
                                self.cache.$userLoginPopup.modal('hide').promise()
                                    .done(function () {
                                        if (!self.isGuestLogin) {
                                            uiUpdateUserLoginProgress("0px", false);
                                        }
                                        self.cache.$mainMenu.hide();
                                    });
                                uiPrecallMenuShow(true);
                            }
                        })
                        .on('fail', function (e, error) {
                            logger.log('error', 'user', 'searchUpdateEvent::fail', e);
                            uiReportError('Search update', error);
                        })
                        .on('cancel', function () {
                            logger.log('debug', 'user', 'searchUpdateEvent::cancel');
                            /* Just show what we currently have */
                            self.users = self.lastUsers;
                            self.events.searchUpdateEvent.trigger('done', self.users);
                        });

                    self.events.loginEvent
                        .on('done', function () {
                            logger.log('info', 'login', 'loginEvent::done');
                            self.isLoggedIn = true;
                            self.recorderProfiles = undefined;
                            portalRecordGetProfiles();
                            /* Will delay show if precall until search results are back */
                            helperSoapPromiseToGetMyAccount()
                                .done(function (response) {
                                    logger.log('info', 'login', 'loginEvent - my Account: ', response, response.Entity);

                                    self.myAccount = response.Entity;
                                    uiUpdateUserLoginProgress("80%");
                                    self.cache.$preCallUserDisplayName.html(self.myAccount.displayName);
                                    self.cache.$preCallPortalName.html(self.loginInfo.portalUri.replace("http://", "").replace("https://", ""));
                                    portalParticipantsPromiseToGet(self.myAccount.entityID)
                                        .done(function (data) {
                                            uiUpdateUserLoginProgress("90%");
                                            self.events.portalParticipantUpdateEvent.trigger('done', data);
                                            portalUserSearchBothFavAndUsers(false);
                                        })
                                        .fail(function (error) {
                                            self.events.loginEvent.trigger('fail', "Unable to get user's participants list: " + error);
                                        });
                                })
                                .fail(function (error) {
                                    self.events.loginEvent.trigger('fail', "Unable to get user's account information: " + error);
                                });

                            uiUpdateUserLoginProgress("80%");
                        })
                        .on('fail', function (event, error) {
                            logger.log('error', 'login', 'loginEvent::fail', event, error);
                            self.isLoggedIn = false;

                            if (!self.isGuestLogin) {
                                self.cache.$userLoginButton.removeClass('disabled');
                                uiUpdateUserLoginProgress("0px", false);
                                self.isGuestLogin = false;
                                uiReportUserLoginError("<h3>Failed to login</h3>" + "<p>" + error + "</p>");
                            }
                        })
                        .on('progress', function (event, percent) {
                            logger.log('debug', 'login', 'loginEvent::progress - percent: ', percent, event);
                            if (!self.isGuestLogin) {
                                if (percent !== undefined) {
                                    uiUpdateUserLoginProgress(percent);
                                } else {
                                    var step = (self.cache.$userLoginProgressBar.data("step") || 1) + 1;
                                    self.cache.$userLoginProgressBar.data("step", step);
                                    uiUpdateUserLoginProgress((step * self.config.progressStepInPercents) + "%");
                                }
                            }
                        });

                    self.events.connectEvent
                        .on('done', function () {
                            logger.log('info', 'call', 'connectEvent::done');
                            self.inConference = true;
                            self.isJoining = false;

                            /* Always have one larger participant */
                            self.numPreferred = 1;
                            clientLayoutSet(self.numPreferred);

                            if (self.config.enableChat && !self.cache.$inCallChatMinimizeLink.data("minimized")) {
                                self.cache.$inCallChatMinimizeLink.click();
                            }
                            self.cache.$inCallParticipantsList.html(" ");

                            if (self.config.enableChat) {
                                /* Reset group tab notify */
                                uiChatViewTabNotifyStop("group");
                            }
                            /* Restore last state of full page mode */
                            logger.log('debug', 'call', 'connectEvent::done');

                            self.cache.$guestLoginPopup.modal('hide').promise()
                                .done(function () {
                                    if (self.isGuestLogin) {
                                        uiUpdateGuestLoginProgress("0px", false);
                                        self.cache.$mainMenu.hide();
                                    } else {
                                        uiUpdateJoinProgress("0px", false);
                                        uiPrecallMenuShow(false);
                                    }
                                    uiLocalShareReset();

                                    uiInCallShow(true, true);

                                    self.cache.$configurationContainer.slideUp();

                                });
                            helperConferenceUpdateTimerStart(self.config.participantRefreshTimeout);
                            /* Update recording state */
                            var recState = clientRecordAndWebcastStateGet();
                            if (recState && recState.recording) {
                                self.events.recorderEvent.trigger("start");
                            } else {
                                self.events.recorderEvent.trigger("stop");
                            }
                        })
                        .on('fail', function (event, error) {
                            logger.log('error', 'call', 'connectEvent::fail - error: ', error, event);
                            self.inConference = false;
                            self.isJoining = false;

                            if (error.details && error.details.faultstring === "Wrong PIN") {
                                uiReportJoinConferencePinError("Wrong PIN");
                                self.cache.$preCallJoinConferencePinDialog.modal('show');
                            } else {
                                if (self.isGuestLogin) {
                                    logger.log('error', 'call', 'Failed to connect as guest');

                                    self.cache.$guestLoginButton.removeClass('disabled');
                                    uiUpdateGuestLoginProgress("0px", false);
                                    self.isGuestLogin = false;
                                    uiReportGuestLoginError("<h3>Failed to connect</h3>" + "<p>" + error.error + "</p>");
                                } else {
                                    logger.log('error', 'call', 'Failed to connect as user');
                                    setTimeout(function() {
                                        uiUpdateJoinProgress("0px", false);
                                    }, 500);
                                    uiReportError("Failed to connect", error.error);
                                }
                            }
                            helperConferenceUpdateTimerStop();
                        })
                        .on('progress', function (event, percent) {
                            logger.log('debug', 'call', 'connectEvent::progress - percent: ', percent, event);
                            var step;
                            if (self.isGuestLogin) {
                                if (percent !== undefined) {
                                    uiUpdateGuestLoginProgress(percent);
                                } else {
                                    step = (self.cache.$guestProgressBar.data("step") || 1) + 1;
                                    self.cache.$guestProgressBar.data("step", step);
                                    uiUpdateGuestLoginProgress((step * self.config.progressStepInPercents) + "%");
                                }
                            } else {
                                if (percent !== undefined) {
                                    uiUpdateJoinProgress(percent);
                                } else {
                                    step = (self.cache.$preCallJoinProgressBar.data("step") || 1) + 1;
                                    self.cache.$preCallJoinProgressBar.data("step", step);
                                    uiUpdateJoinProgress((step * self.config.progressStepInPercents) + "%", true);
                                }
                            }
                        });

                    self.events.logoutEvent
                        .on('done', function () {
                            logger.log('info', 'login', 'logoutEvent::done');
                            uiPrecallMenuShow(false, function () {
                                self.cache.$mainMenu.slideDown();
                            });
                            self.currentSearchRequest = undefined;
                            self.isLoggedIn = false;
                        })
                        .on('fail', function (e, error) {
                            logger.log('error', 'login', 'logoutEvent::fail - error: ', error, e);
                            uiPrecallMenuShow(false, function () {
                                self.cache.$mainMenu.slideDown();
                            });
                            uiReportError("Failed to logout", error);
                            self.currentSearchRequest = undefined;
                            self.isLoggedIn = false;
                        });

                    self.events.disconnectEvent
                        .on('done', function () {
                            logger.log('info', 'call', 'disconnectEvent::done');
                            uiCallCleanup();
                            applicationCallCleanup();
                        })
                        .on('fail', function (event, error) {
                            logger.log('error', 'call', 'disconnectEvent::fail - error: ', error, event);
                            uiReportError("Failed to disconnect", error);
                            uiCallCleanup();
                            applicationCallCleanup();
                        });

                    self.events.muteUpdateEvent
                        .on('done', function (e, muteInfo) {
                            logger.log('info', 'configuration', 'muteUpdateEvent::done', e);

                            if (muteInfo.device === "speaker") {
                                uiSetSpeakerMuted(muteInfo.mute);
                            } else if (muteInfo.device === "microphone") {
                                uiSetMicMuted(muteInfo.mute);
                            } else if (muteInfo.device === "video") {
                                uiSetVideoMuted(muteInfo.mute);
                            } else {
                                logger.log('warning', 'configuration', 'self.events.muteUpdateEvent::done', "unknown device type");

                            }
                        });
                    self.events.fullscreenEvent
                        .on('done', function () {
                            logger.log('info', 'ui', 'fullscreenEvent::done');
                            self.cache.$inCallButtonFullscreen.removeClass(self.config.btnAltClass);
                            self.cache.$inCallButtonFullscreen.addClass(self.config.btnOnClass);
                        })
                        .on('cancel', function (event, error) {
                            logger.log('info', 'ui', 'fullscreenEvent::cancel ', error || "", event);
                            self.cache.$inCallButtonFullscreen.addClass(self.config.btnAltClass);
                            self.cache.$inCallButtonFullscreen.removeClass(self.config.btnOnClass);
                        });

                    self.events.portalParticipantUpdateEvent
                        .on('done', function (event, participants) {
                            logger.log('info', 'portal', 'portalParticipantUpdateEvent::done ', participants, event);
                            if (!self.cache.$preCallJoinMyRoomButton.data('popover')) {
                                self.cache.$preCallJoinMyRoomButton.popover({
                                    toggle: "popover",
                                    trigger: "hover",
                                    placement: "bottom",
                                    html: true,
                                    content: "",
                                    title: "My room information"
                                });
                            }
                            /* Update my room popover */
                            if (participants.total === 1) {
                                participants.Entity = [participants.Entity];
                            }
                            var cont = self.templates.preCallMyRoomTemplate(participants);
                            self.cache.$preCallJoinMyRoomButton.data('popover').options.content = cont;
                            if (self.cache.$preCallJoinMyRoomButton.data('popover').$tip) {
                                self.cache.$preCallJoinMyRoomButton.data('popover').$tip.find(".popover-content").html(cont);
                            }
                            if (participants.total > 0) {
                                self.cache.$preCallJoinMyRoomButton.addClass(self.config.btnChangingClass);
                            } else {
                                self.cache.$preCallJoinMyRoomButton.removeClass(self.config.btnChangingClass);
                            }
                        });

                    self.events.participantUpdateEvent
                        .on('done', function (event, participants) {
                            /* Apply handlebars template to data */
                            logger.log('info', 'call', 'participantUpdateEvent::done', participants, event);
                            var transformedParticipants = {
                                participants: participants
                            };

                            if (self.sessionInfo === undefined) {
                                transformedParticipants.sessionDisplayText = "Conference";
                            }
                            else {
                                transformedParticipants.sessionDisplayText = self.sessionInfo.sessionDisplayText.toLowerCase();
                            }

                            $.each(transformedParticipants.participants, function(p) {
                                p.isChatEnabled = self.config.enableChat;
                            });

                            uiParticipantsUpdateWithData(transformedParticipants);

                            /* Detect what participant left and what joined and notify about it */
                            if (self.currentParticipants && self.currentParticipants.length > 0) {
                                if (self.inConference) {
                                    /* Joined participants */
                                    /*jslint unparam: true*/
                                    $.each(participants, function (j, obj) {
                                        var found = false;
                                        var i;
                                        for (i = 0; i < self.currentParticipants.length; i++) {
                                            if (self.currentParticipants[i].uri === obj.uri) {
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (!found) {
                                            uiParticipantStatusNotify(obj.name, true);
                                        }
                                    });
                                    /*jslint unparam: false*/

                                    /* Left participants */
                                    /*jslint unparam: true*/
                                    $.each(self.currentParticipants, function (j, obj) {
                                        var found = false;
                                        var i;
                                        for (i = 0; i < participants.length; i++) {
                                            if (participants[i].uri === obj.uri) {
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (!found) {
                                            uiParticipantStatusNotify(obj.name, false);
                                        }
                                    });
                                    /*jslint unparam: false*/
                                }
                            }
                            self.currentParticipants = participants;
                        });

                    self.events.shareUpdateEvent
                        .on('done', function (event, shares) {
                            logger.log('info', 'call', 'shareUpdateEvent::done', event);
                            var transformedShares = {
                                shares: []
                            };
                            var i;
                            for (i = 0; i < shares.numApp; i++) {
                                transformedShares.shares.push({
                                    name: shares.remoteAppName[i],
                                    id: i,
                                    highlight: ((shares.numApp - 1) === i) ? true : false
                                });
                            }

                            uiSharesUpdateWithData(transformedShares);
                            /* Select last available share */
                            if (shares.numApp) {
                                clientSharesSetCurrent(shares.numApp - 1);
                            }
                        });

                    self.events.roomLockEvent
                        .on('done', function (event, isLocked) {
                            logger.log('info', 'portal', 'roomLockEvent::done', isLocked, event);
                            var button = self.cache.$inCallParticipantsList.find(self.config.inCallLockButtonClass);
                            var info = button.find(">i");
                            if (self.currentRoomOwnerId && (self.currentRoomOwnerId === self.myAccount.entityID)) {
                                button.removeClass(self.config.btnChangingClass);
                                button.data('locked', isLocked);
                                button.attr('title', isLocked ? "Click to unlock" : "Click to lock");
                                if (isLocked) {
                                    info.removeClass('icon-unlock');
                                    info.addClass('icon-lock');
                                    button.addClass(self.config.btnOffClass);
                                } else {
                                    info.removeClass('icon-lock');
                                    info.addClass('icon-unlock');
                                    button.removeClass(self.config.btnOffClass);
                                }
                            } else {
                                if (isLocked) {
                                    button.stop(true, true).show('fast');
                                } else {
                                    button.stop(true, true).hide('fast');
                                }
                            }
                        })
                        .on('fail', function (event, error) {
                            logger.log('error', 'portal', 'roomLockEvent::fail', error, event);
                            var button = self.cache.$inCallParticipantsList.find(self.config.inCallLockButtonClass);
                            button.removeClass(self.config.btnChangingClass);
                        });

                    self.events.recorderEvent
                        .on('start', function () {
                            logger.log('info', 'portal', 'recorderEvent::start');
                            var $recordButton = self.cache.$inCallParticipantsList.find(self.config.inCallRecordButtonClass);
                            if (self.currentRoomOwnerId && (self.currentRoomOwnerId === self.myAccount.entityID)) {
                                var $recordIcon = $recordButton.find(">i");
                                if ($recordButton.length) {
                                    $recordButton.removeClass(self.config.btnChangingClass);
                                    $recordButton.addClass(self.config.btnOffClass);
                                    $recordButton.attr("title", "Stop recording");
                                    $recordButton.data("record", true);
                                }
                                if ($recordIcon.length) {
                                    $recordIcon.removeClass('icon-record');
                                    $recordIcon.addClass('icon-stop-alt');
                                }
                            } else {
                                $recordButton.stop(true, true).show('fast');
                            }

                        })
                        .on('startFail', function () {
                            logger.log('error', 'portal', 'recorderEvent::startFail');
                            var $recordButton = $(self.cache.$inCallParticipantsList.find(self.config.inCallRecordButtonClass));
                            if (self.currentRoomOwnerId && (self.currentRoomOwnerId === self.myAccount.entityID)) {
                                if ($recordButton.length) {
                                    $recordButton.removeClass(self.config.btnChangingClass);
                                    $recordButton.addClass(self.config.btnOffClass);
                                }
                            } else {
                                $recordButton.stop(true, true).hide('fast');
                            }
                        })
                        .on('stop', function () {
                            logger.log('info', 'portal', 'recorderEvent::stop');
                            var $recordButton = self.cache.$inCallParticipantsList.find(self.config.inCallRecordButtonClass);
                            if (self.currentRoomOwnerId && (self.currentRoomOwnerId === self.myAccount.entityID)) {
                                var $recordIcon = $recordButton.find(">i");
                                if ($recordButton.length) {
                                    $recordButton.removeClass(self.config.btnChangingClass);
                                    $recordButton.removeClass(self.config.btnOffClass);
                                    $recordButton.attr("title", "Start recording");
                                    $recordButton.data("record", false);
                                }
                                if ($recordIcon.length) {
                                    $recordIcon.removeClass('icon-stop-alt');
                                    $recordIcon.addClass('icon-record');
                                }
                            } else {
                                $recordButton.stop(true, true).hide('fast');
                            }
                        })
                        .on('stopFail', function () {
                            logger.log('error', 'plugin', 'recorderEvent::stopFail');
                            var $recordButton = $(self.cache.$inCallParticipantsList.find(self.config.inCallRecordButtonClass));
                            if (self.currentRoomOwnerId && (self.currentRoomOwnerId === self.myAccount.entityID)) {
                                if ($recordButton.length) {
                                    $recordButton.removeClass(self.config.btnChangingClass);
                                    $recordButton.addClass(self.config.btnOffClass);
                                }
                            } else {
                                $recordButton.stop(true, true).hide('fast');
                            }
                        });

                    return self;
                };

                /**
                 * Binds UI events like button press, etc
                 * @return {Object} Application object
                 */
                applicationBindUIEvents = function () {

                    logger.log('info', 'application', 'applicationBindUIEvents()');


                    self.cache.$inCallButtonToggleConfig
                        .on('click', function () {
                            logger.log('info', 'ui', "inCallButtonToggleConfig::click");

                            self.cache.$inCallConfiguration.slideToggle();
                        });

                    self.cache.$preCallSearchNavigationList
                        .on('click', "a", function (e) {
                            logger.log('info', 'ui', "preCallSearchNavigationList::click");

                            var button = $(this);
                            var type = button.data('type');
                            logger.log('info', 'ui', "preCallSearchNavigationList::click - type: ", type, button);
                            if (type) {
                                if (!button.hasClass("disabled")) {
                                    var id = button.data('id');
                                    logger.log('info', 'ui', 'preCallSearchNavigationList::click - About to perform action with type:', type, "and id: ", id);
                                    if (type === "join") {
                                        self.currentRoomOwnerId = self.myAccount.entityID === button.data("ownerId");
                                        self.currentRoomId = id;
                                        self.isDirectCall = false;
                                        if (button.data('haspin')) {
                                            uiJoinConferencePinDialogShow();
                                        } else {
                                            self.isJoining = true;
                                            portalUserJoinConference(id);
                                            uiUpdateJoinProgress("5%", true);
                                        }
                                    } else if (type === "direct") {
                                        self.currentRoomOwnerId = self.myAccount.entityID === button.data("ownerId");
                                        self.isDirectCall = true;
                                        self.isJoining = true;
                                        portalUserCallDirect(id);
                                        uiUpdateJoinProgress("5%", true);
                                    } else if (type === "add") {
                                        helperPortalUsersStatusUpdateTimerStop();
                                        portalUserCancelSearchRequest();

                                        uiUserFavoriteAdd(id);
                                        portalUserFavoritePromiseToAdd(id)
                                            .done(function () {
                                                logger.log('info', 'ui', 'preCallSearchNavigationList::add::portalUserFavoritePromiseToAdd::done');
                                                helperPortalUsersStatusUpdateTimerStart(self.config.userRefreshTimeout);
                                            })
                                            .fail(function () {
                                                logger.log('info', 'ui', 'preCallSearchNavigationList::portalUserFavoritePromiseToAdd::fail - failed to add favorite to portal');
                                            });

                                    } else if (type === "remove") {
                                        helperPortalUsersStatusUpdateTimerStop();
                                        portalUserCancelSearchRequest();

                                        uiUserFavoriteRemove(id);
                                        portalUserFavoritePromiseToRemove(id)
                                            .done(function () {
                                                logger.log('info', 'ui', 'preCallSearchNavigationList::remove::portalUserFavoritePromiseToAdd::done');
                                                helperPortalUsersStatusUpdateTimerStart(self.config.userRefreshTimeout);
                                            })
                                            .fail(function () {
                                                logger.log('info', 'ui', 'preCallSearchNavigationList::portalUserFavoritePromiseToAdd::fail - failed to remove favorite from portal');
                                            });

                                    }
                                }
                            }
                            e.preventDefault();
                        });

                    self.cache.$inCallChatTabs.
                    on("click", "a", function (e) {
                        logger.log('info', 'ui', 'inCallChatTabs::click - ', e);
                        e.preventDefault();

                        var $this = $(this);
                        var uri;
                        if ('#' + $this.attr("id") === self.config.inCallChatMinimizeLink) {
                            var $i = $this.find(">i");
                            if ($this.data("minimized")) {
                                uiChatViewMinimize(false);
                                $i.removeClass("icon-chevron-up");
                                $i.addClass("icon-chevron-down");
                                $this.data("minimized", false);
                                var $activeTab = $(self.cache.$inCallChatTabs.find(".active")[0]);
                                uri = $activeTab.data('uri');
                                uiChatViewTabNotifyStop(uri);
                                self.cache.$inCallChatTextField.focus();
                            } else {
                                uiChatViewMinimize(true);
                                $i.removeClass("icon-chevron-down");
                                $i.addClass("icon-chevron-up");
                                $this.data("minimized", true);
                            }
                        } else {
                            $this.tab('show');
                            uri = $this.data("uri");
                            uiChatViewTabNotifyStop(uri);
                            /* Maximize chat view if needed */
                            if (self.cache.$inCallChatMinimizeLink.data("minimized")) {
                                self.cache.$inCallChatMinimizeLink.click();
                            }
                        }
                    });
                    self.cache.$inCallChatTabs.
                    on("shown", function (e) {
                        logger.log('info', 'ui', 'inCallChatTabs::shown - ', e);
                        uiChatViewScrollToPosition();
                        self.cache.$inCallChatTextField.focus();
                    });

                    self.cache.$inCallChatPanes.
                    scroll(function (e) {
                        logger.log('info', 'ui', 'inCallChatPanes::scroll - ', e);
                        var $activeTab = self.cache.$inCallChatTabs.find(".active");
                        if ((self.cache.$inCallChatPanes.scrollTop() + self.cache.$inCallChatPanes.outerHeight()) < self.cache.$inCallChatPanes[0].scrollHeight) {
                            $activeTab.data("noscroll", self.cache.$inCallChatPanes.scrollTop());
                            self.cache.$inCallChatPanes.data("inscroll", true);


                            if (self.chatScrollTimer) {
                                window.clearTimeout(self.chatScrollTimer);
                            }

                            self.chatScrollTimer = window.setTimeout(function () {
                                self.cache.$inCallChatPanes.data("inscroll", false);

                            }, 300);
                        } else {
                            $activeTab.data("noscroll", false);
                            self.cache.$inCallChatPanes.data("inscroll", false);
                        }
                    });

                    self.cache.$inCallChatTextField
                        .on('keyup', function (e) {
                            logger.log('info', 'ui', 'inCallChatTextField::keyup - ', e);
                            if (e.keyCode === 13) {
                                self.cache.$inCallChatTextSend.click();
                            }
                        });

                    self.cache.$inCallChatTextSend
                        .click(function (e) {
                            logger.log('info', 'ui', 'inCallChatTextSend::click - ', e);
                            var message = self.cache.$inCallChatTextField.val();
                            if (message.length > 0) {
                                var $activeTab = $(self.cache.$inCallChatTabs.find(".active")[0]);
                                var uri = $activeTab.data('uri');
                                if (uri === "group") {
                                    clientGroupChatSend(message);
                                    uiChatUpdateView({
                                        uri: "group",
                                        message: message,
                                        isGroup: true,
                                        isOutgoing: true
                                    });
                                } else {
                                    clientPrivateChatSend(uri, message);
                                    uiChatUpdateView({
                                        uri: uri,
                                        message: message,
                                        isGroup: false,
                                        isOutgoing: true
                                    });
                                }
                                self.cache.$inCallChatTextField.val("");
                            }
                        });

                    self.cache.$inCallChatTabs.
                    on("click", ".close", function (e) {
                        e.preventDefault();
                        e.stopPropagation();
                        var $a = $(this).parent();
                        var $li = $a.parent();
                        var uri = $li.data("uri");
                        var i;
                        var panes = self.cache.$inCallChatPanes.children(),
                            $pane,
                            isActive;

                        for (i = 0; i < panes.length; i++) {
                            $pane = $(panes[i]);
                            isActive = $pane.hasClass("active");
                            if ($pane.data("uri") === uri) {
                                // Select first tab as default
                                if (isActive) {
                                    self.cache.$inCallChatGroupTabLink.tab('show');
                                }
                                $pane.remove();
                                $li.remove();
                                break;
                            }
                        }
                    });

                    self.cache.$inCallParticipantsList
                        .on('click', "a", function (e) {
                            logger.log('info', 'ui', "inCallParticipantsList::click");

                            var button = $(this);
                            var type = button.data('type');
                            logger.log('info', 'ui', "inCallParticipantsList::click - type: ", type, button);
                            if (type) {
                                if (!button.hasClass("disabled")) {
                                    var uri = button.data('uri');
                                    logger.log('info', 'ui', 'inCallParticipantsList::click - About to perform action with type:', type, "and uri: ", uri);
                                    if (type === "pin") {
                                        var pin = button.data("pinned") ? false : true;
                                        button.addClass(self.config.btnChangingClass);
                                        clientParticipantPin(uri, pin);
                                    } else if (type === "info") {
                                        if (!button.data("popover")) {
                                            button.popover({
                                                trigger: "click",
                                                placement: "left",
                                                html: true,
                                                container: self.config.inCallContainer,
                                                content: button.data("content")
                                            });
                                            button.popover("show");
                                        }
                                    } else if (type === "chat") {
                                        var name = button.data('name');
                                        uiChatViewTabCreateIfNotExists(uri, name);
                                        uiChatViewTabSwitch(uri);
                                        self.cache.$inCallChatTextField.focus();
                                    } else if (type === "group_chat") {
                                        uiChatViewTabSwitch("group");
                                        self.cache.$inCallChatTextField.focus();
                                    } else if (type === "record") {
                                        if (self.recorderProfiles && self.recorderProfiles.total > 0) {
                                            /* Update UI to say that we are trying */
                                            var $recordButton = $(self.cache.$inCallParticipantsList.find(self.config.inCallRecordButtonClass));
                                            if ($recordButton.length) {
                                                $recordButton.removeClass(self.config.btnOffClass);
                                                $recordButton.addClass(self.config.btnChangingClass);
                                            }
                                            if (!$recordButton.data("record")) {
                                                /* Set default */
                                                var recorderPrefix = self.recorderProfiles.recorder[0].recorderPrefix;
                                                var i;
                                                for (i = 0; i < self.recorderProfiles.total; i++) {
                                                    if (self.config.defaultRecorderTypes.indexOf(self.recorderProfiles.recorder[i].description) !== -1) {
                                                        recorderPrefix = self.recorderProfiles.recorder[i].recorderPrefix;
                                                        break;
                                                    }
                                                }
                                                portalRecordStart(recorderPrefix, self.currentRoomId);
                                                logger.log('info', 'ui', "inCallParticipantsList::click::record - Starting with recorder ", recorderPrefix);

                                            } else {
                                                logger.log('info', 'ui', "inCallParticipantsList::click::record - Stopping recorder");
                                                portalRecordStop(self.currentRoomId);
                                            }
                                        } else {
                                            logger.log('warning', 'ui', "inCallParticipantsList::click::record - no recorders detected");
                                        }
                                    } else if (type === "lock") {
                                        var isLocked = (button.data("locked") === true);
                                        button.removeClass(self.config.btnOffClass);
                                        button.addClass(self.config.btnChangingClass);
                                        portalRoomPromiseToLock(self.currentRoomId, !isLocked)
                                            .done(function () {
                                                self.events.roomLockEvent.trigger('done', !isLocked);
                                            })
                                            .fail(function (error) {
                                                self.events.roomLockEvent.trigger('fail', error);
                                            });
                                    }
                                }
                            }
                            e.preventDefault();
                        });

                    self.cache.$preCallJoinMyRoomButton
                        .on('click', function () {
                            logger.log('info', 'ui', "preCallJoinMyRoomButton::click");
                            uiUpdateJoinProgress("5%", true);
                            self.currentRoomOwnerId = self.myAccount.entityID;
                            self.currentRoomId = self.myAccount.entityID;
                            self.isJoining = true;
                            portalUserJoinConference(self.myAccount.entityID);
                            self.isDirectCall = false;
                        })
                        .on('mouseenter', function () {
                            self.cache.$preCallJoinMyRoomButton.stop(true, true).popover('show');
                        })
                        .on('mouseleave', function () {
                            self.cache.$preCallJoinMyRoomButton.stop(true, true).popover('hide');
                        });

                    self.cache.$preCallLogoutButton
                        .on('click', function () {
                            logger.log('info', 'ui', "preCallLogoutButton::click");
                            clientUserLogout();
                        });

                    var lastSearchFieldValue = "";

                    self.cache.$preCallSearchField
                        .on('keyup', function (event) {
                            logger.log('info', 'ui', 'preCallSearchField::keyup - ', event);
                            /*
                                Don't search if the field's value did not change
                                for example because of control keys are pressed
                            */
                            if (self.cache.$preCallSearchField.val() === lastSearchFieldValue) {
                                return;
                            }
                            lastSearchFieldValue = self.cache.$preCallSearchField.val();
                            /* Cancel previous request */
                            portalUserCancelSearchRequest();
                            uiSearchProgressShow();
                        })
                        .typeWatch({
                            callback: function () {
                                logger.log('info', 'ui', 'typewatch');

                                var query = self.cache.$preCallSearchField.val();
                                if (query !== "") {
                                    portalUserSearchBothFavAndUsers(true, query);
                                } else {
                                    portalUserSearchBothFavAndUsers(false);
                                }
                            },
                            wait: self.config.searchDelay,
                            highlight: true,
                            captureLength: 1
                        });

                    self.cache.$userLoginButton
                        .on('click', function () {
                            logger.log('info', 'ui', "userLoginButton::click");

                            uiDesktopNotificationRequestPermission();

                            if (self.cache.$userLoginButton.hasClass('disabled')) {
                                return;
                            }
                            logger.log('info', 'ui', "userLoginButton::click - proceeding");

                            var inEventLoginParams = {};

                            self.isGuestLogin = false;

                            inEventLoginParams.portalUri = self.cache.$userLoginPortal.val();
                            inEventLoginParams.userName = self.cache.$userLoginUsername.val();
                            inEventLoginParams.userPass = self.cache.$userLoginPassword.val();

                            self.cache.$userLoginErrorWrapper.hide();
                            self.cache.$userLoginButton.addClass('disabled');

                            if (clientUserLogin(inEventLoginParams) !== undefined) {
                                logger.log('info', 'ui', "userLoginButton::click - sent user login request");
                                self.loginInfo = $.extend({}, self.loginInfo, inEventLoginParams);
                                helperPersistentStorageSetValue('loginInfo', self.loginInfo);
                                uiUpdateUserLoginProgress(self.config.progressStepInPercents + "%", true);
                            }
                        });

                    /* Guest login button is clicked */
                    self.cache.$guestLoginButton
                        .on('click', function () {
                            logger.log('info', 'ui', "guestLoginButton::click");
                            if (self.cache.$guestLoginButton.hasClass('disabled')) {
                                return;
                            }
                            logger.log('info', 'ui', "guestLoginButton::click - proceeding");
                            uiDesktopNotificationRequestPermission();

                            var inEventLoginParams = {};

                            self.isGuestLogin = true;
                            // Test http://dev20.vidyo.com/flex.html?roomdirect.html&key=U6AnrCjEaMBx
                            inEventLoginParams.fullURI = self.cache.$guestURL.val();

                            /* Split full URI into tokens that Vidyo Client library understands */
                            var fullURIArray = inEventLoginParams.fullURI.split('flex.html?roomdirect.html&key=');
                            inEventLoginParams.portalUri = fullURIArray[0];
                            inEventLoginParams.roomKey = fullURIArray[1];

                            inEventLoginParams.guestName = self.cache.$guestName.val();
                            inEventLoginParams.pin = self.cache.$guestPIN.val();

                            self.cache.$guestLoginButton.addClass('disabled');
                            self.cache.$guestLoginErrorWrapper.hide();
                            self.isJoining = true;
                            if (clientGuestLoginAndJoin(inEventLoginParams) !== undefined) {
                                logger.log('info', 'ui', 'guestLoginButton::click - sent guest login request');
                                /* Store login info to persistence */
                                self.guestLoginInfo = $.extend({}, self.guestLoginInfo, inEventLoginParams);
                                self.myAccount = {
                                    displayName: inEventLoginParams.guestName
                                };
                                helperPersistentStorageSetValue('guestLoginInfo', self.guestLoginInfo);

                                /* Start progress bar update */
                                uiUpdateGuestLoginProgress(self.config.progressStepInPercents + "%", true);
                            }
/*p2 added
							self.cache.$inCallButtonMuteVideo.click(); */
                        });

                    self.cache.$plugin
                        .ready(function () {
                            logger.log('info', 'plugin', "plugin::ready");
                            /* Resolve deferred variable */
                            self.events.pluginPreloadEvent.resolve();
                        });


                    self.cache.$plugin
                        .on('error', function () {
                            logger.log('warning', 'plugin', "plugin::error");
                            /* Reject deferred variable */
                            self.events.pluginPreloadEvent.reject("Failed to load");
                        });

                    /**
                     * Process keyup event from all the login inputs to enable login
                     * button when there is some data in all fields
                     */
                    self.cache.$userLoginInputs
                        .on('keyup', function (e) {
                            logger.log('info', 'ui',"userLoginInputs::keyup - ", e);

                            /* Enable login button if all fields are set correctly */
                            if (self.cache.$userLoginPortal.val().length &&
                                self.cache.$userLoginUsername.val().length &&
                                self.cache.$userLoginPassword.val().length
                            ) {
                                self.cache.$userLoginButton.removeClass('disabled');
                                /* Emulate click on enter */
                                if (e.keyCode === 13) {
                                    self.cache.$userLoginButton.click();
                                }
                            } else {
                                self.cache.$userLoginButton.addClass('disabled');
                            }
                        });

                    /**
                     * Process keyup event from all the login inputs to enable login
                     * button when there is some data in all fields
                     */
                    self.cache.$guestLoginInputs
                        .on('keyup', function (e) {
                            logger.log('info', 'ui',"guestLoginInputs::keyup - ", e);

                            /* Enable login button if all fields are set correctly */
                            if (self.cache.$guestURL.val().length && self.cache.$guestName.val().length) {
                                self.cache.$guestLoginButton.removeClass('disabled');
                                /* Emulate click on enter */
                                if (e.keyCode === 13) {
                                    self.cache.$guestLoginButton.click();
                                }
                            } else {
                                self.cache.$guestLoginButton.addClass('disabled');
                            }
                        });

                    /* In call buttons events */

                    /* Prevent UI jumping */
                    self.cache.$inCallContainer
                        .click(function (e) {
                            e.preventDefault();
                        });

                    /**
                     * Show or hide participants' list.
                     */
                    self.cache.$inCallButtonParticipants
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonParticipants::click");
                            /*
                             * If visible hide and slide panel so it disappears.
                             * If not visible slide panel to the left so it appears.
                             */
                            if (self.cache.$inCallParticipantsPanel.is(":visible")) {
                                uiParticipantsPromiseToSlide(false);
                            } else {
                                uiParticipantsPromiseToSlide(true);
                            }
                        });

                    self.cache.$inCallButtonMuteVideo
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonMuteVideo::click");
                            self.isMutedVideo = !self.isMutedVideo;
                            clientVideoMute(self.isMutedVideo);
                        });

                    self.cache.$inCallButtonMuteSpeaker
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonMuteSpeaker::click");
                            self.isMutedSpeaker = !self.isMutedSpeaker;
                            clientSpeakerMute(self.isMutedSpeaker);
                        });

                    self.cache.$inCallButtonMuteMicrophone
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonMuteMicrophone::click");
                            self.isMutedMic = !self.isMutedMic;
                            clientMicrophoneMute(self.isMutedMic);
                        });

                    self.cache.$inCallButtonShare
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonShare::click");
                        });

                    self.cache.$inCallButtonLocalShare
                        .click(function (e) {
                            logger.log('info', 'ui',"inCallButtonLocalShare::click", e);
                            var data = clientLocalSharesGet();
                            var transformedData = {
                                windows: [],
                                desktops: [],
                                sharing: (self.currentShareId === undefined) ? false : true
                            };
                            var i,
                                name,
                                mywindow,
                                desktop;
                            for (i = 0; i < data.numApplicationWindows; i++) {
                                name = (data.appWindowAppName[i] && data.appWindowAppName[i].length) ? data.appWindowAppName[i] : data.appWindowName[i];
                                mywindow = {
                                    id: data.appWindowId[i],
                                    name: name,
                                    highlight: (self.currentShareId === data.appWindowId[i]) ? true : false
                                };
                                transformedData.windows.push(mywindow);
                            }

                            for (i = 0; i < data.numSystemDesktops; i++) {
                                desktop = {
                                    id: data.sysDesktopId[i],
                                    name: data.sysDesktopName[i],
                                    highlight: (self.currentShareId === data.sysDesktopId[i]) ? true : false
                                };
                                transformedData.desktops.push(desktop);
                            }

                            uiLocalSharesUpdateWithData(transformedData);
                        });

                    self.cache.$inCallButtonToggleLayout
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonToggleLayout::click");
                            clientLayoutToggle();
                        });

                    self.cache.$inCallButtonFullscreen
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonFullscreen::click");
                            self.isFullscreen = !self.isFullscreen;
                            if (self.isFullscreen) {
                                uiFullscreenSet(self.cache.$inCallContainer.get()[0]);
                            } else {
                                uiFullscreenCancel();
                            }
                        });

                    self.cache.$inCallButtonTogglePreview
                        .click(function (e) {
                            logger.log('info', 'ui',"inCallButtonTogglePreview::click");
                            e.preventDefault();
                            clientPreviewModeSet($(e.target).data("mode"));
                        });

                    self.cache.$inCallButtonDisconnect
                        .click(function () {
                            logger.log('info', 'ui',"inCallButtonDisconnect::click");
                            clientConferenceLeave();
                        });

                    /* Optimize mute event. Use one mute event for the whole button panel. */
                    self.cache.$inCallButtonPanel
                        .on('mute', function (e, isMuted) {
                            logger.log('info', 'ui',"inCallButtonTogglePreview::mute");
                            if (isMuted) {
                                $(e.target).addClass(self.config.btnOffClass);
                                $(e.target).removeClass(self.config.btnOnClass);
                            } else {
                                $(e.target).removeClass(self.config.btnOffClass);
                                $(e.target).addClass(self.config.btnOnClass);
                            }
                        });

                    self.cache.$inCallShareList
                        .click(function (event) {
                            logger.log('info', 'ui',"inCallShareList::click");
                            var target = $(event.target);
                            var id = target.data('id');
                            clientSharesSetCurrent(id);
                            uiShareSelect(target);
                        });

                    self.cache.$inCallLocalShareList
                        .click(function (event) {
                            logger.log('info', 'ui',"inCallLocalShareList::click");
                            var target = $(event.target);
                            var id = target.data('id');
                            clientLocalShareStart(id);
                            self.currentShareId = id;
                            if (self.currentShareId !== undefined) {
                                self.cache.$inCallButtonLocalShare.removeClass(self.config.btnAltClass);
                                self.cache.$inCallButtonLocalShare.addClass(self.config.btnOnClass);
                            } else {
                                self.cache.$inCallButtonLocalShare.removeClass(self.config.btnOnClass);
                                self.cache.$inCallButtonLocalShare.addClass(self.config.btnAltClass);
                            }
                        });

                    self.cache.$guestLoginPopup
                        .on("show", function () {
                            logger.log('info', 'ui',"guestLoginPopup::shown");
                            logger.log('info', 'ui',"guestLoginPopup::shown - guestLoginInfo", self.guestLoginInfo);

                            /* Fill out inputs if information is cached */

                            if (self.guestLoginInfo.fullURI) {
                                self.cache.$guestURL.val(self.guestLoginInfo.fullURI);
                            }

                            if (self.guestLoginInfo.guestName) {
                                self.cache.$guestName.val(self.guestLoginInfo.guestName);
                            }

                            if (self.guestLoginInfo.pin) {
                                self.cache.$guestPIN.val(self.guestLoginInfo.pin);
                            }

                            self.cache.$guestURL.focus();
                            self.cache.$guestURL.get()[0].select();

                            /* Enable login button if all fields are there */
                            if (self.cache.$guestURL.val().length && self.cache.$guestName.val().length) {
                                self.cache.$guestLoginButton.removeClass('disabled');
                                self.cache.$guestLoginButton.focus();
                            } else {
                                self.cache.$guestLoginButton.addClass('disabled');
                            }
                        })
                        .on("hidden", function () {
                            logger.log('info', 'ui',"guestLoginPopup::hidden");
                            /* Reset error report view */
                            self.cache.$guestLoginErrorWrapper.hide();
                        });

                    self.cache.$userLoginPopup
                        .on("show", function () {
                            logger.log('info', 'ui',"userLoginPopup::shown");

                            /* Fill out inputs if information is cached */
                            if (self.loginInfo.portalUri) {
                                self.cache.$userLoginPortal.val(self.loginInfo.portalUri);
                            }
                            if (self.loginInfo.userName) {
                                self.cache.$userLoginUsername.val(self.loginInfo.userName);
                            }
                            if (self.loginInfo.userPass) {
                                self.cache.$userLoginPassword.val(self.loginInfo.userPass);
                            }


                            /* Enable login button if all fields are there */
                            if (self.cache.$userLoginPortal.val().length &&
                                self.cache.$userLoginUsername.val().length &&
                                self.cache.$userLoginPassword.val().length
                            ) {
                                self.cache.$userLoginButton.removeClass('disabled');
                                self.cache.$userLoginButton.focus();
                            } else {
                                self.cache.$userLoginButton.addClass('disabled');
                                self.cache.$userLoginPortal.focus();
                                self.cache.$userLoginPortal.get()[0].select();
                            }
                        })
                        .on("hidden", function () {
                            logger.log('info', 'ui',"userLoginPopup::hidden");
                            /* Reset error report view */
                            self.cache.$userLoginErrorWrapper.hide();
                        });

                    self.cache.$preCallIntitePopup
                        .on("shown", function () {
                            logger.log('info', 'ui',"preCallIntitePopup::shown");

                            /* Workaroud for bootstrap bug on Chrome */
                            if (self.cache.$preCallIntitePopup.data('hide')) {
                                logger.log('info', 'ui',"preCallIntitePopup::shown - hiding");
                                self.cache.$preCallIntitePopup.modal('hide');
                                self.cache.$preCallIntitePopup.hide();
                            }
                        });

                    /* Handle selection of different input device */
                    self.cache.$configurationContainer
                        .on("change", function (event, obj) {
                            logger.log('info', 'ui',"configurationContainer::change", event, obj);
                            var target = $(event.target),
                                selection = target.val(),
                                isChecked = target.prop("checked") ? 1 : 0;

                            var conf = clientConfigurationGet();
                            /* From VidyoClientParameters.h */
                            var PROXY_VIDYO_FORCE = 1,
                                PROXY_WEB_ENABLE = (1 << 3),
                                PROXY_WEB_IE = (1 << 4);


                            if (target.attr("name") === "Speaker") {
                                conf.currentSpeaker = selection;
                            } else if (target.attr("name") === "Camera") {
                                conf.currentCamera = selection;
                            } else if (target.attr("name") === "Microphone") {
                                conf.currentMicrophone = selection;
                            } else if (target.attr("name") === "SelfViewLoopbackPolicy") {
                                conf.selfViewLoopbackPolicy = selection;
                            } else if (target.attr("name") === "EchoCancel") {
                                conf.enableEchoCancellation = isChecked;
                            } else if (target.attr("name") === "AutoGain") {
                                conf.enableAudioAGC = isChecked;
                            } else if (target.attr("name") === "AlwaysProxy") {
                                /* Set or unset bits in the bit mask */
                                if (isChecked) {
                                    conf.proxySettings |= PROXY_VIDYO_FORCE;
                                } else {
                                    conf.proxySettings &= ~PROXY_VIDYO_FORCE;
                                }
                            } else if (target.attr("name") === "UseWebProxy") {
                                /* Set or unset bits in the bit mask */
                                if (isChecked) {
                                    conf.proxySettings |= (PROXY_WEB_ENABLE | PROXY_WEB_IE);
                                } else {
                                    conf.proxySettings &= ~(PROXY_WEB_ENABLE | PROXY_WEB_IE);
                                }
                            } else if (target.attr("name") === "HideParticipants") {
                                conf.enableShowConfParticipantName = isChecked ? 0 : 1;
                            } else if (target.attr("name") === "MuteMicrophone") {
                                conf.enableMuteMicrophoneOnJoin = isChecked;
                            } else if (target.attr("name") === "HideCamera") {
                                conf.enableHideCameraOnJoin = isChecked;
                            } else if (target.attr("name") === "LogsApplication") {
                                helperPersistentStorageSetValue("log.logsApplication", !! isChecked);
                                self.logConfig.enableAppLogs = !! isChecked;
                                logger.enable( !! isChecked);
                            } else if (target.attr("name") === "LogsJS") {
                                helperPersistentStorageSetValue("log.logsJS", !! isChecked);
                                self.logConfig.enableVidyoPluginLogs = !! isChecked;
                            } else if (target.attr("name") === "LogsClient") {
                                helperPersistentStorageSetValue("log.logsClient", !! isChecked);
                                self.logConfig.enableVidyoClientLogs = !! isChecked;
                                if (self.logConfig.enableVidyoClientLogs) {
                                    var $input = $(self.config.configurationLogLevelsAndCategoriesInput);
                                    var value = $input.val();
                                    logger.log('debug', 'configuration', "Changing log levels and categories", isChecked, value);
                                    helperPersistentStorageSetValue("log.levelsAndCategories", value);
                                    clientLogLevelsAndCategoriesSet(value);
                                    self.logConfig.logLevelsAndCategories = value;
                                }
                            } else if (target.attr("name") === "LogLevelsAndCategories") {
                                var $input = $(self.config.configurationLogLevelsAndCategoriesInput);
                                var value = $input.val();
                                logger.log('debug', 'configuration', "Changing log levels and categories", isChecked, value);
                                helperPersistentStorageSetValue("log.levelsAndCategories", value);
                                clientLogLevelsAndCategoriesSet(value);
                                self.logConfig.logLevelsAndCategories = value;
                            }
                            clientConfigurationSet(conf);
                        });

                    /* Handle invites */
                    self.cache.$preCallIntitePopupButtonAccept
                        .click(function () {
                            logger.log('info', 'ui',"preCallIntitePopupButtonAccept::click");
                            clientIncomingCallAccept();
                            uiIncomingCallNotificationDismiss();
                        });

                    self.cache.$preCallIntitePopupButtonReject
                        .click(function () {
                            logger.log('info', 'ui',"preCallIntitePopupButtonReject::click");
                            clientIncomingCallReject();
                            uiIncomingCallNotificationDismiss();
                        });

                    self.cache.$preCallJoinConferencePinDialogPIN
                        .on('keyup', function (e) {
                            logger.log('info', 'ui','preCallJoinConferencePinDialogPIN::keyup - ', e);
                            if (e.keyCode === 13) {
                                e.stopPropagation();
                                e.preventDefault();
                                self.cache.$preCallJoinConferencePinDialogButton.click();
                            }
                        });

                    self.cache.$preCallJoinConferencePinDialogButton
                        .on('click', function (e) {
                            logger.log('info', 'ui',"preCallJoinConferencePinDialogButton::click", e);
                            var PIN = self.cache.$preCallJoinConferencePinDialogPIN.val();
                            self.cache.$preCallJoinConferencePinDialog.modal('hide');
                            // Using timer as a workaround. This is generally not a good idea as it is not deterministic.
                            setTimeout(function() {
                                logger.log('debug', 'ui', "self.cache.$preCallJoinConferencePinDialogButton");
                                self.isJoining = true;
                                portalUserJoinConference(self.currentRoomId, PIN);
                            }, 500);
                        });

                    self.cache.$preCallJoinConferencePinDialog
                        .on('shown', function () {
                            logger.log('info', 'ui',"preCallJoinConferencePinDialog::shown");
                            self.cache.$preCallJoinConferencePinDialogPIN.val("");
                            self.cache.$preCallJoinConferencePinDialogPIN.focus();
                        });

                    /* Handle user actions */
                    self.cache.$preCallSearchNavigationList
                        .on("mouseenter", self.config.preCallSearchUserClass, function (e) {
                            logger.log('debug', 'ui',"preCallSearchUserClass::mouseenter", e);
                            var $this = $(this);
                            var $buttons = $($this.find(".btn-toolbar")[0]);
                            $buttons.stop(true, true).fadeIn('fast');
                        })
                        .on("mouseleave", self.config.preCallSearchUserClass, function (e) {
                            logger.log('debug', 'ui',"preCallSearchUserClass::mouseleave", e);
                            var $this = $(this);
                            var $buttons = $($this.find(".btn-toolbar")[0]);
                            $buttons.stop(true, true).fadeOut('fast');

                        });

                    self.cache.$inCallParticipantsList
                        .on("mouseenter", self.config.inCallParticipantsClass, function (e) {
                            logger.log('debug', 'ui',"inCallParticipantsList::mouseenter", e);
                            var $this = $(this);

                            /* Make div with name shorter so button toolbar fits */
                            var $nameDiv = $this.find(".inCallParticipantNameDiv");
                            var $buttons = $this.find(".btn-toolbar");
                            $nameDiv.addClass("short").promise().done(function () {
                                $buttons.stop(true, true).show(100, function () {
                                    $nameDiv.stop(true, true).addClass("short");
                                });
                            });

                        })
                        .on("mouseleave", self.config.inCallParticipantsClass, function (e) {
                            logger.log('debug', 'ui',"inCallParticipantsList::mouseleave", e);
                            var $this = $(this);


                            var $buttons = $($this.find(".btn-toolbar")[0]);
                            var $nameDiv = $this.find(".inCallParticipantNameDiv");
                            var $infoButton = $this.find(self.config.inCallParticipantInfoButtonClass);

                            if ($infoButton.data("popover")) {
                                $infoButton.popover("hide");
                            }

                            $buttons.hide(100, function () {
                                $nameDiv.stop(true, true).removeClass("short");
                            });
                        });


                    /* Detect fullscreen mode change
                     * Not all browsers fully support this.
                     * Standard is not yet approved so browser specific events are used.
                     */
                    $(document)
                        .on("mozfullscreenchange", function () {
                            logger.log('info', 'ui',"document.mozfullscreenchange");
                            if (!document.mozFullScreen) {
                                self.events.fullscreenEvent.trigger("cancel");
                            } else {
                                self.events.fullscreenEvent.trigger("done");
                            }
                        })
                        .on("webkitfullscreenchange", function () {
                            logger.log('info', 'ui',"document.webkitfullscreenchange");
                            if (!document.webkitFullscreenElement) {
                                self.events.fullscreenEvent.trigger("cancel");
                            } else {
                                self.events.fullscreenEvent.trigger("done");
                            }
                        })
                        .on("msfullscreenchange", function () {
                            logger.log('info', 'ui',"document.msfullscreenchange");
                            if (!document.msFullscreenElement) {
                                self.events.fullscreenEvent.trigger("cancel");
                            } else {
                                self.events.fullscreenEvent.trigger("done");
                            }
                        })
                        .on("oldmsfullscreenchange", function () {
                            logger.log('info', 'ui',"document.oldmsfullscreenchange");
                            if (!self.isFullscreen) {
                                self.events.fullscreenEvent.trigger("cancel");
                            } else {
                                self.events.fullscreenEvent.trigger("done");
                            }
                        })
                        .on("fullscreenchange", function () {
                            logger.log('info', 'ui',"document.fullscreenchange");
                            if (!document.fullscreenElement) {
                                self.events.fullscreenEvent.trigger("cancel");
                            } else {
                                self.events.fullscreenEvent.trigger("done");
                            }
                        });
                    /* Bootstrap fix for closing modal windows on blur */
                    $(window).blur(function () {
                        $('.modal').removeClass('fade');
                    });
                    $(window).focus(function () {
                        $('.modal').addClass('fade');
                    });
                    return self;
                };

                /**
                 * Loads saved application information like login information from
                 * persistent store.
                 * @return {Object} Application object
                 */
                applicationLoadCacheFromPersistentStore = function () {
                    logger.log('info', 'application',"applicationLoadCacheFromPersistentStore()");

                    /* Get login info */
                    self.loginInfo = helperPersistentStorageGetValue('loginInfo') || {};
                    logger.log('debug', 'application','applicationLoadCacheFromPersistentStore::loginInfo: ', self.loginInfo);

                    self.guestLoginInfo = helperPersistentStorageGetValue('guestLoginInfo') || {};
                    logger.log('debug', 'application','applicationLoadCacheFromPersistentStore::guestLoginInfo: ', self.guestLoginInfo);

                    /* Get self-view mode */
                    self.currentPreviewMode = helperPersistentStorageGetValue('previewMode') || self.config.defaultPreviewMode;
                    logger.log('debug', 'application','applicationLoadCacheFromPersistentStore::previewMode: ', self.currentPreviewMode);

                    self.logConfig.enableAppLogs = (helperPersistentStorageGetValue("log.logsApplication") !== undefined) ? helperPersistentStorageGetValue("log.logsApplication") : self.config.enableAppLogs;
                    logger.enable(self.logConfig.enableAppLogs);
                    self.logConfig.enableVidyoPluginLogs = (helperPersistentStorageGetValue("log.logsJS") !== undefined) ? helperPersistentStorageGetValue("log.logsJS") : self.config.enableVidyoPluginLogs;
                    self.logConfig.enableVidyoClientLogs = (helperPersistentStorageGetValue("log.logsClient") !== undefined) ? helperPersistentStorageGetValue("log.logsClient") : self.config.enableVidyoClientLogs;
                    self.logConfig.logLevelsAndCategories = (helperPersistentStorageGetValue("log.levelsAndCategories") !== undefined) ? helperPersistentStorageGetValue("log.levelsAndCategories") : self.config.defaultLogLevelsAndCategories;

                    return self;
                };

                /**
                 * Master function to bind all asynchronous events
                 * @return {Object} Application object
                 */
                applicationBindEvents = function () {
                    logger.log('info', 'application', 'applicationBindEvents()');

                    applicationBindUIEvents();
                    applicationBindSubscribeEvents();
                    applicationBindVidyoCallbacks();

                    return self;
                };

                /**
                 * Starts UI view
                 * @return {Object} Application object
                 */
                uiStart = function () {
                    logger.log('info', 'ui','uiStart()');
                    uiShowInCallContainerMinimizedAndWithPlugin();
                    return self;
                };

                /**
                 * Update configuration data and make it do appear
                 * @param  {Object} data Configuration data
                 * @return {Object} Application object
                 */
                uiConfigurationUpdateWithData = function (data) {
                    logger.log('info', 'ui','uiConfigurationUpdateWithData()');
                    var htmlData = self.templates.configurationTemplate(data);
                    self.cache.$configurationContainer.html(htmlData);
                    return self;
                };

                /**
                 * Update users in user navigation list
                 * @param  {Object} data Object with information about users
                 * @return {Object} Application object
                 */
                uiUserNavigationUpdateWithData = function (data) {
                    logger.log('info', 'portal','uiUserNavigationUpdateWithData(', data, ')');
                    /* Gently update data without refreshing the whole view */
                    var navHeaders = self.cache.$preCallSearchNavigationList.find(self.config.liHeader);
                    var users = self.cache.$preCallSearchNavigationList.find("li.user");
                    var firstNavHeader = navHeaders[0];
                    var htmlData;

                    if (!firstNavHeader) {
                        htmlData = self.templates.preCallSearchTemplate(data);
                        self.cache.$preCallSearchNavigationList.html(htmlData);
                    } else {
                        var allUsers = $.extend([], data.fav, data.user);
                        var totalNum = allUsers.length;
                        var i, j;
                        var $user, found;
                        var innerHtml,
                            $userHomeButton,
                            $userDirectButton,
                            $userFavButton,
                            $userFavButtonInner;
                        /* Update UI elements */
                        for (i = 0; i < totalNum; i++) {
                            for (j = 0; j < users.length; j++) {
                                $user = users[j] ? $(users[j]) : undefined;
                                if ($user && $user.data("id") === allUsers[i].id) {
                                    innerHtml = self.templates.preCallSearchJustUserTemplate(allUsers[i]);
                                    $user.find('.userName').html(innerHtml);
                                }
                                if ($user && $user.data("id") === allUsers[i].id) {
                                    $userHomeButton = $($user.find(".preCallSearchListUserButtonRoom")[0]);
                                    $userDirectButton = $($user.find(".preCallSearchListUserButtonDirect")[0]);
                                    $userFavButton = $($user.find(".preCallSearchListUserButtonFav")[0]);
                                    $userDirectButton.addClass("disabled");
                                    if (allUsers[i].isOnline) {
                                        if (allUsers[i].isBusy) {
                                            $userDirectButton.attr('title', "Direct call is not available");
                                        } else {
                                            $userDirectButton.removeClass("disabled");
                                            $userDirectButton.attr('title', "Call " + allUsers[i].name + " directly");
                                        }
                                    }

                                    if (allUsers[i].isOccupied) {
                                        $userHomeButton.addClass(self.config.btnChangingClass);
                                    } else {
                                        $userHomeButton.removeClass(self.config.btnChangingClass);
                                    }
                                    if (allUsers[i].isRoomFull) {
                                        $userHomeButton.attr('title', 'Room of ' + allUsers[i].name + ' if full');
                                        $userHomeButton.addClass('disabled');
                                    } else if (allUsers[i].isLocked) {
                                        $userHomeButton.attr('title', 'Room of ' + allUsers[i].name + ' if locked');
                                        $userHomeButton.addClass('disabled');
                                    } else {
                                        $userHomeButton.attr('title', 'Go to the room of ' + allUsers[i].name);
                                        $userHomeButton.removeClass('disabled');
                                    }

                                    $userFavButtonInner = $userFavButton.find(">:first-child");

                                    if (allUsers[i].inFav) {
                                        $userFavButtonInner.removeClass(self.config.preCallAddUserIcon);
                                        $userFavButtonInner.addClass(self.config.preCallRemoveUserIcon);
                                        $userFavButton.removeClass(self.config.btnOnClass);
                                        $userFavButton.addClass(self.config.btnOffClass);
                                        $userFavButton.data("type", "remove");
                                        $userFavButton.attr("title", "Remove from favorites");

                                    } else {
                                        $userFavButtonInner.removeClass(self.config.preCallRemoveUserIcon);
                                        $userFavButtonInner.addClass(self.config.preCallAddUserIcon);
                                        $userFavButton.removeClass(self.config.btnOffClass);
                                        $userFavButton.addClass(self.config.btnOnClass);
                                        $userFavButton.data("type", "add");
                                        $userFavButton.attr("title", "Add to favorites");
                                    }
                                }
                            }
                        }

                        /* Remove non-existent users and add new ones */
                        var favUsers = self.cache.$preCallSearchNavigationList.find("li.favUser");
                        var lastFavUsers = favUsers;
                        var $lastFav;
                        for (i = 0; i < data.fav.length; i++) {
                            found = false;
                            for (j = 0; j < lastFavUsers.length; j++) {
                                $user = $(lastFavUsers[j]);
                                if ($user.data("id") === data.fav[i].id) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                /* Adding new fav */
                                htmlData = self.templates.preCallSearchUserTemplate(data.fav[i]);
                                if (lastFavUsers.length > 0) {
                                    $lastFav = $(lastFavUsers).last();
                                    $lastFav.after(htmlData);
                                    if (!$lastFav.data("id")) {
                                        $lastFav.remove();
                                    }

                                } else {
                                    $(firstNavHeader).after(htmlData);
                                }
                                lastFavUsers = self.cache.$preCallSearchNavigationList.find("li.favUser");
                            }
                        }

                        for (j = 0; j < favUsers.length; j++) {
                            found = false;
                            $user = $(favUsers[j]);
                            found = false;
                            for (i = 0; i < data.fav.length; i++) {
                                if ($user.data("id") === data.fav[i].id) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found && $user.data("id")) { // remove
                                /* removing old fav */
                                $user.remove();
                            }
                        }
                        /* Update count in badge */
                        var badge = $($(firstNavHeader).find(".badge")[0]);
                        if (data.fav.length) {
                            badge.html(String(data.fav.length));
                        } else {
                            badge.html("");
                        }

                    }
                    return self;
                };

                /**
                 * Promise to slide and show participants list
                 * @param  {Boolean} show Show participants list when true or undefined or hide when false
                 * @return {Object} Deferred jQuery promise object
                 */
                uiParticipantsPromiseToSlide = function (show) {
                    /* Toggle participant list panel */
                    logger.log('info', 'ui','uiParticipantsPromiseToSlide(', show, ')');
                    var sidePanelWidth = self.cache.$inCallParticipantsPanel.outerWidth(true);

                    self.isShowingParticipantList = !self.isShowingParticipantList;

                    if (self.isShowingParticipantList && (show || show === undefined)) {
                        logger.log('info', 'ui','uiParticipantsPromiseToSlide() - fullpage');
                        self.cache.$inCallParticipantsPanel.fadeIn();
                        self.cache.$inCallPluginAndControls.removeClass("fullscreenNoParticipantPanel");
                        self.cache.$inCallPluginAndControls.addClass("fullscreen");
                        self.cache.$inCallContainer.css({
                            'min-width': '+=' + sidePanelWidth
                        });
                    } else if (!self.isShowingParticipantList && show === false) {
                        logger.log('info', 'ui','uiParticipantsPromiseToSlide() - fullpage');
                        self.cache.$inCallParticipantsPanel.fadeOut(function () {
                            self.cache.$inCallContainer.css({
                                'min-width': '-=' + sidePanelWidth
                            });
                            self.cache.$inCallPluginAndControls.removeClass("fullscreen");
                            self.cache.$inCallPluginAndControls.addClass("fullscreenNoParticipantPanel");
                        });
                    } else {
                        logger.log('info', 'ui','uiParticipantsPromiseToSlide() - bad state');
                        self.isShowingParticipantList = !self.isShowingParticipantList;
                    }
                };

                /**
                 * Show pre-call UI
                 * @param  {Boolean} show       True - show, false - hide
                 * @param  {Function} onDone    Call when pre-call UI is show/hide is done
                 * @return {Object}             Application object
                 */
                uiPrecallMenuShow = function (show, onDone) {
                    logger.log('info', 'ui','uiPrecallMenuShow(' + show + ')');
                    if (show) {
                        self.cache.$preCallContainer.slideDown(onDone);
                        helperPortalUsersStatusUpdateTimerStart(self.config.userRefreshTimeout);
                    } else {
                        helperPortalUsersStatusUpdateTimerStop(self.config.userRefreshTimeout);
                        self.cache.$preCallContainer.slideUp(onDone);
                    }
                    return self;
                };

                /**
                 * Set UI for microphone mute state
                 * @param  {Boolean} mute true for mute state and false for not mute state
                 * @return {Object}             Application object
                 */
                uiSetMicMuted = function (mute) {
                    logger.log('info', 'ui','uiSetMicMuted()');
                    self.cache.$inCallButtonMuteMicrophone.trigger('mute', mute);
                    return self;
                };

                /**
                 * Set UI for speaker mute state
                 * @param  {Boolean} mute true for mute state and false for not mute state
                 * @return {Object}             Application object
                 */
                uiSetSpeakerMuted = function (mute) {
                    logger.log('info', 'ui','uiSetSpeakerMuted()');
                    self.cache.$inCallButtonMuteSpeaker.trigger('mute', mute);
                    return self;
                };

                /**
                 * Set UI for camera mute state
                 * @param  {Boolean} mute true for mute state and false for not mute state
                 * @return {Object}             Application object
                 */
                uiSetVideoMuted = function (mute) {
                    logger.log('info', 'ui','uiSetVideoMuted()');
                    self.cache.$inCallButtonMuteVideo.trigger('mute', mute);
                    return self;
                };

                /**
                 * Report guest login error
                 * @param  {String} error Error string
                 * @return {Object} Application object
                 */
                uiReportGuestLoginError = function (error) {
                    logger.log('info', 'ui','uiReportGuestLoginError()');

                    self.cache.$guestLoginError.html(error);
                    self.cache.$guestLoginErrorWrapper.fadeIn();
                    return self;
                };

                /**
                 * Report user login error
                 * @param  {String} error Error string
                 * @return {Object} Application object
                 */
                uiReportUserLoginError = function (error) {
                    logger.log('info', 'ui','uiReportUserLoginError()');

                    self.cache.$userLoginError.html(error);
                    self.cache.$userLoginErrorWrapper.fadeIn();
                    return self;
                };

                /**
                 * Report user PIN error
                 * @param  {String} error Error string
                 * @return {Object} Application object
                 */
                uiReportJoinConferencePinError = function (error) {
                    logger.log('info', 'ui','uiReportJoinConferencePinError()');

                    self.cache.$preCallJoinConferencePinDialogError.html(error);
                    self.cache.$preCallJoinConferencePinDialogErrorWrapper.fadeIn();
                    return self;
                };

                /**
                 * Update chat view with new message
                 * @param  {Object} chatEvent Data with new message
                 * @return {Object} Application object
                 */
                uiChatUpdateView = function (chatEvent) {
                    logger.log('info', 'ui','uiChatUpdateView(', chatEvent, ')');
                    var participants = clientParticipantsGet();

                    /* Get from participant */
                    var participantName;
                    var chatTargetParticipant;
                    var endpointId;
                    /* Extract EndpointId */
                    if (chatEvent.uri !== "group") {
                        endpointId = chatEvent.uri.split("scip:")[1].split(";")[0];
                    }
                    /* Name for message sender */
                    if (chatEvent.isOutgoing) {
                        participantName = self.myAccount.displayName;
                    }
                    /*  Get corresponding participant for a message.
                        For a group message just ignore it.
                     */
                    if (chatEvent.uri !== "group") {
                        var i;
                        for (i = 0; i < participants.length; i++) {
                            if (chatEvent.uri === participants[i].uri) {
                                if (!chatEvent.isOutgoing) {
                                    participantName = participants[i].name;
                                }
                                chatTargetParticipant = participants[i];
                                break;
                            }
                        }
                    }

                    if (participantName === undefined || (chatEvent.uri !== "group" && chatTargetParticipant === undefined)) {
                        logger.log('warning', 'ui',"uiChatUpdateView() - did not find participant with URI ", chatEvent.uri);
                    }

                    var pane = [];
                    var tab = [];

                    if (chatEvent.isGroup) {
                        pane = self.cache.$inCallChatGroupPane;
                        tab = self.cache.$inCallChatGroupTab;
                    } else {
                        uiChatViewTabCreateIfNotExists(chatTargetParticipant.uri, participantName);
                        pane = $("#chatPane" + endpointId);
                        tab = $("#chatTab" + endpointId);
                    }
                    /* Prepare data structure for templates */
                    var data = {
                        uri: chatTargetParticipant ? chatTargetParticipant.uri : "group",
                        endpointId: endpointId,
                        name: participantName,
                        time: (new Date()).toLocaleTimeString(),
                        message: chatEvent.message,
                        isOutgoing: chatEvent.isOutgoing
                    };
                    /* Add message to the pane */
                    var $ul = pane.find("ul");
                    var htmlMessage = self.templates.inCallChatPaneMessageTemplate(data);
                    $ul.append(htmlMessage);
                    if (tab.hasClass("active")) {
                        if (chatEvent.isOutgoing) {
                            tab.data("noscroll", false);
                        }
                        uiChatViewScrollToPosition();
                        if (self.cache.$inCallChatMinimizeLink.data("minimized")) {
                            if (chatEvent.isGroup) {
                                uiChatViewTabNotifyStart("group");
                            } else {
                                uiChatViewTabNotifyStart(chatTargetParticipant.uri);
                            }
                        }
                    } else {
                        uiChatViewTabNotifyStart(chatTargetParticipant.uri);
                    }

                };

                /**
                 * Create new chat tab and pane if does not exists for a particular user
                 * @param  {Object} uri Participant URI to associate with
                 * @param  {Object} name Participant name to associate with
                 * @return {Object} Application object
                 */
                uiChatViewTabCreateIfNotExists = function (uri, name) {
                    logger.log('info', 'ui','uiChatViewTabCreateIfNotExists(', uri, name, ')');
                    var endpointId;
                    /* Extract EndpointId */
                    if (uri !== "group") {
                        endpointId = uri.split("scip:")[1].split(";")[0];
                    }

                    if (endpointId === undefined) {
                        logger.log('warning', 'ui',"uiChatViewTabCreateIfNotExists() - did not create tab for URI ", uri);
                        return self;
                    }

                    var tab = [];

                    tab = $("#chatTab" + endpointId);
                    /* Prepare data structure for templates */
                    var data = {
                        uri: uri,
                        endpointId: endpointId,
                        name: name
                    };
                    /*  If no tab for a user exist - create one and append to the end of tab list,
                        also create a pane.
                     */
                    if (tab.length === 0) {
                        var htmlTab = self.templates.inCallChatTabTemplate(data);
                        var htmlPane = self.templates.inCallChatPaneTemplate(data);
                        self.cache.$inCallChatTabs.append(htmlTab);
                        self.cache.$inCallChatPanes.append(htmlPane);
                    }
                    return self;
                };

                /**
                 * Switch tab to a particular user.
                 * @param  {Object} uri Participant URI to associate with
                 * @param  {Object} name Participant name to associate with
                 * @return {Object} Application object
                 */
                uiChatViewTabSwitch = function (uri) {
                    logger.log('info', 'ui','uiChatViewTabSwitch(', uri, ')');
                    var tab;
                    if (uri === "group") {
                        tab = self.cache.$inCallChatGroupTab;
                    } else {
                        var endpointId = uri.split("scip:")[1].split(";")[0];
                        tab = $("#chatTab" + endpointId);
                    }
                    tab.find(">a").click();
                    self.cache.$inCallChatTextField.focus();
                    return self;
                };

                uiChatViewTabNotifyStart = function (uri) {
                    logger.log('info', 'ui','uiChatViewTabNotifyStart(', uri, ')');

                    var endpointId,
                        tab;
                    /* Extract EndpointId */
                    if (uri !== "group") {
                        endpointId = uri.split("scip:")[1].split(";")[0];
                    } else {
                        endpointId = "group";
                    }

                    if (uri === "group") {
                        tab = self.cache.$inCallChatGroupTab;
                    } else {
                        tab = $("#chatTab" + endpointId);
                    }

                    /* Add message notification */
                    tab = tab.find(">a");
                    tab.addClass("notify");
                    var missed = parseInt(tab.data("missed"), 10) | 0;
                    var badge = tab.find(">.badge");
                    missed += 1;
                    tab.data("missed", missed);
                    badge.html(String(missed));
                    badge.show();
                    return self;
                };

                uiChatViewTabNotifyStop = function (uri) {
                    logger.log('info', 'ui','uiChatViewTabNotifyStop(', uri, ')');
                    var endpointId;
                    if (!uri) {
                        return undefined;
                    }
                    /* Extract EndpointId */
                    if (uri !== "group") {
                        endpointId = uri.split("scip:")[1].split(";")[0];
                    } else {
                        endpointId = "group";
                    }

                    var tab;

                    if (uri === "group") {
                        tab = self.cache.$inCallChatGroupTab;
                    } else {
                        tab = $("#chatTab" + endpointId);
                    }

                    tab = tab.find(">a");
                    tab.removeClass("notify");
                    tab.data("missed", 0);
                    var badge = tab.find(">.badge");
                    badge.hide();
                    return self;
                };
                /**
                 * Scroll chat view to the bottom when chat view is allowed to.
                 * @param  {Boolean} isShown If undefined don't change user login popup state. True - show if was hidden. False - hide if was shown.
                 * @return {Object} Application object
                 */
                uiChatViewScrollToPosition = function () {
                    logger.log('info', 'ui','uiChatViewScrollToPosition()');

                    var $activeTab = self.cache.$inCallChatTabs.find(".active");
                    /* Don't apply scrolling when user recently scrolled */
                    if (!self.cache.$inCallChatPanes.data("inscroll")) {
                        if ($activeTab.data("noscroll") === false) {
                            self.cache.$inCallChatPanes.scrollTop(self.cache.$inCallChatPanes[0].scrollHeight);
                        } else {
                            self.cache.$inCallChatPanes.scrollTop($activeTab.data("noscroll"));
                        }
                    }
                    return self;
                };

                /**
                 * Update UI state for user login.
                 * Update progress bar and show/hide user login popup as needed.
                 * @param  {String} progress Optional percent of progress to show
                 * @param  {Boolean} isShown If undefined don't change user login popup state. True - show if was hidden. False - hide if was shown.
                 * @return {Object} Application object
                 */
                uiUpdateUserLoginProgress = function (progress, isShown) {
                    logger.log('info', 'ui','uiUpdateUserLoginProgress(' + progress + ', ' + isShown + ')');

                    self.cache.$userLoginProgressBar.width(progress);

                    if (isShown === undefined) {
                        return;
                    }

                    if (self.cache.$userLoginProgressContainer.is(":visible")) {
                        if (!isShown) {
                            self.cache.$userLoginProgressContainer.fadeOut();
                        }
                    } else {
                        if (isShown) {
                            self.cache.$userLoginProgressContainer.fadeIn();
                        }
                    }
                    return self;
                };

                /**
                 * Update UI state for guest login.
                 * Update progress bar and show/hide guest login popup as needed.
                 * @param  {String} progress Optional percent of progress to show
                 * @param  {Boolean} isShown If undefined don't change guest login popup state. True - show if was hidden. False - hide if was shown.
                 * @return {Object} Application object
                 */
                uiUpdateGuestLoginProgress = function (progress, isShown) {
                    logger.log('info', 'ui','uiUpdateGuestLoginProgress(' + progress + ', ' + isShown + ')');

                    self.cache.$guestProgressBar.width(progress);
                    if (isShown === undefined) {
                        return;
                    }

                    if (self.cache.$guestProgressBarContainer.is(":visible")) {
                        if (!isShown) {
                            self.cache.$guestProgressBarContainer.fadeOut();
                        }
                    } else {
                        if (isShown) {
                            self.cache.$guestProgressBarContainer.fadeIn();
                        }
                    }
                    return self;
                };

                /**
                 * Update UI state for conference ended.
                 * Update UI elements to a precall state.
                 * @return {Object} Application object
                 */
                uiCallCleanup = function () {
                    logger.log('info', 'ui','uiCallCleanup()');
                    if (self.isFullscreen) {
                        uiFullscreenCancel();
                    }
                    if (self.isGuestLogin || self.isLoggedIn) {
                        uiInCallShow(true, false);

                        if (self.isGuestLogin) {
                            self.cache.$mainMenu.slideDown(function () {
                                self.cache.$configurationContainer.slideDown();
                            });
                        } else {
                            uiPrecallMenuShow(true, function () {
                                self.cache.$configurationContainer.slideDown();
                            });
                        }
                        if (self.config.enableChat) {
                            /* Clean up chat tabs and panes */
                            self.cache.$inCallChatTabs.find(".close").click();
                            self.cache.$inCallChatGroupPane.find("ul").html("");
                        }
                        if (self.isGuestLogin || self.isLoggedIn) {
                            uiInCallShow(false);
                        }
                    }
                    self.cache.$guestProgressBar.data("step", 0);
                    self.cache.$preCallJoinProgressBar.data("step", 0);
                    return self;
                };


                /**
                 * Update UI state for conference join progress.
                 * Update progress bar and show/hide it as needed.
                 * @param  {String} progress Optional percent of progress to show
                 * @param  {Boolean} isShown If undefined don't change conference join popup state. True - show if was hidden. False - hide if was shown.
                 * @return {Object} Application object
                 */
                uiUpdateJoinProgress = function (progress, isShown) {
                    logger.log('info', 'ui','uiUpdateJoinProgress(' + progress + ', ' + isShown + ')');

                    self.cache.$preCallJoinProgressBar.width(progress);
                    if (isShown === undefined) {
                        return;
                    }

                    if (self.cache.$preCallJoinAsUserPopup.is(":visible")) {
                        if (!isShown) {
                            self.cache.$preCallJoinAsUserPopup.modal('hide');
                        }
                    } else {
                        if (isShown) {
                            self.cache.$preCallJoinAsUserPopup.modal('show');
                        }
                    }
                    return self;
                };

                /**
                 * Shows plugin in minimized form.
                 * Browser will not enable plugin if it is not visible,
                 * so we show plugin in a view's default minimized state.
                 * @return {Object} Application object
                 */
                uiShowInCallContainerMinimizedAndWithPlugin = function () {
                    logger.log('info', 'ui','uiShowInCallContainerMinimizedAndWithPlugin()');

                    /* We need to make sure about:
                     * 1. Plugin is loaded
                     * 2. Plugin is visible
                     * So when we make plugin visible then we start it after deferred
                     * variable for plugin ready event is resolved.
                     */
                    self.cache.$inCallContainer.show(function () {

                        self.events.pluginPreloadEvent
                            .done(function () {
                                logger.log('info', 'ui',"uiShowInCallContainerMinimizedAndWithPlugin - plugin is ready and visible initializing");
                                vidyoPluginInitAndStart();
                            })
                            .fail(function () {
                                logger.log('warning', 'ui',"uiShowInCallContainerMinimizedAndWithPlugin - Failed to load plugin");
                            });
                    });

                    return self;
                };

                /**
                 * Start plugin detection
                 *
                 * @return None
                 */
                uiStartPluginDetection = function (runWhenDetected) {
                    logger.log('info', 'ui','uiStartPluginDetection(' + runWhenDetected + ')');
                    var reloadPage = false;
                    /* Check if installed */
                    if (vidyoPluginIsInstalled()) {
                        /* Check for browser blockade */
                        if (runWhenDetected) {
                            /* Load plugin into dome */
                            vidyoPluginLoad();
                            /* Check if loaded. In case it was not loaded it is likely blockaded by browser */
                            if (vidyoPluginIsLoaded()) {
                                logger.log('info', 'ui','uiStartPluginDetection() -- plugin is found and loaded - reloading page');
                                if (vidyoPluginIsStarted()) { // started already
                                    self.events.pluginLoadedEvent.trigger('fail', "Another instance is running?");
                                } else { // not started yet
                                    if (vidyoPluginStart()) {
                                        self.events.pluginLoadedEvent.trigger('done');
                                    } else { //failed to start
                                        self.events.pluginLoadedEvent.trigger('fail', "Failed to start Vidyo Library");
                                    }
                                }
                                return;
                            }
                        } else {
                            logger.log('info', 'ui','uiStartPluginDetection() -- plugin is found, reloading');
                            /* IE and Safari does not like loading plugin in the same page after install so reloading page */
                            location.reload();
                            return;
                        }
                    }
                    /* in case of no plugin detected, try again */
                    window.setTimeout(function () {
                            uiStartPluginDetection(runWhenDetected);
                        },
                        self.config.pluginDetectionTimeout);
                    return;
                };

                /**
                 * Highlight selected share
                 * @param  {Object} target jQuery object to apply highlighting style
                 * @return {Object} Application object
                 */
                uiShareSelect = function (target) {
                    logger.log('info', 'ui','uiShareSelect(', target, ')');
                    /* Remove highlight from previously highlighted items */
                    /*jslint unparam: true*/
                    $.each($("." + self.config.inCallSelectedShareClass), function (i, obj) {
                        $(obj).removeClass(self.config.inCallSelectedShareClass);
                    });
                    /*jslint unparam: false*/
                    /* Add highlight on a clicked item */
                    target.addClass(self.config.inCallSelectedShareClass);
                    return self;
                };

                /**
                 * Show search progress element
                 * @return {Object} Application object
                 */
                uiSearchProgressShow = function () {
                    logger.log('info', 'ui','uiSearchProgressShow()');
                    self.cache.$preCallSearchNavigationList.html(self.templates.preCallSearchProgressTemplate());
                    //self.cache.$preCallSearchNavigationList.slideUp()
                    return self;
                };

                /**
                 * Update remote shares list in UI
                 * @param  {Object} data Information about shares
                 * @return {Object} Application object
                 */
                uiSharesUpdateWithData = function (data) {
                    logger.log('info', 'ui','uiSharesUpdateWithData(', data, ')');
                    var htmlData = self.templates.inCallSharesTemplate(data);
                    /* Show new data */
                    self.cache.$inCallShareList.html(htmlData);
                    /* Disable shares button if no shares available */
                    if (data.shares.length) {
                        self.cache.$inCallButtonShare.removeClass('disabled');
                    } else {
                        self.cache.$inCallButtonShare.addClass('disabled');
                    }
                    return self;
                };

                /**
                 * Resets UI state for local share
                 * @return {Object} Application object
                 */
                uiLocalShareReset = function () {
                    logger.log('info', 'ui','uiLocalShareReset()');
                    self.currentShareId = undefined;
                    self.cache.$inCallButtonLocalShare.removeClass(self.config.btnOnClass);
                    self.cache.$inCallButtonLocalShare.addClass(self.config.btnAltClass);
                };

                /**
                 * Update local shares list in UI
                 * @param  {Object} data Information about shares
                 * @return {Object} Application object
                 */
                uiLocalSharesUpdateWithData = function (data) {
                    logger.log('info', 'ui','uiLocalSharesUpdateWithData(', data, ')');
                    var htmlData = self.templates.inCallLocalSharesTemplate(data);
                    /* Show new data */
                    self.cache.$inCallLocalShareList.html(htmlData);
                    return self;
                };

                /**
                 * Update participant list in UI
                 * @param  {Object} data Information about participants
                 * @return {Object} Application object
                 */
                uiParticipantsUpdateWithData = function (data) {
                    logger.log('info', 'ui','uiParticipantsUpdateWithData(', data, ')');

                    /* Gently update data without refreshing the whole view */
                    var navHeaders = self.cache.$inCallParticipantsList.find(self.config.liHeader);
                    var viewParticipants = self.cache.$inCallParticipantsList.find(self.config.inCallParticipantsClass);
                    var firstNavHeader = navHeaders[0];
                    var participants = data.participants;
                    var i, j;
                    var $participant, found, htmlData;
                    /* add information about recorder availability */
                    data.isOwner = self.currentRoomOwnerId ? (self.currentRoomOwnerId === self.myAccount.entityID) : false;
                    data.isRecordable = self.recorderProfiles && (self.recorderProfiles.total > 0);
                    data.isChatEnabled = self.config.enableChat;

                    if (!firstNavHeader) {
                        htmlData = self.templates.inCallParticipantsTemplate(data);
                        /* Show new data */
                        self.cache.$inCallParticipantsList.html(htmlData);
                        /* Update recording state */
                        var recState = clientRecordAndWebcastStateGet();
                        if (recState && recState.recording) {
                            self.events.recorderEvent.trigger("start");
                        } else {
                            self.events.recorderEvent.trigger("stop");
                        }
                        if (data.isOwner) {
                            uiParticipantEnableInvite();
                        }
                    } else {
                        var totalNum = participants.length;
                        var $participantInfo,
                            cont;
                        self.cache.$inCallParticipantHeaderName.html(data.sessionDisplayText);
                        /* Update UI elements */
                        for (i = 0; i < totalNum; i++) {
                            for (j = 0; j < viewParticipants.length; j++) {
                                $participant = viewParticipants[j] ? $(viewParticipants[j]) : undefined;

                                if ($participant && $participant.data("uri") === participants[i].uri) {
                                    $participantInfo = $participant.find(self.config.inCallParticipantInfoButtonClass);
                                    cont = self.templates.inCallParticipantInfoTemplate(participants[i]);
                                    if ($participantInfo.data('popover')) {
                                        $participantInfo.data('popover').options.html = true;
                                        $participantInfo.data('popover').options.content = cont;
                                        if ($participantInfo.data('popover').$tip) {
                                            $participantInfo.data('popover').$tip.find(".popover-content").html(cont);
                                        }
                                    } else {
                                        $participantInfo.data("content", cont);
                                    }
                                }
                            }
                        }

                        /* Remove non-existent participant and add new ones */

                        /* Here we add participants */
                        var $lastParticipant;
                        for (i = 0; i < data.participants.length; i++) {
                            found = false;
                            for (j = 0; j < viewParticipants.length; j++) {
                                $participant = $(viewParticipants[j]);
                                if ($participant.data("uri") === data.participants[i].uri) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                /* Adding new participants */
                                data.participants[i].isChatEnabled = self.config.enableChat;
                                htmlData = self.templates.inCallParticipantTemplate(data.participants[i]);
                                if (viewParticipants.length > 0) {
                                    $lastParticipant = $(viewParticipants).last();
                                    $lastParticipant.after(htmlData);
                                } else {
                                    $(firstNavHeader).after(htmlData);
                                }

                            }
                        }

                        /* Here we remove participants */
                        for (j = 0; j < viewParticipants.length; j++) {
                            $participant = $(viewParticipants[j]);
                            found = false;
                            for (i = 0; i < data.participants.length; i++) {
                                if ($participant.data("uri") === data.participants[i].uri) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found && $participant.data("uri")) { // remove
                                /* removing old participant */
                                $participant.remove();
                            }
                        }
                    }
                    /* Update count in badge */
                    self.cache.$inCallButtonParticipantsBadge.html(String(data.participants.length));
                    return self;
                };

                /**
                 * Show and hide in-call elements.
                 * @param  {Boolean} show true - show, false - hide
                 * @param  {Boolean} inFullpage true - full page, false - fixed page
                 * @return {Object} Application object
                 */
                uiInCallShow = function (show, inFullpage) {
                    logger.log('info', 'ui','uiInCallShow(', show, inFullpage, ')');
                    if (show) {
                        self.cache.$pluginContainer.removeClass("off");
                        if (self.config.enableChat) {
                            self.cache.$inCallChatContainer.show();
                        } else {
                            if (!self.cache.$pluginContainer.hasClass("nochat")) {
                                self.cache.$pluginContainer.addClass("nochat");
                            }
                        }
                        if (inFullpage) { // Configure for full page
                            self.cache.$inCallContainer.removeClass("container");

                            self.cache.$inCallContainer.addClass("fullscreen");
                            /* Apply wider class when participant list is not shown */
                            if (self.isShowingParticipantList) {
                                self.cache.$inCallPluginAndControls.addClass("fullscreen");
                            } else {
                                self.cache.$inCallPluginAndControls.addClass("fullscreenNoParticipantPanel");
                            }

                            self.cache.$inCallButtonPanel.addClass("fullscreen");
                            self.cache.$inCallParticipantsPanel.addClass("fullscreen");
                            self.cache.$pluginAndChatContainer.addClass("fullscreen");
                            self.cache.$pluginContainer.addClass("fullscreen");
                            if (self.config.enableChat) {
                                self.cache.$inCallChatContainer.addClass("fullscreen");
                            }

                            self.cache.$pluginAndChatContainer.css("width", "auto");
                            self.cache.$inCallContainer.css("width", "auto");
                            self.cache.$pluginAndChatContainer.css("height", "100%");
                            self.cache.$inCallPluginAndControls.css("width", "auto");
                        } else { // configure for static size
                            self.cache.$inCallContainer.addClass("container");

                            self.cache.$inCallContainer.removeClass("fullscreen");
                            self.cache.$inCallPluginAndControls.removeClass("fullscreen");
                            self.cache.$inCallPluginAndControls.removeClass("fullscreenNoParticipantPanel");
                            self.cache.$inCallButtonPanel.removeClass("fullscreen");
                            self.cache.$inCallParticipantsPanel.removeClass("fullscreen");
                            self.cache.$pluginAndChatContainer.removeClass("fullscreen");
                            self.cache.$pluginContainer.removeClass("fullscreen");
                            if (self.config.enableChat) {
                                self.cache.$inCallChatContainer.removeClass("fullscreen");
                            }
                            self.cache.$inCallContainer.css("width", self.cache.$inCallContainer.css("min-width"));
                            self.cache.$inCallPluginAndControls.css("width", self.config.pluginWidth + self.cache.$inCallButtonPanel.outerWidth(true));
                            self.cache.$pluginAndChatContainer.css("width", self.config.pluginWidth);
                            self.cache.$pluginAndChatContainer.css("height", self.config.pluginHeight);

                        }

                        self.cache.$inCallContainer.css('height', "auto");
                        self.cache.$inCallContainer.css('padding', "20px");
                        self.cache.$pluginAndChatContainer.css("min-width", self.config.pluginWidth / 2);
                        self.cache.$pluginAndChatContainer.css("min-height", self.config.pluginHeight / 2);
                        self.cache.$plugin.addClass("fullscreen");

                        if (self.isShowingParticipantList) {
                            self.cache.$inCallParticipantsPanel.show();
                        }
                        self.cache.$inCallContainer.addClass('well well-large');

                        self.cache.$inCallButtonPanel.fadeIn();
                        self.cache.$inCallButtonShareBadge.hide();
                        uiChatViewMinimize(true);
                    } else {
                        self.cache.$pluginContainer.removeClass();
                        self.cache.$pluginContainer.addClass("off");
                        if (self.config.enableChat) {
                            self.cache.$inCallChatContainer.hide();
                        }
                        self.cache.$pluginAndChatContainer.css("min-width", 0);
                        self.cache.$pluginAndChatContainer.css("min-height", 0);
                        self.cache.$inCallButtonPanel.hide();
                        self.cache.$plugin.removeClass("fullscreen");
                        self.cache.$inCallContainer.removeClass('well well-large');
                        self.cache.$inCallContainer.css('padding', 0);
                        self.cache.$inCallContainer.css('height', "1px");
                        self.cache.$pluginAndChatContainer.css("height", "1px");
                        self.cache.$pluginAndChatContainer.css("width", "1px");
                        self.cache.$inCallParticipantsPanel.hide();
                    }
                    return self;
                };

                /**
                 * Engage close buttom processing
                 * @return {Object} Application object
                 */
                uiReportCloseEngage = function() {
                    logger.log('info', 'ui','uiReportCloseEngage()');
                    /* Extension to hide alerts instead of dismissing them */
                    $("[data-hide]")
                        .on("click", function(){
                            logger.log('debug', 'ui',"data-hide:click");
                            var $this = $(this);
                            $this.closest("." + $this.attr("data-hide")).hide();
                        });
                    return self;
                };

                /**
                 * Show error in UI
                 * @param  {String} error   Short error description
                 * @param  {String} details Details about error
                 * @return {Object} Application object
                 */
                uiReportError = function (error, details) {
                    logger.log('info', 'ui','uiReportError(', error, ", ", details, ')');

                    var htmlData = self.templates.errorTemplate({
                        error: error,
                        details: details
                    });

                    self.cache.$errorWrapper.html(htmlData);
                    self.cache.$errorWrapper.fadeIn();
                    uiReportCloseEngage();

                    return self;
                };

                /**
                 * Show information message in UI
                 * @param  {String} title   Short information description
                 * @param  {String} details Details
                 * @return {Object} Application object
                 */
                uiReportInfo = function (title, details) {
                    logger.log('info', 'ui','uiReportInfo(', title, ", ", details, ')');

                    var htmlData = self.templates.infoTemplate({
                        title: title,
                        details: details
                    });

                    self.cache.$infoWrapper.html(htmlData);
                    self.cache.$infoWrapper.fadeIn();
                    uiReportCloseEngage();
                    return self;
                };

                /**
                 * Hide information message in UI
                 * @param  {String} title   Short information description
                 * @param  {String} details Details
                 * @return {Object} Application object
                 */
                uiReportInfoDismiss = function () {
                    logger.log('info', 'ui','uiReportInfoDismiss()');
                    self.cache.$infoWrapper.html("");
                    self.cache.$infoWrapper.hide();
                    return self;
                };

                /**
                 * Minimizes or maximizes chat view
                 * @param  {Boolean} minimize   true - minimize, false - maximize
                 * @return {Object} Application object
                 */
                uiChatViewMinimize = function (minimize) {
                    logger.log('info', 'ui','uiChatViewMinimize(', minimize, ')');
                    if (minimize) {
                        self.cache.$pluginContainer.addClass('maximized');
                        self.cache.$inCallChatContainer.addClass('minimized');
                        self.cache.$inCallChatPanes.hide();
                        self.cache.$inCallChatForm.hide();
                    } else {
                        self.cache.$pluginContainer.removeClass('maximized');
                        self.cache.$inCallChatContainer.removeClass('minimized');
                        self.cache.$inCallChatPanes.show();
                        self.cache.$inCallChatForm.show();
                    }
                    return self;
                };

                /**
                 * Show participant notification message
                 * @param  {String} name   Name of the participant
                 * @param  {Boolean} isJoined True - join, false - left
                 * @return {Object} Application object
                 */
                uiParticipantStatusNotify = function (name, isJoined) {
                    logger.log('info', 'ui','uiParticipantStatusNotify(', name, isJoined, ')');

                    var statusText = isJoined ? "joined" : "left";
                    var type = isJoined ? "success" : "warning";
                    uiGenericNotify("<strong>" + name + "</strong>" + " " + statusText, type, self.config.notificationUserStatusTimeout);
                    /* Send desktop notification */
                    uiDesktopNotification("VidyoWeb - participant " + statusText, name + " " + statusText + " the conference at " + (new Date()).toLocaleTimeString(), self.config.notificationUserStatusTimeout);

                    return self;
                };

                /**
                 * Show generic notification message
                 * @param  {String} message   Short notification message
                 * @param  {String} style Can be any bootstrap style like "warning", "success", etc
                 * @param  {Integer} timeout Dismiss after timeout in ms. 0 - don't dismiss
                 * @return {Object} Application object
                 */
                uiGenericNotify = function (message, style, timeout) {
                    logger.log('info', 'ui','uiGenericNotify(', message, style, timeout, ')');
                    if (self.config.enableNotifications) {
                        if (timeout === undefined) {
                            timeout = self.config.notificationDefaultTimeout;
                        }
                        self.cache.$notificationContainer.notify({
                            message: {
                                html: message
                            },
                            type: style,
                            fadeOut: {
                                enabled: (timeout > 0),
                                delay: timeout
                            }
                        }).show();
                    }

                    return self;
                };

                /**
                 * Notifies UI about missed call
                 * @return {Object} Application object
                 */
                uiIncomingCallMissedCallNotify = function () {
                    logger.log('info', 'ui','uiIncomingCallMissedCallNotify()');
                    if (self.missedCallNotification) {
                        var count = self.missedCallNotification.count + 1;

                        var message = "Missed call from " + self.invitee;
                        if (count === 1) {
                            message += " and one other";
                        } else {
                            message += " and " + count + " others";
                        }
                        self.missedCallNotification.cancel();
                        self.missedCallNotification = uiDesktopNotification(
                            "VidyoWeb - missed call - " + (new Date()).toLocaleTimeString(),
                            message, 0);
                        self.missedCallNotification.count = count;
                    } else {
                        self.missedCallNotification = uiDesktopNotification("VidyoWeb - missed call - " + (new Date()).toLocaleTimeString(), "Missed call from " + self.invitee, 0);
                        self.missedCallNotification.count = 0;
                    }
                    return self;
                };

                /**
                 * Post desktop notification.
                 * Will focus page on click. Currently works in the latest Chrome, Safari and Firefox only.
                 *
                 * @param  {String} title Title for notification
                 * @param  {String} message   Short notification message
                 * @param  {Integer} timeout Dismiss after timeout in ms. 0 - don't dismiss
                 * @param  {Function} onClick Function to execute on click
                 * @return {Object} Notification object on success, undefined on failure
                 */
                uiDesktopNotification = function (title, message, timeout, onClick) {
                    logger.log('info', 'ui','uiDesktopNotification(', title, message, timeout, ')');
                    var notification;
                    if (!self.config.enableDesktopNotifications) {
                        return undefined;
                    }

                    if (timeout === undefined) {
                        timeout = 5000;
                    }
                    if (window.webkitNotifications) {
                        logger.log('info', 'ui','uiDesktopNotification() - supported webkit');
                        if (window.webkitNotifications.checkPermission() === 0) { // 0 is PERMISSION_ALLOWED
                            notification = window.webkitNotifications.createNotification(
                                'favicon.ico', title, message);
                            notification.message = message;

                            notification.onclick = function () {
                                window.focus();
                                notification.cancel();
                                if (onClick) {
                                    onClick();
                                }
                            };

                            notification.show();

                            if (timeout > 0) {
                                setTimeout(function () {
                                    notification.cancel();
                                }, timeout);
                            }
                        } else {
                            logger.log('warning', 'ui','uiDesktopNotification() - don\'t have permissions for webkit');
                        }
                    } else if (window.Notification) {
                        logger.log('info', 'ui','uiDesktopNotification() - supported HTML5');
                        if (window.Notification.permission.toLowerCase() === "granted") {
                            notification = new window.Notification(title, {
                                icon: 'favicon.ico',
                                body: message
                            });
                            notification.message = message;

                            notification.onclick = function () {
                                window.focus();
                                notification.close();
                                if (onClick) {
                                    onClick();
                                }
                            };

                            if (timeout > 0) {
                                setTimeout(function () {
                                    notification.close();
                                }, timeout);
                            }
                        } else {
                            logger.log('warning', 'ui','uiDesktopNotification() - don\'t have permissions for HTML5');
                        }
                    } else {
                        logger.log('info', 'ui','uiDesktopNotification() - not supported');
                    }
                    return notification;
                };

                /**
                 * Request desktop notification permissions if available. Currently works in Chrome (webkit) only.
                 * @return {Object} Application object
                 */
                uiDesktopNotificationRequestPermission = function () {
                    logger.log('info', 'ui','uiDesktopNotificationRequestPermission()');
                    if (!self.config.enableDesktopNotifications) {
                        return self;
                    }
                    if (window.webkitNotifications) {
                        logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - supported');
                        if (window.webkitNotifications.checkPermission() !== 0) { // 0 is PERMISSION_ALLOWED
                            // function defined in step 2
                            logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - request permissions webkit');
                            window.webkitNotifications.requestPermission();
                        } else {
                            logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - already have permissions webkit');
                        }
                    } else if (window.Notification) {
                        logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - supported');
                        if (window.Notification.permission.toLowerCase() !== "granted") {
                            // function defined in step 2
                            logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - request permissions HTML5');
                            window.Notification.requestPermission(function (newPermission) {
                                logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - permission state is ', newPermission);

                            });
                        } else {
                            logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - already have permissions HTML5');
                        }
                    } else {
                        logger.log('info', 'ui','uiDesktopNotificationRequestPermission() - not supported');
                    }
                    return self;
                };

                /**
                 * Stop any notifications about incoming call
                 * @return {Object} Application object
                 */
                uiIncomingCallNotificationDismiss = function () {
                    logger.log('info', 'ui','uiIncomingCallNotificationDismiss()');
                    self.cache.$preCallIntitePopup.modal('hide');
                    self.cache.$preCallIntitePopup.data('hide', true);
                    $('body').removeClass('modal-open');
                    $('.modal-backdrop').remove();
                    //self.cache.$preCallIntitePopup.hide();
                    helperRingtoneStop();

                    if (self.incomingCallNotification) {
                        self.incomingCallNotification.cancel();
                        self.incomingCallNotification = undefined;
                    }
                    return self;
                };

                /**
                 * Promise to hide splash screen
                 * @return {Object} Deferred jQuery promise object
                 */
                uiPromiseToEndSplashScreen = function () {
                    logger.log('info', 'ui','uiPromiseToEndSplashScreen()');
                    return self.cache.$splash.fadeOut('fast').promise();
                };

                /**
                 * Promise to show main menu
                 * @param  {Boolean} show Show menu when true or undefined or hide when false
                 * @return {Object} Deferred jQuery promise object
                 */
                uiPromiseToShowMenu = function (show) {
                    logger.log('info', 'ui','uiPromiseToShowMenu(' + show + ')');
                    if (show === undefined || show === true) {
                        return self.cache.$mainMenu.slideDown().promise();
                    }
                    return self.cache.$mainMenu.slideUp().promise();
                };

                /**
                 * Set elem to full screen
                 * @param  {Object} elem DOM element which to show in full screen
                 * @return {Object} Application object
                 */
                uiFullscreenSet = function (elem) {
                    logger.log('info', 'ui',"uiFullscreenSet()");
                    /* WARNING: It is a known problem in Safari that Safari does not support keyboard input in the full screen mode. */

                    /* We need to detect what full screen approach to make as full screen API is not yet standardized */

                    function requestFullScreen(element) {
                        logger.log('info', 'ui',"uiFullscreenSet()::requestFullScreen()");

                        // Supports most browsers and their versions.
                        var requestMethod = element.requestFullScreen || element.webkitRequestFullscreen || element.mozRequestFullScreen || element.msRequestFullScreen;

                        if (requestMethod) { // Native full screen.
                            requestMethod.call(element);
                        } else if (window.ActiveXObject !== undefined) { // IE fallback.
                            try {
                                var wscript = new ActiveXObject("WScript.Shell");
                                if (wscript !== null) {
                                    wscript.SendKeys("{F11}");

                                }
                            } catch (e) {
                                logger.log('warning', 'ui','uiFullscreenSet() - IE security level prevented going to full screen');
                                //uiReportError('Fullscreen error', 'IE security level prevented going to full screen');
                            }

                            $(document).trigger("oldmsfullscreenchange");
                        }
                    }

                    requestFullScreen(elem);
                    return self;
                };

                /**
                 * Return from full screen mode
                 * @return {Object} Application object
                 */
                uiFullscreenCancel = function () {
                    logger.log('info', 'ui',"uiFullscreenCancel()");
                    self.isFullscreen = false;
                    /* We need to detect what full screen approach to make as full screen API is not yet standardized */

                    function requestCancelFullScreen() {
                        logger.log('info', 'ui',"uiFullscreenCancel()::requestCancelFullScreen()");

                        // Supports most browsers and their versions.
                        var requestMethod = document.cancelFullScreen || document.webkitCancelFullScreen || document.mozCancelFullScreen || document.msCancelFullScreen;

                        if (requestMethod) { // Native full screen.
                            requestMethod.call(document);
                        } else if (window.ActiveXObject !== undefined) { // Older IE.
                            try {
                                var wscript = new ActiveXObject("WScript.Shell");
                                if (wscript !== null) {
                                    wscript.SendKeys("{F11}");
                                }
                            } catch (e) {
                                logger.log('warning', 'ui','uiFullscreenSet() - IE security level prevented leaving full screen');
                            }
                            $(document).trigger("oldmsfullscreenchange");
                        }
                    }
                    /* Will trigger fullscreenchange event */
                    requestCancelFullScreen();
                    return self;
                };

                /**
                 * Enable JavaScript to invite users to an outgoing conference
                 * @return {Object} Application object
                 */
                uiParticipantEnableInvite = function () {
                    logger.log('info', 'ui','uiParticipantEnableInvite()');
                    var $searchInput = $(self.config.inCallParticipantsSearchForUserInput);

                    var currentSearch, labels, mapped;
                    $searchInput
                        .on('keypress', function (e) {
                            if (e.which === 13) {
                                $(this).next().focus();
                                return false;
                            }
                        })
                        .typeahead({
                            minLength: 2,
                            items: 10,
                            source: function (query, process) {
                                logger.log('info', 'ui',"uiParticipantEnableInvite - source", query);
                                if (currentSearch && currentSearch.request) {
                                    currentSearch.request.abort();
                                }
                                currentSearch = helperSoapPromiseToSearch(query)
                                    .done(function (results) {
                                        var isAvailable = false;
                                        logger.log('info', 'ui',"uiParticipantEnableInvite - helperSoapPromiseToSearch", results);
                                        if (results.total === 1) {
                                            results.Entity = [results.Entity];
                                        }

                                        labels = [];
                                        mapped = {};
                                        if (results && results.total) {
                                            /*jslint unparam: true*/
                                            $.each(results.Entity, function (i, item) {
                                                if (item.MemberStatus === "Online") {
                                                    var query_label = item.displayName + ' [' + item.extension + ']';
                                                    mapped[query_label] = item;
                                                    labels.push(query_label);
                                                } else {
                                                    isAvailable = true;
                                                }
                                            });
                                            /*jslint unparam: false*/
                                        }
                                        if (labels.length === 0) {
                                            if (isAvailable) {
                                                labels.push(query + " is not available");
                                            } else {
                                                labels.push(query + " returned no results");
                                            }
                                        }
                                        process(labels);
                                    })
                                    .fail(function (error) {
                                        logger.log('warning', 'ui',"uiParticipantEnableInvite - helperSoapPromiseToSearch failure with error: ", error, this);
                                    });
                            },
                            updater: function (item, i) {
                                logger.log('debug', 'ui',"uiParticipantEnableInvite - updater", item, mapped[item]);
                                var entity = mapped[item];
                                if (entity) {
                                    portalUserInviteToConference(self.currentRoomId, entity.entityID);
                                }
                            }
                        });
                    return self;
                };

                /**
                 * Quickly update UI on added favorite user
                 * @param  {Int} userId Entity ID of a user to add
                 * @return {Object} Application object
                 */
                uiUserFavoriteAdd = function (userId) {
                    logger.log('info', 'ui','uiUserFavoriteAdd(', userId, ')');
                    var i;
                    for (i = 0; i < self.users.user.length; i++) {
                        if (self.users.user[i].id === userId) {
                            self.users.favNum = self.users.favNum ? (self.users.favNum + 1) : 0;
                            self.users.user[i].inFav = true;
                            self.users.fav.push(self.users.user[i]);
                            break;
                        }
                    }

                    uiUserNavigationUpdateWithData(self.users);
                    return self;
                };

                /**
                 * Quickly update UI on removed favorite user
                 * @param  {Int} userId Entity ID of a user to add
                 * @return {Object} Application object
                 */
                uiUserFavoriteRemove = function (userId) {
                    logger.log('info', 'ui','uiUserFavoriteRemove(', userId, ')');
                    var i;
                    for (i = 0; i < self.users.fav.length; i++) {
                        if (self.users.fav[i].id === userId) {
                            self.users.favNum--;
                            self.users.fav.splice(i, 1);
                            break;
                        }
                    }

                    /* If user is in search then update its fav state */
                    for (i = 0; i < self.users.user.length; i++) {
                        if (self.users.user[i].id === userId) {
                            self.users.user[i].inFav = false;
                            break;
                        }
                    }

                    uiUserNavigationUpdateWithData(self.users);

                    return self;
                };

                /**
                 * Show dialog that allows user to enter a PIN for a conference
                 * @return {Object} Application object
                 */
                uiJoinConferencePinDialogShow = function() {
                    logger.log('info', 'ui','uiJoinConferencePinDialogShow()');
                    self.cache.$preCallJoinConferencePinDialogErrorWrapper.hide();
                    self.cache.$preCallJoinConferencePinDialogPIN.val("");
                    self.cache.$preCallJoinConferencePinDialog.modal('show');
                    return self;
                };

                /**
                 * Login user with credentials
                 * @param  {Object} inEventLoginParams Credentials
                 * @return {Object} Application object
                 */
                clientUserLogin = function (inEventLoginParams) {
                    logger.log('info', 'login', 'clientUserLogin()');

                    var inEvent = vidyoClientMessages.inEventLogin(inEventLoginParams);

                    if (!self.client.sendEvent(inEvent)) {
                        self.events.loginEvent.trigger('fail', "Failed to send inEvent");
                        return undefined;
                    }
                    return self;
                };

                /**
                 * Logout previously logged in user
                 * @return {Object} Application object
                 */
                clientUserLogout = function () {
                    logger.log('info', 'login', 'clientUserLogout()');

                    var inEvent = vidyoClientMessages.inEventSignoff({});

                    if (!self.client.sendEvent(inEvent)) {
                        self.events.loginEvent.trigger('fail', "Failed to send inEvent");
                        return undefined;
                    }
                    return self;
                };

                /**
                 * Connect user to VidyoPortal as a guest and join to the conference.
                 * @param  {Object} inEventLoginParams Information about portal, room and username
                 * @return {Object} Application object
                 */
                clientGuestLoginAndJoin = function (inEventLoginParams) {
                    logger.log('info', 'login', 'clientGuestLoginAndJoin(', inEventLoginParams, ')');


                    var inEvent = vidyoClientPrivateMessages.privateInEventVcsoapGuestLink(inEventLoginParams);
                    //inEvent.typeRequest = "GuestLink";
                    inEvent.requestId = self.currentRequestId++;

                    if (!self.client.sendEvent(inEvent)) {
                        self.events.connectEvent.trigger('fail', {error:"Failed to send inEvent"});
                        return undefined;
                    }
                    return self;
                };

                /**
                 * Disconnect from a conference
                 * @return {Object} Application object
                 */
                clientConferenceLeave = function () {
                    logger.log('info', 'call', "clientConferenceLeave()");

                    var inEvent = vidyoClientMessages.inEventLeave();
                    if (!self.client.sendEvent(inEvent)) {
                        self.events.disconnectEvent.trigger('fail', "Failed to send leave event");
                    } else {
                        self.events.disconnectEvent.trigger('done');
                    }
                    return self;
                };

                /**
                 * Get a state of the conference
                 * @return {String} State ("Idle", "Ringing", "Calling", "Joining", "InConference", "Disconnecting")
                 */
                clientConferenceStateGet = function () {
                    logger.log('info', 'call', 'clientConferenceStateGet()');
                    var request = vidyoClientMessages.requestGetCallState({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientConferenceStateGet(): " + msg, request);

                    return request;
                };

                /**
                 * Pin a participant
                 * @param  {String} uri Participant uri
                 * @param  {Boolean} pin true - pin, false - unpin
                 * @return {Object} Application object
                 */
                clientParticipantPin = function (uri, pin) {
                    logger.log('info', 'call', 'clientParticipantPin(', uri, pin, ')');
                    var params = {}, inEvent, msg;

                    params.uri = uri;
                    params.pinMode = pin ? "PinHigh" : "None";

                    inEvent = vidyoClientMessages.inEventPinParticipant(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientParticipantPin(): " + msg);

                    return self;
                };


                /**
                 * Set limit to number of participants rendered
                 * @param  {Integer} limit Valid from 0-8, 16
                 * @return {Object} Application object
                 */
                clientParticipantsSetLimit = function (limit) {
                    logger.log('info', 'configuration', 'clientParticipantsSetLimit(', limit, ')');
                    var params = {}, inEvent, msg;

                    params.maxNumParticipants = limit;
                    inEvent = vidyoClientMessages.inEventParticipantsLimit(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'configuration', "clientSpeakerMute(): " + msg);

                    return self;
                };

                /**
                 * Mute local audio output device
                 * @param  {Boolean} mute true - mute, false - unmute
                 * @return {Object} Application object
                 */
                clientSpeakerMute = function (mute) {
                    logger.log('info', 'call', 'clientSpeakerMute()');
                    var params = {}, inEvent, msg;
                    params.willMute = mute;
                    inEvent = vidyoClientMessages.inEventMuteAudioOut(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientSpeakerMute(): " + msg);

                    return self;
                };

                /**
                 * Mute local microphone
                 * @param  {Boolean} mute true - mute, false - unmute
                 * @return {Object} Application object
                 */
                clientMicrophoneMute = function (mute) {
                    logger.log('info', 'call', 'clientMicrophoneMute()');
                    var params = {}, inEvent, msg;
                    params.willMute = mute;
                    inEvent = vidyoClientMessages.inEventMuteAudioIn(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientMicrophoneMute(): " + msg);

                    return self;
                };

                /**
                 * Mute local camera. Other participants will not see the user.
                 * @param  {Boolean} mute true - mute, false - unmute
                 * @return {Object} Application object
                 */
                clientVideoMute = function (mute) {
                    logger.log('info', 'call', 'clientVideoMute()');
                    var params = {}, inEvent, msg;
                    params.willMute = mute;
                    inEvent = vidyoClientMessages.inEventMuteVideo(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientVideoMute(): " + msg);

                    return self;
                };

                /**
                 * Get recording and webcasting state
                 * @return {Object} Recording and webcasting state
                 */
                clientRecordAndWebcastStateGet = function () {
                    logger.log('info', 'call', 'clientRecordAndWebcastStateGet()');
                    var request = vidyoClientMessages.requestGetConferenceInfo({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientRecordAndWebcastStateGet(): " + msg, request);

                    return request;
                };

                /**
                 * Get current user information
                 * @return {Object} Current user information object
                 */
                clientCurrentUserGet = function () {
                    logger.log('info', 'configuration', 'clientCurrentUserGet()');
                    var request = vidyoClientMessages.requestGetCurrentUser({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'configuration', "requestGetCurrentUser(): " + msg, request);

                    return request;
                };

                /**
                 * Select remote share to see
                 * @param  {Int} currApp ID of share to see
                 * @return {Object} Currently available shares
                 */
                clientSharesGet = function () {
                    logger.log('info', 'call', 'clientSharesGet()');
                    var request = vidyoClientMessages.requestGetWindowShares({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientSharesGet(): " + msg, request);

                    return request;
                };

                /**
                 * Select remote share to see
                 * @param  {Int} currApp ID of share to make watch
                 * @return {Object} Application object
                 */
                clientSharesSetCurrent = function (currApp) {
                    logger.log('info', 'call', 'clientSharesSetCurrent()');

                    var request = clientSharesGet();
                    request.newApp = currApp + 1;
                    request.type = "RequestSetWindowShares";
                    request.requestType = "ChangeSharingWindow";

                    var msg;

                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientSharesGet() : " + msg, request);

                    return request;
                };

                /**
                 * Toggle between preview modes
                 * @return {Object} Application object
                 */
                clientPreviewModeToggle = function () {
                    logger.log('info', 'call', "clientPreviewModeToggle()");

                    var previewMode;

                    if (self.currentPreviewMode.localeCompare("None") === 0) {
                        previewMode = "PIP";
                    } else if (self.currentPreviewMode.localeCompare("PIP") === 0) {
                        previewMode = "Dock";
                    } else { // "Dock"
                        previewMode = "None";
                    }

                    self.currentPreviewMode = previewMode;

                    clientPreviewModeSet(previewMode);

                    /* Save for next session */
                    helperPersistentStorageSetValue('previewMode', previewMode);
                    return self;
                };

                /**
                 * Sets preview mode
                 * @param  {String} previewMode 'None' - no preview, 'PIP' - picture in picture, 'Dock' - docked view
                 * @return {Object} Application object
                 */
                clientPreviewModeSet = function (previewMode) {
                    logger.log('info', 'call', "clientPreviewModeSet('" + previewMode + "')");

                    var params = {}, inEvent, msg;
                    params.previewMode = previewMode;

                    inEvent = vidyoClientMessages.eventPreview(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientPreviewModeSet(): " + msg);

                    return self;
                };

                /**
                 * Accept incoming call
                 * @return {Object} Application object
                 */
                clientIncomingCallAccept = function () {
                    logger.log('info', 'call', "clientIncomingCallAccept()");
                    var inEvent = vidyoClientMessages.inEventAnswer();
                    var msg;

                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientIncomingCallAccept(): " + msg);
                    return self;
                };

                /**
                 * Reject incoming call
                 * @return {Object} Application object
                 */
                clientIncomingCallReject = function () {
                    logger.log('info', 'call', "clientIncomingCallReject()");
                    var inEvent = vidyoClientMessages.inEventDecline();
                    var msg;

                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientIncomingCallReject(): " + msg);
                    return self;
                };

                /**
                 * Toggle layout between equal and one big participant views
                 * @return {Object} Application object
                 */
                clientLayoutToggle = function () {
                    logger.log('info', 'call', "clientLayoutToggle()");
                    self.numPreferred = self.numPreferred ? 0 : 1;
                    return clientLayoutSet(self.numPreferred);
                };

                /**
                 * Set number of preferred participants.
                 * Preferred participants will be shown in the larger area.
                 * @param  {Integer} numPreferred Number of preferred participants.
                 * @return {Object} Application object
                 */
                clientLayoutSet = function (numPreferred) {
                    logger.log('info', 'call', "clientLayoutSet(", numPreferred, ")");
                    var params = {}, inEvent, msg;
                    params.numPreferred = numPreferred;

                    inEvent = vidyoClientMessages.inEventLayout(params);
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    self.numPreferred = params.numPreferred;
                    logger.log('info', 'call', "clientLayoutSet(): " + msg);

                    return self;
                };
                /**
                 * Retrieves session information like room display name
                 * @return {Object} Session information
                 */
                clientSessionGetInfo = function () {
                    logger.log('info', 'call', "clientSessionGetInfo()");
                    var request = vidyoClientMessages.requestGetCurrentSessionDisplayInfo({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientSessionGetInfo(): " + msg, request);

                    return request;
                };

                /**
                 * Sets log levels and categories for the Client library
                 * @param  {String} levelsAndCategories Levels and categories for the client library log.
                 * @return {Object} Session information
                 */
                clientLogLevelsAndCategoriesSet = function (levelsAndCategories) {
                    logger.log('info', 'configuration', "clientLogLevelsAndCategoriesSet()");
                    var request = vidyoClientMessages.RequestSetLogLevelsAndCategories({
                        levelsAndCategories: levelsAndCategories
                    });
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'configuration', "clientLogLevelsAndCategoriesSet(): " + msg, request);

                    return request;
                };

                /**
                 * Get Endpoint ID (EID), unique endpoint identifier.
                 * @return {Object} Object with EID
                 */
                clientEndpointIDGet = function () {
                    logger.log('info', 'configuration', 'clientEndpointIDGet()');
                    var request = vidyoClientMessages.requestGetEID({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'configuration', "clientEndpointIDGet(): " + msg, request);
                    return request;
                };

                /**
                 * Get information about local endpoint's media.
                 * @return {Object} Object with local endpoint's media information
                 */
                clientLocalMediaInfo = function () {
                    logger.log('info', 'call', 'clientLocalMediaInfo()');
                    var output = {};
                    var requestGetEncodeResolution = vidyoClientMessages.requestGetEncodeResolution();
                    var requestGetVideoFrameRateInfo = vidyoClientMessages.requestGetVideoFrameRateInfo();
                    var requestGetMediaInfo = vidyoClientMessages.requestGetMediaInfo();
                    var msg;
                    if (self.client.sendRequest(requestGetEncodeResolution) &&
                        self.client.sendRequest(requestGetVideoFrameRateInfo) &&
                        self.client.sendRequest(requestGetMediaInfo)) {
                        msg = "VidyoWeb sent all requests successfully";
                        output = $.extend(output, requestGetVideoFrameRateInfo, requestGetMediaInfo, requestGetEncodeResolution);
                    } else {
                        msg = "VidyoWeb did not send requests successfully!";
                    }
                    logger.log('info', 'call', "clientLocalMediaInfo(): " + msg, output);
                    return output;
                };

                /**
                 * Get information about participants in a conference.
                 * @return {Object} Object with participants' array
                 */
                clientParticipantsGet = function () {
                    logger.log('info', 'call', 'clientParticipantsGet()');
                    var requestNum = vidyoClientMessages.requestGetNumParticipants({});
                    var me = clientCurrentUserGet();
                    var participants = [];
                    var msg;

                    if (self.client.sendRequest(requestNum)) {
                        var i;
                        var participantRequest;
                        for (i = 0; i < requestNum.numParticipants; i++) {
                            participantRequest = vidyoClientMessages.requestGetParticipantStatisticsAt({
                                index: i
                            });
                            if (self.client.sendRequest(participantRequest)) {
                                if (participantRequest.result === true) {
                                    // TODO: Use URI for self detection
                                    if (me && me.currentUserDisplay && (me.currentUserDisplay === participantRequest.name)) {
                                        participantRequest.isMe = true;
                                        participantRequest.encoderInfo = clientLocalMediaInfo();
                                    }
                                    participants.push(participantRequest);
                                } else {
                                    logger.log('warning', 'call', "clientParticipantsGet() - Result is not succesful for participant #", i);
                                }

                            } else {
                                logger.log('warning', 'call', "clientParticipantsGet() - Failed to get participant #", i);
                            }
                        }
                        msg = "VidyoWeb sent " + requestNum.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + requestNum.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientParticipantsGet(): " + msg, participants);
                    return participants;
                };

                /**
                 * Retrieves Vidyo runtime configuration
                 * @return {Object} Runtime configuration
                 */
                clientConfigurationGet = function () {
                    logger.log('info', 'configuration', 'clientConfigurationGet()');
                    var request = vidyoClientMessages.requestGetConfiguration({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'configuration', "clientConfigurationGet(): " + msg, request);

                    return request;
                };

                /**
                 * Sets Vidyo runtime configuration
                 * @return {Object} Applied configuration
                 */
                clientConfigurationSet = function (vidyoConfig) {
                    logger.log('info', 'configuration', 'clientConfigurationGet(', vidyoConfig, ')');
                    var request = vidyoClientMessages.requestSetConfiguration(vidyoConfig);
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'configuration', "clientConfigurationSet(): " + msg, request);

                    return request;
                };

                /**
                 * Gets desktops and windows available in the system
                 * @return {Object} Desktops and windows object
                 */
                clientLocalSharesGet = function () {
                    logger.log('info', 'call', 'clientDesktopsAndWindowsGet()');
                    var request = vidyoClientMessages.requestGetWindowsAndDesktops({});
                    var msg;
                    if (self.client.sendRequest(request)) {
                        msg = "VidyoWeb sent " + request.type + " request successfully";
                    } else {
                        msg = "VidyoWeb did not send " + request.type + " request successfully!";
                    }
                    logger.log('info', 'call', "clientDesktopsAndWindowsGet(): " + msg, request);

                    return request;
                };

                /**
                 * Send a group chat message
                 * @param  {String} message Message to send.
                 * @return {Object} Application object
                 */
                clientGroupChatSend = function (message) {
                    logger.log('info', 'call', "clientGroupChatSend('", message, "')");

                    var params = {}, inEvent, msg;

                    params.message = message;

                    inEvent = vidyoClientMessages.inEventGroupChat(params);

                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientGroupChatSend(): " + msg);

                    return self;
                };

                /**
                 * Send a private chat message
                 * @param  {String} message Message to send.
                 * @return {Object} Application object
                 */
                clientPrivateChatSend = function (uri, message) {
                    logger.log('info', 'call', "clientPrivateChatSend('", uri, message, "')");

                    var params = {}, inEvent, msg;

                    params.message = message;
                    params.uri = uri;

                    inEvent = vidyoClientMessages.inEventPrivateChat(params);

                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientPrivateChatSend(): " + msg);

                    return self;
                };
                /**
                 * Start sharing
                 * @param  {String} shareId Share window or desktop id. Undefined to stop share.
                 * @return {Object} Application object
                 */
                clientLocalShareStart = function (shareId) {
                    logger.log('info', 'call', "clientLocalShareStart('", shareId, "')");

                    var inEvent, msg;
                    if (shareId === undefined) {
                        inEvent = vidyoClientMessages.inEventUnshare();
                    } else {
                        inEvent = vidyoClientMessages.inEventShare({
                            window: shareId
                        });
                    }
                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientLocalShareStart(): " + msg);

                    return self;
                };

                /**
                 * Stop sharing
                 * @return {Object} Application object
                 */
                clientLocalShareStop = function () {
                    logger.log('info', 'call', "clientLocalShareStop()");

                    var inEvent, msg;
                    inEvent = vidyoClientMessages.inEventUnshare();

                    if (self.client.sendEvent(inEvent)) {
                        msg = "VidyoWeb sent " + inEvent.type + " event successfully";
                    } else {
                        msg = "VidyoWeb did not send " + inEvent.type + " event successfully!";
                    }
                    logger.log('info', 'call', "clientLocalShareStop(): " + msg);

                    return self;
                };

                /**
                 * Configure vidyoPlugin runtime on startup
                 * @param  {Object} conf Runtime configuration
                 * @return {Object}      Applied runtime configuration
                 */
                clientConfigurationBootstrap = function (conf) {
                    logger.log('info', 'call', "clientConfigurationBootstrap()");

                    conf.enableAutoStart = 0;
                    //conf.enableShowConfParticipantName = self.config.enableShowConfParticipantName ? 1 : 0;
                    conf.userID = "";
                    conf.password = "";
                    conf.serverAddress = "";
                    conf.serverPort = "";
                    conf.portalAddress = "";
                    clientLogLevelsAndCategoriesSet(self.logConfig.levelsAndCategories);
                    return clientConfigurationSet(conf);
                };

                /**
                 * Initializes and connects vidyo.client JavaScript library and plugin object.
                 * @return {Object} Application object
                 */
                vidyoPluginInitAndStart = function () {
                    logger.log('info', 'plugin', 'vidyoPluginInitAndStart()');

                    /* Sets configuration to defaults */
                    vidyoPluginConfigurationPrepare(self.cache.$plugin.get()[0]);

                    /* Attaches plugin object to the JS vidyo.client library */
                    vidyoPluginLoad();

                    /* Check if started correctly */
                    if (vidyoPluginIsLoaded()) {
                        if (vidyoPluginIsStarted()) { // started already
                            self.events.pluginLoadedEvent.trigger('fail', "Another instance is running?");
                        } else { // not started yet
                            if (vidyoPluginStart()) {
                                self.events.pluginLoadedEvent.trigger('done');
                            } else { //failed to start
                                self.events.pluginLoadedEvent.trigger('fail', "Failed to start Vidyo Library");
                            }
                        }
                    } else {
                        /* Failed to load plugin */
                        logger.log('warning', 'plugin', "Failed to load plugin.");

                        if (vidyoPluginIsInstalled()) {
                            /* Plugin is installed but not loaded. Probably blocked by the browser. */
                            logger.log('warning', 'plugin', "Plugin is installed but not loaded. Probably blocked by the browser.");
                            var details = self.templates.pluginEnableInstructionsTemplate({
                                version: self.config.pluginVersion
                            });
                            self.events.pluginLoadedEvent.trigger('info', {message: "Plugin detected but not loaded", details: details});
                            uiStartPluginDetection(true);
                        } else {
                            /* Notify deferred object to show plugin download */
                            logger.log('warning', 'plugin', "Plugin is not installed. Starting plugin auto detection.");
                            var details = self.templates.pluginInstallInstructionsTemplate({
                                version: self.config.pluginVersion
                            });
                            self.events.pluginLoadedEvent.trigger('info', {message: "Plugin is not installed", details: details});
                            /* Start plugin polling */
                            uiStartPluginDetection(false);
                        }
                    }
                    return self;
                };

                /**
                 * Get status of plugin in the DOM
                 * @return {Boolean} true for plugin is loaded into DOM and false for opposite
                 */
                vidyoPluginIsLoaded = function () {
                    logger.log('info', 'plugin', 'vidyoPluginIsLoaded()');
                    return self.client.isLoaded();
                };

                /**
                 * Prepares configuration object for JavaScript Library
                 * @param  {Object} plugin Plugin DOM object
                 * @param  {Object} config Configuration
                 * @return {Object} Application object with applied configuration
                 */
                vidyoPluginConfigurationPrepare = function (plugin, config) {
                    logger.log('info', 'plugin', 'vidyoPluginConfigurationPrepare()');


                    var localConfig = {
                        plugin: plugin,
                        defaultOutEventCallbackMethod: function (event) {
                            logger.log('info', 'plugin', 'default callback for client lib: ', event);
                        },
                        useCallbackWithPlugin: true,
                        outEventCallbackObject: self,
                        logCallback: function (message) {
                            if (self.logConfig.enableVidyoPluginLogs) {
                                console.log("jsclient::", message);
                            }
                        },
                        callbacks: self.callbacks
                    };

                    self.config.vidyoConfig = $.extend({}, self.config.vidyoConfig, config, localConfig);

                    return self;
                };

                /**
                 * Loads plugin into vidyo.client library with configuration
                 * @param  {Object} config Optional configuration object
                 * @return {Object} Application object
                 */
                vidyoPluginLoad = function (config) {
                    logger.log('info', 'plugin', 'vidyoPluginLoad() begin');

                    self.config.vidyoConfig = $.extend({}, self.config.vidyoConfig, config);
                    //logger.log(conf);
                    self.client = vidyoClient(self.config.vidyoConfig);
                    if (!self.client) {
                        return undefined;
                    }
                    return self;
                };

                /**
                 * Shows or hides plugin by assigning 1x1 size
                 * @param  {Boolean} show True to show and false to hide
                 * @return {Object} Application object
                 */
                uiVidyoPluginShow = function (show) {
                    logger.log('info', 'plugin', 'uiVidyoPluginShow(' + show + ')');
                    if (show) {
                        self.cache.$plugin.addClass("fullscreen");
                        self.cache.$plugin.removeClass("minimized");
                    } else {
                        self.cache.$plugin.removeClass("fullscreen");
                        self.cache.$plugin.addClass("minimized");
                    }
                    return self;
                };

                /**
                 * Returns true if plugin is shown and false otherwise.
                 * @return {Boolean} Application object
                 */
                uiVidyoPluginIsShown = function () {
                    logger.log('info', 'plugin', 'uiVidyoPluginIsShown()');

                    return self.cache.$plugin.hasClass("minimized");
                };

                /**
                 * Detects if plugin is installed or not
                 *
                 * @return {Boolean} Application object
                 */
                vidyoPluginIsInstalled = function() {
                    var isFound = false;
                    logger.log('info', 'plugin', 'vidyoPluginIsInstalled()');
                    navigator.plugins.refresh(false);

                    /* Try NPAPI approach */
                    /*jslint unparam: true*/
                    $.each(navigator.mimeTypes, function (i, val) {
                        if (val.type === self.config.pluginMimeType) {
                            /* Reload page when plugin is detected */
                            logger.log('info', 'plugin', 'vidyoPluginIsInstalled() -- NPAPI plugin found');
                            isFound = true;
                            return true;
                        }
                    });
                    /*jslint unparam: false*/

                    /* Try IE approach */
                    try {
                        var control = new ActiveXObject(self.config.activexType);
                        if (control) {
                            logger.log('info', 'plugin', 'vidyoPluginIsInstalled() -- ActiveX plugin found');
                            isFound = true;
                        }
                    } catch (ignore) {

                    }

                    if (isFound) {
                        return true;
                    } else {
                        return false;
                    }
                };

                /**
                 * Check start status of Vidyo Client library
                 * @return {Boolean} true for started and false for not started
                 */
                vidyoPluginIsStarted = function () {
                    logger.log('info', 'plugin', 'vidyoPluginIsStarted');
                    return self.client.isStarted();
                };

                /**
                 * Starts Vidyo library runtime
                 * @return {Boolena} True for success and false for error
                 */
                vidyoPluginStart = function () {
                    logger.log('info', 'plugin', 'vidyoPluginStart');
                    var msg;

                    if (!self.client) {
                        if (!vidyoPluginLoad()) {
                            return false;
                        }
                    }

                    /* Set all callbacks */
                    try {
                        $.each(self.config.vidyoConfig.callbacks, function (key, val) {
                            self.client.setOutEventCallbackMethod(key, val);
                        });
                    } catch (e) {
                        logger.log('warning', 'plugin', "vidyoPluginStartFailed -  to set callbacks");
                    }

                    if (self.client.start()) {
                        msg = "VidyoWeb started successfully";
                    } else {
                        msg = "VidyoWeb did not start successfully!";
                        return false;
                    }

                    logger.log('info', 'plugin', "vidyoPluginStart(): " + msg);

                    return true;
                };

                /**
                 * Stops Vidyo library runtime
                 * @return {Object} Application object
                 */
                vidyoPluginStop = function () {
                    logger.log('info', 'plugin', 'vidyoPluginStop()');
                    var msg;

                    if (self.client.stop(true, true)) {
                        msg = "VidyoWeb stopped successfully";
                    } else {
                        msg = "VidyoWeb did not stop successfully!";
                    }
                    logger.log('info', 'plugin', "vidyoPluginStop(): " + msg);

                    return self;
                };

                /**
                 * Sends a request to the VidyoPortal to get all recorder profiles.
                 * @return {Object} Application object
                 */
                portalRecordGetProfiles = function () {
                    logger.log('info', 'portal', 'portalRecordGetProfiles()');

                    helperSoapPromiseToSendUserRequest("getRecordingProfiles")
                        .done(function (results) {
                            logger.log('info', 'portal', "portalRecordGetProfiles - profiles: ", results);
                            self.recorderProfiles = results;
                        })
                        .fail(function () {
                            self.recorderProfiles = undefined;
                        });
                    return self;
                };

                /**
                 * Sends a request to the VidyoPortal to start recording of a conference.
                 * @return {Object} Application object
                 */
                portalRecordStart = function (recorderPrefix, conferenceId, enableWebcast) {
                    logger.log('info', 'portal', 'portalRecordStart(', recorderPrefix, conferenceId, enableWebcast, ')');

                    helperSoapPromiseToSendUserRequest("startRecording", {
                        conferenceID: conferenceId,
                        recorderPrefix: recorderPrefix,
                        webcast: enableWebcast ? true : false
                    })
                        .done(function () {
                            self.events.recorderEvent.trigger("start");
                        })
                        .fail(function () {
                            self.events.recorderEvent.trigger("startFail");
                        });
                    return self;
                };

                /**
                 * Sends a request to the VidyoPortal to stop recording of a conference.
                 * @param  {Int} conferenceId Entity ID of a conference to stop recording for
                 * @return {Object} Application object
                 */
                portalRecordStop = function (conferenceId) {
                    logger.log('info', 'portal', 'portalRecordStop(', conferenceId, ')');
                    /* First we need to get recorder ID and than issue stop command */
                    helperSoapPromiseToSendUserRequest("getParticipants", {
                        conferenceID: conferenceId
                    })
                        .done(function (results) {
                            if (results && results.recorderID) {

                                helperSoapPromiseToSendUserRequest("stopRecording", {
                                    conferenceID: conferenceId,
                                    recorderID: results.recorderID
                                })
                                    .done(function () {
                                        self.events.recorderEvent.trigger("stop");
                                    })
                                    .fail(function () {
                                        logger.log('warning', 'portal', "portalRecordStop - failed to stop recording");
                                        self.events.recorderEvent.trigger("stopFail");
                                    });
                            }
                        })
                        .fail(function () {
                            logger.log('warning', 'portal', "portalRecordStop - failed to get conference participants");
                            self.events.recorderEvent.trigger("stopFail");
                        });
                    return self;
                };

                portalRoomPromiseToLock = function (conferenceId, lock) {
                    logger.log('info', 'portal', 'portalRoomPromiseToLock(', conferenceId, lock, ')');
                    if (lock) {
                        return helperSoapPromiseToSendUserRequest("lockRoom", {
                            roomID: conferenceId
                        });
                    }
                    return helperSoapPromiseToSendUserRequest("unlockRoom", {
                        roomID: conferenceId
                    });
                };
                /**
                 * Sends a request to the VidyoPortal to information about conference room.
                 * @param  {Int} conferenceId Entity ID of a conference room
                 * @return {Object} Promise object
                 */
                portalRoomInfoPromiseToGet = function (conferenceId) {
                    logger.log('info', 'portal', 'portalRoomInfoPromiseToGet(', conferenceId, ')');
                    return helperSoapPromiseToSendUserRequest("searchByEntityID", {
                        entityID: conferenceId,
                        Filter: {
                            query: ""
                        }
                    });
                };

                /**
                 * Sends a request to the VidyoPortal to get participants of a conference.
                 * @param  {Int} conferenceId Entity ID of a conference
                 * @return {Object} Promise object
                 */
                portalParticipantsPromiseToGet = function (conferenceId) {
                    logger.log('info', 'portal', 'portalParticipantsPromiseToGet(', conferenceId, ')');
                    return helperSoapPromiseToSendUserRequest("getParticipants", {
                        conferenceID: conferenceId
                    });
                };

                /**
                 * Sends a request to the VidyoPortal to join a conference
                 * @param  {Int} conferenceId Entity ID of a conference to join
                 * @param  {String} pin PIN for a conference
                 * @return {Object} Application object
                 */
                portalUserJoinConference = function (conferenceId, pin) {
                    logger.log('info', 'portal', 'portalUserJoinConference(', conferenceId, ')');

                    helperSoapPromiseToSendUserRequest("joinConference", {
                        conferenceID: conferenceId,
                        PIN: pin
                    })
                        .done(function (response) {
                            logger.log('info', 'portal', 'portalUserJoinConference()::helperSoapPromiseToSendUserRequest.done', response);
                            /* Could have an error */
                            if (response.OK !== "OK") {
                                self.events.connectEvent.trigger("fail", {error:response.faultstring});
                            } else {
                                self.events.connectEvent.trigger("progress");
                            }
                        })
                        .fail(function (error, details) {
                            logger.log('info', 'portal', 'portalUserJoinConference()::helperSoapPromiseToSendUserRequest.fail', JSON.stringify(arguments), error, details);

                            self.events.connectEvent.trigger("fail", {error:error, details:details});
                        });
                    return self;
                };

                /**
                 * Sends a request to the VidyoPortal to make a direct call to a user
                 * @param  {Int} userId Entity ID of a user to call
                 * @return {Object} Application object
                 */
                portalUserCallDirect = function (userId) {
                    logger.log('info', 'portal', 'portalUserCallDirect(', userId, ')');

                    helperSoapPromiseToSendUserRequest("directCall", {
                        entityID: userId
                    })
                        .done(function (response) {
                            logger.log('info', 'portal', 'portalUserCallDirect()::helperSoapPromiseToSendUserRequest.done', response);
                            /* Could have an error */
                            if (response.OK !== "OK") {
                                self.events.connectEvent.trigger("fail", {error:response.faultstring});
                            } else {
                                self.events.connectEvent.trigger("progress");
                            }
                        })
                        .fail(function () {
                            self.events.connectEvent.trigger("fail", {error: "Failed to send SOAP request"});
                        });
                    return self;
                };

                /**
                 * Sends a request to add a user to favorites
                 * @param  {Int} userId Entity ID of a user to add
                 * @return {Object} Promise object
                 */
                portalUserFavoritePromiseToAdd = function (userId) {
                    logger.log('info', 'portal', 'portalUserFavoritePromiseToAdd(', userId, ')');

                    return helperSoapPromiseToSendUserRequest("addToMyContacts", {
                        entityID: userId
                    });
                };

                /**
                 * Sends a request to remove user from favorites
                 * @param  {Int} userId Entity ID of a user to remove
                 * @return {Object} Promise object
                 */
                portalUserFavoritePromiseToRemove = function (userId) {
                    logger.log('info', 'portal', 'portalUserFavoritePromiseToRemove(', userId, ')');

                    return helperSoapPromiseToSendUserRequest("removeFromMyContacts", {
                        entityID: userId
                    });
                };

                /**
                 * Sends a request to the VidyoPortal to invite user to a conference
                 * @param  {Int} conferenceId Entity ID of a conference to invite to
                 * @param  {Int} userId Entity ID of a user to invite
                 * @return {Object} Application object
                 */
                portalUserInviteToConference = function (conferenceId, userId) {
                    logger.log('info', 'portal', 'portalUserInviteToConference(', conferenceId, ', ', userId, ')');

                    helperSoapPromiseToSendUserRequest("inviteToConference", {
                        conferenceID: conferenceId,
                        entityID: userId
                    })
                        .done(function () {
                            logger.log('info', 'portal', "portalUserInviteToConference::done");

                        })
                        .fail(function () {
                            logger.log('info', 'portal', "portalUserInviteToConference::fail");

                        });
                    return self;
                };

                /**
                 * Search for users on a portal.
                 * Application will receive an event searchUpdate when information is received from the VidyoPortal
                 * @param  {Boolean} includeUsers true - search both favorites and other users on a portal, false - just favorites
                 * @param  {String} query        query for search
                 * @return {Object} Application object
                 */
                portalUserSearchBothFavAndUsers = function (includeUsers, query) {
                    logger.log('info', 'portal', 'portalUserSearchBothFavAndUsers("', (query || ""), '")');

                    self.lastUsers = self.users;
                    var tmpUsers = {};
                    self.currentSearchRequest = helperSoapPromiseToSearchMyContacts(query)
                        .done(function (results) {
                            var transformedResult = {
                                fav: []
                            };
                            logger.log('info', 'portal', 'portalUserSearchBothFavAndUsers()::helperSoapPromiseToSearchMyContacts().done(', results, ')');
                            var favIds = [];

                            //logger.log(results);
                            if (results.total > 0) {
                                if (results.total === 1) {
                                    results.Entity = [results.Entity];
                                }
                                transformedResult.favNum = results.Entity.length || "";
                                /*jslint unparam: true*/
                                $.each(results.Entity, function (i, entity) {
                                    var isOnline = (entity.MemberStatus === "Offline") ? false : true,
                                        canCallDirect = (entity.MemberStatus === "Online") ? true : false;

                                    transformedResult.fav.push({
                                        name: entity.displayName,
                                        id: entity.entityID,
                                        isOnline: isOnline,
                                        canCallDirect: canCallDirect,
                                        isBusy: !canCallDirect,
                                        ownerId: entity.ownerID,
                                        isOccupied: (entity.RoomStatus === "Occupied"),
                                        isRoomFull: (entity.RoomStatus === "Full"),
                                        isLocked: entity.RoomMode.isLocked,
                                        hasPin: entity.RoomMode.hasPIN,
                                        emailAddress: (entity.entityID !== entity.ownerID) ? entity.emailAddress : undefined,
                                        inFav: true
                                    });

                                    favIds.push(entity.entityID);
                                });
                                /*jslint unparam: false*/
                            }
                            tmpUsers.favNum = transformedResult.favNum;
                            tmpUsers.fav = transformedResult.fav;
                            tmpUsers.userNum = undefined;
                            tmpUsers.user = [];

                            if (!includeUsers) {
                                self.currentSearchRequest = undefined;
                                self.users = tmpUsers;
                                self.events.searchUpdateEvent.trigger("done", transformedResult);
                            } else {
                                logger.log('info', 'portal', 'portalUserSearchBothFavAndUsers()::helperSoapPromiseToSearchMyContacts() - about to helperSoapPromiseToSearch(', query, ')');
                                self.currentSearchRequest = helperSoapPromiseToSearch(query)
                                    .done(function (results) {
                                        var transformedResult = {
                                            user: []
                                        };
                                        logger.log('info', 'portal', 'portalUserSearchBothFavAndUsers()::helperSoapPromiseToSearchMyContacts().done().helperSoapPromiseToSearch(', results, ')');

                                        if (results.total > 0) {
                                            if (results.total === 1) {
                                                results.Entity = [results.Entity];
                                            }
                                            transformedResult.userNum = results.Entity.length || "";
                                            /*jslint unparam: true*/
                                            $.each(results.Entity, function (i, entity) {
                                                var isOnline = (entity.MemberStatus === "Offline") ? false : true,
                                                    canCallDirect = (entity.MemberStatus === "Online") ? true : false;

                                                transformedResult.user.push({
                                                    name: entity.displayName,
                                                    id: entity.entityID,
                                                    isOnline: isOnline,
                                                    canCallDirect: canCallDirect,
                                                    isBusy: !canCallDirect,
                                                    ownerId: entity.ownerID,
                                                    isOccupied: (entity.RoomStatus === "Occupied"),
                                                    isRoomFull: (entity.RoomStatus === "Full"),
                                                    isLocked: entity.RoomMode.isLocked,
                                                    hasPin: entity.RoomMode.hasPIN,
                                                    emailAddress: (entity.entityID !== entity.ownerID) ? entity.emailAddress : undefined,
                                                    inFav: (favIds.indexOf(entity.entityID) >= 0) ? true : false
                                                });
                                            });
                                            /*jslint unparam: false*/
                                        }
                                        tmpUsers.userNum = transformedResult.userNum;
                                        tmpUsers.user = transformedResult.user;

                                        self.currentSearchRequest = undefined;
                                        self.users = tmpUsers;
                                        self.events.searchUpdateEvent.trigger("done", self.users);
                                    })
                                    .fail(function (reason) {
                                        self.currentSearchRequest = undefined;
                                        if (reason === "abort") {
                                            self.events.searchUpdateEvent.trigger("cancel");
                                        } else {
                                            self.events.searchUpdateEvent.trigger("error", reason);
                                        }
                                    });
                            }
                        })
                        .fail(function (reason) {
                            self.currentSearchRequest = undefined;
                            if (reason === "abort") {
                                self.events.searchUpdateEvent.trigger("cancel");
                            } else {
                                self.events.searchUpdateEvent.trigger("error", reason);
                            }
                        });
                };

                /**
                 * Cancels current search request
                 * @return {Object} Application object
                 */
                portalUserCancelSearchRequest = function () {
                    logger.log('info', 'portal', "portalUserCancelSearchRequest()");

                    if (self.currentSearchRequest && self.currentSearchRequest.request) {
                        logger.log('info', 'portal', 'portalUserCancelSearchRequest::cancellign: ', self.currentSearchRequest);
                        self.currentSearchRequest.request.abort();
                        self.events.searchUpdateEvent.trigger("cancel");
                    }
                    return self;
                };

                /**
                 * Sends a Web Service User API request to the portal using SOAP proxy.
                 * Can replace SOAP interface here.
                 * @param  {String} action SOAP action
                 * @param  {Object} body   Body of the SOAP request
                 * @return {Object}        Promise to resolve the request and Object.request will have jQuery Ajax request that can be canceled
                 */
                helperSoapPromiseToSendUserRequest = function (action, body) {
                    logger.log('info', 'soap', 'helperSoapPromiseToSendUserRequest(', (action || ""), (body || ""), ')');


                    var soapClient = soapProxy();
                    try {
                        return soapClient.request({
                            ajaxDataType: 'jsonp',
                            proxyUrl: self.config.soapProxyURL,
                            soapAction: action,
                            soapServerUrl: self.loginInfo.portalUri,
                            soapServiceUsername: self.loginInfo.userName,
                            soapServicePassword: self.loginInfo.userPass,
                            soapServicePath: self.config.soapUserServicePath,
                            soapBody: (body || "")
                        });

                    } catch (e) {
                        logger.log('warning', 'soap', "helperSoapPromiseToSendUserRequest failure: ", action, e);
                    }
                };

                /**
                 * Sends a Web Service User API request to get user's account information.
                 * @return {Object}        Promise to resolve the request and Object.request will have jQuery Ajax request that can be canceled
                 */
                helperSoapPromiseToGetMyAccount = function () {
                    logger.log('info', 'soap', 'helperSoapPromiseToGetMyAccount()');

                    return helperSoapPromiseToSendUserRequest("myAccount");
                };

                /**
                 * Sends a Web Service User API request to search for users.
                 * @param  {String} query   Search query
                 * @param  {Integer} limit  Optional maximum number of responses. Default is 100.
                 * @return {Object}        Promise to resolve the request and Object.request will have jQuery Ajax request that can be canceled
                 */
                helperSoapPromiseToSearch = function (query, limit) {
                    logger.log('info', 'soap', 'helperSoapPromiseToSearch("', (query || ""), limit || "default 100", '")');

                    var body = {
                        Filter: {
                            limit: limit || 100,
                            query: query
                        }
                    };
                    return helperSoapPromiseToSendUserRequest("search", body);
                };

                /**
                 * Sends a Web Service User API request to search favorites.
                 * @param  {String} query   Search query
                 * @param  {Integer} limit  Optional maximum number of responses. Default is 100.
                 * @return {Object}        Promise to resolve the request and Object.request will have jQuery Ajax request that can be canceled
                 */
                helperSoapPromiseToSearchMyContacts = function (query, limit) {
                    logger.log('info', 'soap', 'helperSoapPromiseToSearchMyContacts("', (query || ""), limit || "default 100", '")');

                    var body = {
                        Filter: {
                            limit: limit || 100,
                            query: query || ""
                        }
                    };
                    return helperSoapPromiseToSendUserRequest("searchMyContacts", body);
                };

                /**
                 * Stores a value to the persistent store
                 * @param  {String} key   Key for the value
                 * @param  {String} value Value to store
                 * @return {Object} Application object
                 */
                helperPersistentStorageSetValue = function (key, value) {
                    logger.log('info', 'cache', "helperPersistentStorageSetValue('", key, "', '", value, "')");

                    $.localStorage.setItem(key, JSON.stringify(value));
                    return self;
                };

                /**
                 * Gets value from the persistent store
                 * @param  {String} key   Key for the value
                 * @return {Object} Value associated with a key
                 */
                helperPersistentStorageGetValue = function (key) {
                    logger.log('info', 'cache', "helperPersistentStorageGetValue('", key, "')");

                    var value = $.localStorage.getItem(key);
                    if (value == undefined) {
                        return undefined;
                    }
                    try {
                        var parsedValue = JSON.parse(value);
                        logger.log('info', 'cache', "helperPersistentStorageGetValue('", key, "') - ", parsedValue);
                        return parsedValue;
                    } catch (e) {
                        logger.log('warning', 'cache', "helperPersistentStorageGetValue::Failed to parse value: ", value, " for key ", key);
                    }

                    return undefined;
                };

                /**
                 * Starts timer that refreshes participant information
                 * @return {Object} Application object
                 */
                helperConferenceUpdateTimerStart = function (timeout) {
                    logger.log('info', 'application', "helperConferenceUpdateTimerStart()");
                    var refreshFunction = function () {
                        var participants = clientParticipantsGet();
                        self.events.participantUpdateEvent.trigger('done', [participants]);
                        /* Cannot get information about room from VidyoPortal in guest mode */
                        if (!self.isGuestLogin && self.currentRoomId !== undefined) {
                            portalRoomInfoPromiseToGet(self.currentRoomId)
                                .done(function (response) {
                                    logger.log('debug', 'application', "helperConferenceUpdateTimerStart()::portalRoomInfoPromiseToGet::done", response);
                                    var i;
                                    if (response.total === 1) {
                                        response.Entity = [response.Entity];
                                    }
                                    for (i = 0; i < response.Entity.length; i++) {
                                        if (response.Entity[i].entityID === self.currentRoomId) {
                                            self.events.roomLockEvent.trigger("done", response.Entity[i].RoomMode.isLocked);
                                            break;
                                        }
                                    }
                                })
                                .fail(function (error) {
                                    logger.log('warning', 'application', "helperConferenceUpdateTimerStart()::portalRoomInfoPromiseToGet::fail", error);
                                });
                        }
                    };
                    refreshFunction();
                    if (self.participantRefreshTimer) {
                        window.clearInterval(self.participantRefreshTimer);
                        self.participantRefreshTimer = 0;
                    }
                    self.participantRefreshTimer = window.setInterval(refreshFunction, timeout);
                    return self;
                };

                /**
                 * Stops participant refresh timer
                 * @return {Object} Application object
                 */
                helperConferenceUpdateTimerStop = function () {
                    logger.log('info', 'application', "helperConferenceUpdateTimerStop()");
                    window.clearInterval(self.participantRefreshTimer);
                    self.participantRefreshTimer = 0;
                    return self;
                };

                /**
                 * Starts timer that refreshes last search result
                 * so we will update users' status.
                 * @return {Object} Application object
                 */
                helperPortalUsersStatusUpdateTimerStart = function (timeout) {
                    logger.log('info', 'application', "helperPortalUsersStatusUpdateTimerStart()");

                    var refreshFunction = function () {
                        var value = self.cache.$preCallSearchField.val();
                        logger.log('debug', 'application', "helperPortalUsersStatusUpdateTimerStart::refreshTimer() - val: ", value);
                        portalUserSearchBothFavAndUsers(value.length ? true : false, value);
                        portalParticipantsPromiseToGet(self.myAccount.entityID)
                            .done(function (data) {
                                self.events.portalParticipantUpdateEvent.trigger('done', data);
                            })
                            .fail(function (error) {
                                logger.log('warning', 'application', "helperPortalUsersStatusUpdateTimerStart - failed to get participant in my room", error);
                            });
                    };

                    refreshFunction();
                    if (self.searchUserRefreshTimer) {
                        window.clearInterval(self.searchUserRefreshTimer);
                        self.searchUserRefreshTimer = 0;
                    }
                    self.searchUserRefreshTimer = window.setInterval(refreshFunction, timeout);
                    return self;
                };

                /**
                 * Stops user refresh timer
                 * @return {Object} Application object
                 */
                helperPortalUsersStatusUpdateTimerStop = function () {
                    logger.log('info', 'application', "helperPortalUsersStatusUpdateTimerStop()");
                    window.clearInterval(self.searchUserRefreshTimer);
                    self.searchUserRefreshTimer = 0;
                    return self;
                };

                /**
                 * Start playing ringtone
                 * @return {Object} Application object
                 */
                helperRingtonePlay = function () {
                    logger.log('info', 'application', "helperRingtonePlay()");
                    try {
                        if (window.Audio !== undefined) {
                            self.ringtoneAudio = new window.Audio();
                            if ( !! (self.ringtoneAudio.canPlayType && self.ringtoneAudio.canPlayType('audio/ogg; codecs="vorbis"').replace(/no/, ''))) {
                                self.ringtoneAudio.src = self.config.audioIncomingCallOgg;
                            } else if ( !! (self.ringtoneAudio.canPlayType && self.ringtoneAudio.canPlayType('audio/mpeg;').replace(/no/, ''))) {
                                self.ringtoneAudio.src = self.config.audioIncomingCallMp3;
                            } else if ( !! (self.ringtoneAudio.canPlayType && self.ringtoneAudio.canPlayType('audio/wave;').replace(/no/, ''))) {
                                self.ringtoneAudio.src = self.config.audioIncomingCallWav;
                            } else {
                                self.ringtoneAudio.src = self.config.audioIncomingCallOgg;
                            }

                            logger.log('info', 'application', "helperRingtonePlay() - using ", self.ringtoneAudio.src);

                            /* Not all browsers support loop, so check */
                            self.ringtoneAudio.addEventListener('ended', function () {
                                logger.log('info', 'application', "helperRingtonePlay() - ended");
                                if (self.ringtoneAudio) {
                                    logger.log('info', 'application', "helperRingtonePlay() - restart");
                                    self.ringtoneAudio.currentTime = 0;
                                    self.ringtoneAudio.pause();
                                    self.ringtoneAudio.load();
                                    self.ringtoneAudio.play();
                                }
                            });
                            self.ringtoneAudio.play();
                        } else {
                            logger.log('warning', 'application', "helperRingtonePlay() - html5 audio is not supported");
                        }
                    } catch (e) {
                        logger.log('warning', 'application', "helperRingtonePlay() - html5 audio is not supported");
                    }

                    return self;
                };

                /**
                 * Stop playing ringtone
                 * @return {Object} Application object
                 */
                helperRingtoneStop = function () {
                    logger.log('info', 'application', "helperRingtoneStop()");
                    if (self.ringtoneAudio) {
                        self.ringtoneAudio.pause();
                        self.ringtoneAudio = undefined;
                    }
                };
                /**
                 * Main application entry point
                 * @return {Object}   Application object
                 */
                var main = function () {
                    /* Startup sequence */
                    applicationClientInfoPrint();
                    applicationBuildTemplates();
                    applicationAddPlugin();
                    applicationBuildCache();
                    applicationBuildSubscribeEvents();
                    applicationBindEvents();
                    applicationLoadCacheFromPersistentStore();
                    applicationCheckForDeveloper();
                    /* Start UI */
                    uiStart();
                    return self;
                };

                self.main = main;
                self.application = application;
                return self;

            };
            /**
             * It is safe to query the DOM after this invoked
             * @param  {Function}   Called when DOM is fully loaded
             * @return {Undefined}  No return
             */
            domReady(function () {
                logger.enable(config.enableAppLogs); // Don't show logs if configuration prohibits
                logger.enableStackTrace(config.enableStackTrace);
                logger.setLevelsCategories(config.applicationLevelsCategories);

                logger.log('info', 'application', 'domReady::DOM is loaded');

                try {
                    var app = application(config);
                    app.main();
                    window.app = app; // use this as a hook for debugging
                } catch (e) {
                    requirejs.onError({
                        requireType: e
                    });
                }
            });

            return application;
        });

}());
