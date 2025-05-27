/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "cextend/logger.h"
#include "parse_args/parse_args.h"

static void print_helper(void)
{
    printf("Helper\n");
}

int main(int ac, const char **av)
{
    zap_srv_parsed_context_t ctxt;

    for (int i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-h") == 0) {
            print_helper();
            return 0;
        }
    }
    parse_args(ac, av, &ctxt);
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Hello, World!");
    return 0;
}
