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

extern bool RotSensor_Init(RotSensor *rs);

uint32_t RotSensor::instances_count = 0;
void * RotSensor::instances[ROTSENSOR_INSTANCES_MAX] = {0};

RotSensor::RotSensor(int pin,
                     const char *name,
                     unsigned long (*Millis)(void),
                     int (*PrintState)(const char *msg)
                     //  void (*IntrHdlr)(void)
                     ) : rs_pin(pin),
                         counter(0),
                         last_intr_time(0),
                         name(name),
                         GetMillis(Millis),
                         PrintState(PrintState)
//   RotSensor_InterruptionHandler(IntrHdlr)
{
    instances_count++;
    int i;
    printf ("Test");
    for (i = 0; i < ROTSENSOR_INSTANCES_MAX; i++)
    {
        /* code */
        if (i==ROTSENSOR_INSTANCES_MAX)
        {
            printf("Error: out of ROTSENSOR_INSTANCES_MAX");
        }

    }

    // instance_num
    //c++ - How to create an ISR in an Arduino class? - Stack Overflow https://stackoverflow.com/questions/41443720/how-to-create-an-isr-in-an-arduino-class
    // for(i; i < ROTSENSOR_INSTANCES_MAX; i++)
    // {
    //     if (instances[i] == 0)
    //     {
    //         instances[i] = (void *) this;
    //     }
    // }
    RotSensor_Init(this);
}

// void RotSensor::Start(int pin,
//                       const char *name,
//                       unsigned long (*Millis)(void),
//                       int (*PrintState)(const char *msg),
//                     //   void (*IntrHdlr)(void)
// )
//                       {
//     rs_pin = pin;
//     counter = 0;
//     last_intr_time = 0;
//     name = name;
//     GetMillis = Millis;
//     PrintState = PrintState;
//     // RotSensor_InterruptionHandler = IntrHdlr;
//     RotSensor_Init(this);
// }

void RotSensor::PlaceMeToYourIntHandler(RotSensor *rs) {
    unsigned long now = rs->GetMillis();
    // If interrupts come faster than debounce_filter_ms, assume it's a bounce and ignore
    if (now - rs->last_intr_time > DEBOUNCE_FILTER_MS) {
        rs->direction_backward ? rs->counter-- : rs->counter++;
        rs->PrintState("L+");
    }
    rs->last_intr_time = now;
}