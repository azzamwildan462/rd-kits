/**
 * @file pid.h
 *
 * @brief This file contains the PID class.
 *
 * This file contains the PID class.
 */

#ifndef PID_H_
#define PID_H_

#include <chrono>

/**
 * @brief The PID class.
 *
 */
class PID
{
    float Kp;
    float Ki;
    float Kd;
    float min_out;
    float max_out;
    float min_integral;
    float max_integral;
    float integral;
    float last_error;
    float proportional;
    float derivative;
    float output_speed;
    std::chrono::system_clock::time_point last_call;

    /**
     * @brief Construct a new PID object.
     *
     * @param Kp The proportional gain.
     * @param Ki The integral gain.
     * @param Kd The derivative gain.
     */
    PID(float Kp, float Ki, float Kd)
    {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
    }

    /**
     * @brief Calculate the PID output.
     *
     * @param error The error.
     * @param minmax The minimum and maximum output.
     * @return float The output.
     */
    float calculate(float error, float minmax)
    {
        std::chrono::high_resolution_clock::time_point t_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_now - this->last_call;
        if (elapsed_seconds.count() > 2)
        {
            this->integral = 0;
            this->last_error = 0;
        }
        this->last_call = std::chrono::high_resolution_clock::now();

        this->min_out = this->min_integral = -minmax;
        this->max_out = this->max_integral = minmax;

        this->proportional = this->Kp * error;
        this->integral += this->Ki * error;
        this->derivative = this->Kd * (error - this->last_error);

        // printf("%.2f %.2f %.2f %.2f %.2f\n", this->proportional, this->integral, this->derivative, error, this->last_error);
        this->last_error = error;

        if (this->integral > this->max_integral)
            this->integral = this->max_integral;
        else if (this->integral < this->min_integral)
            this->integral = this->min_integral;

        this->output_speed = this->proportional + this->integral + this->derivative;

        if (this->output_speed > this->max_out)
            this->output_speed = this->max_out;
        else if (this->output_speed < this->min_out)
            this->output_speed = this->min_out;
        return this->output_speed;
    }
};

#endif // PID_H_