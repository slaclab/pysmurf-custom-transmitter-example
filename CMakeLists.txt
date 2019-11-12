# ----------------------------------------------------------------------------
# Title      : ROGUE Example Module CMAKE
# ----------------------------------------------------------------------------
# File       : CMakeLists.txt
# Created    : 2018-02-27
# ----------------------------------------------------------------------------
# This file is part of the rogue_example software. It is subject to
# the license terms in the LICENSE.txt file found in the top-level directory
# of this distribution and at:
#    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# No part of the rogue_example software, including this file, may be
# copied, modified, propagated, or distributed except according to the terms
# contained in the LICENSE.txt file.
# ----------------------------------------------------------------------------

# Check cmake version
cmake_minimum_required(VERSION 2.8)
include(InstallRequiredSystemLibraries)

# Project name
project (MyModule)

# C/C++
enable_language(CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#####################################
# Find Rogue & Support Librarie
#####################################
# Find Rogue
if (DEFINED ENV{ROGUE_DIR})
   set(Rogue_DIR $ENV{ROGUE_DIR}/lib)
else()
   set(Rogue_DIR ${CMAKE_PREFIX_PATH}/lib)
endif()
find_package(Rogue REQUIRED)

# Find smurf
if (DEFINED ENV{SMURF_DIR})
   set(smurf_DIR $ENV{SMURF_DIR}/lib)
else()
   set(smurf_DIR ${CMAKE_PREFIX_PATH}/lib)
endif()
find_package(smurf REQUIRED)

#####################################
# Setup build
#####################################
# Include files
include_directories(${ROGUE_INCLUDE_DIRS})
include_directories(${SMURF_INCLUDE_DIRS})
include_directories(/usr/local/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/)

# Create MyModule python library
AUX_SOURCE_DIRECTORY(src SRC_FILES)
add_library(MyModule SHARED ${SRC_FILES})

# Set output to TOP/lib, remove lib prefix
set_target_properties(MyModule PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set_target_properties(MyModule PROPERTIES PREFIX "")

# Link to rogue core
TARGET_LINK_LIBRARIES(MyModule LINK_PUBLIC ${ROGUE_LIBRARIES} ${SMURF_LIBRARIES})
