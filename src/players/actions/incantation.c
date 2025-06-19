/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** incantation
*/

#include "actions.h"

/**
 * requirements - A 2D array representing the resource and player requirements
 * for each level of incantation in the game.
 *
 * Each row corresponds to a level (from 1 to 7), and each column represents:
 *   [0] - Number of players required
 *   [1] - Number of 'linemate' resources required
 *   [2] - Number of 'deraumere' resources required
 *   [3] - Number of 'sibur' resources required
 *   [4] - Number of 'mendiane' resources required
 *   [5] - Number of 'phiras' resources required
 *   [6] - Number of 'thystame' resources required
 *
 * Example:
 *   requirements[level][resource_type]
 *   - requirements[0] = {1, 1, 0, 0, 0, 0, 0} // Level 1 requirements
 */
static const size_t requirements[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

/**
 * @brief Checks if the requirements for a specific level are met at the
 * player's current position.
 *
 * This function verifies whether the current tile contains the required number
 * of elements and the correct number of players at the specified level,
 * according to the game's rules.
 *
 * @param ctxt Pointer to the parsed server context, containing map and server
 * state.
 * @param level The level to check requirements for (must be between 2 and 8
 * inclusive).
 * @return true if all requirements for the given level are met, false
 * otherwise.
 */
static bool meets_requirements(zap_srv_parsed_context_t *ctx,
    zap_srv_pos_t *pos, ssize_t level)
{
    size_t nplayers = 0;
    size_t quantity_table[ZAP_SRV_ELEMENTS_QUANTITY] = {0};

    if (level < 2 || level > 8)
        return false;
    for (const zap_srv_elements_list_t *tmp =
        ctx->map.elements[pos->x][pos->y]; tmp; tmp = tmp->next) {
        quantity_table[tmp->element] += 1;
    }
    for (size_t i = 0; i < ctx->server.num_clients; ++i)
        if (ctx->server.clients[i].team && strcmp("GRAPHIC", ctx->server.
            clients[i].team) != 0 && ctx->server.clients[i].level == level - 1)
            nplayers++;
    if (nplayers < requirements[level - 2][0])
        return false;
    for (size_t i = 1; i < 7; ++i) {
        if (quantity_table[i] < requirements[level - 2][i])
            return false;
    }
    return true;
}

/**
 * @brief Adds a player to the beginning of a player list.
 *
 * This function allocates a new list entry for the given player and inserts it
 * at the head of the specified player list. If the player list pointer is
 * NULL, the function does nothing.
 *
 * @param player_list Double pointer to the head of the player list.
 * @param client Pointer to the player to be added to the list.
 */
static void push_to_player_list(zap_srv_player_list_t **player_list,
    zap_srv_player_t *client)
{
    zap_srv_player_list_t *entry;

    if (!player_list) {
        return;
    }
    entry =
        (zap_srv_player_list_t *)safe_malloc(sizeof(zap_srv_player_list_t),
        NULL);
    entry->player = client;
    entry->next = *player_list;
    *player_list = entry;
}

/**
 * @brief Initiates the incantation process for a player and other eligible
 * players at the same level.
 *
 * This function searches through all connected clients to find players who
 * are:
 *   - Not part of the "GRAPHIC" team,
 *   - At the same level as the initiating player,
 *   - Not the initiating player themselves.
 *
 * Eligible players are added to a temporary player list, marked as
 * participating in the incantation, and notified that the elevation is
 * underway. The initiating player is also added to the list, marked as
 * participating, and notified. Finally, a PIC (Player Incantation
 * Commencement) message is sent to inform about the incantation event.
 *
 * @param ctxt   Pointer to the parsed server context containing client and
 * server information.
 * @param client Pointer to the player initiating the incantation.
 */
static void start_incantation(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    zap_srv_player_list_t *player_list = NULL;

    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (ctxt->server.clients[i].team &&
            strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0 &&
            ctxt->server.clients[i].level == client->level &&
            ctxt->server.clients[i].id != client->id) {
            push_to_player_list(&player_list, &(ctxt->server.clients[i]));
            ctxt->server.clients[i].in_incantation = true;
            send_client("Elevation underway\n",
                &(ctxt->server.clients[i].sock));
        }
    }
    push_to_player_list(&player_list, client);
    client->player_list = (void *)player_list;
    client->in_incantation = true;
    send_client("Elevation underway\n", &client->sock);
    send_pic(ctxt, player_list);
}

/**
 * @brief Sends the current level of the specified player to the client and
 * updates the player's level view.
 *
 * This function formats and sends a message indicating the player's current
 * level to the client socket. It then calls send_plv to update the player's
 * level view in the context.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the player structure whose level is to be sent.
 */
