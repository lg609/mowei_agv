/*#####################################
Note: mowei_driver is a sample of TCP/IP interface for Mowei-agv.
There ara some main API for application as follow, please see AgvControl.h for more information.
################################*/


#ifndef MOWEI_DRIVER_H_
#define MOWEI_DRIVER_H_

#include <thread>
#include <string>
#include <sys/timeb.h>
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32MultiArray.h>

#include <mowei_msgs/getLinearActuatorIsLock.h>
#include <mowei_msgs/getLinearActuatorPos.h>
#include <mowei_msgs/getLinearActuatorStatus.h>
#include <mowei_msgs/getMobileBaseBatteryCapacity.h>
#include <mowei_msgs/getMobileBaseIsLock.h>
#include <mowei_msgs/getMobileBaseMoveForPosition1.h>
#include <mowei_msgs/getMobileBaseMoveForPosition2.h>
#include <mowei_msgs/getMobileBaseMoveForSpeed.h>
#include <mowei_msgs/getMobileBaseMoveMode.h>
#include <mowei_msgs/getMobileBaseOcIsEnable.h>
#include <mowei_msgs/setLinearActuatorLock.h>
#include <mowei_msgs/setLinearActuatorPos.h>
#include <mowei_msgs/setMobileBaseLock.h>
#include <mowei_msgs/setMobileBaseMoveForSpeed.h>
#include <mowei_msgs/setMobileBaseMoveMode.h>
#include <mowei_msgs/setMobileBaseMovePosition1.h>
#include <mowei_msgs/setMobileBaseMovePosition2.h>
#include <mowei_msgs/setMobileBaseOcenable.h>

#include "sensor_msgs/JointState.h"
#include "service_interface.h"

#define GET_SERVICE_FAILED -1
#define GET_SERVICE_Succeed 1
#define PORT			8899		/* Port the Ethernet DAQ always uses */

namespace mowei_driver
{
    class MoweiDriver
    {
        public:
            MoweiDriver();
            MoweiDriver(int socket_handle);
            ~MoweiDriver();

            bool getLinearActuatorIsLockServive(mowei_msgs::getLinearActuatorIsLockRequest& req, mowei_msgs::getLinearActuatorIsLockResponse& resp);
            bool getLinearActuatorPosServive(mowei_msgs::getLinearActuatorPosRequest& req, mowei_msgs::getLinearActuatorPosResponse& resp);
            bool getLinearActuatorStatusServive(mowei_msgs::getLinearActuatorStatusRequest& req, mowei_msgs::getLinearActuatorStatusResponse& resp);
            bool getMobileBaseBatteryCapacityServive(mowei_msgs::getMobileBaseBatteryCapacityRequest& req, mowei_msgs::getMobileBaseBatteryCapacityResponse& resp);
            bool getMobileBaseIsLockServive(mowei_msgs::getMobileBaseIsLockRequest& req, mowei_msgs::getMobileBaseIsLockResponse& resp);
            bool getMobileBaseMoveForPosition1Servive(mowei_msgs::getMobileBaseMoveForPosition1Request& req, mowei_msgs::getMobileBaseMoveForPosition1Response& resp);
            bool getMobileBaseMoveForPosition2Servive(mowei_msgs::getMobileBaseMoveForPosition2Request& req, mowei_msgs::getMobileBaseMoveForPosition2Response& resp);
            bool getMobileBaseMoveForSpeedServive(mowei_msgs::getMobileBaseMoveForSpeedRequest& req, mowei_msgs::getMobileBaseMoveForSpeedResponse& resp);
            bool getMobileBaseMoveModeServive(mowei_msgs::getMobileBaseMoveModeRequest& req, mowei_msgs::getMobileBaseMoveModeResponse& resp);
            bool getMobileBaseOcIsEnableServive(mowei_msgs::getMobileBaseOcIsEnableRequest& req, mowei_msgs::getMobileBaseOcIsEnableResponse& resp);
            bool setLinearActuatorLockServive(mowei_msgs::setLinearActuatorLockRequest& req, mowei_msgs::setLinearActuatorLockResponse& resp);
            bool setLinearActuatorPosServive(mowei_msgs::setLinearActuatorPosRequest& req, mowei_msgs::setLinearActuatorPosResponse& resp);
            bool setMobileBaseLockServive(mowei_msgs::setMobileBaseLockRequest& req, mowei_msgs::setMobileBaseLockResponse& resp);
            bool setMobileBaseMoveForSpeedServive(mowei_msgs::setMobileBaseMoveForSpeedRequest& req, mowei_msgs::setMobileBaseMoveForSpeedResponse& resp);
            bool setMobileBaseMoveModeServive(mowei_msgs::setMobileBaseMoveModeRequest& req, mowei_msgs::setMobileBaseMoveModeResponse& resp);
            bool setMobileBaseMovePosition1Servive(mowei_msgs::setMobileBaseMovePosition1Request& req, mowei_msgs::setMobileBaseMovePosition1Response& resp);
            bool setMobileBaseMovePosition2Servive(mowei_msgs::setMobileBaseMovePosition2Request& req, mowei_msgs::setMobileBaseMovePosition2Response& resp);
            bool setMobileBaseOcEnableServive(mowei_msgs::setMobileBaseOcenableRequest& req, mowei_msgs::setMobileBaseOcenableResponse& resp);

            void updateControlStatus();
            void run();
            bool connectToRobotController();
            const int UPDATE_RATE_ = 500;
            const int TIMER_SPAN_ = 50;
            const double THRESHHOLD = 0.000001;

        public:
            int socket_handle_;
            std::string server_host_;
            ServiceInterface *agv_send_service_;      //send

            ros::Publisher joint_states_pub_;
            ros::ServiceServer get_linear_actuator_is_lock_srv_;
            ros::ServiceServer get_linear_actuator_pos_srv_;
            ros::ServiceServer get_linear_actuator_status_srv_;
            ros::ServiceServer get_mobile_base_battery_capacity_srv_;
            ros::ServiceServer get_mobile_base_is_lock_srv_;
            ros::ServiceServer get_mobile_base_move_for_position1_srv_;
            ros::ServiceServer get_mobile_base_move_for_position2_srv_;
            ros::ServiceServer get_mobile_base_move_for_speed_srv_;
            ros::ServiceServer get_mobile_base_move_mode_srv_;
            ros::ServiceServer get_mobile_base_Oc_is_enable_srv_;
            ros::ServiceServer set_linear_actuator_lock_srv_;
            ros::ServiceServer set_linear_actuator_pos_srv_;
            ros::ServiceServer set_mobile_base_lock_srv_;
            ros::ServiceServer set_mobile_base_move_for_speed_srv_;
            ros::ServiceServer set_mobile_base_move_mode_srv_ ;
            ros::ServiceServer set_mobile_base_move_position1_srv_;
            ros::ServiceServer set_mobile_base_move_position2_srv_;
            ros::ServiceServer set_mobile_base_Oc_enable_srv_;

        private:
            void timerCallback(const ros::TimerEvent& e);
            void publishIOMsg();


            bool lock_flag_;
            int data_count_;

            ros::NodeHandle nh_;
            ros::Timer timer_;
            ros::Timer io_publish_timer;
            std::thread* mb_publish_thread_;

    };
}

#endif /* MOWEI_DRIVER_H_ */
