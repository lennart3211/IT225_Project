#include <WiFi.h>

const char* ssid = "esp32_hotspot";
const char* password = "12345678";
const char* serverIP = "192.168.6.198";  // IP address of your laptop
const int serverPort = 12345;  // Port number on which your server is listening

WiFiClient client;

typedef struct {
  float posx;
  float posy;
} GameData;

GameData data;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  data.posx = 0.0f;
  data.posy = 0.0f;
}

void loop() {
  if (client.connect(serverIP, serverPort)) {
    for (uint16_t i = 0; i < 400; i++) {
      for (uint16_t j = 0; j < 800; j++) {
        data.posx = (float)i;
        data.posy = (float)j;
        client.write((uint8_t*)&data, sizeof(data));      }
    }
  }
  delay(10);
}
