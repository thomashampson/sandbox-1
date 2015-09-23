Cheatsheet for cowbuilder
=========================

### Create

See create-cowbuiler-env.sh for creating an environment

### Update

Assumes the base image is in `/var/cache/pbuilder/$DISTRIB-amd64/base.cow`

```
HOME=$HOME DIST=$DISTRIB cowbuilder --update -- --basepath /var/cache/pbuilder/$DISTRIB-amd64/base.cow
```

### Login and save afterwards

Assumes the base image is in `/var/cache/pbuilder/$DISTRIB-amd64/base.cow`

```
HOME=$HOME DIST=$DISTRIB cowbuilder --login --basepath /var/cache/pbuilder/$DISTRIB-amd64/base.cow --save-after-login
```

### Build binaries 

Not techincally required for upload to PPA but it's good to check the build as it takes a while on Launchpad.

```
cd extracted-source
dpkg-buildpackage -uc -us -nc -d -S
cd ../
sudo HOME=$HOME DIST="$DISTRIB" ARCH=amd64 \
cowbuilder --buildresult $PWD \
--build changes.dsc \
--basepath "/var/cache/pbuilder/$DISTRIB-amd64/base.cow" --debbuildopts "-sa" \
--configfile="${HOME}/.pbuilderrc"
```

### Sign changes file

Default result path for cowbuilder is `/var/cache/pbuilder/$DISTRIB-amd64/result`
```
debsign /var/cache/pbuilder/$DISTRIB-amd64/result/package-name-version.changes
```

You will be asked twice for your GPG passphrase for your installed key.

### Build binaries with pdebuild

Assumes the base image is in `/var/cache/pbuilder/$DISTRIB-amd64/base.cow` and the current directory is the root of the extracted source tarball:

```
DIST=$DISTRIB pdebuild --use-pdebuild-internal --pbuilder cowbuilder -- --basepath /var/cache/pbuilder/$DISTRIB-amd64/base.cow
```

