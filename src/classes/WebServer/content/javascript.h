const char javascript[] = R"====(

var JoyNeck;
var JoyNeckX = 0;
var JoyNeckY = 0;

var JoyBody;
var JoyBodyX = 0;
var JoyBodyY = 0;

function sendEyeUpdate(position, action) {
    data = {
        face: {
            left: face_eyes_left,
            right: face_eyes_right
        }
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

var automatic = true;

var face_eyes_all = null;
var face_eyes_left = 'blink';
var face_eyes_right = 'blink';

var neck_rotate = 0;
var neck_tiltForward = 0;
var neck_tiltSideways = 0;

var body_rotate = 0;
var body_tiltForward = 0;
var body_tiltSideways = 0;

function sendData(data) {
    console.log(data);

    postData("/api/post.json", data).then(json => {
        console.log("Result from Server: ");
        console.log(json);

        automatic = json.automatic;

        if (json.face != null) {
            if (json.face.eyes.all != null) {
                face_eyes_all = json.face.eyes.all;
                face_eyes_left = json.face.eyes.all;
                face_eyes_right = json.face.eyes.all;
            }
            if (json.face.eyes.left != null) {
                face_eyes_left = json.face.eyes.left;
            }
            if (json.face.eyes.right != null) {
                face_eyes_right = json.face.eyes.right;
            }
        }

        if (json.neck != null) {
            neck_rotate = json.neck.rotate;
            neck_tiltForward = json.neck.tiltForward;
            neck_tiltSideways = json.neck.tiltSideways;
        }

        if (json.body != null) {
            body_rotate = json.body.rotate;
            body_tiltForward = json.body.tiltForward;
            body_tiltSideways = json.body.tiltSideways;
        }

        updateUserInterface();
    });
}

function updateUserInterface() {
    if (automatic == true)  {
        document.getElementById("button_automatic").innerHTML = "Auto is ON";
    }else{
        document.getElementById("button_automatic").innerHTML = "Auto is OFF";
    }

    console.log("face_eyes_all " + face_eyes_all);
    console.log("face_eyes_left " + face_eyes_left);
    console.log("face_eyes_right " + face_eyes_right);

    document.getElementById("eye_left_open").classList.remove("selected");
    document.getElementById("eye_left_close").classList.remove("selected");
    document.getElementById("eye_left_blink").classList.remove("selected");
    document.getElementById("eye_left_focus").classList.remove("selected");
    document.getElementById("eye_left_sad").classList.remove("selected");
    document.getElementById("eye_left_angry").classList.remove("selected");

    document.getElementById("eye_right_open").classList.remove("selected");
    document.getElementById("eye_right_close").classList.remove("selected");
    document.getElementById("eye_right_blink").classList.remove("selected");
    document.getElementById("eye_right_focus").classList.remove("selected");
    document.getElementById("eye_right_sad").classList.remove("selected");
    document.getElementById("eye_right_angry").classList.remove("selected");

    if (face_eyes_left == "open") {
        document.getElementById("eye_left_open").classList.add("selected");
    } else if (face_eyes_left == "close") {
        document.getElementById("eye_left_close").classList.add("selected");
    } else if (face_eyes_left == "blink") {
        document.getElementById("eye_left_blink").classList.add("selected");
    } else if (face_eyes_left == "focus") {
        document.getElementById("eye_left_focus").classList.add("selected");
    } else if (face_eyes_left == "sad") {
        document.getElementById("eye_left_sad").classList.add("selected");
    } else if (face_eyes_left == "angry") {
        document.getElementById("eye_left_angry").classList.add("selected");
    }

    if (face_eyes_right == "open") {
        document.getElementById("eye_right_open").classList.add("selected");
    } else if (face_eyes_right == "close") {
        document.getElementById("eye_right_close").classList.add("selected");
    } else if (face_eyes_right == "blink") {
        document.getElementById("eye_right_blink").classList.add("selected");
    } else if (face_eyes_right == "focus") {
        document.getElementById("eye_right_focus").classList.add("selected");
    } else if (face_eyes_right == "sad") {
        document.getElementById("eye_right_sad").classList.add("selected");
    } else if (face_eyes_right == "angry") {
        document.getElementById("eye_right_angry").classList.add("selected");
    }



    console.log("neck_rotate " + neck_rotate);
    console.log("neck_tiltForward " + neck_tiltForward);
    console.log("neck_tiltSideways " + neck_tiltSideways);

    document.getElementById("slider_neckTiltSideways").value = neck_tiltSideways;

    console.log("body_rotate " + body_rotate);
    console.log("body_tiltForward " + body_tiltForward);
    console.log("body_tiltSideways " + body_tiltSideways);

    document.getElementById("slider_bodyTiltSideways").value = body_tiltSideways;
}

function getServerData() {
    const data = {
        face: {},
        neck: {},
        body: {}
    };
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

        if (JoyNeckX != stickData.x || JoyNeckY != stickData.y) {
            console.log("joystick JoyNeck action");

            JoyNeckX = stickData.x;
            JoyNeckY = stickData.y;

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

        if (JoyBodyX != stickData.x || JoyBodyY != stickData.y) {
            console.log("joystick JoyBody action");

            JoyBodyX = stickData.x;
            JoyBodyY = stickData.y;

            sendBodyUpdate();
        }
    });
}

)====";
