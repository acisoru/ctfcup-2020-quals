#!/bin/sh

# set timeout interval from env
TIMEOUT=${SERVICE_TIMEOUT:-30}

# run socat and handle connections
socat \
    TCP-LISTEN:31337,reuseaddr,fork \
    SYSTEM:"timeout -s KILL $TIMEOUT ./run.sh; \
            test \$? -eq 137 && echo 'Timeout'"
