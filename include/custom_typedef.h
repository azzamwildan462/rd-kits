/**
 * @file custom_typedef.h
 *
 * @brief This file contains custom typedefs.
 *
 * This file contains custom typedefs.
 */

#ifndef CUSTOM_TYPEDEF_H
#define CUSTOM_TYPEDEF_H

#include <stdint.h>

/**
 * @brief A 2D point.
 *
 */
typedef struct
{
    float x;
    float y;
} point2d_t;

/**
 * @brief A 2D polar point.
 *
 */
typedef struct
{
    float r;
    float theta;
} polar2d_t;

/**
 * @brief A 2D pose.
 *
 */
typedef struct
{
    float x;
    float y;
    float theta;
} pose2d_t;

/**
 * @brief A 2D pose with covariance.
 *
 */
typedef struct
{
    uint16_t curr_px;
    uint16_t prev_px;
    int16_t speed;
} enc_t;

#endif