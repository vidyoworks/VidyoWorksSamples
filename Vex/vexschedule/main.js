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


formScheduleString = function()
 {
    var scheduleToken = document.getElementById("scheduleToken").value;
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

    var scheduleLink = appLocation + encTotal;



    /*var url = "https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64";

    $.ajax({
        url: "https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64",
        //dataType: "jsonp",
        jsonp: false,
        jsonpCallback: "localJsonpCallback"
    });*/
}