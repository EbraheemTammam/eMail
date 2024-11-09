cmake_minimum_required(VERSION 3.30.4)

project(eMail.Core LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/Intermediates/$<CONFIG>/eMail.Core)

# Include Asio
set(ASIO_INCLUDE_DIR "D:\\Programs\\BuildTools\\asio-1.30.2\\include")
include_directories(${ASIO_INCLUDE_DIR})

# Define ASIO_STANDALONE
add_definitions(-DASIO_STANDALONE)

# Define the target
add_library(eMail.Core STATIC)

# Get all source files while ignoring the build directory
file(GLOB_RECURSE SOURCES "Headers/*.h" "Source/*.cpp")

# Source files and include directories
target_sources(eMail.Core PRIVATE ${SOURCES})
target_include_directories(eMail.Core PRIVATE ${ASIO_INCLUDE_DIR} Headers Source)

# Add precompiled header
target_precompile_headers(eMail.Core PRIVATE Headers/PCH.h)

# Windows-specific settings
if (WIN32)
    target_compile_definitions(eMail.Core PRIVATE SYSTEM_VERSION_LATEST)
endif()

# Configurations
set_target_properties(eMail.Core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/eMail.Core
)

# Configuration specific settings
target_compile_definitions(eMail.Core PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)
target_compile_options(eMail.Core PRIVATE
    $<$<CONFIG:Debug>:/MDd>
    $<$<CONFIG:Release>:/MD>
)
target_compile_options(eMail.Core PRIVATE
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2 /Zi>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(eMail.Core PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(eMail.Core PRIVATE -O3)
endif()

# Link against ws2_32.lib and mswsock.lib for Windows sockets
target_link_libraries(eMail.Core PRIVATE ws2_32 mswsock)
