#include <Arduino.h>
#include "KnobPanel.h"
#include "panelComponents.h"
#include "HardwareInterfaces.h"
#include "proto-8PanelComponents.h"
#include "proto-8HardwareInterfaces.h"

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
		break;
	default:
		nextState = PInit;
		break;
	}
	state = nextState;

}
