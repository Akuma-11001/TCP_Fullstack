#!/usr/bin/env bash


# The bash script for stopping both servers

kill "$(cat tcp_kitt.pid)" 2>/dev/null
kill "$(cat http_gateway.pid)" 2>/dev/null

rm -f tcp_kitt.pid http_gateway.pid

