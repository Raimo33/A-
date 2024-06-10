ARG DEPS = "build-essential cmake git libsfml-dev"
ARG DEST = "/app"

FROM ubuntu:24.04

ARG DEPS
ARG DEST

RUN apt-get update && apt-get install -y ${DEPS} && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY srcs ${DEST}

WORKDIR ${DEST}

RUN make && make clean

CMD ["./aStar"]