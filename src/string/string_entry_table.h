/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** string_entry_table
*/

#ifndef STRING_ENTRY_TABLE_H_
    #define STRING_ENTRY_TABLE_H_

/**
 * @enum zap_srv_string_entries_t
 * @brief Enumerates string entry identifiers for server-related messages and
 * errors.
 *
 * This enumeration defines symbolic names for various server string entries,
 * such as error messages and server status notifications. These identifiers
 * can be used to reference specific strings in a table or array, facilitating
 * localization and maintainability.
 *
 * @var ZAP_SRV_STRING_MIN         Minimum value (sentinel).
 * @var ZAP_SRV_START              Message for server start.
 * @var ZAP_SRV_SOCKET_FAIL        Socket creation failure.
 * @var ZAP_SRV_BIND_FAIL          Socket binding failure.
 * @var ZAP_SRV_GETSOCKNAME_FAIL   Failure retrieving socket name.
 * @var ZAP_SRV_LISTEN_FAIL        Failure setting socket to listen.
 * @var ZAP_SRV_SERVER_START       Server start notification.
 * @var ZAP_SRV_SERVER_STOP        Server stop notification.
 * @var ZAP_SRV_SERVER_ABORT       Server abort notification.
 * @var ZAP_SRV_USAGE              Usage information.
 * @var ZAP_SRV_CAUGHT_ERROR       Generic caught error message.
 * @var ZAP_SRV_STRING_MAX         Maximum value (sentinel).
 */
typedef enum {
    ZAP_SRV_STRING_MIN = 0,

    ZAP_SRV_START,
    ZAP_SRV_SOCKET_FAIL,
    ZAP_SRV_ACCEPT_FAIL,
    ZAP_SRV_POLL_FAIL,
    ZAP_SRV_BIND_FAIL,
    ZAP_SRV_GETSOCKNAME_FAIL,
    ZAP_SRV_LISTEN_FAIL,
    ZAP_SRV_SERVER_START,
    ZAP_SRV_SERVER_STOP,
    ZAP_SRV_SERVER_ABORT,
    ZAP_SRV_USAGE,
    ZAP_SRV_CAUGHT_ERROR,
    ZAP_SRV_MAX_CLIENT_ERR,
    ZAP_SRV_CLIENT_CONNECT,
    ZAP_SRV_CLIENT_ERR,
    ZAP_SRV_DISCONNECT_CLIENT,
    ZAP_SRV_JOIN_TEAM,
    ZAP_SRV_JOIN_TEAM_ERR,
    ZAP_SRV_JOIN_FULL_TEAM,

    ZAP_SRV_STRING_MAX
} zap_srv_string_entries_t;

const char *fetch_string(const zap_srv_string_entries_t entry);

#endif /* !STRING_ENTRY_TABLE_H_ */
