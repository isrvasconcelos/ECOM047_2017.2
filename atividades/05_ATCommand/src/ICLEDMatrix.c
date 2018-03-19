//
// Created by matheuswhite on 19/03/18.
//

#include "ICLEDMatrix.h"

static bool __isInitialized = false;
static struct mb_image __heart = MB_IMAGE({ 0, 1, 0, 1, 0 },
                                        { 1, 1, 1, 1, 1 },
                                        { 1, 1, 1, 1, 1 },
                                        { 0, 1, 1, 1, 0 },
                                        { 0, 0, 1, 0, 0 });
static struct mb_display *__display;
static uint8_t __timeActive;

ICStatus ICLEDMatrixInit(void) {
    if (__isInitialized) {
        printk("[LED Matrix|Error|%d] Module already initialized!\n", __LINE__);
        return kFAIL;
    }

    printk("[LED Matrix|Error|%d] Initializing module...\n", __LINE__);
    __display = mb_display_get();
    __isInitialized = true;
    __timeActive = 5;
    printk("[LED Matrix|Error|%d] Module initialized!\n", __LINE__);

    return kOK;
}

ICStatus ICLEDMatrixDrawHeart(void) {
    if (!__isInitialized) {
        printk("[LED Matrix|Error|%d] Module not initialized!\n", __LINE__);
        return kFAIL;
    }

    printk("[LED Matrix|Error|%d] Drawing a heart and showing for %d seconds.\n", __LINE__, __timeActive);
    mb_display_image(__display, MB_DISPLAY_MODE_SINGLE, K_SECONDS(__timeActive), &__heart, 1);
    k_sleep(K_SECONDS(__timeActive));

    return kOK;
}

ICStatus ICLEDMatrixTimeActive(uint8_t seconds) {
    printk("[LED Matrix|Error|%d] Old time active: %d, new time active: %d!\n", __LINE__, __timeActive, seconds);
    __timeActive = seconds;

    return kOK;
}

ICStatus ICLEDMatrixDrawHours(uint8_t hour, uint8_t min) {
    if (!__isInitialized) {
        printk("[LED Matrix|Error|%d] Module not initialized!\n", __LINE__);
        return kFAIL;
    }

    if (hour > 23 || min > 59) {
        printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
        return kFAIL;
    }

    char output[6];
    snprintk(output, 6, "%02d:%02d", hour, min);

    printk("[LED Matrix|Error|%d] Drawing %s.\n", __LINE__, output);

    mb_display_print(__display, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), output);
    k_sleep(K_SECONDS(5));

    return kOK;
}

ICStatus ICLEDMatrixDrawString(const char *str) {
    if (!__isInitialized) {
        printk("[LED Matrix|Error|%d] Module not initialized!\n", __LINE__);
        return kFAIL;
    }

    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] < 0x20 || str[i] > 0x7E) {
            printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
            return kFAIL;
        }
    }

    printk("[LED Matrix|Error|%d] Drawing %s.\n", __LINE__, str);

    mb_display_print(__display, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), str);
    k_sleep(K_SECONDS(1)*strlen(str));

    return kOK;
}

ICStatus ICLEDMatrixDrawName(const char *name, const char *surname) {
    if (!__isInitialized) {
        printk("[LED Matrix|Error|%d] Module not initialized!\n", __LINE__);
        return kFAIL;
    }

    for (size_t i = 0; i < strlen(name); ++i) {
        if (name[i] < 0x20 || name[i] > 0x7E) {
            printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
            return kFAIL;
        }
    }

    for (size_t i = 0; i < strlen(surname); ++i) {
        if (surname[i] < 0x20 || surname[i] > 0x7E) {
            printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
            return kFAIL;
        }
    }

    size_t length = strlen(name)+strlen(surname)+2;
    char output[length];
    snprintk(output, length, "%s-%s", name, surname);

    printk("[LED Matrix|Error|%d] Drawing %s.\n", __LINE__, output);

    mb_display_print(__display, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), output);
    k_sleep(K_SECONDS(1)*(length-1));

    return kOK;
}

ICStatus ICLEDMatrixDrawDate(uint8_t day, const char *month, uint16_t year) {
    if (!__isInitialized) {
        printk("[LED Matrix|Error|%d] Module not initialized!\n", __LINE__);
        return kFAIL;
    }

    if (strlen(month) != 3 || day > 31) {
        printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
        return kFAIL;
    }

    for (size_t i = 0; i < strlen(month); ++i) {
        if (month[i] < 0x20 || month[i] > 0x7E) {
            printk("[LED Matrix|Error|%d] Format not supported!\n", __LINE__);
            return kFAIL;
        }
    }

    char output[12];
    snprintk(output, 12, "%02d-%s-%04d", day, month, year);

    printk("[LED Matrix|Error|%d] Drawing %s.\n", __LINE__, output);

    mb_display_print(__display, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), output);
    k_sleep(K_SECONDS(11));

    return kOK;
}
