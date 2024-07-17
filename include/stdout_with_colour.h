/**
 * @file stdout_with_colour.h
 *
 * @brief This file contains a function to print text with colour.
 */

#ifndef STDOUT_WITH_COLOUR_H
#define STDOUT_WITH_COLOUR_H

/* COLOR DEFINITIONS */
#define COLOR_RED 0x01
#define COLOR_GREEN 0x02
#define COLOR_YELLOW 0x03
#define COLOR_BLUE 0x04
#define COLOR_MAGENTA 0x05
#define COLOR_CYAN 0x06
#define COLOR_WHITE 0x07
#define COLOR_RESET 0x08

#include <stdio.h>
#include <stdarg.h>

/**
 * @brief Print text with colour.
 *
 * @param color The colour of the text.
 * @param text The text to print.
 */
void LogWithColor(__uint8_t color, const char *text, ...)
{

    switch (color)
    {
    case COLOR_RED:
        printf("\033[1;31m");
        break;
    case COLOR_GREEN:
        printf("\033[1;32m");
        break;
    case COLOR_YELLOW:
        printf("\033[1;33m");
        break;
    case COLOR_BLUE:
        printf("\033[1;34m");
        break;
    case COLOR_MAGENTA:
        printf("\033[1;35m");
        break;
    case COLOR_CYAN:
        printf("\033[1;36m");
        break;
    case COLOR_WHITE:
        printf("\033[1;37m");
        break;
    case COLOR_RESET:
        printf("\033[0m");
        break;
    default:
        printf("\033[0m");
        break;
    }

    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
    printf("\033[0m");
}

#endif