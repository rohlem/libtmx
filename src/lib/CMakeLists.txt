include_directories(${TINYXML2_INCLUDE_DIRS})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DZLIB_CONST)

set(LIBTMX_SRC
  Component.cc
  Layers.cc
  LayerVisitor.cc
  Map.cc
  Object.cc
  Parser.cc
  TileSet.cc
)

add_library(tmx0
  ${LIBTMX_SRC}
)
# originally: if(WIN32)
# originally:  add_definitions(-std=c++0x)
# originally: else(WIN32)
# originally:  add_definitions(-std=c++11)
# originally: endif(WIN32)
# new, better alternative (see https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#requiring-language-standards , also discussion around https://stackoverflow.com/a/46809634 )
target_compile_features(tmx0 PUBLIC cxx_std_11)

target_link_libraries(tmx0 ${LIBTMX_TINYXML2_TARGET} ${LIBTMX_ZLIB_TARGET} ${Boost_LIBRARIES})

set_target_properties(tmx0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
)

install(
  TARGETS tmx0
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
