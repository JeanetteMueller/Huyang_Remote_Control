const char styles[] = R"====(

body { 
	font-family: 'Helvetica', 'Arial', sans-serif; 
	font-size: 16pt; 
	background-color: #000; 
	color: #fff;
}

#container { 
	display: flex;
	flex-wrap: wrap;
	justify-content: center;
}

a:link, a:visited, a:active { 
	color: #fff; text-decoration: none; }

.button { 
	background-color: #333; 
	display: inline-block; 
	padding: 5px; 
	margin: 5px; 
	color: #fff; 
	text-decoration: none; 
	border-radius: 5px;
}

h5 { 
	font-family: 'Helvetica', 'Arial', sans-serif; 
	font-size: 22pt; 
	display: flex; 
	align-items: center; 
	justify-content: center; 
	width:100%;
	text-align:center; 
	color: #000;
}

.menuContainer {
  style="display: block;
  width:100%;
  text-align:center;
}

.eyeContainer {
  width:50%;
  text-align:center;
  float:left;
}

.eye {
  display: block;
  margin:auto;
  width:100px;height: 100px;
  text-align:center;
  border-radius: 50px;
  background-color: #fd2;
}


//Slider

.slidecontainer {
  width: 100%;
  text-align:center;
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
  min-width:30%;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  align-items: center;
}
.joystick {
  display: inline-block;
  width:250px;
  height:250px;
  margin:0px;
  cursor: pointer; /* Cursor on hover */
}

.hidden {
  display: none;
}

)====";
