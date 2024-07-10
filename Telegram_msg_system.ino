#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Replace with your network credentials
const char* ssid = "Saad";
const char* password = "AndroiD@mekalil.123,./";

// Initialize Telegram BOT
#define BOTtoken "7075268230:AAGGeD95WSJJh7s0NI7DP65rTf1l0blQxSw"  // your Bot Token (get from BotFather)
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)

WiFiClientSecure client;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTime = 0;
const unsigned long BOT_MTBS = 100; // mean time between scan messages

void setup() {
  Serial.begin(115200);

    // Initialize with the I2C addr 0x3C (for the 128x64)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  client.setInsecure();

   // Clear the buffer
  display.clearDisplay();

  // Print initial message on the OLED display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, ESP32!");

  // Display the content on the screen
  display.display();

}

void loop() {
  if (millis() - lastTime > BOT_MTBS)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Got response");
      for (int i = 0; i < numNewMessages; i++) {
        String chat_id = bot.messages[i].chat_id;
        String text = bot.messages[i].text;

        // Print the message received

        if (chat_id == "6209691381"){
        Serial.println("Message from Ammy :)");
        Serial.println("Message: " + text);

            display.println(text);
            display.display();

        } else {

        Serial.println("Message from chat ID: " + chat_id);
        Serial.println("Message: " + text);
        }
        
        // Optionally, you can send a confirmation message back to your bot
        bot.sendMessage(chat_id, "I received: " + text, "");
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTime = millis();
  }
}
