FROM ubuntu:18.04
WORKDIR /usr/local/src

RUN apt-get -qq update && apt-get install -q -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y
RUN apt-get -qq update && apt-get install -qy g++ gcc git wget
RUN apt-get install -y cmake 3.10.2

# Download and install Boost
RUN apt -y install libboost-all-dev

# Download and install TBB
RUN apt -y install libtbb-dev

# Download and install pagmo
RUN wget https://github.com/esa/pagmo2/archive/v2.15.0.tar.gz && \
    tar zxf v2.15.0.tar.gz -C /usr/include/ && \
    cd /usr/include && \
    mv pagmo2-2.15.0 pagmo && \
    cd /usr/include/pagmo && \
    mkdir build && \
    cd build && \
    cmake ../  && \
    cmake --build . && \
    cmake  --build . --target install

COPY maker.cpp /usr/local/src/

ENV LD_LIBRARY_PATH /usr/local/lib

ENTRYPOINT /bin/bash
