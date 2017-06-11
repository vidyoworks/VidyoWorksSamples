window.LoginAsGuest = React.createClass({

  getInitialState: function() { //variables initial state
    return {
      loggedIn: false,
      text: "",
    }
  },


  joinGuestLink : function() {
    let name = this.refs.name.value;
    let link = this.refs.link.value;
    if(!!name && !!link){ //will start logic to start as guest
      this.props.callbackWindow.setState({
        loggedAsGuest: true,
        loggedAsReg: false,
        guestName: name,
        valueLink: link,
        inCall: false,
        joiningCall: true,
        showLoader: true,
        enableJoinButton: false,
      }, function(){
        if (proxyWrapper.isChrome) {
          this.detectCameraStatusAndContinue();
        } else {
          this.sendJoinEvent();
        }
      }.bind(this));
    }else{
      this.setState({ //if fields not complete, will show error
        text: "Please Complete Fields!!!",
      });
    }
  },

  detectCameraStatusAndContinue : function() { //will make a request to get camera status, if it is ready, will start chrome video, if not try again in 2 seconds
    proxyWrapper.sendRequest({type: 'RequestGetCameraStatus'}, function(cameraReady) {
        if (cameraReady.status) {
            this.startChromeVideo();
        } else {
            setTimeout(detectCameraStatusAndContinue, 2000);
        }
    }.bind(this));
  },

     //CHROME EXTENSION + non-NPAPI plugin
  startChromeVideo : function() { //will start the video
    var retval = false;
    var holder = this.props.pluginDOM;
    holder.innerHTML = '<video autoplay style="width:100%; height: 100%; background: black;" ondblclick="onDoubleClickChrome()"></video>' + '<label id="lbl_usermedia" style="position: relative; color: #ddd; top: -50%; margin-left: 20px; font-size: 20px; font-family: arial;" >' + 'Make sure to allow the browser to use your camera.</label>';

    var usermediaMessage = document.getElementById('lbl_usermedia');
    var video = holder.childNodes[0];

    proxyWrapper.useVideoElem(video, function(message, permissionDeniedError) {
        usermediaMessage.innerHTML = message;
        if (!permissionDeniedError && !message) { //if no errors will start
            this.sendJoinEvent();
        } else if (permissionDeniedError) {
            window.alert('VidyoWeb needs access to your camera in order to join a conference.' + 'If you change your mind, click the camera icon in your url bar and allow the browser to use your devices');
        } else {
            window.alert('VidyoWeb could not start your camera. Please reload the page and try again.');
        }
    }.bind(this));
  },

  sendJoinEvent : function () { //will check to see if it has to login or not, and what type of login
    this.sendGuestLogin();
    this.props.callbackWindow.setState({
      joinType: "guest",
    });
    this.props.callbackWindow.beginProgressBar();
  },

  extractPortalroom:function(){
    var data ={};
    var linkFormat = this.props.callbackWindow.state.valueLink.split('join/');
    if(linkFormat.length>1){
       data.portalAddress = linkFormat[0];
       data.roomKey = linkFormat[1];
    }
    else{
      var linkVal=this.props.callbackWindow.state.valueLink;
      data.portalAddress= linkVal.substring(0,linkVal.indexOf('?')-10); 
      data.roomKey  = linkVal.substring(linkVal.indexOf('key=')+4, linkVal.length) ;
    }
    
    return data;
    
  },
  sendGuestLogin : function () { //will login as a guest
    if (!this.props.callbackWindow.state.valueLink){
        return 0;
    }

    var encoded;
    if (!this.props.callbackWindow.state.url_encoded || (parseInt(this.props.callbackWindow.state.url_encoded,10)==0)){
        encoded = 0;
    }else{
        encoded = 1;
    }
    var portalRoomData= this.extractPortalroom();
  // var portalAddress = this.props.callbackWindow.state.valueLink.split('join/')[0];
    //var roomKey = this.props.callbackWindow.state.valueLink.split('join/')[1];

    var inEvent = {
        'type': "PrivateInEventVcsoapGuestLink",
        'typeRequest': "GuestLink",
        'requestId': 1234,
        'portalUri': portalRoomData.portalAddress,
        'roomKey'  : portalRoomData.roomKey,
        'guestName': this.props.callbackWindow.state.guestName,
        'loginType': "guest"
    };

    if (this.props.callbackWindow.state.url_roomPin){
        inEvent.pin = this.props.callbackWindow.state.url_roomPin;
    }
    vidyoClient.sendEvent(inEvent);
  },

  render: function(){ //this is the layout of the join as guest page
    let pageContent = (
        <div className="center-aligned">
                <input className="vidyo-text" type="text" ref="link" placeholder="Room Link"/><br></br>
                <input className="vidyo-text" type="text" ref="name" placeholder="Guest Name"/><br></br>
                <button className="btn btn-lg vidyo" onClick={this.joinGuestLink} disabled={!this.props.callbackWindow.state.enableJoinButton}>Join</button>
                <h1  className="center-aligned"><blink>{this.state.text}</blink></h1>
        </div>
      );

    return (
      <div>
        {pageContent}
      </div>
    );
  },
});
