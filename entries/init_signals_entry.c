/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** init_sigint_entry
*/

#include <signal.h>
#include <string.h>
#include "entries.h"
#include "../src/server/server_internal.h"

/**
 * @brief Initializes signal handlers for the server.
 *
 * This function is automatically called at program startup due to the
 * constructor attribute. It sets up custom handlers for SIGINT and SIGTERM
 * signals using the sigaction API, allowing the server to handle
 * interruptions and termination requests gracefully.
 *
 * The signal handler function used is `handle_signals`, which should be
 * defined elsewhere in the codebase. The SA_SIGINFO flag is set to provide
 * additional information to the handler.
 */
__attribute__((constructor(ZAP_SRV_INIT_SIGNALS_ENTRY)))
void init_signals_handler(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    // sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}
