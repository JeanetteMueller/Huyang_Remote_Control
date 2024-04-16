#include "WebServer.h"

WebServer::WebServer(uint32_t port)
{
    _server = new AsyncWebServer(port);
}

void WebServer::start()
{
    _server->on(
        "/api/post.json", HTTP_POST, [&](AsyncWebServerRequest *request) {}, nullptr, [&](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { apiPostAction(request, data, len, index, total); });

    // _server->on("/", HTTP_POST, [&](AsyncWebServerRequest *request)
    //             { postAction(request); });

    _server->on("/styles.css", HTTP_GET, [&](AsyncWebServerRequest *request)
                { 
                    AsyncResponseStream *response = request->beginResponseStream("text/css");
                    response->print(styles);
                    request->send(response); });

    _server->on("/javascript.js", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/javascript");
                    response->print(javascript);

                    request->send(response); });

    _server->on("/joystick.js", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/javascript");
                    response->print(javascript_joystick);
                    request->send(response); });

    _server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/html");
                    response->print(getPage(indexPage, request));
                    request->send(response); });
    _server->on("/index.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                {
                    AsyncResponseStream *response = request->beginResponseStream("text/html");
                    response->print(getPage(indexPage, request));
                    request->send(response); });

    _server->on("/settings.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                { request->send(200, "text/html", getPage(settingsPage, request)); });

    _server->onNotFound([&](AsyncWebServerRequest *request)
                        { notFound(request); });

    _server->begin();
}

void WebServer::apiPostAction(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    Serial.println("apiPostAction!");

    JsonDocument json;
    deserializeJson(json, data, len);

    if (!json["automatic"].isNull())
    {
        faceAutomaticAnimations = json["automatic"];
        neckAutomaticAnimations = json["automatic"];
        bodyAutomaticAnimations = json["automatic"];

        Serial.print("post: automatic: ");
        Serial.println(json["automatic"] ? "true" : "false");
    }

    if (!json["face"].isNull())
    {
        if (!json["face"]["all"].isNull())
        {
            allEyes = json["face"]["all"];
            faceAutomaticAnimations = false;
            Serial.print("post: allEyes: ");
            Serial.println(allEyes);
        }
        else
        {
            if (!json["face"]["left"].isNull())
            {
                leftEye = json["face"]["left"];
                faceAutomaticAnimations = false;
                Serial.print("post: leftEye: ");
                Serial.println(leftEye);
            }
            if (!json["face"]["right"].isNull())
            {
                rightEye = json["face"]["right"];
                faceAutomaticAnimations = false;
                Serial.print("post: rightEye: ");
                Serial.println(rightEye);
            }
        }
    }

    if (!json["neck"].isNull())
    {
        if (!json["neck"]["rotate"].isNull())
        {
            neckRotate = json["neck"]["rotate"];
            neckAutomaticAnimations = false;
            Serial.print("post: headRotate: ");
            Serial.println(neckRotate);
        }
        if (!json["neck"]["tiltForward"].isNull())
        {
            neckTiltForward = json["neck"]["tiltForward"];
            neckAutomaticAnimations = false;
            Serial.print("post: headTiltForward: ");
            Serial.println(neckTiltForward);
        }
    }

    if (!json["body"].isNull())
    {
        if (!json["body"]["rotate"].isNull())
        {
            bodyRotate = json["body"]["rotate"];
            bodyAutomaticAnimations = false;
            Serial.print("post: bodyRotate: ");
            Serial.println(bodyRotate);
        }
        if (!json["body"]["tiltForward"].isNull())
        {
            bodyTiltForward = json["body"]["tiltForward"];
            bodyAutomaticAnimations = false;
            Serial.print("post: bodyTiltForward: ");
            Serial.println(bodyTiltForward);
        }
    }

    JsonDocument r = JsonDocument();
    r["face"]["automatic"] = faceAutomaticAnimations;
    if (NULL != allEyes)
    {
        r["face"]["eyes"]["all"] = allEyes;
    }
    if (NULL != leftEye)
    {
        r["face"]["eyes"]["left"] = leftEye;
    }
    if (NULL != rightEye)
    {
        r["face"]["eyes"]["right"] = rightEye;
    }

    r["neck"]["automatic"] = neckAutomaticAnimations;
    r["neck"]["rotate"] = neckRotate;
    r["neck"]["tiltForward"] = neckTiltForward;
    r["neck"]["tiltSideways"] = neckTiltSideways;

    r["body"]["automatic"] = bodyAutomaticAnimations;
    r["body"]["rotate"] = bodyRotate;
    r["body"]["tiltForward"] = bodyTiltForward;
    r["body"]["tiltSideways"] = bodyTiltSideways;

    String result;
    serializeJson(r, result);

    request->send(200, "application/json", result);
}

void WebServer::postAction(AsyncWebServerRequest *request)
{
    Serial.println("ACTION!");

    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

        if (p->name() == "whatever")
        {
        }
    }
    request->send(200, "text/html", getPage(indexPage, request));
}

String WebServer::getPage(Page page, AsyncWebServerRequest *request)
{
    if (request->hasParam("whatever"))
    {
        String action = request->getParam("whatever")->value();

        if (action == "1")
        {
        }
    }

    switch (page)
    {
    case indexPage:
        getBaseHtml(indexHtml, html);

        html.replace("###faceAutomaticAnimations###", faceAutomaticAnimations ? "ON" : "OFF");

        // html.replace("###neckTiltSideways###", neckTiltSideways);

        break;
    case settingsPage:
        getBaseHtml(settingsHtml, html);
        break;
    }
    return html;
}

void WebServer::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void WebServer::getBaseHtml(const String &body, String &target)
{
    target = baseHtml;
    target.replace("###BODY###", body);
    target.replace("###RANDOM###", random_string(10).c_str());
}

std::string WebServer::random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}