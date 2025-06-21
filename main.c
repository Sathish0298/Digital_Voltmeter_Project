#include <xc.h>
#define _XTAL_FREQ 20000000

// Segment patterns
const unsigned char seg_no_dp[]  = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
const unsigned char seg_with_dp[]= {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};

// Digit control pins
#define digit1 PORTBbits.RB0
#define digit2 PORTBbits.RB1
#define digit3 PORTBbits.RB2
#define digit4 PORTBbits.RB3

unsigned char digit_vals[4]; // Holds segment values for each digit

void Analog_setting() {
    ADCON0 = 0x81;     // ADC ON, Channel 0
    ADCON1 = 0x0E;     // AN0 as analog input, rest digital
}

unsigned int Analog_read(unsigned char channel) {
    ADCON0 &= 0xC5;
    ADCON0 |= (channel << 3);
    __delay_ms(2);        // Acquisition delay
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    return (ADRESH << 2) | (ADRESL >> 6);
}

void update_display_digits(unsigned int mv) {
    unsigned int d1 = mv / 1000;
    unsigned int d2 = (mv / 100) % 10;
    unsigned int d3 = (mv / 10) % 10;
    unsigned int d4 = mv % 10;

    if (d1 == 0) {
        digit_vals[0] = 0x00;            // Blank 1st digit if leading zero
        digit_vals[1] = seg_with_dp[d2]; // Decimal point on second digit
        digit_vals[2] = seg_no_dp[d3];   // Tens
        digit_vals[3] = seg_no_dp[d4];   // Units
    } else {
        digit_vals[0] = seg_no_dp[d1];     // Thousands
        digit_vals[1] = seg_with_dp[d2];   // Hundreds with decimal
        digit_vals[2] = seg_no_dp[d3];     // Tens
        digit_vals[3] = seg_no_dp[d4];     // Units
    }
}

void refresh_display() {
    PORTD = digit_vals[0];
    digit1 = 0; __delay_us(300); digit1 = 1;

    PORTD = digit_vals[1];
    digit2 = 0; __delay_us(300); digit2 = 1;

    PORTD = digit_vals[2];
    digit3 = 0; __delay_us(300); digit3 = 1;

    PORTD = digit_vals[3];
    digit4 = 0; __delay_us(300); digit4 = 1;
}

void main(void) {
    TRISD = 0x00; PORTD = 0x00;
    TRISB = 0x00; PORTB = 0x0F;
    digit1 = digit2 = digit3 = digit4 = 1;

    Analog_setting();

    unsigned int adc_val = 0;
    unsigned long mv = 0;

    while (1) {
        adc_val = Analog_read(0);
        mv = ((unsigned long)adc_val * 5000UL + 511) / 1023;
        update_display_digits(mv);

        for (int i = 0; i < 30; i++) {
            refresh_display();
        }
    }
}