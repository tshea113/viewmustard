#include <SPI.h>
#include <SdFat.h>
#include <UTFT.h>
#include <UTFT_SdRaw.h>

#define MODE_PIN 3
#define SD_CHIP_SELECT  53  // SD chip select pin(Arduino Mega)
SdFat sd;

UTFT myGLCD(ILI9486, 38, 39, 40, 41);
UTFT_SdRaw myFiles(&myGLCD);

volatile uint8_t mode = 0;
volatile static unsigned long last_interrupt_time = 0;

void setup()
{
  pinMode(MODE_PIN, INPUT);
  Serial.begin(115200);
  delay(10);
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