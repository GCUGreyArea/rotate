FROM ubuntu:latest

RUN apt update
RUN apt install python3 build-essential make sudo git cmake doxygen -y 
RUN useradd -ms /bin/bash barry
RUN echo "barry     ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers
RUN echo "barry:barry" | chpasswd
RUN echo "root:root" | chpasswd

WORKDIR /home/barry/rotate
RUN cd /home/barry \
    && git clone https://github.com/google/googletest.git \
    && cd googletest \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && cmake --build . \
    && cmake --install .

COPY . /home/barry/rotate

RUN cd /home/barry/rotate && make && make test
RUN find /home/barry -name "*" -exec chown barry {} \;
USER barry
ENV PATH=$PATH:/home/barry/rotate/build:/home/barry/rotate/test/build







