/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** server
*/

#ifndef ZAP_SRV_SERVER_H_
    #define ZAP_SRV_SERVER_H_
    #include "zap_srv_t.h"
    #include "../parse_args/parse_args.h"

void run_server(zap_srv_parsed_context_t *ctxt);
void send_client(const char *buffer, zap_srv_socket_t *client);
void disconnect_client(zap_srv_t *server, size_t i);

#endif /* !ZAP_SRV_SERVER_H_ */
