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

