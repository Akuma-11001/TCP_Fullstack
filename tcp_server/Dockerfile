            
From gcc:14

RUN apt-get update && \
    apt-get install -y make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY Shared_Protocol/ ./Shared_Protocol
COPY tcp_server/ ./tcp_server/

WORKDIR /app/tcp_server

RUN make

EXPOSE 8005

CMD ["./server"]
