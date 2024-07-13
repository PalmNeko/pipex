FROM ubuntu:jammy

# 42 setups v
# see -> https://pastebin.com/4HnnSUpe

RUN apt update && apt upgrade && apt-get install -y \
	zsh \
	vim \
	emacs \
	curl \
	gcc \
	clang \
	g++ \
	lldb \
	valgrind \
	build-essential \
	cmake

ARG AS_USERNAME=pipex
ARG AS_UID=9193
ARG AS_GROUPNAME=user42
ARG AS_GUID=4242
RUN groupadd -g $AS_GUID $AS_GROUPNAME && \
	useradd -G $AS_GROUPNAME -u $AS_UID $AS_USERNAME
USER $AS_USERNAME:$AS_GROUPNAME

CMD [ "cat" ]
