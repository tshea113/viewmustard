#include <SPI.h>
#include <SdFat.h>
#include <UTFT.h>
#include <UTFT_SdRaw.h>

#define MODE_PIN 3
#define LED_PIN  13         // the number of the LED pin
#define SD_CHIP_SELECT  53  // SD chip select pin(Arduino Mega)
SdFat sd;

UTFT myGLCD(ILI9486, 38, 39, 40, 41);
UTFT_SdRaw myFiles(&myGLCD);

volatile int buttonState = 0;   // variable for reading the pushbutton status
volatile static unsigned long last_interrupt_time = 0;

void setup()
{
  // Initialize the pushbutton pin as an input:
  pinMode(MODE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(MODE_PIN), pin_ISR, CHANGE);

  // Setup the serial connection
  Serial.begin(115200);

  delay(10);

  // Setup the SD card
  bool mysd = 0;
  while (!mysd)
  {
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED))
    {
      Serial.println(F("Card failed, or not present"));
      Serial.println(F("Retrying...."));
    }
    else
    {
      mysd = 1;
      Serial.println(F("Card initialised."));
    }
  }

  // Init the LCD
  Serial.println(F("Initialising LCD."));
  myGLCD.InitLCD();
  myGLCD.clrScr();
}

void loop()
{
  myFiles.load(0, 0, 480, 320, "01.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "02.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "03.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "04.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "05.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "06.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "07.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "08.RAW", 1, 0);
  delay(4000);
  myFiles.load(0, 0, 480, 320, "09.RAW", 1, 0);
  delay(4000);
}

void pin_ISR() {
  volatile unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    buttonState = digitalRead(MODE_PIN);
    digitalWrite(LED_PIN, buttonState);

    last_interrupt_time = interrupt_time;
  }
}