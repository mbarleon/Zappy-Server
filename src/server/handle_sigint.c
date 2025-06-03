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

void handle_sigint(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext)
{
    static int sigint_count = 0;

    if (sigint_count == 0) {
        CEXTEND_LOG(CEXTEND_LOG_INFO, "Stopping server...");
    }
    sigint_count++;
    if (sigint_count >= ZAP_SRV_MAX_SIGINT) {
        CEXTEND_PRT(CEXTEND_LOG_ERROR, "%d SIGINT detected, aborting.",
            ZAP_SRV_MAX_SIGINT);
        abort();
    }
    keep_running(true);
}
