/**
 * @file simple_fsm.h
 *
 * @brief This file contains the MachineState class.
 *
 */

#ifndef SIMPLE_FSM_H
#define SIMPLE_FSM_H

#include <chrono>

/**
 * @brief The MachineState class.
 *
 */
class MachineState
{
public:
    /**
     * @brief The value of the state.
     *
     */
    int16_t value;

    /**
     * @brief The interrupt counter.
     *
     */
    uint8_t intr_cntr;

    /**
     * @brief The previous interrupt counter.
     *
     */
    uint8_t prev_intr_cntr;

    /**
     * @brief The uptime timeout.
     *
     */
    std::chrono::system_clock::time_point uptime_timeout;

    /**
     * @brief The uptime reentry.
     *
     */
    std::chrono::system_clock::time_point uptime_reentry;

    /**
     * @brief Construct a new MachineState object.
     *
     */
    MachineState()
    {
        value = 0;
        intr_cntr = 0;
        prev_intr_cntr = 0;
        uptime_timeout = std::chrono::high_resolution_clock::now();
        uptime_reentry = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Check if the state is interrupted.
     *
     * @return uint8_t 1 if the state is interrupted, 0 otherwise.
     */
    uint8_t isInterrupted()
    {
        return (intr_cntr != prev_intr_cntr);
    }

    /**
     * @brief Reset the uptime timeout. So the timeout will be reset to the current time.
     *
     */
    void resetUptimeTimeout()
    {
        uptime_timeout = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Reset the uptime reentry. So the reentry will be reset to the current time.
     *
     */
    void resetUptimeReentry()
    {
        uptime_reentry = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Timeout the state.
     * @brief If the elapsed time is greater than the period, the state will be changed to the target state.
     *
     * @param target_state The target state.
     * @param period The period.
     */
    void timeout(int16_t target_state, float period)
    {
        std::chrono::high_resolution_clock::time_point t_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_now - uptime_timeout;
        if (elapsed_seconds.count() > period)
        {
            value = target_state;
            uptime_timeout = std::chrono::high_resolution_clock::now();
        }
    }

    /**
     * @brief Reentry the state.
     * @brief If the elapsed time is greater than the period (these function not called anymore), the state will be changed to the target state.
     *
     * @param target_state The target state.
     * @param period The period.
     */
    void reentry(int16_t target_state, float period)
    {
        std::chrono::high_resolution_clock::time_point t_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = t_now - uptime_reentry;
        if (elapsed_seconds.count() > period)
        {
            value = target_state;
        }
        uptime_reentry = std::chrono::high_resolution_clock::now();
    }
};

#endif // SIMPLE_FSM_H