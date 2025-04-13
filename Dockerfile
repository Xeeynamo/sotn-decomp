# HOW TO USE THIS DOCKERFILE
#
# 1. build image and tag it as sotn-build:latest
# docker build --tag sotn-build:latest .
#
# 2. launch container and mount current directory under /sotn
# docker run --name sotn-work -it -v $(pwd):/sotn -v sotn_venv:/sotn/.venv -v sotn_build:/sotn/build sotn-build
#
# 3. inside the container, sym-link the .venv dir and perform an update
# python3 -m venv .venv
# source .venv/bin/activate
# make update-dependencies
#
# 4. you now prepared an image that can help you build and work SOTN
# make -j extract && make -j -O build && make expected
#
# 5. from now on, to re-use the same container execute the following:
# docker start -ai sotn-work

# make extract -j && make build -j
FROM ubuntu:noble
COPY /tools/requirements-debian.txt /tools/requirements-debian.txt
RUN apt-get update && \
    apt-get install -y $(cat /tools/requirements-debian.txt) && \
    git clone --depth 1 https://github.com/sozud/dosemu-deb.git /dosemu && \
    dpkg -i /dosemu/fdpp_1.6-1_amd64.deb && \
    dpkg -i /dosemu/fdpp-dev_1.6-1_amd64.deb && \
    dpkg -i /dosemu/comcom32_0.1~alpha3-1_all.deb && \
    dpkg -i /dosemu/dosemu2_2.0~pre9-1_amd64.deb && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /sotn
RUN chown ubuntu:ubuntu /sotn
USER ubuntu
RUN mkdir -p /sotn/.venv /sotn/build

RUN git config --global --add safe.directory /sotn
ENTRYPOINT ["/bin/bash"]
