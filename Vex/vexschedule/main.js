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
      //console.log("....dinesh...typeof = ", (typeof dictOutput), "token = ", dictOutput["token"]);
      return dictOutput;
}


formScheduleStringWithParas = function(scheduleToken, tenantId, serverURL, agentId,  cName, apiKey, appLocation)
 {

    var total = "token={scheduleToken}&tenantId={tenantId}&serverURL={serverURL}&agentId={agentId}&cName={cName}&apiKey={apiKey}"
    .format({scheduleToken: scheduleToken, tenantId: tenantId, serverURL: serverURL, agentId: agentId, cName: cName, apiKey: apiKey});

    var encTotal = b64EncodeUnicode(total);
    encTotal += "=";

    var scheduleLink = appLocation + encTotal;

    console.log("...dinesh...., link = ", scheduleLink);
    var message = "Complete link : " +  scheduleLink;
   
    var result = message.link(scheduleLink);
    document.getElementById("completeLink").innerHTML = result;
}




formScheduleString = function()
 {
  

    $.getJSON("https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64",
         	  {
         	  
         	  },
         	  function(data, textStatus, xhr) {
                   console.log(data);
                   //var webrtcURL = data.webrtcURL;

                   var headers = xhr.getAllResponseHeaders();
                   var dictHeader =  StringToDictionary(headers);
                   //console.log("....dinesh...typrof = ", (typeof dictHeader), "token = ", dictHeader[test]);
                   for (var key in dictHeader) {
                    // check if the property/key is defined in the object itself, not in parent
                    if (dictHeader.hasOwnProperty(key)) {           
                        console.log("key=", key);
                        console.log("val=", dictHeader[key]);
                    }
                }
                var token = dictHeader["token"];
                getSchedule(token);

         	  });
}




getSchedule = function(token)
 {
  
    var scheduleToken = document.getElementById("scheduleToken").value;
    var url = "https://vex.vidyoclouddev.com/v2/schedule?tenant=64&scheduleToken={scheduleToken}"
    .format({scheduleToken: scheduleToken});

    $.ajaxSetup({
        headers : {
          'Authorization' : token
        }
      });

    $.getJSON(url,
         	  {
         	  
         	  },
         	  function(data, textStatus, xhr) {
                console.log(data);
                var scheduleTokenInResponse = data.scheduleToken;
                var tenantId = document.getElementById("tenantId").value;
                var serverURL = document.getElementById("serverURL").value;
                var agentId = data.agentId;
                var cName = document.getElementById("cName").value;
                var apiKey = document.getElementById("apiKey").value;
                var appLocation = document.getElementById("appLocation").value;

                formScheduleStringWithParas(scheduleToken, tenantId, serverURL, agentId,  cName, apiKey, appLocation);

         	  });
}


