cmake_minimum_required(VERSION 3.14)

project(winapi_lib LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(WINAPI_LIBS ole32 oleaut32 uuid)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  link_libraries(-static)
  set(COMMON_FLAGS "-mwindows -municode -Wall -Wextra -Wno-missing-field-initializers")
  set(COMMON_FLAGS_DEBUG "-g3 -Og")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(flags "/Wall")
endif()

set(CMAKE_CXX_FLAGS ${COMMON_FLAGS})
set(CMAKE_C_FLAGS ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${COMMON_FLAGS_DEBUG})
set(CMAKE_C_FLAGS_DEBUG ${COMMON_FLAGS_DEBUG})

set(SOURCES
  src/application.cpp
  src/basic_widget.cpp
  src/main.cpp
  src/widget.cpp
)

add_executable(${PROJECT_NAME}.exe ${SOURCES})
