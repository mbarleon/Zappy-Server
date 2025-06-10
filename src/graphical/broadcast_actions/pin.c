/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pdi
*/

#include "../graphical_internal.h"

/**
 * @brief Sends the inventory information of a player to all graphical clients.
 *
 * Constructs a formatted string containing the player's ID, position (x, y),
 * and the quantities of each inventory resource, then broadcasts this string
 * to all connected graphical clients.
 *
 * The format of the message is:
 * "pin #<id> <x> <y> <food> <linemate> <deraumere> <sibur> <mendiane> <phiras>
 * <thystame>\n"
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the player whose inventory is being sent.
 */
void send_pin(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pin #%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        client->id, client->pos.x, client->pos.y, client->inventory[FOOD],
        client->inventory[LINEMATE], client->inventory[DERAUMERE],
        client->inventory[SIBUR], client->inventory[MENDIANE],
        client->inventory[PHIRAS], client->inventory[THYSTAME]);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
