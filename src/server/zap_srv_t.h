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

    #define ZAP_SRV_MAX_CLIENTS (UINT16_MAX - 10000)

/**
 * @enum client_type_t
 * @brief Represents the type of client connected to the server.
 *
 * This enumeration is used to distinguish between different types of clients:
 * - NONE:        No client type specified or invalid client (-1).
 * - GRAPHICAL:   A graphical client, typically used for visualization or
 * monitoring.
 * - PLAYER:      A player client, representing a user participating in the
 * game.
 */
typedef enum {
    ZAP_SRV_NONE_CLIENT = -1,
    ZAP_SRV_GRAPHICAL_CLIENT,
    ZAP_SRV_PLAYER_CLIENT
} client_type_t;

/**
 * @brief Structure representing a list of clients connected to the server.
 *
 * This structure holds arrays for client pointers and their corresponding
 * types, supporting up to ZAP_SRV_MAX_CLIENTS clients.
 */
typedef struct {
    /**
     * @brief Array of pointers to client objects.
     */
    void *clients[ZAP_SRV_MAX_CLIENTS];
    /**
     * @brief  Array of client types, corresponding to each client in the
     * clients array.
     */
    client_type_t types[ZAP_SRV_MAX_CLIENTS];
} zap_srv_client_list_t;

/**
 * @struct zap_srv_t
 * @brief Structure representing the configuration of a Zappy server.
 *
 * This structure holds the basic configuration parameters for the server,
 * including the network port, the server's frequency and its socket.
 */
typedef struct {
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
    zap_srv_client_list_t clients;
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
