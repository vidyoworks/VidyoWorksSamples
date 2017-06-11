window.LoggedPage = React.createClass({
  logout : function() { //will log you out by refreshing the page, for now the state is not kept
    this.props.onLogoutUser();
  },

  joinRoom : function() { //logic to join your room
    this.props.joinCallState();

    if (proxyWrapper.isChrome) {
        this.detectCameraStatusAndContinue();
    } else {
        this.sendJoinEvent();
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
            styledAlert('VidyoWeb needs access to your camera in order to join a conference.' + 'If you change your mind, click the camera icon in your url bar and allow the browser to use your devices');
        } else {
            styledAlert('VidyoWeb could not start your camera. Please reload the page and try again.');
        }
    }.bind(this));
  },

  sendJoinEvent : function () { //will check to see if it has to login or not, and what type of login
    this.props.callbackWindow.setState({
      loggedAsReg: true,
      loggedAsGuest: false,
    });
    if (!!this.props.callbackWindow.state.url_portalAddress){
        this.sendStartMyMeetingEvent();
        this.props.callbackWindow.beginProgressBar();
    }else{
        console.log("has no user, will have to login");
    }
  },
  answer :function(){
    console.log('Sending InEventAnswer');
    var inEvent = {
        'type': "InEventAnswer"
    };
    vidyoClient.sendEvent(inEvent);
  },
  sendStartMyMeetingEvent: function () { //send start my meeting event
    var inEvent = {
        'type': "PrivateInEventStartMyMeeting"
    };
    vidyoClient.sendEvent(inEvent);
  },

  acceptCalls : function() { 
    this.props.joinCallState();
    if (proxyWrapper.isChrome) {
        this.detectCameraStatusAndContinue();
        
    } 
    this.answer();
    
  },

  render: function(){ //this is the layout of the logged in page
    let pageContent = (
        <div id="pluginStop" className="center-aligned">
            <h1 className="center-aligned">You are logged in</h1><br></br>
            <button className="btn btn-lg vidyo" onClick={this.logout}>Log Out</button><br></br>
            <button className="btn btn-lg vidyo" onClick={this.joinRoom} disabled={!this.props.callbackWindow.state.enableJoinButton}>Join My Room</button><br></br>
            <button className="btn btn-lg vidyo" onClick={this.acceptCalls} disabled={!this.props.callbackWindow.state.enableAcceptButton}>Accept Incoming Calls</button><br></br>
            <p> To test the "Accept Incoming Calls" functionality, you need to login "{this.props.callbackWindow.state.url_portalAddress}" using a different account, and call this user.</p>
          </div>
      );

    return (
      <div>
        {pageContent}
      </div>
    );
  },
});
