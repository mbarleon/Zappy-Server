/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** graphical
*/

#ifndef ZAP_SRV_GRAPHICAL_H_
    #define ZAP_SRV_GRAPHICAL_H_
    #include "../server/zap_srv_socket.h"

/**
 * @struct zap_srv_graph_client_t
 * @brief Represents a graphical client connected to the Zappy server.
 *
 * This structure holds information about a graphical client,
 * specifically its associated socket.
 */
typedef struct {
    /**
     * @brief The socket used to communicate with the graphical client.
     */
    zap_srv_socket_t sock;
} zap_srv_graph_client_t;

#endif /* !ZAP_SRV_GRAPHICAL_H_ */
