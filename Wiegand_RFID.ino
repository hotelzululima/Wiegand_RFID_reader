#include <Wiegand.h>

#define DEBUG

#ifdef DEBUG
  #define debug(x)     Serial.print(x)
  #define debugln(x)   Serial.println(x)
#else
  #define debug(x)     // define empty, so macro does nothing
  #define debugln(x)
#endif

WIEGAND wg;
#define Led_pin 7
#define Buzz_pin 9
unsigned long ERR_SND = 1000; //1000 = 1sec

unsigned long allowedID = 0x8EDB59;

void setup() {
	Serial.begin(115200);  
  pinMode(Led_pin, OUTPUT);  // LED
  pinMode(Buzz_pin, OUTPUT);  // Buzzer
  digitalWrite(Buzz_pin, HIGH);
  debugln("RFID Readers");
	wg.begin();
}

void loop() {
	if(wg.available())
	{
		debug("Wiegand HEX = ");
		Serial.print(wg.getCode(),HEX);
		debug(", DECIMAL = ");
		debug(wg.getCode());
		debug(", Type W");
		debugln(wg.getWiegandType());    
    unsigned long code = wg.getCode();
    if (code == allowedID) {
      debugln( "Welcome!" );
    } else {
      debug( "Invalid code is 0x" );
      Serial.println( code, HEX );
      digitalWrite(Buzz_pin, LOW);
      digitalWrite(Led_pin, HIGH);
      delay(ERR_SND);
      digitalWrite(Led_pin, LOW);
      digitalWrite(Buzz_pin, HIGH);
    }
	}
}
