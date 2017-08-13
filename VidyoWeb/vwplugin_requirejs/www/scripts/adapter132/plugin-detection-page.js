window.PluginDetectionPage = React.createClass({
  pluginVersion: "1.3.10.0005",

  getInitialState: function() { //initial states for variables for detection page
    return {
      didCheckExtension: false,
      extensionInstalled: false,
      showInstallButton: false,

      noVidyoPluginDetected: false,
      noVidyoWebPluginDetected: false,
      vidyoWebDetectionTries: 0,

      showInstallPage: false,

      pluginDetected: false,
      pluginAddedToDom: false,

      text: "",
    }
  },

  detectNPAPIPlugin: function() { // will detect if there is a npapi plugin
    navigator.plugins.refresh(false);
    this.pluginVersion = "1.3.10.0004";
    /* Try NPAPI approach */
    var plugin = navigator.plugins['VidyoWeb'];
    if(plugin){
      if (plugin.version == "VidyoWeb " + this.pluginVersion){
            this.addText('');
            this.addText('NPAPI plugin detected. Go to the next step.');
            this.setState({
              pluginDetected: true,
            }, function(){
              this.props.onPluginDetected();
            }.bind(this));
      }
    }
    /* Try IE approach (add object to DOM)*/
    this.setState({
      pluginAddedToDom: this.addPluginToDom(),
    }, function(){
       if (this.state.pluginAddedToDom) {
          this.addText('detectPlugin() -- Plugin added to DOM');
          this.setState({
            pluginDetected: true,
          }, function(){
            this.props.onPluginDetected();
          }.bind(this));
        }else{
          this.addText('version not supported, need to install VidyoWeb'); //will show install page if not supported

              this.setState({
                showInstallPage: true,
          });
      }
    });
  },

  detectVidyoClientForWeb: function() { //method to check for vidyo client for web
    let checkVersion = proxyWrapper.supportedVersions[0]; //takes the supported versions array, in order to check

    proxyWrapper.sendEvent({
      type: 'RequestConnectVersion',
      version: checkVersion
    }, function(connectRes) {
      this.addText("proxyWrapper.sendEvent(RequestConnectVersion): " + JSON.stringify(connectRes)); //function that checks, if version is correct, will continue

      // Check if connection to vidyoWeb was successful
      if (!!connectRes.result) {
        proxyWrapper.isSupportedVersion(function(supported, version) {

          if (supported) { //if is it supported, then will set pluginDetected to true, and will call logic to continue
            this.addText("proxyWrapper.isSupportedVersion: supported:" + supported + ", version:" + version);
            this.setState({
              noVidyoPluginDetected: false,
              noVidyoWebPluginDetected: false,
              vidyoWebDetectionTries: 0,
              showInstallPage: false,
            }, function(){
              this.setState({
                pluginDetected: true,
              }, function(){
                this.props.onPluginDetected();
              }.bind(this));
            }.bind(this));
            this.addText('');
            this.addText('VidyoClientForWeb detected. Go to the next step.');
          } else {
            this.addText('version not supported, need to install VidyoClientforWeb'); //will show install page if not supported

            this.setState({
              showInstallPage: true,
            });

            this.addText("Will check version again after short delay");
            setTimeout(this.detectVidyoClientForWeb, 4000);
          }

        }.bind(this));
      } else {
        /*
        If there's no answer from VidyoWeb for 2 tries with 2 second intervals in between them,
        display an error message.
        */
        this.addText('no version sent');

        if (this.state.vidyoWebDetectionTries > 2) {
          this.setState({
            noVidyoWebPluginDetected: true,
          });
        } else {
          this.setState({
            vidyoWebDetectionTries: this.state.vidyoWebDetectionTries + 1,
          }, function() {
            setTimeout(this.detectVidyoClientForWeb, 2000);
          }.bind(this));
        }
      }
    }.bind(this));
  },

  detectChromePlugin: function() { //will try to search for chrome plugin
    proxyWrapper.detectExtension('mmedphfiemffkinodeemalghecnicmnh', function (extensionInstalled) { //function in the proxywrapper that checks for installed extensions
      if (!!extensionInstalled && !this.state.didCheckExtension) { //the extension is installed, and then it will connect and continue with the detection logic
        this.setState({
          didCheckExtension: true,
          extensionInstalled: true,
        });

        proxyWrapper.connect();
        proxyWrapper.setOutEventDispatchMethod(this.props.onOutEvent); // will set the callback where the vidyo data is being catched

        this.detectVidyoClientForWeb(); //will continue checking for the vidyo client for web app
      } else if (extensionInstalled && this.state.didCheckExtension) { //when instalation is done will enter here, and will reinit the detection
        window.location.href = window.location.href + "?autoDetect";
      } else {
        this.setState({
          didCheckExtension: true,
          showInstallButton: true,
        });
        this.addText('Extension not detected. Please install the extension to continue.')

        setTimeout(this.detectChromePlugin, 2000); //will set a loop that checks when instalation is done
      }
    }.bind(this));
  },

  detectPlugin: function() { //logic to detect plugin, it checks, if chrome will try to detect the chrome plugin, if not npapi
    let isChrome = proxyWrapper.isChrome;

    if (isChrome) {
      this.detectChromePlugin();
    } else {
      this.detectNPAPIPlugin();
    }
  },

  successFunction : function() {
  //    $scope.isOnExtensionDownloadPage = true;
  //    showInstallStep('install_extension_inline');
  },

  //oops, could not directly install, just pop-up the extension webstore
  errorFunction : function(e) {
      this.openChromeWebStore();
  },


  openChromeWebStore : function() { //will open chrome webstore
      window.open('https://chrome.google.com/webstore/detail/mmedphfiemffkinodeemalghecnicmnh', '', 'width=1000, height=600');
  },

  installExtension: function() { //will try to install extension
    if(this.state.didCheckExtension){
      chrome.webstore.install('https://chrome.google.com/webstore/detail/mmedphfiemffkinodeemalghecnicmnh', this.successFunction(), this.errorFunction());
    }else{
      this.setState({
        showInstallPage: true,
      });
    }
  },

  componentDidMount: function() { //will check if needs to auto detect
    if (window.location.href.indexOf('autoDetect') > 0){
      this.detectPlugin();
    }
  },

  addPluginToDom : function() { //logic to add the plugin html element, in which the plugin will be installed

    //don't add if already added
    var pluginHTML = this.props.document.getElementById('plugin');
    this.addText("plugin html is:" + pluginHTML + ".... document:" + this.props.document);
    if (!pluginHTML) { //it's not added, so will try to add
        this.addText("Attempting to add plugin to the DOM...");

        var pluginMimeType = "application/x-vidyoweb-";
        pluginMimeType+= this.pluginVersion;

        pluginHTML = this.props.document.createElement('object');
        pluginHTML.className = 'plugin';
        pluginHTML.id = 'plugin';
        pluginHTML.width = "100%";
        pluginHTML.height = "100%";

        var ie_version = this.whichIE(); //checks what version of IE
        var holder = this.props.document.getElementById('pluginHolder');
        if (ie_version && ie_version < 11){
            holder.appendChild(pluginHTML);
        }

        try {
            pluginHTML.type = pluginMimeType; //sets the mime type
        } catch (e) {
            var mesg = "Unable to Instantiate VidyoWeb: " + pluginMimeType + "; Error:" + e;
            this.addText(mesg);
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
    console.log("will return true");
    return true;
  },

  whichIE: function() { //checks what version of IE
    var undef,
    rv = -1,
                    // Return value assumes failure.
    ua = window.navigator.userAgent,
    msie = ua.indexOf('MSIE '),
    trident = ua.indexOf('Trident/'),
    rvNum;
    this.addText("userAgent: " + ua);

    if (msie > 0) {
                    // IE 10 or older => return version number
        rv = parseInt(ua.substring(msie + 5, ua.indexOf('.', msie)),
                      10);
    } else if (trident > 0) {
                    // IE 11 (or newer) => return version number
        rvNum = ua.indexOf('rv:');
        rv = parseInt(ua.substring(rvNum + 3, ua.indexOf('.', rvNum)),
                      10);
    }

    return ((rv > -1) ? rv : undef);
  },

  addText : function (text) { //method to add text to output
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  render: function() {
    let pageContent;
    let leftBlock;
    let rightBlock

    if (this.state.showInstallPage) {
      pageContent = ( //here will show a page to install the vidyo client for web app
        <div id="pluginInstallPage">
          <h5>Please follow the following instructions to install the VidyoWeb Plugin.</h5>
          <ol id="instructions">
            <li>Read <a href='files/EULA.html'>End User License Agreement</a>.<br/>By downloading plugin you acknowledge that you read the EULA and that you agree to it.</li>
            <li>
              Download and install the <a href="https://developer.vidyo.com/index.php/download_file/view/249/208/">VidyoWeb plugin</a>
              <ul>
                <li>If you are using Chrome: install <b>VidyoClientForWeb</b> (uses WebRTC) and restart Chrome.</li>
                <li>If you are using other browsers, e.g. Firefox or Safari, install <b>VidyoWeb</b> (NPAPI plugin)</li>
                <li>If you are using Firefox enable permissions for the VidyoWeb plugin via the </li><p href="http://about:addons">Add-ons Manager</p><p>Access it via the Settings/Add-ons or by typing "about:addons" in the browser</p>
              </ul>
            </li>
          </ol>
          <p>
            <small>&copy; 2013-2016 <a href='http://www.vidyo.com'>Vidyo</a>. All rights reserved.</small>
          </p>
        </div>
      );
    } else { //this is the normal page layout, with the output and the buttons to detect plugin and install extension, if needed
      pageContent = (
        <div>
          <div id="pluginDetection">
            <button className="btn btn-lg vidyo" onClick={this.detectPlugin}  disabled={this.state.pluginDetected}>Detect plugin</button>
            <button className="btn btn-lg vidyo" onClick={this.installExtension} disabled={!this.state.showInstallButton}>Install extension</button>
          </div>
          <div className="block">
            <textarea value={this.state.text} readOnly>
            </textarea>
          </div>
        </div>
      );
    }

    return (
      <div className="center-aligned">
        {pageContent}
      </div>
    );
  }
});
