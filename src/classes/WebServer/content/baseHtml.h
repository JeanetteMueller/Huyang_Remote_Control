const char baseHtml[] = R"====(
<!DOCTYPE HTML><html>
<head>
<title>Huyang Control</title>
<meta name="viewport" content="width=device-width, minimal-ui">
<meta name="apple-mobile-web-app-capable" content="yes" />
<link rel="stylesheet" type="text/css" href="/styles.css">

<script type="text/javascript" src="/joystick.js"></script>
<script type="text/javascript" src="/javascript.js"></script>
</head>
<body>
###BODY###

<script>
    window.onload = function () {
        console.log('Dokument geladen');
        systemInit();
    }
</script>
</body>
</html>
)===="; 