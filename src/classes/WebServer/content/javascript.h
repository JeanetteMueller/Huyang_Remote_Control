const char javascript[] = R"====(

var JoyNeck;
var JoyNeckX = 0;
var JoyNeckY = 0;

var JoyBody;
var JoyBodyX = 0;
var JoyBodyY = 0;

function sendEyeUpdate(position, action) {
    console.log(position);
    console.log(" eye do action: ");
    console.log(action);

    data = {
        face: {}
    };

    data["face"][position] = action;

    sendData(data);
}

function changeAutomatic(newState) {
    const data = { 
        automatic: newState
    };

    sendData(data);
}

function sendNeckUpdate() {

    const data = {
        neck: {
            rotate: JoyNeck.GetX(),
            tiltForward: JoyNeck.GetY(),
            tiltSideways: document.getElementById("slider_neckTiltSideways").value
        }
    };
    sendData(data);
}

function sendBodyUpdate(){
    const data = {
        body: {
            rotate: JoyBody.GetX(),
            tiltForward: JoyBody.GetY(),
            tiltSideways: document.getElementById("slider_bodyTiltSideways").value
        }
    };
    sendData(data);
}

async function postData(url = "", data = {}) {
  // Default options are marked with *
  const response = await fetch(url, {
    method: "POST",
    mode: "no-cors", // no-cors, *cors, same-origin
    cache: "no-cache",
    headers: {
      "Content-Type": "application/json"
    },
    referrerPolicy: "no-referrer", // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
    body: JSON.stringify(data), // body data type must match "Content-Type" header
  });
  return response.json();
}
function sendData(data) {
    console.log(data);

    postData("/api/post.json", data).then(json => {
        console.log("Result from Server: ");
        console.log(json);

        if (json.automatic == true)  {
            document.getElementById("button_automatic").innerHTML = "Auto is ON";
        }else{
            document.getElementById("button_automatic").innerHTML = "Auto is OFF";
        }
    });
}

function getServerData() {
    const data = {};
    sendData(data);
}

function systemInit() {
    console.log("systemInit started");

    getServerData();

    JoyNeck = new JoyStick('joyNeck', {
        "autoReturnToCenter": true,
        "internalFillColor": "#fd2",
        "internalLineWidth": 2,
        "internalStrokeColor": "#b90",
        "externalLineWidth": 2,
        "externalStrokeColor": "#b90"
    }, function(stickData) {

        if (JoyNeckX != JoyNeck.GetX() || JoyNeckY != JoyNeck.GetY()) {
            console.log("joystick JoyNeck action");

            JoyNeckX = JoyNeck.GetX();
            JoyNeckY = JoyNeck.GetY();

            sendNeckUpdate();
        }
        
    });

    JoyBody = new JoyStick('joyBody', {
        "autoReturnToCenter": true,
        "internalFillColor": "#fd2",
        "internalLineWidth": 2,
        "internalStrokeColor": "#b90",
        "externalLineWidth": 2,
        "externalStrokeColor": "#b90"
    }, function(stickData) {

        if (JoyBodyX != JoyBody.GetX() || JoyBodyY != JoyBody.GetY()) {
            console.log("joystick action");

            JoyBodyX = JoyBody.GetX();
            JoyBodyY = JoyBody.GetY();

            sendBodyUpdate();
        }
        
    });
}

)====";
