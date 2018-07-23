FROM library/opensuse:tumbleweed
MAINTAINER mvyskocil@opensuse.org

RUN zypper --non-interactive refresh -f
RUN zypper --non-interactive install pkg-config openpgm-devel libsodium-devel vim nano gcc gcc-c++ make automake autoconf libtool asciidoc xmlto git valgrind pcre-devel

RUN useradd -g users -m -s /bin/bash zeromq
USER zeromq
ADD build /home/zeromq/.build
USER root
RUN bash /home/zeromq/.build

USER zeromq
WORKDIR /home/zeromq
