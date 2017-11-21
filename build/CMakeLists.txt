cmake_minimum_required(VERSION 3.5)
project (star)

set(INCLUDE_DIR
  ../include
)

include_directories(${INCLUDE_DIR})

set(SOURCES
  ../src/main.cpp

  ../include/engine.h
  ../src/engine.cpp
)

add_executable(star ${SOURCES})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED audio network graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(star ${SFML_LIBRARIES})
endif()
