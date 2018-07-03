// Generated by gencpp from file mowei_msgs/getMobileBaseBatteryCapacity.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITY_H
#define MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITY_H

#include <ros/service_traits.h>


#include <mowei_msgs/getMobileBaseBatteryCapacityRequest.h>
#include <mowei_msgs/getMobileBaseBatteryCapacityResponse.h>


namespace mowei_msgs
{

struct getMobileBaseBatteryCapacity
{

typedef getMobileBaseBatteryCapacityRequest Request;
typedef getMobileBaseBatteryCapacityResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getMobileBaseBatteryCapacity
} // namespace mowei_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacity > {
  static const char* value()
  {
    return "facd9d25e71b5e79fad5e0fc8b8aab8e";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacity&) { return value(); }
};

template<>
struct DataType< ::mowei_msgs::getMobileBaseBatteryCapacity > {
  static const char* value()
  {
    return "mowei_msgs/getMobileBaseBatteryCapacity";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacity&) { return value(); }
};


// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacityRequest> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacity > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacityRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacity >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseBatteryCapacityRequest> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseBatteryCapacity > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseBatteryCapacityRequest>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseBatteryCapacity >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacityResponse> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacity > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacityResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacity >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseBatteryCapacityResponse> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseBatteryCapacity > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseBatteryCapacityResponse>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseBatteryCapacity >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITY_H