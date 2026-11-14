#ifndef __TS_DRIVER_H
#define __TS_DRIVER_H

#include "main.h"
#include <stdbool.h>

/**
 * @brief Standardized CTP Driver Interface
 */
typedef struct {
    HAL_StatusTypeDef (*Init)(uint16_t addr);
    bool (*DetectTouch)(uint16_t addr);
    bool (*GetXY)(uint16_t addr, uint16_t *x, uint16_t *y);
} ts_driver_t;

#endif /* __TS_DRIVER_H */
