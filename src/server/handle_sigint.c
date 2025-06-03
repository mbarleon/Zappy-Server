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

    if (running == true)
        ret = false;
    return ret;
}

void handle_sigint(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext)
{
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Stopping server...");
    keep_running(true);
}
