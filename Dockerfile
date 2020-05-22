FROM yg397/thrift-microservice-deps:xenial

ARG NUM_CPUS=40

COPY ./ /auto_microservices
RUN cd /auto_microservices \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make -j${NUM_CPUS} \
    && make install

WORKDIR /auto_microservices