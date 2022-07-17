cmake_minimum_required(VERSION 3.0.2)
project(Serial)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(OpenCV_LIB_DIR "~/opencv/opencv-4.5.5/build")
find_package(OpenCV 4.5.5 REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
)

catkin_package(
)
list(APPEND SOURCES
  src/serial.cpp
)
list(APPEND thirdparty_libraries
  ${Boost_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
include_directories(

  # include
  ${catkin_INCLUDE_DIRS}
)
add_executable(open
  ${SOURCES}
)
target_link_libraries(open ${catkin_LIBRARIES} ${thirdparty_libraries})
