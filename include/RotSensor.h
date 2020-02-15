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

#pragma once

#include <stdint.h>
#include <stdio.h>

#define ROTSENSOR_INSTANCES_MAX 8
#define DEBOUNCE_FILTER_MS 10

// #define LOG

typedef void IntHandler_t(void);

class RotSensor {
  private:
    int inst_no;
    uint8_t rs_pin;
    uint32_t counter;
    uint64_t last_intr_time;
    const char *name;
    unsigned long (*GetMillis)(void);
  public:
    static RotSensor *instances[ROTSENSOR_INSTANCES_MAX];
    static void intr_handler(int rs_num);
    static void intr0(void);
    static void intr1(void);
    static void intr2(void);
    static void intr3(void);
    static void intr4(void);
    static void intr5(void);
    static void intr6(void);
    static void intr7(void);

    bool direction_backward;

    RotSensor() = default;
    RotSensor(int pin,
              const char *name,
              unsigned long (*Millis)(void));
    uint32_t GetCounter(void);
    uint32_t GetPin(void);
    IntHandler_t * GetIntrHandler();
};
