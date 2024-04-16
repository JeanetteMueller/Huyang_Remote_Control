const char indexHtml[] = R"====(


<div id="container">
  <div style="display: block;width:100%;text-align:center;">
  <a href="#" id="button_automatic" class="button" onClick="changeAutomatic(true);">Auto is UNKNOWN</a>
   | 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'open');">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'close');">CLOSE</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'blink');">BLINK</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'focus');">FOCUS</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'sad');">SAD</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'angry');">ANGRY</a>
   | 
  <a href="/settings.html" class="button">Settings</a>
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
  
  <div class="joystickContainer">
    <div id="joyDiv" class="joystick"></div>
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
  </div>

  <div id="container">
	<div class="slidecontainer">
        Sideways tilt
        <input id="slider_neckTiltSideways" type="range" min="-25" max="25" value="###neckTiltSideways###" class="slider" onChange="sendNeckUpdate()">
    </div>
  </div>

<script>
    window.onload = function () {
        console.log('Dokument geladen');
        systemInit();
    }
</script>

)====";
