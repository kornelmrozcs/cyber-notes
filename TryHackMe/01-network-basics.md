# TryHackMe — Network Basics

> Pre-Security path. Covers IP addresses, MAC addresses, ping, LAN, network topologies, routers, switches, subnetting, ARP and DHCP.

---

## IP address

An IP address is a logical address that identifies a network interface. "Logical" means it is assigned by network configuration rather than permanently built into hardware — it can change, for example when DHCP assigns a new one.

```
IPv4 example: 192.168.1.100
Format: four octets separated by dots, each 0–255
```

IP addresses can be private (used inside a LAN) or public (used on the internet). IP operates at Layer 3 of the OSI model. It tells the network where to route traffic across different networks.

---

## MAC address

A MAC address identifies a network interface within a local network. It is usually assigned by the manufacturer and can be thought of as a hardware identifier for the network interface card.

```
Example: 00:1A:2B:3C:4D:5E
Format: six octets in hex separated by colons
```

MAC addresses can be changed in software (spoofed). They operate at Layer 2 and are only relevant within the local network — they are not forwarded beyond the local segment.

| | IP | MAC |
|--|--|--|
| Layer | L3 (Network) | L2 (Data Link) |
| Scope | between networks | inside LAN only |
| Changes | can change (DHCP) | usually fixed, but spoofable |

---

## Ping

Ping uses ICMP (Internet Control Message Protocol) to test reachability and measure round-trip latency.

```bash
ping 192.168.1.1
ping google.com
```

It sends an ICMP Echo Request and waits for an ICMP Echo Reply. Ping measures latency and packet loss — it does not measure bandwidth or download speed.

---

## LAN

A LAN (Local Area Network) is a network covering a small physical area such as a home, office or school. Devices within a LAN can communicate directly with each other.

---

## Network topologies

Topology describes how devices are connected.

**Star topology** — all devices connect to a central switch or hub. The most common in modern networks. A single cable failure affects only one device, but if the central switch fails the whole network goes down.

**Bus topology** — all devices share a single backbone cable. Simple and cheap but collisions slow it down, and a break in the main cable affects the entire network.

**Ring topology** — devices are connected in a loop. In token ring, a token controls which device can transmit. A break in the ring can disrupt the entire network. Rarely used in modern LANs.

---

## Router

A router connects different networks. It operates at Layer 3 and forwards packets based on IP addresses and routing tables.

```
LAN (192.168.1.x) ←→ Router ←→ Internet
```

The router acts as the default gateway for devices in the LAN. When a device needs to reach an address outside its local network it sends the packet to the default gateway.

---

## Switch

A switch connects devices within the same LAN. It operates at Layer 2 and forwards Ethernet frames based on MAC addresses.

```
PC1 ↘
PC2 → Switch → (to router)
PC3 ↗
```

A switch learns which MAC address is reachable on which port and forwards frames only to the correct destination rather than broadcasting to all ports.

---

## Subnetting

Subnetting divides a larger network into smaller logical networks. A subnet mask defines which part of an IP address identifies the network and which part identifies the host.

```
Network: 192.168.1.0/24
Subnet mask: 255.255.255.0

Network address: 192.168.1.0   (represents the network, not assigned to a device)
Host range:      192.168.1.1 – 192.168.1.254
Broadcast:       192.168.1.255

Default gateway: usually 192.168.1.1 or 192.168.1.254
```

Devices in the same subnet communicate directly. Traffic to a different subnet must go through the router.

---

## ARP

ARP (Address Resolution Protocol) maps an IP address to a MAC address within the local network. Direction: IP → MAC.

A device knows the destination IP address but needs the destination MAC address to send a frame on the LAN.

```
ARP Request (broadcast): "Who has 192.168.1.10?"
ARP Reply   (unicast):   "That's me. My MAC is 00:1A:2B:3C:4D:5E."
```

The result is cached in the device's ARP table for future use.

---

## DHCP

DHCP (Dynamic Host Configuration Protocol) automatically provides network configuration to devices. Without it, each device would need to be manually configured.

DHCP can assign: IP address, subnet mask, default gateway, DNS server and lease time.

The process is called DORA:

```
Discover — device broadcasts: "Is there a DHCP server?"
Offer    — server responds with an available IP and configuration
Request  — device accepts the offer
ACK      — server confirms and assigns the configuration
```

---

## Key Takeaways

- IP is logical and routes traffic between networks; MAC is physical and delivers frames within a LAN
- ARP bridges the two: given an IP, it finds the MAC needed to actually send the frame locally
- Ping measures latency and reachability, not speed
- Subnetting separates networks; the default gateway (router) connects them
- DHCP automates what would otherwise require manual configuration on every device

---

## References

- [TryHackMe Pre-Security Path](https://tryhackme.com/path/outline/presecurity)
