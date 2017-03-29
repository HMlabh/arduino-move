/* 
 *  Ansteuerung des Hubsystems
 *  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
 *  Version 1.0 
 *  Stand: November 2016
 *  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
 *  Verfasser: Kevin Wayne Wallace
 */

#include <IRremote.h>				//Eingliederung der IR Bibliothek

unsigned short receiver = A0;       //Das digitale Signal wird vom angegebenen Pin abgegriffen
                                  
IRrecv irrecv(receiver);			//Definierung des Objekts welches die Signale der Fernbedienung ausliest
                                  
decode_results results;				//Ergebnisse werden decodiert und unter "results" abgespeichert


//////Motortreiber Pin Belegung//////
unsigned short enable1_1 = 8;				//enablePin MUSS PWM Pin sein
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


void setup()
{
	irrecv.enableIRIn();				//Initialisierung des Pins des IR Empfängers

	//Bestimmung der Pins der Motortreiber als AUsgabe (Output) Pins
	pinMode(enable1_1, OUTPUT);
	pinMode(controlInput1_1, OUTPUT);
	pinMode(controlInput1_2, OUTPUT);
	pinMode(enable1_2, OUTPUT);
	pinMode(controlInput1_3, OUTPUT);
	pinMode(controlInput1_4, OUTPUT);

	pinMode(enable2_1, OUTPUT);
	pinMode(controlInput2_1, OUTPUT);
	pinMode(controlInput2_2, OUTPUT);
	pinMode(enable2_2, OUTPUT);
	pinMode(controlInput2_3, OUTPUT);
	pinMode(controlInput2_4, OUTPUT);

	pinMode(enable3_1, OUTPUT);
	pinMode(controlInput3_1, OUTPUT);
	pinMode(controlInput3_2, OUTPUT);
	pinMode(enable3_2, OUTPUT);
	pinMode(controlInput3_3, OUTPUT);
	pinMode(controlInput3_4, OUTPUT);

	pinMode(enable4_1, OUTPUT);
	pinMode(controlInput4_1, OUTPUT);
	pinMode(controlInput4_2, OUTPUT);
	pinMode(enable4_2, OUTPUT);
	pinMode(controlInput4_3, OUTPUT);
	pinMode(controlInput4_4, OUTPUT);
	
	//enable Pins werden auf LOW gesetzt um unwillkürliches Starten der DC-Motoren zu vermeiden
	digitalWrite(enable1_1, LOW);
	digitalWrite(enable1_2, LOW);
	digitalWrite(enable2_1, LOW);
	digitalWrite(enable2_2, LOW);
	digitalWrite(enable3_1, LOW);
	digitalWrite(enable3_2, LOW);
	digitalWrite(enable4_1, LOW);
	digitalWrite(enable4_2, LOW);
}

void loop()
{
	if (irrecv.decode(&results))
	{
		switch (results.value)					//Switch Case Anweisung um die verschiedenen Motoren anzusteuern.
		{
		case 16712445:	VORWAERTS(); break;		//Taste: Pfeil Hoch
		case 16750695:	RUCKWARTS(); break;		//Taste: Pfeil Runter
		case 16769055:	LINKS(); break;			//Taste: Peil Links
		case 16748655:	RECHTS(); break;		//Taste: Pfeil Rechts
		case 16754775:	STOPP_SYS(); break;		//Taste: Zahnrad
		}
		irrecv.resume();						//Neustart des Receivers
	}
}