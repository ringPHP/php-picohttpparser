/* picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "src/pico.c"
#include "php_picohttpparser.h"
#include "picohttpparser_arginfo.h"

/* {{{ picohttp_parse_request( string request [, int header_limit = 100 ] ) */
PHP_FUNCTION(picohttp_parse_request)
{
  parse_http_request(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ picohttp_parse_response( string request [, int header_limit = 100 ] ) */
PHP_FUNCTION(picohttp_parse_response)
{
  parse_http_response(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(picohttpparser)
{
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(picohttpparser)
{
#if defined(ZTS) && defined(COMPILE_DL_PICOHTTPPARSER)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(picohttpparser)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "picohttpparser support", "enabled");
  php_info_print_table_header(2, "picohttpparser version", PHP_PICOHTTPPARSER_VERSION);
  php_info_print_table_header(2, "picohttpparser author", PHP_PICOHTTPPARSER_AUTHOR);
  php_info_print_table_end();
}
/* }}} */

zend_module_entry picohttpparser_module_entry = {
    STANDARD_MODULE_HEADER,
    "picohttpparser",           /* extension name */
    picohttpparser_functions,   /* zend_function_entry */
    NULL,                       /* PHP_MINIT - module initialization */
    NULL,                       /* PHP_MSHUTDOWN - module shutdown */
    PHP_RINIT(picohttpparser),  /* PHP_RINIT - request initialization */
    NULL,                       /* PHP_RSHUTDOWN - request shutdown */
    PHP_MINFO(picohttpparser),  /* PHP_MINFO - module information */
    PHP_PICOHTTPPARSER_VERSION, /* module version */
    STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_PICOHTTPPARSER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(picohttpparser)
#endif
