/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** create_egg
*/

#include "egg_internal.h"

/**
 * @brief Generates and returns a unique, incrementing index for eggs.
 *
 * This function maintains a static counter that is incremented each time
 * the function is called, ensuring that each call returns a unique index.
 *
 * @return The current egg index (starting from 0).
 */
static ssize_t egg_index(void)
{
    static ssize_t index = 0;

    index += 1;
    return index - 1;
}

/**
 * @brief Creates a new egg structure at the specified position for a given
 * player.
 *
 * Allocates and initializes a zap_srv_egg_t structure, setting its position,
 * associated player number, and assigning it a unique egg number.
 *
 * @param pos Pointer to a zap_srv_pos_t structure specifying the egg's
 * position.
 * @param player_number The identifier of the player associated with the egg.
 * @return Pointer to the newly created zap_srv_egg_t structure, or NULL on
 * allocation failure.
 */
zap_srv_egg_t *create_egg(zap_srv_pos_t *pos, ssize_t player_number)
{
    zap_srv_egg_t *egg = safe_calloc(1, sizeof(zap_srv_egg_t), NULL);

    egg->pos.x = pos->x;
    egg->pos.y = pos->y;
    egg->player_number = player_number;
    egg->number = egg_index();
    return egg;
}

/**
 * @brief Adds a new egg to the end of the egg list.
 *
 * This function creates a new egg with the specified position and player
 * number, and adds it to the begining of the egg list. If the egg list pointer
 * is NULL, the function does nothing.
 *
 * @param egg_list Pointer to the pointer of the head of the egg list.
 * @param pos Pointer to the position structure for the new egg.
 * @param player_number The player number associated with the new egg.
 */
void add_egg(zap_srv_egg_t **egg_list, zap_srv_pos_t *pos,
    ssize_t player_number)
{
    zap_srv_egg_t *new_egg;

    if (!egg_list) {
        return;
    }
    new_egg = create_egg(pos, player_number);
    new_egg->next = *egg_list;
    *egg_list = new_egg;
}
