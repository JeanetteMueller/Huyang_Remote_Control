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

    JsonDocument r = JsonDocument();

    if (!json["automatic"].isNull())
    {
        automaticAnimations = json["automatic"];

        Serial.print("post: automatic: ");
        Serial.println(json["automatic"] ? "true" : "false");
    }

    if (json["face"].isNull() == false)
    {
        uint16_t face_all = json["face"]["all"].as<uint16_t>();
        if (face_all != 0)
        {
            allEyes = face_all;
            leftEye = 0;
            rightEye = 0;

            automaticAnimations = false;
            Serial.print("post: allEyes: ");
            Serial.println(allEyes);
        }
        else
        {
            allEyes = 0;

            uint16_t face_left = json["face"]["left"].as<uint16_t>();
            uint16_t face_right = json["face"]["right"].as<uint16_t>();

            leftEye = face_left;
            rightEye = face_right;
            automaticAnimations = false;

            Serial.print("post: leftEye: ");
            Serial.println(leftEye);
            Serial.print("post: rightEye: ");
            Serial.println(rightEye);
        }
    }

    if (!json["neck"].isNull())
    {
        if (!json["neck"]["rotate"].isNull())
        {
            neckRotate = json["neck"]["rotate"];
            automaticAnimations = false;
            Serial.print("post: headRotate: ");
            Serial.println(neckRotate);
        }
        if (!json["neck"]["tiltForward"].isNull())
        {
            neckTiltForward = json["neck"]["tiltForward"];
            automaticAnimations = false;
            Serial.print("post: neckTiltForward: ");
            Serial.println(neckTiltForward);
        }
        if (!json["neck"]["tiltSideways"].isNull())
        {
            neckTiltSideways = json["neck"]["tiltSideways"];
            automaticAnimations = false;
            Serial.print("post: neckTiltSideways: ");
            Serial.println(neckTiltSideways);
        }
    }

    if (!json["body"].isNull())
    {
        if (!json["body"]["rotate"].isNull())
        {
            bodyRotate = json["body"]["rotate"];
            automaticAnimations = false;
            Serial.print("post: bodyRotate: ");
            Serial.println(bodyRotate);
        }
        if (!json["body"]["tiltForward"].isNull())
        {
            bodyTiltForward = json["body"]["tiltForward"];
            automaticAnimations = false;
            Serial.print("post: bodyTiltForward: ");
            Serial.println(bodyTiltForward);
        }
        if (!json["body"]["tiltSideways"].isNull())
        {
            bodyTiltSideways = json["body"]["tiltSideways"];
            automaticAnimations = false;
            Serial.print("post: bodyTiltSideways: ");
            Serial.println(bodyTiltSideways);
        }
    }

    r["automatic"] = automaticAnimations;

    r["face"]["eyes"]["all"] = allEyes;
    r["face"]["eyes"]["left"] = leftEye;
    r["face"]["eyes"]["right"] = rightEye;

    r["neck"]["rotate"] = neckRotate;
    r["neck"]["tiltForward"] = neckTiltForward;
    r["neck"]["tiltSideways"] = neckTiltSideways;

    r["body"]["rotate"] = bodyRotate;
    r["body"]["tiltForward"] = bodyTiltForward;
    r["body"]["tiltSideways"] = bodyTiltSideways;

    String result;
    serializeJson(r, result);

    request->send(200, "application/json", result);
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

        html.replace("###FACE###", indexHtml_face);
        html.replace("###NECK###", indexHtml_neck);
        html.replace("###BODY###", indexHtml_body);

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