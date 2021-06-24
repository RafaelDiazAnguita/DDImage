CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(DDImage)
ENABLE_LANGUAGE(CXX)

FIND_PACKAGE(OpenCV 4.5.2	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 17)

add_executable(DDimage src/main.cpp src/DFolder.hpp)


 
