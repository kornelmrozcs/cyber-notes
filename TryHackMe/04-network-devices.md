# TryHackMe - Network Devices

> Pre-Security path. Covers Layer 2 and Layer 3 switches, VLANs, port forwarding, firewalls and VPNs.

---

## Layer 2 and Layer 3 switches

A Layer 2 switch forwards Ethernet frames using MAC addresses. It maintains a MAC address table that maps ports to MAC addresses and learns it dynamically. It does not route between IP networks.

A Layer 3 switch adds routing capability. It can forward frames like a Layer 2 switch and route packets between VLANs or subnets like a router. Common in larger networks where inter-VLAN routing needs to happen efficiently without an external router.

---

## VLAN

A VLAN (Virtual LAN) creates logical network segments on a single physical switch. Devices on the same physical switch can be separated into different VLANs and will not see each other's traffic.

```
One physical switch, three logical networks:
  VLAN 10 — IT department
  VLAN 20 — HR department
  VLAN 30 — Finance
```

Devices in different VLANs cannot communicate directly. Routing between VLANs requires a Layer 3 switch or a router. VLANs improve security by limiting broadcast domains and isolating traffic between groups.

---

## Port forwarding

Port forwarding allows inbound traffic from the internet to reach a service running inside a private network. It is configured on the router.

```
Internet → router:8080 → 192.168.1.50:80
```

Someone connecting to the public IP on port 8080 is forwarded to the internal server on port 80. Port forwarding exposes internal services to the internet. Only forward ports when necessary, keep the exposed service updated, and use strong authentication.

---

## Firewall

A firewall filters network traffic based on rules. It can allow or deny traffic based on source IP, destination IP, port, protocol, direction (inbound/outbound) and connection state.

**Stateful firewall** - tracks the state of active connections. When a device inside the network starts a connection to the outside, the firewall remembers it. If incoming traffic is a response to that connection, it gets allowed through automatically. If incoming traffic has no matching outbound connection on record, it gets blocked. This means you do not need to write explicit inbound rules for every expected response. The firewall figures it out from context.

**Stateless firewall** - checks each packet individually against a fixed set of rules. It has no memory of previous packets, so it has no idea if a packet is part of an existing connection or something random coming from outside. Every packet gets judged on its own. Simpler to set up, but easier to exploit because it cannot tell the difference between legitimate response traffic and unsolicited incoming packets.

```
Stateful: user opens connection → server replies → firewall allows reply automatically
Stateless: every packet needs a matching rule regardless of context
```

---

## VPN

A VPN (Virtual Private Network) creates an encrypted tunnel between a device and a remote network. The device behaves as if it were physically inside that network.

```
Device -[encrypted tunnel]- VPN server - private network / internet
```

Common uses: remote access to a corporate network, protecting traffic on untrusted Wi-Fi, connecting two office sites.

What a VPN does not do: it does not protect against malware or phishing, and it does not make the user anonymous; the VPN provider can still see traffic.

### VPN protocols

**PPTP** - Point-to-Point Tunneling Protocol. An older protocol considered weak. Should be avoided.

**IPsec** - Internet Protocol Security. Encrypts and authenticates IP traffic. Used in many enterprise and site-to-site VPN setups.

**OpenVPN** - open-source, strong encryption, widely used.

**WireGuard** - modern, fast, simple to configure. Increasingly common.

---

## Key Takeaways

- A Layer 3 switch adds routing to the capabilities of a Layer 2 switch
- VLANs logically isolate traffic on the same physical hardware; inter-VLAN routing still requires a Layer 3 device
- Port forwarding exposes internal services - use it only when needed
- Stateful firewalls track connection context; stateless firewalls do not
- A VPN encrypts the tunnel but does not protect against phishing or malware
- PPTP is outdated; prefer IPsec, OpenVPN or WireGuard

---

## References

- [TryHackMe Pre-Security Path](https://tryhackme.com/path/outline/presecurity)
