# Build and run:
#   docker build -t clion/ubuntu/cpp-env:1.0 -f Dockerfile.cpp-env-ubuntu .

FROM gcc:12.2.0

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y build-essential \
      make \
      ninja-build \
      locales \
      cmake \
      rsync \
      tar \
      python \
      python-dev \
      python3-pip \
      nasm \
      ccache \
      libmpfr-dev \
      libmpc-dev \
      doxygen \
      grub-common \
      xorriso \
  && apt-get clean \
  && pip install conan

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

ARG UID=1000
RUN useradd -m -u 123123 -s /bin/bash builder
USER builder