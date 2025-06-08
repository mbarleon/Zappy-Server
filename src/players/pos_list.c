/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pos_list
*/

#include "pos_list_internal.h"

/**
 * @brief Frees all nodes in a linked list of positions.
 *
 * This function iterates through the given linked list of type
 * zap_srv_pos_list_t, freeing each node to release allocated memory. After
 * calling this function, the list pointer will be invalid and should not be
 * used.
 *
 * @param list Pointer to the head of the linked list to be freed.
 */
void free_pos_list(zap_srv_pos_list_t *list)
{
    zap_srv_pos_list_t *tmp;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

/**
 * @brief Adds a new position to the beginning of a position list.
 *
 * This function allocates a new element for the position list, copies the
 * coordinates from the given position, and inserts the new element at the
 * head of the list.
 *
 * @param list Pointer to the pointer of the head of the position list.
 * @param pos Pointer to the position to be added to the list.
 *
 * @note If either @p list or @p pos is NULL, the function does nothing.
 * @note If memory allocation fails, an exception is thrown using
 * THROW(CEXTEND_EXCEPTION_BAD_ALLOC).
 */
void add_in_pos_list(zap_srv_pos_list_t **list, zap_srv_pos_t *pos)
{
    zap_srv_pos_list_t *new_elem;

    if (!list || !pos) {
        return;
    }
    new_elem = (zap_srv_pos_list_t *)malloc(sizeof(zap_srv_pos_list_t));
    if (!new_elem) {
        THROW(CEXTEND_EXCEPTION_BAD_ALLOC);
    }
    new_elem->pos.x = pos->x;
    new_elem->pos.y = pos->y;
    new_elem->next = *list;
    *list = new_elem;
}

/**
 * @brief Finds and returns a list of player positions, excluding "GRAPHIC"
 * clients.
 *
 * Iterates through all clients in the server context and adds the position of
 * each client whose team is not "GRAPHIC" to a position list. Returns the
 * constructed list of positions.
 *
 * @param ctxt Pointer to the parsed server context containing client
 * information.
 * @return zap_srv_pos_list_t* Pointer to the list of player positions, or NULL
 * if no players found.
 */
zap_srv_pos_list_t *find_players_positions(zap_srv_parsed_context_t *ctxt)
{
    zap_srv_pos_list_t *list = NULL;

    for (size_t i = 0; i < ctxt->server.num_clients; ++i) {
        if (strcmp("GRAPHIC", ctxt->server.clients[i].team) != 0) {
            add_in_pos_list(&list, &ctxt->server.clients[i].pos);
        }
    }
    return list;
}
