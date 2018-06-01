FROM ubuntu:16.04
MAINTAINER Anurag Ghosh "anurag.ghosh@aricent.com"

RUN apt-get update && apt-get install -y libboost-all-dev

RUN mkdir /app
COPY ./edge_server /app
WORKDIR /app
CMD ["./edge_server"]
EXPOSE "10000"
