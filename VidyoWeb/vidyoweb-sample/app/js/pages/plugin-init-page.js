window.PluginInitialisationPage = React.createClass({

  getInitialState: function() { //initial states for this page
    return {
      text: "",
      useCallbackForOutEvents: true,
    }
  },

  startVidyoClient : function() { //pressing on the detect button will start this function
    if (proxyWrapper.isChrome) { //checks to see if is chrome, if chrome will start vidyoforWeb, if not the npapi plugin
        vidyoClient.setProxy(proxyWrapper);
        this.startVidyoClientForWeb();
    } else {
        this.startPlugin();
    }
  },

  startVidyoClientForWeb : function() { //will init vidyoForWeb
    proxyWrapper.start(function (startRes) {
        if(!startRes.error) {
            this.addText('VidyoClient started');
            this.props.onPluginInitialised(); //will go to the react-app page to continue init
        }
    }.bind(this));
  },

  startPlugin : function ()   { //will init npapi plugin
      if(this.props.addedToDom){ //checks to see if the view is added to the DOM
          var pluginHTML = this.props.document.getElementById('plugin');
          var config = { //sets the configuration
              plugin: pluginHTML,
              outEventCallbackObject: this.props.callbackWindow,
              defaultOutEventCallbackMethod: "onOutEvent",
              useCallbackWithPlugin: this.state.useCallbackForOutEvents
          };
          this.addText("config outEventCallbackObject: " + config.outEventCallbackObject);
          if (vidyoClient.start(config)) {
              this.addText("VidyoWeb started successfully"); //started succesfully
          } else {
              this.addText("VidyoWeb did not start successfully!");
          }
      }else{
          this.addText("VidyoWeb did not start successfully!");
      }
  },

  addText : function (text) { //function to add text to the output
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  render: function(){ //this is the layout of the join as guest page

    return (
      <div className="center-aligned">
        <div id="pluginDetectionPage">
            <button className="btn btn-lg vidyo" onClick={this.startVidyoClient} disabled={this.props.callbackWindow.state.pluginInitialised}>Initialize</button>
        </div>
        <div className="block">
          <textarea value={this.state.text} readOnly>
          </textarea>
        </div>
      </div>
    );
  },
});
