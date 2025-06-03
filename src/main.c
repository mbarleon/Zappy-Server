/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include "macro.h"
#include <stdio.h>
#include <string.h>
#include <cextend/logger.h>
#include <cextend/exception.h>
#include "parse_args/parse_args.h"

/**
 * @brief Prints the usage information for the zappy_server program.
 *
 * This function outputs the correct command-line usage format for the
 * zappy_server executable, detailing the required and optional arguments.
 * It is typically called when the user provides incorrect arguments or
 * requests help.
 */
static void print_helper(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 "
        "... -c clientsNb -f freq\n");
}

/**
 * @brief Attempts to parse command-line arguments and handle exceptions.
 *
 * This function wraps the call to `parse_args` in a try-catch block to handle
 * specific exceptions that may occur during argument parsing. If a memory
 * allocation error (`CEXTEND_EXCEPTION_BAD_ALLOC`) or an invalid argument
 * error (`CEXTEND_EXCEPTION_INVALID_ARGUMENT`) is caught, an error message is
 * logged and an error code is returned. On success, a success code is
 * returned.
 *
 * @param ac The argument count from the command line.
 * @param av The argument vector from the command line.
 * @param ctxt Pointer to a zap_srv_parsed_context_t structure to store parsed
 * results.
 *
 * @return ZAP_SRV_SUCCESS on success, ZAP_SRV_ERROR on failure.
 */
static int try_parse_args(int ac, const char **av,
    zap_srv_parsed_context_t *ctxt)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        parse_args(ac, av, ctxt);
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "Caught exception in parsing: %s",
            get_exception_str(code));
        END_TRY;
        return ZAP_SRV_ERROR;
    } CATCH(code, CEXTEND_EXCEPTION_INVALID_ARGUMENT) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "Caught exception in parsing: %s",
            get_exception_str(code));
        END_TRY;
        return ZAP_SRV_ERROR;
    } CATCH_END(code);
    END_TRY;
    return ZAP_SRV_SUCCESS;
}

int main(int ac, const char **av)
{
    zap_srv_parsed_context_t ctxt;

    for (int i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-help") == 0) {
            print_helper();
            return ZAP_SRV_SUCCESS;
        }
    }
    if (try_parse_args(ac, av, &ctxt) == ZAP_SRV_ERROR) {
        return ZAP_SRV_ERROR;
    }
    return ZAP_SRV_SUCCESS;
}
