FROM python:3.7-alpine

RUN adduser -s /bin/false -H -D esoteric

RUN mkdir -p /var/esoteric/

WORKDIR /var/esoteric/

COPY esoteric.py flag.txt ./

USER esoteric

ENTRYPOINT python3.7 -uB esoteric.py
