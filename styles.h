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

)====";
