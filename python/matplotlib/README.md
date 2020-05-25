# Matplotlib Sandbox

A collection of scripts created while playing with the matplotlib API.

## Docker

A docker image is provided to avoid requiring matplotlib/Qt on the host. Build the image from this directory:

```shell
> docker build . -t ubuntubionic-matplotlib
```

Use [x11docker](https://github.com/mviereck/x11docker/) to run an example:

```shell
x11docker --hostdisplay -- "-v $PWD:/src" ubuntubionic-matplotlib python3 /src/nonorthognal-axes/nonorthogonal_axes.py  
```

