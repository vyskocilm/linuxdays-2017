FROM library/opensuse:tumbleweed
MAINTAINER mvyskocil@opensuse.org

RUN zypper --non-interactive addrepo -G --name 'zeromq-branch' http://download.opensuse.org/repositories/home:/mvyskocil:/branches:/network:/messaging:/zeromq:/git-draft/openSUSE_Tumbleweed/home:mvyskocil:branches:network:messaging:zeromq:git-draft.repo
RUN zypper --non-interactive addrepo -G --name 'zeromq' https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/openSUSE_Tumbleweed/network:messaging:zeromq:git-draft.repo
RUN zypper --non-interactive repos --details
RUN zypper --non-interactive refresh -f
RUN zypper --non-interactive install pkg-config openpgm-devel libsodium-devel
RUN zypper --non-interactive install -r 'home_mvyskocil_branches_network_messaging_zeromq_git-draft' zeromq-devel
RUN zypper --non-interactive install vim nano gcc gcc-c++ make automake autoconf libtool asciidoc xmlto git valgrind curl wget
RUN zypper --non-interactive install czmq-devel generator-scripting-language zproto zyre-devel zproject
# malamute-devel - can't install

RUN useradd -g users -m -s /bin/bash zeromq
RUN chown -R zeromq /usr/local
USER zeromq
RUN cd /home/zeromq/; for repo in "czmq" "libzmq" "gsl" "malamute" "zproject" "zproto" "zyre"; do git clone -o upstream "https://github.com/zeromq/${repo}"; done
RUN cd /home/zeromq/malamute; ./autogen.sh && ./configure && make && make install
