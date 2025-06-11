/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** msz
*/

#include "actions.h"

/**
 * @brief Sends the content of every map tile to the graphical client.
 *
 * This function iterates over all tiles in the map and calls `graph_bct`
 * for each tile, passing the coordinates as arguments. It is typically used
 * to provide a complete snapshot of the map's state to a graphical client.
 *
 * @param ctxt   Pointer to the parsed server context containing map
 * information.
 * @param client Pointer to the graphical client player structure.
 * @param args   Unused argument (for interface compatibility).
 */
void graph_mct(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED zap_srv_graph_args_t *args)
{
    zap_srv_graph_args_t args2;

    args2.nargs = 2;
    args2.is_signed = true;
    for (ssize_t i = 0; i < ctxt->map.x; ++i) {
        for (ssize_t j = 0; j < ctxt->map.x; ++j) {
            args2.ssize_a = i;
            args2.ssize_b = j;
            graph_bct(ctxt, client, &args2);
        }
    }
}
