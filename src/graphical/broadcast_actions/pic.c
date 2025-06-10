/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends a "pic" (player incantation) message to the graphical clients.
 *
 * This function constructs and broadcasts a message indicating the start of an
 * incantation at a specific position and level, including the IDs of all
 * participating players. The message format is: "pic <x> <y> <level> <id1>
 * <id2> ... <idN>\n"
 *
 * @param ctxt Pointer to the parsed server context used for broadcasting
 * messages.
 * @param player_list Pointer to the list of players involved in the
 * incantation.
 */
void send_pic(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_list_t *player_list)
{
    char *block;

    block = snprintf_alloc("pic %ld %ld %ld", player_list->player->pos.x,
        player_list->player->pos.y, player_list->player->level + 1);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
        block = NULL;
    }
    while (player_list) {
        block = snprintf_alloc(" %ld", player_list->player->id);
        if (block) {
            graphical_broadcast(ctxt, block);
            free(block);
            block = NULL;
        }
        player_list = player_list->next;
    }
    graphical_broadcast(ctxt, "\n");
}
