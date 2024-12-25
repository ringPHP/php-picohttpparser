--TEST--
picohttp_parse_response() throws exception when invalid HTTP response syntax is encountered
--FILE--
<?php

try {
  var_dump(
    \picohttp_parse_response("foo\r\nbar\r\n"),
  );
} catch (Throwable $err) {
  var_dump(
    $err->getMessage(),
  );
}

?>
--EXPECT--
string(45) "There is an error in the HTTP response syntax"
