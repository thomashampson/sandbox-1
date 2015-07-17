# CentOS 6.6 with apache and mod_wsgi
FROM centos:centos6.6
USER root

MAINTAINER Martyn Gigg <martyn.gigg@gmail.com>

ENV http_proxy http://wwwcache.rl.ac.uk:8080
ENV https_proxy http://wwwcache.rl.ac.uk:8080

# Install apache and mod_wsgi
RUN yum -y update  && yum -y install mod_wsgi

# Create virtual host
COPY sandbox.conf /etc/httpd/vhosts/sandbox.conf
RUN echo "Include /etc/httpd/vhosts/sandbox.conf" >> /etc/httpd/conf/httpd.conf
# Copy wsgi scripts
COPY upload.wsgi /var/www/wsgi-scripts/upload.wsgi

RUN mkdir /var/www/uploads && chown apache:apache /var/www/uploads

EXPOSE 80

# Simple startup script to avoid some issues observed with container restart
ADD run-httpd.sh /run-httpd.sh
RUN chmod -v +x /run-httpd.sh

CMD ["/run-httpd.sh"]
