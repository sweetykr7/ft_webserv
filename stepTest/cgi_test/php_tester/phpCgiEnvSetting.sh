#!/bin/bash

export REDIRECT_STATUS=200
export CONTENT_TYPE=application/x-www-form-urlencoded
export CONTENT_LENGTH=-1
export SERVER_PROTOCOL=HTTP/1.1
export GATEWAY_INTERFACE=CGI/1.1
export REQUEST_METHOD=GET
export REQUEST_URI=./test.php
export PATH_INFO=./test.php
export PATH_TRANSLATED=./test.php
export SCRIPT_NAME=./test.php
export SCRIPT_FILENAME=./test.php
export QUERY_STRING="name=test&id=this"
export SERVER_NAME=
export SERVER_PORT=8080
export HTTP_HOST=localhost
export REMOTE_ADDR=
export REMOTE_HOST=
export REMOTE_IDENT=
export SERVER_SOFTWARE=webserv/1.0

# ./php-cgi
./php_test