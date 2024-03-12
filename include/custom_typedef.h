#ifndef CUSTOM_TYPEDEF_H
#define CUSTOM_TYPEDEF_H

#include <stdint.h>

typedef struct
{
    float x;
    float y;
} point2d_t;

typedef struct
{
    float r;
    float theta;
} polar2d_t;

typedef struct
{
    float x;
    float y;
    float theta;
} pose2d_t;

typedef struct
{
    uint16_t curr_px;
    uint16_t prev_px;
    int16_t speed;
} enc_t;

#endif