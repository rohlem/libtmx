cmake_minimum_required(VERSION 2.8.9)
# version 2.8.9 is necessary for Qt5
# see http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html#using-qt-5-with-cmake-older-than-2-8-9

project(LIBTMX CXX)

option(BUILD_SHARED_LIBS "Build the library as shared; note that no symbols are exported explicitly (-> no import library generated under MSVC)" OFF)

option(TMX_RENDER "Build tmx_render" OFF)
option(TMX_DOC "Build the documentation" OFF)

include(CPackConfig.cmake)

# originally: find_package(PkgConfig REQUIRED) - unnecessary, CMake uses pkg-config under the hood when it sees fit to do so anyway

option(LINK_TINYXML2_STATICALLY "Link to the static version of tinyxml2 instead of the shared version (previously defaulted to OFF)" ON)
if(LINK_TINYXML2_STATICALLY)
	set( LIBTMX_TINYXML2_TARGET tinyxml2_static )
else(LINK_TINYXML2_STATICALLY)
	set( LIBTMX_TINYXML2_TARGET tinyxml2 )
endif(LINK_TINYXML2_STATICALLY)
find_package(TINYXML2 REQUIRED ${LIBTMX_TINYXML2_TARGET}) # originally: pkg_check_modules(TINYXML2 REQUIRED tinyxml2)

find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

# originally: add_definitions(-Wall -g -O2) - not useful, and can lead to errors ; this particular use case is available as the CMake generated build target "RelWithDebInfo" (Release with Debug information)

# C++11 specification moved into lib/CMakeLists.txt

include_directories(${LIBTMX_SOURCE_DIR}/include)

add_subdirectory(lib)

if(TMX_RENDER)
  find_package(Qt5Core)
  find_package(Qt5Gui)

  if(Qt5Core_FOUND)
    add_subdirectory(bin)
  endif(Qt5Core_FOUND)
endif(TMX_RENDER)

if(TMX_DOC)
  find_package(Doxygen)

  if(DOXYGEN_FOUND)
    configure_file("${LIBTMX_SOURCE_DIR}/Doxyfile.cmake" "${LIBTMX_BINARY_DIR}/Doxyfile" @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${LIBTMX_BINARY_DIR}/Doxyfile")
  endif(DOXYGEN_FOUND)
endif(TMX_DOC)

configure_file("${LIBTMX_SOURCE_DIR}/libtmx0.pc.in" "${LIBTMX_BINARY_DIR}/libtmx0.pc" @ONLY)
install(
  FILES "${LIBTMX_BINARY_DIR}/libtmx0.pc"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig"
)

install(
  DIRECTORY "${LIBTMX_SOURCE_DIR}/include/tmx"
  DESTINATION include
)
