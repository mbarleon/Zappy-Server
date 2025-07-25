/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_graphic
*/

#include "server_internal.h"

/**
 * @brief Sends detailed information about a player to a graphic client.
 *
 * This function formats and sends the following information about a player:
 * - Player new (pnw): ID, position (x, y), orientation, level, team name.
 * - Player inventory (pin): ID, position (x, y), and inventory counts for each
 *   resource type.
 * - Player level (plv): ID and level.
 *
 * The information is sent as formatted strings to the specified client socket.
 *
 * @param player Pointer to the player whose information will be sent.
 * @param client Pointer to the client (graphic client) that will receive the
 * information.
 */
static void send_player_infos(zap_srv_player_t *player,
    zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("pnw #%ld %ld %ld %d %ld %s\npin #%ld %ld %ld %ld "
        "%ld %ld %ld %ld %ld %ld\nplv #%ld %ld\n", player->id, player->pos.x,
        player->pos.y, player->orientation, player->level, player->team,
        player->id, player->pos.x, player->pos.y, player->inventory[FOOD],
        player->inventory[LINEMATE], player->inventory[DERAUMERE],
        player->inventory[SIBUR], player->inventory[MENDIANE],
        player->inventory[PHIRAS], player->inventory[THYSTAME], player->id,
        player->level);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

/**
 * @brief Sends player information to a specific client for all non-graphic
 * clients.
 *
 * Iterates through all connected clients on the server. For each client whose
 * team is not "GRAPHIC", it sends their player information to the specified
 * client.
 *
 * @param ctxt   Pointer to the parsed server context containing server and
 * client data.
 * @param client Pointer to the client to whom the player information will be
 * sent.
 */
static void my_send_pnw(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0) {
            send_player_infos(&(ctxt->server.clients[i]), client);
        }
    }
}

/**
 * @brief Sends an "enw" message to a graphic client with egg information.
 *
 * This function formats and sends a message containing information about an
 * egg (number, player number, and position) to the specified graphic client.
 *
 * @param tmp2 Pointer to the egg structure containing egg details.
 * @param client Pointer to the graphic client to which the message will be
 * sent.
 */
static void send_enw_line(zap_srv_egg_t *tmp2, zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("enw #%ld #%ld %ld %ld\n", tmp2->number,
        tmp2->player_number, tmp2->pos.x, tmp2->pos.y);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

/**
 * @brief Sends information about all eggs to a specific graphic client.
 *
 * Iterates through all teams and their associated eggs, sending each egg's
 * information to the specified graphic client using the send_enw_line
 * function.
 *
 * @param ctxt   Pointer to the parsed server context containing teams and
 * eggs.
 * @param client Pointer to the graphic client to which the egg information
 * will be sent.
 */
static void my_send_enw(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        for (zap_srv_egg_t *tmp2 = tmp->eggs; tmp2; tmp2 = tmp2->next) {
            send_enw_line(tmp2, client);
        }
    }
}

/**
 * @brief Sends the team name announcement ("tna") message for each team to the
 * specified client.
 *
 * Iterates through all teams in the server context and sends a formatted "tna
 * <team_name>\n" message to the given client socket. Each message is
 * dynamically allocated and freed after sending.
 *
 * @param ctxt   Pointer to the parsed server context containing the list of
 * teams.
 * @param client Pointer to the client player structure to which the messages
 * will be sent.
 */
static void my_send_tna(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    char *block;

    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        block = snprintf_alloc("tna %s\n", tmp->name);
        if (block) {
            send_client(block, &client->sock);
            free(block);
        }
    }
}

/**
 * @brief Sends the content of a specific map block to a graphical client.
 *
 * This function constructs and sends a "bct" message to the specified client,
 * containing the coordinates (i, j) of the map block and the quantities of
 * each element present at that location. The quantities are determined by
 * iterating through the linked list of elements at the given map coordinates
 * and counting each type.
 *
 * @param ctxt Pointer to the parsed server context containing the map and its
 * elements.
 * @param client Pointer to the graphical client to which the message will be
 * sent.
 * @param i The x-coordinate of the map block.
 * @param j The y-coordinate of the map block.
 */
static void my_send_bct(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, ssize_t i, ssize_t j)
{
    char *block;
    size_t quantity_table[ZAP_SRV_ELEMENTS_QUANTITY] = {0};

    for (const zap_srv_elements_list_t *tmp = ctxt->map.elements[i][j]; tmp;
        tmp = tmp->next) {
        quantity_table[tmp->element] += 1;
    }
    block = snprintf_alloc("bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", i, j,
        quantity_table[0], quantity_table[1], quantity_table[2],
        quantity_table[3], quantity_table[4], quantity_table[5],
        quantity_table[6]);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

/**
 * @brief Sends the initial connection messages to a graphic client.
 *
 * This function sends the map size, server frequency, and the current state
 * of each map cell to the newly connected graphic client. It also sends
 * team names and egg information.
 *
 * @param client Pointer to the graphic client structure.
 * @param ctxt Pointer to the parsed server context containing map and server
 * information.
 */
void send_graphic_connect_message(zap_srv_player_t *client,
    zap_srv_parsed_context_t *ctxt)
{
    char *block;

    block = snprintf_alloc("msz %ld %ld\nsgt %ld\n", ctxt->map.x, ctxt->map.y,
        ctxt->server.frequency / 100UL);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
    for (ssize_t i = 0; i < ctxt->map.x; ++i) {
        for (ssize_t j = 0; j < ctxt->map.y; ++j) {
            my_send_bct(ctxt, client, i, j);
        }
    }
    my_send_pnw(ctxt, client);
    my_send_tna(ctxt, client);
    my_send_enw(ctxt, client);
}
