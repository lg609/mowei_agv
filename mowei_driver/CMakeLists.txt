cmake_minimum_required(VERSION 2.8.3)
project(mowei_driver)

find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  roscpp
  std_msgs
  mowei_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS sensor_msgs roscpp std_msgs mowei_msgs
)


# check c++11 / c++0x
 include(CheckCXXCompilerFlag)
 CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
 CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
 if(COMPILER_SUPPORTS_CXX11)
     set(CMAKE_CXX_FLAGS "-std=c++11")
 elseif(COMPILER_SUPPORTS_CXX0X)
     set(CMAKE_CXX_FLAGS "-std=c++0x")
 else()
     message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler. Suggested solution: update the pkg build-essential ")
 endif()

include_directories(include ${catkin_INCLUDE_DIRS})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        link_directories(${catkin_LIB_DIRS}  lib/lib64)
else()
        link_directories(${catkin_LIB_DIRS}  lib/lib32)
endif()

## Declare a C++ executable
set(${PROJECT_NAME}_SOURCES1
    src/mowei_driver.cpp
    src/service_interface.cpp
    src/AgvControl.cpp
    src/driver_node.cpp
)

set(${PROJECT_NAME}_SOURCES2
    src/test.cpp
)

add_executable(mowei_driver ${${PROJECT_NAME}_SOURCES1})
add_dependencies(mowei_driver ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(test_driver ${${PROJECT_NAME}_SOURCES2})

LINK_LIBRARIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(mowei_driver ${catkin_LIBRARIES} pthread)
target_link_libraries(test_driver ${catkin_LIBRARIES})
install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


install(TARGETS mowei_driver test_driver
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
 )

add_dependencies(mowei_driver mowei_msgs_gencpp)



