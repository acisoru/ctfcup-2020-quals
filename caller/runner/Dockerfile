FROM docker:19.03

RUN apk update && \
    apk add socat

RUN adduser -s /bin/false -H -D caller-runner

RUN mkdir -p /var/caller-runner/

WORKDIR /var/caller-runner/

COPY ./service/ ./service/

COPY ./runner/entrypoint.sh ./runner/run.sh ./

RUN chmod +x ./entrypoint.sh ./run.sh

USER caller-runner

ENTRYPOINT ./entrypoint.sh
