/** ************************************************************************************************************************************************************
  *Copyright(C), 2017-2018, Mowei Technolohy Co., Ltd
  *
  *FileName:     serviceinterface.h
  *
  *Author:       Allen
  *
  *Version:      V1.0.0
  *
  *Date:         2018-06-27
  *
  ************************************************************************************************************************************************************/

/**
CopyRight Mowei Technology Co.Ltd. All Rights Reserved

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of mosquitto nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


This product includes software developed by the OpenSSL Project for use in the
OpenSSL Toolkit. (http://www.openssl.org/)
This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com)
This product includes software written by Tim Hudson (tjh@cryptsoft.com)
*/



#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "AgvControl.h"

#define PORT			8899		/* Port the Ethernet DAQ always uses */
#define AGV_MESSAGE_SIZE_MAX 64
#define AGV_MESSAGE_ERROR_CODE 0x8000
#define TIME_FOR_WAIT_AGV_MESSAGE_RESPONSE 5  //ms
#define RESEND_AGV_MESSAGE_MAX_TIMERS 5

using namespace std;
typedef unsigned char byte;
typedef int SOCKET_HANDLE;

namespace mowei_driver {
class ServiceInterface    /** API for user **/
{
public:
    int socket_handle_;

    /**
     * @brief constructor
     */
    ServiceInterface();
    ServiceInterface(int socket_handle);
    
    /**
     * @brief destructor
     */
    ~ServiceInterface();

    /**********************************************************************************************************************************************
     ***********¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡agv system interface¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡**********
     **********************************************************************************************************************************************/

public:

    /**
     * @brief: Login¡¡¡¡establish connection with agv server£»
     *
     *
     * @param: host     agv IP address
     * @param: port     agv server port
     * @param: userName username  default: *****
     * @param: possword password ¡¡default: 123456
     * @return¡¡success: ErrnoSucc; error: ErrID
     */
    int agvServiceLogin(const char* host, int port, SOCKET_HANDLE handle);
    int Connect(SOCKET_HANDLE * handle, const char * ipAddress, int port);

    /**
     * @brief ServiceInterface::SendAndReceiveAGVMessage
     * @param socket
     * @param inputBuf
     * @param inputNum
     * @param outputBuf
     * @return
     */
    int SendAndReceiveAGVMessage(SOCKET_HANDLE *socket, unsigned char *inputBuf, int inputNum,  unsigned char *outputBuf);
    int SendAGVCommand(SOCKET_HANDLE *socket, const char *inputBuf, int inputNum,  char *outputBuf, int outputNum);
    /**
     * @brief sleep for a duration
     * @param ms->duration
     */
    void MySleep(unsigned long ms);

    /**
     * @brief: Logout
     * @return¡¡success: ErrnoSucc; error: ErrID
     */
    void  agvServiceLogout(SOCKET_HANDLE * handle);

    /**********************************************************************************************************************************************
     *****¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡query agv system states¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡*******
     **********************************************************************************************************************************************/
public:

    /**
     * @brief: Check whether the LinearActuator is locked.
     * @return: Output parameter£º0:locked£» 1:unlocked. Others:error.
     */
    int getLinearActuatorIsLock(void);


    /**
     * @brief: Get the present position the Linear Actuator is on.
     * @return: Current position from the top of the agv. unit:mm, scope:[0, 1500].
     */
    int getLinearActuatorPos(void);


    /**
     * @brief: Get the status of the Linear Actuator.
     * @return: Status and error.
     */
    int getLinearActuatorStatus(void);


    /**
     * @brief: Check whether the MobileBase is locked.
     * @return: 0:locked£» 1:unlocked. Others:error.
     */
    int getMobileBaseIsLock(void);


    /**
     * @brief: Check whether the sensors for obstacle detection is enabled.
     * @return: 0:locked£» 1:unlocked. Others:error.
     */
    int getMobileBaseOcIsEnable(void);


    /**
     * @brief: Get the capacity of the Battery.
     * @return: Battery capacity 1=0.1V, [0, 560], EX: 495=49.5V.
     */
    int  getMobileBaseBatteryCapacity(void);


    /**
     * @brief: Get the mode of the MobileBase moving.
     * @return: 0:speed mode£» 1:position mode.
     */
    int getMobileBaseMoveMode(void);


