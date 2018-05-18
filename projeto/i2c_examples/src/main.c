/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"
#include "i2c_util.h"

struct i2c_dev acc, compass;

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

void main(void)
{
        SYS_LOG_WRN("Firmware version: v%d.%d.%d",
                        VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

        i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                                ACC_TEST_VALUE);
        i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                                COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);

        u8_t data[2];

        while(1);

        // while(1) {
        //         i2c_util_read_bytes(&acc, 0x02, data, sizeof(data));
        //         SYS_LOG_DBG("ACC X: %d", (data[1] << 8) | data[0]);
        // }
}
