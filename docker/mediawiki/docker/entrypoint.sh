#!/bin/bash
set -o errexit
set -o nounset
set -o pipefail

mediawiki_base_dir=/opt/bitnami/mediawiki

# # If existing images are provided then extract them into the images dir if it is empty
# # that is usally mounted as a named volume for backup purposes
# images_dir=/bitnami/mediawiki/images
# init_images_tarball=/docker-entrypoint-init.d/images.tar.gz
# existing_images=$(ls -1 "${images_dir}")
# if [[ -f "${init_images_tarball}" && -z "${existing_images}" ]]; then
#   echo "Initializing existing image set"
#   tar --directory="${images_dir}" --extract --strip-component=1 --gunzip --file="${init_images_tarball}"
# else
#   echo "${images_dir} contains images - skipping extraction from default set"
# fi
# # Link external images to mediawiki installation
# rm -fr "${mediawiki_base_dir}/images"
# ln -s "${images_dir}" "${mediawiki_base_dir}/images"

# Run mediawiki upgrade maintenance script to ensure DB is consistent
# after importing dumped version
php "${mediawiki_base_dir}/maintenance/update.php"

# Run any command passed to container
exec "$@"
