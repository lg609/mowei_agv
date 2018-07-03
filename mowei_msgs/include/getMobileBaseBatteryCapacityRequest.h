// Generated by gencpp from file mowei_msgs/getMobileBaseBatteryCapacityRequest.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITYREQUEST_H
#define MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITYREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mowei_msgs
{
template <class ContainerAllocator>
struct getMobileBaseBatteryCapacityRequest_
{
  typedef getMobileBaseBatteryCapacityRequest_<ContainerAllocator> Type;

  getMobileBaseBatteryCapacityRequest_()
    {
    }
  getMobileBaseBatteryCapacityRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }






  typedef boost::shared_ptr< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> const> ConstPtr;

}; // struct getMobileBaseBatteryCapacityRequest_

typedef ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<std::allocator<void> > getMobileBaseBatteryCapacityRequest;

typedef boost::shared_ptr< ::mowei_msgs::getMobileBaseBatteryCapacityRequest > getMobileBaseBatteryCapacityRequestPtr;
typedef boost::shared_ptr< ::mowei_msgs::getMobileBaseBatteryCapacityRequest const> getMobileBaseBatteryCapacityRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mowei_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mowei_msgs/getMobileBaseBatteryCapacityRequest";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
";
  }

  static const char* value(const ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct getMobileBaseBatteryCapacityRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::mowei_msgs::getMobileBaseBatteryCapacityRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETMOBILEBASEBATTERYCAPACITYREQUEST_H
