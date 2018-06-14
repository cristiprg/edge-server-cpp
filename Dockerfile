FROM ubuntu:16.04
MAINTAINER Anurag Ghosh "anurag.ghosh@aricent.com"

RUN apt-get update && apt-get install -y libboost-all-dev libopencv-dev

RUN mkdir /app
COPY ./DipperPointMapper /app
COPY ./demo.xml_misc.xml /app
COPY ./server_wrapper.sh /app
RUN chmod u+x /app/server_wrapper.sh /app/DipperPointMapper
WORKDIR /app
CMD ["./server_wrapper.sh"]
EXPOSE "10000"
