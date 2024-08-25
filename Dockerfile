FROM ubuntu:latest
RUN apt-get update \
  && apt-get install -y python3 build-essential make sudo git cmake doxygen \
  && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash barry && echo '%sudo ALL=(ALL:ALL) ALL' >> /etc/sudoers
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







