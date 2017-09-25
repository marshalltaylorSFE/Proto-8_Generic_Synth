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
	Simple10BitKnob A1Knob;
	Simple10BitKnob A2Knob;
	Simple10BitKnob A3Knob;
	Simple10BitKnob A4Knob;
	Simple10BitKnob A5Knob;
	Simple10BitKnob A6Knob;
	Simple10BitKnob A7Knob;
	Simple10BitKnob A8Knob;
	
	Simple10BitKnob B1Knob;
	Simple10BitKnob B2Knob;
	Simple10BitKnob B3Knob;
	Simple10BitKnob B4Knob;
	Simple10BitKnob B5Knob;
	Simple10BitKnob B6Knob;
	Simple10BitKnob B7Knob;
	Simple10BitKnob B8Knob;

	Simple10BitKnob C1Knob;
	Simple10BitKnob C2Knob;
	Simple10BitKnob C3Knob;
	Simple10BitKnob C4Knob;
	Simple10BitKnob C5Knob;
	Simple10BitKnob C6Knob;
	Simple10BitKnob C7Knob;
	Simple10BitKnob C8Knob;

	Led A1Led;
	Led A2Led;
	Led A3Led;
	Led A4Led;
	Led A5Led;
	Led A6Led;
	Led A7Led;
	Led A8Led;

	Led B1Led;
	Led B2Led;
	Led B3Led;
	Led B4Led;
	Led B5Led;
	Led B6Led;
	Led B7Led;
	Led B8Led;
	
	Button A1Button;
	Button A2Button;
	Button A3Button;
	Button A4Button;
	
	Button B1Button;
	Button B2Button;
	Button B3Button;
	Button B4Button;
	
	
	//State machine stuff  
	PStates state;

};



#endif