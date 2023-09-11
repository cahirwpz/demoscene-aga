# To build and publish image run following commands:
# > docker build -t toolchain-aga .
# > docker create --name bebbo toolchain-aga
# > docker cp bebbo:toolchain-aga.tar.gz .
# > docker rm bebbo

# FROM debian:bookworm-backports
FROM debian:bullseye-backports

WORKDIR /root

RUN apt-get -q update && apt-get upgrade -y
RUN apt-get install -y --no-install-recommends \
            autotools-dev bison curl flex g++ gcc gettext git lhasa \
            libgmp-dev libmpc-dev libmpfr-dev libncurses-dev make \
            patch python3-pip rsync texinfo wget
RUN git clone https://github.com/bebbo/amiga-gcc.git

WORKDIR /root/amiga-gcc
ENV CPU=68060
ENV PREFIX=/opt/bebbo

RUN make branch mod=gcc branch=amiga10
RUN make update
RUN make binutils
RUN make gcc
RUN make gdb
RUN make fd2sfd
RUN make fd2pragma
RUN make sfdc
RUN make vasm
RUN make libnix
RUN make libgcc
RUN make libdebug
RUN make ndk
RUN make sdk=ahi

WORKDIR /
RUN tar cvzf toolchain-aga.tar.gz /opt/bebbo
