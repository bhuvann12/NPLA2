#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main (int argc, char *argv[])
{
  uint32_t maxBytes = 0;

  // Create two nodes
  NodeContainer nodes;
  nodes.Create (2);

  // Configure the point-to-point link
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("500Kbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("5ms"));

  // Install devices on the nodes
  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  // Install the internet stack on the nodes
  InternetStackHelper internet;
  internet.Install (nodes);

  // Assign IP addresses to the devices
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);

  uint16_t port = 9;  // well-known echo port number

  // Create a BulkSendHelper for sending data
  BulkSendHelper source ("ns3::TcpSocketFactory", InetSocketAddress (i.GetAddress (1), port));
  source.SetAttribute ("MaxBytes", UintegerValue (maxBytes));

  // Install the BulkSend application on the first node
  ApplicationContainer sourceApps = source.Install (nodes.Get (0));
  sourceApps.Start (Seconds (0.0));
  sourceApps.Stop (Seconds (10.0));

  // Create a PacketSinkHelper for receiving data
  PacketSinkHelper sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));

  // Install the PacketSink application on the second node
  ApplicationContainer sinkApps = sink.Install (nodes.Get (1));
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (Seconds (10.0));

  // Stop the simulation at 10 seconds
  Simulator::Stop (Seconds (10.0));

  // Create an animation interface for visualization
  AnimationInterface anim ("fourth.xml");
  anim.EnablePacketMetadata(true);

  // Run the simulation
  Simulator::Run ();

  // Clean up and destroy the simulation environment
  Simulator::Destroy ();

  return 0;
}
