/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <i2c.h>

#include <display/mb_display.h>

#include "version.h" 

#define SYS_LOG_DOMAIN "PROJECT"
#include <logging/sys_log.h>

#define I2C_DEV CONFIG_I2C_0_NAME

struct device *acc_i2c_dev;

static int write_bytes(struct device *i2c_dev, u8_t i2c_dev_addr, u8_t reg,
                       u8_t *data, u32_t num_bytes)
{
    struct i2c_msg msgs[2];

    /* Send the address to read from */

    msgs[0].buf = &reg;
    msgs[0].len = 1;
    msgs[0].flags = I2C_MSG_WRITE;

    /* Read from device. STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

    return i2c_transfer(i2c_dev, &msgs[0], 2, i2c_dev_addr);
}

static int read_bytes(struct device *i2c_dev, u8_t i2c_dev_addr, u8_t reg,
                      u8_t *data, u32_t num_bytes)
{
    struct i2c_msg msgs[2];

    /* Send the address to read from */

    msgs[0].buf = &reg;
    msgs[0].len = 1;
    msgs[0].flags = I2C_MSG_WRITE;

    /* Read from device. STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

    return i2c_transfer(i2c_dev, &msgs[0], 2, i2c_dev_addr);
}

#define I2C_DEV_ADDR            0x1D
#define ACC_WHO_AM_I_REG        0x0D

//#define MMA8653_DEFAULT_ADDR    0x1D
//#define MMA8653_WHOAMI          0x0D

void __init_accelerometer_i2c() {
    int ret;
    acc_i2c_dev = device_get_binding(I2C_DEV);
    if (!acc_i2c_dev) {
        printk("I2C: Device driver not found.\n");
        return;
    }

    ret = i2c_configure(acc_i2c_dev,
                        I2C_SPEED_SET(I2C_SPEED_STANDARD) | I2C_MODE_MASTER);
    if(ret) {
        SYS_LOG_ERR("Could not configure I2C device. Erro code: %d", ret);
    }
    SYS_LOG_INF("device %s Configured successfuly.", CONFIG_I2C_0_NAME);

    u8_t id = 0;
    id = 0x00;
    ret = read_bytes(acc_i2c_dev, I2C_DEV_ADDR, ACC_WHO_AM_I_REG, &id, 1);
    if (ret) {
        SYS_LOG_DBG("Could not turn on display. Error Code %d", ret);
    } else {
        if(id == 0x54) {
            SYS_LOG_DBG("I2C test Success. ACC addr: 0x%X!", id);
        }
    }   
   
    /** @brief Setup button for testing purpose. It simulates the interrupt pin. 
    struct device *gpiob;
    gpiob = device_get_binding(SW0_GPIO_NAME);
    if (!gpiob) {
        printk("error\n");
        return;
    }
    gpio_pin_configure(gpiob, SW0_GPIO_PIN,
                       GPIO_DIR_IN | GPIO_INT |  GPIO_PUD_PULL_UP | GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW);
    gpio_init_callback(&gpio_cb, button_pressed, BIT(SW0_GPIO_PIN));
    gpio_add_callback(gpiob, &gpio_cb);
    gpio_pin_enable_callback(gpiob, SW0_GPIO_PIN);*/
}


static struct mb_image smiley = MB_IMAGE({ 0, 1, 0, 1, 0 },
					 { 0, 1, 0, 1, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 1, 0, 0, 0, 1 },
					 { 0, 1, 1, 1, 0 });

static const struct mb_image scroll[] = {
	MB_IMAGE({ 1, 0, 0, 0, 0 },
		 { 1, 0, 0, 0, 1 },
		 { 1, 0, 0, 1, 0 },
		 { 1, 0, 1, 0, 0 },
		 { 1, 1, 0, 0, 0 }),
	MB_IMAGE({ 1, 0, 0, 0, 0 },
		 { 0, 1, 0, 0, 0 },
		 { 0, 0, 1, 0, 0 },
		 { 0, 0, 0, 1, 0 },
		 { 0, 0, 0, 0, 1 }),
	MB_IMAGE({ 0, 0, 0, 0, 1 },
		 { 0, 0, 1, 0, 1 },
		 { 0, 1, 0, 1, 1 },
		 { 1, 0, 0, 0, 1 },
		 { 0, 0, 0, 0, 1 }),
};

static const struct mb_image animation[] = {
	MB_IMAGE({ 0, 0, 0, 0, 0 },
		 { 0, 0, 0, 0, 0 },
		 { 0, 0, 1, 0, 0 },
		 { 0, 0, 0, 0, 0 },
		 { 0, 0, 0, 0, 0 }),
	MB_IMAGE({ 0, 0, 0, 0, 0 },
		 { 0, 1, 1, 1, 0 },
		 { 0, 1, 1, 1, 0 },
		 { 0, 1, 1, 1, 0 },
		 { 0, 0, 0, 0, 0 }),
	MB_IMAGE({ 1, 1, 1, 1, 1 },
		 { 1, 1, 1, 1, 1 },
		 { 1, 1, 0, 1, 1 },
		 { 1, 1, 1, 1, 1 },
		 { 1, 1, 1, 1, 1 }),
	MB_IMAGE({ 1, 1, 1, 1, 1 },
		 { 1, 0, 0, 0, 1 },
		 { 1, 0, 0, 0, 1 },
		 { 1, 0, 0, 0, 1 },
		 { 1, 1, 1, 1, 1 }),
};

void main(void)
{
    SYS_LOG_WRN("Firmware version: v%d.%d.%d",
                VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);
                
    __init_accelerometer_i2c();
    
	struct mb_display *disp = mb_display_get();
	int x, y;

	/* Note: the k_sleep() calls after mb_display_print() and
	 * mb_display_image() are not normally needed since the APIs
	 * are used in an asynchronous manner. The k_sleep() calls
	 * are used here so the APIs can be sequentially demonstrated
	 * through this single main function.
	 */

	/* Display countdown from '9' to '0' */
	mb_display_print(disp, MB_DISPLAY_MODE_SINGLE,
			 K_SECONDS(1), "9876543210");
	k_sleep(K_SECONDS(11));

	/* Iterate through all pixels one-by-one */
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 5; x++) {
			struct mb_image pixel = {};
			pixel.row[y] = BIT(x);
			mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
					 K_MSEC(250), &pixel, 1);
			k_sleep(K_MSEC(300));
		}
	}

	/* Show a smiley-face */
	mb_display_image(disp, MB_DISPLAY_MODE_SINGLE, K_SECONDS(2),
			 &smiley, 1);
	k_sleep(K_SECONDS(2));

	/* Show a short scrolling animation */
	mb_display_image(disp, MB_DISPLAY_MODE_SCROLL, K_SECONDS(1),
			 scroll, ARRAY_SIZE(scroll));
	k_sleep(K_SECONDS(1) * (ARRAY_SIZE(scroll) + 2));

	/* Show a sequential animation */
	mb_display_image(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
			 K_MSEC(150), animation, ARRAY_SIZE(animation));
	k_sleep(K_MSEC(150) * ARRAY_SIZE(animation) * 5);

	/* Show some scrolling text ("Hello Zephyr!") */
	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
			 K_MSEC(500), "Hello Zephyr!");
}
