/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2017-2018, MOWEI
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *       * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *       * Neither the name of the Southwest Research Institute, nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "mowei_driver/mowei_driver.h"

namespace mowei_driver {

MoweiDriver::MoweiDriver(int socket_handle):lock_flag_(false)
{
    /** initialize the parameters **/ 
    socket_handle_ = socket_handle;
    agv_send_service_ = new ServiceInterface(socket_handle_);
    /** publish messages **/
    get_linear_actuator_is_lock_srv_ = nh_.advertiseService("/mowei_driver/get_linear_actuator_is_lock", &MoweiDriver::getLinearActuatorIsLockServive, this);
    get_linear_actuator_pos_srv_ = nh_.advertiseService("/mowei_driver/get_linear_actuator_pos", &MoweiDriver::getLinearActuatorPosServive, this);
    get_linear_actuator_status_srv_ = nh_.advertiseService("/mowei_driver/get_linear_actuator_status", &MoweiDriver::getLinearActuatorStatusServive, this);
    get_mobile_base_battery_capacity_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_battery_capacity", &MoweiDriver::getMobileBaseBatteryCapacityServive, this);
    get_mobile_base_is_lock_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_is_lock", &MoweiDriver::getMobileBaseIsLockServive, this);
    get_mobile_base_move_for_position1_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_move_for_position1", &MoweiDriver::getMobileBaseMoveForPosition1Servive, this);
    get_mobile_base_move_for_position2_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_move_for_position2", &MoweiDriver::getMobileBaseMoveForPosition2Servive, this);
    get_mobile_base_move_for_speed_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_move_for_speed", &MoweiDriver::getMobileBaseMoveForSpeedServive, this);
    get_mobile_base_move_mode_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_move_mode", &MoweiDriver::getMobileBaseMoveModeServive, this);
    get_mobile_base_Oc_is_enable_srv_ = nh_.advertiseService("/mowei_driver/get_mobile_base_Oc_is_enable", &MoweiDriver::getMobileBaseOcIsEnableServive, this);
    set_linear_actuator_lock_srv_ = nh_.advertiseService("/mowei_driver/set_linear_actuator_lock", &MoweiDriver::setLinearActuatorLockServive, this);
    set_linear_actuator_pos_srv_ = nh_.advertiseService("/mowei_driver/set_linear_actuator_pos", &MoweiDriver::setLinearActuatorPosServive, this);
    set_mobile_base_lock_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_lock", &MoweiDriver::setMobileBaseLockServive, this);
    set_mobile_base_move_for_speed_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_move_for_speed", &MoweiDriver::setMobileBaseMoveForSpeedServive, this);
    set_mobile_base_move_mode_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_move_mode", &MoweiDriver::setMobileBaseMoveModeServive, this);
    set_mobile_base_move_position1_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_move_position1", &MoweiDriver::setMobileBaseMovePosition1Servive, this);
    set_mobile_base_move_position2_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_move_position2", &MoweiDriver::setMobileBaseMovePosition2Servive, this);
    set_mobile_base_Oc_enable_srv_ = nh_.advertiseService("/mowei_driver/set_mobile_base_Oc_enable", &MoweiDriver::setMobileBaseOcEnableServive, this);


    /** subscribe topics **/
//    trajectory_execution_subs_ = nh_.subscribe("trajectory_execution_event", 10, &MoweiDriver::trajectoryExecutionCallback,this);
}

MoweiDriver::~MoweiDriver()
{
    agv_send_service_->agvServiceLogout(&socket_handle_);
    agv_send_service_ = NULL;
}

void MoweiDriver::publishIOMsg()
{
    ros::Rate update_rate(50);
    while (ros::ok())
    {
//        mowei_msgs::IOState io_msg;
//        io_pub_.publish(io_msg);
        update_rate.sleep();
        ros::spinOnce();
    }
}

bool MoweiDriver::getLinearActuatorIsLockServive(mowei_msgs::getLinearActuatorIsLockRequest& req, mowei_msgs::getLinearActuatorIsLockResponse& resp)
{
    if(!lock_flag_)
    {
        ROS_INFO("Enter getLinearActuatorIsLockServive process");
        lock_flag_ = true;
        resp.success = agv_send_service_->getLinearActuatorIsLock();
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getLinearActuatorIsLockServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getLinearActuatorPosServive(mowei_msgs::getLinearActuatorPosRequest& req, mowei_msgs::getLinearActuatorPosResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.pos = agv_send_service_->getLinearActuatorPos();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getLinearActuatorPosServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getLinearActuatorStatusServive(mowei_msgs::getLinearActuatorStatusRequest& req, mowei_msgs::getLinearActuatorStatusResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.status = agv_send_service_->getLinearActuatorStatus();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getLinearActuatorStatusServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseBatteryCapacityServive(mowei_msgs::getMobileBaseBatteryCapacityRequest& req, mowei_msgs::getMobileBaseBatteryCapacityResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.capacity = agv_send_service_->getLinearActuatorPos();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseBatteryCapacityServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseIsLockServive(mowei_msgs::getMobileBaseIsLockRequest& req, mowei_msgs::getMobileBaseIsLockResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->getMobileBaseIsLock();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseIsLockServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseMoveForPosition1Servive(mowei_msgs::getMobileBaseMoveForPosition1Request& req, mowei_msgs::getMobileBaseMoveForPosition1Response& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        std::vector<int8_t> result;
        int *output = agv_send_service_->getMobileBaseMoveForPosition1();
        result.resize(4);
        result[0] = output[0];
        result[1] = output[1];
        result[2] = output[2];
        result[3] = output[3];
        resp.output = result;
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseMoveForPosition1Servive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseMoveForPosition2Servive(mowei_msgs::getMobileBaseMoveForPosition2Request& req, mowei_msgs::getMobileBaseMoveForPosition2Response& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        std::vector<int8_t> result;
        int *output = agv_send_service_->getMobileBaseMoveForPosition2();
        result.resize(2);
        result[0] = output[0];
        result[1] = output[1];
        resp.output = result;
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseMoveForPosition2Servive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseMoveForSpeedServive(mowei_msgs::getMobileBaseMoveForSpeedRequest& req, mowei_msgs::getMobileBaseMoveForSpeedResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        std::vector<int8_t> result;
        int *output = agv_send_service_->getMobileBaseMoveForSpeed();
        result.resize(3);
        result[0] = output[0];
        result[1] = output[1];
        result[2] = output[2];
        resp.output = result;
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseMoveForSpeedServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseMoveModeServive(mowei_msgs::getMobileBaseMoveModeRequest& req, mowei_msgs::getMobileBaseMoveModeResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.mode = agv_send_service_->getMobileBaseMoveMode();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseMoveModeServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::getMobileBaseOcIsEnableServive(mowei_msgs::getMobileBaseOcIsEnableRequest& req, mowei_msgs::getMobileBaseOcIsEnableResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.enabled = agv_send_service_->getMobileBaseOcIsEnable();
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("getMobileBaseOcIsEnableServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setLinearActuatorLockServive(mowei_msgs::setLinearActuatorLockRequest& req, mowei_msgs::setLinearActuatorLockResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setLinearActuatorLock(req.fun);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setLinearActuatorLockServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setLinearActuatorPosServive(mowei_msgs::setLinearActuatorPosRequest& req, mowei_msgs::setLinearActuatorPosResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setLinearActuatorPos(req.pos, req.speed);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setLinearActuatorPosServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseLockServive(mowei_msgs::setMobileBaseLockRequest& req, mowei_msgs::setMobileBaseLockResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseLock(req.fun);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseLockServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseMoveForSpeedServive(mowei_msgs::setMobileBaseMoveForSpeedRequest& req, mowei_msgs::setMobileBaseMoveForSpeedResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseMoveForSpeed(req.xSpeed, req.ySpeed, req.zSpeed);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseMoveForSpeedServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseMoveModeServive(mowei_msgs::setMobileBaseMoveModeRequest& req, mowei_msgs::setMobileBaseMoveModeResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseMoveMode(req.fun);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseMoveModeServive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseMovePosition1Servive(mowei_msgs::setMobileBaseMovePosition1Request& req, mowei_msgs::setMobileBaseMovePosition1Response& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseMovePosition1(req.x, req.y, req.speed);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseMovePosition1Servive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseMovePosition2Servive(mowei_msgs::setMobileBaseMovePosition2Request& req, mowei_msgs::setMobileBaseMovePosition2Response& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseMovePosition2(req.angle, req.velocity);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseMovePosition2Servive is not available now, please try it later!");
    }
    return resp.success;
}

bool MoweiDriver::setMobileBaseOcEnableServive(mowei_msgs::setMobileBaseOcenableRequest& req, mowei_msgs::setMobileBaseOcenableResponse& resp)
{
    if(!lock_flag_)
    {
        lock_flag_ = true;
        resp.success = agv_send_service_->setMobileBaseOcEnable(req.fun);
        resp.success = GET_SERVICE_Succeed;
        lock_flag_ = false;
    }
    else
    {
        resp.success = GET_SERVICE_FAILED;
        ROS_WARN("setMobileBaseOcenableServive is not available now, please try it later!");
    }
    return resp.success;
}

void MoweiDriver::updateControlStatus()
{
    data_count_++;
    if(data_count_ > 10)
    {
        data_count_ = 0;
        //        data_recieved_ = false;
        /** If the total size of the trajectory is less than buffer_size_, then it will move after 0.1s **/
    }
}

bool MoweiDriver::connectToRobotController()
{
    int ret1 = 0;

    std::string s;
    ros::param::get("/mowei_driver/server_host", s); //The server_host should be corresponding to the robot controller setup.
    server_host_ = (s=="")? "10.10.100.254" : s;
    std::cout<<"server_host:"<<server_host_<<std::endl;

    /** log in ***/
    int max_link_times = 5;
    int count = 0;
    do {
        count++;
        ret1 = agv_send_service_->agvServiceLogin(server_host_.c_str(), PORT, socket_handle_);
    }while(ret1 != 0 && count < max_link_times);
    if(count < max_link_times)
        return true;
    else
        return false;
}

void MoweiDriver::run()
{
    ROS_INFO("Start the driver!");

    /** connect to the robot controller **/
    if(connectToRobotController())
    {
        /** communication Timer between ros node and real robot controller. **/
//        timer_ = nh_.createTimer(ros::Duration(1.0 / TIMER_SPAN_), &MoweiDriver::timerCallback, this);
//        timer_.start();

        /** get the io states of the robot **/
//        mb_publish_thread_ = new std::thread(boost::bind(&MoweiDriver::publishIOMsg, this));

    } 
}

}

