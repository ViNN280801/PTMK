FROM alpine as console_app

RUN apk add build-base cmake make
WORKDIR /app
COPY . .

RUN cmake . && \
    cmake --build .

FROM alpine:latest

COPY --from=console_app /app /app
WORKDIR /app
