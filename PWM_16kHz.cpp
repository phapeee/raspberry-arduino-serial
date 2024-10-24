#include "PWM_16kHz.h"
#include <Arduino.h>

namespace PWM{

#define FAST_PWM__A             (0x03)  // select bit for Waveform Generation Mode in Timer/Counter1 Control Register A
#define COMA__NON_INVERT        (0x80)  // select bit for Compare Output Mode for Channel A (Clear OC0A on compare match when up-counting. Set OC0A on compare match when down counting.)
#define COMB__NON_INVERT        (0x20)  // select bit for Compare Output Mode for Channel B (same for B)
#define CSL__1                  (0x01)  // x1 prescalar for clock
#define TOV_ENABLE              (0x01)  // timer overflow enable bit
#define PWM_MAX_COUNT           (4)

char volatile preOCR2A;
char volatile preOCR2B;
char volatile PWM_count_2A;
char volatile PWM_count_2B;
char volatile PWM_count_2A_top;
char volatile PWM_count_2B_top;

void init_16kHz_PWM() {
    pinMode(PWM1A, OUTPUT);
    pinMode(PWM1B, OUTPUT);
    pinMode(PWM2A, OUTPUT);
    pinMode(PWM2B, OUTPUT);

    TCCR1A = (COMA__NON_INVERT | COMB__NON_INVERT | (1 << WGM11));     // Configure Fast PWM mode using ICR as TOP value and non-inverting output for OC1A.
    TCCR1B = CSL__1 | (1 << WGM12) | (1 << WGM13);   // set div = 1

    TCCR2A = (FAST_PWM__A | COMA__NON_INVERT | COMB__NON_INVERT);     // Configure Fast PWM mode using ICR as TOP value and non-inverting output for OC1A.
    TCCR2B = CSL__1;   // set div = 1 
    
    ICR1 = 1020;

    TIMSK2 = (1 << TOIE2);    // enable overflow for timer 2
    
    preOCR2A = 0;
    preOCR2B = 0;
    PWM_count_2A = 0;
    PWM_count_2B = 0;

    OCR2A = 0;
    OCR2B = 0;

}

void setDuty(unsigned int PIN, float duty) {
    float clipped_duty = min(100, max(0, duty));
    unsigned char count;
    unsigned char compare;
    if (PIN == PWM2A || PIN == PWM2B) {
        count = (unsigned char)clipped_duty / 25.0;
        compare = round((float)(clipped_duty - 25.0 * (float)count) * 10.24);
    }
    //Serial.print((unsigned int) count);
    //Serial.print(", ");
    //Serial.print((unsigned int) compare);
    //Serial.print(", ");
    //Serial.println((float)((float) count * 255.0 + (float) compare) / (255.0 * 4.0) * 100);
    switch (PIN) {
    case PWM1A:
        OCR1B = round(clipped_duty * 10.24);
        break;
    case PWM1B:
        OCR1A = round(clipped_duty * 10.24);
        break;
    case PWM2A:
        PWM_count_2A_top = count;
        preOCR2A = compare;
        break;
    case PWM2B:
        PWM_count_2B_top = count;
        preOCR2B = compare;
        break;
    default: break;
    }
}

ISR(TIMER2_OVF_vect) {
    if (PWM_count_2A >= PWM_MAX_COUNT) {PWM_count_2A = 0;}
    if (PWM_count_2B >= PWM_MAX_COUNT) {PWM_count_2B = 0;}
    if (PWM_count_2A == PWM_count_2A_top) OCR2A = preOCR2A;
    else if (PWM_count_2A < PWM_count_2A_top) OCR2A = 255;
    else if (PWM_count_2A > PWM_count_2A_top) OCR2A = 0;
    if (PWM_count_2B == PWM_count_2B_top) OCR2B = preOCR2B;
    else if (PWM_count_2B < PWM_count_2B_top) OCR2B = 255;
    else if (PWM_count_2B > PWM_count_2B_top) OCR2B = 0;
    PWM_count_2A++;
    PWM_count_2B++;
}

}