# Minimal image to create a PSX disk image with Maria replacing Richter.
#
# 1. build image
# docker build --tag sotn-maria:latest .
#
# 2. create the directory disks/ and place the following two files:
#   disks/sotn.us.bin
#   disks/sotn.pspeu.iso
#
# 3. generate disks/sotn_mariapsp.us.bin
# docker run --rm -v ./disks:/disks sotn-maria:latest

FROM sotn-build:latest

USER ubuntu
WORKDIR /disks
RUN git clone https://github.com/xeeynamo/sotn-decomp.git --branch master --depth 1 /sotn/sotn-decomp && \
    cp -r /sotn/.venv /sotn/sotn-decomp/ && \
    rm -rf /sotn/sotn-decomp/disks && \
    ln -s /disks /sotn/sotn-decomp/
WORKDIR /sotn/sotn-decomp/mods/mariapsp-forpsx
ENTRYPOINT ["make" "disk"]
