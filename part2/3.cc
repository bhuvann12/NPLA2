#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main(int argc, char *argv[]) {
  // Create nodes
  NodeContainer nodes;
  nodes.Create(2);

  // Create CSMA helper
  CsmaHelper csma;
  csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
  csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

  // Install CSMA devices
  NetDeviceContainer devices = csma.Install(nodes);

  // Install internet stack on nodes
  InternetStackHelper stack;
  stack.Install(nodes);

  // Assign IP addresses to devices
  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign(devices);

  // Create server application
  UdpEchoServerHelper serverHelper(9);
  ApplicationContainer serverApp = serverHelper.Install(nodes.Get(1));
  serverApp.Start(Seconds(1.0));
  serverApp.Stop(Seconds(10.0));

  // Create client application
  UdpEchoClientHelper clientHelper(interfaces.GetAddress(1), 9);
  clientHelper.SetAttribute("MaxPackets", UintegerValue(5));
  clientHelper.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  clientHelper.SetAttribute("PacketSize", UintegerValue(1024));

  ApplicationContainer clientApp = clientHelper.Install(nodes.Get(0));
  clientApp.Start(Seconds(2.0));
  clientApp.Stop(Seconds(10.0));

  // Enable pcap tracing
  csma.EnablePcapAll("csma");

  // Create animation interface
  AnimationInterface anim("csma-animation.xml");

  // Run simulation
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
