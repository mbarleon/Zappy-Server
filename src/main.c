/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** main
*/

#include "macro.h"
#include <stdio.h>
#include <string.h>
#include "cextend/logger.h"
#include "cextend/exception.h"
#include "parse_args/parse_args.h"

static void print_helper(void)
{
    printf("Helper\n");
}

static int try_parse_args(int ac, const char **av,
    zap_srv_parsed_context_t *ctxt)
{
    cextend_exception_code_t code = 0;
    cextend_exception_context_t *except_ctxt = INIT_TRY;

    TRY(code, except_ctxt) {
        parse_args(ac, av, ctxt);
    } CATCH(code, CEXTEND_EXCEPTION_BAD_ALLOC) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "Caught exception in parsing: %s",
            get_exception_str(code));
        return ZAP_SRV_ERROR;
    } CATCH(code, CEXTEND_EXCEPTION_INVALID_ARGUMENT) {
        CEXTEND_LOG(CEXTEND_LOG_ERROR, "Caught exception in parsing: %s",
            get_exception_str(code));
        return ZAP_SRV_ERROR;
    } CATCH_END(code);
    END_TRY;
    return ZAP_SRV_SUCCESS;
}

int main(int ac, const char **av)
{
    zap_srv_parsed_context_t ctxt;

    for (int i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-h") == 0) {
            print_helper();
            return 0;
        }
    }
    if (try_parse_args(ac, av, &ctxt) == ZAP_SRV_ERROR) {
        return ZAP_SRV_ERROR;
    }
    CEXTEND_LOG(CEXTEND_LOG_INFO, "Hello, World!");
    return ZAP_SRV_SUCCESS;
}
