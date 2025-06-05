/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** recv
*/

#include "server_internal.h"

/**
 * @brief Attempts to reallocate memory for a line buffer with exception
 * handling.
 *
 * This function tries to reallocate the memory pointed to by `*line` to the
 * specified `size` (in bytes), but only if `size` does not exceed
 * `ZAP_SRV_MAX_LINE_SIZE`.  Memory allocation is performed using
 * `safe_realloc`, and exceptions are handled using the TRY/CATCH macros. If a
 * bad allocation occurs (`CEXTEND_EXCEPTION_BAD_ALLOC`), the function returns
 * NULL.
 *
 * @param line Pointer to the buffer pointer to be reallocated.
 * @param size The new size (in bytes) for the buffer.
 * @return A pointer to the newly allocated buffer on success, or NULL on
 * allocation failure.
 */
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

/**
 * @brief Resizes the buffer pointed to by 'line' to twice its current size.
 *
 * This function attempts to reallocate the memory for the buffer pointed to by
 * 'line' to double its current size. If the reallocation is successful, it
 * zeroes out the newly allocated portion of the buffer, updates the buffer
 * size, and updates the pointer to the new buffer. If the reallocation fails,
 * it frees the original buffer and returns -1.
 *
 * @param line Pointer to the buffer pointer to be resized.
 * @param buffer_size Pointer to the current size of the buffer; will be
 * updated.
 * @return 0 on success, -1 on failure.
 */
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

/**
 * @brief Handles errors and end-of-file conditions after attempting to read
 * data into a line buffer.
 *
 * This function checks the result of a read operation and manages the memory
 * of the line buffer accordingly.
 * - If no bytes were read and the buffer length is zero, it frees the buffer,
 *   sets the pointer to NULL, and returns -1.
 * - If a read error occurred (bytes_read < 0), it frees the buffer and returns
 *   -1.
 * - Otherwise, it null-terminates the buffer at position len + 1 and returns
 *   the length.
 *
 * @param line Pointer to the buffer containing the read line. May be freed and
 * set to NULL on error.
 * @param bytes_read The result of the read operation (number of bytes read, 0
 * for EOF, or negative for error).
 * @param len The current length of the buffer.
 * @return ssize_t The length of the buffer on success, or -1 on error or EOF.
 */
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

/**
 * @brief Performs initial error handling for a client socket and ensures the
 * line buffer is allocated.
 *
 * This function checks for socket errors using getsockopt() and handles client
 * disconnection if an error is detected. It also verifies that the provided
 * line buffer pointer is valid and allocates memory for it if necessary.
 *
 * @param line Pointer to a character buffer pointer to be checked or
 * allocated.
 * @param buffer_size The size to allocate for the line buffer if it is not
 * already allocated.
 * @param client Pointer to the zap_srv_socket_t structure representing the
 * client socket.
 * @return 0 on success, -1 on error (e.g., invalid socket, getsockopt failure,
 * or invalid line pointer).
 */
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

/**
 * @brief Checks if a character is valid for input processing.
 *
 * A character is considered valid if it is a newline ('\n'), a tab ('\t'),
 * or any printable ASCII character (from space ' ' (32) to tilde '~' (126)).
 *
 * @param c The character to validate.
 * @return Non-zero if the character is valid, 0 otherwise.
 */
static int is_valid_char(char c)
{
    return c == '\n' || c == '\t' || (c >= 32 && c <= 126);
}

/**
 * @brief Reads a line from the specified client socket into a dynamically
 * allocated buffer.
 *
 * This function reads characters one by one from the client's file descriptor
 * until a newline character is encountered or an error occurs. The buffer is
 * resized dynamically if needed. It performs initial error handling and
 * validates each character read.
 *
 * @param line Pointer to a buffer pointer where the read line will be stored.
 * The buffer is  allocated and/or resized as necessary.
 * @param client Pointer to the zap_srv_socket_t structure representing the
 * client socket.
 * @param buf_size Pointer to a size_t variable holding the current buffer
 * size. It is updated if the buffer is resized.
 *
 * @return The number of bytes read on success, or -1 on error.
 */
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
