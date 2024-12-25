/* picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael */
#include "pico.h"

static void parse_http_request(INTERNAL_FUNCTION_PARAMETERS)
{
  zend_string *request;
  int http_parser, http_minor_version;
  zval retval, retval_headers;
  char *method, *path;
  size_t header_count, method_len, path_len, buffer_len;
  zend_long header_limit = DEFAULT_HTTP_HEADER_LIMIT;

  ZEND_PARSE_PARAMETERS_START(1, 2)
  Z_PARAM_STR(request)
  Z_PARAM_OPTIONAL
  Z_PARAM_LONG(header_limit)
  ZEND_PARSE_PARAMETERS_END();

  buffer_len = ZSTR_LEN(request);
  phr_header_t headers[(size_t)header_limit];
  char buffer[(size_t)buffer_len];

  header_count = sizeof(headers) / sizeof(headers[0]);
  php_strncpy(buffer, ZSTR_VAL(request), buffer_len + 1);

  http_parser = phr_parse_request(
    buffer, buffer_len, (const char **)&method, &method_len, (const char **)&path,
    &path_len, &http_minor_version, headers, &header_count, 0);

  if (http_parser < 0)
  {
    PHP_PICOHTTP_THROW("There is an error in the HTTP request syntax");
    RETURN_NULL();
  }

  array_init(&retval);
  array_init(&retval_headers);

  char *body, tmp_method[method_len], tmp_path[path_len];
  body = buffer + http_parser;

  php_strncpy(tmp_method, method, method_len + 1);
  php_strncpy(tmp_path, path, path_len + 1);

  add_assoc_string(&retval, "path", tmp_path);
  add_assoc_string(&retval, "method", tmp_method);
  add_assoc_string(&retval, "body", body);

  // initialize array for response headers
  for (size_t idx = 0; idx < header_count; idx++)
  {
    if (headers[idx].name && headers[idx].value)
    {
      char tmp_header_name[headers[idx].name_len], tmp_header_value[headers[idx].value_len];
      php_strncpy(tmp_header_name, (char *)headers[idx].name, headers[idx].name_len + 1);
      php_strncpy(tmp_header_value, (char *)headers[idx].value, headers[idx].value_len + 1);

      add_assoc_string(&retval_headers, tmp_header_name, tmp_header_value);
    }
  }

  add_assoc_zval(&retval, "headers", &retval_headers);

  RETURN_ZVAL(&retval, 0, 1);
}
static void parse_http_response(INTERNAL_FUNCTION_PARAMETERS)
{
  zend_string *response;
  int http_parser, http_minor_version, http_status;
  zval retval, retval_headers;
  char *message;
  size_t header_count, message_len, buffer_len;
  zend_long header_limit = DEFAULT_HTTP_HEADER_LIMIT;

  ZEND_PARSE_PARAMETERS_START(1, 2)
  Z_PARAM_STR(response)
  Z_PARAM_OPTIONAL
  Z_PARAM_LONG(header_limit)
  ZEND_PARSE_PARAMETERS_END();

  buffer_len = ZSTR_LEN(response);
  phr_header_t headers[(size_t)header_limit];
  char buffer[(size_t)buffer_len];

  header_count = sizeof(headers) / sizeof(headers[0]);
  php_strncpy(buffer, ZSTR_VAL(response), buffer_len + 1);

  http_parser = phr_parse_response(
    buffer, buffer_len, &http_minor_version, &http_status, (const char **)&message,
    &message_len, headers, &header_count, 0);

  if (http_parser < 0)
  {
    PHP_PICOHTTP_THROW("There is an error in the HTTP response syntax");
    RETURN_NULL();
  }

  array_init(&retval);
  array_init(&retval_headers);

  char tmp_message[message_len], *body;
  php_strncpy(tmp_message, message, message_len + 1);
  body = buffer + http_parser;

  add_assoc_string(&retval, "reason", tmp_message);
  add_assoc_long(&retval, "status", http_status);
  add_assoc_string(&retval, "body", body);

  for (size_t idx = 0; idx < header_count; idx++)
  {
    if (headers[idx].name && headers[idx].value)
    {
      char tmp_header_name[headers[idx].name_len], tmp_header_value[headers[idx].value_len];
      php_strncpy(tmp_header_name, (char *)headers[idx].name, headers[idx].name_len + 1);
      php_strncpy(tmp_header_value, (char *)headers[idx].value, headers[idx].value_len + 1);

      add_assoc_string(&retval_headers, tmp_header_name, tmp_header_value);
    }
  }

  add_assoc_zval(&retval, "headers", &retval_headers);
  RETURN_ZVAL(&retval, 0, 1);
}
static size_t php_strncpy(char *dst, char *src, size_t nbytes)
{
  const char *osrc = src;
  size_t nleft = nbytes;

  // copy as many bytes as will fit
  if (nleft != 0)
  {
    while (--nleft != 0)
    {
      if ((*dst++ = *src++) == '\0')
        break;
    }
  }

  // not enough room in dst, add null byte and traverse rest of src
  if (nleft == 0)
  {
    if (nbytes != 0)
      *dst = '\0';
    while (*src++)
      ;
  }

  return (src - osrc - 1);
}
