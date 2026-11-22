From gcc:14

RUN apt-get update && \
    apt-get install -y make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY Shared_Protocol/ ./Shared_Protocol
COPY http_gateway/ ./http_gateway/

WORKDIR /app/http_gateway

RUN make

EXPOSE 9000

CMD ["./server"] 
