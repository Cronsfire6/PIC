#include "uart.h"

//==============================================================================
void uart_init(unsigned short baudrate) {
    TRISBbits.TRISB1 = 0x01; // RX Pin
    TRISBbits.TRISB2 = 0x01; // TX Pin
    TXSTAbits.BRGH = 1; //Asyncronous mode
    SPBRG = ((_XTAL_FREQ / 16) / baudrate) - 1;
    
    //1 - Enable USART (TXSTA Register)
    TXSTAbits.TXEN = 1; // Transmission enabled
    RCSTAbits.SPEN = 1; // Enable Serial Port
    
    //2 - Enable 8 bit, asynchronous continuous mode (TXSTA Register)
    TXSTAbits.TX9 = 0;  // 8-bit transmission
    RCSTAbits.RX9 = 0;  // 8-bit reception
    TXSTAbits.SYNC = 0; // Asynchronous mode
    RCSTAbits.CREN = 1; // Enable continuous receive mode (RCSTA Register)

    INTCONbits.GIE = 1; // Enable Global Interrupts
    INTCONbits.PEIE = 1; //Enable Peripheral Interrupts
}
//==============================================================================
void uart_send(unsigned char byte) {
    while(!PIR1bits.TXIF) {
        // Wait for last transmission finish
    }
    //Put data on TXREG register to send
    TXREG = byte;
}
//==============================================================================
void uart_send_string(const char* str) {
    while(!PIR1bits.TXIF) {
        // Wait for last transmission finish
    }
    //Put data on TXREG register to send
    while(*str)
        uart_send((unsigned char)*str++);
}
//==============================================================================
unsigned char uart_read(void) {
    /* 
     * If we have an overrun error, reset CREN register 
     * in order to clear OERR bit
     */
    if (RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    
    while(!PIR1bits.RCIF) {
        //Wait for reception 
    }
    // Read data from register RCREG
    unsigned char data = RCREG;
    
    return data;
}