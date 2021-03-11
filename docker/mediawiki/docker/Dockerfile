# Build on bitnami image and add extensions/skin
FROM bitnami/mediawiki:1.35.1-debian-10-r69

# Add LocalSettings
COPY ./LocalSettings.php /opt/bitnami/mediawiki/LocalSettings.php

# Add custom skins & extensions
COPY ./skins/ /opt/bitnami/mediawiki/skins/

# Add extensions
COPY ./extensions/ /opt/bitnami/mediawiki/extensions/

# Add entry point
COPY ./entrypoint.sh /opt/mantidwiki/scripts/entrypoint.sh
ENTRYPOINT [ "/opt/mantidwiki/scripts/entrypoint.sh" ]
CMD [ "/opt/bitnami/scripts/apache/run.sh" ]