# HOW TO USE THIS DOCKERFILE
#
# 1. build image and tag it as sotn-build:latest
# docker build --tag sotn-build:latest .
#
# 2. launch container and mount current directory under /sotn
# docker run --name sotn-work -it -v $(pwd):/sotn -v sotn_venv:/sotn/.venv -v sotn_build:/sotn/build sotn-build
#
# 3. you are now ready to build and work on SOTN
# make expected
#
# 4. from now on, to re-use the same container execute the following:
# docker start -ai sotn-work

FROM ubuntu:noble

COPY /tools/requirements-debian.txt /tools/requirements-debian.txt
COPY /tools/requirements-python.txt /tools/requirements-python.txt
COPY --from=golang:1.24-bookworm /usr/local/go/ /usr/local/go/

WORKDIR /sotn
RUN apt-get update && \
    apt-get install -y $(cat /tools/requirements-debian.txt) && \
    git clone --depth 1 https://github.com/sozud/dosemu-deb.git /dosemu && \
    dpkg -i /dosemu/fdpp_1.6-1_amd64.deb && \
    dpkg -i /dosemu/fdpp-dev_1.6-1_amd64.deb && \
    dpkg -i /dosemu/comcom32_0.1~alpha3-1_all.deb && \
    dpkg -i /dosemu/dosemu2_2.0~pre9-1_amd64.deb && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /dosemu && \
    chown ubuntu:ubuntu /sotn

USER ubuntu
RUN mkdir -p /sotn/.venv /sotn/build && \
    mkdir -p ~/go/bin && \
    ln -s /usr/local/go/bin/go ~/go/bin/go && \
    git config --global --add safe.directory /sotn && \
    python3 -m venv .venv && \
    . .venv/bin/activate && \
    pip3 install -r /tools/requirements-python.txt

ENTRYPOINT ["/bin/bash"]
