/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_buf
*/

#include "player_functions.h"

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

static bool command_takes_argument(size_t idx)
{
    return idx == 5 || idx == 9 || idx == 10;
}

static void add_action(zap_srv_player_t *player, const char *arg,
    time_t current_time, zap_srv_player_actions_t action)
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

static bool is_full_command_match(const char *cmd, const char *line)
{
    return strcmp(cmd, line) == 0;
}

static bool is_prefix_command_match(const char *cmd, const char *line)
{
    size_t cmd_len = strlen(cmd);

    return strncmp(cmd, line, cmd_len) == 0;
}

static const char *extract_argument(const char *line, size_t cmd_len)
{
    const char *arg = line + cmd_len;

    while (*arg == ' ') {
        ++arg;
    }
    return *arg ? arg : NULL;
}

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

static void handle_invalid_command(zap_srv_player_t *player)
{
    send_client("ko\n", &player->sock);
}

static void identify_action(zap_srv_player_t *player, const char *line,
    time_t current_time)
{
    zap_srv_player_actions_t action = ZAP_SRV_PL_NONE;
    const char *arg = NULL;

    if (!find_command(line, &action, &arg)) {
        handle_invalid_command(player);
        return;
    }
    add_action(player, arg, current_time, action);
}

void parse_buf(zap_srv_player_t *player)
{
    time_t current_time = time(NULL);
    char *saveptr = NULL;
    char *line = NULL;
    char *buf;

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
}
