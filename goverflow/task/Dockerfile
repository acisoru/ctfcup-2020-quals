FROM ubuntu:18.04

RUN apt-get update && apt-get install socat sudo -yqq \
  && rm -rf /var/lib/apt/lists/*
WORKDIR /task

COPY ./vuln ./
COPY ./flag.txt ./
COPY ./server.sh /

EXPOSE 1337
ENTRYPOINT /server.sh

