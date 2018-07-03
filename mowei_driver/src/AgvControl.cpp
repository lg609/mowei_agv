#include "mowei_driver/AgvControl.h"

AgvControl::AgvControl()
{
    mAgvDeviceId=DEFAULT_AGV_DEVICE_ID; //set defalut id


    for (int i=0;i<SIZE_OF_AGV_MOBILE_BASE_STATUS;i++)
    {
        AgvMobileBaseStatus[i]=0;
    }

    for (int i=0;i<SIZE_OF_AGV_LINEAR_ACTUATOR_STATUS;i++)
    {
        AgvLinearActuatorStatus[i]=0;
    }
}

AgvControl::~AgvControl()
{
}

 // CRC high table
const unsigned char chCRCHTalbe[] =
{
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40
};

// CRC low table
const unsigned char chCRCLTalbe[] =
{
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
0x41, 0x81, 0x80, 0x40
};

//Function: CRC16
//Description: calculate the CRC16 checksum
//param pchMsg buffer want to calculate
//param wDataLen buffert length
//return: CRC16 checksum
short AgvControl::CRC16(const unsigned char* pchMsg, int wDataLen)
{
    unsigned char chCRCHi = 0xFF;
    unsigned char chCRCLo = 0xFF;
    short wIndex;

    while (wDataLen--)
    {
        //calcaulate
        wIndex = chCRCLo ^ *pchMsg++ ;
        chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex];
        chCRCHi = chCRCLTalbe[wIndex] ;
    }

    return ((chCRCHi << 8) | chCRCLo) ;
}

