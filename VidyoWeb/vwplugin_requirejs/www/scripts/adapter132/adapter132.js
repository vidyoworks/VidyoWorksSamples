
//
// Remarks:
//    1. Assumes inclusion of proxywrapper.js !
// 
// 

var adapter123 = {

   pluginDetected: false,
   pluginVersion: "not initialized",


   // ----- Public APIs -----

   // logic to detect plugin, it checks, if chrome will try to detect the chrome plugin, if not npapi
   detectPlugin: function() {
      var retv;
      if (this.isChrome) {
      
      
         // *** !!! ***
         console.log("ERROR: unexpected execution path in detectPlugin()");
         return(false);
         // *** !!! ***
         
         
         retv = this.detectChromePlugin();
      } else {
         retv = this.detectNPAPIPlugin();
      }
   return(retv);
   },

   startVidyoClient : function(contextObject) {
      var retv;
      if (proxyWrapper.isChrome) { //checks to see if is chrome, if chrome will start vidyoforWeb, if not the npapi plugin
      
      
         // *** !!! ***
         console.log("ERROR: unexpected execution path in startVidyoClient()");
         return(false);
         // *** !!! ***
         
         
         contextObject.client.setProxy(proxyWrapper);
         retv = this.startVidyoClientForWeb();
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


    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //*** this.pluginVersion = "1.3.10.0004";
    this.pluginVersion = "1.3.20.0006";
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    /* Try NPAPI approach */
    var plugin = navigator.plugins['VidyoWeb'];
    if(plugin){
      if (plugin.version == "VidyoWeb " + this.pluginVersion){
        this.pluginDetected = true;
      }
    }

    // 
    // M.F. (info):
    // 
    // some online postings mentioned (for THE OLD versions of IE ?):
    //    for each plugin...
    //    // if plugins array is there and not fake
    //    if (navigator.plugins && navigator.plugins.length > 0) {
    //       var pluginsArrayLength = navigator.plugins.length;
    //       for (pluginsArrayCounter=0; pluginsArrayCounter < pluginsArrayLength; pluginsArrayCounter++ ) {
    //           // loop through all desired names and check each against the current plugin name
    //           var numFound = 0;
    //           for(namesCounter=0; namesCounter < daPlugins.length; namesCounter++) {
    //              // if desired plugin name is found in either plugin name or description
    //              if( (navigator.plugins[pluginsArrayCounter].name.indexOf(daPlugins[namesCounter]) >= 0) || 
    //                  (navigator.plugins[pluginsArrayCounter].description.indexOf(daPlugins[namesCounter]) >= 0) ) {
    //                  // this name was found
    //                  numFound++;
    //              }   
    //           }
    //           // now that we have checked all the required names against this one plugin,
    //           // if the number we found matches the total number provided then we were successful
    //           if(numFound == daPlugins.length) {
    //              pluginFound = true;
    //              // if we've found the plugin, we can stop looking through at the rest of the plugins
    //              break;
    //           }
    //       }
    //    }
    // 
    // 
    // For Internet Explorer 11 you can use navigator.plugins JS API, but you need to add apropriate registrey
    // keys in order for IE11 to detect it.
    // Then checking for the plugin existence is done using this code:
    //    var plugin = navigator.plugins["<your plugin activex id>"];
    //    if(plugin) {
    //      //plugin detected
    //    } else {
    //      //plugin not found
    //    }
    // 

    /* Try IE approach (add object to DOM)*/

    // *** this.setState({
    // ***   pluginAddedToDom: this.addPluginToDom(),
    // *** }, function(){
    // ***    if (this.state.pluginAddedToDom) {
    // ***       this.addText('detectPlugin() -- Plugin added to DOM');
    // ***       this.setState({
    // ***         pluginDetected: true,
    // ***       }, function(){
    // ***         this.props.onPluginDetected();
    // ***       }.bind(this));
    // ***     }else{
    // ***       //will show install page if not supported
    // ***       this.addText('version not supported, need to install VidyoWeb');
    // *** 
    // ***           this.setState({
    // ***             showInstallPage: true,
    // ***       });
    // ***   }
    // *** });

    var retv = this.addPluginToDom();
    return(retv);
  },


  detectVidyoClientForWeb: function() { //method to check for vidyo client for web


    // *** !!! ***
    console.log("ERROR: unexpected invocation of detectVidyoClientForWeb()");
    return;
    // *** !!! ***


    // *** let checkVersion = proxyWrapper.supportedVersions[0]; //takes the supported versions array, in order to check
    // *** 
    // *** proxyWrapper.sendEvent({
    // ***   type: 'RequestConnectVersion',
    // ***   version: checkVersion
    // *** }, function(connectRes) {
    // *** 
    // ***   this.addText("proxyWrapper.sendEvent(RequestConnectVersion): " + JSON.stringify(connectRes)); //function that checks, if version is correct, will continue
    // *** 
    // ***   // Check if connection to vidyoWeb was successful
    // ***   if (!!connectRes.result) {
    // ***     proxyWrapper.isSupportedVersion(function(supported, version) {
    // *** 
    // ***       if (supported) { //if is it supported, then will set pluginDetected to true, and will call logic to continue
    // ***         this.addText("proxyWrapper.isSupportedVersion: supported:" + supported + ", version:" + version);
    // ***         this.setState({
    // ***           noVidyoPluginDetected: false,
    // ***           noVidyoWebPluginDetected: false,
    // ***           vidyoWebDetectionTries: 0,
    // ***           showInstallPage: false,
    // ***         }, function(){
    // ***           this.setState({
    // ***             pluginDetected: true,
    // ***           }, function(){
    // ***             this.props.onPluginDetected();
    // ***           }.bind(this));
    // ***         }.bind(this));
    // ***         this.addText('');
    // ***         this.addText('VidyoClientForWeb detected. Go to the next step.');
    // ***       } else {
    // ***         this.addText('version not supported, need to install VidyoClientforWeb'); //will show install page if not supported
    // *** 
    // ***         this.setState({
    // ***           showInstallPage: true,
    // ***         });
    // *** 
    // ***         this.addText("Will check version again after short delay");
    // ***         setTimeout(this.detectVidyoClientForWeb, 4000);
    // ***       }
    // *** 
    // ***     }.bind(this));
    // ***   } else {
    // ***     /*
    // ***     If there's no answer from VidyoWeb for 2 tries with 2 second intervals in between them,
    // ***     display an error message.
    // ***     */
    // ***     this.addText('no version sent');
    // *** 
    // ***     if (this.state.vidyoWebDetectionTries > 2) {
    // ***       this.setState({
    // ***         noVidyoWebPluginDetected: true,
    // ***       });
    // ***     } else {
    // ***       this.setState({
    // ***         vidyoWebDetectionTries: this.state.vidyoWebDetectionTries + 1,
    // ***       }, function() {
    // ***         setTimeout(this.detectVidyoClientForWeb, 2000);
    // ***       }.bind(this));
    // ***     }
    // ***   }
    // *** }.bind(this));

  },

  detectChromePlugin: function() { //will try to search for chrome plugin


    // *** !!! ***
    console.log("ERROR: unexpected invocation of detectChromePlugin()");
    return;
    // *** !!! ***


    // *** proxyWrapper.detectExtension('mmedphfiemffkinodeemalghecnicmnh', function (extensionInstalled) { //function in the proxywrapper that checks for installed extensions
    // ***   if (!!extensionInstalled && !this.state.didCheckExtension) { //the extension is installed, and then it will connect and continue with the detection logic
    // ***     this.setState({
    // ***       didCheckExtension: true,
    // ***       extensionInstalled: true,
    // ***     });
    // *** 
    // ***     proxyWrapper.connect();
    // ***     proxyWrapper.setOutEventDispatchMethod(this.props.onOutEvent); // will set the callback where the vidyo data is being catched
    // *** 
    // ***     this.detectVidyoClientForWeb(); //will continue checking for the vidyo client for web app
    // ***   } else if (extensionInstalled && this.state.didCheckExtension) { //when instalation is done will enter here, and will reinit the detection
    // ***     window.location.href = window.location.href + "?autoDetect";
    // ***   } else {
    // ***     this.setState({
    // ***       didCheckExtension: true,
    // ***       showInstallButton: true,
    // ***     });
    // ***     this.addText('Extension not detected. Please install the extension to continue.')
    // *** 
    // ***     setTimeout(this.detectChromePlugin, 2000); //will set a loop that checks when instalation is done
    // ***   }
    // *** }.bind(this));

  },

  // add the plugin html element, in which the plugin will be installed
  addPluginToDom : function() {
    // don't add if already added

    // *** var pluginHTML = this.props.document.getElementById('plugin');
    var pluginHTML = window.document.getElementById('plugin');

    if (!pluginHTML) { // it's not added, so will try to add
        console.log("INFO: Attempting to add plugin to DOM ...");

        var pluginMimeType = "application/x-vidyoweb-";
        pluginMimeType+= this.pluginVersion;

        //
        // in 1.3.2 react-app.js (JSX):
        //
        // let pluginDOM = (
        //   <div id="pluginOverlay" className={pluginClass}>
        //     <div id="pluginWrapper">
        //       <div id="pluginHolder"></div>
        //     </div>
        //   </div>
        // );
        //
        //
        // in 1.1.1 index.html:
        //
        // <div id="pluginAndChatContainer" class="pull-right">
        //     <div id="pluginContainer" class="off">
        //         <!-- Will autogenerate plugin tag -->
        //         <br/>
        //     </div>
        //     <!-- End Plugin wrapper  -->
        //     .....
        // </div>
        //

        //
        // M.F. constructs element of type 'object' and then sets its type - this is what
        // wires it up to the binary plugin ! 
        //


        // *** pluginHTML = this.props.document.createElement('object');
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
            console.log(mesg);
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
    console.log("INFO: succesfully loaded the plugin");
    return true;
  },

  startVidyoClientForWeb : function() { //will init vidyoForWeb


    // *** !!! ***
    console.log("ERROR: unexpected invocation of startVidyoClientForWeb()");
    return;
    // *** !!! ***


    proxyWrapper.start(function (startRes) {
        if(!startRes.error) {
            this.addText('VidyoClient started');
            this.props.onPluginInitialised(); //will go to the react-app page to continue init
        }
    }.bind(this));
  },

  // initializes npapi plugin
  startPlugin : function (contextObject)   {
      var retv;

      // application is the global object -> 'self'

      // *** if(this.props.addedToDom){ //checks to see if the view is added to the DOM

      // *** var pluginHTML = this.props.document.getElementById('plugin');
      var pluginHTML = window.document.getElementById('plugin');

      // set the configuration
      var locConfig = {

          plugin: pluginHTML,

          // old way (e.g. 1.3.2):
          // --------
          // *** outEventCallbackObject: this.props.callbackWindow,
          // *** defaultOutEventCallbackMethod: "onOutEvent",
          // *** useCallbackWithPlugin: this.state.useCallbackForOutEvents


          // new way (e.g. 1.1.1):
          // --------
          outEventCallbackObject: contextObject,      // callbacks actually do not use 'this' (they use 'self')
          defaultOutEventCallbackMethod:              // M.F. --- should NOT get called
             function (event) {
                // *** logger.log('info', 'plugin', 'default callback for client lib: ', event);
                console.log("INFO: invoked default callback for VidyoClient lib: ", event);
             },
          useCallbackWithPlugin: true
      };

      // add:
      // ----
      /* Set all callbacks */
      $.each(contextObject.callbacks, function (key, val) {
         contextObject.client.setOutEventCallbackMethod(key, val);
      });

      if (contextObject.client.start(locConfig)) {
          // *** this.addText("VidyoWeb started successfully"); //started succesfully
          console.log("INFO: VidyoClient lib started successfully");
          retv = true;
      } else {
          // *** this.addText("VidyoWeb did not start successfully!");
          console.log("ERROR: failed to start VidyoClient lib");
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

    // *** this.addText("userAgent: " + ua);

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


/* End of File */

