FROM ubuntu:18.04

RUN apt update && \
    apt install -y python3.7

RUN useradd -s /bin/false -M caller

RUN mkdir -p /var/caller/

WORKDIR /var/caller/

COPY caller.py flag.txt ./

USER caller

ENTRYPOINT python3.7 -uB caller.py
