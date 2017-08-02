/*
*  Ansteuerung des Hubsystems
*  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
*  Version 1.1b
*  Stand: November 2016
*  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
*  Verfasser: Kevin Wayne Wallace
*/

//Weiterführung ab April 2017 : Markus Gutekunst

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(53);

byte data[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

namespace pin
{
	//Treiber 1 (M0|M1)
	uint8_t m0_fb	= A0	;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m0_sf	= 16	;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m0_pwm	= 2 ;	//PWM- Input
	uint8_t m0_in2	= 15;	//Steuertung der Drehrichtung
	uint8_t m0_in1	= 0 ;	//Steuertung der Drehrichtung
	uint8_t m01_en	= 17;	//Ein bzw. Ausschalten des gesammten Treibers (HIGH=ein)
	uint8_t m1_fb	= A1;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m1_sf	= 20;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m1_pwm	= 3 ;	//PWM- Input
	uint8_t m1_in2	= 18;	//Steuertung der Drehrichtung
	uint8_t m1_in1	= 1 ;	//Steuertung der Drehrichtung

	//Treiber 2 (M2|M3)
	uint8_t m2_fb	= A2;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m2_sf	= 24;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m2_pwm	= 4 ;	//PWM- Input
	uint8_t m2_in2	= 26;	//Steuertung der Drehrichtung
	uint8_t m2_in1	= 14;	//Steuertung der Drehrichtung
	uint8_t m23_en	= 28;	//Ein bzw. Ausschalten des gesammten Treibers (HIGH=ein)
	uint8_t m3_fb	= A3;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m3_sf	= 30;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m3_pwm	= 5 ;	//PWM- Input
	uint8_t m3_in2	= 32;	//Steuertung der Drehrichtung
	uint8_t m3_in1	= A5;	//Steuertung der Drehrichtung

	//Treiber 3 (M4|M5)
	uint8_t m4_fb	= A9;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m4_sf	= 31;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m4_pwm	= 7 ;	//PWM- Input
	uint8_t m4_in2	= 29;	//Steuertung der Drehrichtung
	uint8_t m4_in1	= 33;	//Steuertung der Drehrichtung
	uint8_t m45_en	= 27;	//Ein bzw. Ausschalten des gesammten Treibers (HIGH=ein)
	uint8_t m5_fb	= A8;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m5_sf	= 25;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m5_pwm	= 6 ;	//PWM- Input
	uint8_t m5_in2	= 23;	//Steuertung der Drehrichtung
	uint8_t m5_in1	= 35;	//Steuertung der Drehrichtung

	//Treiber 4 (M6|M7)
	uint8_t m6_fb	= A12;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m6_sf	= 49;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m6_pwm	= 46;	//PWM- Input
	uint8_t m6_in2	= 47;	//Steuertung der Drehrichtung
	uint8_t m6_in1	= 42;	//Steuertung der Drehrichtung
	uint8_t m67_en	= 45;	//Ein bzw. Ausschalten des gesammten Treibers (HIGH=ein)
	uint8_t m7_fb	= A11;	//Feedback (analoges Signal (525mV pro A Ausgangsleistung))
	uint8_t m7_sf	= 43;	//Status Flag (LOW, Wenn Treiber ausgeschaltet (Temp, D1 oder D2))
	uint8_t m7_pwm	= 44;	//PWM- Input
	uint8_t m7_in2	= 41;	//Steuertung der Drehrichtung
	uint8_t m7_in1	= 38;	//Steuertung der Drehrichtung

	//Enable Vector	------------MT1-----MT2-----MT3-----MT4---
	uint8_t	enable[4] =		{ m01_en, m23_en, m45_en, m67_en};

	//Control Verctor Motor:------0-------1-------2-------3-------4-------5-------6-------7
	uint8_t feedback[8] =	{	m0_fb,	m1_fb,	m2_fb,	m3_fb,	m4_fb,	m5_fb,	m6_fb,	m7_fb  };
	uint8_t status[8] =		{	m0_sf,	m1_sf,	m2_sf,	m3_sf,	m4_sf,	m5_sf,	m6_sf,	m7_sf  };
	uint8_t pwm[8] =			{	m0_pwm,	m1_pwm,	m2_pwm,	m3_pwm,	m4_pwm,	m5_pwm,	m6_pwm,	m7_pwm };
	uint8_t dir2[8] =		{	m0_in2,	m1_in2,	m2_in2,	m3_in2,	m4_in2,	m5_in2,	m6_in2,	m7_in2 };
	uint8_t dir1[8] =		{	m0_in1,	m1_in1,	m2_in1,	m3_in1,	m4_in1,	m5_in1,	m6_in1,	m7_in1 };

}

uint8_t status[8] = { 0 };


void setup()
{

	//-----IO----------


	// Motortreiber deaktiviert
	for (int i = 0; i <= 3; i++)
	{
		digitalWrite(pin::enable[i], LOW);
		pinMode(pin::enable[i], OUTPUT);
	}

	//restliche IO-Pins einstellen
	for (int i = 0; i <= 7; i++)
	{
		//Feedback <-- Input
		pinMode(pin::feedback[i], INPUT);
		//Status <-- Input
		pinMode(pin::status[i], INPUT);
		//PWM <-- 0%
		analogWrite(pin::pwm[i], 0);
		//Direction <-- Output, LOW
		digitalWrite(pin::dir2[i], LOW);
		pinMode(pin::dir2[i], OUTPUT);
		digitalWrite(pin::dir1[i], LOW);
		pinMode(pin::dir1[i], OUTPUT);

	}

	CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ);
	delay(100);
	CAN0.setMode(MCP_NORMAL);

	
}

