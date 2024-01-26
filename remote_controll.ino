#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const uint16_t kRecvPin = 14;  // GPIO 14 on NodeMCU

IRrecv irrecv(kRecvPin);
decode_results results;

const char* kodiIp = "";
const int kodiPort = 8080;
const char* kodiUsername = "";
const char* kodiPassword = "";

const char* ssid = "";
const char* password = "";

unsigned long lastDigitTime = 0;
int digitBuffer = 0;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  irrecv.enableIRIn();
}

int getCorrespondingValue(unsigned long hexCode) {
  // Add more hex codes as needed
  switch (hexCode) {
    case 0x1FE50AF: return 1;
    case 0x1FED827: return 2;
    case 0x1FEF807: return 3;
    case 0x1FE30CF: return 4;
    case 0x1FEB04F: return 5;
    case 0x1FE708F: return 6;
    case 0x1FE00FF: return 7;
    case 0x1FEF00F: return 8;
    case 0x1FE9867: return 9;
    case 0x1FEE01F: return 0;
    default: return -1;  // Unknown code
  }
}

void processDigit(int digit) {
  digitBuffer = digitBuffer * 10 + digit;
  lastDigitTime = millis();  // Update the time of the last received digit
}


void sendKodiRequest(const char* method, int channelId) {
  HTTPClient http;

  String url = "http://" + String(kodiIp) + ":" + String(kodiPort) + "/jsonrpc";
  http.begin(url);
  http.setAuthorization(kodiUsername, kodiPassword);
  http.addHeader("Content-Type", "application/json");

  String jsonRequest = "{\"jsonrpc\": \"2.0\", \"method\": \"" + String(method) + "\", \"params\": {\"item\": {\"channelid\": " + String(channelId) + "}}, \"id\": 1}";
  int httpResponseCode = http.POST(jsonRequest);

  Serial.print("HTTP Response Code: ");
  Serial.println(httpResponseCode);

  http.end();
}

void loop() {
  if (irrecv.decode(&results)) {
    int digit = getCorrespondingValue(results.value);
    if (digit != -1) {
      processDigit(digit);
      Serial.print("Received digit: ");
      Serial.println(digit);
    }

    irrecv.resume();  // Receive the next value
  }

  // Adjust the delay as needed for your application
  delay(100);

  // Check if a certain time period has passed (e.g., 2 seconds) since the last digit
  if (millis() - lastDigitTime > 2000 && digitBuffer != 0) {
    Serial.print("Entered Number: ");
    Serial.println(digitBuffer);

    // Process the entered number (send to Kodi or perform any other action)
     sendKodiRequest("Player.Open", digitBuffer);
    // Reset the digit buffer for the next input
    digitBuffer = 0;
  }
}