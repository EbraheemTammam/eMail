cmake_minimum_required(VERSION 3.30.4)

project(SMTPServer.Application LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/Intermediates/$<CONFIG>/SMTPServer.Application)

# Include Asio
set(ASIO_INCLUDE_DIR "D:\\Programs\\BuildTools\\asio-1.30.2\\include")
include_directories(${ASIO_INCLUDE_DIR})

# Define ASIO_STANDALONE
add_definitions(-DASIO_STANDALONE)

# Get all source files while ignoring the build directory
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Source/*.h")

# Source files and include directories
target_sources(SMTPServer.Core PRIVATE ${SOURCES})

# Define the target
add_executable(SMTPServer.Application ${SOURCES})

target_include_directories(SMTPServer.Application PRIVATE ${ASIO_INCLUDE_DIR} Source ../SMTPServer.Core/Source)

# Link against the SMTPServer.Core library
target_link_libraries(SMTPServer.Application PRIVATE SMTPServer.Core)

# Windows-specific settings
if (WIN32)
    target_compile_definitions(SMTPServer.Application PRIVATE WINDOWS)
endif()

# Configurations
set_target_properties(SMTPServer.Application PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Binaries/$<CONFIG>/SMTPServer.Application
)

# Configuration specific settings
target_compile_definitions(SMTPServer.Application PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)
target_compile_options(SMTPServer.Application PRIVATE
    $<$<CONFIG:Debug>:/MDd>
    $<$<CONFIG:Release>:/MD>
)
target_compile_options(SMTPServer.Application PRIVATE
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2 /Zi>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(SMTPServer.Application PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(SMTPServer.Application PRIVATE -O3)
endif()

# Link against ws2_32.lib and mswsock.lib for Windows sockets
target_link_libraries(SMTPServer.Core PRIVATE ws2_32 mswsock)
