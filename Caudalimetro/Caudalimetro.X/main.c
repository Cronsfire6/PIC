// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000

#include <xc.h>

int count = 0, count_2 = 0;
//PIC/Include path add
void inicio( void );

void main(void) {
    
    inicio();
    PORTBbits.RB1=0;
    PORTBbits.RB2=0;
    PORTBbits.RB3=0;
    while(1){
    }
    return;
}

void inicio ( void ){
    
    //OPTION_REG
    
    nRBPU = 1;
    INTEDG = 1;// int flanco ascendente
    T0CS = 1; //Extern fuente de clock
    T0SE = 0; // low to high increment
    PSA = 0; //TMR0 prescaler  
    PS0 = 0; // 
    PS1 = 0; //0 prescaler
    PS2 = 0; //
    
    //INTCON 
    
    PEIE = 1; //Enable Peripheral interrupt
    T0IE = 1; //TM0 interrupt enable
    INTE = 1; //External interrupt enable
    T0IF = 0;
    INTF = 0;
    
    //PIE1
    
    CCP1IE = 0;
    TMR1IE = 1; // Enable Interrupt TMR1
    
    //PIR1
    
    TMR1IF = 0; //Interrupcion por TMR1 enabled
    
    //T1CON
    T1CKPS0 = 1;//Prescaler 8 TMR1
    T1CKPS1 = 1; 
    T1OSCEN = 0; //
    TMR1CS = 0;//Internal clock source (FOSC/4) Timer mode
    TMR1ON = 1;//Habilitacion de timer 1
    
    //PCON
    OSCF = 1; //Oscilador 4 MHz
    
    //CMCON
    CM0 = 1;
    CM1 = 1;//Comparators Off
    CM2 = 1; 
    
    //TRISA
    TRISA = 0b00110000; //RA5 MCLR - RA4 Input clock TMR0
    TRISB = 0b00000001; //RB0 input INT
    
    GIE = 1;
    
}

void __interrupt() ISR ( void ){
    
    if( TMR1IE && TMR1IF ){
        
        TMR1IF = 0;
        count++;
        if(count == 2){
            count = 0;
            PORTBbits.RB1=~PORTBbits.RB1;  
        }
        
    }
    if( T0IE && T0IF){
        
        T0IF = 0;
        count_2++;
        if(count_2 == 1){
            count_2 = 0;
            PORTBbits.RB2=~PORTBbits.RB2;
        }
        
    }
    
    if( INTE && INTF ){
        
        INTF = 0;
        PORTBbits.RB3=~PORTBbits.RB3;
        
    }
    
}
