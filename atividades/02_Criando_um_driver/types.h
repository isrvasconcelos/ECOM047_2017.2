#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <stdio.h>

typedef enum {
	ok = 0,
	fail = 1
} status_t;

typedef enum {
	lowPowerMode = 0x00,
	runMode = 0x01
} mode_t;

#define IS_VALID_MODE_TYPE(type) ((type) == lowPowerMode ||\
							(type) == runMode)

#endif //__TYPES_H__
