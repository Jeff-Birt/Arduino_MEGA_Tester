#pragma once

//PORTA bit           Ard Prt Pin 
#define DA0TODA7  0xFF
//	DA0				      PA0 #22 
//  DA1                   PA1 #23
//  DA2                   PA2 #24
//  DA3                   PA3 #25
//  DA4                   PA4 #26
//  DA5                   PA5 #27
//  DA6                   PA6 #28
//  DA7                   PA7 #29  

//PORTB bit           Ard Prt Pin 
#define CB0T0CB6  0xF7 
//	CB0					  PB0 #53 
//  CB1                   PB1 #52
//  CB2                   PB2 #51
//  CB3                   PB3 #50
//  CB4                   PB4 #10
//  CB5                   PB5 #11
//  CB6                   PB6 #12
//                        PB7 #13  

// PORTC bits         Ard Prt Pin
#define DB0T0DB6  0xFF 
//	DB0					  PC0 #37
//	DB1				      PC1 #36
//	DB2				      PC2 #35
//	DB3				      PC3 #34
//	DB4				      PC4 #33
//	DB5				      PC5 #32  
//  DB6                   PC6 #31
//	DB7			          PC7 #30

// PORTD bits       Ard Prt Pin
#define PRTD      0xFF 
//	SCL					  PD0 #21
//	SDA				      PD1 #20
//	RX1				      PD2 #19
//	TX1				      PD3 #18
//					      PD4
//					      PD5  
//                        PD6
//				          PD7

// PORTF bits       Ard Prt Pin
#define PRTF      0xFF 
//	KEYPAD0				  PF0 #A0
//	KEYPAD1				  PF1 #A1
//	KEYPAD2				  PF2 #A2
//	    				  PF3 #A3
//					      PF4 #A4
//					      PF5 #A5
//                        PF6 #A6
//				          PF7 #A7

// PORTH bits       Ard Prt Pin
#define PRTH      0xFF 
//	CA2					  PH0 16
//	CA3				      PH1 17
//					      PH2 
//	     				  PH3 
//					      PH4
//	DUT_PWR5		      PH5 8
//  DUT_PWR12             PH6 9
//				          PH7

// PORTK bits         Ard Prt Pin
#define PRTK      0xFF 
//	AA0					  PK0 #A8
//	AA1				      PK1 #A9
//	AA2				      PK2 #A10
//	AA3    				  PK3 #A11
//	AA4				      PK4 #A12
//	AA5     		      PK5 #A13
//  AA6                   PK6 #A14
//	AA7 		          PK7 #A15

// PORTL bits         Ard Prt Pin
#define PRTL      0xFF 
//	DC0					  PK0 #49
//	DC1				      PK1 #48
//	DC2				      PK2 #47
//	DC3    				  PK3 #46
//	DC4				      PK4 #45
//	DC5     		      PK5 #44
//  DC6                   PK6 #43
//	DC7 		          PK7 #42

//PORTL bit         Ard Prt Pin  DRAM
#define DOUT    0x01 // PL0 #49  #14
 
// to set pins to HIZ set DDRx bits to zero and set corresponding PORTx pin low
void initTest()
{
  DDRA = DDRA | A0TOA7;
  DDRC = DDRC | A8;
  DDRC = DDRC | DIN | RAS | CAS | WE | GRN_LED | DUT_PWR | BLU_LED; // outputs
  DDRL = DDRL & ~DOUT; // input

  PORTC = PORTC | RAS | CAS | WE;  // set HIGH
  PORTC = PORTC & ~(GRN_LED | BLU_LED); // turn off LEDs
  PORTC = PORTC & ~DUT_PWR; // turn ON +5V to DUT
}

// For HIZ set DDRx bits to zero and set corresponding PORTx pins low
void initStandby()
{
  DDRA = DDRA & ~A0TOA7;
  DDRC = DDRC & ~A8;
  DDRC = DDRC & ~(DIN | RAS | CAS | WE);
  DDRL = DDRL & ~DOUT;

  PORTA = PORTA & ~A0TOA7;
  PORTC = PORTC & ~A8;
  PORTC = PORTC | DUT_PWR; // turn OFF +5V to DUT
  PORTC = PORTC & ~(DIN | RAS | CAS | WE);
  PORTL = PORTL & ~DOUT;
}

inline void setDIN(byte pattern, byte bitMask)
{
  PORTC = (PORTC & ~DIN) | ( ((pattern & bitMask)>0) ? DIN : 0); // clear DIN bit, conditinally set
}

inline void setCol(int col)
{
  PORTA = (byte)col;    // Write out COL address
  PORTC = (PORTC & ~A8) | (col >> 8); // not using rest of PORTC only bit0 
}

inline void setRow(int row)
{
  PORTA = (byte)row;    // 
  PORTC = (PORTC & ~A8) | (row >> 8); // not using rest of PORTC only bit0
}

inline void resetCAS()
{
  PORTC = PORTC | CAS;  // Set CAS HIGH
}

inline void setCAS()
{
  PORTC = PORTC & ~CAS; // Set CAS LOW
}

inline void setRAS()
{
  PORTC = PORTC & ~RAS; // set RAS low
}

inline void resetRAS()
{
  PORTC = PORTC | RAS;  // Set RAS HIGH
}

inline void setWE()
{
  PORTC = PORTC & ~WE;  // Set WE low for write
}

inline void resetWE()
{
  PORTC = PORTC | WE;   // Set WE high to complete write
}

inline bool readBit()
{
  return ((PINL & DOUT) != 0);
}

inline void refreshRow(int row)
{
    PORTA = (byte)row;      // & 0xFF implicit
    PORTC = (PORTC & ~A8) | (row >> 8); // not using rest of PORTC only bit0
    PORTC = PORTC & ~RAS; // set RAS low
    PORTC = PORTC | RAS;  // set RAS high
}

inline void ledOFF()
{
  PORTC = PORTC & ~GRN_LED; // turn off grn LED
}

inline void ledON()
{
  PORTC = PORTC | GRN_LED; // turn off grn LED
}

inline void ledToggle()
{
  PORTC = PORTC ^ GRN_LED; // toggle grn LED
}
