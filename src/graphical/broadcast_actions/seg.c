/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** seg
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "seg" (end of game) message to all graphical clients for the
 * specified team.
 *
 * This function constructs and broadcasts a "seg" message indicating that the
 * specified team  won or the game has ended for them. It ensures the message
 * is only sent once per team by checking and setting the team's `seg` flag.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param team Pointer to the team.
 */
void send_seg(zap_srv_parsed_context_t *ctxt, zap_srv_team_t *team)
{
    char *block;

    if (team->seg) {
        return;
    }
    block = snprintf_alloc("seg %s\n", team->name);
    team->seg = true;
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
