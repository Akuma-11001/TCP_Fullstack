#!/usr/bin/env bash


# Compile every program inside this project

set -e # stops the script anything doesnt work



printf "\n"
printf "\n"

printf "Compiling TCP server\n"

make -C ./tcp_server


printf "\n"
printf "\n"



printf "Compiling HTTP Gateway Server\n"
make -C ./http_gateway

printf "\n"

echo "Done."
