//
// Created by matheuswhite on 19/03/18.
//

#ifndef PROJECT_ICLEDMATRIX_H
#define PROJECT_ICLEDMATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>

#include "ICStatus.h"

/*!
 * @brief This function initialize the module: "LED Matrix"
 * @return kOK if the module has not been initialized. And, kFAIL otherwise.
 */
ICStatus ICLEDMatrixInit(void);

/*!
 * @at_command AT+HEART
 * @brief This function draw a heart in the LED Matrix. This heart will remain in the LED Matrix, by default, 5 seconds.
 * @return kOK if the module has been initialized. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixDrawHeart(void);

/*!
 * @at_command AT+TIME=<int>
 * @brief This function change the time the heart remains in the LED Matrix
 * @param seconds - A unsigned integer that represent the seconds in which the heart will remain in the LED matrix.
 * @return kOK if the module has been initialized. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixTimeActive(uint8_t seconds);

/*!
 * @at_command AT+HOURS=<int>,<int>
 * @brief This function will draw, in the LED Matrix, a hour and a minute. Each number will be shown sequentially, and
 *        will stay in the LED Matrix for 1 seconds. The hour will be followed by ":".
 * @param hour - A unsigned integer that represent the hours. This value must be less than 24.
 * @param min - A unsigned integer that represent the minutes. This value must be less than 60.
 * @return kOK if the module has been initialized and the conditions of above params has been met. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixDrawHours(uint8_t hour, uint8_t min);

/*!
 * @at_command AT+STRING=<str>
 * @brief This function will draw, in the LED Matrix, an any string. Each character will be shown sequentially, and
 *        will stay in the LED Matrix for 1 seconds.
 * @param str - A generic string. The characters of this string must be between 0x20 and 0x7E.
 * @return kOK if the module has been initialized and the conditions of above params has been met. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixDrawString(const char *str);

/*!
 * @at_command AT+NAME=<str>,<str>
 * @brief This function will draw, in the LED Matrix: a name and a surname. Each character will be shown sequentially, and
 *        will stay in the LED Matrix for 1 seconds. The name and surname will be separated by a hyphen.
 * @param name - A string that represent a name. The characters of this string must be between 0x20 and 0x7E.
 * @param surname - A string that represent a surname. The characters of this string must be between 0x20 and 0x7E.
 * @return kOK if the module has been initialized and the conditions of above params has been met. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixDrawName(const char *name, const char *surname);

/*!
 * @at_command AT+DATE=<int>,<str>,<int>
 * @brief This function will draw, in the LED Matrix, a date. Each character (or number) will be
 *        shown sequentially, and will stay in the LED Matrix for 1 seconds. The day, the month and the year will be
 *        separated by a hyphen.
 * @param day - A unsigned integer that represent the day of a date. This value must be less than 32.
 * @param month - A string that represent the month of a date. The length of this string must be less than 3 and the
 *                characters of this string must be between 0x20 and 0x7E.
 * @param year - A unsigned integer that represent the year of a date.
 * @return kOK if the module has been initialized and the conditions of above params has been met. And kFAIL, otherwise.
 */
ICStatus ICLEDMatrixDrawDate(uint8_t day, const char *month, uint16_t year);

#endif //PROJECT_ICLEDMATRIX_H
