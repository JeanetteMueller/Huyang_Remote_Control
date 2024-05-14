const char styles[] = R"====(

body { 
	font-family: 'Helvetica', 'Arial', sans-serif; 
	font-size: 30pt; 
	background-color: #000; 
	color: #fff;
  text-align:center;
}

#container { 
	display: flex;
	flex-wrap: wrap;
	justify-content: center;
}

a:link, a:visited, a:active { 
	color: #fff; 
  text-decoration: none;
}

.button { 
	background-color: #333; 
	display: inline-block; 
	padding: 10px; 
	margin: 10px; 
	color: #fff; 
	text-decoration: none; 
	border-radius: 5px;
}
.clear {
	clear: both;
}
h4 {
  margin: 0;
} 

.menuContainer {
  width: 100%;
  margin: 0 auto;
  float: left;
  display: block;
}

.eyeContainer {
  width:50%;
  text-align:center;
  float:left;
}

.eye {
  display: block;
  margin:auto;
  width:200px; height: 200px;
  text-align:center;
  border-radius: 100px;
  background-color: #fd2;
}

.eye > h5 {
  font-family: 'Helvetica', 'Arial', sans-serif; 
	font-size: 40pt; 
	display: flex; 
	align-items: center; 
	justify-content: center; 
	width: 100%;
	text-align:center; 
  margin: 0;
  padding: 70px 0 0 0;
  color: black;
}

.slidecontainer {
  width: 100%;
  text-align:center;
  font-size: 12pt; 
}

.selected {
  background-color: #f00 !important;
}

/* The slider itself */
.slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 50px; /* Specified height */
  background: #333; /* Grey background */
  outline: none; /* Remove outline */
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
  text-align: center;
  border-radius: 25px; 
}

/* Mouse-over effects */
.slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

/* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */ 
.slider::-webkit-slider-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 50px; /* Set a specific slider handle width */
  height: 50px; /* Slider handle height */
  background: #fd2; /* Marker background */
  cursor: pointer; /* Cursor on hover */
  border-radius: 25px; 
}

.slider::-moz-range-thumb {
  width: 50px; /* Set a specific slider handle width */
  height: 50px; /* Slider handle height */
  background: #fd2; /* Marker background */
  cursor: pointer; /* Cursor on hover */
  border-radius: 20px;
}

.joystickContainer {
  justify-content: center;
  align-items: center;
}
.joystick {
  display: inline-block;
  width:400px;
  height:400px;
  margin:0px;
  padding: 0;
  cursor: pointer; /* Cursor on hover */
}

.hidden {
  display: none;
}

/* Buttons */
.eye_buttons {
	margin: 0 auto;
	width: 420px;
}
.menu_eye_buttons {
	margin: 0 auto;
	width: 504px;
}
.eye_button_headline {
    float:left;
    display: block;
}
.eye_button {
  width: 60px;
  height: 60px;
  border-radius: 60px;
  border: 2px solid #fd2;
  float:left;
  display: block;
  padding: 0px;
  margin: 10px;
}
.eye_open {
  background-color: #fd2;
  font-size: 15px;
  line-height: 58px;
  color: #000;
}
.eye_close {
  background-color: #000;
}

.eye_focus {
  background-color: #000;
}
.eye_focus > div {
  width: 100%;
  height: 20px;
  position: relative;
  top: 20px;
  background-color: #fd2;
}

.eye_sad {
	background-color: #fd2;
}
.eye_sad > div {
  width: 100%;
  height: 20px;
  position: relative;
  top: 0px;
  background-color: #000;
  
}

.eye_angry {
	background-color: #fd2;
}
.eye_angry > div {
  width: 100%;
  height: 20px;
  position: relative;
  top: 0px;
  background-color: #000;
}

.left {
	transform: rotate(30deg);
}
.right {
	transform: rotate(-30deg);
}

)====";
