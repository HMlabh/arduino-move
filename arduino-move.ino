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


	//CAN
	uint8_t can_int = 19;	//Interrupt pin
	uint8_t can_cs = 53;		//Chipselect pin

}

//---------------------CAN ----------------------------------
MCP_CAN CAN0(pin::can_cs);//CS-Pin des CAN-Moduls
byte can_send_msg[8] = {0};
byte can_read_msg[8] = {0};
long unsigned int can_read_id;
unsigned char can_read_length = 0;
long unsigned int can_send_id;
unsigned char can_send_length = 0;

//IDs:
long unsigned int can_id_command = 0x040;
long unsigned int can_id_response = 0x041;

//commands
byte can_com_stop = 0;			//
byte can_com_setspeed_mt01 = 1;	//
byte can_com_setspeed_mt23 = 2;	//
byte can_com_setspeed_mt45 = 3;	//
byte can_com_setspeed_mt67 = 4;	//

byte can_com_ping = 10;			//
byte can_com_ack_on = 11;		//
byte can_com_ack_off = 12;		//
byte can_com_ramp_on = 13;		//
byte can_com_ramp_off = 14;		//

byte can_com_set_rampdelay = 21;		//

byte can_com_get_status = 30;	//
byte can_com_get_current = 31;	//

byte can_com_selftest = 0;		//

byte can_com_test = 255;			//

//responses
byte can_res_error = 0;			//

byte can_res_status1 = 1;		//sendet Status von Motor 0 bis 3
byte can_res_status2 = 2;		//sendet Status von Motor 4 bis 7
byte can_res_current1 = 11;		//sendet Strom von Motor 0 bis 3
byte can_res_current2 = 12;		//sendet Strom von Motor 4 bis 7

byte can_res_ack = 255;			//


//sonstigte 
uint8_t status[8] = { 0 };
int8_t enableack = 0;
int8_t enableramp = 0;
int8_t error = 0;
int16_t rampdelay = 20;


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

	pinMode(pin::can_int, INPUT);// Configuring pin for /INT input


	CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ);
	delay(100);
	CAN0.setMode(MCP_NORMAL);

	
}

//-------Funktionen-------
void testit()
{

	//reply message 
	can_send_length = can_read_length;
	for (int i = 0; i < can_read_length; i++)
	{
		can_send_msg[i] = can_read_msg[i] + 1;
	}
	CAN0.sendMsgBuf(0x21, 0, can_send_length, can_send_msg);

	//Aktiviere alle Treiber
	for (int i = 0; i <= 3; i++)
	{
		enabledriver(i);
	}
	
	sendstatus();
	sendcurrent();
	setramp(0, 20, 255, 5);
	sendstatus();
	sendcurrent();
	delay(1000);
	setramp(0, 255, 20, 5);

	sendstatus();
	setramp(0, -20, -255, 5);
	sendstatus();
	delay(1000);
	setramp(0, -255, -20, 5);
	delay(1000);

	stopall();
	

	
}


