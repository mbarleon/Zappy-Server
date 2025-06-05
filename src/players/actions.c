/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#include "player_functions.h"

/**
 * @brief Array of function pointers for player actions.
 *
 * This static array holds pointers to functions that implement various player
 * actions.
 * Each function should take two parameters:
 *   - zap_srv_parsed_context_t *: Pointer to the parsed context of the server.
 *   - zap_srv_player_t *: Pointer to the player structure.
 *
 * @note The size of the array determines the number of supported actions.
 */
static void (* const action_ptrs[])(zap_srv_parsed_context_t *,
    zap_srv_player_t *) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/**
 * @brief Executes a specific action for a player based on their action queue.
 *
 * This function checks the player's action at the given index. If the action
 * is ZAP_SRV_PL_NONE or there is no corresponding function pointer in
 * action_ptrs, it sends a "ko" message to the client to indicate failure.
 * Otherwise, it executes the action by calling the appropriate function
 * pointer from action_ptrs.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player structure.
 * @param i Index of the action to execute in the player's action queue.
 */
static void do_action(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, size_t i)
{
    if (client->actions[i].action == ZAP_SRV_PL_NONE) {
        send_client("ko\n", &client->sock);
        return;
    }
    if (action_ptrs[client->actions[i].action] == NULL) {
        send_client("not implemented (ko)\n", &client->sock);
        return;
    }
    action_ptrs[client->actions[i].action](ctxt, client);
}

/**
 * @brief Removes an action from the player's action queue at the specified
 * index.
 *
 * This function frees the memory allocated for the arguments of the action at
 * index `i`, shifts all subsequent actions one position forward to fill the
 * gap, and resets the last action slot to indicate it is empty.
 *
 * @param client Pointer to the player structure whose action is to be removed.
 * @param i Index of the action to remove in the actions array.
 */
static void remove_action(zap_srv_player_t *client, size_t i)
{
    char *arg = client->actions[i].arguments;

    safe_free((void **)&arg);
    for (; i < ZAP_SRV_MAX_ACTIONS - 1; ++i) {
        client->actions[i].action = client->actions[i + 1].action;
        client->actions[i].timestamp = client->actions[i + 1].timestamp;
        client->actions[i].arguments = client->actions[i + 1].arguments;
    }
    client->actions[ZAP_SRV_MAX_ACTIONS - 1].action = ZAP_SRV_PL_NONE;
    client->actions[ZAP_SRV_MAX_ACTIONS - 1].arguments = NULL;
}

/**
 * @brief Consumes and executes pending player actions if their scheduled time
 * has elapsed.
 *
 * This function iterates through the player's action queue and checks if each
 * action's scheduled execution time (based on the server frequency and action
 * type) has passed. If so, it executes the action and removes it from the
 * queue.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player whose actions are being processed.
 */
static void consume_actions(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    double real_time;
    double action_timepoint;
    double current_time = get_time();

    for (size_t i = 0; i < ZAP_SRV_MAX_ACTIONS; ++i) {
        if (client->actions[i].action == ZAP_SRV_PL_NONE) {
            continue;
        }
        real_time = ((double)action_time[client->actions[i].action] /
            (double)ctxt->server.frequency);
        action_timepoint = (double)client->actions[i].timestamp;
        if (current_time >= action_timepoint + real_time) {
            do_action(ctxt, client, i);
            remove_action(client, i);
            i--;
        }
    }
}

/**
 * @brief Decreases the number of clients for a given team.
 *
 * This function searches for the team with the specified name in the context's
 * team list and decrements its client count by one.
 *
 * @param ctxt Pointer to the parsed server context containing the team list.
 * @param team Name of the team whose client count should be decreased.
 */
static void decrease_team_count(zap_srv_parsed_context_t *ctxt,
    const char *team)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, team) == 0) {
            tmp->num_clients -= 1;
            return;
        }
    }
}

/**
 * @brief Checks if a player is still alive based on their time units and the
 * server frequency.
 *
 * This function determines whether the specified player (`client`) has
 * exceeded their allowed lifetime by comparing the current time with the
 * calculated real time of death. If the player is dead, it sends a "dead"
 * message to the client, decreases the team's player count, and disconnects
 * the client from the server.
 *
 * @param ctxt Pointer to the parsed server context containing server and
 * client information.
 * @param client Pointer to the player structure to check for alive status.
 */
static void check_alive(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client)
{
    size_t client_nbr = 0;
    double current_time = get_time();
    double real_time = client->birth_time +
        (client->time_units / (double)ctxt->server.frequency);

    if (client->dead) {
        return;
    }
    client->dead = current_time >= real_time;
    if (client->dead) {
        send_client("dead\n", &client->sock);
        decrease_team_count(ctxt, client->team);
        for (; client_nbr < ZAP_SRV_MAX_CLIENTS &&
            ctxt->server.clients[client_nbr].id != client->id; ++client_nbr);
        if (client_nbr < ZAP_SRV_MAX_CLIENTS) {
            disconnect_client(&ctxt->server, client_nbr);
        }
    }
}

/**
 * @brief Handles the actions for a player by consuming their queued actions
 * and parsing their input buffer.
 *
 * This function processes the current actions of the specified player by
 * first consuming any pending actions and then parsing the player's input
 * buffer for new commands or data.
 *
 * @param ctxt   Pointer to the parsed server context structure.
 * @param client Pointer to the player structure whose actions are to be
 * handled.
 */
void player_actions(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    check_alive(ctxt, client);
    if (client->dead) {
        return;
    }
    consume_actions(ctxt, client);
    parse_buf(client);
}
