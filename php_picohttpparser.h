/* picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael */
#ifndef PHP_PICOHTTPPARSER_H
#define PHP_PICOHTTPPARSER_H

extern zend_module_entry picohttpparser_module_entry;

#define PHP_PICOHTTPPARSER_VERSION "0.1.0"
#define PHP_PICOHTTPPARSER_AUTHOR "Lochemem Bruno Michael"

#if defined(ZTS) && defined(COMPILE_DL_PICOHTTPPARSER)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* PHP_PICOHTTPPARSER_H */