//Function: ProcessReceivedAgvMessage
//Description: process received communication buffer,
//param sendbuf last send communication buffer
//param sendlength last send communication buffer length
//param receivedbuf received communication buffer
//param receivedlength received commnication buffer length
//return MsgRevState
int AgvControl::ProcessReceivedAgvMessage(unsigned char* sendbuf,int sendlength,unsigned char* receivedbuf,int receivedlength)
{
    int ret=0;
    if ((receivedlength==0)||(sendlength==0))
    {
        ret=MsgRevState::msgEmpty;
    }
    else
    {
        int i;
        for (i=0;i<receivedlength;i++)
        {
            AgvDataReceived[i]=receivedbuf[i];
            if (i>=AGV_CONTROL_DATA_MAX_SIZE-1)
            {
                i=AGV_CONTROL_DATA_MAX_SIZE-1;
                break;
            }
        }
        AgvDataReceivedLength=i;
        if ((AgvDataReceivedLength<4)||(AgvDataReceivedLength>60))
        {
            ret=MsgRevState::msgLengthError;
        }
        else
        {
            if (receivedbuf[0]==mAgvDeviceId)
            {
                short crc=CRC16(receivedbuf,receivedlength-2);
                short rev_crc;
                rev_crc=receivedbuf[receivedlength-1];
                rev_crc=rev_crc<<8;
                rev_crc+=receivedbuf[receivedlength-2];
                if (rev_crc!=crc)
                {
                   ret=MsgRevState::msgCrcError;
                }
                else
                {
                    switch (receivedbuf[1]) {
                    case 0x03:
                        short add_start;
                        int len,i,j;
                        add_start=(short)sendbuf[2];
                        add_start=add_start<<8;
                        add_start+=(short)sendbuf[3];
                        len=sendbuf[5];

                        if ((add_start>=ADDRESS_FOR_AGV_MIN)&&(add_start<=ADDRESS_FOR_AGV_MAX))
                        {
                            if ((add_start+len)<=ADDRESS_FOR_AGV_MAX+1)
                            {
                                //save new status
                                j=add_start-ADDRESS_FOR_AGV_MIN;
                                for (i=0;i<len;i++)
                                {
                                    AgvMobileBaseStatus[j+i]=(short)receivedbuf[2*i+3];
                                    AgvMobileBaseStatus[j+i]=AgvMobileBaseStatus[j+i]<<8;
                                    AgvMobileBaseStatus[j+i]+=(short)receivedbuf[2*i+4];
                                }
                                ret=MsgRevState::msgOK;
                            }
                            else
                            {
                                ret=MsgRevState::msgAddressError;
                            }
                        }
                        else if ((add_start>=ADDRESS_FOR_LA_MIN)&&(add_start<=ADDRESS_FOR_LA_MAX))
                        {
                            if ((add_start+len)<=ADDRESS_FOR_LA_MAX+1)
                            {
                                //save new status
                                j=add_start-ADDRESS_FOR_LA_MIN;
                                for (i=0;i<len;i++)
                                {
                                    AgvLinearActuatorStatus[j+i]=(short)receivedbuf[2*i+3];
                                    AgvLinearActuatorStatus[j+i]=AgvLinearActuatorStatus[j+i]<<8;
                                    AgvLinearActuatorStatus[j+i]+=(short)receivedbuf[2*i+4];
                                }
                                ret=MsgRevState::msgOK;
                            }
                            else
                            {
                                ret=MsgRevState::msgAddressError;
                            }
                        }
                        else
                        {
                            ret=MsgRevState::msgAddressError;
                        }
                        break;
                    case 0x06:
                        ret=MsgRevState::msgOK;
                        break;
                    case 0x10:
                        ret=MsgRevState::msgOK;
                        break;
                    case 0x04:
                        ret=MsgRevState::msgOK;
                        break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                ret=MsgRevState::msgIdError;
            }
        }
    }
    return ret;
}

//Function: readAgvSingleRegister
//Description: request update one register
//param sendbuf message buffer will save in sendbuf
//param address register address to update
//return message buffer length
int AgvControl::readAgvSingleRegister(unsigned char *sendbuf, short address)
{
    int len;
    short crc;
    sendbuf[0]=mAgvDeviceId;
    sendbuf[1]=0x03;
    sendbuf[2]=address>>8;
    sendbuf[3]=address;
    sendbuf[4]=0x00;
    sendbuf[5]=0x01;
    crc=CRC16(sendbuf,6);
    sendbuf[6]=crc;
    sendbuf[7]=crc>>8;
    len=8;
    return len;
}

//Function: readAgvMultiRegisters
//Description: request update multi registers
//param sendbuf message buffer will save in sendbuf
//param address register start address to update
//param length length to update
//return message buffer length
int AgvControl::readAgvMultiRegisters(unsigned char *sendbuf,short address,short length)
{
    int len;
    short crc;
    sendbuf[0]=mAgvDeviceId;
    sendbuf[1]=0x03;
    sendbuf[2]=address>>8;
    sendbuf[3]=address;
    sendbuf[4]=length>>8;
    sendbuf[5]=length;
    crc=CRC16(sendbuf,6);
    sendbuf[6]=crc;
    sendbuf[7]=crc>>8;
    len=8;
    return len;
}

//Function: writeAgvSingleRegister
//Description: write single register
//param sendbuf message buffer will save in sendbuf
//param address register address to write
//param value value to write
//return message buffer length
int AgvControl::writeAgvSingleRegister(unsigned char *sendbuf, short address,short value)
{
    int len;
    short crc;
    sendbuf[0]=mAgvDeviceId;
    sendbuf[1]=0x06;
    sendbuf[2]=address>>8;
    sendbuf[3]=address;
    sendbuf[4]=value>>8;
    sendbuf[5]=value;
    crc=CRC16(sendbuf,6);
    sendbuf[6]=crc;
    sendbuf[7]=crc>>8;
    len=8;
    return len;
}

//Function: writeAgvMultiRegisters
//Description: write multi registers
//param sendbuf message buffer will save in sendbuf
//param address register start address to write
//param length length to write
//param write_buf buffer to write
//return message buffer length
int AgvControl::writeAgvMultiRegisters(unsigned char *sendbuf, short address,unsigned char length,unsigned char *write_buf)
{
    int len;
    short crc;
    int i;
    sendbuf[0]=mAgvDeviceId;
    sendbuf[1]=0x10;
    sendbuf[2]=address>>8;
    sendbuf[3]=address;
    sendbuf[4]=0;
    sendbuf[5]=length;
    sendbuf[6]=length*2;
    for(i=0;i<sendbuf[6];i++)
    {
        sendbuf[7+i]=write_buf[i];
    }
    crc=CRC16(sendbuf,6+sendbuf[6]);
    sendbuf[7+sendbuf[6]]=crc;
    sendbuf[8+sendbuf[6]]=crc>>8;
    len=9+sendbuf[6];
    return len;
}

//Function: getAgvRegisterByAddress
//Description: read agv status
//param address register start address to read
//return point of agv status
int *AgvControl::getAgvRegisterByAddress(short address)
{
    int *ret=nullptr;
    if ((address>=ADDRESS_FOR_AGV_MIN)||(address<=ADDRESS_FOR_AGV_MAX))
    {
        ret=&AgvMobileBaseStatus[address-ADDRESS_FOR_AGV_MIN];
    }
    else if ((address>=ADDRESS_FOR_LA_MIN)||(address<=ADDRESS_FOR_LA_MAX))
    {
        ret=&AgvLinearActuatorStatus[address-ADDRESS_FOR_LA_MIN];
    }
    return ret;
}

//***************************************************************
//linear actuator control function

//Function: wr_setLinearActuatorLock
//Description: get command for setLinearActuatorLock
//param sendbuf message buffer will save in sendbuf
//param flag 0,lock;1,unlock
//return message buffer length
int AgvControl::wr_setLinearActuatorLock(unsigned char *sendBuf,bool flag)
{
    int len;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x06;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_LA_ENABLE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_LA_ENABLE;
    sendBuf[4]=0x00;
    if (flag==true)
    {
        sendBuf[5]=0x01;
    }
    else
    {
        sendBuf[5]=0x00;
    }
    crc=CRC16(sendBuf,6);
    sendBuf[6]=crc;
    sendBuf[7]=crc>>8;
    len=8;
    return len;
}

//Function: wr_getLinearActuatorIsLock
//Description: get command for getLinearActuatorIsLock
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getLinearActuatorIsLock(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_LA_ENABLE);
}

//Function: rd_getLinearActuatorIsLock
//Description: get value of getLinearActuatorIsLock
//return 0,lock; 1,unlock
short AgvControl::rd_getLinearActuatorIsLock()
{
    return AgvLinearActuatorStatus[ADDRESS_FOR_LA_ENABLE-ADDRESS_FOR_LA_MIN];
}

//Function: wr_setLinearActuatorPos
//Description: get command for setLinearActuatorPos
//param sendbuf message buffer will save in sendbuf
//param speed linear actuator move speed, mm/s,0-500mm/s
//param pos linear actuator move target position, mm,0-1500mm
//return message buffer length
int AgvControl::wr_setLinearActuatorPos(unsigned char *sendBuf, short speed, short pos)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_LA_SPEED>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_LA_SPEED;
    sendBuf[4]=0x00;
    sendBuf[5]=0x02;
    sendBuf[6]=0x04;
    sendBuf[7]=pos>>8;
    sendBuf[8]=pos;
    sendBuf[9]=speed>>8;
    sendBuf[10]=speed;
    crc=CRC16(sendBuf,11);
    sendBuf[11]=crc;
    sendBuf[12]=crc>>8;
    ret=13;
    return ret;
}

