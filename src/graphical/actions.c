/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** actions
*/

#include "actions/actions.h"

/**
 * Array of authorized command strings for the graphical interface.
 *
 * Each string in this array represents a valid command that can be processed
 * by the graphical subsystem of the server. The array is terminated by a NULL
 * pointer to indicate the end of the list.
 *
 * Commands:
 * - "msz"  : Get map size
 * - "bct " : Get content of a map tile
 * - "mct"  : Get content of the whole map
 * - "tna"  : Get team names
 * - "ppo " : Get player position
 * - "plv " : Get player level
 * - "pin " : Get player inventory
 * - "sgt"  : Get current time unit
 * - "sst " : Set time unit
 */
const char *authorized_strings[] = {
    "msz",
    "bct ",
    "mct",
    "tna",
    "ppo ",
    "plv ",
    "pin ",
    "sgt",
    "sst ",
    NULL
};

/**
 * @brief Array of function pointers to graphical action handlers.
 *
 * This static constant array holds pointers to functions that handle
 * various graphical actions in the server. Each function in the array
 * takes three parameters:
 *   - zap_srv_parsed_context_t *: The parsed context of the server.
 *   - zap_srv_player_t *: The player structure.
 *   - zap_srv_graph_args_t *: Additional graphical arguments.
 *
 * The functions are:
 *   - graph_msz: Handles the map size request.
 *   - graph_bct: Handles the tile content request.
 *   - graph_mct: Handles the map content request.
 *   - graph_tna: Handles the team names request.
 *   - graph_ppo: Handles the player position request.
 *   - graph_plv: Handles the player level request.
 *   - graph_pin: Handles the player inventory request.
 *   - graph_sgt: Handles the server time unit request.
 *   - graph_sst: Handles the server time unit modification request.
 *
 * This array is used to dispatch graphical commands to their respective
 * handlers.
 */
static void (* const action_ptrs[])(zap_srv_parsed_context_t *,
    zap_srv_player_t *, zap_srv_graph_args_t *) = {
    &graph_msz,
    &graph_bct,
    &graph_mct,
    &graph_tna,
    &graph_ppo,
    &graph_plv,
    &graph_pin,
    &graph_sgt,
    &graph_sst
};

/**
 * @brief Checks if the given command string ends with a space, indicating it
 * has arguments.
 *
 * This function determines whether the provided command string (`cmd`)
 * is non-empty and its last character is a space (' '), which typically
 * signifies that the command is followed by arguments.
 *
 * @param cmd The command string to check.
 * @return int Returns 1 if the command ends with a space (has arguments), 0
 * otherwise.
 */
static int is_command_with_args(const char *cmd)
{
    size_t len = strlen(cmd);

    return len > 0 && cmd[len - 1] == ' ';
}

/**
 * @brief Matches a given command line against a list of authorized command
 * strings.
 *
 * This function iterates through the list of authorized command strings and
 * checks if the input line matches any of them. It distinguishes between
 * commands that require arguments and those that do not. If a match is found,
 * it sets the command index and, if applicable, a pointer to the arguments.
 *
 * @param line The input command line to match.
 * @param cmd_idx Pointer to an integer where the index of the matched command
 * will be stored.
 * @param args Pointer to a char pointer where the arguments (if any) will be
 * stored.
 *  If the matched command does not require arguments, *args will be set to
 * NULL.
 *
 * @return 1 if a matching command is found, 0 otherwise.
 */
