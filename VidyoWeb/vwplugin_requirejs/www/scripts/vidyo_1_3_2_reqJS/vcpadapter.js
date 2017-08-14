/**
 * @fileOverview This file defines an adapter for the vwer. 1.3.2 VidyoClient and plugin.
 * @author Vidyo Inc.
 * @version 1.0.0
 */

define(["./proxywrapper"],
    function () {

        // Remarks:
        //    1. Assumes inclusion of proxywrapper.js !
        // 

        var logger = null;

        var locVcpadapter = {
        
           pluginDetected: false,
           pluginVersion: "not initialized",
        
           // ----- Public APIs -----
        
           init: function(loggerArg) {
              logger = loggerArg;
           },
        
           // logic to detect plugin, it checks, if chrome will try to detect the chrome plugin, if not npapi
           detectPlugin: function() {
              var retv;
              if (this.isChrome) {
                 // *** temporary ***
                 logger.log('error', 'plugin', "unexpected execution path in detectPlugin()");
                 return(false);
                 // *** temporary ***
              } else {
                 retv = this.detectNPAPIPlugin();
              }
           return(retv);
           },
        
           startVidyoClient : function(contextObject) {
              var retv;
              if (proxyWrapper.isChrome) { //checks to see if is chrome, if chrome will start vidyoforWeb, if not the npapi plugin
                 // *** temporary ***
                 logger.log('error', 'plugin', "unexpected execution path in startVidyoClient()");
                 return(false);
                 // *** temporary ***
              } else {
                 retv = this.startPlugin(contextObject);
              }
           return(retv);
           },
        
        
           // ----- Private Methods -----
        
            isChrome: (function() { // This method returns true if the running browser is Google Chrome version 42+
              // if (navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
              //  navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42) {
              if ((navigator.appVersion.indexOf("Win")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1) ||
                (navigator.appVersion.indexOf("Mac")!=-1 && navigator.userAgent.toLowerCase().indexOf('chrome') !== -1 &&
                  navigator.userAgent.substr(navigator.userAgent.lastIndexOf('Chrome/') + 7, 10).split('.')[0] >= 42)){
                return true;
              } else {
                return false;
              }
            })(),
        
        
          // will detect if there is a npapi plugin
          detectNPAPIPlugin: function() {
            navigator.plugins.refresh(false);     // do not reload open documents
        
            // !!!
            this.pluginVersion = "1.3.20.0006";
        
            /* Try NPAPI approach */
            var plugin = navigator.plugins['VidyoWeb'];
            if(plugin){
              if (plugin.version == "VidyoWeb " + this.pluginVersion){
                this.pluginDetected = true;
              }
            }
        
            var retv = this.addPluginToDom();
            return(retv);
          },
        
          detectVidyoClientForWeb: function() { //method to check for vidyo client for web
            // *** temporary ***
            logger.log('error', 'plugin', "unexpected execution path in detectVidyoClientForWeb()");
            return;
            // *** temporary ***
          },
        
          detectChromePlugin: function() { //will try to search for chrome plugin
            // *** temporary ***
            logger.log('error', 'plugin', "unexpected invocation of detectChromePlugin()");
            return;
            // *** temporary ***
          },
        
          // add the plugin html element, in which the plugin will be installed
          addPluginToDom : function() {
            // don't add if already added
            var pluginHTML = window.document.getElementById('plugin');
        
            if (!pluginHTML) { // it's not added, so will try to add
                logger.log('info', 'plugin', "Attempting to add plugin to DOM ...");
        
                var pluginMimeType = "application/x-vidyoweb-";
                pluginMimeType+= this.pluginVersion;
        
                pluginHTML = window.document.createElement('object');
        
                pluginHTML.className = 'plugin';
                pluginHTML.id = 'plugin';
                pluginHTML.width = "100%";
                pluginHTML.height = "100%";
        
                var ie_version = this.whichIE(); //checks what version of IE
        
                // use the correct 1.1.1 HTML element
                var holder = window.document.getElementById('pluginContainer');
        
                if (ie_version && ie_version < 11){
                    holder.appendChild(pluginHTML);
                }
        
                try {
                    pluginHTML.type = pluginMimeType; // sets the mime type
                } catch (e) {
                    var mesg = "Unable to Instantiate VidyoWeb: " + pluginMimeType + "; Error:" + e;
                    logger.log('error', 'plugin', mesg);
        
                    if (ie_version && ie_version < 11){
                        holder.removeChild(pluginHTML);
                    }
                    return false;
                }
        
                if (!pluginHTML.parentNode) {
                    holder.appendChild(pluginHTML);
                }
                if (!pluginHTML.start) { //if plugin doesn't have start method, will remove it, it is not correctly added
                    holder.removeChild(pluginHTML);
                    return false;
                }
            }
            logger.log('info', 'plugin', "succesfully loaded the plugin");
            return true;
          },
        
          startVidyoClientForWeb : function() { //will init vidyoForWeb
            // *** temporary ***
            logger.log('error', 'plugin', "unexpected invocation of startVidyoClientForWeb()");
            return;
            // *** temporary ***
          },
        
          // initializes npapi plugin
          startPlugin : function (contextObject)   {
              var retv;
              var pluginHTML = window.document.getElementById('plugin');
        
              // set the configuration
              var locConfig = {
                  plugin: pluginHTML,
                  outEventCallbackObject: contextObject,      // callbacks actually do not use 'this' (they use 'self')
                  defaultOutEventCallbackMethod:              // M.F. --- should NOT get called
                     function (event) {
                        logger.log('warning', 'plugin', "invoked default callback for VidyoClient event: ",
                           event.type);
                     },
                  useCallbackWithPlugin: true
              };
        
              // add callbacks
              $.each(contextObject.callbacks, function (key, val) {
                 contextObject.client.setOutEventCallbackMethod(key, val);
              });
        
              if (contextObject.client.start(locConfig)) {
                  logger.log('info', 'plugin', "VidyoClient lib started successfully");
                  retv = true;
              } else {
                  logger.log('error', 'plugin', "failed to start VidyoClient lib!");
                  retv = false;
              }
          return(retv);
          },
        
          //checks version of IE
          whichIE: function() {
            var undef,
                rv = -1,         // Return value assumes failure.
                ua = window.navigator.userAgent,
                msie = ua.indexOf('MSIE '),
                trident = ua.indexOf('Trident/'),
                rvNum;
            if (msie > 0) {
                // IE 10 or older => return version number
                rv = parseInt(ua.substring(msie + 5, ua.indexOf('.', msie)),10);
            } else if (trident > 0) {
                // IE 11 (or newer) => return version number
                rvNum = ua.indexOf('rv:');
                rv = parseInt(ua.substring(rvNum + 3, ua.indexOf('.', rvNum)),10);
            }
            return ((rv > -1) ? rv : undef);
          }
        
        };

        return locVcpadapter;
    }
);

