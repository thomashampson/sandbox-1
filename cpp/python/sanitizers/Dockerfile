FROM ubuntu:bionic

# add kitware repository
RUN apt-get update && apt-get install -y \
    apt-transport-https \
    ca-certificates \
    gnupg \
    software-properties-common \
    wget && \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add - && \
    apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'

RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    g++-7 \
    g++-8 \
    libboost-python-dev \
    ninja-build \
    python3-dev

RUN useradd \
    --create-home \
    --user-group \
    --uid 1000 \
    builder

RUN mkdir /src && \
    mkdir /build && \
    chown builder:builder /build

USER 1000:1000

WORKDIR /build
