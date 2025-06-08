/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** look
*/

#include "actions.h"
#include "../pos_list.h"

/**
 * @brief Calculates the map position relative to a player's orientation and
 * position.
 *
 * This function computes the absolute position on the map based on the
 * player's current position, orientation, and the given offsets (i, j). The
 * calculation wraps around the map boundaries using modulo arithmetic to
 * ensure positions remain within the map.
 *
 * @param client Pointer to the player structure containing current position
 * and orientation.
 * @param map Pointer to the map structure containing map dimensions.
 * @param i Offset along the player's forward/backward axis.
 * @param j Offset along the player's left/right axis.
 * @return zap_srv_pos_t The calculated map position after applying orientation
 * and offsets.
 */
static zap_srv_pos_t get_position(zap_srv_player_t *client, zap_srv_map_t *map,
    ssize_t i, ssize_t j)
{
    zap_srv_pos_t pos = client->pos;

    switch (client->orientation) {
        case NORTH:
            return (zap_srv_pos_t){(client->pos.x - i + map->x) % map->x,
                (client->pos.y + j + map->y) % map->y};
        case SOUTH:
            return (zap_srv_pos_t){(client->pos.x + i + map->x) % map->x,
                (client->pos.y - j + map->y) % map->y};
        case EAST:
            return (zap_srv_pos_t){(client->pos.x + j + map->x) % map->x,
                (client->pos.y + i + map->y) % map->y};
        case WEST:
            return (zap_srv_pos_t){(client->pos.x - j + map->x) % map->x,
                (client->pos.y - i + map->y) % map->y};
        default:
            return pos;
    }
}

/**
 * @brief Appends the string 'src' to the end of the string pointed to by
 * 'dest'.
 *
 * If '*dest' is NULL, this function duplicates 'src' and assigns it to
 * '*dest'. Otherwise, it reallocates memory for '*dest' to fit the
 * concatenated result, appends 'src' to the end of '*dest', and ensures the
 * result is null-terminated.
 *
 * @param dest Pointer to a char pointer representing the destination string.
 * May be NULL or point to a dynamically allocated string.
 * @param src The source string to append. Must not be NULL.
 *
 * @note If memory allocation fails, '*dest' remains unchanged.
 */
static void add_to_string(char **dest, const char *src)
{
    char *tmp;
    size_t src_len;
    size_t dest_len;

    if (!dest || !src) {
        return;
    }
    if (!*dest) {
        *dest = strdup(src);
        return;
    }
    src_len = strlen(src);
    dest_len = strlen(*dest);
    tmp = realloc(*dest, sizeof(char) * (dest_len + src_len + 1));
    if (!tmp) {
        return;
    }
    *dest = tmp;
    memcpy(&(*dest)[dest_len], src, src_len + 1);
}

/**
 * @brief Adds information about players at a specific position to a buffer.
 *
 * Iterates through a linked list of player positions and, for each player
 * whose position matches the specified position, appends the string "player"
 * to the provided buffer. If multiple players are found at the same position,
 * they are separated by a space.
 *
 * @param buf Pointer to the buffer where player information will be appended.
 * @param pos Pointer to the position to match against player positions.
 * @param players Pointer to the head of the linked list of player positions.
 * @return The number of players found at the specified position.
 */
static size_t add_players(char **buf, zap_srv_pos_t *pos,
    zap_srv_pos_list_t *players)
{
    size_t nelems = 0;

    for (; players; players = players->next) {
        if (players->pos.x != pos->x || players->pos.y != pos->y) {
            continue;
        }
        if (nelems) {
            add_to_string(buf, " ");
        }
        add_to_string(buf, "player");
        ++nelems;
    }
    return nelems;
}

/**
 * @brief Adds the string representations of items at a given position to a
 * buffer.
 *
 * This function iterates through a linked list of elements located at the
 * specified position (`pos`) in a 2D array of element lists (`elements`).
 * For each element, it appends its string representation to the provided
 * buffer (`buf`). If `nelems` is non-zero, a space is added before the element
 * string to separate items.
 *
 * @param buf Pointer to the buffer where item strings will be appended.
 * @param pos Pointer to the position structure specifying the coordinates in
 * the elements array.
 * @param elements 2D array of pointers to linked lists of elements.
 * @param nelems Number of elements already added to the buffer (used for
 * formatting).
 */
static void add_items(char **buf, zap_srv_pos_t *pos,
    zap_srv_elements_list_t ***elements, size_t nelems)
{
    zap_srv_elements_list_t *list = elements[pos->x][pos->y];

    for (; list; list = list->next) {
        if (nelems) {
            add_to_string(buf, " ");
        }
        add_to_string(buf, get_elements_str(list->element));
        ++nelems;
    }
}

/**
 * @brief Finalizes the "look" action for a player by sending the accumulated
 * buffer to the client, cleaning up resources, and freeing memory.
 *
 * This function appends the closing bracket and newline to the buffer,
 * sends the buffer to the client associated with the given socket,
 * frees the list of positions, and then frees the buffer itself.
 *
 * @param buf Pointer to the buffer containing the look response to send.
 * The buffer will be freed by this function.
 * @param sock Pointer to the client's socket structure.
 * @param positions Pointer to the list of positions to be freed.
 */
static void end_player_look(char **buf, zap_srv_socket_t *sock,
    zap_srv_pos_list_t *positions)
{
    add_to_string(buf, "]\n");
    send_client(*buf, sock);
    free_pos_list(positions);
    free(*buf);
}

/**
 * @brief Handles the "look" action for a player, generating a string
 * representation of the visible map tiles and entities around the player based
 * on their level.
 *
 * This function constructs a response string containing the items and players
 * visible to the player within their field of view, determined by their
 * current level. The response is formatted and sent to the client. If memory
 * allocation fails, an error message ("ko") is sent instead.
 *
 * @param ctxt   Pointer to the parsed server context containing map and game
 * state.
 * @param client Pointer to the player structure representing the client
 * issuing the look command.
 * @param arguments Unused arguments for the function.
 */
void player_look(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    UNUSED const char *arguments)
{
    zap_srv_pos_t pos;
    char *buf = strdup("[");
    const char *end_char = NULL;
    zap_srv_pos_list_t *positions = find_players_positions(ctxt);

    if (!buf) {
        send_client("ko", &client->sock);
        return;
    }
    for (ssize_t i = 0; i <= client->level; ++i) {
        for (ssize_t j = -i; j <= i; ++j) {
            add_to_string(&buf, end_char);
            end_char = ",";
            pos = get_position(client, &ctxt->map, i, j);
            add_items(&buf, &pos, ctxt->map.elements,
                add_players(&buf, &pos, positions));
        }
    }
    end_player_look(&buf, &client->sock, positions);
}
