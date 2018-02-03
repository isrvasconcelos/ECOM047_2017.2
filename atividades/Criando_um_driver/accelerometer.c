#include "accelerometer.h"

#define ADDRESS 0xE3
#define ACCELERATION_BUFFER_SIZE 10

typedef enum {
	kIdle = 0,
	kOpen,
	kRegisterSelection,
	kOperation
} accelerometerState_t;

typedef enum {
	kNoneOp = 0,
	kRead = 0x21,
	kWrite = 0x31
} accelerometOperation_t;

typedef enum {
	kNoneRegister = 0,
	kLowPowerMode = 0xB3,
	kAcceleration = 0xC3
} accelerometerRegister_t;

#define IS_VALID_ACCELERATION_REGISTER(reg) ((reg) == kLowPowerMode ||\
										(reg) == kAcceleration)
#define IS_VALID_ACCELERATION_OPERATION(op) ((op) == kRead ||\
										(op) == kWrite)

static accelerometerState_t __state = kIdle;
static accelerometOperation_t __op = kNoneOp;
static accelerometerRegister_t __register = kNoneRegister;

static const uint8_t __accelerations[ACCELERATION_BUFFER_SIZE] = {238, 54, 191, 174, 103, 228, 184, 57, 206, 13};

static mode_t __lowPowerMode = runMode;
static uint8_t __accelerationCursor = 0;

void incrementeAccelerationCursor(void) {
	if (__accelerationCursor == ACCELERATION_BUFFER_SIZE) {
		__accelerationCursor = 0;
	}
	else {
		__accelerationCursor++;
	}
}

status_t registerChanges(uint8_t data) {
	if (__op != kWrite) return fail;

	switch (__register) {
		case kLowPowerMode:
			if (!IS_VALID_MODE_TYPE(data)) return fail;
			__lowPowerMode = data;
			break;
		case kAcceleration:
			__accelerations[__accelerationCursor] = data;
			incrementeAccelerationCursor();
			break;
		default:
			break;
	}

	return ok;
}

status_t readValues(uint8_t *data) {
	if (__op != kRead) return fail;

	switch (__register) {
		case kLowPowerMode:
			*data = __lowPowerMode;
			break;
		case kAcceleration:
			*data = __accelerations[__accelerationCursor];
			incrementeAccelerationCursor();
			break;
		default:
			break;
	}
}

status_t write(uint8_t data) {
	switch (__state) {
		case kIdle:
			if (data == ADDRESS) {
				__state = kOpen;
				return ok;
			}
			return fail;
			break;
		case kOpen:
			if (data == ADDRESS) {
				__state = kIdle;
			}
			else if (IS_VALID_ACCELERATION_OPERATION(data)) {
				__state = kRegisterSelection;
				__op = data;
			}
			else {
				return fail;
			}
			return ok;
			break;
		case kRegisterSelection:
			if (data == ADDRESS) {
				__state = kIdle;
			}
			else if (IS_VALID_ACCELERATION_REGISTER(data)) {
				__state = kOperation;
				__register = data;
			}
			else {
				return fail;
			}
			return ok;
			break;
		case kOperation:
			__state = kIdle;
			return registerChanges(data);
			break;
		default:
			__state = kIdle;
			return fail;
			break;
	}
}

status_t read(uint8_t *data) {
	switch (__state) {
		case kOperation:
			__state = kIdle;
			return readValues(data);
			break;
		default:
			__state = kIdle;
			return fail;
			break;
	}
}
