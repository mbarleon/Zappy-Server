/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** pos_list
*/

#ifndef ZAP_SRV_POS_LIST_H_
    #define ZAP_SRV_POS_LIST_H_
    #include "types.h"
    #include "../parse_args/parse_args.h"

typedef struct zap_srv_pos_list_s {
    zap_srv_pos_t pos;
    struct zap_srv_pos_list_s *next;
} zap_srv_pos_list_t;

void free_pos_list(zap_srv_pos_list_t *list);
void add_in_pos_list(zap_srv_pos_list_t **list, zap_srv_pos_t *pos);
zap_srv_pos_list_t *find_players_positions(zap_srv_parsed_context_t *ctxt);


#endif /* !ZAP_SRV_POS_LIST_H_ */