//stopall
void stopall()
{
	for (int i = 0; i <= 7; i++)
	{
		digitalWrite(pin::dir1[i], LOW);
		digitalWrite(pin::dir2[i], LOW);
		analogWrite(pin::pwm[i], 0);
	}
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

void cansend()
{
	CAN0.sendMsgBuf(can_send_id, 0, can_send_length, can_send_msg);
}

//sendstatus
void sendstatus()
{
	//erste Status Nachticht (Motor 0 bis 3)
	can_send_id = can_id_response;
	can_send_length = 5;
	can_send_msg[0] = can_res_status1;

	can_send_msg[1] = digitalRead(pin::m0_sf);
	can_send_msg[2] = digitalRead(pin::m1_sf);
	can_send_msg[3] = digitalRead(pin::m2_sf);
	can_send_msg[4] = digitalRead(pin::m3_sf);
	cansend();//sende erste nachricht

	//zweite Status Nachticht (Motor 4 bis 7)
	can_send_msg[0] = can_res_status2;

	can_send_msg[1] = digitalRead(pin::m4_sf);
	can_send_msg[2] = digitalRead(pin::m5_sf);
	can_send_msg[3] = digitalRead(pin::m6_sf);
	can_send_msg[4] = digitalRead(pin::m7_sf);
	cansend();//sende zweite nachricht
}

//sendcurrent
void sendcurrent()
{
	//erste Status Nachticht (Motor 0 bis 3)
	can_send_id = can_id_response;
	can_send_length = 5;
	can_send_msg[0] = can_res_current1;

	can_send_msg[1] = analogRead(pin::m0_fb) / 4;
	can_send_msg[2] = analogRead(pin::m1_fb) / 4;
	can_send_msg[3] = analogRead(pin::m2_fb) / 4;
	can_send_msg[4] = analogRead(pin::m3_fb) / 4;
	cansend();//sende erste nachricht

	//zweite Status Nachticht (Motor 4 bis 7)
	can_send_msg[0] = can_res_current2;

	can_send_msg[1] = analogRead(pin::m4_fb) / 4;
	can_send_msg[2] = analogRead(pin::m5_fb) / 4;
	can_send_msg[3] = analogRead(pin::m6_fb) / 4;
	can_send_msg[4] = analogRead(pin::m7_fb) / 4;
	cansend();//sende zweite nachricht
}

void sendack()
{
	can_send_id = can_id_response;
	can_send_length = 1;
	can_send_msg[0] = can_res_ack;
	cansend();
}

void selftest()
{
	//TODO
	delay(10);
}

void loop()
{

	

	if (!digitalRead(pin::can_int))// If CAN0_INT pin is low, read receive buffer
	{
		CAN0.readMsgBuf(&can_read_id, &can_read_length, can_read_msg);// Read data: len = data length, buf = data byte(s)

		//ID = 40?
		if (can_read_id == can_id_command)
		{
			//Befehl : STOP
			if (can_read_msg[0] == can_com_stop)
			{
				if (enableack) sendack();
				stopall();
			}
			
			//Befehl : Steppe Motorgeschwindigkeit Motor 0 und 1
			else if (can_read_msg[0] == can_com_setspeed_mt01)
			{
				if (enableack) sendack();
				enabledriver(0);

				setspeed(0, ((int16_t)(can_read_msg[1]) << 8) | (int16_t)(can_read_msg[2]));
				setspeed(1, ((int16_t)(can_read_msg[3]) << 8) | (int16_t)(can_read_msg[4]));
			}

			//Befehl : Steppe Motorgeschwindigkeit Motor 2 und 3
			else if (can_read_msg[0] == can_com_setspeed_mt23)
			{
				if (enableack) sendack();
				enabledriver(1);

				setspeed(2, ((int16_t)(can_read_msg[1]) << 8) | (int16_t)(can_read_msg[2]));
				setspeed(3, ((int16_t)(can_read_msg[3]) << 8) | (int16_t)(can_read_msg[4]));
			}

			//Befehl : Steppe Motorgeschwindigkeit Motor 4 und 5
			else if (can_read_msg[0] == can_com_setspeed_mt45)
			{
				if (enableack) sendack();
				enabledriver(2);

				setspeed(4, ((int16_t)(can_read_msg[1]) << 8) | (int16_t)(can_read_msg[2]));
				setspeed(5, ((int16_t)(can_read_msg[3]) << 8) | (int16_t)(can_read_msg[4]));
			}

			//Befehl : Steppe Motorgeschwindigkeit Motor 6 und 7
			else if (can_read_msg[0] == can_com_setspeed_mt67)
			{
				if (enableack) sendack();
				enabledriver(3);

				setspeed(6, ((int16_t)(can_read_msg[1]) << 8) | (int16_t)(can_read_msg[2]));
				setspeed(7, ((int16_t)(can_read_msg[3]) << 8) | (int16_t)(can_read_msg[4]));
			}

			//Befehl : Ping (Anfrage nach einzelnem Ack)
			else if (can_read_msg[0] == can_com_ping)
			{
				sendack();
			}

			//Befehl : Ping (Anfrage nach einzelnem Ack)
			else if (can_read_msg[0] == can_com_ping)
			{
				sendack();
			}

			//Befehl : Ack on
			else if (can_read_msg[0] == can_com_ack_on)
			{
				sendack();
				enableack = 1;
			}

			//Befehl : Ack off
			else if (can_read_msg[0] == can_com_ack_off)
			{
				sendack();
				enableack = 0;
			}

			//Befehl : Ramp on
			else if (can_read_msg[0] == can_com_ramp_on	)
			{
				if (enableack) sendack();
				enableramp = 1;
			}

			//Befehl : Ramp off
			else if (can_read_msg[0] == can_com_ramp_off)
			{
				if (enableack) sendack();
				enableramp = 0;
			}

			//Befehl : Set Rampdelay
			else if (can_read_msg[0] == can_com_set_rampdelay)
			{
				if (enableack) sendack();
				rampdelay = ((int16_t)(can_read_msg[1]) << 8) | (int16_t)(can_read_msg[2]);
			}

			//Befehl : Get status
			else if (can_read_msg[0] == can_com_get_status)
			{
				sendstatus();
			}

			//Befehl : Get current
			else if (can_read_msg[0] == can_com_get_current)
			{
				sendcurrent();
			}

			//Befehl : Selftest
			else if (can_read_msg[0] == can_com_get_current)
			{
				if (enableack) sendack();
				selftest();
			}


			//Befehl : Test
			else if (can_read_msg[0] == can_com_test)
			{
				testit();
			}


			else {};
		}
		else{}

	}

}