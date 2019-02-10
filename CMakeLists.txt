cmake_minimum_required(VERSION 3.5)

project(stbe-weblog C CXX)

# version number
SET ( VERSION_MAJOR 0 )
SET ( VERSION_MINOR 1 )

# CMake policies
cmake_policy(SET CMP0022 NEW)

SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

# External dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external)

# Location where external projects will be downloaded
set (DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
     CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

# External dependencies
include(stbe)
include(re2)
include(gflags)
#find_package(gflags REQUIRED)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${DOWNLOAD_LOCATION}/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${DOWNLOAD_LOCATION} )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${DOWNLOAD_LOCATION} )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()


# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

#add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/gflags-src
#                 ${CMAKE_CURRENT_BINARY_DIR}/gflags-build
#                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
#  include_directories("${CMAKE_CURRENT_BINARY_DIR}/re2-src")
#  include_directories("${CMAKE_CURRENT_BINARY_DIR}/stbe-src/include")
endif()

add_library(stbeweblog
        src/weblog-encoder.cpp
        src/weblog-decoder.cpp
        src/weblog-reader.cpp)

add_dependencies(stbeweblog re2_lib re2 stbe gtest gflags gflags_lib)

# Now simply link against gtest or gtest_main as needed. Eg

#set(gflags_DIR "${PROJECT_SOURCE_DIR}/external")

# Setup testing
enable_testing()
#find_package(GTest REQUIRED)
#find_package(gflags REQUIRED)

include_directories(include src
                    ${gtest_SOURCE_DIR}/include 
                    ${re2_INCLUDE_DIR}
                    ${gflags_INCLUDE_DIR}
                    ${stbe_INCLUDE_DIR})


# Add main cpp file
add_executable(stbewl
    src/main.cpp
)
#add_test(NAME memblock_test COMMAND memblock_test)
#
#add_executable(stbe_test
#  tests/stbe_test.cpp
#)

#message( "tigerdebug re2 lib ${re2_STATIC_LIBRARIES}" )
target_link_libraries(stbewl stbeweblog stbe_lib gtest gtest_main re2_lib gflags_lib)
#target_link_libraries(stbe_test libstbe gtest gtest_main)
#add_test(NAME stbe_test COMMAND stbe_test)

