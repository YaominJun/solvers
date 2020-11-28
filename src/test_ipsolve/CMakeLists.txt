cmake_minimum_required(VERSION 2.8.3)
project(test_ipsolve)

add_definitions(-DBOOST_ALL_DYN_LINK)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 ${CMAKE_CXX_FLAGS}")

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(catkin REQUIRED COMPONENTS
    roscpp
    roslib
    rospy    
)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp roslib rospy
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
 	    src/test.cpp
        
)

link_directories(
    include/ipsolve
  ${catkin_LIB_DIRS}
)
  
target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
)

set(linked_libs
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    lpsolve55
)

add_executable(test_ipsolve_node 
                src/test.cpp 
                )
add_dependencies(test_ipsolve_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_ipsolve_node ${linked_libs} )

add_executable(test_ipsolve_binary_node 
                src/test_binary.cpp 
                )
add_dependencies(test_ipsolve_binary_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_ipsolve_binary_node ${linked_libs} )



