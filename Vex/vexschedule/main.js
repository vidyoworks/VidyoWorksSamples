


String.prototype.format = function (placeholders) {
    var s = this;
    for (var propertyName in placeholders) {
        var re = new RegExp('{' + propertyName + '}', 'gm');
        s = s.replace(re, placeholders[propertyName]);
    }
    return s;
};

function b64EncodeUnicode(str) {
    try {
        // first we use encodeURIComponent to get percent-encoded UTF-8,
        // then we convert the percent encodings into raw bytes which
        // can be fed into btoa.
        return btoa(encodeURIComponent(str).replace(/%([0-9A-F]{2})/g,
            function toSolidBytes(match, p1) {
                return String.fromCharCode('0x' + p1);
            }));
    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }
    return "";
}

function StringToDictionary(input) {
    try {

        var inputArray = input.split('\n');
        var dictOutput = [];
        for (var i = 0; i < inputArray.length; ++i) {
            var line = inputArray[i];
            if (line.length == 0)
                continue;
            var components = line.split(':');
            if (components.length < 2)
                continue;

            dictOutput[components[0].trim()] = components[1].trim();

        }
        return dictOutput;
    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }
    return null;
}

function XmlKeyValue(input, key) {
    try {
        if (window.DOMParser) {
            parser = new DOMParser();
            xmlDoc = parser.parseFromString(input, "application/xml");
        }
        else // Internet Explorer
        {
            xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
            xmlDoc.async = false;
            xmlDoc.loadXML(input);
        }

        return xmlDoc.getElementsByTagName(key)[0].childNodes[0].nodeValue;
    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }
    return "";
}


formScheduleStringWithParas = function (scheduleToken, tenantId, serverURL, agentId, skill, cName, apiKey, appLocation) {

    try {
        var total = "";
        if(agentId)
            total = "token={scheduleToken}&tenantId={tenantId}&serverURL={serverURL}&agentId={agentId}&cName={cName}&apiKey={apiKey}"
            .format({ scheduleToken: scheduleToken, tenantId: tenantId, serverURL: serverURL, agentId: agentId, cName: cName, apiKey: apiKey });
        else
            total = "token={scheduleToken}&tenantId={tenantId}&serverURL={serverURL}&skill={skill}&cName={cName}&apiKey={apiKey}"
            .format({ scheduleToken: scheduleToken, tenantId: tenantId, serverURL: serverURL, skill: skill, cName: cName, apiKey: apiKey });

        var encTotal = b64EncodeUnicode(total);
        //encTotal += "=";

        var scheduleLink = appLocation + encTotal;
        var message = "Complete link : " + scheduleLink;

        var result = message.link(scheduleLink);
        document.getElementById("completeLink").innerHTML = result;
    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }
}


getSchedule = function (token) {
    try {

        var scheduleToken = document.getElementById("scheduleToken").value;
        var url = "{defServerURL}/v2/schedule?tenant={defTenantId}&scheduleToken={scheduleToken}"
            .format({ defServerURL:defServerURL, defTenantId:defTenantId, scheduleToken: scheduleToken });

        $.ajaxSetup({
            headers: {
                'Authorization': token
            }
        });

        $.getJSON(url,
            {

            },
            function (data, textStatus, xhr) {
                console.log(data);
                var scheduleTokenInResponse = data.scheduleToken;
                var tenantId = document.getElementById("tenantId").value;
                var serverURL = document.getElementById("serverURL").value;
                
                var agentId =null;
                var skill = null;
                if(data.agentId)
                    agentId = data.agentId;
                else
                    skill = data.skillCategory[0].skill;
                var cName = XmlKeyValue(data.xmlBlob, "customerName");
                var apiKey = document.getElementById("apiKey").value;
                var appLocation = document.getElementById("appLocation").value;

                formScheduleStringWithParas(scheduleToken, tenantId, serverURL, agentId, skill, cName, apiKey, appLocation);

            });

    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }
}

formScheduleString = function () {
    var scheduleToken = document.getElementById("scheduleToken").value;
    if(scheduleToken.length == 0)
    {
        window.alert("Schedule token is empty. Please fill it before starting");
        return;
    }
    try {

        var url = "{defServerURL}/v2/customerProfile?tenant={defTenantId}"
            .format({ defServerURL:defServerURL, defTenantId:defTenantId });

        $.getJSON(url,
            {

            },
            function (data, textStatus, xhr) {
                console.log(data);
                //var webrtcURL = data.webrtcURL;

                var headers = xhr.getAllResponseHeaders();
                var dictHeader = StringToDictionary(headers);
                if(dictHeader)
                {
                    var token = dictHeader["token"];
                    getSchedule(token);
                }
            });

    }
    catch (error) {
        var errorWithFunc = arguments.callee.toString() + " : " + error;
        console.error(error);
        document.getElementById("completeLink").innerHTML = errorWithFunc;
    }

}



var bodyLoaded = function () 
{
    document.getElementById("tenantId").value = defTenantId;
    document.getElementById("serverURL").value = defServerURL;
    document.getElementById("apiKey").value = defApiKey;
    document.getElementById("appLocation").value = defAppLocation;
}






