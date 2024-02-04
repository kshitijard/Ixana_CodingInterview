/// @File: modes.c
/// @brief: Implementation of mode 0, mode 1 , mode 2 and other helper functions
/// @Author: Kshitija Dhondage
/// @version: 1.0
/// @Date : 2/3/2024

/// User define header file
#include "modes.h"

/// @brief Initialize the Device pins directions(Input/Output mode)
void Device_Initilization()
{
  // Initialize Test pin as an input with pull up as it sets to  1
  assert(ntestPin.init(PUPD_UP) && "Initialization of ntestPin failed");
  
  // Initialize SELECT pin as an input with pull down as it sets to  0 means device is not being selected for configuration
  assert(selectPin.init(PUPD_DOWN) && "Initialization of selectPin failed");

  // Initialize NRST pin as an input irq with  pull-up resistor
  assert(nrstPin_in.init(PUPD_UP, EDGE_POSITIVE) && "Initialization of nrstPin failed");
  // Set the callback function
  nrstPin_in.set_callback(nrstPinCallback);
  // Enable the interrupt on the pin
  nrstPin_in.enable();

  // Initialize CTRL pin as an input with pull-down resistor
  assert(ctrlPin_in.init(PUPD_DOWN) && "Initialization of ctrlPin failed");
  
  // Initialize DONE pin as an output with OPENDRAIN mode
  assert(donePin.init(PUPD_UP, OUT_OPENDRAIN) && "Initialization of donePin failed");

  // Initialize SUCCESS pin as an output with OPENDRAIN mode
  assert(successPin.init(PUPD_DOWN, OUT_OPENDRAIN) && "Initialization of successPin failed");
}

/// @brief Set the device in configuration mode
void Device_Configuration()
{
     gpioSetHigh(PIN_SELECT); 
}

/// @brief Function to select the mode and call the corresponding configuration function.
/// @param int selects the mode 0/1/2
/// @return bool: true Selected mode's operation is successfull.
///               false Error in Selected mode's operation. 

bool Mode_Select(int selectedMode) 
{
    if (selectedMode >= 0 && selectedMode < sizeof(configureFunctions) / sizeof(configureFunctions[0])) 
    {
        // Call the corresponding configure function using the function pointer
       bool result = configureFunctions[selectedMode]();

       return result;
    }
    else 
    {
        // Handle invalid mode
        printf("Invalid mode selected.\n");
        return false;
    }
}

/// @brief Callback function for NRST pin 
/// @param edge NRST pin edge on which irq happened
void nrstPinCallback(edge) 
{
    /* Mode 0*/
    if (edge == EDGE_POSITIVE && configData.ctrlState==0 ) 
    {
        delay_us(10000);
    
        // Activate communications
        if (send_communications(&configData, sizeof(configData))) 
        {
            // Configuration is completed without error
            gpioSetHigh(PIN_DONE);
            gpioSetHigh(PIN_SUCCESS);
            config_success_flag = true;    
        } 
        else 
        {
            // Configuration is failed 
            gpioSetHigh(PIN_DONE);
            gpioSetLow(PIN_SUCCESS);
            config_success_flag = false;
        }
    }
    else if(edge == EDGE_POSITIVE && configData.ctrlState==1) // Mode 1
    {
        // 5ms delay
        delay_us(5000);

        // Stop the input mode of CTRL pin
       assert(ctrlPin_in.deinit() && "Uninitialization of ctrlPin failed");

       // Initialize CTRL pin as an output pin for externel control 
       assert(ctrlPin_out.init(PUPD_UP, OUT_PUSHPULL) && "Initialization of donePin failed");

       // This delay will change accordingly the externel control functionality.
       // On the basis of define externel control functionality , we have to replace this delay with given functionality.
       // then make the DONE pin high
       delay_us(external_control_delay);

       // Configuration is completed without error
        gpioSetHigh(PIN_DONE);
        gpioSetHigh(PIN_SUCCESS);
        config_success_flag = true;    
    }

    // Set the ISR completion flag
    callbackComplete = true;
}

