
#!/bin/bash

set -x

# Take ownership of working directories
chown ${TARGET_USERNAME}:${TARGET_USERNAME} /src
