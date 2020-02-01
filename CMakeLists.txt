cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (mPMTAnalysis VERSION 1.0)

set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard

include($ENV{ROOTSYS}/etc/cmake/FindROOT.cmake)
include(${ROOT_USE_FILE})

add_library(mPMTlib SHARED
            mPMTEventManager.hxx
            mPMTEventAnalyser.hxx
            mPMTEventAnalyser.cxx
            mPMTEventAnalyser.hxx
            mPMTTreeReader.cxx
)

target_link_libraries(mPMTlib ${ROOT_LIBRARIES})

add_executable(RunmPMTAnalysis.exe RunmPMTAnalysis.cxx)
target_link_libraries(RunmPMTAnalysis.exe mPMTlib)

