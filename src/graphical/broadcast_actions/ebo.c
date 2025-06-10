/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** enw
*/

#include "../graphical_internal.h"

void send_ebo(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg)
{
    char *block;

    block = snprintf_alloc("ebo #%ld\n", egg->number);
    if (block) {
        graphical_broadcast(ctxt, block);
        free(block);
    }
}
