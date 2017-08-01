/*
*  Ansteuerung des Hubsystems
*  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
*  Version 1.1b
*  Stand: November 2016
*  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
*  Verfasser: Kevin Wayne Wallace
*/

//Weiterführung ab April 2017 : Markus Gutekunst




namespace pin
{
	unsigned short enable1_1 = 8;
}

////////////////Motor--------1-----2---3---4---5---6---7---8
uint8_t	enable[8] =		{ 9,		8,	7,	6,	5,	4,	3,	2 };
uint8_t control_1[8] =	{ 23	,	25,	27,	29,	31,	33,	35,	37 };
uint8_t control_2[8] =	{ 53	,	51,	49,	47,	39,	41,	43,	45 };


int16_t wheelpwm[8] = { 0 };
uint8_t mram[16] = { 0 };



void setup()
{

	


}

//-------Funktionen-------
void testit()
{
	


	
}


//stopall
void stopall()
{
	
}

//set speed of a mecanum wheel
void setspeed(int8_t wheelnumber, int16_t pwmfactor)
{
	
}







void loop()
{

	testit();


}