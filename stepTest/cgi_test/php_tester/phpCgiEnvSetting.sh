#!/bin/bash

export REDIRECT_STATUS=200
export CONTENT_TYPE=application/x-www-form-urlencoded
export CONTENT_LENGTH=-1
export SERVER_PROTOCOL=HTTP/1.1
export GATEWAY_INTERFACE=CGI/1.1
export REQUEST_METHOD=GET
export REQUEST_URI=./nginx_test/index.php
export PATH_INFO=./nginx_test/index.php
export PATH_TRANSLATED=./nginx_test/index.php
export SCRIPT_NAME=./nginx_test/index.php
export SCRIPT_FILENAME=./nginx_test/index.php
export QUERY_STRING="name=test&id=this"
export SERVER_NAME=
export SERVER_PORT=8080
export HTTP_HOST=localhost
export REMOTE_ADDR=
export REMOTE_HOST=
export REMOTE_IDENT=
export SERVER_SOFTWARE=webserv/1.0
export HTTP_COOKIE=session_id=webserv-Jacob

# ./php-cgi
./php_test