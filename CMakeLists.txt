cmake_minimum_required(VERSION 3.20)
project(ZadanieRekrutacyjne LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(ZadanieRekrutacyjne ${SOURCES})
target_include_directories(ZadanieRekrutacyjne SYSTEM PRIVATE include
)








