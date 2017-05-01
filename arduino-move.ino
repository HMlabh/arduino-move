/*
*  Ansteuerung des Hubsystems
*  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
*  Version 1.1b
*  Stand: November 2016
*  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
*  Verfasser: Kevin Wayne Wallace
*/

//Weiterführung ab April 2017 : Markus Gutekunst
#define IRRemote

#include <SoftPWM_timer.h>	//Libary for Software-PWM
#include <SoftPWM.h>		//Libary for Software-PWM

#ifdef IRRemote
#include <IRremote.h>        //Eingliederung der IR Bibliothek 

int16_t pwmspeed = 200;

unsigned short receiver = A0;       //Das digitale Signal wird vom angegebenen Pin abgegriffen 



IRrecv irrecv(receiver);      //Definierung des Objekts welches die Signale der Fernbedienung ausliest 

decode_results results;        //Ergebnisse werden decodiert und unter "results" abgespeichert 
#endif // IRRemote


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

int16_t wheelpwm[8] = { 0 };
uint8_t mram[16] = { 0 };



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


#ifdef IRRemote
	irrecv.enableIRIn();        //Initialisierung des Pins des IR Empfängers 
#endif // IRRemote


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
		SoftPWMSet(pin::control_1[i], 0);
		SoftPWMSet(pin::control_2[i], 0);
	}
}

//set speed of a mecanum wheel
void setspeed(int8_t wheelnumber, int16_t pwmfactor)
{
	if (pwmfactor = 0)		//stop
	{
		SoftPWMSet(pin::control_1[wheelnumber], 0);
		SoftPWMSet(pin::control_2[wheelnumber], 0);
	}
	else if (pwmfactor > 0)	//forward
	{
		uint8_t pwm = pwmfactor;
		SoftPWMSet(pin::control_1[wheelnumber], pwm);
		SoftPWMSet(pin::control_2[wheelnumber], 0);
	}
	else if (pwmfactor < 0)	//backward
	{
		uint8_t pwm = -pwmfactor;
		SoftPWMSet(pin::control_1[wheelnumber], 0);
		SoftPWMSet(pin::control_2[wheelnumber], pwm);
	}
}

#ifdef IRRemote
void irremote()
{
	if (irrecv.decode(&results))
	{
		switch (results.value)          //Switch Case Anweisung um die verschiedenen Motoren anzusteuern. 
		{
			
		case 16712445:	//Taste: Pfeil Hoch 
			setspeed(0, pwmspeed);
			setspeed(1, pwmspeed);
			setspeed(2, pwmspeed);
			setspeed(3, pwmspeed);

			setspeed(4, pwmspeed);
			setspeed(5, pwmspeed);
			setspeed(6, pwmspeed);
			setspeed(7, pwmspeed);
			break;    
		case 16750695:	//Taste: Pfeil Runter 
			setspeed(0, -pwmspeed);
			setspeed(1, -pwmspeed);
			setspeed(2, -pwmspeed);
			setspeed(3, -pwmspeed);

			setspeed(4, -pwmspeed);
			setspeed(5, -pwmspeed);
			setspeed(6, -pwmspeed);
			setspeed(7, -pwmspeed);
			break;    
		case 16769055:	//Taste: Peil Links 
			setspeed(0, pwmspeed);
			setspeed(1, pwmspeed);
			setspeed(2, pwmspeed);
			setspeed(3, pwmspeed);

			setspeed(4, -pwmspeed);
			setspeed(5, -pwmspeed);
			setspeed(6, -pwmspeed);
			setspeed(7, -pwmspeed);
			break;      
		case 16748655:  //Taste: Pfeil Rechts 
			setspeed(0, -pwmspeed);
			setspeed(1, -pwmspeed);
			setspeed(2, -pwmspeed);
			setspeed(3, -pwmspeed);

			setspeed(4, pwmspeed);
			setspeed(5, pwmspeed);
			setspeed(6, pwmspeed);
			setspeed(7, pwmspeed);
			break;    
		case 16754775:  //Taste: Zahnrad 
			setspeed(0, 0);
			setspeed(1, 0);
			setspeed(2, 0);
			setspeed(3, 0);
			setspeed(4, 0);
			setspeed(5, 0);
			setspeed(6, 0);
			setspeed(7, 0);
			break;    
			
		}
		irrecv.resume();    //Neustart des Receivers 
	}
}
#endif // IRRemote





void loop()
{
	testit();


#ifdef IRRemote
	irremote();

#endif // IRRemote

}