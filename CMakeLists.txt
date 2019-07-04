cmake_minimum_required(VERSION 3.5)

project(Decoder LANGUAGES CXX)

# Default to a Release build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
    message(STATUS "Defaulting to a Release build")
endif()

# Set hard requirements for C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warn on CMake API deprecations
set(CMAKE_WARN_DEPRECATED ON)

# Set compilation flags
if (MSVC)
	# Silence "deprecation" warnings
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
	add_compile_options(/W3 /MP /Zi /Zo /permissive- /EHsc /std:c++latest /Zc:throwingNew,inline)
else()
	add_compile_options("-Wno-attributes")
endif()

# Disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif()

set(Boost_ADDITIONAL_VERSIONS "1.69" "1.69.0")

# Boost is required for the algebra library
find_package(Boost 1.50.0 REQUIRED)

if(Boost_FOUND)
    message("Boost found, include : ${Boost_INCLUDE_DIRS} lib : ${Boost_LIBRARY_DIRS}")
endif()

# Zlib is required to support .npy format
find_package(ZLIB REQUIRED)

if(ZLIB_FOUND)
    message("Zlib found, include : ${ZLIB_INCLUDE_DIRS} lib : ${ZLIB_LIBRARY}")
endif()

# OpenCL is optional but if found computations are done on the device
#find_package(OpenCL)

#if(OpenCL_FOUND)
#	message("OpenCL found, include : ${OpenCL_INCLUDE_DIRS} lib : ${OpenCL_LIBRARY}")
#endif()

# Include externals
add_subdirectory(externals)

# Include sub-projects.
add_subdirectory(src)
