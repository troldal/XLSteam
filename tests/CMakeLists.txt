#=======================================================================================================================
# Preamble
#=======================================================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(XLSteam.Tests)

#=======================================================================================================================
# Define TEST target
#=======================================================================================================================
add_executable(XLSteamTests EXCLUDE_FROM_ALL "")
target_sources(XLSteamTests
        PRIVATE
        catch_amalgamated.cpp
        TestXLSteamPT.cpp
        TestXLSteamPH.cpp
        TestXLSteamPS.cpp
        TestXLSteamPU.cpp
        TestXLSteamPV.cpp
        TestXLSteamTV.cpp
#        TestXLSteamUV.cpp
        )
