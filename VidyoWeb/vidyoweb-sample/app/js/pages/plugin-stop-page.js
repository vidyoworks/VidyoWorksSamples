window.PluginStop = React.createClass({

  getInitialState: function() { //here is where we declare the state variables we want to use
    return {
      stoppedPlugin: false,
      domRemoved: false,
      text: "",
    }
  },

  stopPlugin : function() { //this function will stop the plugin
      if (!proxyWrapper.isChrome) {
        vidyoClient.stop();
        this.stopped();
      } else {
        proxyWrapper.stop(function(response){
          console.log("response is:" + response.result + "...." + response.error);
          if(response.result == "ok"){
            this.stopped();
          }else{
            window.alert("Error trying to stop: " + response.error);
          }
        }.bind(this));
      }
  },

  stopped : function() {
    this.props.onPluginStoped();
    this.addText('Plugin Stopped');
    this.setState({
      stoppedPlugin: true,
    });
  },

  removeDom : function() { //this function will remove the DOM by reloading the page and deinit the plugin
    var holder = this.props.document.getElementById('pluginHolder');
    var pluginHTML = this.props.document.getElementById('plugin');
    if (!pluginHTML) {
      holder.removeChild(holder.childNodes[0]);
    }
    this.setState({
      domRemoved: true,
    });
    this.addText('Plugin removed from DOM');
  },

  addText : function (text) { //function to add text to the state
    console.log(text);
    this.setState({
      text: this.state.text + text + "\r\n"
    });
  },

  render: function(){ //this is the layout of the plugin stop page
    let pageContent = (
        <div id="pluginStop" className="center-aligned">
          <div>
            <button className="btn btn-lg vidyo" onClick={this.stopPlugin} disabled={this.state.stoppedPlugin}>Stop Plugin</button>
             <button className="btn btn-lg vidyo" onClick={this.removeDom} disabled={proxyWrapper.isChrome || this.state.domRemoved} >Remove from DOM</button>

               <div>
              </div>
          </div>
          <div className="block">
            <textarea value={this.state.text} readOnly>
            </textarea>
          </div>
        </div>
      );

    return (
      <div>
        {pageContent}
      </div>
    );
  },
});
