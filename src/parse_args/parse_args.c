/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_args
*/

#include "parse_args_internal.h"

/**
 * @brief Checks if all required command-line flags have been initialized.
 *
 * Iterates through the array of flag initialization statuses and throws an
 * exception if any required flag (except for the flag at index ZAP_SRV_FLAG_F)
 * has not been initialized.
 *
 * @param are_flags_init An array of boolean values indicating whether each
 * flag has been initialized. The length of the array is ZAP_SRV_FLAG_LEN.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if any required flag is not
 * initialized.
 */
static void all_flags_init(const bool are_flags_init[ZAP_SRV_FLAG_LEN])
{
    for (size_t i = 0; i < ZAP_SRV_FLAG_LEN; ++i) {
        if (i != ZAP_SRV_FLAG_F && !are_flags_init[i]) {
            THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
        }
    }
}

/**
 * @brief Parses a command-line flag from the argument vector and dispatches
 * handling to the appropriate flag handler function.
 *
 * This function checks if the current argument is a valid flag (i.e., starts
 * with '-' and is two characters long), and then calls the corresponding
 * handler function based on the flag character. If the flag is unknown or
 * invalid, it returns ZAP_SRV_FLAG_UNKNOWN.
 *
 * @param av The argument vector (array of strings).
 * @param ctxt Pointer to the parsed context structure to be updated.
 * @param i Pointer to the current index in the argument vector; may be
 * incremented by handler functions.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if the value is invalid.
 * @throws CEXTEND_EXCEPTION_BAD_ALLOC if memory allocation fails.
 *
 * @return zap_srv_flags_t  The parsed flag type, or ZAP_SRV_FLAG_UNKNOWN if
 * the flag is invalid or unrecognized.
 */
static zap_srv_flags_t parse_flags(const char **av,
    zap_srv_parsed_context_t *ctxt, int *i)
{
    if (!av[*i] || strlen(av[*i]) != 2 || av[*i][0] != '-') {
        return ZAP_SRV_FLAG_UNKNOWN;
    }
    switch (av[*i][1]) {
        case 'p':
            return handle_p_flag(av, ctxt, i);
        case 'x':
            return handle_x_flag(av, ctxt, i);
        case 'y':
            return handle_y_flag(av, ctxt, i);
        case 'n':
            return handle_n_flag(av, ctxt, i);
        case 'c':
            return handle_c_flag(av, ctxt, i);
        case 'f':
            return handle_f_flag(av, ctxt, i);
        default:
            return ZAP_SRV_FLAG_UNKNOWN;
    }
}

/**
 * @brief Parses command-line arguments and populates the server context
 * structure.
 *
 * This function processes the command-line arguments provided to the server,
 * initializes the context structure to default values, and updates it based on
 * the parsed flags. It ensures that all required flags are set and throws an
 * exception if an invalid argument is encountered.
 *
 * @param ac The argument count.
 * @param av The argument vector (array of argument strings).
 * @param ctxt Pointer to the server context structure to be populated.
 *
 * @throws @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if a command-line
 * argument is wrong.
 * @throws CEXTEND_EXCEPTION_BAD_ALLOC if memory allocation fails.
 */
void parse_args(int ac, const char **av, zap_srv_parsed_context_t *ctxt)
{
    int i = 1;
    zap_srv_flags_t ret = ZAP_SRV_FLAG_UNKNOWN;
    bool are_flags_init[ZAP_SRV_FLAG_LEN] = {false};

    memset(ctxt, 0, sizeof(zap_srv_parsed_context_t));
    ctxt->server.frequency = 10000UL;
    while (i < ac) {
        ret = parse_flags(av, ctxt, &i);
        if (ret == ZAP_SRV_FLAG_UNKNOWN) {
            THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
        }
        are_flags_init[ret] = true;
    }
    all_flags_init(are_flags_init);
}
