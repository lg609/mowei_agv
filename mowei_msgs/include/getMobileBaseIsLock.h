// Generated by gencpp from file mowei_msgs/getMobileBaseIsLock.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETMOBILEBASEISLOCK_H
#define MOWEI_MSGS_MESSAGE_GETMOBILEBASEISLOCK_H

#include <ros/service_traits.h>


#include <mowei_msgs/getMobileBaseIsLockRequest.h>
#include <mowei_msgs/getMobileBaseIsLockResponse.h>


namespace mowei_msgs
{

struct getMobileBaseIsLock
{

typedef getMobileBaseIsLockRequest Request;
typedef getMobileBaseIsLockResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getMobileBaseIsLock
} // namespace mowei_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseIsLock > {
  static const char* value()
  {
    return "0b13460cb14006d3852674b4c614f25f";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseIsLock&) { return value(); }
};

template<>
struct DataType< ::mowei_msgs::getMobileBaseIsLock > {
  static const char* value()
  {
    return "mowei_msgs/getMobileBaseIsLock";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseIsLock&) { return value(); }
};


// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseIsLockRequest> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseIsLock > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseIsLockRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseIsLock >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseIsLockRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseIsLockRequest> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseIsLock > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseIsLockRequest>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseIsLock >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseIsLockRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseIsLockResponse> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseIsLock > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseIsLockResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseIsLock >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseIsLockResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseIsLockResponse> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseIsLock > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseIsLockResponse>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseIsLock >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseIsLockResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETMOBILEBASEISLOCK_H
