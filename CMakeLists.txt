cmake_minimum_required(VERSION 3.17)
project(ProjektPJC1)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR "C:/Program Files (x86)/opencv-4.5.1/build")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui imgcodecs)
find_package(SFML 2.5 COMPONENTS system window graphics)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ProjektPJC1 main.cpp sfbutton.cpp sfbutton.h)
target_link_libraries(ProjektPJC1 sfml-system sfml-window sfml-graphics)
target_link_libraries(ProjektPJC1 ${OpenCV_LIBS})


