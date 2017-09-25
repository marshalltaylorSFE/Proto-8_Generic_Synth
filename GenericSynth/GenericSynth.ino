//Generic Proto-8 Hardware Sketch

#include "stdint.h"
#include "Wire.h"
#include "timerModule32.h"
#include "panelComponents.h"
#include "KnobPanel.h"
#include "proto-8Hardware.h"

//Globals
uint32_t maxTimer = 60000000;
uint32_t maxInterval = 2000000;
uint32_t usTicks = 0;
uint8_t usTicksLocked = 1; //start locked out

LEDShiftRegister LEDs;
AnalogMuxTree knobs;
SwitchMatrix switches;

IntervalTimer myTimer; //Interrupt for Teensy

KnobPanel myCustomPanel;

//**Current list of timers********************//
TimerClass32 serialTimer( 5000000 ); //5 seconds
TimerClass32 panelTimer( 5000 ); //5ms
TimerClass32 LEDsTimer(20);
TimerClass32 switchesTimer(500);
TimerClass32 knobsTimer(500);


void setup()
{
	Serial.begin(115200);
	// initialize IntervalTimer
	myTimer.begin(serviceUS, 1);  // serviceMS to run every 0.000001 seconds
	myCustomPanel.reset();

    LEDs.begin();
    knobs.begin();
    switches.begin();

}

void loop()
{
	//Update the timers, but only once per interrupt
	if( usTicksLocked == 0 )
	{
		serialTimer.update(usTicks);
		panelTimer.update(usTicks);
		LEDsTimer.update(usTicks);
		switchesTimer.update(usTicks);
		knobsTimer.update(usTicks);
		
		usTicksLocked = 1;
	}

    if(serialTimer.flagStatus() == PENDING)
    {
        //User code
        Serial.println("Program running...");
    }
    if(panelTimer.flagStatus() == PENDING)
    {
		myCustomPanel.tickStateMachine(5);  //5 ms timer
    }
    if(LEDsTimer.flagStatus() == PENDING)
    {
		LEDs.send();
    }
    if(switchesTimer.flagStatus() == PENDING)
    {
		switches.scan();
    }
    if(knobsTimer.flagStatus() == PENDING)
    {
		knobs.scan();
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

