cmake_minimum_required(VERSION 3.20)
project(main LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ROOT
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})


set(PYTHIA8 ../pythia8318)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(main ${SOURCES})
target_include_directories(main SYSTEM PRIVATE include ${PYTHIA8}/include)
target_link_directories(main PRIVATE ${PYTHIA8}/lib)
target_link_libraries(main PRIVATE pythia8 ${ROOT_LIBRARIES} ${CMAKE_DL_LIBS})
set_target_properties(main PROPERTIES BUILD_RPATH ${PYTHIA8}/lib)








