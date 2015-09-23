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

### Build binaries with pdebuild

Assumes the base image is in `/var/cache/pbuilder/$DISTRIB-amd64/base.cow` and the current directory is the root of the extracted source tarball:

```
DIST=$DISTRIB pdebuild --use-pdebuild-internal --pbuilder cowbuilder -- --basepath /var/cache/pbuilder/$DISTRIB-amd64/base.cow
```
