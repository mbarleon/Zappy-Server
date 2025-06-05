/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** egg_functions
*/

#ifndef ZAP_SRV_EGG_FUNCTIONS_H_
    #define ZAP_SRV_EGG_FUNCTIONS_H_
    #include "egg.h"
    #include <sys/types.h>
    #include "../parse_args/parse_args.h"

zap_srv_egg_t *create_egg(zap_srv_pos_t *pos, ssize_t player_number);
void add_egg(zap_srv_egg_t **egg_list, zap_srv_pos_t *pos,
    ssize_t player_number);
void spawn_eggs(zap_srv_parsed_context_t *ctxt);
void hatch_egg(zap_srv_parsed_context_t *ctxt, const char *team);

#endif /* !ZAP_SRV_EGG_FUNCTIONS_H_ */
