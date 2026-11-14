#!/usr/bin/env bash


# Bash script to stop every server running and start them again
set -e
Script_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"




"$Script_DIR/stop.sh"



"$Script_DIR/start.sh"
