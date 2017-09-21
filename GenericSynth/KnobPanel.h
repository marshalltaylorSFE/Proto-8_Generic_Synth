//Header
#ifndef KNOBPANEL_H_INCLUDED
#define KNOBPANEL_H_INCLUDED

#include "Panel.h"
#include "PanelComponents.h"
#include "HardwareInterfaces.h"
#include <Arduino.h>


enum PStates
{
	PInit,
	PRun,
};

class KnobPanel : public Panel
{
public:
	KnobPanel( void );
	void reset( void );
	void tickStateMachine( int msTicksDelta );
	
private:
	//Internal Panel Components
	Windowed10BitKnob A1Knob;
	Windowed10BitKnob A2Knob;
	Windowed10BitKnob A3Knob;
	Windowed10BitKnob A4Knob;
	Windowed10BitKnob A5Knob;
	Windowed10BitKnob A6Knob;
	Windowed10BitKnob A7Knob;
	Windowed10BitKnob A8Knob;
	
	Windowed10BitKnob B1Knob;
	Windowed10BitKnob B2Knob;
	Windowed10BitKnob B3Knob;
	Windowed10BitKnob B4Knob;
	Windowed10BitKnob B5Knob;
	Windowed10BitKnob B6Knob;
	Windowed10BitKnob B7Knob;
	Windowed10BitKnob B8Knob;

	Windowed10BitKnob C1Knob;
	Windowed10BitKnob C2Knob;
	Windowed10BitKnob C3Knob;
	Windowed10BitKnob C4Knob;
	Windowed10BitKnob C5Knob;
	Windowed10BitKnob C6Knob;
	Windowed10BitKnob C7Knob;
	Windowed10BitKnob C8Knob;

	//State machine stuff  
	PStates state;

};



#endif