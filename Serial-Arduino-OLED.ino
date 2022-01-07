#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial cdSerial_ESP(10, 11);


void setup() {

  cdSerial_ESP.begin(9600);
  delay(500);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.print("Inicializando...");
  display.display();
  delay(500);
}

void loop() {

  String vsData;
  
  if (cdSerial_ESP.available() > 0)
  {
    vsData = cdSerial_ESP.readString();
    if (vsData.startsWith("i") && vsData.endsWith("f"))
    {
      vsData = vsData.substring(1, (vsData.length() - 1));
      display.clearDisplay();
      display.setCursor(0,16);
      display.print("Dado recebido: " + vsData);
      display.display();
    }
  }

  delay(1000);
}
