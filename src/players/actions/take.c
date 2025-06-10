/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** take
*/

#include "actions.h"

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
 * @brief Handles the "take" action for a player, allowing them to pick up an
 * element from their current position.
 *
 * This function attempts to remove the specified element from the map at the
 * player's current position. If successful, it updates the player's inventory
 * and sends an "ok" response to the client. If the element cannot be taken,
 * it sends a "ko" response to the client.
 *
 * @param ctxt Pointer to the server context containing map and game state.
 * @param client Pointer to the player performing the action.
 * @param arguments String representing the element the player wants to take.
 */
void player_take(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *arguments)
{
    zap_srv_elements_t element = get_element_from_str(arguments);

    if (remove_element_at(ctxt->map.elements, &client->pos, element) ==
        ZAP_SRV_SUCCESS) {
        client->inventory[element] += 1;
        send_client("ok\n", &client->sock);
        send_pin(ctxt, client);
        return;
    }
    send_client("ko\n", &client->sock);
}
