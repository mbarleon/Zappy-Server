/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** inventory
*/

#include "actions.h"

/**
 * @brief Sends the player's inventory to the client.
 *
 * This function formats the player's inventory into a string and sends it to
 * the client through their socket. The inventory includes the quantities of
 * linemate, deraumere, sibur, mendiane, phiras, and thystame. The formatted
 * string is dynamically allocated and freed after sending.
 *
 * @param ctxt Unused parsed context parameter.
 * @param client Pointer to the player structure whose inventory will be sent.
 */
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
