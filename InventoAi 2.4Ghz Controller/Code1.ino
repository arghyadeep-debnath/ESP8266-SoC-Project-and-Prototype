/*
MIT License

Copyright (c) 2024 Arghyadeep Debnath

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/





#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "YourSSID";
const char *password = "YourPassword";

ESP8266WebServer server(80);

const int ledPin = D5;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, []() {
    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; text-align: center; margin-top: 50px; }";
    html += "h1 { color: #333; }";
    html += "form { margin-top: 20px; }";
    html += "input[type=submit] { background-color: #4CAF50; color: white; padding: 10px 15px; font-size: 16px; cursor: pointer; }";
    html += "@media only screen and (max-width: 600px) { body { margin-top: 20px; } }";
    html += "</style></head><body>";
    html += "<h1>InventoAi 2.4G Controler</h1>";
    html += "<p>LED State: " + String(ledState ? "ON" : "OFF") + "</p>";
    html += "<form action='/on' method='get'><input type='submit' value='Turn On'></form>";
    html += "<form action='/off' method='get'><input type='submit' value='Turn Off'></form>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/on", HTTP_GET, []() {
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/off", HTTP_GET, []() {
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
