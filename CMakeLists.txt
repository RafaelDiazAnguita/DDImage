CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(DDImage)
ENABLE_LANGUAGE(CXX)

FIND_PACKAGE(OpenCV 3.0	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS "-g")

add_executable(DDimage src/main.cpp src/DFolder.hpp)


 
