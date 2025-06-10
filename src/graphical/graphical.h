/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** graphical
*/

#ifndef ZAP_SRV_GRAPHICAL_H_
    #define ZAP_SRV_GRAPHICAL_H_
    #include "../players/players.h"
    #include "../parse_args/parse_args.h"

void graphic_actions(zap_srv_player_t *client);
void graphical_broadcast(zap_srv_parsed_context_t *ctxt, const char *str);

void send_bct(zap_srv_parsed_context_t *ctxt, zap_srv_pos_t *pos);
void send_ebo(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg);
void send_enw(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg);
void send_edi(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg);
void send_seg(zap_srv_parsed_context_t *ctxt, zap_srv_team_t *team);
void send_plv(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_ppo(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pin(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pfk(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pdi(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pnw(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pie(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    bool worked);
void send_pbc(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    const char *msg);
void send_pdr(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_elements_t element);
void send_pgt(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client,
    zap_srv_elements_t element);
void send_pic(zap_srv_parsed_context_t *ctxt,
    zap_srv_player_list_t *player_list);

#endif /* !ZAP_SRV_GRAPHICAL_H_ */
