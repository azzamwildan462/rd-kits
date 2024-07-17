/**
 * @file kf_1d_v_const.h
 *
 * @brief This file contains a 1D Kalman filter with constant velocity model.
 *
 * This header was not used anymore, don't include it in the future.
 */

#ifndef KF_1d_V_CONST_H
#define KF_1d_V_CONST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <float.h>

typedef struct
{
    float x;
    float x_dot;
} differential_v_const_t;

double get_time(void)
{
    double tm;
    struct timeval tim;

    gettimeofday(&tim, NULL);

    tm = (double)tim.tv_sec + tim.tv_usec / 1000000.0;

    return tm;
}

typedef struct
{
    differential_v_const_t uncertainly_est;
    differential_v_const_t uncertainly_mea;

    differential_v_const_t kalman_gain;

    differential_v_const_t current_state;
    differential_v_const_t current_covariance;

    differential_v_const_t prediction_state;
    differential_v_const_t prediction_covariance;

    double dt;
    double last_update_s;

    uint8_t has_init;

    float q; // process noise

} KF;

void KF_init(KF *kf, float x, float x_dot)
{
    kf->current_state.x = x;
    kf->current_state.x_dot = x_dot;

    kf->current_covariance.x = kf->uncertainly_est.x;
    kf->current_covariance.x_dot = kf->uncertainly_est.x_dot;

    kf->prediction_state.x = kf->current_state.x + kf->current_state.x_dot * kf->dt;
    kf->prediction_state.x_dot = kf->current_state.x_dot;

    kf->prediction_covariance.x = kf->current_covariance.x + kf->current_covariance.x_dot * kf->dt * kf->dt;
    kf->prediction_covariance.x_dot = kf->current_covariance.x_dot;

    kf->last_update_s = get_time() - kf->dt;

    kf->has_init = 1;
}
differential_v_const_t KF_update(KF *kf, float x)
{
    double t_now = get_time();
    kf->dt = t_now - kf->last_update_s;
    kf->last_update_s = t_now;

    if (kf->dt < DBL_EPSILON)
    {
        printf("TIME JITTER\n");
        return kf->current_state;
    }

    // Reset if there is new data coming
    if (kf->dt > 1)
    {
        printf("RESET KF\n");
        KF_init(kf, x, 0);
        return kf->current_state;
    }

    // Kalman gain calculation
    kf->kalman_gain.x = kf->uncertainly_est.x / (kf->uncertainly_est.x + kf->uncertainly_mea.x);
    kf->kalman_gain.x_dot = kf->uncertainly_est.x_dot / (kf->uncertainly_est.x_dot + kf->uncertainly_mea.x_dot);

    // State calculation
    kf->current_state.x = kf->prediction_state.x + kf->kalman_gain.x * (x - kf->prediction_state.x);
    kf->current_state.x_dot = kf->prediction_state.x_dot + kf->kalman_gain.x_dot * (x - kf->prediction_state.x) / kf->dt;

    kf->current_covariance.x = (1 - kf->kalman_gain.x) * kf->prediction_covariance.x;
    kf->current_covariance.x_dot = (1 - kf->kalman_gain.x_dot) * kf->prediction_covariance.x_dot;

    // Prediction calculation
    kf->prediction_state.x = kf->current_state.x + kf->current_state.x_dot * kf->dt;
    kf->prediction_state.x_dot = kf->current_state.x_dot;

    kf->prediction_covariance.x = kf->current_covariance.x + kf->current_covariance.x_dot * kf->dt * kf->dt;
    kf->prediction_covariance.x_dot = kf->current_covariance.x_dot;

    kf->uncertainly_est.x = kf->current_covariance.x + kf->q;
    kf->uncertainly_est.x_dot = kf->current_covariance.x_dot + kf->q;

    return kf->current_state;
}

differential_v_const_t KF_predict(KF *kf, float time_target)
{
    differential_v_const_t predicted_state;

    predicted_state.x = kf->current_state.x + kf->current_state.x_dot * time_target;
    predicted_state.x_dot = kf->current_state.x_dot;

    return predicted_state;
}

#endif