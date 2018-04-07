rd /s /q Build
mkdire Build
cd Build
cmake -G "Visual Studio 15 2017 Win64" "-DBOOST_INCLUDEDIR=C:\Users\Migun\Desktop\vcpkg\installed\x64-windows\include" "-DCMAKE_TOOLCHAIN_FILE=C:/Users/Migun/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows-static" ../.
