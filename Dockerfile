# build container and tag it as sotn-build:latest
# docker build --tag sotn-build:latest . 

# launch container and mount current directory under /sotn 
# docker run --rm -it -v $(pwd):/sotn sotn-build /bin/bash

# cd /sotn
# make extract -j && make build -j
FROM ubuntu:22.04
RUN apt-get update
ADD tools tools
RUN apt-get install -y $(cat tools/requirements-debian.txt)
RUN pip3 install -r tools/requirements-python.txt 
