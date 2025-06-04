/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recv
*/

#include "server_internal.h"

static char *try_realloc(char **line, size_t size)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;
    char *new_line = NULL;

    TRY(code, except_ctxt) {
        if (size <= ZAP_SRV_MAX_LINE_SIZE) {
            new_line = (char *)safe_realloc(*line, sizeof(char) * size, NULL);
        }
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        END_TRY;
        return NULL;
    } CATCH_END(code);
    END_TRY;
    return new_line;
}

static int resize_buffer(char **line, size_t *buffer_size)
{
    char *new_line = try_realloc(line, *buffer_size * 2);

    if (!new_line) {
        safe_free((void **)line);
        return -1;
    }
    memset(line[*buffer_size], 0, *buffer_size);
    *buffer_size *= 2;
    *line = new_line;
    return 0;
}

static ssize_t handle_read_error(char **line, ssize_t bytes_read, ssize_t len)
{
    if (bytes_read == 0 && len == 0) {
        safe_free((void **)line);
        *line = NULL;
        return -1;
    }
    if (bytes_read < 0) {
        safe_free((void **)line);
        return -1;
    }
    (*line)[len + 1] = '\0';
    return len;
}

static int initial_error_handling(char **line, size_t buffer_size,
    zap_srv_socket_t *client)
{
    int error = 0;
    socklen_t len = sizeof(error);

    if (client->fd == ZAP_SRV_SOCK_ERROR)
        return -1;
    if (getsockopt(client->fd, SOL_SOCKET, SO_ERROR, &error, &len) != 0) {
        handle_client_disconnect(client);
        return -1;
    }
    if (!line)
        return -1;
    if (!*line) {
        *line = (char *)safe_calloc(buffer_size, sizeof(char), NULL);
    }
    return 0;
}

static int is_valid_char(char c)
{
    return c == '\n' || c == '\t' || (c >= 32 && c <= 126);
}

ssize_t recv_client(char **line, zap_srv_socket_t *client, size_t *buf_size)
{
    char c = 0;
    ssize_t len = 0;
    ssize_t bytes_read = 0;

    if (*buf_size == 0)
        *buf_size = ZAP_SRV_COMMAND_LENGTH;
    if (initial_error_handling(line, *buf_size, client) == -1)
        return -1;
    for (bytes_read = read(client->fd, &c, 1); bytes_read > 0;
        bytes_read = read(client->fd, &c, 1)) {
        if (!is_valid_char(c) || ((size_t)(len + 1) >= *buf_size &&
            resize_buffer(line, buf_size) == -1))
            return -1;
        (*line)[len] = c;
        len++;
        if (c == '\n')
            break;
    }
    return handle_read_error(line, bytes_read, len);
}
