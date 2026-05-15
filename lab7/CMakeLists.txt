cmake_minimum_required(VERSION 3.10)
project(OpenCV_Lab7)

set(OpenCV_DIR "C:/opencv/build")
find_package(OpenCV REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab7 ${SOURCES})

target_link_libraries(lab7 ${OpenCV_LIBS})