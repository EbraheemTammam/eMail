cmake_minimum_required(VERSION 3.30.4)

project(SMTPServer)

# Set the architecture to x64
set(CMAKE_CXX_ARCHITECTURE_ID x64)

# Set configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set the start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "SMTPServer.Application")

# Output directory
set(OutputDir "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/$<CONFIG>")

# Group Core
add_subdirectory("SMTPServer.Core")

# Group App
add_subdirectory("SMTPServer.Application")
