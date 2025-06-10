/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** set
*/

#include "actions.h"

/**
 * @brief Adds a new element to the elements list at the specified position.
 *
 * This function allocates a new zap_srv_elements_list_t node, initializes it
 * with the provided element, and inserts it at the beginning of the linked
 * list located at elements[pos->x][pos->y].
 *
 * @param elements A triple pointer to the 2D array of element lists.
 * @param pos Pointer to the position structure specifying the (x, y)
 * coordinates.
 * @param element The element to add to the list at the specified position.
 */
static void add_elem_at(zap_srv_elements_list_t ***elements,
    zap_srv_pos_t *pos, zap_srv_elements_t element)
{
    zap_srv_elements_list_t *new_elem = (zap_srv_elements_list_t *)safe_malloc(
            sizeof(zap_srv_elements_list_t), NULL);

    new_elem->element = element;
    new_elem->next = elements[pos->x][pos->y];
    elements[pos->x][pos->y] = new_elem;
}

/**
 * @brief Handles the "set" action for a player, allowing them to place an item
 * from their inventory onto the map.
 *
 * This function parses the element to be set from the given arguments, checks
 * if the player has at least one of the specified element (and that the
 * element is valid), and if so, removes one from the player's inventory and
 * adds it to the map at the player's position. It sends "ok\n" to the client
 * on success, or "ko\n" if the action is invalid or not possible.
 *
 * @param ctxt Pointer to the server context containing map and game state.
 * @param client Pointer to the player performing the action.
 * @param arguments String containing the name of the element to set.
 */
void player_set(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments)
{
    zap_srv_elements_t element = get_element_from_str(arguments);

    if (element == UNKNOWN_ELEMENT || client->inventory[element] <= 0) {
        send_client("ko\n", &client->sock);
    }
    client->inventory[element] -= 1;
    add_elem_at(ctxt->map.elements, &client->pos, element);
    send_client("ok\n", &client->sock);
    send_pin(ctxt, client);
}
