// Atoll v4 Stick - Controller Software
// Todo:
// - Add soft auto calibration
// - Add tft screen to allow manual calibrations without having to flash the controller
// - Add pedals
// - Add a proper linearity measurement mode + counter curve

#include <Wire.h>
#include <ADS1X15.h>

// Pin Definitions:
#define HAT_PIN_TOP 2
#define HAT_PIN_BOTTOM 3
#define HAT_PIN_LEFT 4
#define HAT_PIN_RIGHT 5
#define PIN_BUTTON_FIRE 6
//#define PIN_BUTTON_BELOW_HAT 6
//#define PIN_BUTTON_SIDE_UP 4
//#define PIN_BUTTON_SIDE_DOWN 5

// Variables:
ADS1115 ADS(0x48);

bool calibrate = false;
int minimum = 12357;
int maximum = 28745;
int medium = 20691;
float range_multiplier = 3.931f;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  ADS.begin();
  ADS.setGain(1);
  ADS.setDataRate(7);
  ADS.setMode(0);
  ADS.requestADC(0);   

  //pinMode(PIN_BUTTON_SIDE_UP, INPUT_PULLUP);  // 4
  //pinMode(PIN_BUTTON_SIDE_DOWN, INPUT_PULLUP);// 5
  //pinMode(PIN_BUTTON_BELOW_HAT, INPUT_PULLUP);// 6
  pinMode(PIN_BUTTON_FIRE, INPUT_PULLUP);     // 7
  pinMode(HAT_PIN_RIGHT, INPUT_PULLUP); // 8
  pinMode(HAT_PIN_LEFT, INPUT_PULLUP);  // 9
  pinMode(HAT_PIN_BOTTOM, INPUT_PULLUP);// 10
  pinMode(HAT_PIN_TOP, INPUT_PULLUP);   // 11
  //pinMode(13, OUTPUT);      // Polling rate indicator LED

  Joystick.begin();
  Joystick.useManualSend(true);

  if(calibrate) Serial.begin(9600);
}


void loop() {
  unsigned long start_time = micros();
  Joystick.X(32768); // reserved for the gunfighter gimbal x 
  Joystick.Y(32768); // reserved for the gunfighter gimbal y
  Joystick.Xrotate(32768); // reserved for second stick x
  Joystick.Yrotate(32768); // reserved for second stick y
  Joystick.Zrotate(32768); // reserved for pedal sensitivity adjust axis
  
  int32_t axis = ADS.getValue();
  
  if(calibrate)
  {
    if( axis < minimum ) minimum = axis;
    if( axis > maximum ) maximum = axis;
    if( digitalRead(PIN_BUTTON_FIRE) == LOW)
    {
      minimum = 65536;
      maximum = 0;
      medium = axis;
    }
    String s = (String)axis+"    MIN: "+(String)minimum +"  MED: "+(String)medium+"  MAX: "+(String)maximum +"     LOW_RANGE: "+(String)(medium - minimum)+"  HIGH_RANGE: "+(String)(maximum - medium) ;
    Serial.println(s);
  }
  else
  {
    // clamp input within the expected range, gross mismatches here would indicate a shifting magnet/sensor position which would be useful to display with an led
    if(axis < minimum) axis = minimum;
    else if(axis > maximum) axis = maximum;
  
    axis = 32768 + ((float)(axis - medium) * range_multiplier); //* (invert_axis ? -1 : 1);

    if(axis < 0) axis = 0;
    else if(axis > 65536) axis = 65536;
    //Serial.println(axis);
    Joystick.Z(axis);

  }

  process_firing_buttons();
  process_8way_hat();


  Joystick.send_now();
  unsigned long end_time = micros();
  int time_passed_in_microseconds = end_time - start_time;
  if(time_passed_in_microseconds < 950)
    delayMicroseconds(1000 - time_passed_in_microseconds);
}


void process_firing_buttons()
{
  Joystick.button(1, digitalRead(PIN_BUTTON_FIRE) == LOW ? 1 : 0);  
  //Joystick.button(2, digitalRead(PIN_BUTTON_BELOW_HAT) == LOW ? 1 : 0);   
  //Joystick.button(3, digitalRead(PIN_BUTTON_SIDE_UP) == LOW ? 1 : 0);   
  //Joystick.button(4, digitalRead(PIN_BUTTON_SIDE_DOWN) == LOW ? 1 : 0);   
}

void process_8way_hat()
{
    // read the hat and set one of the 8 directions
  int hat = 0;
  hat += (digitalRead(HAT_PIN_TOP) == LOW ? 1 : 0);
  hat += (digitalRead(HAT_PIN_RIGHT) == LOW ? 2 : 0);
  hat += (digitalRead(HAT_PIN_BOTTOM) == LOW ? 4 : 0);
  hat += (digitalRead(HAT_PIN_LEFT) == LOW ? 8 : 0);

  // 0 1 2 3 => top, right, below, left
  // 1 2 4 8 -> 0, 1, 2, 4, 8, 3, 6, 12, 9
  switch(hat){
    case 0:  Joystick.hat(0, -1); break; // hat is in neutral position
    case 1:  Joystick.hat(0, 0); break;      // top
    case 2:  Joystick.hat(0, 90); break;     // right
    case 3:  Joystick.hat(0, 45); break;     // top + right
    case 4:  Joystick.hat(0, 180); break;    // below
    case 6:  Joystick.hat(0, 135); break;    // below + right
    case 8:  Joystick.hat(0, 270); break;    // left
    case 9:  Joystick.hat(0, 315); break;    // top + left      
    case 12: Joystick.hat(0, 225); break;    // below + left
      
  }
}
