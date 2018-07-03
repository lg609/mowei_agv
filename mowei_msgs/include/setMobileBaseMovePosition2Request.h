// Generated by gencpp from file mowei_msgs/setMobileBaseMovePosition2Request.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2REQUEST_H
#define MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2REQUEST_H


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
struct setMobileBaseMovePosition2Request_
{
  typedef setMobileBaseMovePosition2Request_<ContainerAllocator> Type;

  setMobileBaseMovePosition2Request_()
    : angle(0)
    , velocity(0)  {
    }
  setMobileBaseMovePosition2Request_(const ContainerAllocator& _alloc)
    : angle(0)
    , velocity(0)  {
  (void)_alloc;
    }



   typedef int8_t _angle_type;
  _angle_type angle;

   typedef int8_t _velocity_type;
  _velocity_type velocity;




  typedef boost::shared_ptr< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> const> ConstPtr;

}; // struct setMobileBaseMovePosition2Request_

typedef ::mowei_msgs::setMobileBaseMovePosition2Request_<std::allocator<void> > setMobileBaseMovePosition2Request;

typedef boost::shared_ptr< ::mowei_msgs::setMobileBaseMovePosition2Request > setMobileBaseMovePosition2RequestPtr;
typedef boost::shared_ptr< ::mowei_msgs::setMobileBaseMovePosition2Request const> setMobileBaseMovePosition2RequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "93b271bb249a52a9eb6cc3958b2a9dc4";
  }

  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x93b271bb249a52a9ULL;
  static const uint64_t static_value2 = 0xeb6cc3958b2a9dc4ULL;
};

template<class ContainerAllocator>
struct DataType< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mowei_msgs/setMobileBaseMovePosition2Request";
  }

  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 angle\n\
int8 velocity\n\
";
  }

  static const char* value(const ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.angle);
      stream.next(m.velocity);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct setMobileBaseMovePosition2Request_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mowei_msgs::setMobileBaseMovePosition2Request_<ContainerAllocator>& v)
  {
    s << indent << "angle: ";
    Printer<int8_t>::stream(s, indent + "  ", v.angle);
    s << indent << "velocity: ";
    Printer<int8_t>::stream(s, indent + "  ", v.velocity);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_SETMOBILEBASEMOVEPOSITION2REQUEST_H