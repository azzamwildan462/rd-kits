/**
 * Implementation of KalmanFilter class.
 *
 * @author: Hayk Martirosyan
 * @date: 2014.11.15
 */

#include <Eigen/Dense>
#include <iostream>
#include <stdexcept>

class KalmanFilter
{

public:
    /**
     * Create a Kalman filter with the specified matrices.
     *   A - System dynamics matrix
     *   C - Output matrix
     *   Q - Process noise covariance
     *   R - Measurement noise covariance
     *   P - Estimate error covariance
     */
    KalmanFilter(
        double dt,
        const Eigen::MatrixXd &A,
        const Eigen::MatrixXd &C,
        const Eigen::MatrixXd &Q,
        const Eigen::MatrixXd &R,
        const Eigen::MatrixXd &P)
        : A(A), C(C), Q(Q), R(R), P0(P), m(C.rows()), n(A.rows()), dt(dt), initialized(false), I(n, n), x_hat(n), x_hat_new(n)
    {
        I.setIdentity();
    }

    /**
     * Create a blank estimator.
     */
    KalmanFilter() {}

    /**
     * Initialize the filter with initial states as zero.
     */
    void init()
    {
        x_hat.setZero();
        P = P0;
        t0 = 0;
        t = t0;
        initialized = true;
    }

    /**
     * Initialize the filter with a guess for initial states.
     */
    void init(double t0, const Eigen::VectorXd &x0)
    {
        x_hat = x0;
        P = P0;
        this->t0 = t0;
        t = t0;
        initialized = true;
    }

    /**
     * Update the estimated state based on measured values. The
     * time step is assumed to remain constant.
     */
    void update(const Eigen::VectorXd &y)
    {
        if (!initialized)
            throw std::runtime_error("Filter is not initialized!");

        x_hat_new = A * x_hat;
        P = A * P * A.transpose() + Q;
        K = P * C.transpose() * (C * P * C.transpose() + R).inverse();
        x_hat_new += K * (y - C * x_hat_new);
        P = (I - K * C) * P;
        x_hat = x_hat_new;

        t += dt;
    }

    /**
     * Update the estimated state based on measured values,
     * using the given time step and dynamics matrix.
     */
    void update(const Eigen::VectorXd &y, double dt, const Eigen::MatrixXd A)
    {
        this->A = A;
        this->dt = dt;
        update(y);
    }

    /**
     * Return the current state and time.
     */
    Eigen::VectorXd state() { return x_hat; };
    double time() { return t; };

private:
    // Matrices for computation
    Eigen::MatrixXd A, C, Q, R, P, K, P0;

    // System dimensions
    int m, n;

    // Initial and current time
    double t0, t;

    // Discrete time step
    double dt;

    // Is the filter initialized?
    bool initialized;

    // n-size identity
    Eigen::MatrixXd I;

    // Estimated states
    Eigen::VectorXd x_hat, x_hat_new;
};
