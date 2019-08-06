
#!/bin/bash

set -x

PUID=${PUID:-1000}
PGID=${PGID:-1000}

# Set target user's IDs to match that of the "external"/"host" user
groupmod --non-unique --gid ${PGID} ${TARGET_USERNAME}
usermod --non-unique --uid ${PUID} ${TARGET_USERNAME}
