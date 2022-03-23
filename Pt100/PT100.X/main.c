/*
 * File:   main.c
 * Author: Usuario
 *
 * Created on 19 de marzo de 2022, 12:26
 */

#include "configuracion.h"
#include "SPI_Library.h"
#include <xc.h>

#define SS


void main(void) {
    
    //OSCCON
    OSCCONbits.IRCF=0x07; // 8 MHz frecuencia de reloj
    OSCCONbits.IOFS=1; //Frequency stable
    OSCCONbits.SCS=0x02; //Internal block oscillator 
    
    //OSCTUNE
    OSCTUNEbits.TUN=00000; //Frecuencia centrada para ser usada en USART
    
    //RCON
    RCONbits.IPEN=0; //Interrupt priority disable
    
    SPI_Init_Master(SPI_Clock_4, MODO_1, DATO_Mitad);
    __delay_ms(100);
    
    while(1){
        
        SS = 0;
        SPI_Tx(0x01);
        __delay_ms(500);
        SPI_Tx(0x06);
        __delay_ms(500);
        SPI_Tx(0xff);
        __delay_ms(500);
        SS = 1;
        __delay_ms(1000);
    }
        
    }
    
}


