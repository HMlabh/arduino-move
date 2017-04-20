/*
*  Ansteuerung des Hubsystems
*  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
*  Version 1.0
*  Stand: November 2016
*  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
*  Verfasser: Kevin Wayne Wallace
*/

//Weiterführung ab April 2017 : Markus Gutekunst


#include <SoftPWM_timer.h>	//Libary for Software-PWM
#include <SoftPWM.h>		//Libary for Software-PWM

namespace pin
{
	uint8_t	enable[8] =		{ 9,		8,	7,	6,	5,	4,	3,	2 };
	uint8_t control_1[8] =	{ 23	,	25,	27,	29,	31,	33,	35,	37 };
	uint8_t control_2[8] =	{ 53	,	51,	49,	47,	39,	41,	43,	45 };
}

									//////Motortreiber Pin Belegung//////
/*
unsigned short enable1_1 = 8;
unsigned short controlInput1_1 = 51;
unsigned short controlInput1_2 = 25;
unsigned short enable1_2 = 9;
unsigned short controlInput1_3 = 23;
unsigned short controlInput1_4 = 53;

unsigned short enable2_1 = 6;
unsigned short controlInput2_1 = 47;
unsigned short controlInput2_2 = 29;
unsigned short enable2_2 = 7;
unsigned short controlInput2_3 = 27;
unsigned short controlInput2_4 = 49;

unsigned short enable3_1 = 4;
unsigned short controlInput3_1 = 41;
unsigned short controlInput3_2 = 33;
unsigned short enable3_2 = 5;
unsigned short controlInput3_3 = 31;
unsigned short controlInput3_4 = 39;

unsigned short enable4_1 = 2;
unsigned short controlInput4_1 = 45;
unsigned short controlInput4_2 = 37;
unsigned short enable4_2 = 3;
unsigned short controlInput4_3 = 35;
unsigned short controlInput4_4 = 43;
*/

uint8_t wheelpwm[8] = { 0 };
uint8_t mram[16] = { 0 };
int8_t direction[8] = { 0 };


void setup()
{

	//Bestimmung der Pins der Motortreiber als AUsgabe (Output) Pins
	for (int i = 0; i < 8; i++)
	{
		pinMode(pin::enable[i], OUTPUT);
		pinMode(pin::control_1[i], OUTPUT);
		pinMode(pin::control_2[i], OUTPUT);
	}

	//enable Pins werden auf LOW gesetzt um unwillkürliches Starten der DC-Motoren zu vermeiden
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(pin::enable[i], HIGH);
	}

	SoftPWMBegin();



}

//-------Funktionen-------
void testit()
{
	/*
	for (int n = 0; n < 255; n++)
	{
		for (int i = 0; i < 8; i++)
		{
			SoftPWMSet(pin::control_1[i], n);
			SoftPWMSet(pin::control_2[i], 0);
		}
	delay(10);
	}
	for (int n = 255; n >0; n--)
	{
		for (int i = 0; i < 8; i++)
		{
			SoftPWMSet(pin::control_1[i], n);
			SoftPWMSet(pin::control_2[i], 0);
		}
		delay(10);
	}
	*/
	for (int i = 0; i < 8; i++)
	{
		SoftPWMSet(pin::control_1[i], 0);
		SoftPWMSet(pin::control_2[i], 0);
	}
	delay(2000);


	
}


//stopall
void stopall()
{
	for (int i = 0; i < 8; i++)
	{
		pinMode(pin::enable[i], LOW);
	}
}

//set speed of a mecanum wheel
void setspeed(int8_t wheelnumber, uint8_t wheelpwmfactor, int8_t wheeldirection)
{
	if (wheeldirection = 1)//forward
	{

	}
}






void loop()
{
	testit();
}