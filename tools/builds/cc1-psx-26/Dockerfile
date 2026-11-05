FROM fedora:43 AS build
RUN dnf install -y -q make patch gcc-15.3.1-1.fc43 glibc-static-2.42-17.fc43 binutils-2.45.1-5.fc43 && dnf clean all

WORKDIR /work
RUN curl -fsSLO https://mirrors.slackware.com/slackware/slackware-2.2.0/source/d/gcc/gcc-2.6.3.tar.gz
RUN echo "66529b6ced4ccc580ec365809c1abed856d948283deff656801dec14f47d081a  gcc-2.6.3.tar.gz" | sha256sum -c
RUN tar xzf gcc-2.6.3.tar.gz

WORKDIR /work/gcc-2.6.3
COPY cc1-psx-26.patch /work/
RUN patch -su -p1 < /work/cc1-psx-26.patch

RUN touch -c cp/parse.y cp/parse.h cp/parse.c
RUN touch insn-config.h

RUN ./configure \
    --target=mips-sony-psx \
    --prefix=/opt/cross \
    --with-endian-little \
    --with-gnu-as \
    --host=i386-pc-linux \
    --build=i386-pc-linux

ENV CFLAGS="-std=gnu89 -w -static -O2 -fno-pie -flto=auto -Dbsd4_4 -Dmips -DHAVE_STRERROR -DHZ=100 \
    -DIO_BUFFER_SIZE=65536 -Dgetc=getc_unlocked -Dputc=putc_unlocked"
ENV LDFLAGS="-no-pie -flto=auto"

RUN make -j$(nproc) insn-config.h insn-flags.h insn-codes.h insn-attr.h CFLAGS="$CFLAGS"
RUN make -j$(nproc) cc1 CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS"
RUN strip cc1

WORKDIR /release
RUN cp /work/gcc-2.6.3/cc1 cc1-psx-26
RUN tar --owner=0 --group=0 --mtime=@0 -cf - cc1-psx-26 | gzip -9n > cc1-psx-26.tar.gz
RUN mkdir bin && mv cc1-psx-26.tar.gz bin/ && sha256sum bin/cc1-psx-26.tar.gz > cc1-psx-26.tar.gz.sha256

FROM scratch AS export
COPY --from=build /release/bin/cc1-psx-26.tar.gz /release/cc1-psx-26.tar.gz.sha256 /
