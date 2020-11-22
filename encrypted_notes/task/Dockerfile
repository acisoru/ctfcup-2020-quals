FROM ubuntu:18.04

RUN apt-get update && apt-get install socat sudo -yqq \
  && rm -rf /var/lib/apt/lists/*
WORKDIR /task

COPY ./flag.txt ./
COPY ./server.sh /
COPY vuln libc.so.6 ./

EXPOSE 1337
ENTRYPOINT /server.sh
