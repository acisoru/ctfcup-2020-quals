#!/bin/bash

socat tcp-l:1337,fork,reuseaddr exec:"sudo -u nobody /task/vuln"

