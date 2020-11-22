FROM python:3.7

RUN apt update && \
    apt install -y libmpfr-dev libmpc-dev socat

RUN pip install gmpy2

RUN useradd -s /bin/false -M warmer

RUN mkdir -p /var/warmer/

WORKDIR /var/warmer/

COPY warmer.py flag.txt entrypoint.sh run.sh ./

RUN chmod +x ./entrypoint.sh ./run.sh

USER warmer

ENTRYPOINT ./entrypoint.sh
