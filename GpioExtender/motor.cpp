#include "motor.h"
#include "pins.h"
_Motor Motor;

#define ALPHA 0.10

// Direct PWM change variables
#define PWM10  OCR1B

// Frequency modes for TIMER4
#define PWM187k 1   // 187500 Hz
#define PWM94k  2   //  93750 Hz
#define PWM47k  3   //  46875 Hz
#define PWM23k  4   //  23437 Hz
#define PWM12k  5   //  11719 Hz
#define PWM6k   6   //   5859 Hz
#define PWM3k   7   //   2930 Hz

// Configure the PWM clock
// The argument is one of the 5 previously defined modes
void pwm91011configure(int mode)
{
	// TCCR1A configuration
	//  00 : Channel A disabled D9
	//  00 : Channel B disabled D10
	//  00 : Channel C disabled D11
	//  01 : Fast PWM 8 bit
	TCCR1A = 1;

	// TCCR1B configuration
	// Clock mode and Fast PWM 8 bit
	TCCR1B = mode | 0x08;

	// TCCR1C configuration
	TCCR1C = 0;
}

// Set PWM to D10
// Argument is PWM between 0 and 255
void pwmSet10(int value)
{
	OCR1B = value;   // Set PWM value
	DDRB |= 1 << 6;    // Set Output Mode B6
	TCCR1A |= 0x20;  // Set PWM value
}

void _Motor::Init()
{
	digitalWrite(MOTOR_DIR_A_PIN, HIGH);
	pinMode(MOTOR_DIR_A_PIN, OUTPUT);
	digitalWrite(MOTOR_DIR_B_PIN, HIGH);
	pinMode(MOTOR_DIR_B_PIN, OUTPUT);
	pinMode(MOTOR_PWM_PIN, OUTPUT);

	pwm91011configure(PWM23k);
	pwmSet10(0);


	pinMode(ENCODER_IRQ_PIN, INPUT);
	pinMode(ENCODER_DIRECTION_PIN, INPUT);
	digitalWrite(ENCODER_IRQ_PIN, HIGH);
	digitalWrite(ENCODER_DIRECTION_PIN, HIGH);
	attachInterrupt(digitalPinToInterrupt(ENCODER_IRQ_PIN), EncoderTick, FALLING);

	Tick = 0;
	lastSetpoint = -1;
	lastTick = 0;
	lastMicros = 0;
	rpm = 0;
}

void _Motor::Update(const int setpoint)
{
	if (setpoint != lastSetpoint)
	{
		if (setpoint < 0)
		{
			digitalWrite(MOTOR_DIR_A_PIN, HIGH);
		}
		else
		{
			digitalWrite(MOTOR_DIR_A_PIN, LOW);
		}

		if (setpoint < 0)
		{
			digitalWrite(MOTOR_DIR_B_PIN, LOW);
		}
		else
		{
			digitalWrite(MOTOR_DIR_B_PIN, HIGH);
		}

		PWM10 = abs(setpoint);
		lastSetpoint = setpoint;
	}
}

int _Motor::GetRpm()
{
	long tick = 0;
	noInterrupts();
	tick = Motor.Tick;
	interrupts();

	float rev = (tick - lastTick) / 480.0;
	float interval = ((micros() - lastMicros) / 1000000.0);
	float unfiltered = (rev / interval) * 60;
	lastTick = tick;
	lastMicros = micros();
	rpm = (unfiltered * ALPHA) + (float)(rpm * (1 - ALPHA));
	return rpm;
}

void _Motor::EncoderTick()
{
	if (PIND & 0x02) // Pin D1 - ENCODER_DIRECTION_PIN
	{
		Motor.Tick++;
	}
	else
	{
		Motor.Tick--;
	}
}

