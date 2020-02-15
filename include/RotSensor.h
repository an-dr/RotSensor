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

#include "to_implement.h"
#include <Arduino.h>
#include <stdint.h>

#define ROTSENSOR_INSTANCES_MAX 8
#define DEBOUNCE_FILTER_MS 10

class RotSensor {
  public:
    RotSensor() = default;
    RotSensor(int pin,
              const char *name,
              unsigned long (*Millis)(void),
              int (*PrintState)(const char *msg));
            //   void (*IntrHdlr)(void))
    static void * instances[ROTSENSOR_INSTANCES_MAX];
    static uint32_t instances_count;
    uint32_t instance_num;
    uint8_t rs_pin;
    uint32_t counter;
    uint64_t last_intr_time;
    const char *name;
    unsigned long (*GetMillis)(void);
    int (*PrintState)(const char *msg);
    // void (*RotSensor_InterruptionHandler)();

    bool direction_backward;
    // void Start(int pin,
    //            const char *name,
    //            unsigned long (*Millis)(void),
    //            int (*PrintState)(const char *msg),
    //            void (*IntrHdlr)(void));
    uint32_t GetCounter();
    static void PlaceMeToYourIntHandler(RotSensor *rs);
};
