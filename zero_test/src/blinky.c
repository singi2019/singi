/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#include <logging/log.h>

#define LOG_MODULE_NAME blinky_thread
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000
#if 1

/* The devicetree node identifier for the "led2" alias. */
#define LED2_NODE DT_ALIAS(led2)

#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
#define LED2	DT_GPIO_LABEL(LED2_NODE, gpios)
#define LED2_PIN	DT_GPIO_PIN(LED2_NODE, gpios)
#define LED2_FLAGS	DT_GPIO_FLAGS(LED2_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led2 devicetree alias is not defined"
#define LED2	""
#define LED2_PIN	0
#define LED2_FLAGS	0
#endif

#endif

#if 1
/* The devicetree node identifier for the "led3" alias. */
#define LED3_NODE DT_ALIAS(led3)

#if DT_NODE_HAS_STATUS(LED3_NODE, okay)
#define LED3	DT_GPIO_LABEL(LED3_NODE, gpios)
#define LED3_PIN	DT_GPIO_PIN(LED3_NODE, gpios)
#define LED3_FLAGS	DT_GPIO_FLAGS(LED3_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led3 devicetree alias is not defined"
#define LED3	""
#define LED3_PIN	0
#define LED3_FLAGS	0
#endif
#endif

void blinky_thread(void)
{
    const struct device *dev;
    bool led_is_on = true;
    int ret;

    dev = device_get_binding(LED3);
    dev = device_get_binding(LED2);
    if (dev == NULL) {
        return;
    }

    ret = gpio_pin_configure(dev, LED3_PIN, GPIO_OUTPUT_ACTIVE | LED3_FLAGS);
    ret = gpio_pin_configure(dev, LED2_PIN, GPIO_OUTPUT_ACTIVE | LED2_FLAGS);
    if (ret < 0) {
        return;
    }

    LOG_INF("blinky thread -> LED3 and LED4 1s loop flashing");
    while (1) {
        gpio_pin_set(dev, LED3_PIN, (int)led_is_on);
        gpio_pin_set(dev, LED2_PIN, (int)!led_is_on);
        led_is_on = !led_is_on;
        k_msleep(SLEEP_TIME_MS);
    }
}

K_THREAD_DEFINE(blinky_thread_id, 1024, blinky_thread, NULL, NULL,
        NULL, 7, 0, 0);
