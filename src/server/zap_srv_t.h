/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** zap_srv_t
*/

#ifndef ZAP_SRV_T_H_
    #define ZAP_SRV_T_H_
    #include <poll.h>
    #include <stddef.h>
    #include <stdint.h>
    #include "zap_srv_socket.h"
    #include "../players/players.h"

    #define ZAP_SRV_SOCK_ERROR INT32_MIN
    #define ZAP_SRV_MAX_CLIENTS (UINT16_MAX - 10000)

/**
 * @struct zap_srv_t
 * @brief Structure representing the configuration of a Zappy server.
 *
 * This structure holds the basic configuration parameters for the server,
 * including the network port, the server's frequency and its socket.
 */
typedef struct {
    /**
     * @brief Last time ressources spawned.
     */
    double last_spawn;
    /**
     * @brief Current number of clients
     */
    size_t num_clients;
    /**
     * @brief The network port number on which the server listens
     * (16-bit unsigned integer).
     */
    uint16_t port;
    /**
     * @brief The frequency at which the server operates (size_t).
     */
    size_t frequency;
    /**
     * @brief The socket of the server.
     */
    zap_srv_socket_t sock;
    /**
     * @brief List of all the clients.
     */
    zap_srv_player_t *clients;
    /**
     * @brief List of all the fds.
     */
    struct pollfd fds[ZAP_SRV_MAX_CLIENTS + 1];
    /**
     * @brief List of all the ports.
     */
    int32_t port_list[ZAP_SRV_MAX_CLIENTS];
} zap_srv_t;

#endif /* !ZAP_SRV_T_H_ */
