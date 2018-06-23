#!/usr/bin/env python
"""
An HTTP server tailored for step-debugging through Emscripten-compiled code

Usage:
    debug-emscripten-httpd.py

This will serve the entire contents of the project's directory, along
with all of its subdirectories, to the local machine.  It will also
serve files from some key, system-level directories, in order to
serve C++ header files.

This server will attempt to resolve requests for files in a number of
ways, often modifying requests' path, in order to get step-debugging
working with C++ code (that's been compiled to wasm, or Javascript).
Further details are listed in its code.

Very little has been done to this script to aid with security or
performance.  It has been designed as an aid to developers, when they
debug code on their machine.  Using it in any other scenario may result
a bad time for you, your users, your boss(es), etc.

Initial version by David Ludwig <dludwig@pobox.com>

"""

DefaultPort = 8080
DefaultAltRoots = [
    "/usr/local/Cellar/emscripten/"
]


from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer

import errno
import mimetypes
import os.path
import posixpath
import sys

def rootless_posixpath(path):
    if len(path) > 0 and path[0] == "/":
        return path[1:]
    else:
        return path

class EmscriptenDebugServerHandler(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self._did_start = False
        BaseHTTPRequestHandler.__init__(self, *args, **kwargs)

    def _get_client_state(self):
        key = "%s;%s" % (str(self.client_address[0]), str(self.headers.get("user-agent")))
        if not key in self.server.client_states:
            self.server.client_states[key] = {}
        return self.server.client_states[key]

    def _start_response(self):
        if self._did_start:
            return
        self._did_start = True

    def _end_response(self):
        client_state = self._get_client_state()
        client_state["last_path"] = self.path
        print("")   # this adds some whitespace in between requests' log-entries

    def _send_directory(self, local_path):
        body = ""
        if os.path.isdir(local_path):
            body = "<ul>\n"
            for d in sorted(os.listdir(local_path), key=lambda s: s.lower()):
                body += '\t<li><a href="%s">%s</a></li>\n' % (posixpath.join(self.path, d), d)
            body += "</ul>\n"
        format_args = {
            "title": posixpath.split(self.path)[1],
            "body": body
        }
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write("""
<html>
    <head>
        <title>%(title)s</title>
    </head>
    <body>
        %(body)s
    </body>
</html>
""" % format_args)
        self._end_response()

    def _send_error(self, code, message=None):
        self.send_response(code)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        if message:
            self.wfile.write(str(message))
        self._end_response()
    
    def _guess_content_type(self, path):
        content_type = mimetypes.guess_type(path)
        if content_type and content_type[0]:
            return content_type[0]
        elif path.lower().endswith(".wasm"):
            return "application/wasm"
        else:
            return "application/octet-stream"

    def _send_file_or_error(self, file_path):
        try:
            f = open(file_path, 'rb')
            content = f.read()
            f.close()
            content_type = self._guess_content_type(file_path)
            # print("content_type: %s  (file_path: %s)" % (str(content_type), file_path))
        except IOError as e:
            message = "I/O error({0}): {1}\n".format(e.errno, e.strerror)
            if e.errno == errno.EACCES:
                self._send_error(403, message)
            else:
                self._send_error(500, message)
            return
        except:
            self._send_error(500, "Unknown error: %s\n" % str(sys.exc_info()[0]))
            return

        self.send_response(200)
        self.send_header('Content-type', content_type)
        self.end_headers()
        self.wfile.write(content)
        self._end_response()
    
    def _try_send_path(self, path):
        if os.path.isfile(path):
            self._send_file_or_error(path)
            return True
        elif os.path.isdir(path):
            self._send_directory(path)
            return True
        else:
            return False

    def _handle_request(self):
        self._start_response()

        # Try to resolve files normally, using the server's 'local_root' var (which defaults to the
        # same directory that the server script is in) as a root directory.
        normpath = posixpath.normpath(self.path)
        normpath_rootless = rootless_posixpath(normpath)
        try_path = os.path.join(self.server.local_root, normpath_rootless)
        if self._try_send_path(try_path):
            return

        # Try to resolve files specified with the full path name.  This can happen to
        # file-paths listed in .map files, especially.
        try_path = normpath
        common = os.path.commonprefix([self.server.local_root, normpath])
        if common.startswith(self.server.local_root):
            if self._try_send_path(try_path):
                return
        
        # Try to resolve requests for .map files, which are often looked for in directories other
        # than the one they are in.  (This directory is typically encoded by Emscripten, via
        # external tools that it invokes, when building code.)
        if normpath.lower().endswith(".map"):
            client_state = self._get_client_state()
            if "last_path" in client_state:
                last_path_rootless = rootless_posixpath(client_state["last_path"])
                possible_path_rootless = posixpath.join(
                    self.server.local_root, posixpath.dirname(last_path_rootless), normpath_rootless)
                if self._try_send_path(possible_path_rootless):
                    return
        
        if self.server.alt_roots:
            for alt_root in self.server.alt_roots:
                try_path = normpath
                common = os.path.commonprefix([alt_root, normpath])
                if common.startswith(alt_root):
                    if self._try_send_path(normpath):
                        return

        # There's only so much we can do.  :-(  (But perhaps there is more?)
        self._send_error(404)

    def do_GET(self):
        self._handle_request()



def run(port=8080):
    server_address = ('localhost', DefaultPort)
    httpd = HTTPServer(server_address, EmscriptenDebugServerHandler)
    httpd.local_root = os.path.split(os.path.abspath(__file__))[0]
    httpd.alt_roots = DefaultAltRoots
    httpd.client_states = {}
    print('Starting http server at http://%s:%d' % server_address)
    print('Directories-to-serve: ')
    print('  %s' % httpd.local_root)
    for alt_root in httpd.alt_roots:
        print('  %s' % alt_root)
    print('')
    httpd.serve_forever()


if __name__ == "__main__":
    from sys import argv
    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
