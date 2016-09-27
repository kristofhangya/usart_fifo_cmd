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

uint8_t buffer[8]={0};
uint8_t i=0;
void LCD_Puts(char *s);
void menu();

int main(){
    _delay_ms(500);
    _delay_ms(500);
    _delay_ms(500);

    LCD_init();

    USART_Init(MYUBRR);

    uint8_t tmp;
    sei();

    menu();

    while(1){
        if(has_sen()){

            USART_get_sen(buffer);

            LCD_Puts(buffer);

            USART_Transmit(12);
            if(!(strcmp(buffer,"elso")))     {USART_Transmit_Puts(" azonositva->1");}
            if(!(strcmp(buffer,"masodik")))  {USART_Transmit_Puts(" azonositva->2");}
            if(!(strcmp(buffer,"harmadik"))) {USART_Transmit_Puts(" azonositva->3");}
            if(!(strcmp(buffer,"negyedik"))) {USART_Transmit_Puts(" azonositva->4");}
            if(!(strcmp(buffer,"help")))     {USART_Transmit_Puts(" azonositva->help");menu();}

            USART_Transmit('>');
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

    USART_Transmit_Puts("MENU");
    USART_Transmit_Puts("");
    USART_Transmit_Puts("1. elso");
    USART_Transmit_Puts("2. masodik");
    USART_Transmit_Puts("3. harmadik");
    USART_Transmit_Puts("4. negyedik");
    USART_Transmit_Puts("5. help");
}



