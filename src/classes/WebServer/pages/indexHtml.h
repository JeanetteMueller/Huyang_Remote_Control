const char indexHtml[] = R"====(

<div class="menuContainer">
  <a href="#" id="button_automatic" class="button" onClick="changeAutomatic(true);">Auto is UNKNOWN</a>
   | 
  <a href="/settings.html" class="button">Settings</a>
</div>

<h3>Face</h3>
<hr>
<div class="menuContainer">
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'open');">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'close');">CLOSE</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'blink');">BLINK</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'focus');">FOCUS</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'sad');">SAD</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'angry');">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('left', 'blink');">
    <h5 style="padding: 34px 0 0 0;">BLINK</h5>
  </div>
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'close');">CLOSE</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'open');">OPEN</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'focus');">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'sad');">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'angry');">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('right', 'blink');">
    <h5 style="padding: 34px 0 0 0;">BLINK</h5>
  </div>
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'close');">CLOSE</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'open');">OPEN</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'focus');">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'sad');">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'angry');">ANGRY</a>

</div>

<hr>
<h3>Neck</h3>

<div class="joystickContainer">
    <div id="joyNeck" class="joystick"></div>
</div>
<div class="slidecontainer">
  Sideways tilt
  <input id="slider_neckTiltSideways" type="range" min="-25" max="25" value="0" class="slider" onInput="sendNeckUpdate()">
</div>

<hr>
<h3>Body</h3>

<div class="joystickContainer">
    <div id="joyBody" class="joystick"></div>
</div>
<div class="slidecontainer">
  Sideways tilt
  <input id="slider_bodyTiltSideways" type="range" min="-25" max="25" value="0" class="slider" onInput="sendBodyUpdate()">
</div>

<script>
    window.onload = function () {
        console.log('Dokument geladen');
        systemInit();
    }
</script>

<hr>
Made with Love by Jeanette M&uuml;ller

)====";
