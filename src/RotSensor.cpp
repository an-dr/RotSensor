// *************************************************************************
//
// Copyright (c) 2020 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "RotSensor.h"

RotSensor *RotSensor::instances[ROTSENSOR_INSTANCES_MAX] = {0};
RotSensor::RotSensor(int pin,
                     const char *name,
                     unsigned long (*Millis)(void)) : rs_pin(pin),
                                                      counter(0),
                                                      last_intr_time(0),
                                                      name(name),
                                                      GetMillis(Millis) {
    int i;
    for (i = 0; i < ROTSENSOR_INSTANCES_MAX; i++) {
        if (RotSensor::instances[i] == NULL) {
            instances[i] = this;
            this->inst_no = i;
            break;
        }
        if (i == ROTSENSOR_INSTANCES_MAX) {
#ifdef LOG
            printf("Error: out of ROTSENSOR_INSTANCES_MAX\n");
#endif
        }
    }
#ifdef LOG
    printf("Set instance : %d\n", i);
#endif
}

uint32_t RotSensor::GetPin(void) {
    return this->rs_pin;
}

uint32_t RotSensor::GetCounter(void) {
    return this->counter;
}

IntHandler_t *RotSensor::GetIntrHandler() {
#ifdef LOG
    printf("Got intr for an instanse no %d\n", this->inst_no);
#endif
    switch (this->inst_no) {
    case 0:
        return RotSensor::intr0;
    case 1:
        return RotSensor::intr1;
    case 2:
        return RotSensor::intr2;
    case 3:
        return RotSensor::intr3;
    case 4:
        return RotSensor::intr4;
    case 5:
        return RotSensor::intr5;
    case 6:
        return RotSensor::intr6;
    case 7:
        return RotSensor::intr7;
    default:
        return NULL;
    }
}

void RotSensor::intr_handler(int rs_num) {
    RotSensor *rs = RotSensor::instances[rs_num];
    if (rs != NULL) {
        unsigned long now = rs->GetMillis();
        // If interrupts come faster than debounce_filter_ms, assume it's a bounce and ignore
        if (now - rs->last_intr_time > DEBOUNCE_FILTER_MS) {
            rs->direction_backward ? rs->counter-- : rs->counter++;
#       ifdef LOG
            printf("[RS] %s : %lu\n", rs->name, rs->counter);
#       endif
        }
        rs->last_intr_time = now;
    }
}

void RotSensor::intr0(void) {
    intr_handler(0);
}
void RotSensor::intr1(void) {
    intr_handler(1);
}
void RotSensor::intr2(void) {
    intr_handler(2);
}
void RotSensor::intr3(void) {
    intr_handler(3);
}
void RotSensor::intr4(void) {
    intr_handler(4);
}
void RotSensor::intr5(void) {
    intr_handler(5);
}
void RotSensor::intr6(void) {
    intr_handler(6);
}
void RotSensor::intr7(void) {
    intr_handler(7);
}