const char javascript[] = R"====(

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

var JoyNeck;
var JoyNeckX = 0;
var JoyNeckY = 0;

var JoyBody;
var JoyBodyX = 0;
var JoyBodyY = 0;

function sendEyeUpdate(position, action) {
    data = {
        automatic: false,
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
        automatic: false,
        neck: {
            rotate: JoyNeck.GetX(),
            tiltForward: JoyNeck.GetY(),
            tiltSideways: document.getElementById("slider_neckTiltSideways").value
        }
    };

    sendData(data);
}

function sendBodyUpdate() {
    const data = {
        automatic: false,
        body: {
            rotate: JoyBody.GetX(),
            tiltForward: JoyBody.GetY(),
            tiltSideways: document.getElementById("slider_bodyTiltSideways").value
        }
    };

    sendData(data);
}

async function postData(url = "", data = {}) {
    const response = await fetch(url, {
        method: "POST",
        mode: "no-cors", // no-cors, *cors, same-origin
        cache: "no-cache",
        headers: {
            "Content-Type": "application/json"
        },
        referrerPolicy: "no-referrer",
        body: JSON.stringify(data), 
    });

    return response.json();
}

function sendData(data) {
    console.log(data);

    postData("/api/post.json", data).then(json => {
        console.log("Result from Server: ");
        console.log(json);

        automatic = json.automatic;

        if (json.face != null) {
            face_eyes_all = json.face.eyes.all;
            face_eyes_left = json.face.eyes.left;
            face_eyes_right = json.face.eyes.right;
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
    if (automatic == true) {
        document.getElementById("button_automatic").innerHTML = "Auto is ON";
    } else {
        document.getElementById("button_automatic").innerHTML = "Auto is OFF";
    }

    document.getElementById("eye_all_open").classList.remove("selected");
    document.getElementById("eye_all_close").classList.remove("selected");
    document.getElementById("eye_all_blink").classList.remove("selected");
    document.getElementById("eye_all_focus").classList.remove("selected");
    document.getElementById("eye_all_sad").classList.remove("selected");
    document.getElementById("eye_all_angry").classList.remove("selected");

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

    if (face_eyes_all == 1) {
        document.getElementById("eye_all_open").classList.add("selected");
    } else if (face_eyes_all == 2) {
        document.getElementById("eye_all_close").classList.add("selected");
    } else if (face_eyes_all == 3) {
        document.getElementById("eye_all_blink").classList.add("selected");
    } else if (face_eyes_all == 4) {
        document.getElementById("eye_all_focus").classList.add("selected");
    } else if (face_eyes_all == 5) {
        document.getElementById("eye_all_sad").classList.add("selected");
    } else if (face_eyes_all == 6) {
        document.getElementById("eye_all_angry").classList.add("selected");
    }

    if (face_eyes_left == 1) {
        document.getElementById("eye_left_open").classList.add("selected");
    } else if (face_eyes_left == 2) {
        document.getElementById("eye_left_close").classList.add("selected");
    } else if (face_eyes_left == 3) {
        document.getElementById("eye_left_blink").classList.add("selected");
    } else if (face_eyes_left == 4) {
        document.getElementById("eye_left_focus").classList.add("selected");
    } else if (face_eyes_left == 5) {
        document.getElementById("eye_left_sad").classList.add("selected");
    } else if (face_eyes_left == 6) {
        document.getElementById("eye_left_angry").classList.add("selected");
    }

    if (face_eyes_right == 1) {
        document.getElementById("eye_right_open").classList.add("selected");
    } else if (face_eyes_right == 2) {
        document.getElementById("eye_right_close").classList.add("selected");
    } else if (face_eyes_right == 3) {
        document.getElementById("eye_right_blink").classList.add("selected");
    } else if (face_eyes_right == 4) {
        document.getElementById("eye_right_focus").classList.add("selected");
    } else if (face_eyes_right == 5) {
        document.getElementById("eye_right_sad").classList.add("selected");
    } else if (face_eyes_right == 6) {
        document.getElementById("eye_right_angry").classList.add("selected");
    }

    document.getElementById("slider_neckTiltSideways").value = neck_tiltSideways;
    document.getElementById("slider_bodyTiltSideways").value = body_tiltSideways;
}

function getServerData() {
    const data = {};

    sendData(data);
}

function systemInit() {
    console.log("systemInit started");

    getServerData();

    setInterval(getServerData, 2000);

    JoyNeck = new JoyStick('joyNeck', {
        "autoReturnToCenter": true,
        "internalFillColor": "#fd2",
        "internalLineWidth": 2,
        "internalStrokeColor": "#b90",
        "externalLineWidth": 2,
        "externalStrokeColor": "#b90"
    }, function (stickData) {

        if (JoyNeckX != stickData.x || JoyNeckY != stickData.y) {
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
    }, function (stickData) {

        if (JoyBodyX != stickData.x || JoyBodyY != stickData.y) {
            
            JoyBodyX = stickData.x;
            JoyBodyY = stickData.y;

            sendBodyUpdate();
        }
    });
}

)====";
