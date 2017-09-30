#include <Arduino.h>
#include "KnobPanel.h"
#include "panelComponents.h"
#include "HardwareInterfaces.h"
#include "proto-8PanelComponents.h"
#include "proto-8HardwareInterfaces.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

extern AudioControlSGTL5000     sgtl5000_1;

KnobPanel::KnobPanel( void )
{
	A1Knob.setHardware(new Proto8AnalogIn( 25 ));
	A2Knob.setHardware(new Proto8AnalogIn( 26 ));
	A3Knob.setHardware(new Proto8AnalogIn( 27 ));
	A4Knob.setHardware(new Proto8AnalogIn( 28 ));
	A5Knob.setHardware(new Proto8AnalogIn( 29 ));
	A6Knob.setHardware(new Proto8AnalogIn( 30 ));
	A7Knob.setHardware(new Proto8AnalogIn( 31 ));
	A8Knob.setHardware(new Proto8AnalogIn( 32 ));
	add( &A1Knob );
	add( &A2Knob );
	add( &A3Knob );
	add( &A4Knob );
	add( &A5Knob );
	add( &A6Knob );
	add( &A7Knob );
	add( &A8Knob );

	B1Knob.setHardware(new Proto8AnalogIn( 17 ));
	B2Knob.setHardware(new Proto8AnalogIn( 18 ));
	B3Knob.setHardware(new Proto8AnalogIn( 19 ));
	B4Knob.setHardware(new Proto8AnalogIn( 20 ));
	B5Knob.setHardware(new Proto8AnalogIn( 21 ));
	B6Knob.setHardware(new Proto8AnalogIn( 22 ));
	B7Knob.setHardware(new Proto8AnalogIn( 23 ));
	B8Knob.setHardware(new Proto8AnalogIn( 24 ));
	add( &B1Knob );
	add( &B2Knob );
	add( &B3Knob );
	add( &B4Knob );
	add( &B5Knob );
	add( &B6Knob );
	add( &B7Knob );
	add( &B8Knob );

	C1Knob.setHardware(new Proto8AnalogIn( 9 ));
	C2Knob.setHardware(new Proto8AnalogIn( 10 ));
	C3Knob.setHardware(new Proto8AnalogIn( 11 ));
	C4Knob.setHardware(new Proto8AnalogIn( 12 ));
	C5Knob.setHardware(new Proto8AnalogIn( 13 ));
	C6Knob.setHardware(new Proto8AnalogIn( 14 ));
	C7Knob.setHardware(new Proto8AnalogIn( 15 ));
	C8Knob.setHardware(new Proto8AnalogIn( 16 ));
	add( &C1Knob );
	add( &C2Knob );
	add( &C3Knob );
	add( &C4Knob );
	add( &C5Knob );
	add( &C6Knob );
	add( &C7Knob );
	add( &C8Knob );

	A1Led.setHardware(new Proto8DigitalOut( 25 ), 0);
	A2Led.setHardware(new Proto8DigitalOut( 26 ), 0);
	A3Led.setHardware(new Proto8DigitalOut( 27 ), 0);
	A4Led.setHardware(new Proto8DigitalOut( 28 ), 0);
	A5Led.setHardware(new Proto8DigitalOut( 29 ), 0);
	A6Led.setHardware(new Proto8DigitalOut( 30 ), 0);
	A7Led.setHardware(new Proto8DigitalOut( 31 ), 0);
	A8Led.setHardware(new Proto8DigitalOut( 32 ), 0);

	add( &A1Led );
	add( &A2Led );
	add( &A3Led );
	add( &A4Led );
	add( &A5Led );
	add( &A6Led );
	add( &A7Led );
	add( &A8Led );

	B1Led.setHardware(new Proto8DigitalOut( 17 ), 0);
	B2Led.setHardware(new Proto8DigitalOut( 18 ), 0);
	B3Led.setHardware(new Proto8DigitalOut( 19 ), 0);
	B4Led.setHardware(new Proto8DigitalOut( 20 ), 0);
	B5Led.setHardware(new Proto8DigitalOut( 21 ), 0);
	B6Led.setHardware(new Proto8DigitalOut( 22 ), 0);
	B7Led.setHardware(new Proto8DigitalOut( 23 ), 0);
	B8Led.setHardware(new Proto8DigitalOut( 24 ), 0);

	add( &B1Led );
	add( &B2Led );
	add( &B3Led );
	add( &B4Led );
	add( &B5Led );
	add( &B6Led );
	add( &B7Led );
	add( &B8Led );

	A1Button.setHardware(new Proto8DigitalIn( 2,1 ), 0);
	A2Button.setHardware(new Proto8DigitalIn( 2,2 ), 0);
	A3Button.setHardware(new Proto8DigitalIn( 2,3 ), 0);
	A4Button.setHardware(new Proto8DigitalIn( 2,4 ), 0);

	add( &A1Button );
	add( &A2Button );
	add( &A3Button );
	add( &A4Button );

	B1Button.setHardware(new Proto8DigitalIn( 1,1 ), 0);
	B2Button.setHardware(new Proto8DigitalIn( 1,2 ), 0);
	B3Button.setHardware(new Proto8DigitalIn( 1,3 ), 0);
	B4Button.setHardware(new Proto8DigitalIn( 1,4 ), 0);

	add( &B1Button );
	add( &B2Button );
	add( &B3Button );
	add( &B4Button );
	
	state = PInit;
}

void KnobPanel::reset( void )
{
	state = PInit;
	
}

void KnobPanel::tickStateMachine( int msTicksDelta )
{
	freshenComponents( msTicksDelta );
	
	//***** PROCESS THE LOGIC *****//
	//Now do the states.
	PStates nextState = state;
	switch( state )
	{
	case PInit:
		nextState = PRun;
		A3Led.setState(LEDON);
		break;
	case PRun:
		if( A1Knob.serviceChanged() )
		{
			Serial.print("knob A-1: ");
			Serial.println(A1Knob.getState());
		}
		if( B1Knob.serviceChanged() )
		{
			Serial.print("knob B-1: ");
			Serial.println(B1Knob.getState());
		}
		if( C1Knob.serviceChanged() )
		{
			Serial.print("knob C-1: ");
			Serial.println(C1Knob.getState());
		}
		if( A8Knob.serviceChanged() )
		{
			Serial.print("knob A-8: ");
			Serial.println(A8Knob.getState());
			sgtl5000_1.volume((float)A8Knob.getState()/1024);
		}
		if( A1Button.serviceRisingEdge() )
		{
			A1Led.setState(LEDON);
		}
		if( A2Button.serviceRisingEdge() )
		{
			A1Led.setState(LEDOFF);
		}
		if( B1Button.serviceRisingEdge() )
		{
			A2Led.setState(LEDFLASHING);
		}
		break;
	default:
		nextState = PInit;
		break;
	}
	state = nextState;

}
