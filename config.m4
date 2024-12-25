dnl picohttpparser extension for PHP (c) 2024 Lochemem Bruno Michael

PHP_ARG_WITH([picohttpparser],
  [for picohttpparser library],
  [AS_HELP_STRING([--with-picohttpparser],
    [specify path to picohttpparser library])],
  [no])

if test "$PHP_PICOHTTPPARSER" != "no"; then
  PHP_VERSION=$($PHP_CONFIG --vernum)
  AC_MSG_CHECKING([PHP version])
  if test $PHP_VERSION -lt 80100; then
    AC_MSG_ERROR([ext-picohttpparser requires PHP 8.1+])
  else
    AC_MSG_RESULT([ok])
  fi

  AC_MSG_CHECKING([for picohttpparser library])
  if test -s "$PHP_PICOHTTPPARSER/picohttpparser.c"; then
    AC_MSG_RESULT(found picohttpparser library)
  else
    AC_MSG_RESULT(picohttpparser is not downloaded)
    AC_MSG_ERROR(Please download picohttpparser)
  fi

  CFLAGS="-g -O3 -I$PHP_PICOHTTPPARSER/"
  AC_DEFINE(HAVE_PICOHTTPPARSER, 1, [Have picohttpparser support])

  PHP_NEW_EXTENSION(picohttpparser, php_picohttpparser.c, $ext_shared)
fi
