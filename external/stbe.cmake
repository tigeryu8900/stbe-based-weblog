include (ExternalProject)

set(stbe_SOURCE_DIR ${CMAKE_BINARY_DIR}/stbe/source)
set(stbe_BUILD_DIR ${CMAKE_BINARY_DIR}/stbe/build)
set(stbe_INCLUDE_DIR ${stbe_SOURCE_DIR}/include)
set(stbe_URL https://github.com/tigeryu8900/static-trie-based-encoding.git)
set(stbe_TAG master)
set(stbe_LIBRARIES ${stbe_BUILD_DIR}/obj/so/libstbe.so)
get_filename_component(stbe_STATIC_LIBRARIES ${stbe_BUILD_DIR}/libstbe.a ABSOLUTE)

ExternalProject_Add(stbe
    PREFIX stbe
    GIT_REPOSITORY  ${stbe_URL}
    GIT_TAG         ${stbe_TAG}
    DOWNLOAD_DIR    "${DOWNLOAD_LOCATION}"
    SOURCE_DIR      "${stbe_SOURCE_DIR}"
    BINARY_DIR      "${stbe_BUILD_DIR}"
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
)

ADD_LIBRARY(stbe_lib STATIC IMPORTED
    DEPENDS stbe)
SET_TARGET_PROPERTIES(stbe_lib PROPERTIES
    IMPORTED_LOCATION ${stbe_STATIC_LIBRARIES})

message( ">>>>>>>>tigerdebug stbe include ${stbe_INCLUDE_DIR}" )
message( ">>>>>>>>tigerdebug stbe build ${stbe_BUILD_DIR}" )
message( ">>>>>>>>tigerdebug stbe lib ${stbe_STATIC_LIBRARIES}" )
message( ">>>>>>>>tigerdebug stbe DOWNLOAD_LOCATION ${DOWNLOAD_LOCATION}" )
