FROM debian:stable-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    valgrind \
    build-essential \
    gcc \
    g++ \
    clang \
    make \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
