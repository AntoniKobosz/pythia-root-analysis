cmake_minimum_required(VERSION 3.20)
project(ZadanieRekrutacyjne LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(PYTHIA8 ../pythia8318)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(ZadanieRekrutacyjne ${SOURCES})
target_include_directories(ZadanieRekrutacyjne SYSTEM PRIVATE include ${PYTHIA8}/include)
target_link_directories(ZadanieRekrutacyjne PRIVATE ${PYTHIA8}/lib)
target_link_libraries(ZadanieRekrutacyjne PRIVATE pythia8 ${CMAKE_DL_LIBS})
set_target_properties(ZadanieRekrutacyjne PROPERTIES BUILD_RPATH ${PYTHIA8}/lib)








