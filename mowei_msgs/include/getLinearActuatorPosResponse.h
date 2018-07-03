// Generated by gencpp from file mowei_msgs/getLinearActuatorPosResponse.msg
// DO NOT EDIT!


#ifndef MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOSRESPONSE_H
#define MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOSRESPONSE_H


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
struct getLinearActuatorPosResponse_
{
  typedef getLinearActuatorPosResponse_<ContainerAllocator> Type;

  getLinearActuatorPosResponse_()
    : pos(0)  {
    }
  getLinearActuatorPosResponse_(const ContainerAllocator& _alloc)
    : pos(0)  {
  (void)_alloc;
    }



   typedef int8_t _pos_type;
  _pos_type pos;




  typedef boost::shared_ptr< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> const> ConstPtr;

}; // struct getLinearActuatorPosResponse_

typedef ::mowei_msgs::getLinearActuatorPosResponse_<std::allocator<void> > getLinearActuatorPosResponse;

typedef boost::shared_ptr< ::mowei_msgs::getLinearActuatorPosResponse > getLinearActuatorPosResponsePtr;
typedef boost::shared_ptr< ::mowei_msgs::getLinearActuatorPosResponse const> getLinearActuatorPosResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "82b076b0db1717b26c92c819d52e9d17";
  }

  static const char* value(const ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x82b076b0db1717b2ULL;
  static const uint64_t static_value2 = 0x6c92c819d52e9d17ULL;
};

template<class ContainerAllocator>
struct DataType< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mowei_msgs/getLinearActuatorPosResponse";
  }

  static const char* value(const ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 pos\n\
\n\
";
  }

  static const char* value(const ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pos);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct getLinearActuatorPosResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mowei_msgs::getLinearActuatorPosResponse_<ContainerAllocator>& v)
  {
    s << indent << "pos: ";
    Printer<int8_t>::stream(s, indent + "  ", v.pos);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOWEI_MSGS_MESSAGE_GETLINEARACTUATORPOSRESPONSE_H