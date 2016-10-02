#pragma once
#include "Arduino.h"

class _Motor
{
public:
	void Init();
	void Update(int setpoint);
	int GetRpm();

private:
	static void EncoderTick();
	//void SetPwmFrequency(int pin, int divisor);
	int lastSetpoint;
	long lastTick;
	unsigned long lastMicros;
	int rpm;
	volatile long Tick;
};
extern _Motor Motor;

