Apache WSGI Server With Chunked Transfer Encoding
=================================================

Uses Apache 2.2 on Centos 6 to mirror RHEL 6

To build the image:

```
docker build --rm -t apache-wsgi .
```

To run the container on localhost port 80 (make sure apache is not already running on the host):

```
docker run -p 80:80 --rm --name=apache2.2 apache-wsgi
```
Swap `--rm` for `-d` to force docker to detach after starting the container
