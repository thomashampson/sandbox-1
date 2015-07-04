# Basic Qt app
FROM ubuntu:14.04

MAINTAINER Martyn Gigg <martyn.gigg@gmail.com>

RUN apt-get -y update && apt-get install -y libqt4-dev

RUN export uid=1000 gid=1000 && \
    mkdir -p /home/developer && \
    echo "developer:x:${uid}:${gid}:Developer,,,:/home/developer:/bin/bash" >> /etc/passwd && \
    echo "developer:x:${uid}:" >> /etc/group && \
    echo "developer ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/developer && \
    chmod 0440 /etc/sudoers.d/developer && \
    chown ${uid}:${gid} -R /home/developer && \
    usermod -a -G video developer

USER developer
ENV HOME /home/developer
# Avoids error with sharing X11 connections with host
ENV QT_X11_NO_MITSHM 1

COPY textures /usr/bin/textures

# Start the app
#ENTRYPOINT ["/usr/bin/textures"]
