/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include "cextend/logger.h"
#include "cextend/entries/logger_init.h"

int main(__attribute__((unused))int ac, __attribute__((unused))char **av)
{
    CEXTEND_INIT_LOG;
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Hello, World!");
    return 0;
}
