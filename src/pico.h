/* picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael */
#ifndef __PICO_H__
#define __PICO_H__

#include "php.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/standard/info.h"
#include "ext/standard/php_array.h"
#include "ext/standard/php_string.h"
#include "ext/standard/php_var.h"
#include "zend_exceptions.h"
#include "picohttpparser.c"

#define DEFAULT_HTTP_HEADER_LIMIT 100

typedef struct phr_header phr_header_t;

/* safe rendition of native C strncpy (adapted from https://github.com/ariadnavigo/strlcpy) */
static size_t php_strncpy(char *dst, char *src, size_t nbytes);
/* parses an HTTP request */
static void parse_http_request(INTERNAL_FUNCTION_PARAMETERS);
/* parses an HTTP response */
static void parse_http_response(INTERNAL_FUNCTION_PARAMETERS);

#define PHP_PICOHTTP_THROW(message) zend_throw_exception(spl_ce_RuntimeException, message, 0);

#endif
