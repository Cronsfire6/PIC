// 'C' source line config statements

#define _XTAL_FREQ 4000000
// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB3      // CCP1 Pin Selection bit (CCP1 function on RB3)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define LED1 PORTBbits.RB4
#define LED2 PORTBbits.RB5
#define LED3 PORTBbits.RB6
#define LED4 PORTBbits.RB7

void __interrupt() ADC_ISR(void);
void inicio ( void );
int result;
int adc = 0;

void main(void) {
    
    inicio();
    ADRESH = 0x00;
    ADRESL = 0x00;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    ADCON0bits.CHS = 0b0000;
    GIE=1;
    ADON = 1;
    
    
    while(1){
        if ((result >= 0)&&(result < 205)){
            // 0-1 V
            LED1 = 0;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 205)&&(result < 409)){
            // 1-2 V
            LED1 = 1;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 409)&&(result < 614)){
            // 2-3 V
            LED1 = 1;   LED2 = 1;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 614)&&(result < 818)){
            // 3-4 V
            LED1 = 1;   LED2 = 1;   LED3 = 1;   LED4 = 0;
        }
        else if ((result >= 818)&&(result <= 1023)){
            // 4-5 V
            LED1 = 1;   LED2 = 1;   LED3 = 1;   LED4 = 1;
        }
        else{
            LED1 = 0;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
    }
    
    return;
}

void inicio ( void ){
    
    //OPTION_REG
    nRBPU = 1;
    INTEDG = 1;
    T0CS = 0;
    T0SE = 0;
    PSA = 0;
    PS0 = 1; 
    PS1 = 1; 
    PS2 = 1; 
    
    //INTCON
    GIE = 0;
    PEIE = 1;
    TMR0IE = 0;
    INT0IE = 1;
    RBIE = 0;
    TMR0IF = 0;
    INT0IF = 0;
    RBIF = 0;
    
    //PIE1
    ADIE = 1; 
    RCIE = 0;
    TXIE = 0;
    SSPIE = 0;
    CCP1IE = 0;
    TMR2IE = 0;
    TMR1IE = 0;
    
    //PIR1
    ADIF = 0;
    
    //PIE2
    
    //OSCTUNE
    
    TUN0 = 0;
    TUN1 = 0;
    TUN2 = 0;
    TUN3 = 0;
    TUN4 = 0;
    TUN5 = 0;
    
    //OSCCON
   OSCCONbits.IRCF = 0b0111; //8 MHz de clock interno
   OSTS = 1;
   IOFS = 1;
   SCS0 = 0;
   SCS1 = 0;
   
   //ANSEL
   ANSEL = 0x0F;//RA0 - RA3 Entradas analogicas
   
   //ADCON0
   ADCS0 = 1; //F/32 para la frecuencia de conversion 
   ADCS1 = 0;
   ADCON0bits.GO_nDONE = 1;
   ADON = 0;
   
   //ADCON1
   ADFM = 1;//Right justified
   ADCS2 = 0; // no se divide por 2 la frecuencia de conversion
   VCFG0 = 0;//VSS Y VDD para conversion 
   VCFG1 = 0;
   
   //TRISA
   TRISA = 0x2F;
   
   //TRISB
   TRISB = 0x01;
    
}

void __interrupt() ADC_INTB0(void){
    
    if(ADIF && ADIE){
        result = ((ADRESH << 8) | ADRESL);
        PIR1bits.ADIF = 0;
        ADCON0bits.GO_nDONE = 1;
    }
    if(INT0IE && INT0IF){
        INT0IF = 0;
        adc++;
        if(adc==4){
            adc=0;
        }
        switch(adc){
            case 0:
            ADCON0bits.CHS = 0b0000;
            break;
            case 1:
            ADCON0bits.CHS = 0b0001;
            break;
            case 2:
            ADCON0bits.CHS = 0b0010;
            break;
            case 3:
            ADCON0bits.CHS = 0b0011;
            break;
        }
        __delay_us(3);
        
    }
}