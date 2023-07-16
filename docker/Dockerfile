FROM ubuntu:20.04

# Set default shell during Docker image build to bash
SHELL ["/bin/bash", "-c"]

ENV TZ=Asia/Tehran
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

LABEL maintainer="Mohammad Niaraki <mohammadniaraki@outlook.com>"

# Download Linux support tools
RUN apt-get update && apt-get clean && apt-get install -y \
      build-essential git wget python3 doxygen graphviz gcovr lcov cppcheck \
      python3-pip flawfinder clang-format \
      && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Lizard
RUN pip3 install lizard

# Get and install the CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.2/cmake-3.24.2-linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh   

ENV PATH="/usr/bin/cmake/bin:${PATH}"

# Install ARM compiler
RUN mkdir /stm32 \ 
      && mkdir /stm32/toolchain \
      && cd /stm32/toolchain \
      && wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \ 
      && tar xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
      && rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

ENV PATH="/stm32/toolchain/gcc-arm-none-eabi-10.3-2021.10/bin:${PATH}"

# Set up the working directory
WORKDIR /home/project
