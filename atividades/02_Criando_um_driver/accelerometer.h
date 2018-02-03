#ifndef __ACCELETOMETER_H__
#define __ACCELETOMETER_H__

#include "types.h"

//to disable the accelerometer's log set the value of this define to 0
#define ACCELEROMETER_LOG_EN 1

status_t accelerometerWrite(uint8_t data);
status_t accelerometerRead(uint8_t *data);

#endif //__ACCELETOMETER_H__
