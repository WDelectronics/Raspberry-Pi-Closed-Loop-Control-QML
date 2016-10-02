#include "motor.h"
#include "pins.h"

void setup()
{
	Serial.begin(115200);

	pinMode(VCC_PIN, OUTPUT);
	digitalWrite(VCC_PIN, HIGH);
	pinMode(GND_PIN, OUTPUT);
	digitalWrite(GND_PIN, LOW);

	Motor.Init();
}

unsigned long lastTxTime = 0;
unsigned long lastRxTime = 0;
int pwm = 0;

#define BUFFERSIZE 32

static void pollSerial(void)
{
	static char buffer[BUFFERSIZE];
	static char index = 0;

	while (Serial.available())
	{
		char data = Serial.read();
		if ((data == '\n') || (data == '\r'))
		{
			char next = Serial.peek();
			if ((next == '\n') || (next == '\r'))
			{
				Serial.read();
			}
			pwm = atoi(buffer);
			if ((pwm < -255) || (pwm > 255))
			{
				pwm = 0;
			}
			buffer[0] = '\0';
			index = 0;
			lastRxTime = millis();
		}
		else if (isprint(data))
		{
			if (index < BUFFERSIZE)
			{
				buffer[index++] = data;
				buffer[index] = '\0';
			}
		}
	}
}
void loop()
{
	static int lastRpm = -1, cntr = 0;
	pollSerial();

	if ((millis() - lastRxTime) > 5000)
	{
		Motor.Update(0);
	}
	else
	{
		Motor.Update(pwm);
	}
	if ((millis() - lastTxTime) > 10)
	{
		int rpm = Motor.GetRpm();
		if ((rpm != lastRpm) || (cntr >= 50))
		{
			Serial.println(rpm);
			lastRpm = rpm;
			cntr = 0;
		}
		cntr++;
		lastTxTime = millis();
	}
}
