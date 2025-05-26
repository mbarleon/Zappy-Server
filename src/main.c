/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include "../external/lib-cextend/include/cextend/logger.h"

int main(__attribute__((unused))int ac, __attribute__((unused))char **av)
{
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Hello, World!");
    return 0;
}
