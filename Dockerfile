# build container and tag it as sotn-build:latest
# docker build --tag sotn-build:latest --build-arg USER=$USER .

# launch container and mount current directory under /sotn
# docker run --rm -it -v $(pwd):/sotn sotn-build /bin/bash

# make extract -j && make build -j
FROM ubuntu:22.04
ARG USER
RUN adduser ${USER}
RUN apt-get update
ADD tools tools
RUN apt-get install -y $(cat tools/requirements-debian.txt)
RUN mkdir /sotn
WORKDIR /sotn
ENV VENV_PATH=/tools/.venv
RUN mkdir $VENV_PATH
RUN chown ${USER} /sotn $VENV_PATH
USER ${USER}
# this is similar to `make python-dependencies`, however,
# the Makefile is not available until a container has
# been created.
RUN cd /sotn && \
    python3 -m venv $VENV_PATH && \
    . $VENV_PATH/bin/activate && \
    pip install -r /tools/requirements-python.txt
RUN git config --global --add safe.directory /sotn
