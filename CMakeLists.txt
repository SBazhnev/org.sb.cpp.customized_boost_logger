# Copyright (c) 2021 Sergey Bazhnev <SBazhnev@gmail.com>
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.16)

project(CustomizedBoostLoggerExample 
  VERSION 1.0
  LANGUAGES CXX
)

set(SOURCE_FILES_DIR
  ${CMAKE_SOURCE_DIR}/src
)

set(MAIN_SOURCE_FILES
  ${SOURCE_FILES_DIR}/main.cpp
) 

set(SOURCE_FILES 
  ${SOURCE_FILES_DIR}/logger.cpp
)

find_package(Boost 
  COMPONENTS log
  REQUIRED 
)

add_executable(CustomizedBoostLoggerExample ${MAIN_SOURCE_FILES} ${SOURCE_FILES})

target_link_libraries(CustomizedBoostLoggerExample 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_LOG_LIBRARY}
)
