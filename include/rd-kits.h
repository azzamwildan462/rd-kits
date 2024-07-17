/**
 * @file rd-kits.h
 *
 * @brief This file contains all the custom libraries.
 */

/**
 * @mainpage Custom Libraries
 *
 * @section intro_sec Introduction
 * This is the documentation for the custom libraries.
 *
 * @section features_sec Features
 * The custom libraries provide the following features:
 * - Extended math functions
 * - Keyboard input functions
 * - PID controller
 * - Simple finite state machine
 * - Standard Kalman filter
 * - Custom time functions
 * - Custom typedefs
 *
 *
 *
 * @section install_sec Installation
 * It just a header file, so you can include it in your project easily.
 *
 * @section example_sec Example
 * Here is an example of how to use the custom libraries:
 *
 * @code{.cpp}
 * #include "rd-kits.h"
 *
 * int main()
 * {
 *    // Your code here
 *   return 0;
 * }
 * @endcode
 */

#ifndef RD_KITS_H
#define RD_KITS_H

#include "custom_time.h"
#include "custom_typedef.h"
#include "extended_math.h"
#include "pid.h"
#include "simple_fsm.h"
#include "keyboard_input.h"
#include "standard_kf.h"

#endif