static void send_current_level(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    char *block;

    block = snprintf_alloc("Current level: %ld\n", client->level);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
    send_plv(ctxt, client);
}

/**
 * @brief Removes the first occurrence of a specified element from a linked
 * list at a given position in a 2D array of element lists.
 *
 * This function searches for the first node containing the specified element
 * in the linked list located at elements[pos->x][pos->y]. If found, it removes
 * the node from the list, frees its memory, and returns ZAP_SRV_SUCCESS.
 * If the element is not found, the function returns ZAP_SRV_ERROR.
 *
 * @param elements A triple pointer to the 2D array of linked lists of
 * elements.
 * @param pos Pointer to the position structure specifying the (x, y)
 * coordinates.
 * @param element The element to remove from the list.
 * @return int ZAP_SRV_SUCCESS if the element was removed, ZAP_SRV_ERROR
 * otherwise.
 */
static int remove_element_at(zap_srv_elements_list_t ***elements,
    zap_srv_pos_t *pos, zap_srv_elements_t element)
{
    zap_srv_elements_list_t *prev = NULL;
    zap_srv_elements_list_t *list = elements[pos->x][pos->y];

    for (; list; list = list->next) {
        if (list->element != element) {
            prev = list;
            continue;
        }
        if (!prev) {
            elements[pos->x][pos->y] = list->next;
        } else {
            prev->next = list->next;
        }
        safe_free((void **)&list);
        return ZAP_SRV_SUCCESS;
    }
    return ZAP_SRV_ERROR;
}

/**
 * @brief Consumes the required elements from the map at the player's position
 * for an incantation.
 *
 * This function iterates through the list of required elements for the
 * player's current level (excluding food), and removes the specified quantity
 * of each element from the map at the player's current position. After all
 * required elements are consumed, it sends an updated block content message to
 * notify clients of the change.
 *
 * @param ctxt Pointer to the parsed server context containing the map and
 * other game state.
 * @param client Pointer to the player performing the incantation.
 */
static void consume_elements(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    for (size_t i = 1; i < 7; ++i) {
        for (size_t j = 0; j < requirements[client->level - 2][i]; ++j) {
            remove_element_at(ctxt->map.elements, &client->pos,
                (zap_srv_elements_t)i);
        }
    }
    send_bct(ctxt, &client->pos);
}

/**
 * @brief Ends the incantation process for a group of players.
 *
 * This function finalizes an incantation action for all players involved,
 * updating their state and notifying them of the result. If the incantation
 * was successful (`worked` is true), each player's level is incremented and
 * their new level is sent to them. If unsuccessful, a "ko" message is sent.
 * The function also frees the player list associated with the incantation,
 * resets the player's incantation state, sends the PIE event, and consumes
 * the required elements.
 *
 * @param ctxt   The server context containing parsed information.
 * @param client The player who initiated the incantation.
 * @param worked Indicates whether the incantation was successful.
 */
static void end_incantation(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, bool worked)
{
    zap_srv_player_list_t *tmp;
    zap_srv_player_list_t *player_list =
        (zap_srv_player_list_t *)client->player_list;

    while (player_list) {
        player_list->player->in_incantation = false;
        if (worked) {
            player_list->player->level += 1;
            send_current_level(ctxt, player_list->player);
        } else {
            send_client("ko\n", &player_list->player->sock);
        }
        tmp = player_list;
        player_list = player_list->next;
        safe_free((void **)&tmp);
    }
    client->player_list = NULL;
    send_pie(ctxt, client, worked);
    if (worked && client->level >= 2)
        consume_elements(ctxt, client);
}

/**
 * @brief Handles the incantation action for a player.
 *
 * This function checks if the player meets the requirements to perform an
 * incantation to reach the next level. If the requirements are not met and the
 * player is already in an incantation, it ends the incantation with failure.
 * If the requirements are not met and the player is not in an incantation, it
 * sends a failure message to the client. If the requirements are met and the
 * player is already in an incantation, it ends the incantation with success.
 * Otherwise, it starts a new incantation for the player.
 *
 * @param ctxt Pointer to the server context.
 * @param client Pointer to the player structure.
 * @param arguments Unused command arguments.
 * @return true if the incantation was started or successfully ended, false
 * otherwise.
 */
bool player_incantation(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, UNUSED const char *arguments)
{
    bool meet_req = meets_requirements(ctxt, &client->pos, client->level + 1);

    if (!meet_req) {
        if (client->in_incantation) {
            end_incantation(ctxt, client, false);
            return false;
        }
        send_client("ko\n", &client->sock);
        return false;
    }
    if (client->in_incantation) {
        end_incantation(ctxt, client, true);
        return true;
    }
    start_incantation(ctxt, client);
    return true;
}
