FROM library/opensuse:tumbleweed
MAINTAINER mvyskocil@opensuse.org

RUN zypper --non-interactive addrepo -G --name 'zeromq' https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/openSUSE_Tumbleweed/network:messaging:zeromq:git-draft.repo
RUN zypper --non-interactive repos --details
RUN zypper --non-interactive refresh -f
RUN zypper --non-interactive install generator-scripting-language malamute-devel zproto zyre-devel vim nano gcc gcc-c++ make automake autoconf libtool asciidoc xmlto git valgrind zproject

RUN useradd -g users -m -s /bin/bash zeromq

RUN for repo in "czmq" "libzmq" "gsl" "malamute" "zproject" "zproto" "zyre"; do git clone -o upstream "https://github.com/zeromq/${repo}"; done
