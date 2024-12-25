--TEST--
picohttp_parse_request() parses HTTP request
--FILE--
<?php

var_dump(
  \picohttp_parse_request(
    "GET / HTTP/1.1\r\nhost: localhost:8080\r\ncontent-type: text/plain\r\n\r\n",
  ),
);
?>
--EXPECT--
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
    ["content-type"]=>
    string(10) "text/plain"
  }
}
