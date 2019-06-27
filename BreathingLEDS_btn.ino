
#include <SPI.h>
#include <Adafruit_DotStar.h>

#define NUMPIXELS 120


const int ledPin = 13;
const int buttonPin = 7;
int flag = 1;
int buttonStatus = LOW;
//enum { OFF=0, WHITE_FADE, NUM_MODES } mode = OFF;
int mode = 0; // OFF, WHITE_FADE
#define OFF 0
#define WHITE_FADE 1
#define NUM_MODES 2

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG) ;

void btn_wait(int ms){
  for (int i = 0; i < ms; i++){
    if (digitalRead(buttonPin))
      buttonStatus = HIGH;
    delay(1);
  }
}

// Create the Strip

int start = 255;
int finish = 0;
uint16_t purple = strip.ColorHSV(282, 44, 42);
uint16_t noColor = strip.ColorHSV(0, 0, 0);

// Color Fade Purple
void whiteFade() {
  for ( int i = 200; i >= 0; i--) {
    strip.fill(purple, 0, 120);
    strip.setBrightness(i);
    btn_wait(10);
    strip.show();
  }

  for ( int i = 0; i <= 200; i++) {
    strip.fill(purple, 0, 120);
    strip.setBrightness(i);
    btn_wait(10);
    strip.show();
  }
}

// No color
void voidColor() {
  for ( int i = 200; i >= 0; i--) {
    strip.fill(noColor, 0, 120);
    strip.setBrightness(i);
    btn_wait(10);
    strip.show();
  }

  for ( int i = 0; i <= 200; i++) {
    strip.fill(noColor, 0, 120);
    strip.setBrightness(i);
    btn_wait(10);
    strip.show();
  }
}



void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void BTN(void) {

  if (buttonStatus){
      buttonStatus = LOW;
      if (++mode >= NUM_MODES)
        mode = OFF;
  }

  switch(mode){
    case OFF:
      voidColor();
      break;

    case WHITE_FADE:
      whiteFade();
      break;

    default:
      mode = OFF;   
  }
}



void loop() {
  BTN();
/*
  int currentStatus = digitalRead(buttonPin);

  if (currentStatus == HIGH && buttonStatus == LOW) {
    if (flag == 0 ) {
      digitalWrite(ledPin, HIGH);
      flag = 1;
      whiteFade();
      btn_wait(10);
      loop;

    } else {
      digitalWrite(ledPin, LOW);
       flag = 0;
      voidColor();
      btn_wait(10);
      loop;
    }
  }
  buttonStatus = currentStatus;
 */

}

//  whiteFade();
//  Serial.print(flag);
