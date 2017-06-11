window.GetConfiguration = React.createClass({

  getInitialState: function() { //initial states for the get configuration page

    return {
      onCall: false,
      devicesVisible: false,
      cameras: [],
      selectedCameraId: undefined,

      microphones: [],
      selectedMicrophoneId: undefined,

      speakers: [],
      selectedSpeakerId: undefined,

      text:""
    }
  },

  getConfiguration : function() { //this function will make a call in order to return the configurations
    this.addText('Get Configuration');
    vidyoClient.sendRequest({type: 'RequestGetConfiguration'}, function(response) {
      this.addText(JSON.stringify(response));
      if (!response.error) {
        this.setState({ //after the response it will set the states in order to fill the dropdowns
          cameras: response.cameras,
          selectedCameraId: response.currentCamera,
          microphones: response.microphones,
          selectedMicrophoneId: response.currentMicrophone,
          speakers: response.speakers,
          selectedSpeakerId: response.currentSpeaker,
          devicesVisible: true
        });
      } else {
        this.addText('An error ocurred getting your configuration.')
      }
    }.bind(this));
  },

  setConfiguration: function(fields, callback) { //call to set the configuration
    vidyoClient.sendRequest({type: 'RequestGetConfiguration'}, function(response) {
      var setRequest = {};
      setRequest.type = 'RequestSetConfiguration';
      for (var key in response) {
        if (key !== 'type' && response.hasOwnProperty(key)) {
          setRequest[key] = response[key];
        }
      }
      for (key in fields) {
        if (fields.hasOwnProperty(key)) {
          setRequest[key] = fields[key];
          if (key === 'currentCamera') {
            var cameras = response['cameras'];
            var currentCamera = setRequest['currentCamera'];
            var vidyoCameraIndex = cameras.indexOf('WebPluginVirtualCamera');
            if (vidyoCameraIndex > - 1 && currentCamera >= vidyoCameraIndex) {
              setRequest.currentCamera = setRequest['currentCamera'] + 1;
            }
          }
        }
      }
      setRequest.currentSpeaker = Math.max(0, setRequest.currentSpeaker);
      setRequest.currentMicrophone = Math.max(0, setRequest.currentMicrophone);
      setRequest.currentCamera = Math.max(0, setRequest.currentCamera);
      vidyoClient.sendRequest(setRequest, function(response) {
        if (callback) {
          callback(response);
        }
      });
    });
  },

  changeCamera: function(e) { //this method will change the camera used
    const cameraId = e.target.value;
    const camera = this.state.cameras[cameraId];

    this.setState({
      selectedCameraId: cameraId,
    }, function(){
      this.setConfiguration({currenCamera: this.state.selectedCameraId}, function(){
        this.addText('New Selected Camera => key: ' + cameraId + ' name: ' + camera);
      }.bind(this));
    });

  },

  changeMicrophone: function(e) { //this method will change the microphone used
    const microphoneId = e.target.value;
    const microphone = this.state.microphones[microphoneId];

    this.setState({
      selectedMicrophoneId: microphoneId,
    }, function(){
      this.setConfiguration({currentMicrophone: this.state.selectedMicrophoneId}, function(){
        this.addText('New Selected Micro => key: ' + microphoneId + ' name: ' + microphone);
      }.bind(this));
    });
  },

  changeSpeaker: function(e) { //this method will change the speaker used
    var speakerId = e.target.value;
    var speaker = this.state.speakers[speakerId];

    this.setState({
      selectedSpeakerId: speakerId,
    }, function(){
      this.setConfiguration({currentSpeaker: this.state.selectedSpeakerId}, function(){
        this.addText('New Selected Speaker => key: ' + speakerId + ' name: ' + speaker);
      }.bind(this));
    });
  },

  addText : function (text) { //function to add text to the state
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  render: function(){ //the layout for the configuration page
    let dropdownBlock = <div/>;
    if (this.state.devicesVisible) { //in case the devices are fetched, it will show them
      const camerasContent = this.state.cameras.map(function(item, index) { //the dropdown items for cameras
        return (
          <option key={index} value={index}>
            {item}
          </option>
        );
      }.bind(this));
      const microphonesContent = this.state.microphones.map(function(item, index) { //the dropdown items for microphones
        return (
          <option key={index} value={index}>
            {item}
          </option>
        );
      }.bind(this));
      const speakersContent = this.state.speakers.map(function(item, index) { //the dropdown items for speakers
        return (
          <option key={index} value={index}>
            {item}
          </option>
        );
      }.bind(this));

      dropdownBlock = ( //this is the layout which contains the dropdowns
        <div id="dropdownBlock">
        <div>
          <label htmlFor="cameraSelect">Camera</label>
            <div className="select-style">
              <select
                id="cameraSelect"
                className="selectpicker show-menu-arrow"
                name="cameraSelect"
                value={this.state.selectedCameraId}
                onChange={this.changeCamera}>
                  {camerasContent}
              </select>
            </div>
          </div>
          <div>
            <label htmlFor="microSelect">Microphone</label>
            <div className="select-style">
              <select
                id="microSelect"
                className="selectpicker show-menu-arrow"
                name="microSelect"
                value={this.state.selectedMicrophoneId}
                onChange={this.changeMicrophone}>
                  {microphonesContent}
              </select>
            </div>
          </div>
          <div>
            <label htmlFor="speakerSelect">Speaker</label>
            <div className="select-style">
              <select
                id="speakerSelect"
                className="selectpicker show-menu-arrow"
                name="speakerSelect"
                value={this.state.selectedSpeakerId}
                onChange={this.changeSpeaker}>
                  {speakersContent}
              </select>
            </div>
          </div>
        </div>
      );
    }


    let leftBlock = ( //configuration layout
      <div className="block left">
        <div id="getConfiguration">
          <button className="btn btn-lg vidyo" onClick={this.getConfiguration}>Get Configuration</button>
          {dropdownBlock}
        </div>
      </div>
    );
    let rightBlock = ( //output window
      <div className="block right">
        <textarea className="full" value={this.state.text} readOnly>
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
