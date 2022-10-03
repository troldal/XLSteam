#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.20)
project(XLSteam)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#==============================================================================
# Add the Xll base library
#==============================================================================
add_subdirectory(xll)

#==============================================================================
# Add xll template library and set source file paths
#==============================================================================
add_library(
        XLSteam
        SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/XLSteamFrontend.cpp
)

#==============================================================================
# Set Xll library properties and compile options
#==============================================================================
target_compile_options(XLSteam PRIVATE "/J" "/utf-8")
target_link_libraries(XLSteam PRIVATE xlcall xll)
set_target_properties(XLSteam PROPERTIES OUTPUT_NAME "XLSteam" SUFFIX ".xll")

add_subdirectory(tests)
add_subdirectory(fuzz)
add_subdirectory(demo)
