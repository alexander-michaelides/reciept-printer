#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "wifi_handler.h"
#include "HardwareSerial.h"
#include "WiFiType.h"
#include "esp32-hal.h"
#include "esp_wifi_types_generic.h"
#include "http_parser.h"
#include "secrets.h"

WebServer server(80);

void initNetwork() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    Serial.print("Connecting to Wi-Fi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected, IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", R"rawliteral(
            <!DOCTYPE html>
            <html>
            <head>
                <meta name="viewport" content="width=device-width, initial-scale=1">
                <title>Receipt Printer</title>
            </head>
            <body>
                <h1>Receipt Printer</h1>

                <form action="/print" method="POST">
                    <input type="text" name="text"
                        placeholder="Enter a task" required>
                    <button type="submit">Print</button>
                </form>
            </body>
            </html>
        )rawliteral");
    });

    server.on("/print", HTTP_POST, []() {
        if (!server.hasArg("text")) {
            server.send(400, "text/plain", "Missing text");
            return;
        }

        String text = server.arg("text");
        Serial.printf("Printing \"%s\"", text.c_str());

        server.send(200, "text/plain", "Received: " + text);
    });

    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found :(");
    });

    server.begin();
    Serial.println("HTTP server started");
}

void handleNetwork() {
    server.handleClient();
}