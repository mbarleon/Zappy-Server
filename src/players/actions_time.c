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
    7,
    7,
    7,
    7,
    1,
    7,
    0,
    42,
    7,
    7,
    7,
    300
};

double get_time(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
