cmake_minimum_required(VERSION 3.8)

project(io2d CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Concurrent DBus Gui OpenGL OpenGLExtensions Test Widgets Xml REQUIRED)

add_library(io2d_qt
	xqt.h
	xqt_headers.h
	xqt_brushes_impl.h
	xqt_command_list_impl.h
	xqt_helpers.h
	xqt_paths_impl.h
	xqt_surfaces_image_impl.h
	xqt_surfaces_impl.h
	xqt_surface_state_props_impl.h
	xqt_text_impl.h
	xio2d_qt_main.h
)

target_include_directories(io2d_qt PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(io2d_qt PUBLIC cxx_std_17)

#find_package(Qt5 COMPONENTS Core Concurrent ConcurrentPrivate CorePrivate DBus DBusPrivate Gui Gui_EGL GuiPrivate Gui_GLESv2 Network NetworkPrivate QGenericEnginePlugin OpenGL OpenGLPrivate OpenGLExtensions OpenGLExtentionsPrivate PrintSupport PrintSupportPrivate Sql SqlPrivate QPSQLDriverPlugin Test TestPrivate Widgets WidgetsPrivate Xml XmlPrivate QTgaPlugin QICNSPlugin QTiffPlugin QWbmpPlugin Svg QSvgPlugin SvgPrivate QSvgIconPlugin REQUIRED)
#find_package(Qt5 COMPONENTS Core Concurrent DBus Gui Network OpenGL OpenGLExtensions PrintSupport Sql Test Widgets Xml Svg REQUIRED)

#find_package(Qt5 COMPONENTS Concurrent REQUIRED)
#find_package(Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt5Concurrent CONFIG REQUIRED)
target_link_libraries(io2d_qt PUBLIC io2d_core Qt5::Core Qt5::WinMain Qt5::Concurrent Qt5::DBus Qt5::Gui Qt5::OpenGL Qt5::OpenGLExtensions Qt5::Test Qt5::Widgets )

target_link_libraries(io2d_qt PRIVATE Qt5::CorePrivate Qt5::ConcurrentPrivate Qt5::DBusPrivate Qt5::GuiPrivate Qt5::OpenGLPrivate Qt5::OpenGLExtensionsPrivate Qt5::TestPrivate Qt5::WidgetsPrivate)
# rcc_object_${outfilename} 

#target_link_libraries(io2d_qt PRIVATE Qt5::Concurrent Qt5::ConcurrentPrivate)

#find_package(Qt5Core CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::Core Qt5::WinMain Qt5::CorePrivate rcc_object_${outfilename})

#find_package(Qt5DBus CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::DBus Qt5::DBusPrivate)

#find_package(Qt5Gui CONFIG REQUIRED)
# Note: 9 target(s) were omitted.
#target_link_libraries(io2d_qt PRIVATE Qt5::Gui Qt5::Gui_EGL Qt5::GuiPrivate Qt5::Gui_GLESv2)

#find_package(Qt5Network CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::Network Qt5::NetworkPrivate Qt5::QGenericEnginePlugin)

#find_package(Qt5OpenGL CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::OpenGL Qt5::OpenGLPrivate)

#find_package(Qt5OpenGLExtensions CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::OpenGLExtensions Qt5::OpenGLExtensionsPrivate)

#find_package(Qt5PrintSupport CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::PrintSupport Qt5::PrintSupportPrivate Qt5::QWindowsPrinterSupportPlugin)

#find_package(Qt5Sql CONFIG REQUIRED)
# Note: 1 target(s) were omitted.
#target_link_libraries(io2d_qt PRIVATE Qt5::Sql Qt5::SqlPrivate Qt5::QODBCDriverPlugin Qt5::QPSQLDriverPlugin)

#find_package(Qt5Test CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::Test Qt5::TestPrivate)

#find_package(Qt5Widgets CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::Widgets Qt5::WidgetsPrivate Qt5::QWindowsVistaStylePlugin)

#find_package(Qt5Xml CONFIG REQUIRED)
#target_link_libraries(io2d_qt PRIVATE Qt5::Xml Qt5::XmlPrivate)

#target_link_libraries(io2d_qt PRIVATE Qt5::QTgaPlugin Qt5::QICNSPlugin Qt5::QTiffPlugin Qt5::QWbmpPlugin)
#target_link_libraries(io2d_qt PRIVATE Qt5::Svg Qt5::QSvgPlugin Qt5::SvgPrivate Qt5::QSvgIconPlugin)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
#set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

install(
	TARGETS io2d_qt EXPORT io2d_targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

file(
	GLOB IO2D_QT_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
	FILES ${IO2D_QT_HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
