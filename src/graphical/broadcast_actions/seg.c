/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** seg
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "seg" (end of game) message to all graphical clients.
 *
 * This function constructs and broadcasts a "seg" message, indicating the end
 * of the game, to all connected graphical clients. If a team is provided and
 * has not already been marked as having sent a "seg" message, it sends
 * "seg <team_name>\n" and marks the team as having sent the message. If no
 * team is provided, it sends "seg (null)\n".
 *
 * @param ctxt Pointer to the parsed server context.
 * @param team Pointer to the team structure, or NULL if no team is specified.
 */
void send_seg(zap_srv_parsed_context_t *ctxt, zap_srv_team_t *team)
{
    char *block;

    if (team) {
        if (team->seg) {
            return;
        }
        block = snprintf_alloc("seg %s\n", team->name);
        team->seg = true;
    } else {
        block = snprintf_alloc("seg (null)\n");
    }
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
