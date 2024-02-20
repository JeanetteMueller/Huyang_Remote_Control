
String prepareEyeHtml(String name) {
  String s = "";

  s += "<div class=\"eyeContainer\">";

  s += "<a href=\"/get?" + ActionStringBlink + "=" + name + "\">";
  s += "<div class=\"eye\">";
  s += "<h5 style=\"padding: 34px 0 0 0;\">BLINK</h5>";
  s += "</div>";
  s += "</a>";

  s += "<a href=\"/get?" + ActionStringClose + "=" + name + "\" class=\"button\">CLOSE</a> ";
  s += "<a href=\"/get?" + ActionStringOpen + "=" + name + "\" class=\"button\">OPEN</a> ";
  s += "<br />";
  s += "<a href=\"/get?" + ActionStringFocus + "=" + name + "\" class=\"button\">FOCUS</a> ";
  s += "<a href=\"/get?" + ActionStringSad + "=" + name + "\" class=\"button\">SAD</a> ";
  s += "<a href=\"/get?" + ActionStringAngry + "=" + name + "\" class=\"button\">ANGRY</a>";
  s += "<br />";

  s += "</div>";

  return s;
}

String getBaseHtml(String body) {
  String html = baseHtml;
  html.replace("###STYLES###", styles);
  html.replace("###JAVASCRIPT###", javascript);
  html.replace("###BODY###", body);
  return html;
}

String getIndexPage() {

  String s = "";
  s += "<div id=\"container\">";
  s += "<div style=\"";
  s += "display: block;";

  s += "width:100%;";
  s += "text-align:center;";
  s += "\">";

  if (automaticState == AutomaticOn) {
    s += "<a href=\"/get?" + ActionStringAutomatic + "=" + ActionStringAutomaticOff + "\" class=\"button\">Auto is ON</a>";
  }else{
    s += "<a href=\"/get?" + ActionStringAutomatic + "=" + ActionStringAutomaticOn + "\" class=\"button\">Auto is OFF</a>";
  }

  s += " | ";
  s += "<a href=\"/get?" + ActionStringOpen + "=" + ActionTargetAll + "\" class=\"button\">OPEN</a>";
  s += " ";
  s += "<a href=\"/get?" + ActionStringClose + "=" + ActionTargetAll + "\" class=\"button\">CLOSE</a>";
  s += " ";
  s += "<a href=\"/get?" + ActionStringBlink + "=" + ActionTargetAll + "\" class=\"button\">BLINK</a>";
  s += " ";
  s += "<a href=\"/get?" + ActionStringFocus + "=" + ActionTargetAll + "\" class=\"button\">FOCUS</a>";
  s += " ";
  s += "<a href=\"/get?" + ActionStringSad + "=" + ActionTargetAll + "\" class=\"button\">SAD</a>";
  s += " ";
  s += "<a href=\"/get?" + ActionStringAngry + "=" + ActionTargetAll + "\" class=\"button\">ANGRY</a>";
  s += "</div>";

  s += prepareEyeHtml(ActionTargetLeft);
  s += prepareEyeHtml(ActionTargetRight);

  s += "</div>";

  return getBaseHtml(s);
}