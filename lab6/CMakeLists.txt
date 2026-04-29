cmake_minimum_required(VERSION 3.10)
project(OpenCV_Lab6)

set(OpenCV_DIR "C:/opencv/build")
find_package(OpenCV REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab6 ${SOURCES})

target_link_libraries(lab6 ${OpenCV_LIBS})