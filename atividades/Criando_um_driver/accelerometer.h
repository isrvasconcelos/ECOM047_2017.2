#ifndef __ACCELETOMETER_H__
#define __ACCELETOMETER_H__

#include "types.h"

#define ACCELEROMETER_LOG_EN 0

status_t write(uint8_t data);
status_t read(uint8_t *data);

#endif //__ACCELETOMETER_H__
