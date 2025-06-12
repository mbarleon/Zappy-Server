/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the current server frequency to a graphical client.
 *
 * This function formats and sends the server's frequency to the specified
 * graphical client using the "sgt" command. The frequency value is retrieved
 * from the parsed context. The message is dynamically allocated and freed
 * after being sent.
 *
 * @param ctxt Pointer to the parsed server context containing server
 * information.
 * @param client Pointer to the graphical client to which the frequency will be
 * sent.
 * @param args Unused graphical arguments.
 */
void graph_sgt(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED zap_srv_graph_args_t *args)
{
    char *block;

    block = snprintf_alloc("sgt %ld\n", ctxt->server.frequency / 100UL);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
