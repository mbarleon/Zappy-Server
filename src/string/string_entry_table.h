/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** string_entry_table
*/

#ifndef STRING_ENTRY_TABLE_H_
    #define STRING_ENTRY_TABLE_H_

typedef enum {
    ZAP_SRV_STRING_MIN = 0,
    ZAP_SRV_SOCKET_FAIL,
    ZAP_SRV_BIND_FAIL,
    ZAP_SRV_GETSOCKNAME_FAIL,
    ZAP_SRV_LISTEN_FAIL,
    ZAP_SRV_SERVER_START,
    ZAP_SRV_SERVER_STOP,
    ZAP_SRV_SERVER_ABORT,
    ZAP_SRV_USAGE,
    ZAP_SRV_PARSING_ERROR,
    ZAP_SRV_RUNTIME_ERROR,
    ZAP_SRV_STRING_MAX
} zap_srv_string_entries_t;

const char *fetch_string(const zap_srv_string_entries_t entry);

#endif /* !STRING_ENTRY_TABLE_H_ */
