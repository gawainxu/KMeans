cmake_minimum_required(VERSION 2.6)
project(kmeans)

find_package(OpenCV REQUIRED)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")
add_executable(kmeans ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(kmeans ${OpenCV_LIBS})
install(TARGETS kmeans RUNTIME DESTINATION bin)
