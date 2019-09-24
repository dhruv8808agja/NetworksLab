#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

#include "ns3/packet-sink.h"
using namespace ns3;

//NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");

int 
main (int argc, char *argv[])
{
	CommandLine cmd;
	cmd.Parse (argc, argv);

	NodeContainer p2pNodes;
	p2pNodes.Create (2);

        LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  	NodeContainer csmaLeftNodes;
  	csmaLeftNodes.Add (p2pNodes.Get (0));
  	csmaLeftNodes.Create (2);

	NodeContainer csmaRightNodes;
  	csmaRightNodes.Add (p2pNodes.Get (1));
  	csmaRightNodes.Create (3);

	PointToPointHelper pointToPoint;
 	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
 	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer p2pDevices;
 	p2pDevices = pointToPoint.Install (p2pNodes);

	CsmaHelper csma;
  	csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  	csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (65600000)));

  	NetDeviceContainer csmaLeftDevices;
	NetDeviceContainer csmaRightDevices;
  	csmaLeftDevices = csma.Install (csmaLeftNodes);	
  	csmaRightDevices = csma.Install (csmaRightNodes);

	InternetStackHelper stack;
  	stack.Install (csmaRightNodes);
  	stack.Install (csmaLeftNodes);

	Ipv4AddressHelper address;
  	address.SetBase ("10.1.1.0", "255.255.255.0");
  	Ipv4InterfaceContainer p2pInterfaces;
  	p2pInterfaces = address.Assign (p2pDevices);

  	address.SetBase ("10.1.2.0", "255.255.255.0");
  	Ipv4InterfaceContainer csmaLeftInterfaces;
 	Ipv4InterfaceContainer csmaRightInterfaces;
  	csmaLeftInterfaces = address.Assign (csmaLeftDevices);
	address.SetBase ("10.1.3.0", "255.255.255.0");
  	csmaRightInterfaces = address.Assign (csmaRightDevices);

	
	UdpEchoServerHelper echoServer (8008);
  	ApplicationContainer serverApps = echoServer.Install (csmaLeftNodes.Get(1));
  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

	UdpEchoClientHelper echoClient (csmaLeftInterfaces.GetAddress (1), 8008);
  	echoClient.SetAttribute ("MaxPackets", UintegerValue (2));
 	echoClient.SetAttribute ("Interval", TimeValue (Seconds (2.0)));
  	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  	ApplicationContainer clientApps = echoClient.Install (csmaRightNodes.Get (2));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));
	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//	B U L K send & P A C K E T  S I N K 
//send at right 3
  uint16_t port = 8080;  // well-known echo port number
  uint32_t maxBytes = 0;

  BulkSendHelper source ("ns3::TcpSocketFactory",
                         InetSocketAddress (csmaLeftInterfaces.GetAddress (2), port));
  // Set the amount of data to send in bytes.  Zero is unlimited.
  source.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  ApplicationContainer sourceApps = source.Install (csmaRightNodes.Get(3));
  sourceApps.Start (Seconds (1.0));
  sourceApps.Stop (Seconds (10.0));

//
// Create a PacketSinkApplication and install it on node 1
// psink at left 2
  PacketSinkHelper sink ("ns3::TcpSocketFactory",
                         InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApps = sink.Install (csmaLeftNodes.Get(2));
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (Seconds (10.0));

//

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	

  	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  	pointToPoint.EnablePcapAll ("second");
  	csma.EnablePcap ("second", csmaLeftDevices.Get (1), true);

  	Simulator::Run();
  	Simulator::Destroy ();
  	return 0;
}
