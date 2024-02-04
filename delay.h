#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief block for a number of microseconds
/// @param us_ number of microseconds to wait 
void delay_us(uint32_t us_);

/// @brief running microsecond counter value
/// @return value of the microsecond counter
uint32_t time_us();

#ifdef __cplusplus
}
#endif

#endif