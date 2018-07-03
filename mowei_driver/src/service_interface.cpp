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
CopyRight  Mowei Technology Co.Ltd. All Rights Reserved

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

#include "mowei_driver/service_interface.h"
#include "mowei_driver/AgvControl.h"

namespace mowei_driver {
	
typedef struct SendCommandStruct
{
    byte command[19];
    byte reserved;
}SendCommand;

typedef struct CommandResponseStruct
{
    byte command[30];
}CommandResponse;

CommandResponse commandResponse;


ServiceInterface::ServiceInterface(int socket_handle)
{
    socket_handle_ = socket_handle;
}

/* Sleep ms milliseconds */
void ServiceInterface::MySleep(unsigned long ms)
{
    usleep(ms * 1000);
}

int ServiceInterface::agvServiceLogin(const char* host, int port, SOCKET_HANDLE socketHandle)
{
    return Connect(&socketHandle, host, port);
}

int ServiceInterface::Connect(SOCKET_HANDLE * handle, const char * ipAddress, int port)
{
    struct sockaddr_in addr;
    struct hostent *he;
    int err;

    *handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (*handle == -1)
    {
        std::cout<<"Socket could not be opened."<<std::endl;
        return -2;
    }
    he = gethostbyname(ipAddress);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    std::cout<<"Connecting to EtherDAQ."<<std::endl;

    err = connect(*handle, (struct sockaddr *)&addr, sizeof(addr));
    if (err < 0)
    {
        return -3;
    }
    return 0;
}

void ServiceInterface::agvServiceLogout(SOCKET_HANDLE * handle)
{
    close(*handle);
}

int ServiceInterface::SendAGVCommand(SOCKET_HANDLE *socket, const char *inputBuf, int inputNum,  char *outputBuf, int outputNum)
{
    int sendSuccess, readSuccess;
    sendSuccess = send(*socket, (const void *)inputBuf, inputNum, 0);
    if (sendSuccess < 0)
        return sendSuccess;

    MySleep(2);

    readSuccess = recv(*socket, outputBuf, outputNum, 0);

    if (readSuccess < 0)
        return readSuccess;

    for(int i = 0; i < outputNum; i++)
        std::cout << "data:" << hex << (int)outputBuf[i] << std::endl;

    return 0;
}

int ServiceInterface::SendAndReceiveAGVMessage(SOCKET_HANDLE *socket, unsigned char *inputBuf, int inputNum,  unsigned char *outputBuf)
{
    int sendSuccess, readSuccess;
    int resendCounter=0;

    while(resendCounter<RESEND_AGV_MESSAGE_MAX_TIMERS)
    {
        sendSuccess = send(*socket, (const void *)inputBuf, inputNum, 0);
        if (sendSuccess >= 0)
        {
            MySleep(TIME_FOR_WAIT_AGV_MESSAGE_RESPONSE);

            readSuccess = recv(*socket, outputBuf, AGV_MESSAGE_SIZE_MAX, 0);

            if (readSuccess >= 0)
            {
                if (mAgvController.ProcessReceivedAgvMessage(inputBuf,inputNum,outputBuf,readSuccess)>=0)
                {
                    for(int i = 0; i < readSuccess; i++)
                    {
                        std::cout << "data:" << hex << (int)outputBuf[i] << std::endl;
                    }
                    break;
                }
            }
        }
        resendCounter++;
    }

    if (resendCounter>=RESEND_AGV_MESSAGE_MAX_TIMERS)
    {
        std::cout << "Send ERROR!!!" << std::endl;
        return AGV_MESSAGE_ERROR_CODE;
    }

    return 0;
}


/**
 * @brief: Check whether the LinearActuator is locked.
 * @return: Output parameter£º0:locked£» 1:unlocked. Others:error.
 */
int ServiceInterface::getLinearActuatorIsLock(void)
{
     //if check connected
    agvSendLen=mAgvController.wr_getLinearActuatorIsLock(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return mAgvController.rd_getLinearActuatorIsLock();
}

/**
 * @brief: Get the present position the Linear Actuator is on.
 * @return: Current position from the top of the agv. unit:mm, scope:[-1500, 1500].
 */
// if return [0x0000~0xffff] then error=???????
int ServiceInterface::getLinearActuatorPos(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getLinearActuatorPos(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getLinearActuatorPos();
}



/**
 * @brief: Get the status of the Linear Actuator.
 * @return: Status and error.
 */
int ServiceInterface::getLinearActuatorStatus(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getLinearActuatorStatus(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getLinearActuatorStatus();
}


/**
 * @brief: Check whether the MobileBase is locked.
 * @return: 0:locked£» 1:unlocked. Others:error.
 */
int ServiceInterface::getMobileBaseIsLock(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseIsLock(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getMobileBaseIsLock();
}


/**
 * @brief: Check whether the sensors for obstacle detection is enabled.
 * @return: 0:locked£» 1:unlocked. Others:error.
 */
int ServiceInterface::getMobileBaseOcIsEnable(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseODIsEnalbe(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getMobileBaseODIsEnalbe();
}


/**
 * @brief: Get the capacity of the Battery.
 * @return: Battery capacity 1=0.1V, [0, 560], EX: 495=49.5V.
 */
int  ServiceInterface::getMobileBaseBatteryCapacity(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseBatteryCapacity(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getMobileBaseBatteryCapacity();
}


/**
 * @brief: Get the mode of the MobileBase moving.
 * @return: 0:speed mode£» 1:position mode.
 */
int ServiceInterface::getMobileBaseMoveMode(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseMoveMode(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }

    return mAgvController.rd_getMobileBaseMoveMode();
}

/**
 * @brief: Get the distance of x axis and y axis that MobileBase have moved.
 * @return: Output parameter 1£ºdistence of  x axis that MobileBase have moved, unit: 1mm, scope: [-1000,1000].
 *          Output parameter 2£ºdistence of  y axis that MobileBase have moved, unit: 1mm, scope: [-1000,1000].
 *          Output parameter 3£ºrated speed, unit: 1mm/s. scope: [0, 800].
 *          need modify
 */

//Function: rd_getMobileBaseMoveCurrentSpeedAndPosition
//Description: get value of getMobileBaseMoveCurrentSpeedAndPosition
//return
//data[0], current x axis speed,
//data[1], current y axis speed,
//data[2], current x axis position,
//data[3], current y axis position,
int*  ServiceInterface::getMobileBaseMoveForPosition1(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseMoveAll(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return nullptr;
    }

    return mAgvController.rd_getMobileBaseMoveCurrentSpeedAndPosition();
}

/**
 * @brief: Get the angle of z axis that MobileBase have moved and current velocity of MobileBase.
 * @return: Output parameter 1£ºdata[0], angle of  MobileBase have moved. unit: 0.1¡ã, scope: [-3590, 3590].
 *          Output parameter 2£ºdata[1], current velocity, unit: 0.1¡ã/s.  scope: [0, 500],  EX: 200=20¡ã/s.
 */
int*  ServiceInterface::getMobileBaseMoveForPosition2(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseMoveForRevolve(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return nullptr;
    }

    return mAgvController.rd_getMobileBaseMoveForRevolve();
}


/**
 * @brief: Get the current speed of  MobileBase.
 * @return: Output parameter 1£º	data[0], current x axis speed, unit: 1mm/s. scope: [-800, 800].
 *          Output parameter 2£ºdata[1], current y axis speed, unit: 1mm/s. scope: [-800, 800].
 *          Output parameter 3£ºdata[2], current z axis speed, unit: 0.1¡ã/s, scope: [-500, 500], EX: 360=36¡ã/s.
 */
int*  ServiceInterface::getMobileBaseMoveForSpeed(void)
{
    //if check connected
    agvSendLen=mAgvController.wr_getMobileBaseMoveForSpeed(agvSendBuf);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return nullptr;
    }

    return mAgvController.rd_getMobileBaseMoveForSpeed();
}

/**
 * @brief: lock the LinearActuator
 * @param value: 0:lock£» 1:unlock; Others:invalid.
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setLinearActuatorLock(short value)
{
    //if check connected
    bool flag;
    if (value==0)
    {
        flag = false;
    }
    else
    {
        flag = true;
    }
    agvSendLen=mAgvController.wr_setLinearActuatorLock(agvSendBuf,flag);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}


/**
 * @brief: Set the target position that you expect the Linear Actuator reach.
 * @param pos: target position from the top of the agv. unit: mm, scope: [0, 1500].
 * @param speed: linear actuator move rated speed. unit: mm/s, scope: [0, 500].
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setLinearActuatorPos(short pos, short speed)
{
    //if check connected
    agvSendLen=mAgvController.wr_setLinearActuatorPos(agvSendBuf,speed,pos);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}


/**
 * @brief: Lock the MobileBase.
 * @param value: 0:lock£» 1:unlock.
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setMobileBaseLock(short value)
{
    //if check connected
    bool flag;
    if (value==0)
    {
        flag = false;
    }
    else
    {
        flag = true;
    }
    agvSendLen=mAgvController.wr_setMobileBaseLock(agvSendBuf,flag);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}

/**
 * @brief: Enable or disable the sensors for obstacle detection.
 * @param value: 0:enable£» 1:disable.
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setMobileBaseOcEnable(short value)
{
    //if check connected
    bool flag;
    if (value==0)
    {
        flag = false;
    }
    else
    {
        flag = true;
    }
    agvSendLen=mAgvController.wr_setMobileBaseODEnalbe(agvSendBuf,flag);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}

/**
 * @brief: Set the mode of the MobileBase moving.
 * @param value: 0:speed mode£» 1:position mode.
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setMobileBaseMoveMode(short value)
{
    //if check connected
    bool flag;
    if (value==0)
    {
        flag = false;
    }
    else
    {
        flag = true;
    }
    agvSendLen=mAgvController.wr_setMobileBaseMoveMode(agvSendBuf,flag);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}

/**
 * @brief: Set required distance of x axis and y axis.
 * @param xAxis: Set required distance of x axis, unit: mm, scope: [-1000,1000].
 * @param yAxis: Set required distance of y axis, unit: mm, scope: [-1000,1000].
 * @param ratedSpeed: unit:mm/s, scope:[0, 800].
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setMobileBaseMovePosition1(short xAxis, short yAxis,  short ratedSpeed)
{
    //if check connected
    agvSendLen=mAgvController.wr_setMobileBaseMovePosition1(agvSendBuf,xAxis,yAxis,ratedSpeed);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}


/**
  * @brief: Set required angle of z axis.
  * @param requiredAngle: unit: 0.1¡ã, scope: [-3590, 3590], EX: 900=90¡ã.
  * @param velocity: unit: 0.1¡ã/s. scope: [0, 500], EX: 200=20¡ã/s.
  * @return: 0:succeed; Others:error.
  */
 int ServiceInterface::setMobileBaseMovePosition2(short requiredAngle, short velocity)
 {
     //if check connected
     agvSendLen=mAgvController.wr_setMobileBaseMovePosition2(agvSendBuf,requiredAngle,velocity);
     if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
     {
         return AGV_MESSAGE_ERROR_CODE;
     }
     return 0;
 }


 /**
 * @brief: Set the required speed of MobileBase.
 * @param xAxis: x axis required speed, unit: 1mm/s. scope: [-800, 800].
 * @param yAxis: y axis required speed, unit: 1mm/s. scope: [-800, 800].
 * @param zAxis: z axis required speed, unit: 0.1¡ã/s, scope: [-500, 500], EX:360=36¡ã/s.
 * @return: 0:succeed; Others:error.
 */
int ServiceInterface::setMobileBaseMoveForSpeed(short xAxis, short yAxis , short zAxis)
{
    //if check connected
    agvSendLen=mAgvController.wr_setMobileBaseMoveForSpeed(agvSendBuf,xAxis,yAxis,zAxis);
    if (SendAndReceiveAGVMessage(&socket_handle_, agvSendBuf, agvSendLen, agvReceiveBuf) != 0)
    {
        return AGV_MESSAGE_ERROR_CODE;
    }
    return 0;
}

}
