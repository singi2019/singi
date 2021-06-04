/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>

#define LOG_MODULE_NAME hello_world_thread
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

void hello_world_thread(void)
{
    LOG_INF("Print Hello World!");
#if 0
    while(1)
    {
        LOG_INF("Print Hello World!");
        k_sleep(K_SECONDS(10));
    }
#endif
}
K_THREAD_DEFINE(hello_world_id, 1024, hello_world_thread, NULL, NULL,
        NULL, 7, 0, 0);
