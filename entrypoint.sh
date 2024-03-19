#!/bin/sh

# This script is for the docker container to run the server or client

# Check the first argument for the program to run
if [ "$1" = 'server' ]; then
  # Shift to remove the first argument and pass the rest to the server
  shift
  exec ./server "$@"
elif [ "$1" = 'client' ]; then
  # Shift to remove the first argument and pass the rest to the client
  shift
  exec ./client "$@"
else
  echo "Unknown command: $1"
  echo "Usage: server <socket_path> | client <socket_path> <message>"
  exit 1
fi
