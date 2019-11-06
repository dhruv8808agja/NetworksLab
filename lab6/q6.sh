ip netns add ns1
ip netns add ns2
ip netns add ns3

ip netns add i1
ip netns add i2
ip netns add i3

ip link add veth11 type veth peer name veth12
ip link add veth21 type veth peer name veth22
ip link add veth31 type veth peer name veth32

ip link add vethU121 type veth peer name vethU122
ip link add vethU231 type veth peer name vethU232
ip link add vethU311 type veth peer name vethU312

ip link set veth11 netns ns1
ip link set veth12 netns i1

ip link set veth21 netns ns2
ip link set veth22 netns i2

ip link set veth31 netns ns3
ip link set veth32 netns i3

ip link set vethU121 netns i1
ip link set vethU122 netns i2

ip link set vethU231 netns i2
ip link set vethU232 netns i3

ip link set vethU311 netns i3
ip link set vethU312 netns i1 

ip netns exec ns1 ip link set veth11 up
ip netns exec i1 ip link set veth12 up

ip netns exec ns2 ip link set veth21 up
ip netns exec i2 ip link set veth22 up

ip netns exec ns3 ip link set veth31 up
ip netns exec i3 ip link set veth32 up

ip netns exec i1 ip link set vethU121 up
ip netns exec i2 ip link set vethU122 up

ip netns exec i2 ip link set vethU231 up
ip netns exec i3 ip link set vethU232 up

ip netns exec i3 ip link set vethU311 up
ip netns exec i1 ip link set vethU312 up

#assigning ip addresses now

ip netns exec ns1 ip address add 10.0.0.1/24 dev veth11
ip netns exec i1 ip address add 10.0.0.2/24 dev veth12

ip netns exec ns2 ip address add 10.0.1.1/24 dev veth21
ip netns exec i2 ip address add 10.0.1.2/24 dev veth22

ip netns exec ns3 ip address add 10.0.2.1/24 dev veth31
ip netns exec i3 ip address add 10.0.2.2/24 dev veth32

ip netns exec i1 ip address add 10.0.4.1/24 dev vethU121
ip netns exec i2 ip address add 10.0.4.2/24 dev vethU122

ip netns exec i2 ip address add 10.0.5.1/24 dev vethU231
ip netns exec i3 ip address add 10.0.5.2/24 dev vethU232

ip netns exec i3 ip address add 10.0.6.1/24 dev vethU311
ip netns exec i1 ip address add 10.0.6.2/24 dev vethU312
#assigning default routing for outer nodes

ip netns exec ns1 ip route add default via 10.0.0.2 dev veth11
ip netns exec ns2 ip route add default via 10.0.1.2 dev veth21
ip netns exec ns3 ip route add default via 10.0.2.2 dev veth31



#assinging default routing for inner nodes

ip netns exec i1 ip route add 10.0.1.1 via 10.0.4.2 dev vethU121
ip netns exec i2 ip route add 10.0.2.1 via 10.0.5.2 dev vethU231
ip netns exec i3 ip route add 10.0.3.1 via 10.0.6.2 dev vethU311


#enableing ip forwarding for all the routers
ip netns exec i1 sysctl -w net.ipv4.ip_forward=1
ip netns exec i2 sysctl -w net.ipv4.ip_forward=1
ip netns exec i3 sysctl -w net.ipv4.ip_forward=1


#
