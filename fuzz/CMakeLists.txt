#=======================================================================================================================
# Preamble
#=======================================================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(XLSteam.Fuzz)

#=======================================================================================================================
# Define TEST target
#=======================================================================================================================
add_executable(XLSteamFuzz EXCLUDE_FROM_ALL "")
target_sources(XLSteamFuzz
        PRIVATE
        fuzz.cpp
        )