//Function: wr_getLinearActuatorPos
//Description: get command for getLinearActuatorPos
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getLinearActuatorPos(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_LA_POSITION_CURRENT);
}

//Function: rd_getLinearActuatorPos
//Description: get value of getLinearActuatorPos
//return linear actuator current position, mm,0-1500mm
short AgvControl::rd_getLinearActuatorPos(void)
{
    return AgvLinearActuatorStatus[ADDRESS_FOR_LA_POSITION_CURRENT-ADDRESS_FOR_LA_MIN];
}

//Function: wr_getLinearActuatorStatus
//Description: get command for getLinearActuatorStatus
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getLinearActuatorStatus(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_LA_STATUS);
}

//Function: rd_getLinearActuatorPos
//Description: get value of getLinearActuatorPos
//return linear actuator current position, mm,0-1500mm
short AgvControl::rd_getLinearActuatorStatus(void)
{
    return AgvLinearActuatorStatus[ADDRESS_FOR_LA_STATUS-ADDRESS_FOR_LA_MIN];
}
//****************************************************************


//***************************************************************
//mobile base control function

//Function: wr_setMobileBaseLock
//Description: get command for setMobileBaseLock
//param sendbuf message buffer will save in sendbuf
//param flag 0,lock;1,unlock
//return message buffer length
int AgvControl::wr_setMobileBaseLock(unsigned char *sendBuf,bool flag)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x06;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_ENABLE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_ENABLE;
    sendBuf[4]=0x00;
    if (flag==true)
    {
        sendBuf[5]=0x01;
    }
    else
    {
        sendBuf[5]=0x00;
    }
    crc=CRC16(sendBuf,6);
    sendBuf[6]=crc;
    sendBuf[7]=crc>>8;
    ret=8;
    return ret;
}

//Function: wr_getMobileBaseIsLock
//Description: get command for getMobileBaseIsLock
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseIsLock(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_AGV_ENABLE);
}

//Function: rd_getMobileBaseIsLock
//Description: get value of getMobileBaseIsLock
//return 0,lock;1,unlock
short AgvControl::rd_getMobileBaseIsLock()
{
    return AgvMobileBaseStatus[ADDRESS_FOR_AGV_ENABLE-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_setMobileBaseODEnalbe
//Description: get command for setMobileBaseODEnalbe
//param sendbuf message buffer will save in sendbuf
//param flag 0,enable;1,disable
//return message buffer length
int AgvControl::wr_setMobileBaseODEnalbe(unsigned char *sendBuf,bool flag)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x06;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_OD_ENABLE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_OD_ENABLE;
    sendBuf[4]=0x00;
    if (flag==true)
    {
        sendBuf[5]=0x01;
    }
    else
    {
        sendBuf[5]=0x00;
    }
    crc=CRC16(sendBuf,6);
    sendBuf[6]=crc;
    sendBuf[7]=crc>>8;
    ret=8;
    return ret;
}

//Function: wr_getMobileBaseODIsEnalbe
//Description: get command for getMobileBaseODIsEnalbe
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseODIsEnalbe(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_AGV_OD_ENABLE);
}

//Function: rd_getMobileBaseODIsEnalbe
//Description: get value of getMobileBaseODIsEnalbe
//return 0,enable;1,disable
short AgvControl::rd_getMobileBaseODIsEnalbe()
{
    return AgvMobileBaseStatus[ADDRESS_FOR_AGV_OD_ENABLE-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_getMobileBaseBatteryCapacity
//Description: get command for getMobileBaseBatteryCapacity
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseBatteryCapacity(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_AGV_BATTERY);
}

//Function: rd_getMobileBaseBatteryCapacity
//Description: get value of getMobileBaseBatteryCapacity
//return battery capacity 1=0.1V, E.X.:495=49.5V
short AgvControl::rd_getMobileBaseBatteryCapacity()
{
    return AgvMobileBaseStatus[ADDRESS_FOR_AGV_BATTERY-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_setMobileBaseMoveMode
//Description: get command for setMobileBaseMoveMode
//param sendbuf message buffer will save in sendbuf
//param flag 0,speed mode;1,position mode
//return message buffer length
int AgvControl::wr_setMobileBaseMoveMode(unsigned char *sendBuf,bool flag)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x06;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_MODE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_MODE;
    sendBuf[4]=0x00;
    if (flag==true)
    {
        sendBuf[5]=0x01;
    }
    else
    {
        sendBuf[5]=0x00;
    }
    crc=CRC16(sendBuf,6);
    sendBuf[6]=crc;
    sendBuf[7]=crc>>8;
    ret=8;
    return ret;
}

//Function: wr_getMobileBaseMoveMode
//Description: get command for getMobileBaseMoveMode
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseMoveMode(unsigned char *sendBuf)
{
    return readAgvSingleRegister(sendBuf,ADDRESS_FOR_AGV_MODE);
}

//Function: rd_getMobileBaseMoveMode
//Description: get value of getMobileBaseMoveMode
//return 0,speed mode;1,position mode
short AgvControl::rd_getMobileBaseMoveMode()
{
    return AgvMobileBaseStatus[ADDRESS_FOR_AGV_MODE-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_setMobileBaseMoveForSpeed
//Description: get command for setMobileBaseMoveForSpeed, use in speed mode
//param sendbuf message buffer will save in sendbuf
//param speed_x x axis speed,mm/s 0-800mm/s
//param speed_y y axis speed,mm/s 0-800mm/s
//param speed_z z axis speed,0.1°/s -50-50°/s, E.X.:360=36°/s
//return message buffer length
int AgvControl::wr_setMobileBaseMoveForSpeed(unsigned char *sendBuf, int speed_x, int speed_y, short speed_z)
{
    int ret;
    short crc;
    short speed,dir;
    double temp;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_X>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_X;
    sendBuf[4]=0x00;
    sendBuf[5]=0x03;
    sendBuf[6]=0x06;

    //get speed
    speed=(short)sqrt(speed_x*speed_x+speed_y*speed_y);

    //get direction
    temp=atan2(speed_y,speed_x);
    if(temp<0)
    {
        //-pi~0 change to pi~2*pi
        temp=temp+M_PI+M_PI;
    }
    //pi to degress
    dir=(short)((temp*180)/M_PI);

    sendBuf[7]=speed>>8;
    sendBuf[8]=speed;
    sendBuf[9]=dir>>8;
    sendBuf[10]=dir;
    sendBuf[11]=speed_z>>8;
    sendBuf[12]=speed_z;

    crc=CRC16(sendBuf,13);
    sendBuf[13]=crc;
    sendBuf[14]=crc>>8;
    ret=15;
    return ret;
}

//Function: wr_getMobileBaseMoveForSpeed
//Description: get command for getMobileBaseMoveForSpeed
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseMoveForSpeed(unsigned char *sendBuf)
{
    //need modify
    return readAgvMultiRegisters(sendBuf,ADDRESS_FOR_AGV_CURRENT_SPEED,3);
}

//Function: rd_getMobileBaseMoveForSpeed
//Description: get value of getMobileBaseMoveForSpeed
//return
//data[0], current speed,
//data[1], current position,
//data[2], current direction,
int *AgvControl::rd_getMobileBaseMoveForSpeed()
{
    return &AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_SPEED-ADDRESS_FOR_AGV_MIN];
}

//Function: rd_getMobileBaseMoveCurrentSpeedAndPosition
//Description: get value of getMobileBaseMoveCurrentSpeedAndPosition
//return
//data[0], current x axis speed,
//data[1], current y axis speed,
//data[2], current x axis position,
//data[3], current y axis position,
int* AgvControl::rd_getMobileBaseMoveCurrentSpeedAndPosition()
{
    short speed,dir,pos;
    double temp;
    speed=AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_SPEED-ADDRESS_FOR_AGV_MIN];
    pos=AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_POSITION-ADDRESS_FOR_AGV_MIN];
    dir=AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_DIRECTION-ADDRESS_FOR_AGV_MIN];

    temp= (dir*M_PI)/180;
    AgvCurrentSpeedAndPositino[0]=speed*cos(temp);
    AgvCurrentSpeedAndPositino[1]=speed*sin(temp);
    AgvCurrentSpeedAndPositino[2]=pos*cos(temp);
    AgvCurrentSpeedAndPositino[3]=pos*sin(temp);

    return AgvCurrentSpeedAndPositino;
}

