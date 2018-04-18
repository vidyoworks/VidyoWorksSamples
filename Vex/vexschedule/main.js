function localJsonpCallback(json) {
    console.log(json);
}


String.prototype.format = function(placeholders) {
    var s = this;
    for(var propertyName in placeholders) {
        var re = new RegExp('{' + propertyName + '}', 'gm');
        s = s.replace(re, placeholders[propertyName]);
    }    
    return s;
};

function b64EncodeUnicode(str) {
    // first we use encodeURIComponent to get percent-encoded UTF-8,
    // then we convert the percent encodings into raw bytes which
    // can be fed into btoa.
    return btoa(encodeURIComponent(str).replace(/%([0-9A-F]{2})/g,
        function toSolidBytes(match, p1) {
            return String.fromCharCode('0x' + p1);
    }));
}

function StringToDictionary(input) {
    var inputArray = input.split('\n');
    var dictOutput = [];
    for (var i = 0; i < inputArray.length; ++i) 
    {
        var line = inputArray[i];
        if(line.length == 0)
            continue;
        var components = line.split(':');
        if(components.length < 2)
            continue;

        dictOutput[components[0].trim()] = components[1].trim();

      }
      console.log("....dinesh...typrof = ", (typeof dictOutput), "token = ", dictOutput["token"]);
      return dictOutput;
}


formScheduleString = function()
 {
    /*var scheduleToken = document.getElementById("scheduleToken").value;
    var tenantId = document.getElementById("tenantId").value;
    var serverURL = document.getElementById("serverURL").value;
    var agentId = document.getElementById("agentId").value;
    var cName = document.getElementById("cName").value;
    var apiKey = document.getElementById("apiKey").value;
    var appLocation = document.getElementById("appLocation").value;


    var total = "token={scheduleToken}&tenantId={tenantId}&serverURL={serverURL}&agentId={agentId}&cName={cName}&apiKey={apiKey}"
    .format({scheduleToken: scheduleToken, tenantId: tenantId, serverURL: serverURL, agentId: agentId, cName: cName, apiKey: apiKey});

    var encTotal = b64EncodeUnicode(total);
    encTotal += "=";

    var scheduleLink = appLocation + encTotal;*/



    /*var url = "https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64";

    $.ajax({
        url: "https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64",
        dataType: "jsonp",
        jsonp: false,
        jsonpCallback: "localJsonpCallback"
    });*/


    $.getJSON("https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64",
         	  {
         	  
         	  },
         	  function(data) {
                   console.log(data);
         	  
         	  });
}




myFunction = function()
 {
  

    $.getJSON("https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64",
         	  {
         	  
         	  },
         	  function(data, textStatus, xhr) {
                   console.log(data);
                   var webrtcURL = data.webrtcURL;
                   console.log("....dinesh.... = ", webrtcURL);

                   var headers = xhr.getAllResponseHeaders();
                   console.log("....dinesh...tpeof = ", (typeof headers), "headers = ", headers);
                   var dictHeader =  StringToDictionary(headers);
                   console.log("....dinesh...dict = ", dictHeader);
                   var test="token";
                   console.log("....dinesh...typrof = ", (typeof dictHeader), "token = ", dictHeader[test]);
                   for (var key in dictHeader) {
                    // check if the property/key is defined in the object itself, not in parent
                    if (dictHeader.hasOwnProperty(key)) {           
                        console.log("key=", key);
                        console.log("val=", dictHeader[key]);
                    }
                }

         	  });
}