--TEST--
picohttp_parse_request() throws exception when invalid HTTP request syntax is encountered
--FILE--
<?php

try {
  var_dump(
    \picohttp_parse_request("foo\nbar\n"),
  );
} catch (Throwable $err) {
  var_dump(
    $err->getMessage(),
  );
}

?>
--EXPECT--
string(44) "There is an error in the HTTP request syntax"