/// @brief mode 0 implementation 
/// @return true : mode configured successfully
///         false: error in mode configuration
bool configure_mode_0()
{
    /// Read the status of input/ output pins
    configData.nrstState = nrstPin_in.read();  /// read the state of NRST pin
    configData.ctrlState = ctrlPin_in.read();  /// read the state of CTRL pin
    configData.doneState = donePin.read();  /// read the state of Done pin

    if((!(configData.doneState || configData.ctrlState)) && configData.nrstState)
    {
        delay_us(10000); ///10ms delay
    }
    else
    {
        //set the pins first
        gpioSetLow(PIN_CTRL);
        gpioSetLow(PIN_DONE);
        gpioSetHigh(PIN_NRST);
        delay_us(10000); //10ms delay
    }

    /// Lower nRST for 4 clock cycles
    gpioSetLow(PIN_NRST);
    
    ///enable vcca supply
    vcca(true);

    /// Wait for stabilization time. This willl vary according to device
    delay_us(stabilization_time_us); ///1ms delay

    ///enable vccb supply
    vccb(true);

    ///20ms delay. to keep NRST Low for 4 clock cycles
    delay_us(20000); 

    // Set the pin high
    gpioSetHigh(PIN_NRST);

    // Wait for the callback to complete 
    while (!callbackComplete);
    
    // Disable the interrupt after completing the code
    nrstPin_in.disable();
    
    return config_success_flag; 
}

/// @brief mode 1 implementation 
/// @return true : mode configured successfully
///         false: error in mode configuration
bool configure_mode_1()
{
    /// Read the status of input/ output pins
    configData.nrstState = nrstPin_in.read();  /// read the state of NRST pin
    configData.ctrlState = ctrlPin_in.read();  /// read the state of CTRL pin
    configData.doneState = donePin.read();  /// read the state of Done pin

    if((!(configData.doneState || configData.ctrlState)) && configData.nrstState)
    {
        delay_us(10000); ///10ms delay means 2 clock cycles 
    }
    else
    {
        //set the pins first
        gpioSetLow(PIN_CTRL);
        gpioSetLow(PIN_DONE);
        gpioSetHigh(PIN_NRST);
        delay_us(10000); //10ms delay  means 2 clock cycles 
    }

    /// Lower nRST for 3 clock cycles
    gpioSetLow(PIN_NRST);
    
    ///enable vcca supply
    vcca(true);

    /// Wait for stabilization time. This willl vary according to device
    delay_us(stabilization_time_us); ///1ms delay

    ///enable vccb supply
    vccb(true);

    ///15ms delay. to keep NRST Low for 3 clock cycles
    delay_us(15000); 
    
    /// Set the CTRL pin high
    gpioSetHigh(PIN_CTRL);

    ///5ms delay. 
    delay_us(5000); 
    
    /// Set the pin high
    gpioSetHigh(PIN_NRST);

    /// Wait for the callback to complete 
    while (!callbackComplete);
    
    /// Disable the interrupt after completing the code
    nrstPin_in.disable();
    
    return config_success_flag;  
}

/// @brief mode 2 implementation 
/// @return true : mode configured successfully
///         false: error in mode configuration
bool configure_mode_2()
{
    // Initialize CTRL pin as an output pin for externel control 
    assert(ctrlPin_out.init(PUPD_UP, OUT_PUSHPULL) && "Initialization of donePin failed");

    // Initialize NRST pin as an output pin for externel control 
    assert(nrstPin_out.init(PUPD_UP, OUT_PUSHPULL) && "Initialization of donePin failed");

    /// Read the status of input/ output pins
    configData.nrstState = nrstPin_out.read();  /// read the state of NRST pin
    configData.ctrlState = ctrlPin_out.read();  /// read the state of CTRL pin
    configData.doneState = donePin.read();  /// read the state of Done pin

    if((!configData.doneState) && configData.ctrlState && configData.nrstState)
    {
        // This delay will change accordingly the externel control functionality.
        // On the basis of define externel control functionality , we have to replace this delay with given functionality.
        // then make the DONE pin high
        delay_us(external_control_delay);

        // Configuration is completed without error
        gpioSetHigh(PIN_DONE);
        gpioSetHigh(PIN_SUCCESS);

        config_success_flag =true;
    }
    else
    {
        //set the pins first
        gpioSetHigh(PIN_CTRL);
        gpioSetHigh(PIN_NRST);
        gpioSetLow(PIN_DONE);

        // This delay will change accordingly the externel control functionality.
        // On the basis of define externel control functionality , we have to replace this delay with given functionality.
        // then make the DONE pin high
        delay_us(external_control_delay);

        // Configuration is completed without error
        gpioSetHigh(PIN_DONE);
        gpioSetHigh(PIN_SUCCESS);

        config_success_flag =true;
    }
    
    return config_success_flag;  
}