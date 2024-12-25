/* picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael */
ZEND_BEGIN_ARG_INFO_EX(arginfo_picohttp_parse_request, 0, 0, 2)
ZEND_ARG_TYPE_INFO(0, request, IS_STRING, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, header_limit, IS_LONG, 0, "100")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_picohttp_parse_response, 0, 0, 2)
ZEND_ARG_TYPE_INFO(0, response, IS_STRING, 0)
ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, header_limit, IS_LONG, 0, "100")
ZEND_END_ARG_INFO()

ZEND_FUNCTION(picohttp_parse_request);
ZEND_FUNCTION(picohttp_parse_response);

static const zend_function_entry picohttpparser_functions[] = {
  ZEND_FE(picohttp_parse_request, arginfo_picohttp_parse_request)
    ZEND_FE(picohttp_parse_response, arginfo_picohttp_parse_response)
      PHP_FE_END};
