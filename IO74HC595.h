#pragma once
#include <arduino.h>
//#define unsigned char byte
//#include <stdint.h>
class IO74HC595
{
protected:
	short latchPin;		// shift register clock / latch
	short dataPin;		// ser
	short clockPin;		// register clock
	short numberOfRegisters;
	byte* registerState;
	
	void Init();

public:
	IO74HC595(short iLatchPin, short iDataPin, short iClockPin, short iNumberOfRegisters=1);

	short GetLatchPin();
	short GetDataPin();
	short GetClockPin();
	void SetLatchPin();
	void SetDataPin();
	void SetClockPin();

	void UpdateShiftRegister();
	void SetPin(int pin, bool state);
	void ResetPins();
};

