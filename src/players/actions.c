/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#include "player_functions.h"
#include "actions_arr.h"

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
    bool ret;

    if (client->actions[i].action == ZAP_SRV_PL_NONE) {
        send_client("ko\n", &client->sock);
        return;
    }
    client->actions[i].count += 1;
    ret = action_ptrs[client->actions[i].action](ctxt, client,
        client->actions[i].arguments);
    if (client->actions[i].action == ZAP_SRV_PL_INCANTATION) {
        if (ret == false) {
            client->actions[i].count = 2;
            return;
        }
    }
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

    if (client->actions[i].action == ZAP_SRV_PL_INCANTATION &&
        client->actions[i].count < 2) {
        return;
    }
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
 * @brief Determines whether the player's action processing should continue.
 *
 * This function checks the current action of the player at the given index.
 * It returns true if:
 *   - The action at index 'i' is ZAP_SRV_PL_NONE (no action to process), or
 *   - The player is currently in an incantation, but the action at index 'i'
 *     is not an incantation action (ZAP_SRV_PL_INCANTATION).
 * Otherwise, it returns false, indicating that action processing should not
 * continue.
 *
 * @param client Pointer to the zap_srv_player_t structure representing the
 * player.
 * @param i Index of the action to check in the player's action list.
 * @return true if action processing should continue, false otherwise.
 */
static bool should_continue(zap_srv_player_t *client, size_t i)
{
    if (client->actions[i].action == ZAP_SRV_PL_NONE) {
        return true;
    }
    if (client->in_incantation &&
        client->actions[i].action != ZAP_SRV_PL_INCANTATION) {
        return true;
    }
    return false;
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
        if (should_continue(client, i))
            continue;
        if (client->actions[i].action == ZAP_SRV_PL_INCANTATION &&
            client->actions[i].count == 0)
            real_time = 0.0;
        else
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
 * @brief Checks if a player is alive based on their time units and food
 * inventory.
 *
 * This function determines whether the specified player (`client`) should be
 * marked as dead by comparing the current time with the player's allowed
 * lifetime, which is calculated using their birth time and time units. If the
 * player is dead and has no food left, it sends a "dead" message to the
 * client, notifies the server, decreases the team's player count, and
 * disconnects the client. If the player is dead but still has food, it
 * consumes one unit of food, extends the player's lifetime, marks them as
 * alive, and notifies the server of the inventory change.
 *
 * @param ctxt   Pointer to the parsed server context.
 * @param client Pointer to the player structure to check.
 * @param i      Index of the client in the server's player list.
 */
static void check_alive(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, UNUSED size_t i)
{
    double current_time = get_time();
    double real_time = client->birth_time +
        (client->time_units / (double)ctxt->server.frequency);

    if (client->dead)
        return;
    client->dead = current_time >= real_time;
    if (client->dead) {
        if (client->inventory[FOOD] <= 0) {
            send_client("dead\n", &client->sock);
            send_pdi(ctxt, client);
            decrease_team_count(ctxt, client->team);
            THROW(CEXTEND_EXCEPTION_SYSTEM_ERROR);
        }
        client->inventory[FOOD] -= 1;
        client->time_units += ZAP_SRV_FOOD_TIME_UNITS;
        client->dead = false;
        send_pin(ctxt, client);
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
void player_actions(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i)
{
    check_alive(ctxt, client, i);
    if (client->dead) {
        return;
    }
    consume_actions(ctxt, client);
    parse_buf(client);
}
