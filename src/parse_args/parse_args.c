/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_args
*/

#include "parse_args_internal.h"

static void all_flags_init(const bool are_flags_init[ZAP_SRV_FLAG_LEN])
{
    for (size_t i = 0; i < ZAP_SRV_FLAG_LEN; ++i) {
        if (i != ZAP_SRV_FLAG_F && !are_flags_init[i]) {
            THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
        }
    }
}

static zap_srv_flags_t parse_flags(const char **av,
    zap_srv_parsed_context_t *ctxt, int *i)
{
    if (!av[*i] || strlen(av[*i]) != 2 || av[*i][0] != '-') {
        return ZAP_SRV_FLAG_UNKNOWN;
    }
    switch (av[*i][1]) {
        case 'p':
            return handle_p_flag(av, ctxt, i);
        case 'x':
            return handle_x_flag(av, ctxt, i);
        case 'y':
            return handle_y_flag(av, ctxt, i);
        case 'n':
            return handle_n_flag(av, ctxt, i);
        case 'c':
            return handle_c_flag(av, ctxt, i);
        case 'f':
            return handle_f_flag(av, ctxt, i);
        default:
            return ZAP_SRV_FLAG_UNKNOWN;
    }
}

void parse_args(int ac, const char **av, zap_srv_parsed_context_t *ctxt)
{
    int i = 1;
    zap_srv_flags_t ret = ZAP_SRV_FLAG_UNKNOWN;
    bool are_flags_init[ZAP_SRV_FLAG_LEN] = {false};

    memset(ctxt, 0, sizeof(zap_srv_parsed_context_t));
    ctxt->server.frequency = 100;
    while (i < ac) {
        ret = parse_flags(av, ctxt, &i);
        if (ret == ZAP_SRV_FLAG_UNKNOWN) {
            THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
        }
        are_flags_init[ret] = true;
    }
    all_flags_init(are_flags_init);
}
