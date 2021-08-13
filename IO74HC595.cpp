#include "IO74HC595.h"

IO74HC595::IO74HC595(short iLatchPin, short iDataPin, short iClockPin, short iNumberOfRegisters = 1)
{
	latchPin = iLatchPin;
	dataPin = iDataPin;
	clockPin = iClockPin;
	numberOfRegisters = iNumberOfRegisters;
	Init();
}

void IO74HC595::Init()
{
	registerState = new byte[numberOfRegisters];
	for (size_t i = 0; i < numberOfRegisters; i++) {
		registerState[i] = 0;
	}
}

void IO74HC595::UpdateShiftRegister()
{
	digitalWrite(latchPin, LOW);
	for (int i = 0; i < numberOfRegisters; i++) {
		//Get actual states for register
		byte* states = registerState[i];
		shiftOut(dataPin, clockPin, MSBFIRST, *states);
	}

	digitalWrite(latchPin, HIGH);
}

void IO74HC595::SetPin(int pin, bool state)
{
	//Determines register 
	int reg = pin / 8;
	//Determines pin for actual register
	int actualPin = pin - (8 * reg);
	//Begin session
	//digitalWrite(latchPin, LOW);
	for (int i = 0; i < numberOfRegisters; i++) {
		//Get actual states for register
		byte* states = registerState[i];
		//Update state
		if (i == reg) {
			bitWrite(*states, actualPin, state);
		}
		//Write
		//shiftOut(dataPin, clockPin, MSBFIRST, *states);
	}
	UpdateShiftRegister();
	//End session
	//digitalWrite(latchPin, HIGH);
}

void IO74HC595::ResetPins()
{
	for (size_t i = 0; i < numberOfRegisters; i++) {
		registerState[i] = 0;
	}
	UpdateShiftRegister();
}