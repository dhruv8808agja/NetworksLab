#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("BulkSendApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("500Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);
  
  uint32_t tcp_adu_size = 1000;
//>>>>>>>>>>>>>>>>>



  //std::cout<<TcpOptionWinScale::GetSerializedSize()<<std::endl; 	
//>>>>>>>>>>>>>>>>
  std::cout<<"Enter Segment size of TCP in Bytes\n";
  std::cin>>tcp_adu_size;

  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcp_adu_size));

  InternetStackHelper stack;
  stack.Install (nodes.Get(0));
//measured in Kb
  uint32_t recbuff=1000;
  std::cout<<"Enter Receiver buffer size in Kb\n";
  std::cin>>recbuff;
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (recbuff));

  std::string transport_prot = "ns3::TcpWestwood";
  TypeId tcpTid;
  NS_ABORT_MSG_UNLESS (TypeId::LookupByNameFailSafe (transport_prot, &tcpTid), "TypeId " << transport_prot << " not found");
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (transport_prot)));
 
  std::cout<<"Do you want to use window Scalling?  1-true  0-false"<<std::endl; 
  int ikk;
  std::cin>>ikk;
	if(ikk==0)
 		Config::SetDefault ("ns3::TcpSocketBase::WindowScaling", BooleanValue (false));
  InternetStackHelper stack1;
  stack1.Install (nodes.Get(1));

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer i = address.Assign (devices);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   Application Installation

  uint16_t port = 9;


  BulkSendHelper source ("ns3::TcpSocketFactory",
                         InetSocketAddress (i.GetAddress (1), port));
  ApplicationContainer sourceApps = source.Install (nodes.Get (0));
  sourceApps.Start (Seconds (1.0));
  sourceApps.Stop (Seconds (10.0));

  PacketSinkHelper sink ("ns3::TcpSocketFactory",
                         InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApps = sink.Install (nodes.Get (1));
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (Seconds (10.0));
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      AsciiTraceHelper ascii;
      pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("week4First.tr"));
      pointToPoint.EnablePcapAll ("Week4First", true);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
