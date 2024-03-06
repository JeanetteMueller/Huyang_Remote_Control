const String form = R"====(
<form method="POST" action="" name="HuyangNeckForm" id="PostID">
<div class="slidecontainer">
<input name="neckrotate" type="range" min="-50" max="50" value="###neckrotate###" class="slider" id="myRange" onchange="HuyangNeckForm.submit()">
</div>
</form>
)===="; 