//Function: wr_setMobileBaseMovePosition1
//Description: get command for setMobileBaseMovePosition1
//param sendbuf message buffer will save in sendbuf
//param dis_x, x axis target move distence,mm,1=1mm
//param dis_y, y axis target move distence,mm,1=1mm
//param speed, move max speed,mm/s, 0-800mm/s
//return message buffer length
int AgvControl::wr_setMobileBaseMovePosition1(unsigned char *sendBuf, short dis_x, short dis_y, short speed)
{
    int ret;
    short crc;
    short dis,dir;
    double temp;

    dis= (short)(sqrt(dis_x*dis_x+dis_y*dis_y));
    //get direction
    temp=atan2(dis_y,dis_x);
    if(temp<0)
    {
        //-pi~0 change to pi~2*pi
        temp=temp+M_PI+M_PI;
    }
    //pi to degress
    dir=(short)((temp*180)/M_PI);

    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_POSITION_MOVE_DISTANCE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_POSITION_MOVE_DISTANCE;
    sendBuf[4]=0x00;
    sendBuf[5]=0x03;
    sendBuf[6]=0x06;

    sendBuf[7]=dis>>8;
    sendBuf[8]=dis;
    sendBuf[9]=speed>>8;
    sendBuf[10]=speed;
    sendBuf[11]=dir>>8;
    sendBuf[12]=dir;

    crc=CRC16(sendBuf,13);
    sendBuf[13]=crc;
    sendBuf[14]=crc>>8;
    ret=15;
    return ret;
}

//Function: wr_setMobileBaseMovePosition2
//Description: get command for setMobileBaseMovePosition2
//param sendbuf message buffer will save in sendbuf
//param dis, revolve degress 0.1°/s , E.X.:900=90°
//param speed, revolve speed,0.1°/s 50°/s, E.X.:360=36°/s
//return message buffer length
int AgvControl::wr_setMobileBaseMovePosition2(unsigned char *sendBuf, short dis, short speed)
{
    int ret;
    short crc;
    //short speed,dir,rev;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_POSITION_ROTATE_DISTANCE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_POSITION_ROTATE_DISTANCE;
    sendBuf[4]=0x00;
    sendBuf[5]=0x02;
    sendBuf[6]=0x04;

    sendBuf[7]=dis>>8;
    sendBuf[8]=dis;
    sendBuf[9]=speed>>8;
    sendBuf[10]=speed;

    crc=CRC16(sendBuf,11);
    sendBuf[11]=crc;
    sendBuf[12]=crc>>8;
    ret=13;
    return ret;
}

//Function: wr_getMobileBaseMoveForRevolve
//Description: get command for getMobileBaseMoveForRevolve
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseMoveForRevolve(unsigned char *sendBuf)
{
    return readAgvMultiRegisters(sendBuf,ADDRESS_FOR_AGV_CURRENT_ROTATE_POSITION,2);
}

//Function: rd_getMobileBaseMoveForRevolve
//Description: get value of getMobileBaseMoveForRevolve
//return
//data[0], current revolve speed,
//data[1], current revolve position,
int *AgvControl::rd_getMobileBaseMoveForRevolve()
{
    return &AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_ROTATE_POSITION-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_getMobileBaseMoveAll
//Description: get command for getMobileBaseMoveAll
//param sendbuf message buffer will save in sendbuf
//return message buffer length
int AgvControl::wr_getMobileBaseMoveAll(unsigned char *sendBuf)
{
    return readAgvMultiRegisters(sendBuf,ADDRESS_FOR_AGV_CURRENT_SPEED,5);
}

//Function: rd_getMobileBaseMoveAll
//Description: get value of getMobileBaseMoveAll
//return
//data[0], current speed,
//data[1], current position,
//data[2], current direction,
//data[3], current revolve speed,
//data[4], current revolve position,
int *AgvControl::rd_getMobileBaseMoveAll()
{
    return &AgvMobileBaseStatus[ADDRESS_FOR_AGV_CURRENT_SPEED-ADDRESS_FOR_AGV_MIN];
}

//Function: wr_setLinearActuatorZeroPosition
//Description: get command for setLinearActuatorZeroPosition, current position will change to 0 position
//param sendbuf message buffer will save in sendbuf
//return message buffer length
//谨慎使用！
int AgvControl::wr_setLinearActuatorZeroPosition(unsigned char *sendBuf)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x06;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_LA_SET_ZERO>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_LA_SET_ZERO;
    sendBuf[4]=0x00;
    sendBuf[5]=0x01;
    crc=CRC16(sendBuf,6);
    sendBuf[6]=crc;
    sendBuf[7]=crc>>8;
    ret=8;
    return ret;
}

//Function: wr_setMobileBaseMoveForSpeed
//Description: get command for setMobileBaseMoveForSpeed
//param sendbuf message buffer will save in sendbuf
//param speed ,mm/s 0-800mm/s
//param dir direction °,0-359°,1=1°
//param revolve revolve speed,0.1°/s -50-50°/s, E.X.:360=36°/s
//return message buffer length
int AgvControl::wr_setMobileBaseMoveForSDR(unsigned char *sendBuf,short speed,short dir,short revolve)
{
    int ret;
    short crc;
    //short speed,dir,rev;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_X>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_X;
    sendBuf[4]=0x00;
    sendBuf[5]=0x03;
    sendBuf[6]=0x06;
    sendBuf[7]=speed>>8;
    sendBuf[8]=speed;
    sendBuf[9]=dir>>8;
    sendBuf[10]=dir;
    sendBuf[11]=revolve>>8;
    sendBuf[12]=revolve;

    crc=CRC16(sendBuf,13);
    sendBuf[13]=crc;
    sendBuf[14]=crc>>8;
    ret=15;
    return ret;
}

//Function: wr_setMobileBaseMoveDSD
//Description: get command for setMobileBaseMoveDSD
//param sendbuf message buffer will save in sendbuf
//param distence, target distence to move,mm,1=1mm
//param speed, max speed,mm/s 0-800mm/s
//param dir, direction to move,0-359°,1=1°
//return message buffer length
int AgvControl::wr_setMobileBaseMoveForDSD(unsigned char *sendBuf, short distence, short speed, short dir)
{
    int ret;
    short crc;
    sendBuf[0]=mAgvDeviceId;
    sendBuf[1]=0x10;
    sendBuf[2]=(unsigned char)(ADDRESS_FOR_AGV_POSITION_MOVE_DISTANCE>>8);
    sendBuf[3]=(unsigned char)ADDRESS_FOR_AGV_POSITION_MOVE_DISTANCE;
    sendBuf[4]=0x00;
    sendBuf[5]=0x03;
    sendBuf[6]=0x06;

    sendBuf[7]=distence>>8;
    sendBuf[8]=distence;
    sendBuf[9]=speed>>8;
    sendBuf[10]=speed;
    sendBuf[11]=dir>>8;
    sendBuf[12]=dir;

    crc=CRC16(sendBuf,13);
    sendBuf[13]=crc;
    sendBuf[14]=crc>>8;
    ret=15;
    return ret;
}

