const char indexHtml_neck[] = R"====(

<h4>Neck</h4>

<div class="joystickContainer">
    <div id="joyNeck" class="joystick"></div>
</div>
<div class="slidecontainer">
  Sideways tilt
  <input id="slider_neckTiltSideways" type="range" min="-100" max="100" value="0" class="slider" onInput="sendNeckUpdate()">
</div>

)====";