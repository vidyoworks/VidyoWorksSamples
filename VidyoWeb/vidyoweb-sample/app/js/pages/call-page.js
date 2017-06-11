window.CallPage = React.createClass({

  getInitialState: function() { //initial states for variables for call page
    return {
      currentShareId: -1,
      isSharing: false,
      sysDesktopId: [],
      cameraMuted: false,
      micMuted: false,
      speakerMuted: false,
    }
  },

  componentDidMount: function() { //will start the call, either for chrome of npapi
    console.log("callback window : " + this.props.callbackWindow);
    this.props.callbackWindow.setState({
          stateF: this,
    });
    this.updateShareList();
  },

  sendLeaveEvent: function () { //will stop the call
    var inEvent = {
        'type': "InEventLeave"
    };
    vidyoClient.sendEvent(inEvent);
    this.props.onCallStoped();
  },

  toggleCamera: function () //will toggle camera as active or not
  {
    this.setState({
      cameraMuted: !this.state.cameraMuted,
    }, function() {
      this.sendMuteCameraEvent(this.state.cameraMuted);
    }.bind(this));
  },

  toggleMic: function() //will toggle mic as mute or not
  {
    this.setState({
      micMuted: !this.state.micMuted,
    }, function() {
      this.sendMuteMicEvent(this.state.micMuted);
    }.bind(this));
  },

  toggleSpeaker: function() //will toggle camera as active or not
  {
    this.setState({
      speakerMuted: !this.state.speakerMuted,
    }, function() {
      this.sendMuteSpeakerEvent(this.state.speakerMuted);
    }.bind(this));
  },

  sendMuteCameraEvent: function (bMute) { //event to mute camera
    var inEvent = {
        'type': "InEventMuteVideo",
        'willMute': true
    };
    inEvent.willMute = bMute;

    vidyoClient.sendEvent(inEvent);
  },


  sendMuteMicEvent: function (bMute) { //event to mute mic
      var inEvent = {
          'type': "InEventMuteAudioIn",
          'willMute': true
      };
      inEvent.willMute = bMute;

      vidyoClient.sendEvent(inEvent);
  },


  sendMuteSpeakerEvent: function (bMute) { //event to mute speaker
      var inEvent = {
          'type': "InEventMuteAudioOut",
          'willMute': true
      };
      inEvent.willMute = bMute;

      vidyoClient.sendEvent(inEvent);
  },

  updateShareList: function() { //will update the list of dropdowns (apps that you can share your screen)
    console.log('updateShareList()');
    var request = {
        'type': "RequestGetWindowsAndDesktops"
    };
    vidyoClient.sendRequest(request, this.updateShareDropDown);
  },

  updateShareDropDown: function(response){ //when getting callback, will set the dropdowns for share list
    console.log("updateShareDropDown(): " + response);

    var transformedData = {
        windows: [],
        desktops: [],
        sharing: (this.state.currentShareId === -1) ? false : true
    };
    var i,
    name,
    mywindow,
    desktop;
    //windows and desktops are separated in the response
    //you may choose not to expose all windows and/or desktops based on the use case. The filtering would happen here.
    for (i = 0; i < response.numApplicationWindows; i++) {
        name = (response.appWindowAppName[i] && response.appWindowAppName[i].length) ? response.appWindowAppName[i] : response.appWindowName[i];
        mywindow = {
            id: response.appWindowId[i],
                name: name,
                highlight: (this.state.currentShareId === response.appWindowId[i]) ? true : false
        };
        transformedData.windows.push(mywindow);
    }
    this.state.sysDesktopId.length = 0;
    for (i = 0; i < response.numSystemDesktops; i++) {
        //Custom text for sharing full displays
        var desktopName = "Desktop ";
        desktopName = desktopName + (i+1).toString();
        desktop = {
            id: response.sysDesktopId[i],
            name: desktopName,
            highlight: (this.state.currentShareId === response.sysDesktopId[i]) ? true : false
        };
        transformedData.desktops.push(desktop);
        this.state.sysDesktopId.push(response.sysDesktopId[i]);
    }


    var options = $("#img_share_b");
    options.html('');

    //note that using an HTML dropdown list allows the dropdown to appear over the video window.
    //Javascript and other more complex UI may not always overlay plugin/video divs in some browsers.
    if (this.state.isSharing) {
        options.append($("<option/>").val(-1).text("Stop Sharing"));
    }

    $.each(transformedData.windows, function() {
        if (this.highlight){
           options.append($("<option selected/>").val(this.id).text(this.name));
        }else{
           options.append($("<option/>").val(this.id).text(this.name));
        }
    });
    $.each(transformedData.desktops, function() {
        if (this.highlight){
           options.append($("<option selected/>").val(this.id).text(this.name));
        }else{
           options.append($("<option/>").val(this.id).text(this.name));
        }
    });

  },

  shareChanged: function(e) {
    //keep track of what's newly shared to updated highlighting on share dropdown
    var shareId = e.target.value;
    console.log('shareChanged()' + shareId + ".. " + e);
    this.setState({
      currentShareId: shareId
    });
    //shareId = -1 means stop sharing
    if (shareId == -1) {
        this.setState({
          isSharing: false
        });
        console.log("sending unshare event");
        this.sendUnshareEvent();
    } else {
        this.setState({
          isSharing: true
        });
        console.log("sending share event with id " + shareId);
        this.sendShareEvent(shareId);
    }
  },

  sendShareEvent : function(shareId) { //will toggle sharing
    var shareType;
    var window = shareId;

    if (this.state.sysDesktopId.indexOf(shareId)!==-1){
        shareType = 'DesktopWindow';
        if (proxyWrapper.isChrome){
            window = sysDesktopId.indexOf(shareId);
        }
    }else{
        shareType = 'ApplicationWindow';
    }
    var inEvent = {
             'type': 'InEventShare',
             'window': window,
             'shareType': shareType
    };

    vidyoClient.sendEvent(inEvent);
  },

  sendUnshareEvent: function() { //will stop sharing
      var inEvent = {
          'type': 'InEventUnshare'
      };

      vidyoClient.sendEvent(inEvent);
  },

  setPreviewModeonStatusChange: function(){
    if (this.props.callbackWindow.state.fullScreenShare){
      this.setPreviewMode("None");
    }else{
       if (this.props.callbackWindow.state.participantsInCall == 2){
          if (this.props.callbackWindow.state.sharesInCall>0){
              this.setPreviewMode("Dock");
          }else{
              this.setPreviewMode("PIP");
          }
      }else if (this.props.callbackWindow.state.participantsInCall == 1){
          this.setPreviewMode("None");
      }else{
          this.setPreviewMode("Dock");
      }
   }
  },

  setPreviewMode: function(previewMode){
    var inEvent = {
        'type': "EventPreview"
    };
    inEvent.previewMode = previewMode;
    vidyoClient.sendEvent(inEvent);
  },

  setPreferredMode : function(preferred){ //will set preferred mode
    var inEvent = {
        'type': "InEventLayout"
    };
    inEvent.numPreferred = preferred;
    vidyoClient.sendEvent(inEvent);
  },

  clientSharesSetCurrent: function () {
    this.clientSharesGet(this.displayNewShare);
  },

  clientSharesGet: function (callback) {
    var request = {};
    request.type = "RequestGetWindowShares";

    // public properties for created object,
    // initial values of which are potentially passed
    // into this factory function
    request.requestType ="";// params && params.requestType || "";
    request.remoteAppUri = [""];//params && params.remoteAppUri || [""];
    request.remoteAppName = [""];// params && params.remoteAppName || [""];
    request.numApp = 0;// params && params.numApp || 0;
    request.currApp = 0;// params && params.currApp || 0;
    request.eventUri = "";// params && params.eventUri || "";
    request.newApp =  0;//params && params.newApp || 0;

    vidyoClient.sendRequest(request, callback);
  },

  displayNewShare: function(request) {
    var shares = request.numApp;
    //if there's a new share, display it
    if (this.props.callbackWindow.state.newShareURI){
        for (var i = 0; i < request.numApp; i++){
            if (request.remoteAppUri[i]==this.props.callbackWindow.state.newShareURI){
                request.newApp = i+1;
                break;
            }
        }
    //otherwise (when shares are removed), display the last share added
    }else{
        request.newApp = request.numApp;
    }
    request.type = "RequestSetWindowShares";
    request.requestType = "ChangeSharingWindow";

    //FIX: add response callback to check for success
    vidyoClient.sendRequest(request);
  },

  setParticipantLimit: function(count){ //will set the participant limit
      if (count>8 || count<0)
        count = 16;
      var inEvent = {
          'type': "InEventParticipantsLimit",
    'maxNumParticipants': count
      };
      vidyoClient.sendEvent(inEvent);

  },

  render: function(){ //layout for the call page, including the buttons
    return (
      <div className="buttons" id="Buttons">
        <div className="toolbarBlock left">
          <button id="disconnectButton" onClick={this.sendLeaveEvent}></button>
        </div>
        <div className="toolbarBlock centerBlock">
          <button id="cameraButton" className={this.state.cameraMuted ? 'muted':''} onClick={this.toggleCamera}></button>
          <button id="micButton" className={this.state.micMuted ? 'muted':''} onClick={this.toggleMic}></button>
          <button id="speakerButton" className={this.state.speakerMuted ? 'muted':''} onClick={this.toggleSpeaker}></button>
        </div>
        <div className="toolbarBlock right">
          <div className="share-select-style">
            <select id="img_share_b"
                onMouseEnter={this.updateShareList}
                onChange={this.shareChanged}
                 value="Share">
            </select>
          </div>
        </div>
      </div>
    );
  },
});
