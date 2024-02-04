/// @File: test.c
/// @brief: Entry function file , which has test cases to verify the implementation of modes.
/// @Author: Kshitija Dhondage
/// @version: 1.0
/// @Date : 2/3/2024


/// Standard Library files 
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/// User define header file
#include"modes.h"

/// @brief  Testing Functions to show how the implemented code for Mode 0, 1 and 2 would be used in an application.
/// @return 0: Each mode testing is successful
int main()
{

    assert(test_mode0() && "Error in Mode 0");
    assert(test_mode1() && "Error in Mode 1");
    assert(test_mode2() && "Error in Mode 2");
   
    return 0;
}

/// @brief  Test function for mode 0
/// @return true: mode 0 implementation testing is successful
///         false: Error in mode 0 implementation testing
bool test_mode0()
{
    Device_Initilization(); // Device Initilization

    Device_Configuration(); // Select the device for configuration

    bool status = Mode_Select(0);

    return status;
}

/// @brief  Test function for mode 1
/// @return true: mode 0 implementation testing is successful
///         false: Error in mode 1 implementation testing 
bool test_mode1()
{
    Device_Initilization(); // Device Initilization

    Device_Configuration(); // Select the device for configuration

    bool status = Mode_Select(1);

    return status;
}

/// @brief  Test function for mode 2
/// @return true: mode 0 implementation testing is successful
///         false: Error in mode 2 implementation testing
bool  test_mode2()
{
    Device_Initilization(); // Device Initilization

    Device_Configuration(); // Select the device for configuration

    bool status = Mode_Select(2);

    return status;

}