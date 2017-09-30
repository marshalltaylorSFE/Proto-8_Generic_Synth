//Generic Proto-8 Hardware Sketch

#include "stdint.h"
#include "Wire.h"
#include "timerModule32.h"
#include "panelComponents.h"
#include "KnobPanel.h"
#include "proto-8Hardware.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=497,207
AudioOutputI2S           i2s1;           //xy=717,205
AudioConnection          patchCord1(sine1, 0, i2s1, 0);
AudioConnection          patchCord2(sine1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=705,293
// GUItool: end automatically generated code

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

	//**** Audio Section ****//
	AudioMemory(35);
	
	sine1.frequency(220);
	sine1.amplitude(1.0);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);
	
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

