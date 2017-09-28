FROM library/opensuse:tumbleweed
MAINTAINER mvyskocil@opensuse.org

RUN zypper --non-interactive addrepo -G --name 'zeromq' https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/openSUSE_Tumbleweed/network:messaging:zeromq:git-draft.repo
RUN zypper --non-interactive refresh -f
RUN zypper --non-interactive install generator-scripting-language malamute-devel zproto zyre-devel vim nano gcc make automake autoconf libtool asciidoc xmlto git valgrind
# FIXME: add zproject to dependiencies

RUN useradd -g users -m -s /bin/bash zeromq

#TODO: clone all zeromq git repositories?
