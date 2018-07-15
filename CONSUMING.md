# IO2D Consuming How-To

First, you need to build and install this library somewhere where it will be found using `find_package`. Then, add the following line to import the targets into your CMake build script:

	find_package(io2d REQUIRED)

Then you can choose which target to link your app to. The most reasonable choice is to link to `io2d::io2d`:

	target_link_libraries(ExampleApp PRIVATE io2d::io2d)

This will link to backends that were built. This will make your app cross-platform out of the box. If you want to link to specific backend, you can specify it, for example:

	target_link_libraries(ExampleApp PRIVATE io2d::io2d_cairo_xlib)

This will link to Cairo/Xlib backend only. Available backends are:

* `io2d::io2d_cairo_win32`
* `io2d::io2d_cairo_xlib`
* `io2d::io2d_coregraphics_mac`
* `io2d::io2d_coregraphics_ios`
