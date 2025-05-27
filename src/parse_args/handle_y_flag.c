/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** handle_p_flag
*/

#include "parse_args_internal.h"

zap_srv_flags_t handle_y_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i)
{
    size_t y = get_size_t_from_str(av[(*i) + 1]);

    ctxt->map.y = y;
    *i += 2;
    return ZAP_SRV_FLAG_Y;
}
