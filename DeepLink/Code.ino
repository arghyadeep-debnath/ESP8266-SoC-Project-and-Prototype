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

  server.on("/deepaccess", HTTP_GET, []() { // Modified route to /deepaccess
    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; text-align: center; margin-top: 50px; }";
    html += "h1 { color: #333; }";
    html += "form { margin-top: 20px; }";
    html += "input[type=submit] { background-color: #4CAF50; color: white; padding: 10px 15px; font-size: 16px; cursor: pointer; }";
    html += "@media only screen and (max-width: 600px) { body { margin-top: 20px; } }";
    html += "</style></head><body>";
    html += "<h1>InventoAi 2.4G Controller</h1>"; // Corrected spelling of Controller
    html += "<p>LED State: " + String(ledState ? "ON" : "OFF") + "</p>";
    html += "<form action='/deepaccess/on' method='get'><input type='submit' value='Turn On'></form>"; // Modified action to /deepaccess/on
    html += "<form action='/deepaccess/off' method='get'><input type='submit' value='Turn Off'></form>"; // Modified action to /deepaccess/off
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/deepaccess/on", HTTP_GET, []() { // Modified route to /deepaccess/on
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/deepaccess"); // Modified redirect location to /deepaccess
    server.send(303);
  });

  server.on("/deepaccess/off", HTTP_GET, []() { // Modified route to /deepaccess/off
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/deepaccess"); // Modified redirect location to /deepaccess
    server.send(303);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
