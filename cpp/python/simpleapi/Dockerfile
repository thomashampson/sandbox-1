FROM ubuntu:bionic

# Add target user
RUN useradd \
  --uid 911 \
  --user-group \
  --shell /bin/bash \
  --create-home abc

# Install boost python and compilers
RUN apt-get update && \
    # Install prerequisite tools
    apt-get install -y \
      g++ \
      libboost-python-dev && \
    # Clean up
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Allow mounting source
VOLUME ["/src"]

ADD entrypoint.sh /entrypoint.sh
ADD entrypoint.d/ /etc/entrypoint.d/
ENTRYPOINT ["/entrypoint.sh"]