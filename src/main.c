/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include "macro.h"
#include <stdio.h>
#include <string.h>
#include "server/server.h"
#include <cextend/logger.h>
#include <cextend/exception.h>
#include "parse_args/parse_args.h"
#include "string/string_entry_table.h"

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
    printf(fetch_string(ZAP_SRV_USAGE));
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
        generate_map(&ctxt->map);
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_PARSING_ERROR),
            get_exception_str(code));
    } CATCH(code, CEXTEND_EXCEPTION_INVALID_ARGUMENT) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_PARSING_ERROR),
            get_exception_str(code));
    } CATCH_END(code);
    END_TRY;
    return code ? ZAP_SRV_ERROR : ZAP_SRV_SUCCESS;
}

/**
 * @brief Attempts to run the server and handles any exceptions that occur.
 *
 * This function wraps the call to run_server() in a TRY/CATCH block to handle
 * exceptions gracefully. If an exception is caught during server execution,
 * an error message is logged with the exception details. The function returns
 * ZAP_SRV_SUCCESS if the server ran without exceptions, or ZAP_SRV_ERROR if
 * an exception was encountered.
 *
 * @param ctxt Pointer to the parsed server context structure.
 * @return int ZAP_SRV_SUCCESS on success, ZAP_SRV_ERROR on exception.
 */
static int try_run_server(zap_srv_parsed_context_t *ctxt)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        run_server(ctxt);
    } CATCH_ALL {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_RUNTIME_ERROR),
            get_exception_str(code));
    }
    END_TRY;
    return code ? ZAP_SRV_ERROR : ZAP_SRV_SUCCESS;
}

/**
 * @brief Entry point for the Zappy Server application.
 *
 * This function parses command-line arguments, displays help if requested,
 * initializes the server context, and starts the server.
 *
 * @param ac Argument count.
 * @param av Argument vector (array of argument strings).
 * @return int Returns ZAP_SRV_SUCCESS on success, or ZAP_SRV_ERROR on failure.
 *
 * The function performs the following steps:
 * 1. Checks if the "-help" flag is present among the arguments and prints
 *    the helper message if found, then exits successfully.
 * 2. Attempts to parse the command-line arguments into a server context.
 * 3. If parsing fails or the server fails to start, returns an error code.
 * 4. Returns success code if the server starts successfully.
 */
int main(int ac, const char **av)
{
    zap_srv_parsed_context_t ctxt;

    for (int i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-help") == 0) {
            print_helper();
            return ZAP_SRV_SUCCESS;
        }
    }
    if (try_parse_args(ac, av, &ctxt) == ZAP_SRV_ERROR ||
        try_run_server(&ctxt) == ZAP_SRV_ERROR) {
        return ZAP_SRV_ERROR;
    }
    return ZAP_SRV_SUCCESS;
}
