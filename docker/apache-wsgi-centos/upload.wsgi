#!/usr/bin/env python
import cgi
import os

def application(environ, start_response):
   fields = None
   if 'POST' == environ['REQUEST_METHOD'] :
      fields = cgi.FieldStorage(fp=environ['wsgi.input'],
                                environ=environ, keep_blank_values=1)
      fileitem = fields['file']
      fn = os.path.basename(fileitem.filename)
      open("/var/www/uploads/" + fn, "w").write(fileitem.file.read())


   response_body = "{message: success}"
   status = '200 OK'
   response_headers = [('Content-Type', 'application/json'),
                  ('Content-Length', str(len(response_body)))]
   start_response(status, response_headers)

   return [response_body]
