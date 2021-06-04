# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zero_test)

# NORDIC SDK APP START
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/dk_led_and_button.c)
target_sources(app PRIVATE src/uart.c)
target_sources(app PRIVATE src/blinky.c)
target_sources(app PRIVATE src/hello_world.c)
# NORDIC SDK APP END

zephyr_library_include_directories(.)
