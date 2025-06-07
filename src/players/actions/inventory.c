/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** inventory
*/

#include "actions.h"

void player_inventory(__attribute__((unused))zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("[linemate %ld, deraumere %ld, sibur %ld, "
        "mendiane %ld, phiras %ld, thystame %ld]\n",
        client->inventory[LINEMATE], client->inventory[DERAUMERE],
        client->inventory[SIBUR], client->inventory[MENDIANE],
        client->inventory[PHIRAS], client->inventory[THYSTAME]);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}
