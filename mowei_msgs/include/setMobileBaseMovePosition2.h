// Generated by gencpp from file mowei_msgs/setMobileBaseMovePosition2.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2_H
#define MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2_H

#include <ros/service_traits.h>


#include <mowei_msgs/setMobileBaseMovePosition2Request.h>
#include <mowei_msgs/setMobileBaseMovePosition2Response.h>


namespace mowei_msgs
{

struct setMobileBaseMovePosition2
{

typedef setMobileBaseMovePosition2Request Request;
typedef setMobileBaseMovePosition2Response Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct setMobileBaseMovePosition2
} // namespace mowei_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2 > {
  static const char* value()
  {
    return "ea119264410580196e5a3865d7790d35";
  }

  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2&) { return value(); }
};

template<>
struct DataType< ::mowei_msgs::setMobileBaseMovePosition2 > {
  static const char* value()
  {
    return "mowei_msgs/setMobileBaseMovePosition2";
  }

  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2&) { return value(); }
};


// service_traits::MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2Request> should match 
// service_traits::MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2 > 
template<>
struct MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2Request>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2 >::value();
  }
  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Request&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::setMobileBaseMovePosition2Request> should match 
// service_traits::DataType< ::mowei_msgs::setMobileBaseMovePosition2 > 
template<>
struct DataType< ::mowei_msgs::setMobileBaseMovePosition2Request>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::setMobileBaseMovePosition2 >::value();
  }
  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Request&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2Response> should match 
// service_traits::MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2 > 
template<>
struct MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2Response>
{
  static const char* value()
  {
    return MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2 >::value();
  }
  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Response&)
  {
    return value();
  }
};

// service_traits::DataType< ::mowei_msgs::setMobileBaseMovePosition2Response> should match 
// service_traits::DataType< ::mowei_msgs::setMobileBaseMovePosition2 > 
template<>
struct DataType< ::mowei_msgs::setMobileBaseMovePosition2Response>
{
  static const char* value()
  {
    return DataType< ::mowei_msgs::setMobileBaseMovePosition2 >::value();
  }
  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Response&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2_H
