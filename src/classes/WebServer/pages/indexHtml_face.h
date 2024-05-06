const char indexHtml_face[] = R"====(

<h4>Face</h4>

<div class="menuContainer">
	<div class="menu_eye_buttons">
  <div class="eye_button eye_open" onClick="sendEyeUpdate('all', 1);" id="eye_all_open"></div> 
  <div class="eye_button eye_close" onClick="sendEyeUpdate('all', 2);" id="eye_all_close"></div> 
  <div class="eye_button eye_open" onClick="sendEyeUpdate('all', 3);" id="eye_all_blink">BLINK</div>
  <div class="eye_button eye_focus" onClick="sendEyeUpdate('all', 4);" id="eye_all_focus"><div></div></div> 
  <div class="eye_button eye_sad right" onClick="sendEyeUpdate('all', 5);" id="eye_all_sad"><div></div></div> 
  <div class="eye_button eye_angry left" onClick="sendEyeUpdate('all', 6);" id="eye_all_angry"><div></div></div> 
</div>
</div>
<div class="clear"></div>
<div class="eyeContainer">
	<h4>Left Eye</h4>
  <div class="eye" onClick="sendEyeUpdate('left', 3);" id="eye_left_blink">
    <h5>BLINK</h5>
  </div>
  <div class="eye_buttons">
  <div class="eye_button eye_open" onClick="sendEyeUpdate('left', 1);" id="eye_left_open"></div> 
  <div class="eye_button eye_close" onClick="sendEyeUpdate('left', 2);" id="eye_left_close"></div> 
  <div class="eye_button eye_focus" onClick="sendEyeUpdate('left', 4);" id="eye_left_focus"><div></div></div> 
  <div class="eye_button eye_sad right" onClick="sendEyeUpdate('left', 5);" id="eye_left_sad"><div></div></div> 
  <div class="eye_button eye_angry left" onClick="sendEyeUpdate('left', 6);" id="eye_left_angry"><div></div></div>
  </div>
</div>
<div class="eyeContainer">
	<h4>Right Eye</h4>
  <div class="eye" onClick="sendEyeUpdate('right', 3);" id="eye_right_blink">
    <h5>BLINK</h5>
  </div>
  <div class="eye_buttons">
  <div class="eye_button eye_open" onClick="sendEyeUpdate('right', 1);" id="eye_right_open"></div> 
  <div class="eye_button eye_close" onClick="sendEyeUpdate('right', 2);" id="eye_right_close"></div> 
  <div class="eye_button eye_focus" onClick="sendEyeUpdate('right', 4);" id="eye_right_focus"><div></div></div>
  <div class="eye_button eye_sad left" onClick="sendEyeUpdate('right', 5);" id="eye_right_sad"><div></div></div>
  <div class="eye_button eye_angry right" onClick="sendEyeUpdate('right', 6);" id="eye_right_angry"><div></div></div>
  </div>
</div>

)====";