#include "lcd.h"

/*wcom(0xC0);
	wdat('A');
	wcom(0x80);
	char revo [9] = {'R','e','f','e','r','e','n','c','e'};
	for(int i = 0; i < 10; i++)
		wdat(revo[i]);
	for(int i=0;i<0xFFFF;i++);//Delay*/
//Create a function called "delay"
void delay(void){
	int i;//Create a variable
	for(i=0;i<65;i++);//The "for" loop create a delay as 162.5 us.
}

//Configure the communication between LCD and the board.
void wcom(char dato){
	GPIOA->ODR &=~0x3;//A1 y A0. OFF (HIGH) RS & EN
	GPIOA->ODR =(dato&0x3C)|(GPIOA->ODR&0x3);//A5, A4, A3 and A2.
	GPIOA->ODR |=0x2;//A1 Enable port. EN off
	delay();//162.5 us.
	GPIOA->ODR &=~0xE;//A1 Disable port. EN on
	GPIOA->ODR =(dato<<2&0x3C)|(GPIOA->ODR&0x3);//A5, A4, A3 and A2.
	GPIOA->ODR |=0x2;//A1 Enable port. EN off
	delay();//162.25 us
	GPIOA->ODR &=~0xE;//A1 Disable port. EN on
}

//Transfer the information at LCD.
void wdat(char dato){
	GPIOA->ODR &=~0xE;//A1 Enable port.
	GPIOA->ODR |=0x1;//A0 RS port.
	GPIOA->ODR =(dato&0x3C)|(GPIOA->ODR&0x3);//A5, A4, A3 and A2.
	GPIOA->ODR |=0x2;//A1 Enable port.
	delay();//162.25 us.
	GPIOA->ODR &=~0x2;//A1 Enable port.
	GPIOA->ODR =(dato<<2&0x3C)|(GPIOA->ODR&0x3);//A5, A4, A3 and A2.
	GPIOA->ODR |=0x2;//A1 Enable port.
	delay();//162.25 us
	GPIOA->ODR &=~0x2;//A1 Enable port.
}

void init_lcd(void){
	int i;
	GPIOA->ODR = 0;
	for(i=0;i<64000;i++);//Create a delay of 160 mS.
	wcom(0x32);
	for(i=0;i<16000;i++);//Create a delay of 40 mS.
	wcom(0x28);
	for(i=0;i<32000;i++);//Create a delay of 80 mS.
	wcom(0x28);
	for(i=0;i<16000;i++);//Create a delay of 40 mS.
	wcom(0x0C); //ON command.
	for(i=0;i<16000;i++);//Create a delay of 16000 clock cycles.
	wcom(0x01); // CLEAR command.
	for(i=0;i<16000;i++);//Create a delay of 16000 clock cycles.
	wcom(0x06); //ENTRY MODE SET command.
}

void rev(int ref){
	wdat((char)(ref/(100))+'0');
	ref%=(100);//15
	wdat((char)(ref/(10))+'0');
	ref%=(10);//5
	wdat((char)(ref%10)+'0');
	for(int i=0;i<0xFFFF;i++);//Delay
}



