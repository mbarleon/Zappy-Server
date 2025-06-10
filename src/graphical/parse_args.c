/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_args
*/

#include "actions/actions.h"

/**
 * @brief Parses two signed integer arguments from a string for graphical
 * server commands.
 *
 * This function extracts two space-separated signed integer values from the
 * input string `args` and stores them in the `parsed` structure. It performs
 * error checking for range errors, invalid input, and ensures the values are
 * within the bounds of `SSIZE_MAX` and `(-1 * SSIZE_MAX) - 1`.
 *
 * @param args The input string containing two space-separated integer
 * arguments.
 * @param parsed Pointer to a zap_srv_graph_args_t structure where the parsed
 * values will be stored.
 * - `parsed->nargs` is set to 2.
 * - `parsed->is_signed` is set to true.
 * - `parsed->ssize_a` and `parsed->ssize_b` are set to the parsed values.
 *
 * @return ZAP_SRV_SUCCESS on successful parsing, ZAP_SRV_ERROR on failure.
 */
static int parse_bct_args(const char *args, zap_srv_graph_args_t *parsed)
{
    long long val;
    char *end = NULL;

    parsed->nargs = 2;
    parsed->is_signed = true;
    errno = 0;
    val = strtoll(args, &end, 10);
    if (errno == ERANGE || end == args || *end != ' ' || val > SSIZE_MAX ||
        val < (-1 * SSIZE_MAX) - 1 || val < 0) {
        return ZAP_SRV_ERROR;
    }
    parsed->ssize_a = (ssize_t)val;
    errno = 0;
    val = strtoll(end + 1, &end, 10);
    if (errno == ERANGE || end == args || (*end != '\0' && *end != '\n') ||
        val > SSIZE_MAX || val < (-1 * SSIZE_MAX) - 1) {
        return ZAP_SRV_ERROR;
    }
    parsed->ssize_b = (ssize_t)val;
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Parses an ID argument from a string and stores the result in a
 * zap_srv_graph_args_t structure.
 *
 * The function expects the argument string to start with a '#' character
 * followed by a signed integer. It validates the format, checks for conversion
 * errors, and ensures the value fits within the range of ssize_t.
 *
 * @param args The input argument string to parse (should start with '#').
 * @param parsed Pointer to a zap_srv_graph_args_t structure where the parsed
 * value will be stored.
 * @return ZAP_SRV_SUCCESS on successful parsing and validation, ZAP_SRV_ERROR
 * otherwise.
 */
static int parse_id_arg(const char *args, zap_srv_graph_args_t *parsed)
{
    long long val;
    char *end = NULL;

    parsed->nargs = 1;
    parsed->is_signed = true;
    if (args[0] != '#') {
        return ZAP_SRV_ERROR;
    }
    errno = 0;
    val = strtoll(args + 1, &end, 10);
    if (errno == ERANGE || end == args + 1 || (*end != '\0' && *end != '\n') ||
        val > SSIZE_MAX || val < (-1 * SSIZE_MAX) - 1) {
        return ZAP_SRV_ERROR;
    }
    parsed->ssize_a = (ssize_t)val;
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Parses a string argument as an unsigned size value for the server.
 *
 * This function attempts to convert the input string `args` to an unsigned
 * long long integer, ensuring it is a valid, non-negative, and within the
 * range of `size_t`. The result is stored in the `size_a` field of the
 * `parsed` structure.
 *
 * @param args The input string to parse as a size value.
 * @param parsed Pointer to a zap_srv_graph_args_t structure where the parsed
 * value will be stored.
 * @return ZAP_SRV_SUCCESS on successful parsing and assignment,
 * ZAP_SRV_ERROR if the input is invalid or out of range.
 */
static int parse_sst_arg(const char *args, zap_srv_graph_args_t *parsed)
{
    char *end = NULL;
    unsigned long long val;

    parsed->nargs = 1;
    parsed->is_signed = false;
    errno = 0;
    val = strtoull(args, &end, 10);
    if (errno == ERANGE || end == args || (*end != '\0' && *end != '\n') ||
        val > SIZE_MAX) {
        return ZAP_SRV_ERROR;
    }
    parsed->size_a = (size_t)val;
    return ZAP_SRV_SUCCESS;
}

/**
 * @brief Parses graphical command arguments and fills the parsed structure.
 *
 * This function selects the appropriate argument parsing function based on the
 * command index and the corresponding authorized command string. It supports
 * parsing for "bct", "ppo", "plv", "pin", and "sst" commands. If parsing
 * fails,cit sends an error message ("sbp\n") to the client.
 *
 * @param args The argument string to parse.
 * @param parsed Pointer to the structure where parsed arguments will be
 * stored.
 * @param cmd_idx Index of the command in the authorized_strings array.
 * @param client Pointer to the client structure (used for error reporting).
 *
 * @return 0 on success, ZAP_SRV_ERROR on failure.
 */
int parse_graph_args(const char *args, zap_srv_graph_args_t *parsed,
    int cmd_idx, zap_srv_player_t *client)
{
    int ret = 0;

    if (strcasecmp(authorized_strings[cmd_idx], "bct ") == 0) {
        ret = parse_bct_args(args, parsed);
    }
    if (strcasecmp(authorized_strings[cmd_idx], "ppo ") == 0 ||
        strcasecmp(authorized_strings[cmd_idx], "plv ") == 0 ||
        strcasecmp(authorized_strings[cmd_idx], "pin ") == 0) {
        ret = parse_id_arg(args, parsed);
    }
    if (strcasecmp(authorized_strings[cmd_idx], "sst ") == 0) {
        ret = parse_sst_arg(args, parsed);
    }
    if (ret == ZAP_SRV_ERROR) {
        send_client("sbp\n", &client->sock);
    }
    return ret;
}
