// Generated by gencpp from file mowei_msgs/getMobileBaseOcIsEnable.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETMOBILEBASEOCISENABLE_H
#define MOWEI_MSGS_MESSAGE_GETMOBILEBASEOCISENABLE_H

#include <ros/service_traits.h>


#include <mowei_msgs/getMobileBaseOcIsEnableRequest.h>
#include <mowei_msgs/getMobileBaseOcIsEnableResponse.h>


namespace mowei_msgs
{

struct getMobileBaseOcIsEnable
{

typedef getMobileBaseOcIsEnableRequest Request;
typedef getMobileBaseOcIsEnableResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getMobileBaseOcIsEnable
} // namespace mowei_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnable > {
  static const char* value()
  {
    return "a6443b0eeced033f2bdf37f5297439af";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnable&) { return value(); }
};

template<>
struct DataType< ::mowei_msgs::getMobileBaseOcIsEnable > {
  static const char* value()
  {
    return "mowei_msgs/getMobileBaseOcIsEnable";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnable&) { return value(); }
};


// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnableRequest> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnable > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnableRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnable >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnableRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseOcIsEnableRequest> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseOcIsEnable > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseOcIsEnableRequest>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseOcIsEnable >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnableRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnableResponse> should match 
// service_traits::MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnable > 
template<>
struct MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnableResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::getMobileBaseOcIsEnable >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnableResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::getMobileBaseOcIsEnableResponse> should match 
// service_traits::DataType< ::mowei_msgs::getMobileBaseOcIsEnable > 
template<>
struct DataType< ::mowei_msgs::getMobileBaseOcIsEnableResponse>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::getMobileBaseOcIsEnable >::value();
  }
  static const char* value(const ::mowei_msgs::getMobileBaseOcIsEnableResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETMOBILEBASEOCISENABLE_H
