#ifndef COMS_H_
#define COMS_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief communicate the configuration data to the device
/// @param data pointer to configuration data
/// @param size size of the configuration located at data pointer
/// @return true: data was communicated successfully. false: an error occured in the communication
bool send_communications(const void* data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif