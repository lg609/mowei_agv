#ifndef AGVCONTROL_H
#define AGVCONTROL_H

#include <math.h>

#define AGV_CONTROL_DATA_MAX_SIZE 64

//message receive state
enum MsgRevState{
    msgEmpty=0,
    msgOK,
    msgReceiving,
    msgGetRespondWriteOneByte,
    msgGetRespondWriteMultiBytes,
    msgGetRespondReadOneByte,
    msgGetRespondReadMultiBytes,
    msgUpdateMobileBaseState,
    msgUpdataLinearActuatorState,
    msgIdError,
    msgLengthError,
    msgCrcError,
    msgAddressError
};


class AgvControl
{
public:
    AgvControl();
    ~AgvControl();    

    //process received Agv data
    //MUST call ProcessReceivedAgvMessage() when received one frame Agv data over!
    //buf= received data
    //length= received data length
    int ProcessReceivedAgvMessage(unsigned char* sendbuf,int sendlength,unsigned char* receivedbuf,int receivedlength);


    //Function: wr_setLinearActuatorLock
    //Description: get command for setLinearActuatorLock
    //param sendbuf message buffer will save in sendbuf
    //param flag 0,lock;1,unlock
    //return message buffer length
    int wr_setLinearActuatorLock(unsigned char *sendBuf, bool flag);

    //Function: wr_getLinearActuatorIsLock
    //Description: get command for getLinearActuatorIsLock
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getLinearActuatorIsLock(unsigned char *sendBuf);
    //Function: rd_getLinearActuatorIsLock
    //Description: get value of getLinearActuatorIsLock
    //return 0,lock; 1,unlock
    short rd_getLinearActuatorIsLock();

    //Function: wr_setLinearActuatorPos
    //Description: get command for setLinearActuatorPos
    //param sendbuf message buffer will save in sendbuf
    //param speed linear actuator move speed, mm/s,0-500mm/s
    //param pos linear actuator move target position, mm,0-1500mm
    //return message buffer length
    int wr_setLinearActuatorPos(unsigned char *sendBuf,short pos, short speed);

    //Function: wr_getLinearActuatorPos
    //Description: get command for getLinearActuatorPos
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getLinearActuatorPos(unsigned char *sendBuf);
    //Function: rd_getLinearActuatorPos
    //Description: get value of getLinearActuatorPos
    //return linear actuator current position, mm,0-1500mm
    short rd_getLinearActuatorPos(void);

    //Function: wr_getLinearActuatorStatus
    //Description: get command for getLinearActuatorStatus
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getLinearActuatorStatus(unsigned char *sendBuf);
    //Function: rd_getLinearActuatorPos
    //Description: get value of getLinearActuatorPos
    //return linear actuator current position, mm,0-1500mm
    short rd_getLinearActuatorStatus(void);

    //Function: wr_setMobileBaseLock
    //Description: get command for setMobileBaseLock
    //param sendbuf message buffer will save in sendbuf
    //param flag 0,lock;1,unlock
    //return message buffer length
    int wr_setMobileBaseLock(unsigned char *sendBuf,bool flag);

    //Function: wr_getMobileBaseIsLock
    //Description: get command for getMobileBaseIsLock
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseIsLock(unsigned char *sendBuf);
    //Function: rd_getMobileBaseIsLock
    //Description: get value of getMobileBaseIsLock
    //return 0,lock;1,unlock
    short rd_getMobileBaseIsLock();

    //Function: wr_setMobileBaseODEnalbe
    //Description: get command for setMobileBaseODEnalbe
    //param sendbuf message buffer will save in sendbuf
    //param flag 0,enable;1,disable
    //return message buffer length
    int wr_setMobileBaseODEnalbe(unsigned char *sendBuf,bool flag);

    //Function: wr_getMobileBaseODIsEnalbe
    //Description: get command for getMobileBaseODIsEnalbe
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseODIsEnalbe(unsigned char *sendBuf);
    //Function: rd_getMobileBaseODIsEnalbe
    //Description: get value of getMobileBaseODIsEnalbe
    //return 0,enable;1,disable
    short rd_getMobileBaseODIsEnalbe();

    //Function: wr_getMobileBaseBatteryCapacity
    //Description: get command for getMobileBaseBatteryCapacity
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseBatteryCapacity(unsigned char *sendBuf);
    //Function: rd_getMobileBaseBatteryCapacity
    //Description: get value of getMobileBaseBatteryCapacity
    //return battery capacity 1=0.1V, E.X.:495=49.5V
    short rd_getMobileBaseBatteryCapacity();

    //Function: wr_setMobileBaseMoveMode
    //Description: get command for setMobileBaseMoveMode
    //param sendbuf message buffer will save in sendbuf
    //param flag 0,speed mode;1,position mode
    //return message buffer length
    int wr_setMobileBaseMoveMode(unsigned char *sendBuf,bool flag);

