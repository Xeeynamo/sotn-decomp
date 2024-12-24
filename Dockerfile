# build container and tag it as sotn-build:latest
# docker build --tag sotn-build:latest --build-arg USER=$USER .

# launch container and mount current directory under /sotn
# docker run --rm -it -v $(pwd):/sotn sotn-build /bin/bash

# make extract -j && make build -j
FROM ubuntu:22.04
ADD /tools/requirements-debian.txt /tools/requirements-debian.txt
RUN apt-get update && apt-get install -y $(cat /tools/requirements-debian.txt)

WORKDIR /sotn
ARG USER
RUN adduser ${USER}
ENV VENV_PATH=/tools/.venv
RUN mkdir -p ${VENV_PATH}
RUN chown ${USER} /sotn ${VENV_PATH}
USER ${USER}
# this is similar to `make python-dependencies`, however,
# the Makefile is not available until a container has
# been created.
ADD tools/requirements-python.txt /tools/requirements-python.txt
RUN python3 -m venv ${VENV_PATH} && \
    . ${VENV_PATH}/bin/activate && \
    pip install -r /tools/requirements-python.txt
RUN git config --global --add safe.directory /sotn
