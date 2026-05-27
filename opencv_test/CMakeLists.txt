cmake_minimum_required(VERSION 3.10)
project(opencv_camera LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 强制在 /usr/local 里找 OpenCV（你源码编译的版本）
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")

find_package(OpenCV REQUIRED)

# 打印调试信息（可选，但强烈建议保留）
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

add_executable(opencv_camera opencv_test.cpp)

target_link_libraries(opencv_camera PRIVATE ${OpenCV_LIBS})