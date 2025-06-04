/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** string_entry_table
*/

#include "string_entry_table.h"

static const char *string_table[] = {
    "Missing string in string entry table.",

    "socket failed.",
    "bind failed.",
    "getsockname failed.",
    "listen failed.",
    "Server listening on %s:%d.",
    "Stopping server...",
    "%d SIGINT or SIGTERM detected, aborting.",
    ("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c "
        "clientsNb -f freq\n"),
    "Caught exception in %s: %s",

    "Missing string in string entry table."
};

const char *fetch_string(const zap_srv_string_entries_t entry)
{
    if (entry <= ZAP_SRV_STRING_MIN || entry >= ZAP_SRV_STRING_MAX) {
        return string_table[ZAP_SRV_STRING_MAX];
    }
    return string_table[entry];
}
