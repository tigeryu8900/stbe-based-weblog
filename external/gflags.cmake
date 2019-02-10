include (ExternalProject)

set(gflags_SOURCE_DIR ${CMAKE_BINARY_DIR}/gflags/source)
set(gflags_BUILD_DIR ${CMAKE_BINARY_DIR}/gflags/build)
set(gflags_INCLUDE_DIR ${gflags_SOURCE_DIR}/include)
set(gflags_URL https://github.com/gflags/gflags)
set(gflags_TAG master)
set(gflags_LIBRARIES ${gflags_BUILD_DIR}/obj/so/libgflags.so)
get_filename_component(gflags_STATIC_LIBRARIES ${gflags_BUILD_DIR}/lib/libgflags.a ABSOLUTE)

ExternalProject_Add(gflags
    PREFIX gflags
    GIT_REPOSITORY  ${gflags_URL}
    GIT_TAG         ${gflags_TAG}
    DOWNLOAD_DIR    "${DOWNLOAD_LOCATION}"
    SOURCE_DIR      "${gflags_SOURCE_DIR}"
    BINARY_DIR      "${gflags_BUILD_DIR}"
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
)

ADD_LIBRARY(gflags_lib STATIC IMPORTED
    DEPENDS gflags)
SET_TARGET_PROPERTIES(gflags_lib PROPERTIES
    IMPORTED_LOCATION ${gflags_STATIC_LIBRARIES})

message( ">>>>>>>>tigerdebug gflags include ${gflags_INCLUDE_DIR}" )
message( ">>>>>>>>tigerdebug gflags build ${gflags_BUILD_DIR}" )
message( ">>>>>>>>tigerdebug gflags lib ${gflags_STATIC_LIBRARIES}" )
message( ">>>>>>>>tigerdebug gflags DOWNLOAD_LOCATION ${DOWNLOAD_LOCATION}" )
