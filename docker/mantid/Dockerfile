# Test bundle of Mantid
FROM ubuntu:14.04

MAINTAINER Martyn Gigg <martyn.gigg@gmail.com>

# Setup a user home directory, require for both X and mantid
RUN export uid=1000 gid=1000 && \
    mkdir -p /home/mantid && \
    echo "mantid:x:${uid}:${gid}:Mantid,,,:/home/mantid:/bin/bash" >> /etc/passwd && \
    echo "mantid:x:${uid}:" >> /etc/group && \
    echo "mantid ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/mantid && \
    chmod 0440 /etc/sudoers.d/mantid && \
    chown ${uid}:${gid} -R /home/mantid && \
    usermod -a -G video mantid

USER mantid

# Install Mantid
RUN sudo apt-get -y update && \
    sudo apt-get -y install software-properties-common gdebi-core wget && \
    wget -q https://github.com/mantidproject/mantid/releases/download/v3.4.0/mantid_3.4.0-1_amd64.deb -O /tmp/mantid_3.4.0-1_amd64.deb && \
     sudo apt-add-repository ppa:mantid/mantid && \
     sudo apt-get update && \
     sudo gdebi -n /tmp/mantid_3.4.0-1_amd64.deb

ENV HOME /home/mantid
# Avoids error when sharing X11 connections with host
ENV QT_X11_NO_MITSHM 1

#ENTRYPOINT ["/opt/Mantid/bin/MantidPlot"]
