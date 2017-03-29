/*
*  Ansteuerung des Hubsystems
*  Dies ist der Ansteuerungscode für die Schrittmotoren, welche den Hub des Prototyps übernehmen.
*  Version 1.0
*  Stand: November 2016
*  Dieser Code wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
*  Verfasser: Kevin Wayne Wallace
*/

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

/*
Funktionen zum fahren..
Sie wurden ausgelagert um die Übersichtlichkeit zu gewährleisten.
Version 1.0
Stand: November 2016
Dieser Coder wurde im Rahmen einer Bachelorarbeit an der Hochschule München erstellt.
Verfasser: Kevin Wayne Wallace
*/

void VORWAERTS()
{
	/////////////////////////////////////////////
	//DC-Motorpaar 1 - Links
	digitalWrite(controlInput1_1, LOW);
	digitalWrite(controlInput1_2, HIGH);
	digitalWrite(enable1_1, HIGH);

	//DC-Motorpaar 2 - Rechts
	digitalWrite(controlInput1_3, LOW);
	digitalWrite(controlInput1_4, HIGH);
	digitalWrite(enable1_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 2 - Links
	digitalWrite(controlInput2_1, HIGH);
	digitalWrite(controlInput2_2, LOW);
	digitalWrite(enable2_1, HIGH);

	//DC-Motorpaar 2 - Rechts
	digitalWrite(controlInput2_3, HIGH);
	digitalWrite(controlInput2_4, LOW);
	digitalWrite(enable2_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 3 - Links
	digitalWrite(controlInput3_1, HIGH);
	digitalWrite(controlInput3_2, LOW);
	digitalWrite(enable3_1, HIGH);

	//DC-Motorpaar 3 - Rechts
	digitalWrite(controlInput3_3, HIGH);
	digitalWrite(controlInput3_4, LOW);
	digitalWrite(enable3_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 4 - Links
	digitalWrite(controlInput4_1, HIGH);
	digitalWrite(controlInput4_2, LOW);
	digitalWrite(enable4_1, HIGH);

	//DC-Motorpaar 4 - Rechts
	digitalWrite(controlInput4_3, HIGH);
	digitalWrite(controlInput4_4, LOW);
	digitalWrite(enable4_2, HIGH);
}

void RUCKWARTS()									//U=Ü und A=Ä, Umlaute werden nicht erkannt
{
	/////////////////////////////////////////////
	//DC-Motorpaar 1 - Links
	digitalWrite(controlInput1_1, HIGH);
	digitalWrite(controlInput1_2, LOW);
	digitalWrite(enable1_1, HIGH);

	//DC-Motorpaar 1 - Rechts
	digitalWrite(controlInput1_3, HIGH);
	digitalWrite(controlInput1_4, LOW);
	digitalWrite(enable1_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 2 - Links
	digitalWrite(controlInput2_1, LOW);
	digitalWrite(controlInput2_2, HIGH);
	digitalWrite(enable2_1, HIGH);

	//DC-Motorpaar 2 - Rechts
	digitalWrite(controlInput2_3, LOW);
	digitalWrite(controlInput2_4, HIGH);
	digitalWrite(enable2_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 3 - Links
	digitalWrite(controlInput3_1, LOW);
	digitalWrite(controlInput3_2, HIGH);
	digitalWrite(enable3_1, HIGH);

	//DC-Motorpaar 3 - Rechts
	digitalWrite(controlInput3_3, LOW);
	digitalWrite(controlInput3_4, HIGH);
	digitalWrite(enable3_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 4 - Links
	digitalWrite(controlInput4_1, LOW);
	digitalWrite(controlInput4_2, HIGH);
	digitalWrite(enable4_1, HIGH);

	//DC-Motorpaar 4 - Rechts
	digitalWrite(controlInput4_3, LOW);
	digitalWrite(controlInput4_4, HIGH);
	digitalWrite(enable4_2, HIGH);
}

void LINKS()
{
	/////////////////////////////////////////////
	//DC-Motorpaar 1 - Links
	digitalWrite(controlInput1_1, HIGH);
	digitalWrite(controlInput1_2, LOW);
	digitalWrite(enable1_1, HIGH);

	//DC-Motorpaar 1 - Rechts
	digitalWrite(controlInput1_3, LOW);
	digitalWrite(controlInput1_4, HIGH);
	digitalWrite(enable1_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 2 - Links
	digitalWrite(controlInput2_1, HIGH);
	digitalWrite(controlInput2_2, LOW);
	digitalWrite(enable2_1, HIGH);

	//DC-Motorpaar 2 - Rechts
	digitalWrite(controlInput2_3, LOW);
	digitalWrite(controlInput2_4, HIGH);
	digitalWrite(enable2_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 3 - Links
	digitalWrite(controlInput3_1, HIGH);
	digitalWrite(controlInput3_2, LOW);
	digitalWrite(enable3_1, HIGH);

	//DC-Motorpaar 3 - Rechts
	digitalWrite(controlInput3_3, LOW);
	digitalWrite(controlInput3_4, HIGH);
	digitalWrite(enable3_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 4 - Links
	digitalWrite(controlInput4_1, HIGH);
	digitalWrite(controlInput4_2, LOW);
	digitalWrite(enable4_1, HIGH);

	//DC-Motorpaar 4 - Rechts
	digitalWrite(controlInput4_3, LOW);
	digitalWrite(controlInput4_4, HIGH);
	digitalWrite(enable4_2, HIGH);
}

void RECHTS()
{
	/////////////////////////////////////////////
	//DC-Motorpaar 1 - Links
	digitalWrite(controlInput1_1, LOW);
	digitalWrite(controlInput1_2, HIGH);
	digitalWrite(enable1_1, HIGH);

	//DC-Motorpaar 1 - Rechts
	digitalWrite(controlInput1_3, HIGH);
	digitalWrite(controlInput1_4, LOW);
	digitalWrite(enable1_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 2 - Links
	digitalWrite(controlInput2_1, LOW);
	digitalWrite(controlInput2_2, HIGH);
	digitalWrite(enable2_1, HIGH);

	//DC-Motorpaar 2 - Rechts
	digitalWrite(controlInput2_3, HIGH);
	digitalWrite(controlInput2_4, LOW);
	digitalWrite(enable2_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 3 - Links
	digitalWrite(controlInput3_1, LOW);
	digitalWrite(controlInput3_2, HIGH);
	digitalWrite(enable3_1, HIGH);

	//DC-Motorpaar 3 - Rechts
	digitalWrite(controlInput3_3, HIGH);
	digitalWrite(controlInput3_4, LOW);
	digitalWrite(enable3_2, HIGH);

	/////////////////////////////////////////////
	//DC-Motorpaar 4 - Links
	digitalWrite(controlInput4_1, LOW);
	digitalWrite(controlInput4_2, HIGH);
	digitalWrite(enable4_1, HIGH);

	//DC-Motorpaar 4 - Rechts
	digitalWrite(controlInput4_3, HIGH);
	digitalWrite(controlInput4_4, LOW);
	digitalWrite(enable4_2, HIGH);
}

void STOPP_SYS()
{
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
	
}