const char indexHtml_body[] = R"====(

<h4>Body</h4>

<div class="joystickContainer">
    <div id="joyBody" class="joystick"></div>
</div>
<div class="slidecontainer">
  Sideways tilt
  <input id="slider_bodyTiltSideways" type="range" min="-100" max="100" value="0" class="slider" onInput="sendBodyUpdate()">
</div>

)====";