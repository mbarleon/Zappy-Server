/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** bct
*/

#include "../graphical_internal.h"

/**
 * @brief Sends the "bct" command to all graphical clients with the resource
 * quantities at a given map position.
 *
 * This function calculates the quantity of each resource element present at
 * the specified position on the map and formats a message according to the
 * "bct" protocol command. The message is then broadcasted to all connected
 * graphical clients.
 *
 * @param ctxt Pointer to the parsed server context containing the map and
 * graphical client information.
 * @param pos Pointer to the position structure specifying the x and y
 * coordinates on the map.
 */
void send_bct(zap_srv_parsed_context_t *ctxt, zap_srv_pos_t *pos)
{
    char *block;
    size_t quantity_table[ZAP_SRV_ELEMENTS_QUANTITY] = {0};

    for (const zap_srv_elements_list_t *tmp =
        ctxt->map.elements[pos->x][pos->y]; tmp; tmp = tmp->next) {
        quantity_table[tmp->element] += 1;
    }
    block = snprintf_alloc("bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", pos->x,
        pos->y, quantity_table[0], quantity_table[1], quantity_table[2],
        quantity_table[3], quantity_table[4], quantity_table[5],
        quantity_table[6]);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
