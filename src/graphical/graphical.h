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

void send_ebo(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg);
void send_enw(zap_srv_parsed_context_t *ctxt, zap_srv_egg_t *egg);
void send_seg(zap_srv_parsed_context_t *ctxt, zap_srv_team_t *team);
void send_pin(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pfk(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pdi(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);
void send_pnw(zap_srv_parsed_context_t *ctxt, zap_srv_player_t *client);

#endif /* !ZAP_SRV_GRAPHICAL_H_ */
