/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions_time
*/

#include "player_actions.h"

/**
 * @brief Array containing the execution time (in arbitrary time units)
 * for each player action.
 *
 * Each element in the array corresponds to the time required to perform a
 * specific action by a player in the game. The index of the array matches the
 * action's identifier.
 */
const size_t action_time[] = {
    700,
    700,
    700,
    700,
    100,
    700,
    0,
    4200,
    700,
    700,
    700,
    30000
};

/**
 * @brief Retrieves the current time in seconds with nanosecond precision.
 *
 * This function uses clock_gettime with CLOCK_REALTIME to obtain the current
 * time. The result is returned as a double, representing the number of seconds
 * (including fractional seconds) since the Unix epoch (January 1, 1970).
 *
 * @return Current time in seconds as a double.
 */
double get_time(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
