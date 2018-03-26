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

#include <display/mb_display.h>

#include "uart_driver.h"

#define ASCII_TO_INT(x) x - '0'

union command{
    struct {
        u8_t op;
        u8_t x;
        u8_t y;
        u8_t reserved;
    } params;
    u8_t data[4];
};

static union command current_command = {0};

static struct mb_image image = MB_IMAGE(
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 });

void DisplaySetPixel(u8_t x, u8_t y) {
    image.row[y] = image.row[y] | BIT(x);
}

void DisplayClearPixel(u8_t x, u8_t y) {
    image.row[y] = image.row[y] & ~BIT(x);
}

void DisplayReset() {
    for(u8_t i = 0; i < 5; ++i)
        image.row[i] = 0;
}
u8_t DisplayGetPixel(u8_t x, u8_t y) {
    return (image.row[y] & BIT(x)) >= 1;
}

void DisplayInvoker() {
    printk("Command executed: %s", current_command.data);
    if('0' <= current_command.params.x && current_command.params.x <= '9') {
        if('0' <= current_command.params.y && current_command.params.y <= '9') {
            switch (current_command.params.op) {
            case 'S':
                DisplaySetPixel(ASCII_TO_INT(current_command.params.x),
                                ASCII_TO_INT(current_command.params.y));
                printk("\n\nOK\n");
                break;
            case 'C':
                DisplayClearPixel(ASCII_TO_INT(current_command.params.x),
                                  ASCII_TO_INT(current_command.params.y));
                printk("\n\nOK\n");
                break;
            case 'R':
                DisplayReset();
                printk("\n\nOK\n");
                break;
            case 'G':
                printk("Result: %d\n",
                       DisplayGetPixel(ASCII_TO_INT(current_command.params.x),
                                       ASCII_TO_INT(current_command.params.y)));
                printk("\n\nOK\n");
                break;
            default:
                printk("Command not found... Please type S,C,R and G\n");
                break;
            }
        }
    }
}

uint8_t _cmd_index = 0;
void DisplayCommandParser(uint8_t data) {
    current_command.data[_cmd_index] = data;
    ++_cmd_index;
    printk("%c", data);
    if(_cmd_index == 3) {
        printk("\n");
        DisplayInvoker();
        _cmd_index = 0;
    }
}

void main(void)
{
    printk("hello world!\n");
    struct mb_display *disp = mb_display_get();

    DriverOpen();
    DriverSetCallback(DisplayCommandParser);
    /* Note: the k_sleep() calls after mb_display_print() and
     * mb_display_image() are not normally needed since the APIs
     * are used in an asynchronous manner. The k_sleep() calls
     * are used here so the APIs can be sequentially demonstrated
     * through this single main function.
     */
    DisplaySetPixel(0,0);
    if(DisplayGetPixel(0,0)) {
        printk("pass\n");
    }
    DisplayClearPixel(0,0);
    if(!DisplayGetPixel(0,0)) {
        printk("pass\n");
    }
    DisplaySetPixel(0,0);
    DisplayReset();
    if(!DisplayGetPixel(0,0)) {
        printk("pass\n");
    }


    /* Iterate through all pixels one-by-one */

    DisplaySetPixel(0, 0);
    DisplaySetPixel(1, 1);
    DisplaySetPixel(2, 2);
    DisplaySetPixel(3, 3);
    DisplaySetPixel(4, 4);

    while(1) {
        mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                         K_MSEC(250), &image, 1);
        k_sleep(K_MSEC(250));
    }
}
