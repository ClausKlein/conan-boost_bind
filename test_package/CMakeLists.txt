project(test_package)
cmake_minimum_required(VERSION 3.1.2)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
### target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
conan_target_link_libraries(${PROJECT_NAME})
