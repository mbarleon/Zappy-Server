/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

zap_srv_flags_t handle_p_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    uint16_t port = get_uint16_from_str(av[(*i) + 1]);

    ctxt->server.port = port;
    *i += 2;
    return ZAP_SRV_FLAG_P;
}
