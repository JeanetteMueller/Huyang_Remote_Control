#include "indexHtml_face.h"
#include "indexHtml_neck.h"
#include "indexHtml_body.h"

const char indexHtml[] = R"=====(

<div class="menuContainer">
  <a href="#" id="button_automatic" class="button" onClick="changeAutomatic(true);">LOADING</a>
   | 
  <a href="/index.html" class="button">Start</a>
  <a href="/settings.html" class="button">Settings</a>
</div>

###FACE###
###NECK###
###BODY###

<script language="javascript">
  window.onload = function(){
    loadJoystick();
  }
  async function getHtml(url = "") {
    return await fetch(url);
  }
  function loadContainer(url, elementId) {
    getHtml(url)
      .then(response => {
        return response.text()
      })
      .then(html => {
        document.getElementById(elementId).innerHTML = html;
        document.getElementById(elementId).removeAttribute("onclick");

        initJoystick();
      });
  }

  function loadJoystick() {
    var newScript = document.createElement("script");
    newScript.src = "joystick.js";
    document.head.appendChild(newScript);

    setTimeout(() => { loadJavascript(); }, 1000);
  }

  function loadJavascript() {
    var newScript = document.createElement("script");
    newScript.src = "javascript.js";
    document.head.appendChild(newScript);
    console.log('javascript loaded');

    setTimeout(() => { systemInit(); }, 500);
  }   
</script>
)=====";
