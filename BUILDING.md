# IO2D Building How-To

This article describes the process of configuring Reference Implementation of IO2D(also known as [P0267]).

## Compatibility

This IO2D implementation supports the following platforms out of the box:
* Cairo/Win32: Windows
* Cairo/Xlib: Linux, macOS
* CoreGraphics/Mac: macOS

## General Notes

### Build process
IO2D employs CMake as a build system. The following variables control the configuration process:
* IO2D_DEFAULT  
Controls a selection of default backend which is used when non-template symbols from std::experimental::io2d, like "brush" or "surface", are referenced.
There're 3 backends in this RefImpl:
  * CAIRO_WIN32
  * CAIRO_XLIB
  * COREGRAPHICS_MAC

  The build script expects this variable to have a valid value, otherwise the script will abort.  
* IO2D_ENABLED  
Specifies a list of enabled backends, which means a set of backends included in the build process.
By default, a value of IO2D_DEFAULT is used, so this variable can be left undefined.
If, however, you want to have a multi-backend configuration of IO2D, this variable has to contain a valid list, for instance: "COREGRAPHICS_MAC;CAIRO_XLIB". 
* IO2D_WITHOUT_SAMPLES  
This variable can be defined to exclude sample code from the build process.
Please note that Boost is required to build the sample code.
Pass any value, like "1" to skip this part. 
* IO2D_WITHOUT_TESTS  
This variable controls whether test suites will be included in the build process.
Pass any value, like "1" to skip this part.

### Xcode and libc++
Xcode currently comes with an old version of libc++ which lacks many of C++17 features required by IO2D.
The easiest solution is to download a fresh build of libc++ from [here](http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-x86_64-apple-darwin.tar.xz).
Export appropriate CXX and LD flags to make clang use this version of the standard library (replace NEWPATH with a path of extracted archive contents):
```
export CXXFLAGS="-nostdinc++ -isystemNEWPATH/include/c++/v1"
export LDFLAGS="-LNEWPATH/clang/lib -Wl,-rpath,NEWPATH/lib"
```
## Building Steps

### Cairo/Win32 on Windows
CMake script expects vcpkg to be installed and integrated in Visual Studio.
Installation steps:
1. Clone the github repository at https://github.com/Microsoft/vcpkg.
2. Follow the instructions in the "Quick Start" section of https://github.com/Microsoft/vcpkg/blob/master/README.md to install and integrate vcpkg.
3. Open a powershell window and navigate to the vcpkg repository.
4. Install cairo for win32 with the command ".\vcpkg.exe install cairo"
5. Install cairo for x64 with the command ".\vcpkg.exe install cairo --triplet x64-windows"
6. Install graphicsmagick for win32 with the command ".\vcpkg.exe install graphicsmagick"
7. Install graphicsmagick for x64 with the command ".\vcpkg.exe install graphicsmagick --triplet x64-windows"
8. Inspect which packages have been installed with the command ".\vcpkg.exe list"   
Please note that only x64 build is being tested at the moment.

Example of CMake execution (assuming that vcpkg was installed in c:/tools):
```
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
git clone --recurse-submodules https://github.com/ISOCPP-2D/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Visual Studio 15 2017 Win64" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=CAIRO_WIN32 -DIO2D_WITHOUT_SAMPLES=1 "-DCMAKE_TOOLCHAIN_FILE=c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" ../.
io2d.sln
```

### Cairo/Xlib on Linux
CMake script expects cairo and graphicsmagick to be installed. libpng is required in order to run tests.
These installation steps assume APT package manager on Ubuntu Linux.
Installation steps:
1. Refresh apt: sudo apt-get update
2. Install GCC: sudo apt-get install g++-7 build-essential
3. Install Cairo: sudo apt-get install libcairo2-dev
4. Install graphicsmagick: sudo apt-get install libgraphicsmagick1-dev
5. Install libpng: sudo apt-get install libpng-dev

Example of CMake execution:
```
export CXX=g++-7
git clone --recurse-submodules https://github.com/ISOCPP-2D/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Unix Makefiles" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=CAIRO_XLIB -DIO2D_WITHOUT_SAMPLES=1 ../.
make
```

### Cairo/Xlib on macOS
CMake script expects cairo and graphicsmagick to be installed. libpng is required in order to run tests.
Since cairo in brew doesn't support X11, MacPorts can be used instead.
Installation steps:
1. Setup a modern libc++ version as described above.
2. Install Brew: /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
3. Install libpng: brew install libpng
4. Install graphicsmagick: brew install graphicsmagick
5. Install cmake: brew install cmake
6. Install MacPorts: https://www.macports.org/install.php.
7. Install Cairo: sudo /opt/local/bin/port -N -k install cairo +x11

```
export CXXFLAGS="$CXXFLAGS -isystem/opt/X11/include -isystem/opt/local/include -isystem/usr/local/include"
export LDFLAGS="$LDFLAGS -L/opt/X11/lib -L/opt/local/lib -L/usr/local/lib"
git clone --recurse-submodules https://github.com/ISOCPP-2D/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Xcode" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=CAIRO_XLIB -DIO2D_WITHOUT_SAMPLES=1 ../.
open io2d.xcodeproj
```

### CoreGraphics/Mac on macOS
CMake script expects libpng to be installed if tests are required.
Installation steps:
1. Setup a modern libc++ version as described above.
2. Install Brew: /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
3. Install libpng: brew install libpng
4. Install cmake: brew install cmake

Example of CMake execution:
```
git clone --recurse-submodules https://github.com/ISOCPP-2D/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Xcode" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=COREGRAPHICS_MAC -DIO2D_WITHOUT_SAMPLES=1 ../.
open io2d.xcodeproj
```
