const char indexHtml_face[] = R"====(

<h4>Face</h4>

<div class="menuContainer">
  Both: 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 1);" id="eye_all_open">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('all', 2);" id="eye_all_close">CLOSE</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 3);" id="eye_all_blink">BLINK</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 4);" id="eye_all_focus">FOCUS</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 5);" id="eye_all_sad">SAD</a>
  <a href="#" class="button" onClick="sendEyeUpdate('all', 6);" id="eye_all_angry">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('left', 3);" id="eye_left_blink">
    <h5>BLINK</h5>
  </div>
  <a href="#" class="button" onClick="sendEyeUpdate('left', 1);" id="eye_left_open">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 2);" id="eye_left_close">CLOSE</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('left', 4);" id="eye_left_focus">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 5);" id="eye_left_sad">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('left', 6);" id="eye_left_angry">ANGRY</a>
</div>
<div class="eyeContainer">
  <div class="eye" onClick="sendEyeUpdate('right', 3);" id="eye_right_blink">
    <h5>BLINK</h5>
  </div>

  <a href="#" class="button" onClick="sendEyeUpdate('right', 1);" id="eye_right_open">OPEN</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 2);" id="eye_right_close">CLOSE</a> 
  <br />
  <a href="#" class="button" onClick="sendEyeUpdate('right', 4);" id="eye_right_focus">FOCUS</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 5);" id="eye_right_sad">SAD</a> 
  <a href="#" class="button" onClick="sendEyeUpdate('right', 6);" id="eye_right_angry">ANGRY</a>
</div>

)====";