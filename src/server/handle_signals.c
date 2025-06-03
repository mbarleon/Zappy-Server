/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_sigint
*/

#include "server_internal.h"

bool keep_running(bool running)
{
    static bool ret = true;

    if (running == true) {
        ret = false;
    }
    return ret;
}

void handle_signals(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext)
{
    static volatile sig_atomic_t sig_count = 0;

    if (sig_count == 0) {
        CEXTEND_LOG(CEXTEND_LOG_INFO, "Stopping server...");
    }
    sig_count++;
    if (sig_count >= ZAP_SRV_MAX_SIGINT) {
        CEXTEND_PRT(CEXTEND_LOG_ERROR, "%d SIGINT or SIGTERM detected, "
            "aborting.", ZAP_SRV_MAX_SIGINT);
        abort();
    }
    keep_running(true);
}
