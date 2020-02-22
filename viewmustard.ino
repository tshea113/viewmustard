#include <SPI.h>
#include <SdFat.h>
#include <UTFT.h>
#include <UTFT_SdRaw.h>

#define MODE_PIN 3
#define LED_PIN  13         // the number of the LED pin
#define SD_CHIP_SELECT  53  // SD chip select pin(Arduino Mega)

#define NUM_IMAGES 9

SdFat sd;

UTFT myGLCD(ILI9486, 38, 39, 40, 41);
UTFT_SdRaw myFiles(&myGLCD);



volatile int image = 0;   // variable for reading the pushbutton status
volatile bool ready = 1;   // variable to verify ready for next image
volatile bool newImage = 0;
volatile static unsigned long last_interrupt_time = 0;

void setup()
{
  // Initialize the pushbutton pin as an input:
  pinMode(MODE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(MODE_PIN), pin_ISR, RISING);

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
  if (newImage)
  {
    ready = 0;

    char imName[6]; 
    char fileType[4] = ".RAW";

    sprintf(imName, "%i%s", image, fileType); 

    Serial.println(imName);

    myFiles.load(0, 0, 480, 320, imName, 1, 0);
    delay(4000);

    newImage = 0;
    ready = 1;
  }
}

void pin_ISR() {
  volatile unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    if (ready)
    {
      if (image < NUM_IMAGES) image++;
      else 
      {
        image = 1;
      }

      newImage = 1;
    }
    last_interrupt_time = interrupt_time;
  }
}