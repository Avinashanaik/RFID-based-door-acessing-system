



#include <p18f452.h>
#include <delays.h>
#include<string.h>
#include <stdio.h>               /* prototype declarations for I/O functions */	 
#pragma config OSC=HS   
int i;
#define rs PORTDbits.RD5 /* PORT for RS */
#define rw PORTDbits.RD6 /* PORT for RW */
#define en PORTDbits.RD7 /* PORT for E */
#define motor_pin_1 PORTBbits.RB0
#define motor_pin_2 PORTBbits.RB1
#define ldata PORTD
void lcd_data(unsigned int);
void lcd_cmd(unsigned int);
void lcd_init(void);
void One_Second_Delay(void);
unsigned char data1[]="Access Accepted" ;
unsigned char data2[]="Access   denied" ;
void recieve(void);
unsigned char message[];
unsigned char count; 
unsigned char card_id1[]="05747801"; 
unsigned char card_id2[]="05726401"; 
unsigned char card_id3[]="05742248"; 
unsigned char card_id4[]="05742951";
void servo(); 
void delay(void)
       {
        unsigned char i;
        for(i=0;i<250;i++); 
	}

void One_Second_Delay( )
{
Delay10KTCYx(100);
}

unsigned int j;
void lcd_cmd(unsigned int cmd)
{
ldata=cmd >> 4;
en = 1;
en = 0;
ldata=cmd &0x0f;
en = 1;
en = 0;
Delay10KTCYx(5);
}
void lcd_init(void)
{
en = 0;
rs = 0;
rw = 0;
lcd_cmd(0b00000010);// 02H
lcd_cmd(0b00000001);//01H
lcd_cmd(0b00001100);//0AH
lcd_cmd(0b00101000);//28H
}
//4-bit print interface
void lcd_data(unsigned int character)
{
ldata=character >> 4;
rs = 1;
en = 1;
en = 0;
rs = 0;
ldata=character & 0x0f;
rs = 1;
en = 1;
en = 0;
rs = 0;
Delay10KTCYx(5);
}
//4-bit instruction interface

void MSDelay( int itime)
  {
    unsigned int i, j;
    for(i=0;i<itime;i++)
      for(j=0;j<135;j++);
  }


void recieve(void) 				// serial receive function
{
unsigned char i;
			for(i=0;i<=7;i++)
             {
           message[i]=0x00; 
              }
for(i=0;i<=7;i++)
             {
           	while(PIR1bits.RCIF==0)
              {
              }
message[i]=RCREG;                
              }	

}
void motor()

{motor_pin_1=1;
motor_pin_2=0;//roatates anticlockwise
MSDelay(1000);
motor_pin_1 = 0;
motor_pin_1 = 0; //stops
 One_Second_Delay( );
 One_Second_Delay( );
MSDelay(1000);
motor_pin_1 = 0;
motor_pin_2 = 1; // clockwise
MSDelay(1000);
motor_pin_1 = 0;
motor_pin_2 = 0; //stops
MSDelay(1000);

}




	
void main()
{

	int i;
	char a[]="CARD ID  ";
	TXSTA=0x20;		// low baud, 8bit mode
	RCSTA=0x90;		//enable serial port and receiver
	SPBRG=32;		//9600 baud @20MHz
	TXSTAbits.TXEN=1;	//enable transmitter
	RCSTAbits.SPEN=1;	//enable serial comm
	TRISD=0x00;
PORTBbits.RB0=0;
PORTBbits.RB1=0;
TRISBbits.TRISB0=0;
TRISBbits.TRISB1=0;
    TRISEbits.TRISE0=0;    
	TRISCbits.TRISC7 = 1;// rx input
	TRISCbits.TRISC0 = 0;
	TRISCbits.TRISC1 = 0;
	RCREG=0x00;	
	lcd_init();	
    while(1)
    {
//lcd_cmd(0x01);
delay();
lcd_cmd(0x82);        //Place cursor to second position of first line 
for(i=0;a[i]!='\0';i++)
lcd_data(a[i]);
Delay10KTCYx(500);

One_Second_Delay( );One_Second_Delay( );One_Second_Delay( );

//lcd_cmd(0xC0);   //Place cursor to second position of second line
recieve();
for(i=0;i<=7;i++ )
{ 
lcd_data(message[i]);				
}
Delay10KTCYx(500);  
 if(message[0] == '0' && message[1] == '5' && message[2] == '7' && message[3] == '4' && message[4] == '7'&& message[5] == '8' && message[6] == '0'&& message[7] == '1') //05747801
 
{ 
lcd_cmd(0Xc3);
for(i=0;i<=15;i++)
{
lcd_data(data1[i]); // Call lcddata function to send character one by from 'data' array


} 
motor();
}
else if(message[0] == '0' && message[1] == '5' && message[2] == '7' && message[3] == '2' && message[4] == '6'&& message[5] == '4' && message[6] == '0'&& message[7] == '1') //05726401
{                    //open the door
lcd_cmd(0Xc3);
for(i=0;i<=15;i++)
{
lcd_data(data1[i]); // Call lcddata function to send character one by from 'data' array

 
}
motor();			
} 
else if(message[0] == '0' && message[1] == '5' && message[2] == '7' && message[3] == '4' && message[4] == '2'&& message[5] == '2' && message[6] == '4'&& message[7] == '8') //05742248
{                    //open the door
lcd_cmd(0Xc3);
for(i=0;i<=15;i++)
{
lcd_data(data1[i]); // Call lcddata function to send character one by from 'data' array


} 
 motor();
}
 
else if(message[0] == '0' && message[1] == '5' && message[2] == '7' && message[3] == '4' && message[4] == '2'&& message[5] == '9' && message[6] == '5'&& message[7] == '1') //05742951 
{                //open the door
lcd_cmd(0Xc3);
for(i=0;i<=15;i++)
{
lcd_data(data1[i]); // Call lcddata function to send character one by from 'data' array

 
} 
motor();
} 
else
{lcd_cmd(0Xc3);
for(i=0;i<=15;i++)
{
lcd_data(data2[i]); // Call lcddata function to send character one by from 'data' array

}

}
for(i=0;i<3;i++)
{
One_Second_Delay( );
}
lcd_cmd(0x01);
} 
}







