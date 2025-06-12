/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_client
*/

#include "server_internal.h"


/**
 * @brief Returns the minimum of two size_t values.
 *
 * Compares the two input values and returns the smaller one.
 *
 * @param a First value to compare.
 * @param b Second value to compare.
 * @return The smaller of the two input values.
 */
static size_t my_min(size_t a, size_t b)
{
    return a < b ? a : b;
}

/**
 * @brief Generates and returns a unique, incrementing index value.
 *
 * This function maintains a static variable that is incremented each time
 * the function is called, ensuring that each call returns a unique index.
 *
 * @return The current index value before incrementing.
 */
static ssize_t get_index(void)
{
    static ssize_t id = 0;

    id += 1;
    return id - 1;
}

/**
 * @brief Counts the length of the team name in the client's buffer up to the
 * first newline character.
 *
 * This function iterates through the client's buffer ('client->buf') and
 * counts the number of characters until it encounters either a null terminator
 * ('\0') or a newline character ('\n'). The result is the length of the team
 * name or command present at the beginning of the buffer.
 *
 * @param client Pointer to a zap_srv_player_t structure representing the
 * client.
 * @return The length (in characters) of the team name or command before the
 * newline or null terminator.
 */
static size_t count_team_len(const zap_srv_player_t *client)
{
    size_t i = 0;

    for (; client->buf[i] && client->buf[i] != '\n'; ++i);
    return i;
}

/**
 * @brief Checks if a given team name exists in the server context.
 *
 * This function verifies whether the specified team name matches the special
 * "GRAPHIC" team or exists within the list of teams in the provided context.
 *
 * @param team The name of the team to check.
 * @param ctxt Pointer to the server context containing the list of teams.
 * @return true if the team exists (either "GRAPHIC" or found in the list),
 * false otherwise.
 */
static bool team_exists(char *team, zap_srv_parsed_context_t *ctxt)
{
    if (strcmp(team, "GRAPHIC") == 0) {
        return true;
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(team, tmp->name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Computes the number of available slots for a given team.
 *
 * This function checks if the provided team name matches "GRAPHIC".
 * If so, it returns 1 as the number of available slots. Otherwise,
 * it searches through the list of teams in the provided context to find
 * a team with a matching name and returns its available slots.
 * If the team is not found, it returns 0.
 *
 * @param team The name of the team to check.
 * @param ctxt The parsed server context containing the list of teams.
 * @return The number of available slots for the specified team, or 0 if not
 * found.
 */
static size_t compute_slots_in_team(char *team, zap_srv_parsed_context_t *ctxt)
{
    int cmp;

    if (strcmp(team, "GRAPHIC") == 0) {
        return 1;
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        cmp = strcmp(team, tmp->name);
        if (cmp != 0) {
            continue;
        }
        if (tmp->num_clients >= tmp->max_clients) {
            return 0;
        }
        return my_min(tmp->available_slots,
            tmp->max_clients - tmp->num_clients);
    }
    return 0;
}

/**
 * @brief Decreases the available slots for a given team and increments the
 * client count.
 *
 * This function checks if the specified team is not "GRAPHIC". If it is not,
 * it searches for the team in the context's team list. When found, it
 * increments the number of clients for that team, decrements the available
 * slots, and calls the hatch_egg function for the team.
 *
 * @param team The name of the team to update.
 * @param ctxt The server context containing the list of teams.
 */
static zap_srv_pos_t decrease_team_slots(char *team,
    zap_srv_parsed_context_t *ctxt)
{
    zap_srv_pos_t pos;

    if (strcmp(team, "GRAPHIC") == 0) {
        return (zap_srv_pos_t){0, 0};
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(team, tmp->name) == 0) {
            tmp->num_clients += 1;
            tmp->available_slots -= 1;
            pos = hatch_egg(ctxt, team);
            return pos;
        }
    }
    return (zap_srv_pos_t){0, 0};
}

/**
 * @brief Handles client connection errors by logging a warning and throwing an
 * exception.
 *
 * This function logs a warning message with the provided error string, the
 * client's socket file descriptor, and the client's team. After logging,
 * it throws an invalid argument exception to indicate an error during the
 * client connection process.
 *
 * @param client Pointer to the client structure representing the player
 * attempting to connect.
 * @param error  Error string entry indicating the reason for the connection
 * failure.
 */
static void connect_client_err(zap_srv_player_t *client,
    zap_srv_string_entries_t error)
{
    CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(error),
        client->sock.fd, client->team);
    THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
}

/**
 * @brief Sends a connection message to a newly connected player and updates
 * team slots.
 *
 * This function constructs and sends a message to the specified player client
 * upon connection. The message includes the number of available slots left in
 * the player's team (after this connection), and the dimensions of the game
 * map. It then decreases the available slots for the team, sends the
 * constructed message to the client, and assigns a unique ID to the player.
 *
 * @param client Pointer to the player structure representing the connected
 * client.
 * @param ctxt Pointer to the parsed context containing map information.
 * @param slots_in_team The current number of available slots in the player's
 * team before connection.
 */
static void send_player_connect_message(zap_srv_player_t *client,
    zap_srv_parsed_context_t *ctxt, size_t slots_in_team)
{
    char *block;
    zap_srv_pos_t pos;

    block = snprintf_alloc("%ld\n%ld %ld\n", slots_in_team - 1, ctxt->map.x,
        ctxt->map.y);
    pos = decrease_team_slots(client->team, ctxt);
    client->pos.x = pos.x;
    client->pos.y = pos.y;
    client->id = get_index();
    send_pnw(ctxt, client);
    send_pin(ctxt, client);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
    client->birth_time = get_time();
    client->in_incantation = false;
    client->player_list = NULL;
}

/**
 * @brief Handles the connection of a client to the server, assigning them to a
 * team.
 *
 * This function processes a client's request to join a team. It allocates
 * memory for the team name, checks if the requested team exists, and verifies
 * if there are available slots in the team. If the team does not exist or is
 * full, an error is sent to the client. Otherwise, the client is connected to
 * the team, and appropriate connection messages are sent depending on whether
 * the client is a graphic client or a regular player.
 *
 * @param client Pointer to the client structure representing the connecting
 * player.
 * @param ctxt Pointer to the parsed server context containing team and game
 * state information.
 */
void connect_client(zap_srv_player_t *client, zap_srv_parsed_context_t *ctxt)
{
    size_t slots_in_team;
    size_t team_len = count_team_len(client);

    client->team = safe_calloc(team_len + 1, sizeof(char), NULL);
    memcpy(client->team, client->buf, team_len);
    memset(client->buf, 0, client->buf_size);
    if (!team_exists(client->team, ctxt)) {
        connect_client_err(client, ZAP_SRV_JOIN_TEAM_ERR);
    }
    slots_in_team = compute_slots_in_team(client->team, ctxt);
    if (slots_in_team <= 0) {
        connect_client_err(client, ZAP_SRV_JOIN_FULL_TEAM);
    }
    CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_JOIN_TEAM),
        client->sock.fd, client->team);
    if (strcmp(client->team, "GRAPHIC") == 0) {
        send_graphic_connect_message(client, ctxt);
    } else {
        send_player_connect_message(client, ctxt, slots_in_team);
    }
}
