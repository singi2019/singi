/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <logging/log.h>

#define LOG_MODULE_NAME main
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

void main(void)
{
    LOG_INF("The device start,Run! borrd:%s", CONFIG_BOARD);
    while(1)
    {
        k_sleep(K_MSEC(1000));
    }
}