    /**
     * @brief: Get the distance of x axis and y axis that MobileBase have moved.
     * @return: Output parameter 1£ºdistence of  x axis that MobileBase have moved, unit: 1mm, scope: [-1000,1000].
     *          Output parameter 2£ºdistence of  y axis that MobileBase have moved, unit: 1mm, scope: [-1000,1000].
     *          Output parameter 3£ºrated speed, unit: 1mm/s. scope: [0, 800].
     */
    int*  getMobileBaseMoveForPosition1(void);


    /**
     * @brief: Get the angle of z axis that MobileBase have moved and current velocity of MobileBase.
     * @return: Output parameter 1£ºdata[0], angle of  MobileBase have moved. unit: 0.1¡ã, scope: [-3590, 3590].
     *          Output parameter 2£ºdata[1], current velocity, unit: 0.1¡ã/s.  scope: [0, 500],  EX: 200=20¡ã/s.
     */
    int*  getMobileBaseMoveForPosition2(void);


    /**
     * @brief: Get the current speed of  MobileBase.
     * @return: Output parameter 1£º	data[0], current x axis speed, unit: 1mm/s. scope: [-800, 800].
     *          Output parameter 2£ºdata[1], current y axis speed, unit: 1mm/s. scope: [-800, 800].
     *          Output parameter 3£ºdata[2], current z axis speed, unit: 0.1¡ã/s, scope: [-500, 500], EX: 360=36¡ã/s.
     */
    int*  getMobileBaseMoveForSpeed(void);

    /*******************************************************************agvÔË¶¯½Ó¿ÚÏà¹ØµÄ½Ó¿Ú*************************************************************/
 
public:

    /**
     * @brief: lock the LinearActuator
     * @param value: 0:lock£» 1:unlock; Others:invalid.
     * @return: 0:succeed; Others:error.
     */
    int setLinearActuatorLock(short value);


    /**
     * @brief: Set the target position that you expect the Linear Actuator reach.
     * @param pos: target position from the top of the agv. unit: mm, scope: [0, 1500].
     * @param speed: linear actuator move rated speed. unit: mm/s, scope: [0, 500].
     * @return: 0:succeed; Others:error.
     */
    int setLinearActuatorPos(short pos, short speed);


    /**
     * @brief: Lock the MobileBase.
     * @param value: 0:lock£» 1:unlock.
     * @return: 0:succeed; Others:error.
     */
    int setMobileBaseLock(short value);


    /**
     * @brief: Enable or disable the sensors for obstacle detection.
     * @param value: 0:enable£» 1:disable.
     * @return: 0:succeed; Others:error.
     */
    int setMobileBaseOcEnable(short value);


    /**
     * @brief: Set the mode of the MobileBase moving.
     * @param value: 0:speed mode£» 1:position mode.
     * @return: 0:succeed; Others:error.
     */
    int setMobileBaseMoveMode(short value);


    /**
     * @brief: Set required distance of x axis and y axis.
     * @param xAxis: Set required distance of x axis, unit: mm, scope: [-1000,1000].
     * @param yAxis: Set required distance of y axis, unit: mm, scope: [-1000,1000].
     * @param ratedSpeed: unit:mm/s, scope:[0, 800].
     * @return: 0:succeed; Others:error.
     */
    int setMobileBaseMovePosition1(short xAxis, short yAxis,  short ratedSpeed);


    /**
      * @brief: Set required angle of z axis.
      * @param requiredAngle: unit: 0.1¡ã, scope: [-3590, 3590], EX: 900=90¡ã.
      * @param velocity: unit: 0.1¡ã/s. scope: [0, 500], EX: 200=20¡ã/s.
      * @return: 0:succeed; Others:error.
      */
     int setMobileBaseMovePosition2(short requiredAngle, short velocity);


     /**
     * @brief: Set the required speed of MobileBase.
     * @param xAxis: x axis required speed, unit: 1mm/s. scope: [-800, 800].
     * @param yAxis: y axis required speed, unit: 1mm/s. scope: [-800, 800].
     * @param zAxis: z axis required speed, unit: 0.1¡ã/s, scope: [-500, 500], EX:360=36¡ã/s.
     * @return: 0:succeed; Others:error.
     */
    int setMobileBaseMoveForSpeed(short xAxis, short yAxis , short zAxis);


private:
    pthread_mutex_t                    m_robotEndSpeedCallbackChangeMutex;

    AgvControl mAgvController;
    unsigned char agvSendBuf[AGV_MESSAGE_SIZE_MAX];
    unsigned char agvReceiveBuf[AGV_MESSAGE_SIZE_MAX];
    int agvSendLen;
};
}
#endif // SERVICEINTERFACE_H
