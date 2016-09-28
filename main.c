#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"
#include "FIFO.h"
#include <avr/interrupt.h>
#include "USART.h"

uint8_t buffer[16]={0};
uint8_t i=0;
void LCD_Puts(char *s);
void menu();
void cmd();

int main(){

    LCD_init();

    USART_Init(MYUBRR);

    uint8_t tmp;
    sei();
    menu();

    while(1){

        if(has_sen()){
            USART_get_sen(buffer);
            LCD_Puts(buffer);
            cmd();
        }
    }


    return 0;
}

void LCD_Puts(char *s){
	while(*s && (*s!=13)){
		LCD_data(*s);
		s++;
	}

}

void menu(){

    USART_Transmit(12);
    USART_Transmit_Puts("");
    USART_Transmit_Puts("****MENU****");
    USART_Transmit_Puts("");        //only /enter
    USART_Transmit_Puts("1. first");
    USART_Transmit_Puts("2. second");
    USART_Transmit_Puts("3. third");
    USART_Transmit_Puts("4. fourth");
    USART_Transmit_Puts("5. help");
    USART_Transmit('>');
}

void cmd(){
    uint8_t element=0;
    USART_Transmit(12);

    if(!(strcmp(buffer,"first"))    || (!(strcmp(buffer,"1"))))     {element = 1;}
    if(!(strcmp(buffer,"second"))   || (!(strcmp(buffer,"2"))))     {element = 2;}
    if(!(strcmp(buffer,"third"))    || (!(strcmp(buffer,"3"))))     {element = 3;}
    if(!(strcmp(buffer,"fourth"))   || (!(strcmp(buffer,"4"))))     {element = 4;}
    if(!(strcmp(buffer,"help"))     || (!(strcmp(buffer,"h"))))     {element = 5;}

    switch(element){
    case 1:USART_Transmit_Puts(" detected->1"); break;
    case 2:USART_Transmit_Puts(" detected->2"); break;
    case 3:USART_Transmit_Puts(" detected->3"); break;
    case 4:USART_Transmit_Puts(" detected->4"); break;
    case 5:USART_Transmit_Puts(" detected->help"); menu(); break;
    default:USART_Transmit_Puts(" undetected->error");break;
    }
    USART_Transmit('>');
}

