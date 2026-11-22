#!/usr/bin/env bash

# Bash script for running both servers

# Server 1 (TCP_Server)
kitty --title "TCP SERVER" sh -c './tcp_server/server; exec sh' &
echo $! > tcp_kitt.pid

# Server 2 (http gateway)
kitty --title "Gateway" sh -c ' ./http_gateway/server;exec sh' &
echo $! > http_gateway.pid

