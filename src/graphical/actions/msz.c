/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the map size to a graphical client.
 *
 * This function formats and sends the current map dimensions (width and
 * height) to the specified graphical client in the format "msz <width>
 * <height>\n".
 *
 * @param ctxt Pointer to the parsed server context containing map information.
 * @param client Pointer to the graphical client to which the message will be
 * sent.
 * @param args Unused graphical arguments.
 */
void graph_msz(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED zap_srv_graph_args_t *args)
{
    char *block;

    block = snprintf_alloc("msz %ld %ld\n", ctxt->map.x, ctxt->map.y);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
