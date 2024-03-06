const String form = R"====(
<form method="POST" action="" name="HuyangNeckForm" id="PostID">
<div class="slidecontainer">
Rotate
<input name="neckRotate" type="range" min="-45" max="45" value="###neckRotate###" class="slider" onchange="HuyangNeckForm.submit()">
Pitch
<input name="neckTiltForward" type="range" min="0" max="100" value="###neckTiltForward###" class="slider" onchange="HuyangNeckForm.submit()">
Sideways tilt
<input name="neckTiltSideways" type="range" min="-20" max="20" value="###neckTiltSideways###" class="slider" onchange="HuyangNeckForm.submit()">
</div>
</form>
)===="; 