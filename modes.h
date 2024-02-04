#ifndef MODES_H_
#define MODES_H_

/// Standard Library files 
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/// User define header file
#include"board.h"
#include "gpio.hpp"
#include "pin.h"

/// These two macros are define for stabilization and externel control.
/// As these two informations are not given, the time required to complete those operations are assumed and implemented using delay.
/// During actual implementation these macros will be change with the actual values.
#define stabilization_time_us (1000)
#define external_control_delay (2000)

/// Global flag to configuration status (successfull/failed)
bool config_success_flag = false;

/// Global flag to signal completion of the callback
volatile bool callbackComplete = false;

/// Create an instance for input/output pins
struct gpio_in_t ntestPin = {PIN_NTEST};
struct gpio_in_t selectPin = {PIN_SELECT};
struct gpio_irq_t nrstPin_in = {PIN_NRST};
struct gpio_out_t nrstPin_out = {PIN_NRST};
struct gpio_in_t ctrlPin_in = {PIN_CTRL};
struct gpio_out_t ctrlPin_out = {PIN_CTRL};
struct gpio_out_t donePin = {PIN_DONE};
struct gpio_out_t successPin = {PIN_SUCCESS};

///  configuration data structure
struct config_data{
    bool ntestState;
    bool doneState ;
    bool nrstState ;
    bool ctrlState ;
    bool selectState ;
} ;

/// instance of configuration data structure
struct config_data configData ;

/// Array of function pointers for configuration functions
void (*configureFunctions[])(void) = 
{
    configure_mode_0,
    configure_mode_1,
    configure_mode_2
};

/// Functions Declaration
void Device_Initilization();
void Device_Configuration();
bool Mode_Select(uint8_t);
bool configure_mode_0();
bool configure_mode_1();
bool configure_mode_2();

#endif