Licenses
==============

There are several distinct and unique projects in this repository, each with its
own licensing terms and conditions. If you wish to use one of these libraries,
you must comply with its licensing terms. The maintainer of this repository makes
no claims to authorship or ownership of any files in the directories `/cairo`,
`/pixman`, `/libpng16`, or `/zlib-1.2.8`, except as may be documented in the
appropriate location(s) within those directories. Mention of a directory shall
be deemed to include all subdirectories and their subdirectories, etc., within
the mentioned directory. Mention of files in a directory shall be deemed to
include all files located in that directory and in its subdirectories and their
subdirectories, etc.

cairo
--------------
The contents of the `/cairo` directory are subject to the licensing terms described
in the `/cairo/COPYING` file. For more information about the cairo graphics
library, please see [cairographics.org](http://cairographics.org/).

pixman
--------------
The contents of the `/pixman` directory are subject to the licensing terms described
in the `/pixman/COPYING` file. For more information about the pixman library,
please see [pixman.org](http://www.pixman.org/) or [cgit.freedesktop.org/pixman/](http://cgit.freedesktop.org/pixman/).

libpng
--------------
The contents of the `/libpng16` directory are subject to the licensing terms
described in the `/libpng16/LICENSE` file. For more information about libpng,
please see [libpng.org](http://www.libpng.org/pub/png/libpng.html).

zlib
--------------
The contents of the `/zlib-1.2.8` directory are subject to the licensing terms
described in the `/zlib-1.2.8/zlib.h` file. For more information about zlib,
please see [zlib.net](http://zlib.net/).

win32
--------------

With the exception of the files contained in the directories
`/N3888_RefImpl/src/win32/DLLs`, `/N3888_RefImpl/src/win32/include`, and 
`/N3888_RefImpl/src/win32/libs`, the following license applies to the files contained
in the `/N3888_RefImpl` directory.


`The MIT License (MIT)

Copyright (c) 2014 Michael B. McLaughlin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.`


The files in `/N3888_RefImpl/src/win32/include` are header files used to interface
with the cairo graphics library. Their license is described above under the **cairo**
section.

The files in `/N3888_RefImpl/src/win32/libs` are .lib files used to dynamically
link with:

  * The cairo graphics library in accordance with the terms of the Mozilla
    Public License version 1.1, a copy of which can be found at
    `/cairo/COPYING-MPL-1.1`.
  * The zlib general purpose compression library in accordance with the terms
    of its license, which can be found at `/zlib-1.2.8/zlib.h`.

The files in `/N3888_RefImpl/src/win32/DLLs` are executable code versions of
cairo and zlib in the form of DLL files. These files were built in accordance
with the instructions provided at `/N3888_RefImpl/src/win32/DLL build instructions.txt`.
Their licensing is as described above for the .lib files.
