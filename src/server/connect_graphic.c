/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** connect_graphic
*/

#include "server_internal.h"

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

static void send_enw(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    for (zap_srv_team_t *tmp = ctxt->teams; tmp; tmp = tmp->next) {
        for (zap_srv_egg_t *tmp2 = tmp->eggs; tmp2; tmp2 = tmp2->next) {
            send_enw_line(tmp2, client);
        }
    }
}

static void send_tna(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
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

void send_graphic_connect_message(zap_srv_player_t *client,
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
    send_tna(ctxt, client);
    send_enw(ctxt, client);
}