    //Function: wr_getMobileBaseMoveMode
    //Description: get command for getMobileBaseMoveMode
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseMoveMode(unsigned char *sendBuf);
    //Function: rd_getMobileBaseMoveMode
    //Description: get value of getMobileBaseMoveMode
    //return 0,speed mode;1,position mode
    short rd_getMobileBaseMoveMode();

    //Function: wr_setMobileBaseMoveForSpeed
    //Description: get command for setMobileBaseMoveForSpeed, use in speed mode
    //param sendbuf message buffer will save in sendbuf
    //param speed_x x axis speed,mm/s 0-800mm/s
    //param speed_y y axis speed,mm/s 0-800mm/s
    //param speed_z z axis speed,0.1°/s -50-50°/s, E.X.:360=36°/s
    //return message buffer length
    int wr_setMobileBaseMoveForSpeed(unsigned char *sendBuf,int speed_x,int speed_y,short speed_z);
    //Function: rd_getMobileBaseMoveCurrentSpeedAndPosition
    //Description: get value of getMobileBaseMoveCurrentSpeedAndPosition
    //return
    //data[0], current x axis speed,
    //data[1], current y axis speed,
    //data[2], current x axis position,
    //data[3], current y axis position,
    int* rd_getMobileBaseMoveCurrentSpeedAndPosition();

    //Function: wr_getMobileBaseMoveForSpeed
    //Description: get command for getMobileBaseMoveForSpeed
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseMoveForSpeed(unsigned char *sendBuf);
    //Function: rd_getMobileBaseMoveForSpeed
    //Description: get value of getMobileBaseMoveForSpeed
    //return
    //data[0], current speed,
    //data[1], current position,
    //data[2], current direction,
    int *rd_getMobileBaseMoveForSpeed();
    \
    //Function: wr_setMobileBaseMovePosition1
    //Description: get command for setMobileBaseMovePosition1
    //param sendbuf message buffer will save in sendbuf
    //param dis_x, x axis target move distence,mm,1=1mm
    //param dis_y, y axis target move distence,mm,1=1mm
    //param speed, move max speed,mm/s, 0-800mm/s
    //return message buffer length
    int wr_setMobileBaseMovePosition1(unsigned char *sendBuf,short dis_x,short dis_y,short speed);
    //Function: wr_setMobileBaseMovePosition2
    //Description: get command for setMobileBaseMovePosition2
    //param sendbuf message buffer will save in sendbuf
    //param dis, revolve degress 0.1°/s , E.X.:900=90°
    //param speed, revolve speed,0.1°/s 50°/s, E.X.:360=36°/s
    //return message buffer length
    int wr_setMobileBaseMovePosition2(unsigned char *sendBuf, short dis, short speed);

    //Function: wr_getMobileBaseMoveForRevolve
    //Description: get command for getMobileBaseMoveForRevolve
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseMoveForRevolve(unsigned char *sendBuf);

    //Function: rd_getMobileBaseMoveForRevolve
    //Description: get value of getMobileBaseMoveForRevolve
    //return
    //data[0], current revolve speed,
    //data[1], current revolve position,
    int *rd_getMobileBaseMoveForRevolve();


    //Function: wr_getMobileBaseMoveAll
    //Description: get command for getMobileBaseMoveAll
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    int wr_getMobileBaseMoveAll(unsigned char *sendBuf);

    //Function: rd_getMobileBaseMoveAll
    //Description: get value of getMobileBaseMoveAll
    //return
    //data[0], current speed,
    //data[1], current position,
    //data[2], current direction,
    //data[3], current revolve speed,
    //data[4], current revolve position,
    int *rd_getMobileBaseMoveAll();

    //Function: wr_setLinearActuatorZeroPosition
    //Description: get command for setLinearActuatorZeroPosition, current position will change to 0 position
    //param sendbuf message buffer will save in sendbuf
    //return message buffer length
    //谨慎使用！
    int wr_setLinearActuatorZeroPosition(unsigned char *sendBuf);
    //Function: wr_setMobileBaseMoveForSpeed
    //Description: get command for setMobileBaseMoveForSpeed
    //param sendbuf message buffer will save in sendbuf
    //param speed ,mm/s 0-800mm/s
    //param dir direction °,0-359°,1=1°
    //param revolve revolve speed,0.1°/s -50-50°/s, E.X.:360=36°/s
    //return message buffer length
    int wr_setMobileBaseMoveForSDR(unsigned char *sendBuf,short speed,short dir,short revolve);
    //Function: wr_setMobileBaseMoveDSD
    //Description: get command for setMobileBaseMoveDSD
    //param sendbuf message buffer will save in sendbuf
    //param distence, target distence to move,mm,1=1mm
    //param speed, max speed,mm/s 0-800mm/s
    //param dir, direction to move,0-359°,1=1°
    //return message buffer length
    int wr_setMobileBaseMoveForDSD(unsigned char *sendBuf,short distence,short speed,short dir);



    //***********************************************


