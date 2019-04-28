# IO2D Building How-To

This article describes the process of configuring Reference Implementation of IO2D(also known as [P0267]).

## Compatibility

This IO2D implementation supports the following platforms out of the box:
* Cairo/Win32: Windows
* Cairo/Xlib: Linux, macOS
* CoreGraphics/Mac: macOS
* CoreGraphics/iOS: iOS

## General Notes

### Build process
IO2D employs CMake as a build system. The following variables control the configuration process:
* IO2D_DEFAULT
Controls a selection of default backend which is used when non-template symbols from std::experimental::io2d, like "brush" or "surface", are referenced.
There're 5 backends in this RefImpl:
  * CAIRO_WIN32
  * CAIRO_XLIB
  * CAIRO_SDL2
  * COREGRAPHICS_MAC
  * COREGRAPHICS_IOS

  If no default backend was defined, the build script will try to automatically set an appropriate Cairo backend based on the host environment.
  
* IO2D_ENABLED
Specifies a list of enabled backends, which means a set of backends included in the build process.
By default, a value of IO2D_DEFAULT is used, so this variable can be left undefined.
If, however, you want to have a multi-backend configuration of IO2D, this variable has to contain a valid list, for instance: "COREGRAPHICS_MAC;CAIRO_XLIB". 
* IO2D_WITHOUT_SAMPLES
This variable can be defined to exclude sample code from the build process.
Please note that some samples might be exculed from the build process depending on your environment.
More specifically, the SVG example requires Boost.
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
export LDFLAGS="-LNEWPATH/lib -Wl,-rpath,NEWPATH/lib"
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
Both Win32 and x64 builds are supported and being tested.

Example of CMake execution (assuming that vcpkg was installed in c:/tools):
```
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Visual Studio 15 2017 Win64" --config Debug "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_TOOLCHAIN_FILE=c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" ../.
io2d.sln
```

### Cairo/Xlib on Linux
CMake script expects cairo and graphicsmagick to be installed. libpng is required in order to run tests.
These installation steps assume APT package manager on Ubuntu Linux.
Installation steps:
1. Refresh apt: `sudo apt update`
2. Install GCC: `sudo apt install build-essential`
3. Install CMake: `sudo apt install cmake`
4. Install Cairo: `sudo apt install libcairo2-dev`
5. Install graphicsmagick: `sudo apt install libgraphicsmagick1-dev`
6. Install libpng: `sudo apt install libpng-dev`

Example of CMake execution:
```
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
cmake --build .
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
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Xcode" --config Debug "-DCMAKE_BUILD_TYPE=Debug" ../.
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
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Xcode" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=COREGRAPHICS_MAC ../.
open io2d.xcodeproj
```

### CoreGraphics/iOS on iOS
Since CMake doesn't support iOS out of the box, some additional configuration is required. To simplify the configuration process, an external toolchain can be specified. This one was used during the delopment: https://github.com/leetal/ios-cmake, but nothing stops from getting another one or configuring the build environment manually. The only requirement for the iOS toolchain is to set the IOS_PLATFORM variable during configuration. In the sample script below, you need to change PathToModernLibCXX to a valid path to libc++ installation (see above). To deploy on a physical device, the IOS_PLATFORM variable must be changed from SIMULATOR64 to OS.

Installation steps:
1. Setup a modern libc++ version as described above.
2. Install Brew: /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
3. Install cmake: brew install cmake

Example of CMake execution:
```
git clone https://github.com/leetal/ios-cmake
ex -sc '1i|set( CXX_FLAGS "-nostdinc++ -IPathToModernLibCXX/include/c++/v1" )' -cx ios-cmake/ios.toolchain.cmake
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -G "Xcode" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=COREGRAPHICS_IOS -DIO2D_WITHOUT_TESTS=1 -DIOS_PLATFORM=SIMULATOR64 -DCMAKE_TOOLCHAIN_FILE=../../ios-cmake/ios.toolchain.cmake ../.
open io2d.xcodeproj
```
