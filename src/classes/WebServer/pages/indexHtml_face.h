const char indexHtml_face[] = R"====(

<h4>Face</h4>

<div class="menuContainer">
  Both: 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'open');" id="eye_all_open">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'close');" id="eye_all_close">CLOSE</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'blink');" id="eye_all_blink">BLINK</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'focus');" id="eye_all_focus">FOCUS</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'sad');" id="eye_all_sad">SAD</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 'angry');" id="eye_all_angry">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('left', 'blink');" id="eye_left_blink">
    <h5>BLINK</h5>
  </div>
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'close');" id="eye_left_close">CLOSE</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'open');" id="eye_left_open">OPEN</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'focus');" id="eye_left_focus">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'sad');" id="eye_left_sad">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 'angry');" id="eye_left_angry">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('right', 'blink');" id="eye_right_blink">
    <h5>BLINK</h5>
  </div>
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'close');" id="eye_right_close">CLOSE</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'open');" id="eye_right_open">OPEN</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'focus');" id="eye_right_focus">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'sad');" id="eye_right_sad">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 'angry');" id="eye_right_angry">ANGRY</a>
</div>

)====";