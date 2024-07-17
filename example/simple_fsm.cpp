/**
 * @file simple_fsm.cpp
 *
 * @brief This file contains the example of how to do with MachineState class.
 * @brief The basic usage of these MachineState, you must have 3 kind of things on each state, there are input, outpu, and action
 * @brief The input is the condition that what the trigger for another state going into current state
 * @brief The output is the condition that what the trigger for current state going into another state
 * @brief The action is the action that you want to do with your state
 *
 *
 * @code{.cpp}
 * #include "simple_fsm.h"
 *
 * int main()
 * {
 *   // Declare MachineState object
 *   MachineState state;
 *
 *   state.reentry(0,0.04)
 *
 *   switch (state.value)
 *   {
 *      case 0:
 *      // You can do something here
 *      state.timeout(1, 0.04);
 *      break;
 *
 *      case 1:
 *      state.value = 2;
 *      // You can do something here
 *      break;
 *
 *      default:
 *      break;
 *   }
 *   return 0;
 * }
 * @endcode
 */

#include "simple_fsm.h"

int main()
{
    /* Declare MachineState object */
    MachineState state;
    state.value = 1;
    state.intr_cntr = 0;
    state.prev_intr_cntr = 0;
    state.uptime_timeout = std::chrono::high_resolution_clock::now();
    state.uptime_reentry = std::chrono::high_resolution_clock::now();

    switch (state.value)
    {
    case 1:
        // You can do something here
        break;
    case 2:
        // You can do something here
        break;
    default:
        break;
    }

    return 0;
}