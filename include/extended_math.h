/**
 * @file extended_math.h
 *
 * @brief This file contains extended math functions.
 *
 * This file contains extended math functions.
 */

#ifndef EXTENDED_MATH_H
#define EXTENDED_MATH_H

#include "custom_typedef.h"
#include "math.h"

/**
 * @brief Calculate the distance between two points.
 *
 * @param point1 The first point.
 * @param point2 The second point.
 * @return float The distance between the two points.
 */
float pythagoras(point2d_t point1, point2d_t point2)
{
    return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
}

/**
 * @brief Calculate the distance between two points.
 *
 * @param x0 The x coordinate of the first point.
 * @param y0 The y coordinate of the first point.
 * @param x1 The x coordinate of the second point.
 * @param y1 The y coordinate of the second point.
 * @return float The distance between the two points.
 */
float pythagoras(float x0, float y0, float x1, float y1)
{
    return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

/**
 * @brief Calculate if the point is inside the rectangle.
 *
 * @param point The point to check.
 * @param field_max_x The maximum x coordinate of the field.
 * @param field_min_x The minimum x coordinate of the field.
 * @param field_max_y The maximum y coordinate of the field.
 * @param field_min_y The minimum y coordinate of the field.
 *
 * @return bool True if the point is inside the rectangle, false otherwise.
 */
bool is_inside_rectangle(point2d_t point, int field_max_x, int field_min_x, int field_max_y, int field_min_y)
{
    return (point.x > field_min_x && point.x < field_max_x && point.y > field_min_y && point.y < field_max_y);
}

/**
 * @brief Calculate if the point is inside the rectangle.
 *
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param field_max_x The maximum x coordinate of the field.
 * @param field_min_x The minimum x coordinate of the field.
 * @param field_max_y The maximum y coordinate of the field.
 * @param field_min_y The minimum y coordinate of the field.
 *
 * @return bool True if the point is inside the rectangle, false otherwise.
 */
bool is_inside_rectangle(float x, float y, int field_max_x, int field_min_x, int field_max_y, int field_min_y)
{
    return (x > field_min_x && x < field_max_x && y > field_min_y && y < field_max_y);
}

/**
 * @brief Calculate the area of a triangle.
 *
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param x3 The x coordinate of the third point.
 * @param y3 The y coordinate of the third point.
 *
 * @return float The area of the triangle.
 * */
float calc_area(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

/**
 * @brief Check if a point is inside a triangle.
 *
 * @param x The x coordinate of the point.
 * @param y The y coordinate of the point.
 * @param x1 The x coordinate of the first point of the triangle.
 * @param y1 The y coordinate of the first point of the triangle.
 * @param x2 The x coordinate of the second point of the triangle.
 * @param y2 The y coordinate of the second point of the triangle.
 * @param x3 The x coordinate of the third point of the triangle.
 * @param y3 The y coordinate of the third point of the triangle.
 *
 * @return bool True if the point is inside the triangle, false otherwise.
 */
bool check_point_is_inside_triangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
    float A = calc_area(x1, y1, x2, y2, x3, y3);
    float A1 = calc_area(x, y, x2, y2, x3, y3);
    float A2 = calc_area(x1, y1, x, y, x3, y3);
    float A3 = calc_area(x1, y1, x2, y2, x, y);

    return (A == A1 + A2 + A3);
}

/**
 * @brief Check if a point is inside a triangle.
 *
 * @param point The point to check.
 * @param x1 The x coordinate of the first point of the triangle.
 * @param y1 The y coordinate of the first point of the triangle.
 * @param x2 The x coordinate of the second point of the triangle.
 * @param y2 The y coordinate of the second point of the triangle.
 * @param x3 The x coordinate of the third point of the triangle.
 * @param y3 The y coordinate of the third point of the triangle.
 *
 * @return bool True if the point is inside the triangle, false otherwise.
 */
bool check_point_is_inside_triangle(point2d_t point, int x1, int y1, int x2, int y2, int x3, int y3)
{
    float A = calc_area(x1, y1, x2, y2, x3, y3);
    float A1 = calc_area(point.x, point.y, x2, y2, x3, y3);
    float A2 = calc_area(x1, y1, point.x, point.y, x3, y3);
    float A3 = calc_area(x1, y1, x2, y2, point.x, point.y);

    return (A == A1 + A2 + A3);
}

#endif