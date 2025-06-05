/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** create_egg
*/

#include "egg_internal.h"

static ssize_t egg_index(void)
{
    static ssize_t index = 0;

    index += 1;
    return index - 1;
}

zap_srv_egg_t *create_egg(zap_srv_pos_t *pos, ssize_t player_number)
{
    zap_srv_egg_t *egg = safe_calloc(1, sizeof(zap_srv_egg_t), NULL);

    egg->pos.x = pos->x;
    egg->pos.y = pos->y;
    egg->player_number = player_number;
    egg->number = egg_index();
    return egg;
}

void add_egg(zap_srv_egg_t **egg_list, zap_srv_pos_t *pos,
    ssize_t player_number)
{
    zap_srv_egg_t *tmp;
    zap_srv_egg_t *new_egg;

    if (!egg_list) {
        return;
    }
    new_egg = create_egg(pos, player_number);
    if (!*egg_list) {
        *egg_list = new_egg;
        return;
    }
    for (tmp = *egg_list; tmp->next; tmp = tmp->next);
    if (tmp) {
        tmp->next = new_egg;
    }
}
