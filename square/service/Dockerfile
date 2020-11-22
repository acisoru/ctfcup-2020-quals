FROM python:3.7

RUN apt update && \
    apt install -y libmpfr-dev libmpc-dev socat

RUN pip install gmpy2

RUN useradd -s /bin/false -M square

RUN mkdir -p /var/square/

WORKDIR /var/square/

COPY square.py flag.txt entrypoint.sh run.sh ./

RUN chmod +x ./entrypoint.sh ./run.sh

USER square

ENTRYPOINT ./entrypoint.sh
