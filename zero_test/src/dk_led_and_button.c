/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <soc.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>


#define LOG_MODULE_NAME dk_leds_buttons_thread
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

#define CON_STATUS_LED DK_LED2


void button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	
	if (buttons & DK_BTN1_MSK) {
		LOG_INF("dk button:1 press");		
	}

	if (buttons & DK_BTN2_MSK) {
		LOG_INF("dk button:2 press");
	}

	if (buttons & DK_BTN3_MSK) {
		LOG_INF("dk button:3 press");
	}

	if (buttons & DK_BTN4_MSK) {
		LOG_INF("dk button:4 press");
	}
}

static void configure_gpio(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		LOG_ERR("Cannot init buttons (err: %d)", err);
	}

	err = dk_leds_init();
	if (err) {
		LOG_ERR("Cannot init LEDs (err: %d)", err);
	}
}

void leds_buttons_thread(void)
{
    configure_gpio();
	LOG_INF("leds and buttons init done!");
}

K_THREAD_DEFINE(leds_buttons_thread_id, 1024, leds_buttons_thread, NULL, NULL,
        NULL, 7, 0, 0);
