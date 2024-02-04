#ifndef BOARD_H_
#define BOARD_H_

#define PIN_NRST (0)
#define PIN_NTEST (1)
#define PIN_DONE (2)
#define PIN_SUCCESS (3)
#define PIN_CTRL (4)
#define PIN_SELECT (5)

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief controls the VCCA, assume it is disabled at reset
/// @param enable true: enable the supply. false: disable the supply
void vcca(bool enable);

/// @brief controls the VCCB, assume it is disabled at reset
/// @param enable true: enable the supply. false: disable the supply
void vccb(bool enable);

#ifdef __cplusplus
}
#endif

#endif