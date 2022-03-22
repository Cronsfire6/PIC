/*
 * File:   main.c
 * Author: Usuario
 *
 * Created on 19 de marzo de 2022, 12:26
 */

#include "configuracion.h"


void main(void) {
    
    //OSCCON
    OSCCONbits.IRCF=111; // 8 MHz frecuencia de reloj
    OSCCONbits.IOFS=1; //Frequency stable
    OSCCONbits.SCS=10; //Internal block oscillator 
    
    //OSCTUNE
    OSCTUNEbits.TUN=00000; //Frecuencia centrada para ser usada en USART
    
    //RCON
    RCONbits.IPEN=0; //Interrupt priority disable
    
    while(1);
    
}


