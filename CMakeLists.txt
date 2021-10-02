cmake_minimum_required(VERSION 3.14)

project(winapi_lib LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  link_libraries(-static)
  set(COMMON_FLAGS "-mwindows -municode -Wall -Wextra -Wno-missing-field-initializers")
  set(COMMON_FLAGS_DEBUG "-g -O0")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(COMMON_FLAGS "/Wall /DUNICODE /D_UNICODE /utf-8")
endif()

set(CMAKE_CXX_FLAGS ${COMMON_FLAGS})
set(CMAKE_C_FLAGS ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${COMMON_FLAGS_DEBUG})
set(CMAKE_C_FLAGS_DEBUG ${COMMON_FLAGS_DEBUG})

set(SOURCES
  src/application.cpp
  src/basic_widget.cpp
  src/button.cpp
  src/edit.cpp
  src/label.cpp
  src/listbox.cpp
  src/main.cpp
  src/singleline_edit.cpp
  src/multiline_edit.cpp
  src/widget.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_executable(${PROJECT_NAME}.exe ${SOURCES})
else()
  add_executable(${PROJECT_NAME} ${SOURCES})
endif()
