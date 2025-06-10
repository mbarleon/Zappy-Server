/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the content of a map block to a graphical client.
 *
 * This function constructs and sends a message to the specified graphical
 * client containing the quantities of each element present at a specific
 * position on the map. The message follows the "bct" protocol format,
 * including the position and the count of each element type.
 *
 * @param ctxt Pointer to the parsed server context containing the map and its
 * elements.
 * @param client Pointer to the graphical client to which the message will be
 * sent.
 * @param args Pointer to the arguments specifying the position (ssize_a,
 * ssize_b) on the map.
 */
void graph_bct(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_graph_args_t *args)
{
    char *block;
    size_t quantity_table[ZAP_SRV_ELEMENTS_QUANTITY] = {0};

    if (args->ssize_a < 0 || args->ssize_a >= ctxt->map.x ||
        args->ssize_b < 0 || args->ssize_b >= ctxt->map.y) {
        send_client("sbp\n", &client->sock);
        return;
    }
    for (const zap_srv_elements_list_t *tmp = ctxt->map.elements[args->ssize_a]
        [args->ssize_b]; tmp; tmp = tmp->next) {
        quantity_table[tmp->element] += 1;
    }
    block = snprintf_alloc("bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        args->ssize_a, args->ssize_b, quantity_table[0], quantity_table[1],
        quantity_table[2], quantity_table[3], quantity_table[4],
        quantity_table[5], quantity_table[6]);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
