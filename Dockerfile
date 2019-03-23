FROM ubuntu:18.04

WORKDIR /work

ENV PYTHON_INC_DIRS /usr/include/python3.5
ENV PYTHON_LIB_DIR /usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/

RUN mkdir challenge

COPY . challenge

RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y git gcc g++ make python3-dev uuid-dev wget

RUN wget https://github.com/Kitware/CMake/archive/v3.13.4.tar.gz && \
tar xf v3.13.4.tar.gz && \
cd CMake-3.13.4 && \
./bootstrap && make && make install && \
cd ..

RUN wget https://github.com/google/googletest/archive/release-1.8.1.tar.gz && \
tar xf release-1.8.1.tar.gz && \
cd googletest-release-1.8.1 && \
cmake -DBUILD_SHARED_LIBS=ON . && \
cmake --build . --target install && \
cd ..

RUN mkdir build && cd build && \
cmake -G "Unix Makefiles" . -DCMAKE_BUILD_TYPE=Release /work/challenge && \
cmake --build . 