/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions_arr
*/

#ifndef ZAP_SRV_ACTIONS_ARR_H_
    #define ZAP_SRV_ACTIONS_ARR_H_
    #include "actions/actions.h"

/**
 * @brief Array of function pointers for player actions.
 *
 * This static array holds pointers to functions that implement various player
 * actions.
 * Each function should take two parameters:
 *   - zap_srv_parsed_context_t *: Pointer to the parsed context of the server.
 *   - zap_srv_player_t *: Pointer to the player structure.
 *
 * @note The size of the array determines the number of supported actions.
 */
static bool (* const action_ptrs[])(zap_srv_parsed_context_t *,
    zap_srv_player_t *, const char *) = {
    &player_forward,
    &player_right,
    &player_left,
    &player_look,
    &player_inventory,
    &player_broadcast,
    &player_connect_nbr,
    &player_fork,
    &player_eject,
    &player_take,
    &player_set,
    &player_incantation
};

#endif /* !ZAP_SRV_ACTIONS_ARR_H_ */
