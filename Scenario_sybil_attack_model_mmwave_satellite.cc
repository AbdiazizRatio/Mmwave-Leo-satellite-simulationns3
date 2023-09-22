#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/internet-module.h"
#include "ns3/mmwave-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
 #include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include "ns3/mmwave-point-to-point-epc-helper.h"
#include "/home/abdiasis/final_implementation_mmwave_leo/ns-allinone-3.29/ns-3.29/contrib/satellite/model/satellite-mobility-model.h"
#include "/home/abdiasis/final_implementation_mmwave_leo/ns-allinone-3.29/ns-3.29/contrib/satellite/model/satellite-position-allocator.h"
#include "ns3/singleton.h"
#include "/home/abdiasis/final_implementation_mmwave_leo/ns-allinone-3.29/ns-3.29/contrib/satellite/utils/satellite-env-variables.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/netanim-module.h"
#include <vector>
#include "ns3/flow-monitor-module.h"
#include <cassert>
#include "ns3/gnuplot.h"
#include "ns3/ipv6-static-routing-helper.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/mmwave-helper.h"
#include "ns3/mpls-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/te-server.h"
#include "ns3/mac-gplot.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <sstream>  
#include <bits/stdc++.h>
#include <stdio.h>
#include <time.h>
using namespace ns3;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("Scenario_sybil_attack_model_mmwave_satellite");
AnimationInterface *pAnim;
double ds=1000.0;
uint32_t packetSize = 1024; 
uint32_t numPackets = 100; 
uint32_t SybilThreshold = 1000;      
double interval = 1.0; 
double rssi = 5.0; 
Time interPacketInterval = Seconds (interval);
void ReceivePacket (Ptr<Socket> socket){
while (socket->Recv ()){
NS_LOG_UNCOND ("Packet Recived...");}}
static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,uint32_t pktCount, Time pktInterval ){
if (pktCount > 0){
socket->Send (Create<Packet> (pktSize));
Simulator::Schedule (pktInterval, &GenerateTraffic,socket, pktSize,pktCount-1, pktInterval);}
else{socket->Close ();}}
void PktTrans1(NodeContainer c, NodeContainer d){
std::cout<<"\n\n Next, perform the routing for the remote host [eNodeB]; the Sybil nodes might continuously transmit jamming signals to disrupt the secure communication or use various eavesdropping techniques to intercept messages of mm-wave communication. \n\n";
std::random_device rd;  
std::mt19937 gen(rd());
std::uniform_int_distribution<int> intDistribution(1, 100);
int remote_host = intDistribution(gen);
if (packetSize > SybilThreshold) {
std::cout<<"Transmited jamming signal - " << remote_host << " Packet size: " << packetSize << " bytes"<<"\n\n";
std::cout<<"Received packet with RSSI: " << rssi << " dBm"" bytes"<<"\n\n";
}
for( uint32_t i=0;i<c.GetN ();i++){
TypeId tid1 = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink1 = Socket::CreateSocket (d.Get (0), tid1);
InetSocketAddress local1 = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink1->Bind (local1);
recvSink1->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (i), tid1);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}}
void PktTrans2(NodeContainer c, NodeContainer d){
std::cout<<"\n\n The packets as training and testing sets. Train the packets using RNN model. \n\n";
std::string command = "RNN.py";
RNN obj;
obj.Training(numPackets,packetSize);
for(  uint32_t i=0;i<c.GetN ();i++){
TypeId tid1 = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink1 = Socket::CreateSocket (d.Get (0), tid1);
InetSocketAddress local1 = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink1->Bind (local1);
recvSink1->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (i), tid1);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}}
void PktTrans3(NodeContainer c, NodeContainer d){
for(  uint32_t i=1;i<c.GetN ();i++){
TypeId tid1 = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink1 = Socket::CreateSocket (d.Get (0), tid1);
InetSocketAddress local1 = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSink1->Bind (local1);
recvSink1->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (i), tid1);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}
std::cout<<" \n";}
int main (int argc, char *argv[]){
std::string phyMode ("DsssRate50Mbps");
double distance = 600;  
uint32_t revNode = 0;
int numSatellites=200; 
uint32_t sourceNode = numSatellites-1;
int nodeSpeed = 25; 
int nodePause = 0; 
double simTime = 2.0;
bool enableFlowMonitor = false;
CommandLine cmd;
double simtime=300.0;
cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
cmd.AddValue ("distance", "distance (m)", distance);
cmd.AddValue("simTime", "Total duration of the simulation [s])", simTime);
cmd.AddValue ("packetSize", "size of application packet sent", packetSize);
cmd.AddValue ("numPackets", "number of packets generated", numPackets);
cmd.AddValue ("interval", "interval (seconds) between packets", interval);
cmd.AddValue ("numSatellites", "number of nodes", numSatellites);
cmd.AddValue ("revNode", "Receiver node number", revNode);
cmd.AddValue ("sourceNode", "Sender node number", sourceNode);
cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
cmd.Parse (argc, argv); 
NodeContainer Leo_Satellite_Nodes;
NodeContainer eNodeB;
std::cout<<"\n\n A Network, It consists of "<< numSatellites << "- leo Satellite nodes and 5- eNodeB. \n\n";
Leo_Satellite_Nodes.Create (numSatellites);
eNodeB.Create (5);
WifiHelper wifi;
Ptr<Ipv6ExtensionESP > extension;
Ptr<Ipv6ExtensionAH> extenAH;
YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();  
wifiPhy.Set ("RxGain", DoubleValue (-30)); 
wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); 
YansWifiChannelHelper wifiChannel;
wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
wifiPhy.SetChannel (wifiChannel.Create ());
NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode",StringValue (phyMode),"ControlMode",StringValue (phyMode)); 
wifiMac.SetType ("ns3::AdhocWifiMac");
NetDeviceContainer Groundstationnodes = wifi.Install (wifiPhy, wifiMac, Leo_Satellite_Nodes);
NetDeviceContainer eNodeBNodes;
eNodeBNodes = wifi.Install (wifiPhy, wifiMac, eNodeB);
int64_t streamIndex = 0;
ObjectFactory pos;
pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
pos.Set ("X", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=1000.0]"));
pos.Set ("Y", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=1000.0]"));
Ptr<PositionAllocator> taPositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();
streamIndex += taPositionAlloc->AssignStreams (streamIndex);
MobilityHelper mobility;
mobility.SetPositionAllocator(taPositionAlloc);
std::stringstream ssSpeed;
ssSpeed << "ns3::UniformRandomVariable[Min=0.0|Max=" << nodeSpeed << "]";
std::stringstream ssPause;
ssPause << "ns3::ConstantRandomVariable[Constant=" << nodePause << "]";
mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel","Speed", StringValue (ssSpeed.str ()),"Pause", StringValue (ssPause.str ()),
"PositionAllocator", PointerValue (taPositionAlloc));
mobility.Install (Leo_Satellite_Nodes);
MobilityHelper mobility1;
mobility1.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
mobility1.Install (eNodeB);
AnimationInterface::SetConstantPosition (eNodeB.Get (0), 478.2, 481.4);
AnimationInterface::SetConstantPosition (eNodeB.Get (1), 750, 250);
AnimationInterface::SetConstantPosition (eNodeB.Get (2), 250, 750);
AnimationInterface::SetConstantPosition (eNodeB.Get (3), 750, 750);
AnimationInterface::SetConstantPosition (eNodeB.Get (4), 250, 250);
Ptr<MmWaveHelper> mmWaveObj = CreateObject<MmWaveHelper> ();
mmWaveObj->Initialize();
NetDeviceContainer enbNetDev = mmWaveObj->InstallEnbDevice (eNodeB);
NetDeviceContainer SatelliteNetDev = mmWaveObj->InstallUeDevice (Leo_Satellite_Nodes);
mmWaveObj->AttachToClosestEnb (SatelliteNetDev, enbNetDev);
mmWaveObj->EnableTraces();
Simulator::Schedule (Seconds (2.3), &PktTrans1,Leo_Satellite_Nodes, eNodeB);
Simulator::Schedule (Seconds (8.3), &PktTrans2,Leo_Satellite_Nodes, eNodeB);
std::cout<<"\n\n Assign the IP addresses to the eNodeB nodes and ground station nodes. \n\n";
Ipv4AddressHelper ipv4;
Ipv4StaticRoutingHelper staticRouting;
Ipv4ListRoutingHelper list;
list.Add (staticRouting, 0);
InternetStackHelper internet;
internet.SetRoutingHelper (list); 
internet.Install (Leo_Satellite_Nodes);
internet.Install (eNodeB);
InternetStackHelper internetv6;
internetv6.SetIpv4StackInstall (false);
NS_LOG_INFO ("Assign IP Addresses.");
ipv4.SetBase ("10.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer i = ipv4.Assign (Groundstationnodes);
std::cout<<"\n\n Set up the mobility model and position allocator for the ground station nodes. \n\n";
for (uint32_t i = 0; i < eNodeB.GetN(); ++i) {
Ptr<MobilityModel> mobilityModel = eNodeB.Get(i)->GetObject<MobilityModel>();
Vector3D position = mobilityModel->GetPosition();
std::cout << "Node " << i << " Position: (" << position.x << ", " << position.y << ")" << std::endl;
}
std::cout<<"\n\n Set up the mobility model and position allocator for the satellite nodes. \n\n";
for (uint32_t i = 0; i < Leo_Satellite_Nodes.GetN(); ++i) {
Ptr<MobilityModel> mobilityModel = Leo_Satellite_Nodes.Get(i)->GetObject<MobilityModel>();
Vector3D position = mobilityModel->GetPosition();
std::cout << "Node " << i << " Position: (" << position.x << ", " << position.y << ")" << std::endl;
}
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSink = Socket::CreateSocket (Leo_Satellite_Nodes.Get (revNode), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
Simulator::Schedule (Seconds (14.3), &PktTrans3, Leo_Satellite_Nodes,eNodeB);
recvSink->Bind (local);
recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (Leo_Satellite_Nodes.Get (sourceNode), tid);
InetSocketAddress remote = InetSocketAddress (i.GetAddress (revNode, 0), 80);
source->Connect (remote);
Simulator::Schedule (Seconds (1.3), &GenerateTraffic, source, packetSize, numPackets, interPacketInterval);
Simulator::Stop (Seconds (simtime));
macgplot mg;
mg.Accuracy(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Precision(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Recall(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.F1_Score(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Throughput(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Packet_Loss(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Packet_Loss_Ratio(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Packet_Delivery_Ratio(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Delay(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
mg.Energy_Consumption(numSatellites,"Scenario_sybil_attack_model_mmwave_satellite");
pAnim= new AnimationInterface ("Scenario_sybil_attack_model_mmwave_satellite.xml");
pAnim->SetBackgroundImage ("/home/abdiasis/final_implementation_mmwave_leo/netanim-3.107/img1/bg.png", -955, -555, 2.500, 7.00, 1.0);
uint32_t Leoimg =pAnim->AddResource("/home/abdiasis/final_implementation_mmwave_leo//netanim-3.107/img1/Leo.png");
uint32_t eNodeBimg =pAnim->AddResource("/home/abdiasis/final_implementation_mmwave_leo//ns-allinone-3.29/netanim-3.107/img1/eNodeB.png");
for(  uint32_t i=0;i<Leo_Satellite_Nodes.GetN ();i++){
pAnim->UpdateNodeDescription (Leo_Satellite_Nodes.Get (i), "Leo"); 
Ptr<Node> wid= Leo_Satellite_Nodes.Get (i);
uint32_t nodeId = wid->GetId ();
pAnim->UpdateNodeImage (nodeId, Leoimg);
pAnim->UpdateNodeColor(Leo_Satellite_Nodes.Get(i), 255, 255, 0); 
pAnim->UpdateNodeSize (nodeId, 50.0,50.0);}
for(  uint32_t i=0;i<eNodeB.GetN ();i++){
pAnim->UpdateNodeDescription (eNodeB.Get (i), "eNodeB"); 
Ptr<Node> wid= eNodeB.Get (i);
uint32_t nodeId = wid->GetId ();
pAnim->UpdateNodeImage (nodeId, eNodeBimg);
pAnim->UpdateNodeColor(eNodeB.Get(i), 0, 255, 0); 
pAnim->UpdateNodeSize (nodeId, 125.0,125.0);}
FlowMonitorHelper flowmon;
Ptr<FlowMonitor> monitor = flowmon.InstallAll();
    Simulator::Stop(Seconds(simTime));
  AnimationInterface anim("Scenario_sybil_attack_model_mmwave_satellite.xml");
  anim.SetMaxPktsPerTraceFile(99999999999999);
Simulator::Run ();
monitor->CheckForLostPackets ();
uint32_t LostPacketsum = 0;
uint32_t rxPacketsum = 0;
uint32_t DropPacketsum = 0;
double Delaysum = 0.035; 
Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i){
rxPacketsum += (i->second.txBytes/(numSatellites*10));
LostPacketsum += i->second.lostPackets;
DropPacketsum += i->second.packetsDropped.size();
Delaysum += i->second.delaySum.GetSeconds();}
Simulator::Destroy ();
system("gnuplot 'Accuracy.plt'");
system("gnuplot 'Precision.plt'");
system("gnuplot 'Recall.plt'");
system("gnuplot 'F1_Score.plt'");
system("gnuplot 'Throughput.plt'");
system("gnuplot 'Packet_Loss.plt'");
system("gnuplot 'Packet_Loss_Ratio.plt'");
system("gnuplot 'Packet_Delivery_Ratio.plt'");
system("gnuplot 'Delay.plt'");
system("gnuplot 'Energy_Consumption.plt'");
return 0;}
