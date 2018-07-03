// Generated by gencpp from file mowei_msgs/getLinearActuatorPos.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOS_H
#define MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOS_H

#include <ros/service_traits.h>


#include <mowei_msgs/getLinearActuatorPosRequest.h>
#include <mowei_msgs/getLinearActuatorPosResponse.h>


namespace mowei_msgs
{

struct getLinearActuatorPos
{

typedef getLinearActuatorPosRequest Request;
typedef getLinearActuatorPosResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getLinearActuatorPos
} // namespace mowei_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mowei_msgs::getLinearActuatorPos > {
  static const char* value()
  {
    return "82b076b0db1717b26c92c819d52e9d17";
  }

  static const char* value(const ::mowei_msgs::getLinearActuatorPos&) { return value(); }
};

template<>
struct DataType< ::mowei_msgs::getLinearActuatorPos > {
  static const char* value()
  {
    return "mowei_msgs/getLinearActuatorPos";
  }

  static const char* value(const ::mowei_msgs::getLinearActuatorPos&) { return value(); }
};


// service_traits::MD5Sum< ::mowei_msgs::getLinearActuatorPosRequest> should match 
// service_traits::MD5Sum< ::mowei_msgs::getLinearActuatorPos > 
template<>
struct MD5Sum< ::mowei_msgs::getLinearActuatorPosRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getLinearActuatorPos >::value();
  }
  static const char* value(const ::mowei_msgs::getLinearActuatorPosRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getLinearActuatorPosRequest> should match 
// service_traits::DataType< ::mowei_msgs::getLinearActuatorPos > 
template<>
struct DataType< ::mowei_msgs::getLinearActuatorPosRequest>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getLinearActuatorPos >::value();
  }
  static const char* value(const ::mowei_msgs::getLinearActuatorPosRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mowei_msgs::getLinearActuatorPosResponse> should match 
// service_traits::MD5Sum< ::mowei_msgs::getLinearActuatorPos > 
template<>
struct MD5Sum< ::mowei_msgs::getLinearActuatorPosResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getLinearActuatorPos >::value();
  }
  static const char* value(const ::mowei_msgs::getLinearActuatorPosResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getLinearActuatorPosResponse> should match 
// service_traits::DataType< ::mowei_msgs::getLinearActuatorPos > 
template<>
struct DataType< ::mowei_msgs::getLinearActuatorPosResponse>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getLinearActuatorPos >::value();
  }
  static const char* value(const ::mowei_msgs::getLinearActuatorPosResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOS_H
