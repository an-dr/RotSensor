#include "RotSensor.h"
#include <Arduino.h>


int left_encoder_pin = 2;  // pulse output from the module
int right_encoder_pin = 3; // pulse output from the module

/**** For printf ****/
int getChar(FILE *fp) {
    while (!(Serial.available()))
        ;
    return (Serial.read());
}

int putChar(char c, FILE *fp) {
    if (c == '\n') {
        putChar((char)'\r', fp);
    }
    Serial.write(c);
    return 0;
}
/* For printf <- */


void setup() {
    //  printf:
    Serial.begin(9600);
    fdevopen(putChar, getChar);
    // encoders:
    RotSensor rs_l(left_encoder_pin, "Left", millis);
    RotSensor rs_r(right_encoder_pin, "Right", millis);
    attachInterrupt(digitalPinToInterrupt(rs_l.GetPin()), rs_l.GetIntrHandler(), FALLING);
    attachInterrupt(digitalPinToInterrupt(rs_r.GetPin()), rs_r.GetIntrHandler(), FALLING);
}

void loop() {
}
