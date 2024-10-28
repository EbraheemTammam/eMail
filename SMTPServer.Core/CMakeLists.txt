cmake_minimum_required(VERSION 3.30.4)

project(SMTPServer.Core LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/Intermediates/$<CONFIG>/SMTPServer.Core)

# Define the target
add_library(SMTPServer.Core STATIC)

# Get all source files while ignoring the build directory
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")

# Source files and include directories
target_sources(SMTPServer.Core PRIVATE ${SOURCES})
target_include_directories(SMTPServer.Core PRIVATE Source)

# Add precompiled header
target_precompile_headers(SMTPServer.Core PRIVATE Source/PCH.h)

# Windows-specific settings
if (WIN32)
    target_compile_definitions(SMTPServer.Core PRIVATE SYSTEM_VERSION_LATEST)
endif()

# Configurations
set_target_properties(SMTPServer.Core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Core
)

# Configuration specific settings
target_compile_definitions(SMTPServer.Core PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)
target_compile_options(SMTPServer.Core PRIVATE
    $<$<CONFIG:Debug>:/MDd>
    $<$<CONFIG:Release>:/MD>
)
target_compile_options(SMTPServer.Core PRIVATE
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2 /Zi>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(SMTPServer.Core PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(SMTPServer.Core PRIVATE -O3)
endif()