    int AgvCurrentSpeedAndPositino[4];
    //AgvCurrentSpeedAndPositino[0], x axis speed
    //AgvCurrentSpeedAndPositino[1], y axis speed
    //AgvCurrentSpeedAndPositino[2], x axis position
    //AgvCurrentSpeedAndPositino[3], y axis position

    int AgvCurrentRevolve[2];
    //AgvCurrentRevolve[0], revolve speed
    //AgvCurrentRevolve[1], revolve position



    //mobile base status
#define SIZE_OF_AGV_MOBILE_BASE_STATUS 24
    int AgvMobileBaseStatus[SIZE_OF_AGV_MOBILE_BASE_STATUS];

    //linear actuator status
#define SIZE_OF_AGV_LINEAR_ACTUATOR_STATUS 8
    int AgvLinearActuatorStatus[8];

    //received data save in AgvDataReceived[]
    unsigned char AgvDataReceived[AGV_CONTROL_DATA_MAX_SIZE];
    //received data length
    int AgvDataReceivedLength;

    //Function: readAgvSingleRegister
    //Description: request update one register
    //param sendbuf message buffer will save in sendbuf
    //param address register address to update
    //return message buffer length
    int readAgvSingleRegister(unsigned char *sendbuf,short address);
    //Function: readAgvMultiRegisters
    //Description: request update multi registers
    //param sendbuf message buffer will save in sendbuf
    //param address register start address to update
    //param length length to update
    //return message buffer length
    int readAgvMultiRegisters(unsigned char *sendbuf,short address,short length);
    //Function: writeAgvSingleRegister
    //Description: write single register
    //param sendbuf message buffer will save in sendbuf
    //param address register address to write
    //param value value to write
    //return message buffer length
    int writeAgvSingleRegister(unsigned char *sendbuf, short address,short value);
    //Function: writeAgvMultiRegisters
    //Description: write multi registers
    //param sendbuf message buffer will save in sendbuf
    //param address register start address to write
    //param length length to write
    //param write_buf buffer to write
    //return message buffer length
    int writeAgvMultiRegisters(unsigned char *sendbuf, short address,unsigned char length,unsigned char *write_buf);
    //Function: getAgvRegisterByAddress
    //Description: read agv status
    //param address register start address to read
    //return point of agv status
    int *getAgvRegisterByAddress(short address);

private:
    //set Agv device id,default value=65
#define DEFAULT_AGV_DEVICE_ID 65
    unsigned char mAgvDeviceId;
    //Function: CRC16
    //Description: calculate the CRC16 checksum
    //param pchMsg buffer want to calculate
    //param wDataLen buffert length
    //return: CRC16 checksum
    short CRC16(const unsigned char *pchMsg, int wDataLen);

//Registers address list
#define ADDRESS_FOR_AGV_X 0x1001
#define ADDRESS_FOR_AGV_Y 0x1002
#define ADDRESS_FOR_AGV_Z 0x1003

#define ADDRESS_FOR_AGV_POSITION_MOVE_DISTANCE 0x1004
#define ADDRESS_FOR_AGV_POSITION_MOVE_SPEED 0x1005
#define ADDRESS_FOR_AGV_POSITION_MOVE_DIR 0x1006

#define ADDRESS_FOR_AGV_POSITION_ROTATE_DISTANCE 0x1007
#define ADDRESS_FOR_AGV_POSITION_ROTATE_SPEED 0x1008


#define ADDRESS_FOR_AGV_CURRENT_SPEED 0x1009
#define ADDRESS_FOR_AGV_CURRENT_POSITION 0x100a
#define ADDRESS_FOR_AGV_CURRENT_DIRECTION 0x100b
#define ADDRESS_FOR_AGV_CURRENT_ROTATE_SPEED 0x100c
#define ADDRESS_FOR_AGV_CURRENT_ROTATE_POSITION 0x100d

#define ADDRESS_FOR_AGV_ENABLE 0x100e
#define ADDRESS_FOR_AGV_MODE 0x100f
#define ADDRESS_FOR_AGV_OD_ENABLE 0x1010
#define ADDRESS_FOR_AGV_BATTERY 0x1011
#define ADDRESS_FOR_AGV_OB_SENSOR 0x1012

#define ADDRESS_FOR_AGV_MIN (0x1001)
#define ADDRESS_FOR_AGV_MAX (0x1012)


#define ADDRESS_FOR_LA_ENABLE 0x2001
#define ADDRESS_FOR_LA_STATUS 0x2002
#define ADDRESS_FOR_LA_SPEED 0x2003
#define ADDRESS_FOR_LA_POSITION_TARGET 0x2004
#define ADDRESS_FOR_LA_POSITION_CURRENT 0x2005
#define ADDRESS_FOR_LA_SET_ZERO 0x2006

#define ADDRESS_FOR_LA_MIN  (0x2001)
#define ADDRESS_FOR_LA_MAX  (0x2006)

};

#endif // AGVCONTROL_H
