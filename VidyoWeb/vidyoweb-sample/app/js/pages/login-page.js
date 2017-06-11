window.LoginAsRegUser = React.createClass({

  getInitialState: function() { //variables initial state
    return {
      loggedIn: false,
      text: "",
    }
  },

  logInUser : function() { //will start the login process
    let portal = this.refs.Portal.value;
    let login = this.refs.Login.value;
    let password = this.refs.Password.value;
    if(!!portal && portal.indexOf("https://") == -1 && portal.indexOf("http://") == -1){ //will put https:// in case it doesn't exist in the link
        portal = "https://" + portal;
    }
    if(!!portal && !!login && !!password){
      this.setState({
              loggedIn: true,
      });
      this.addText('Logging in, please wait....');
      this.props.callbackWindow.setState({
        loggedAsReg: true,
        enableLoginButton: false,
        url_portalAddress : portal,
        url_user          : login,
        url_pass          : password,
        stateF: this,
        joinType: "user",
        inCall: false,
        showLoader: true,
      }, function(){
        this.sendUserLogin();
      }.bind(this));
    }else{ //if the fields are not all complete will show an error
      this.addText('Please Complete Fields!!!');
    }
  },

  addText : function (text) { //function to add text to the output
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  sendUserLogin : function () { //will login as a user
     if (!this.props.callbackWindow.state.url_portalAddress || !this.props.callbackWindow.state.url_user || !this.props.callbackWindow.state.url_pass){
         return 0;
     }
     if (this.props.callbackWindow.state.useLoginEvent){
       var inEvent = {
            'type': "InEventLogin",
            'portalUri': this.props.callbackWindow.state.url_portalAddress,
            'userName': this.props.callbackWindow.state.url_user,
            'userPass': this.props.callbackWindow.state.url_pass
        };
        vidyoClient.sendEvent(inEvent);
    } else {
        this.sendSoapUserLogin()
            .done(function (response) {
                if (response) {
                    var mesg = "Login Response: " + response;
                    console.log(mesg);
                    vidyoClient.sendRequest({type: 'RequestGetEID'}, function(response) {
                        if (response.EID) {
                            this.sendSoapUserLinkEndpoint(response.EID);
                        }
                    });
                    //"BGHT4Z2VTJUJ7HTRCNHQS4YSQXZZZBSFZR2J5HPHYE97400VM0001@sandboxga.vidyo.com:17992;transport=TCP"
                    var vmsplit = response.vmaddress.split("@");
                    var vmIdentity = vmsplit[0];
                    var serverplit = vmsplit[1].split(":");
                    var serverAddress = serverplit[0];
                    var secured = response.vmaddress.indexOf("TLS");
                    var proxyAddress = "";
                    if (response.proxyaddress)
                        proxyAddress = response.proxyaddress.substring(0,response.proxyaddress.length-4);
                    if (secured > 0)
                        secured = true;
                    else
                        secured = false;

                    var SignInEvent = {
                        'type': "InEventSignIn",
                        'serverAddress': serverAddress,
                        'serverPort': "17992",
                        'userName': this.props.callbackWindow.state.url_user,
                        'portalAccessKey': response.pak,
                        'portalAddress': this.props.callbackWindow.state.url_portalAddress + "/services/",
                        'portalVersion': "",
                        'vmIdentity': vmIdentity,
                        'locationTag': response.loctag,
                        'vidyoProxyAddress': [proxyAddress],
                        'vidyoProxyPort': ["443"],
                        'emcpSecured': secured,
                        'guestLogin': false,
                        'showDialpad': true,
                        'showStartmeeting': true
                    };
                    vidyoClient.sendEvent(SignInEvent);
                }
            })
            .fail(function () {
                console.log("Failed");
            });
    }
  },

  sendSoapUserLogin: function () { //soap user login function
    return this.props.callbackWindow.sendSoapUserRequest("logIn","", this.state.url_portalAddress, this.state.url_user, this.state.url_pass);
  },

  sendSoapUserLinkEndpoint: function(endpointID){
    var body = {
        EID: endpointID
    };

    return this.props.callbackWindow.sendSoapUserRequest("linkEndpoint",body, this.state.url_portalAddress, this.state.url_user, this.state.url_pass);
  },

  render: function(){ //this is the layout of the logged in page
    var loader = "";
    if(this.state.loggedIn){ //will only show the loader after you press the Login button
      loader = (
          <div className="center-aligned">
            <img src="/images/spinner.gif" className="pic"></img>
          </div>
        );
    }
    let pageContent = (
        <div className="center-aligned">
                <input className="vidyo-text" type="text" ref="Portal" placeholder="Portal"/><br></br>
                <input className="vidyo-text" type="text" ref="Login" placeholder="Login"/><br></br>
                <input className="vidyo-text" type="password" ref="Password" placeholder="Password"/><br></br>
                <button className="btn btn-lg vidyo" disabled={!this.props.callbackWindow.state.enableLoginButton} onClick={this.logInUser}>Login</button>
        </div>
      );

    let leftBlock = (
      <div className="block">
        {pageContent}
        {loader}
      </div>
    );
    let rightBlock = (
      <div className="block">
        <textarea value={this.state.text}>
        </textarea>
      </div>
    );

    return (
      <div className="center-aligned">
        {leftBlock}
        {rightBlock}
      </div>
    );
  },
});
