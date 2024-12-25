# ext-picohttpparser

A PHP port of the fast HTTP parser used in the [H2O project](https://github.com/h2o/h2o).

## Rationale

The picohttpparser project is a tiny, (near) stateless HTTP parser. The performance gains associated with the library are largely attributable to its zero-copy internals: it is almost entirely reliant on stack-allocated data structures. `ext-picohttpparser` is an attempt to expose the API of the aforedescribed eponymous lightweight, efficient parser to the PHP userspace.

## Requirements

- PHP 8.1 or newer
- [picohttpparser](https://github.com/h2o/picohttpparser)

## Installation

It is important to have all the aforelisted requirements at the ready before attempting to install `ext-picohttpparser`. The directives in the snippet to follow should allow you to build the extension's shared object file (`picohttpparser.so`).

```sh
$ git clone https://github.com/h2o/picohttpparser.git <picohttp-dir>
$ git clone https://github.com/ringphp/php-picohttpparser.git <dir>
$ cd <dir>
$ phpize
$ ./configure --with-picohttpparser=<picohttp-dir>
$ make && sudo make install
```

After successfully building the shared object, proceed to operationalize the extension by adding the line `extension=picohttpparser` to your `php.ini` file. If you prefer to perform the said operationalization via command line interface, the following should suffice.

```sh
$ printf "\nextension=picohttpparser\n" >> "$(php-config --ini-path)/php.ini"
```

## API Synopsis

```php
/* core functions */
picohttp_parse_request(string $request, int $header_limit = 100): array
picohttp_parse_response(string $response, int $header_limit = 100): array
```

- [picohttp_parse_request](#picohttp_parse_request)
- [picohttp_parse_response](#picohttp_parse_response)

### `parse_http_request`

```php
picohttp_parse_request(string $request, int $header_limit = 100): array
```

Parses an HTTP request.

**Parameter(s)**

- **request** (string) - The HTTP request to parse.
- **header_limit** (int) - The number of headers to parse.
  > The default limit is `100`.

**Return value(s)**

The parser will throw an exception in the event that an invalid HTTP request is encountered and will output a hashtable with the contents enumerated below otherwise.

- **body** (string) - The request body.
- **headers** (iterable) - An associative array containing request headers.
- **method** (string) - The request method.
- **path** (string) - The request path.

```php
$request = <<<EOF
GET / HTTP/1.1
host: localhost:8080
accept: */*


EOF;

var_dump(
  \picohttp_parse_request($request),
);
```

The example above will produce output similar to that in the snippet to follow.

```
array(4) {
  ["path"]=>
  string(1) "/"
  ["method"]=>
  string(3) "GET"
  ["body"]=>
  string(0) ""
  ["headers"]=>
  array(2) {
    ["host"]=>
    string(14) "localhost:8080"
    ["accept"]=>
    string(3) "*/*"
  }
}
```

### `picohttp_parse_response`

```php
picohttp_parse_response(string $response, int $header_limit = 100): array
```

Parses an HTTP response.

**Parameter(s)**

- **response** (string) - The HTTP response to parse.
- **header_limit** (int) - The number of headers to parse.
  > The default limit is `100`.

**Return value(s)**

The parser will throw an exception in the event that an invalid HTTP response is encountered and will output a hashtable with the contents enumerated below otherwise.

- **body** (string) - The response body.
- **headers** (iterable) - An associative array containing response headers.
- **status** (int) - The response status code.
- **reason** (string) - The response reason phrase.

```php
$response = <<<EOF
HTTP/1.1 200 OK
server: ringphp
content-type: application/json; charset=utf-8
content-length: 37

{
  "foo": "foo",
  "bar": "bar"
}
EOF;

var_dump(
  \picohttp_parse_response($response),
);
```

The example above will produce output similar to that in the snippet to follow.

```
array(4) {
  ["reason"]=>
  string(2) "OK"
  ["status"]=>
  int(200)
  ["body"]=>
  string(37) "{
  "foo": "foo",
  "bar": "bar"
}"
  ["headers"]=>
  array(3) {
    ["server"]=>
    string(7) "ringphp"
    ["content-type"]=>
    string(16) "application/json; charset=utf-8"
    ["content-length"]=>
    string(2) "37"
  }
}
```
