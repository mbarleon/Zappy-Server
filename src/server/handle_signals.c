/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_sigint
*/

#include "signals_handling.h"

/**
 * @brief Controls and queries the running state of the server.
 *
 * This function uses a static variable to maintain the running state across
 * calls. When called with `running == true`, it sets the internal state to
 * false, indicating that the server should stop running. On every call, it
 * returns the current state.
 *
 * @param running If true, sets the running state to false (request to stop).
 * @return true if the server should keep running, false otherwise.
 */
bool keep_running(bool running)
{
    static bool ret = true;

    if (running == true) {
        ret = false;
    }
    return ret;
}

/**
 * @brief Handles incoming signals for the server, such as SIGINT.
 *
 * This function is intended to be used as a signal handler. It logs a message
 * the first time it is called, and increments a static signal count each time
 * it is invoked. If the number of received signals reaches or exceeds
 * ZAP_SRV_MAX_SIGINT, it logs an error message and aborts the program.
 * Otherwise, it signals the server to keep running.
 *
 * @param sig Unused signal number.
 * @param info Unused pointer to siginfo_t structure.
 * @param ucontext Unused pointer to ucontext structure.
 */
void handle_signals(int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext)
{
    static volatile sig_atomic_t sig_count = 0;

    if (sig == SIGINT) {
        printf("\r");
        fflush(stdout);
    }
    if (sig_count == 0) {
        CEXTEND_LOG(CEXTEND_LOG_INFO, fetch_string(ZAP_SRV_SERVER_STOP));
    }
    ++sig_count;
    if (sig_count >= ZAP_SRV_MAX_SIGINT) {
        CEXTEND_PRT(CEXTEND_LOG_ERROR, fetch_string(ZAP_SRV_SERVER_ABORT),
            ZAP_SRV_MAX_SIGINT);
        abort();
    }
    keep_running(true);
}
