//HOW TO OPERATE
//  Make TimerClass objects for each thing that needs periodic service
//  pass the interval of the period in ticks
//
//  Set maxInterval to rollover rate
//  Set maxTimer to the max foreseen interval of any timer.
//  maxTimer + maxInterval = max countable value.

//NOTICE:
//  The timerModule32 only works on teensy / fast processors.  It works the same
//  but keeps track of everything in us counts.


//Not used by this sketch but dependant on one 
#include "stdint.h"
#include "Wire.h"
#include "timerModule32.h"
#include "panelComponents.h"

#define LEDPIN 13

//Globals
uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;
uint32_t usTicks = 0;
uint8_t usTicksLocked = 1; //start locked out

IntervalTimer myTimer; //Interrupt for Teensy

//**Current list of timers********************//
TimerClass32 debugTimer( 1000000 ); //1 second
TimerClass32 serialTimer( 500000 ); //500ms
TimerClass32 knobTimer( 5000 ); //5ms

//components
Windowed10BitKnob myKnob;

void setup()
{
  //Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  // initialize IntervalTimer
  myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.000001 seconds
  myKnob.setHardware( new ArduinoAnalogIn( A1 ));
}

void loop()
{
	//Update the timers, but only once per interrupt
	if( usTicksLocked == 0 )
	{
		//**Copy to make a new timer******************//  
		//msTimerA.update(usTicks);
		debugTimer.update(usTicks);
		serialTimer.update(usTicks);
		knobTimer.update(usTicks);
		
		//Done?  Lock it back up
		usTicksLocked = 1;
	}  //The ISR will unlock.

	//**Copy to make a new timer******************//  
	//if(usTimerA.flagStatus() == PENDING)
	//{
	//	//User code
	//}
	
	if(debugTimer.flagStatus() == PENDING)
	{
		//User code
		digitalWrite( LEDPIN, digitalRead( LEDPIN ) ^ 0x01 );
	}
    if(serialTimer.flagStatus() == PENDING)
    {
        //User code
        Serial.println("Hello World");
    }
    if(knobTimer.flagStatus() == PENDING)
    {
        //User code
        myKnob.freshen(5);
		if(myKnob.serviceChanged())
		{
			Serial.println(myKnob.getState());
		}
    }
}

void serviceUS(void)
{
  uint32_t returnVar = 0;
  if(usTicks >= ( maxTimer + maxInterval ))
  {
    returnVar = usTicks - maxTimer;

  }
  else
  {
    returnVar = usTicks + 1;
  }
  usTicks = returnVar;
  usTicksLocked = 0;  //unlock
}

