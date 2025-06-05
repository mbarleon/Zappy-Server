/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_client
*/

#include "server_internal.h"

static size_t count_team_len(const zap_srv_player_t *client)
{
    size_t i = 0;

    for (; client->buf[i] && client->buf[i] != '\n'; ++i);
    return i;
}

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

static size_t compute_slots_in_team(char *team, zap_srv_parsed_context_t *ctxt)
{
    if (strcmp(team, "GRAPHIC") == 0) {
        return 1;
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(team, tmp->name) == 0) {
            return tmp->max_clients - tmp->num_clients;
        }
    }
    return 0;
}

static void decrease_team_slots(char *team, zap_srv_parsed_context_t *ctxt)
{
    if (strcmp(team, "GRAPHIC") == 0) {
        return;
    }
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        if (strcmp(team, tmp->name) == 0) {
            tmp->num_clients += 1;
            return;
        }
    }
}

static void connect_client_err(zap_srv_player_t *client,
    zap_srv_string_entries_t error)
{
    CEXTEND_LOG(CEXTEND_LOG_WARNING, fetch_string(error),
        client->sock.fd, client->team);
    THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
}

static void send_player_connect_message(zap_srv_player_t *client,
    zap_srv_parsed_context_t *ctxt, size_t slots_in_team)
{
    char *block;

    block = snprintf_alloc("%ld\n%ld %ld\n", slots_in_team - 1, ctxt->map.x,
        ctxt->map.y);
    decrease_team_slots(client->team, ctxt);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
}

static void send_bct(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    size_t i, size_t j)
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

static void send_graphic_connect_message(zap_srv_player_t *client,
    zap_srv_parsed_context_t *ctxt)
{
    char *block;

    block = snprintf_alloc("msz %ld %ld\nsgt %ld\n", ctxt->map.x, ctxt->map.y,
        ctxt->server.frequency);
    if (block) {
        send_client(block, &client->sock);
        free(block);
    }
    for (size_t i = 0; i < ctxt->map.x; ++i) {
        for (size_t j = 0; j < ctxt->map.y; ++j) {
            send_bct(ctxt, client, i, j);
        }
    }
}

void connect_client(zap_srv_player_t *client, zap_srv_parsed_context_t *ctxt)
{
    size_t slots_in_team;
    size_t team_len = count_team_len(client);

    client->team = safe_calloc(team_len + 1, sizeof(char), NULL);
    memcpy(client->team, client->buf, team_len);
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
