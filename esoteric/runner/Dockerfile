FROM docker:19.03

RUN apk update && \
    apk add socat

RUN adduser -s /bin/false -H -D esoteric-runner

RUN mkdir -p /var/esoteric-runner/

WORKDIR /var/esoteric-runner/

COPY ./service/ ./service/

COPY ./runner/entrypoint.sh ./runner/run.sh ./

RUN chmod +x ./entrypoint.sh ./run.sh

USER esoteric-runner

ENTRYPOINT ./entrypoint.sh
