const String styles = R"====(

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

.eyeContainer {
  margin:auto;
  min-width:48%;
  text-align:center;
  background-color: #333;
  border-radius: 10px;
  border: 5px solid #000;
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
  width: 100%; /* Width of the outside container */
}

/* The slider itself */
.slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 25px; /* Specified height */
  background: #d3d3d3; /* Grey background */
  outline: none; /* Remove outline */
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
}

/* Mouse-over effects */
.slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

/* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */ 
.slider::-webkit-slider-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: #04AA6D; /* Green background */
  cursor: pointer; /* Cursor on hover */
}

.slider::-moz-range-thumb {
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: #04AA6D; /* Green background */
  cursor: pointer; /* Cursor on hover */
}

)====";
