/**
 * @file keyboard_input.h
 *
 * @brief This file contains keyboard input functions.
 *
 * This file contains keyboard input functions.
 */

#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "stdio.h"
#include "sys/ioctl.h"
#include "termios.h"

/**
 * @brief Check if a key is pressed.
 *
 * @brief It's an unblocking function that returns the number of bytes waiting in the input buffer.
 *
 * @return int The number of bytes waiting in the input buffer.
 */
int kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized)
    {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#endif