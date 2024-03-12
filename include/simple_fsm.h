#ifndef SIMPLE_FSM_H
#define SIMPLE_FSM_H

#include <chrono>

class MachineState
{
public:
    int16_t value;
    uint8_t intr_cntr;
    uint8_t prev_intr_cntr;
    std::chrono::system_clock::time_point uptime_timeout;
    std::chrono::system_clock::time_point uptime_reentry;

    MachineState()
    {
        value = 0;
        intr_cntr = 0;
        prev_intr_cntr = 0;
        uptime_timeout = std::chrono::high_resolution_clock::now();
        uptime_reentry = std::chrono::high_resolution_clock::now();
    }

    uint8_t isInterrupted()
    {
        return (intr_cntr != prev_intr_cntr);
    }

    void resetUptimeTimeout()
    {
        uptime_timeout = std::chrono::high_resolution_clock::now();
    }

    void resetUptimeReentry()
    {
        uptime_reentry = std::chrono::high_resolution_clock::now();
    }

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