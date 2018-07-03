cmake_minimum_required(VERSION 2.8.3)
project(mowei_msgs)

find_package(catkin REQUIRED COMPONENTS message_generation std_msgs)

# add_message_files(
#   FILES
# )

## Generate services in the 'srv' folder
add_service_files(
   FILES
   getLinearActuatorIsLock.srv
   getLinearActuatorPos.srv
   getLinearActuatorStatus.srv 
   getMobileBaseBatteryCapacity.srv
   getMobileBaseIsLock.srv
   getMobileBaseMoveForPosition1.srv
   getMobileBaseMoveForPosition2.srv
   getMobileBaseMoveForSpeed.srv
   getMobileBaseMoveMode.srv
   getMobileBaseOcIsEnable.srv
   setLinearActuatorLock.srv
   setLinearActuatorPos.srv
   setMobileBaseLock.srv
   setMobileBaseMoveForSpeed.srv
   setMobileBaseMoveMode.srv
   setMobileBaseMovePosition1.srv
   setMobileBaseMovePosition2.srv
   setMobileBaseOcenable.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