static int match_command(char *line, int *cmd_idx, char **args)
{
    size_t len;
    int has_args;

    for (int i = 0; authorized_strings[i]; ++i) {
        len = strlen(authorized_strings[i]);
        has_args = is_command_with_args(authorized_strings[i]);
        if (!has_args && strcasecmp(line, authorized_strings[i]) == 0) {
            *cmd_idx = i;
            *args = NULL;
            return 1;
        }
        if (has_args && strncasecmp(line, authorized_strings[i], len) == 0 &&
            line[len] != '\0') {
            *cmd_idx = i;
            *args = (char *)(line + len);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Calls the appropriate action function for a graphical command.
 *
 * This function parses the arguments for a graphical command if provided,
 * and then calls the corresponding action function from the action_ptrs array,
 * passing the parsed arguments if available.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the player/client structure.
 * @param cmd_idx Index of the command to execute in the action_ptrs array.
 * @param args String containing the arguments for the command, or NULL.
 */
static void call_action(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, int cmd_idx, char *args)
{
    zap_srv_graph_args_t parsed_args = {0};

    if (args && parse_graph_args(args, &parsed_args, cmd_idx, client) != 0) {
        return;
    }
    if (args) {
        action_ptrs[cmd_idx](ctxt, client, &parsed_args);
    } else {
        action_ptrs[cmd_idx](ctxt, client, NULL);
    }
}

/**
 * @brief Handles a single line of input from a client, parses the command,
 * and executes the corresponding action.
 *
 * This function attempts to match the input line to a known command. If the
 * command is recognized, it extracts the command index and arguments, then
 * calls the appropriate action handler. If the command is not recognized,
 * it sends an error message ("suc\n") back to the client.
 *
 * @param ctxt Pointer to the server's parsed context structure.
 * @param client Pointer to the client/player structure.
 * @param line The input line received from the client.
 */
static void handle_line(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_t *client, char *line)
{
    int cmd_idx = -1;
    char *args = NULL;

    if (!match_command(line, &cmd_idx, &args)) {
        send_client("suc\n", &client->sock);
        return;
    }
    call_action(ctxt, client, cmd_idx, args);
}

/**
 * @brief Finds the length of a line in a buffer up to a newline character or
 * buffer size.
 *
 * This function iterates through the given buffer, counting characters until
 * it encounters a newline character ('\n') or reaches the specified buffer
 * size.
 *
 * @param buf Pointer to the buffer to search.
 * @param buf_size The maximum number of characters to examine in the buffer.
 * @return The number of characters before the first newline or up to buf_size.
 */
static size_t find_line_len(const char *buf, size_t buf_size)
{
    size_t len = 0;

    while (len < buf_size && buf[len] != '\n') {
        ++len;
    }
    return len;
}

/**
 * @brief Extracts a single line from a buffer into a provided line buffer.
 *
 * This function copies characters from the input buffer `buf` into the output
 * buffer `line`, up to either the end of the line (as determined by
 * `find_line_len`), the end of the buffer (`buf_size`), or the maximum length
 * allowed in `line` (`max_len - 1`), whichever comes first. The output buffer
 * is always null-terminated.
 *
 * @param buf The input buffer containing the data to extract the line from.
 * @param buf_size The size of the input buffer.
 * @param line The output buffer where the extracted line will be stored.
 * @param max_len The maximum length of the output buffer (including null
 * terminator).
 * @return The number of bytes consumed from the input buffer, including the
 * newline character if present; otherwise, the number of bytes copied.
 */
static size_t extract_line(char *buf, size_t buf_size, char *line,
    size_t max_len)
{
    size_t len = find_line_len(buf, buf_size);

    if (len >= max_len) {
        len = max_len - 1;
    }
    memcpy(line, buf, len);
    line[len] = '\0';
    return (len < buf_size && buf[len] == '\n') ? len + 1 : len;
}

/**
 * @brief Shifts the contents of a buffer to the left by a specified offset.
 *
 * This function moves the contents of the buffer `buf` left by `offset` bytes,
 * effectively removing the first `offset` bytes from the buffer. The size of
 * the buffer, pointed to by `buf_size`, is reduced by `offset`.
 *
 * @param buf Pointer to the buffer to be shifted.
 * @param buf_size Pointer to the size of the buffer; will be updated after
 * shifting.
 * @param offset Number of bytes to shift the buffer by.
 */
static void shift_buffer(char *buf, size_t *buf_size, size_t offset)
{
    size_t old_size;

    if (offset < *buf_size) {
        memmove(buf, buf + offset, *buf_size - offset);
    }
    old_size = *buf_size;
    *buf_size -= offset;
    memset(buf + *buf_size, 0, old_size - *buf_size);
}

/**
 * @brief Processes and handles graphical actions from a client's buffer.
 *
 * This function iterates through the client's buffer, extracting and handling
 * each line of input using the provided context and client information.
 * For each extracted line, it calls handle_line() to process the command.
 * After processing, it shifts the buffer to remove the consumed data.
 *
 * @param ctxt Pointer to the parsed server context.
 * @param client Pointer to the client structure containing the buffer and its
 * size.
 */
void graphic_actions(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client)
{
    size_t consumed;
    size_t offset = 0;
    char line[client->buf_size];

    while (offset < client->buf_size) {
        consumed = extract_line(client->buf + offset,
            client->buf_size - offset, line, sizeof(line));
        if (consumed == 0 || (offset + consumed > client->buf_size)) {
            break;
        }
        if (line[0] != '\0') {
            handle_line(ctxt, client, line);
        }
        offset += consumed;
    }
    shift_buffer(client->buf, &client->buf_size, offset);
}
