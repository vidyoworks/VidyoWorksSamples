var App = React.createClass({
  getInitialState: function () { //initial states for variables for the app
    return {
      activeTab: 'pluginDetection',
      pluginInstalled: false,
      pluginInitialised: false,
      loggedAsReg: false,
      loggedAsGuest: false,
      pluginStopped: false,
      useLoginEvent:true,
      inLoggedPage: false,
      url_portalAddress: "",
      url_user: "",
      url_pass: "",
      url_portalUri: "",
      url_roomPin: "",
      url_encoded: "",
      url_useSignIn: false,
      callState: "Idle",
      joinType: "guest",
      participantsInCall: 0,
      joiningCall: false,
      inCall: false,
      showLoader: false,
      valueLink:"",
      guestName: "",
      progressWidth: 0,
      addedToDom: false,
      soapProxy: "https://vidyoweb.apps.vidyo.com/sp/soap_proxy.php",
      pluginHidden: true,
      stateF: null,
      sharesInCall: 0,
      newShareURI: undefined,
      fullScreenShare: false,
      enableJoinButton: true,
      enableLoginButton: true,
      enableAcceptButton: false,
      userLogged: false,
      text: "",
      step: "",   //Stopped, Detected, Started, Logged, InConference
    }
  },
  onPluginDetected: function() { //callback from the plugin detected page
    this.setState({
              pluginInstalled: true,
              addedToDom: true,
              step: "Detected",
      }, function(){
                if(window.location.href.indexOf("?autoDetect") !== -1){
                    this.changeTab('pluginInitialisation');
                }
      }.bind(this));
  },

  onPluginInitialised: function() { //callback from the plugin initialised page page
    this.setState({
      pluginInitialised: true,
      step: "Started",
    });
  },

  joinCallState: function() { //callback from when the user tries to open the callpage from the logged In page
      this.setState({
        showLoader: true,
        inLoggedPage: true,
        inCall: false,
        joiningCall: true,
        enableJoinButton: false,
      });
  },

  onLogoutUser: function() {
    this.sendSoapUserLogOut();
    this.setState({
      inLoggedPage: false,
      userLogged: false,
      step: "Started",
      joiningCall: false,
      inCall: false,
    });
  },

  onPluginStoped: function() { //callback from when the plugin is being stoped
      var step = "Detected";
      var states = {
        pluginInitialised: false,
        pluginStopped: true,
        joiningCall: false,
        inCall: false,
        step: step,
      };
      this.setState(states);
  },

  onCallStoped: function() { //callback from when the call is being stoped
      this.setState({
        joiningCall: false,
        inCall: false,
        progressWidth: 0,
        pluginHidden: true,
      });
  },

  addText : function (text) { //function to add text to the output
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  onOutEvent: function(event) { //this function will catch all the callbacks from the library, regarding the video
    console.log("!!!onOutEvent event is : " + event.type);
      try {
          var string = "";
          if(event.error !== undefined){
            string = string + "Error:" + event.error;
          }
          if(event.message !== undefined){
            string = string + " / Message:" + event.message;
          }
          this.addText("Event reveived:" + event.type + " / " + string);
          if(this.state.stateF){
            this.state.stateF.addText("Event reveived:" + event.type + " / " + string);
          }
      }
      catch(err) {}
    switch (event.type) {
        case 'OutEventPluginConnectionSuccess':
            this.onPluginInitialised();
            break;
        case 'OutEventPluginConnectionFailure':
            if (!proxyWrapper.isChrome) {
                vidyoClient.stop();
            }
            this.setState({
              step: "Detected",
            });
            window.alert("VidyoWeb is started in another tab")
            break;
        case 'OutEventPluginError':
            if (!proxyWrapper.isChrome) {
                vidyoClient.stop();
            }
            this.setState({
              step: "Detected",
            });
            break;
        case 'OutEventReloaded':
            if (!proxyWrapper.isChrome) {
                vidyoClient.stop();
            }
            break;
        case 'extensionMsgClientClosed':
            console.log(event.message);
            break;
        case 'extensionMsgClientStarting':
            console.log("client is now starting!!!!!!!");
            break;
        case 'OutEventCallState':
            this.setState({
              callState: event.callState,
            });
            break;
        case 'OutEventSignedIn':
            if (this.state.joinType == "user"){
              console.log("User logged in");
              this.setState({
                inLoggedPage: true,
                stateF: null,
                step: "Logged",
                userLogged: true,
                enableLoginButton: true,
              });
            }
            break;
        case 'OutEventLinked':
          if (event.error) {
            this.setState({
              enableLoginButton: true,
              enableJoinButton: true,
              joiningCall: false,
              inCall: false,
            });
          }
          break;
        case 'OutEventSignIn':
            if (parseInt(event.activeEid, 10) === 0){
                var licenseEvent = {
                    'type': "InEventLicense"
                };
                vidyoClient.sendEvent(licenseEvent);
            }
            break;
        case 'OutEventIncomingCall':
              console.log('Receving a call : CallingUser-' + event.invitingUser + ', isDirectCall-' +event.isDirectCall);
              this.setState({enableAcceptButton:true});
            break;
        case 'OutEventIncomingCallEnded':
              console.log('Receving a call : ended');
              this.setState({enableAcceptButton:false});
          break;
        case 'OutEventLogicStarted':
            this.setState({
              step: "Started",
            });
            console.log('VidyoClient started correctly')
            break;
        case 'OutEventConferenceActive':
            if (proxyWrapper.isChrome){
                document.getElementsByTagName("video")[0].style.width="100%";
                document.getElementsByTagName("video")[0].style.height="100%";
            }
            this.setState({
              progressWidth: 1100,
              showLoader: false,
              pluginHidden: false,
              step: "InConference",
              joiningCall: false,
              inCall: true,
            });
            this.state.stateF.setPreferredMode(1);
            this.state.stateF.setParticipantLimit(16);
            break;
        case 'OutEventConferenceEnded':
            let step = this.state.userLogged ? "Logged" : "Started";
            this.setState({
              enableJoinButton: true,
              step: step,
				      stateF: null,
              enableAcceptButton:false,
            });
            this.onCallStoped();
            break;
        case 'OutEventJoinProgress':
            //TODO will need to show progress
            var pg = this.state.progressWidth + 200;
            this.setState({
              progressWidth: pg,
              joiningCall: true,
              inCall: false,
            });
            break;
        case 'OutEventAddShare':
            this.setState({
              sharesInCall: this.state.sharesInCall + 1,
              newShareURI: event.URI,
            });
            this.state.stateF.clientSharesSetCurrent();
            this.state.stateF.setPreviewModeonStatusChange();
            break;
        case 'OutEventRemoveShare':
            this.setState({
              sharesInCall: this.state.sharesInCall - 1,
            });
            if (this.state.sharesInCall==0){
              this.setState({
                fullScreenShare: false,
              });
              this.state.stateF.setParticipantLimit(16);
            }
            this.state.stateF.setPreviewModeonStatusChange();
            break;
        case 'OutEventParticipantsChanged':
            this.setState({
              participantsInCall: event.participantCount,
            });
            break;
        case 'PrivateOutEventGetJoinApproval':
            if (!event.joinStatus) {
                location.reload();
            }
            break;
        case 'PrivateOutEventVcsoapGuestLink':
            console.log("****** GuestID = " + event.guestID + "********");
            break;
        case 'OutEventLogin':
            if(event.error == 401){
              this.state.stateF.setState({
                loggedIn: false,
              });
              this.state.stateF.addText("Error trying to login: " + event.error);
              return;
            }
            break;
        case 'OutEventRemoteSourceAdded':
            break;
        default:
            break;
    }
  },

  changeTab: function(tabName, event) { // will change the tabs
    console.log("tabname: " + tabName + "..." + event + ".." + this.state.step);
    if (!!event) {
      event.preventDefault();
    }
    if ((tabName === "pluginDetection" && this.state.step === "") ||
        (tabName == "pluginInitialisation" && this.state.step === "Detected") ||
        (tabName == "GetConfiguration" && (this.state.step === "Started" || this.state.step === "Logged")) ||
        (tabName == "loginAsGuest" && (this.state.step === "Started")) ||
        (tabName == "loginAsRegUser" && (this.state.step === "Started" || this.state.step === "Logged")) ||
        (tabName == "pluginStop" && (this.state.step === "Started" || this.state.step === "Logged"))) {
      this.setState({
        activeTab: tabName,
      });
    }
  },

  sendSoapUserLogOut: function () { //will log out
    return this.sendSoapUserRequest("logOut","", this.state.url_portalAddress, this.state.url_user, this.state.url_pass);
  },

  beginProgressBar : function() { //will show progress bar
    this.setState({
      showLoader: true,
    });
  },

  sendSoapUserRequest: function (action, body, portalAddr, username, password) { //user request method
    if (!this.state.url_portalAddress){
        return;
    }

    try {
        return soapClient.request({
            ajaxDataType: 'jsonp',
            proxyUrl: this.state.soapProxy,
            soapAction: action,
            soapServerUrl: portalAddr,
            soapServiceUsername: username,
            soapServicePassword: password,
            soapServicePath: "/services/v1_1/VidyoPortalUserService?wsdl",
            soapBody: (body || "")
        });

    } catch (e) {
        var mesg = "Failed to send Soap request(" + action + "): " + e;
        log(mesg);
        return "";
    }
  },

  render: function() { //layout for the global page
    let tabBar = (
      <ul className="nav navbar">
        <li className={this.state.step === "" ? 'active' : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'pluginDetection')}>Detection</a></li>
        <li className={this.state.step === "Detected" ? (this.state.activeTab === 'pluginInitialisation' ? 'active':'') : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'pluginInitialisation')}>Initialize</a></li>
        <li className={this.state.step === "Started" ? (this.state.activeTab === 'loginAsGuest' ? 'active':'') : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'loginAsGuest')}>Guest</a></li>
        <li className={this.state.step === "Started" || this.state.step === "Logged" ? (this.state.activeTab === 'loginAsRegUser' ? 'active':'') : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'loginAsRegUser')}>Login</a></li>
        <li className={this.state.step === "Started" || this.state.step === "Logged" ? (this.state.activeTab === 'pluginStop' ? 'active':'') : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'pluginStop')}>Plugin Stop</a></li>
        <li className={this.state.step === "Started" || this.state.step === "Logged" ? (this.state.activeTab === 'GetConfiguration' ? 'active':'') : 'disabled'}>
          <a onClick={this.changeTab.bind(null, 'GetConfiguration')}>Configure Device</a></li>
      </ul>
    );
    let pluginClass = this.state.pluginHidden ? "pluginHidden" : "";
    let pluginDOM = (
      <div id="pluginOverlay" className={pluginClass}>
        <div id="pluginWrapper">
          <div id="pluginHolder"></div>
        </div>
      </div>
    );
    let pageContent2 = "";
    let pageContent = {
        pluginDetection: (<PluginDetectionPage onOutEvent={this.onOutEvent} onPluginDetected={this.onPluginDetected} document={document} />),
        pluginInitialisation: (<PluginInitialisationPage onPluginInitialised={this.onPluginInitialised} addedToDom={this.state.addedToDom} document={document} callbackWindow={this}/>),
        loginAsGuest: (<LoginAsGuest callbackWindow={this} pluginDOM={document.getElementById('pluginHolder')}/>),
        loginAsRegUser: (<LoginAsRegUser callbackWindow={this}/>),
        pluginStop: (<PluginStop onPluginStoped={this.onPluginStoped} document={document} />),
        GetConfiguration: (<GetConfiguration/>),
      }[this.state.activeTab];

    let title = {
      pluginDetection: "Plugin Detection",
      pluginInitialisation: "Plugin Initialisation",
      loginAsGuest: "Login as Guest",
      loginAsRegUser: "Login and Join as a registered User",
      pluginStop: "Deinitialize",
      GetConfiguration: "Configuration",
    }[this.state.activeTab];

    var pageStyle = {};
    if (this.state.activeTab === 'loginAsRegUser') {
      if (this.state.inLoggedPage && !(this.state.joiningCall || this.state.inCall)) {
        pageContent = (<LoggedPage callbackWindow={this} joinCallState={this.joinCallState} onLogoutUser={this.onLogoutUser} pluginDOM={document.getElementById('pluginHolder')}/>);
      } else if (this.state.joiningCall || this.state.inCall) {
        pageContent = "";
      }
    } else if ((this.state.activeTab === 'loginAsGuest') && (this.state.joiningCall || this.state.inCall)) {
      pageContent = "";
    }
    if (this.state.activeTab === 'loginAsRegUser' || this.state.activeTab === 'loginAsGuest') {
      if(this.state.joiningCall) {
        if(this.state.showLoader && this.state.progressWidth < 1100){
          var divStyle = {
            color: 'white',
            width: this.state.progressWidth,
          };
          pageContent2 = (
              <div>
                <div className="center-aligned-margins">
                 <img src="../images/logo-big.jpg"></img>
                </div>
                <h1 className="center-aligned-margins">Loading...</h1>
                <div className="progress center-aligned-margins">
                  <div className="progress-bar" role="progressbar" id="progressbar" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100" style={divStyle}>
                    <span className="sr-only">0% Complete</span>
                  </div>
                </div>
                <div className="block">
                  <textarea value={this.state.text}>
                  </textarea>
                </div>
              </div>
          );
        }
      }
    }
    if (this.state.inCall) {
      pageContent = (
        <div id="toolbar">
          <CallPage callbackWindow={this} onCallStoped={this.onCallStoped}/>
        </div>
      );
      tabBar = <ul className="nav navbar"></ul>;
      title = "In Call";
    }

    return (
      <div>
        <div>
          <img src="/images/logo-big.jpg" className="pic"></img>
          <div className="top">
            <p className="top-text">{title}</p>
          </div>
        </div>
        <div className="tabBarContainer">
          {
            tabBar
          }
        </div>

        <div id="content" className="center">
          {pluginDOM}
          {pageContent}
          {pageContent2}
        </div>
      </div>
    );
  }
});


ReactDOM.render(<App />, document.getElementById('app'));
