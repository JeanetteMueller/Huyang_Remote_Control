#include "indexHtml_face.h"
#include "indexHtml_neck.h"
#include "indexHtml_body.h"


const char indexHtml[] = R"====(

<div class="menuContainer">
  <a href="#" id="button_automatic" class="button" onClick="changeAutomatic(true);">LOADING</a>
   | 
  <a href="/settings.html" class="button">Settings</a>
</div>

<hr>

###FACE###

<hr>

###NECK###

<hr>

###BODY###


<script language="javascript">
  window.onload = function(){

    loadJoystick();
  }

  function loadJoystick() {
    var newScript = document.createElement("script");
    newScript.src = "joystick.js";
    document.body.appendChild(newScript);

    console.log('joystick loaded');

    setTimeout(() => { loadJavascript(); }, 1000);
    
  }

  function loadJavascript() {
    var newScript = document.createElement("script");
    newScript.src = "javascript.js?random=###RANDOM###";
    document.body.appendChild(newScript);
    console.log('javascript loaded');

    setTimeout(() => { systemInit(); }, 500);
  }
        
</script>

<hr>
Made with &#9829; by Jeanette M&uuml;ller

)====";
