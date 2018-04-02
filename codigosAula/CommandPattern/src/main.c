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
#include <ic_assert.h>

#include <display/mb_display.h>

#include "uart_driver.h"

#define ASCII_TO_INT(x) x - '0'
#define UNUSED(x) (void) x
#define IS_VALID(x) ASSERT(0 <= x && x < 5, #x " must be between 0 and 4");

typedef enum {
    Set = 'S',
    Get = 'G',
    Clear = 'C',
    Reset = 'R'
} command_type_t;

typedef union {
    struct {
        u8_t op;
        u8_t x;
        u8_t y;
        u8_t reserved;
    } params;
    u8_t data[4];
} command_t;

static command_t current_command = {0};

static struct mb_image image = MB_IMAGE(
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 });

void print_command(command_t *cmd) {
    printk("Command: Op = %c, x = %c, y = %c\n", cmd->params.op, cmd->params.x, cmd->params.y);
}

void DisplaySetPixel(command_t *cmd) {
    u8_t x = ASCII_TO_INT(cmd->params.x);
    IS_VALID(x);
    u8_t y = ASCII_TO_INT(cmd->params.y);
    IS_VALID(y);
    image.row[y] = image.row[y] | BIT(x);
}

void DisplayClearPixel(command_t *cmd) {
    u8_t x = ASCII_TO_INT(cmd->params.x);
    IS_VALID(x);
    u8_t y = ASCII_TO_INT(cmd->params.y);
    IS_VALID(x);
    image.row[y] = image.row[y] & ~BIT(x);
}

void DisplayReset(command_t *cmd) {
    UNUSED(cmd);
    for(u8_t i = 0; i < 5; ++i)
        image.row[i] = 0;
}
u8_t DisplayGetPixel(command_t *cmd) {
    u8_t x = ASCII_TO_INT(cmd->params.x);
    IS_VALID(x);
    u8_t y = ASCII_TO_INT(cmd->params.y);
    IS_VALID(x);
    return (image.row[y] & BIT(x)) >= 1;
}

void DisplayInvoker() {
    printk("Command executed: %s", current_command.data);
    if('0' <= current_command.params.x && current_command.params.x <= '4') {
        if('0' <= current_command.params.y && current_command.params.y <= '4') {
            switch (current_command.params.op) {
            case Set:
                DisplaySetPixel(&current_command);
                printk("\n\nOK\n");
                return;
            case Clear:
                DisplayClearPixel(&current_command);
                printk("\n\nOK\n");
                return;
            case Reset:
                DisplayReset(&current_command);
                printk("\n\nOK\n");
                return;
            case Get:
                printk("Result: %d\n",
                       DisplayGetPixel(&current_command));
                printk("\n\nOK\n");
                return;
            default:
                printk("\nCommand not found... Please type S,C,R and G\n");
            }
        }
    }
    printk("\n\nERROR\n");
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
    struct mb_display *disp = mb_display_get();

#ifdef ASSERT_ENABLED
    printk(" ** ASSERT enabled for this project.\n");
    command_t test_command = {.data="S00"};
    print_command(&test_command);

    DisplaySetPixel(&test_command);
    ASSERT(DisplayGetPixel(&test_command) == 1, "GetPixel failed: result must be 1");
    printk("Pass test 01!\n");
    DisplayClearPixel(&test_command);
    ASSERT(DisplayGetPixel(&test_command) == 0, "GetPixel failed: result must be 0");
    printk("Pass test 02!\n");
    DisplaySetPixel(&test_command);
    ASSERT(DisplayGetPixel(&test_command) == 1, "GetPixel failed: result must be 1");
    printk("Pass test 03!\n");
    DisplayReset(&test_command);
    ASSERT(DisplayGetPixel(&test_command) == 0, "GetPixel failed: result must be 0");
    printk("Pass test 04!\n");
    printk("Display testing done. No errors found!\n");


    /* Iterate through all pixels one-by-one */

    test_command.params.x = '0';
    test_command.params.y = '0';
    DisplaySetPixel(&test_command);
    test_command.params.x = '1';
    test_command.params.y = '1';
    DisplaySetPixel(&test_command);
    test_command.params.x = '2';
    test_command.params.y = '2';
    DisplaySetPixel(&test_command);
    test_command.params.x = '3';
    test_command.params.y = '3';
    DisplaySetPixel(&test_command);
    test_command.params.x = '4';
    test_command.params.y = '4';
    DisplaySetPixel(&test_command);
#endif

    DriverOpen();
    DriverSetCallback(DisplayCommandParser);
    /* Note: the k_sleep() calls after mb_display_print() and
     * mb_display_image() are not normally needed since the APIs
     * are used in an asynchronous manner. The k_sleep() calls
     * are used here so the APIs can be sequentially demonstrated
     * through this single main function.
     */

    while(1) {
        mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                         K_MSEC(260), &image, 1);
        k_sleep(K_MSEC(250));
    }
}
