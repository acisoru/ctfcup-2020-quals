#!/bin/sh

docker run \
    --rm \
    --interactive \
    --cpus 0.1 \
    --memory 8M \
    --memory-swap 8M \
    --network none \
    --pids-limit 16 \
    --ulimit nofile=32:32 \
    --read-only \
    --stop-timeout 1 \
    esoteric-service
