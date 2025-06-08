/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_buf
*/

#include "player_functions.h"

/**
 * @brief Array of authorized command strings for player actions.
 *
 * This static constant array contains the list of valid command strings
 * that can be received and processed by the server for player actions.
 * Each string represents a specific command that a player can issue.
 * The array is terminated with a NULL pointer.
 *
 * Commands include movement, inventory management, communication, and
 * other in-game actions.
 */
static const char *authorized_strings[] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast ",
    "Connect_nbr",
    "Fork",
    "Eject",
    "Take ",
    "Set ",
    "Inventory",
    NULL
};

/**
 * @brief Determines if the command at the given index requires an argument.
 *
 * This function checks if the command corresponding to the provided index
 * is one that expects an argument. Specifically, it returns true if the
 * index is 5, 9, or 10, and false otherwise.
 *
 * @param idx The index of the command to check.
 * @return true if the command takes an argument, false otherwise.
 */
static bool command_takes_argument(size_t idx)
{
    return idx == 5 || idx == 9 || idx == 10;
}

/**
 * @brief Adds a new action to the player's action queue.
 *
 * This function searches for the first available slot in the player's actions
 * array (where the action is ZAP_SRV_PL_NONE) and assigns the specified
 * action, timestamp, and optional argument to it. If the argument is provided
 * and non-empty, it is duplicated and stored; otherwise, the arguments
 * field is set to NULL.
 *
 * @param player Pointer to the zap_srv_player_t structure representing the
 * player.
 * @param arg Optional argument string for the action. Can be NULL or empty.
 * @param current_time The current timestamp to associate with the action.
 * @param action The action to be added to the player's action queue.
 */
static void add_action(zap_srv_player_t *player, const char *arg,
    double current_time, zap_srv_player_actions_t action)
{
    for (size_t i = 0; i < ZAP_SRV_MAX_ACTIONS - 1; ++i) {
        if (player->actions[i].action != ZAP_SRV_PL_NONE) {
            continue;
        }
        player->actions[i].action = action;
        player->actions[i].timestamp = current_time;
        if (arg && *arg) {
            player->actions[i].arguments = safe_strdup(arg);
        } else {
            player->actions[i].arguments = NULL;
        }
        break;
    }
}

/**
 * @brief Checks if the given line exactly matches the specified command
 * string.
 *
 * This function compares the provided command string (`cmd`) with the input
 * line (`line`) using a string comparison. It returns true if both strings are
 * identical.
 *
 * @param cmd The command string to compare.
 * @param line The input line to compare against the command.
 * @return true if the command and line are identical, false otherwise.
 */
static bool is_full_command_match(const char *cmd, const char *line)
{
    return strcasecmp(cmd, line) == 0;
}

/**
 * @brief Checks if the given line starts with the specified command prefix.
 *
 * This function compares the beginning of the 'line' string with the 'cmd'
 * string. It returns true if 'line' starts with 'cmd', otherwise returns
 * false.
 *
 * @param cmd The command prefix to check for.
 * @param line The input string to check against the command prefix.
 * @return true if 'line' starts with 'cmd', false otherwise.
 */
static bool is_prefix_command_match(const char *cmd, const char *line)
{
    size_t cmd_len = strlen(cmd);

    return strncasecmp(cmd, line, cmd_len) == 0;
}

/**
 * @brief Extracts the argument part from a command line string.
 *
 * Given a command line string and the length of the command,
 * this function returns a pointer to the first non-space character
 * following the command, which is considered the argument.
 * If there is no argument present, returns NULL.
 *
 * @param line The input command line string.
 * @param cmd_len The length of the command part in the string.
 * @return Pointer to the argument string, or NULL if no argument exists.
 */
static const char *extract_argument(const char *line, size_t cmd_len)
{
    const char *arg = line + cmd_len;

    while (*arg == ' ') {
        ++arg;
    }
    return *arg ? arg : NULL;
}

/**
 * @brief Searches for a matching command in the input line and extracts its
 * action and argument.
 *
 * This function iterates through the list of authorized command strings,
 * checking if the input line matches any of them. If a command that takes an
 * argument is matched by prefix, it extracts the argument from the line. If a
 * command that does not take an argument is matched exactly, it sets the
 * action accordingly and sets the argument to NULL.
 *
 * @param line The input string to parse for a command.
 * @param action Pointer to a variable where the matched action will be stored.
 * @param arg Pointer to a variable where the extracted argument (if any) will
 * be stored. If the command does not take an argument, this will be set to
 * NULL.
 * @return true if a valid command is found and parsed; false otherwise.
 */
static bool find_command(const char *line, zap_srv_player_actions_t *action,
    const char **arg)
{
    size_t cmd_len;

    for (size_t i = 0; authorized_strings[i]; ++i) {
        cmd_len = strlen(authorized_strings[i]);
        if (command_takes_argument(i) &&
            is_prefix_command_match(authorized_strings[i], line)) {
            *action = (zap_srv_player_actions_t)i;
            *arg = extract_argument(line, cmd_len);
            return true;
        }
        if (!command_takes_argument(i) &&
            is_full_command_match(authorized_strings[i], line)) {
            *action = (zap_srv_player_actions_t)i;
            *arg = NULL;
            return true;
        }
    }
    return false;
}

/**
 * @brief Handles the case when a player sends an invalid command.
 *
 * This function sends a "ko\n" response to the player's socket to indicate
 * that the received command was not recognized or is invalid.
 *
 * @param player Pointer to the zap_srv_player_t structure representing the
 * player.
 */
static void handle_invalid_command(zap_srv_player_t *player)
{
    send_client("ko\n", &player->sock);
}

/**
 * @brief Identifies and processes a player's action from an input line.
 *
 * This function attempts to parse the given input line to determine the
 * corresponding player action. If the command is valid, it adds the action
 * to the player's action queue with the provided timestamp. If the command
 * is invalid, it handles the invalid command appropriately.
 *
 * @param player Pointer to the player structure.
 * @param line The input line containing the player's command.
 * @param current_time The current time to associate with the action.
 */
static void identify_action(zap_srv_player_t *player, const char *line,
    double current_time)
{
    zap_srv_player_actions_t action = ZAP_SRV_PL_NONE;
    const char *arg = NULL;

    if (!find_command(line, &action, &arg)) {
        handle_invalid_command(player);
        return;
    }
    add_action(player, arg, current_time, action);
}

/**
 * @brief Parses the buffer of a player, extracting and processing each command
 * line.
 *
 * This function duplicates the player's buffer, splits it into lines using
 * '\n' as the delimiter, and processes each line as a separate action by
 * calling identify_action(). After processing, the original buffer is cleared.
 *
 * @param player Pointer to the zap_srv_player_t structure representing the
 * player whose buffer is to be parsed.
 */
void parse_buf(zap_srv_player_t *player)
{
    char *buf;
    char *line = NULL;
    char *saveptr = NULL;
    double current_time = get_time();

    if (!player->buf) {
        return;
    }
    buf = strdup(player->buf);
    if (!buf)
        return;
    line = strtok_r(buf, "\n", &saveptr);
    while (line) {
        identify_action(player, line, current_time);
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(buf);
    memset(player->buf, 0, player->buf_size);
}