//-------Funktionen-------
void testit()
{
	//Aktiviere alle Treiber
	for (int i = 0; i <= 3; i++)
	{
		enabledriver(i);
	}
	
	int test = 0;
	
	while (1)
	{
		
		byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);

		setramp(0, 20, 255, 5);
		delay(1000);
		setramp(0, 255, 20, 5);

		setramp(0, -20, -255, 5);
		setramp(0, -255, -20, 5);
		
		
		delay(1000);
		
	}
	

	
}


//stopall
void stopall()
{
	
}

//set speed of a mecanum wheel
void setspeed(int8_t wheelnumber, int16_t pwmfactor)
{
	if (wheelnumber < 8)
	{
		//vorwärts
		if (pwmfactor>0 && pwmfactor <= 255)
		{
			digitalWrite(pin::dir1[wheelnumber], LOW);
			digitalWrite(pin::dir2[wheelnumber], HIGH);
			analogWrite(pin::pwm[wheelnumber], pwmfactor);
		}
		//rückwärts
		else if (pwmfactor<0 && pwmfactor >= -255)
		{
			digitalWrite(pin::dir1[wheelnumber], HIGH);
			digitalWrite(pin::dir2[wheelnumber], LOW);
			analogWrite(pin::pwm[wheelnumber], -pwmfactor);
		}
		//stop
		else
		{
			digitalWrite(pin::dir1[wheelnumber], LOW);
			digitalWrite(pin::dir2[wheelnumber], LOW);
			analogWrite(pin::pwm[wheelnumber], 0);
		}
	}
	else{}
}

//rampup
void setramp(int8_t wheelnumber, int16_t pwmfactor_beginn, int16_t pwmfactor_end, int16_t rampdelay)
{
	//Plausibilitätscheck
	if (wheelnumber >= 0 && wheelnumber < 8 && -256 < pwmfactor_beginn < 256 && -256 < pwmfactor_end < 256 && rampdelay>0)
	{
		//vorwärts
		if (pwmfactor_end >= 0 && pwmfactor_beginn>=0)
		{
			//hochrampen
			if (pwmfactor_beginn < pwmfactor_end)
			{
				digitalWrite(pin::dir1[wheelnumber], LOW);
				digitalWrite(pin::dir2[wheelnumber], HIGH);
				for (int16_t i = pwmfactor_beginn; i <= pwmfactor_end; i++)
				{
					analogWrite(pin::pwm[wheelnumber], i);
					delay(rampdelay);
				}
			}
			//abrampen
			else if (pwmfactor_beginn > pwmfactor_end)
			{
				digitalWrite(pin::dir1[wheelnumber], LOW);
				digitalWrite(pin::dir2[wheelnumber], HIGH);
				for (int16_t i = pwmfactor_beginn; i >= pwmfactor_end; i--)
				{
					analogWrite(pin::pwm[wheelnumber], i);
					delay(rampdelay);
				}
			}
			else{}

		}
		//rückwärts
		else if (pwmfactor_end <= 0 && pwmfactor_beginn <= 0)
		{
			//hochrampen
			if (pwmfactor_beginn > pwmfactor_end)
			{
				digitalWrite(pin::dir1[wheelnumber], HIGH);
				digitalWrite(pin::dir2[wheelnumber], LOW);
				for (int16_t i = -pwmfactor_beginn; i <= -pwmfactor_end; i++)
				{
					analogWrite(pin::pwm[wheelnumber], i);
					delay(rampdelay);
				}
			}
			//abrampen
			else if (pwmfactor_beginn < pwmfactor_end)
			{
				digitalWrite(pin::dir1[wheelnumber], HIGH);
				digitalWrite(pin::dir2[wheelnumber], LOW);
				for (int16_t i = -pwmfactor_beginn; i >= -pwmfactor_end; i--)
				{
					analogWrite(pin::pwm[wheelnumber], i);
					delay(rampdelay);
				}
			}
			else{}
		}
		else{}
	}
	else {}
}


//enabledriver
void enabledriver(int8_t driver)
{
	if (driver <4)
	{
		digitalWrite(pin::enable[driver], HIGH);
	}
	else{}
}

//getstatus
void getstatus(int8_t wheelnumber)
{

}

//getcurrent
void getcurrent(int8_t wheelnumber)
{

}


void loop()
{

	testit();


}