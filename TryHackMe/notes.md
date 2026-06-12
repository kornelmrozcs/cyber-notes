# TryHackMe Notes

## Network basics

### IP address

- IP = Internet Protocol address.
- It is a logical address used to identify a network interface on a network.
- “Logical” means it is assigned by network configuration, not permanently burned into hardware.
- IP can be:
  - private, used inside LAN
  - public, used on the internet

- IP can change, for example when DHCP gives a new address.
- IPv4 has 4 octets.
- Example:
  - `192.168.1.100`

- Simple idea:
  - IP tells network traffic where to go at Layer 3.

### MAC address

- MAC = Media Access Control address.
- It identifies a network interface inside local network.
- Example:
  - Wi-Fi card has a MAC address
  - Ethernet card has a MAC address

- MAC is usually assigned by the manufacturer.
- It is similar to a serial number for a network interface, but not perfect identity.
- MAC can be spoofed/changed in software.
- Simple idea:
  - MAC is used for local delivery inside LAN at Layer 2.

### Ping

- Ping uses ICMP.
- ICMP = Internet Control Message Protocol.
- Ping sends ICMP Echo Request.
- If the target replies, it sends ICMP Echo Reply.
- Ping is used to check:
  - if a host is reachable
  - response time / latency
  - packet loss

- Ping is not the same as internet speed test.
- Simple idea:
  - ping checks reachability and latency, not download speed.

## LAN — Local Area Network

- LAN = Local Area Network.
- It is a network in a small area like:
  - home
  - office
  - school
  - lab

- Devices in a LAN can communicate with each other.
- LAN usually uses switches, routers, Ethernet cables, Wi-Fi, IP addresses and MAC addresses.

## Network topology

- Topology means the way devices are connected together in a network.

### Star topology

- Star topology is very common.
- All devices connect to one central device.
- Central device is usually:
  - switch
  - hub, older/simple networks

- Advantages:
  - easy to add new devices
  - easy to manage
  - if one cable fails, usually only one device is affected

- Disadvantage:
  - if central switch fails, many/all devices can lose connection

- Simple idea:
  - many devices connect to one central point.

### Bus topology

- Devices are connected to one main cable/backbone.
- All devices share the same communication medium.
- Advantages:
  - simple design
  - less cabling

- Disadvantages:
  - can be slow with many devices
  - collisions/traffic problems can happen
  - if main cable fails, network can be affected

- Simple idea:
  - one shared cable for many devices.

### Ring topology

- Devices are connected in a loop/ring.
- Data travels around the ring.
- In token ring, a token controls which device can send data.
- Advantages:
  - more controlled access to the network

- Disadvantages:
  - failure in the ring can affect communication
  - less common in modern basic LANs

- Simple idea:
  - devices are connected in a circle/loop.

## Router

- Router connects different networks together.
- Example:
  - home LAN to the internet
  - one subnet to another subnet

- Router mainly works at OSI Layer 3.
- Router uses IP addresses and routing tables.
- It decides where packets should go next.
- Example:
  - your PC wants to reach Google
  - traffic goes to your default gateway/router
  - router sends it toward the internet

- Simple idea:
  - router connects networks using IP/routing.

## Switch

- Switch connects devices inside the same LAN.
- Example devices:
  - PCs
  - printers
  - servers
  - access points

- Switch mainly works at OSI Layer 2.
- It forwards Ethernet frames using MAC addresses.
- Switch learns which MAC address is on which port.
- It does not mainly “break data into packets”.
- It forwards frames inside local network.
- Simple idea:
  - switch connects devices in LAN using MAC addresses.

## Subnetting

- Subnetting means splitting one larger network into smaller logical networks.
- A subnet mask helps decide:
  - which part of IP is the network part
  - which part of IP is the host part

- Example network:
  - `192.168.1.0/24`

- Network address:
  - `192.168.1.0`
  - represents the whole network
  - usually not assigned to normal device

- Host address:
  - `192.168.1.100`
  - assigned to a device/interface inside the network

- Default gateway:
  - usually router IP inside LAN
  - examples:
    - `192.168.1.1`
    - `192.168.1.254`

- Devices use default gateway when they need to send traffic outside their local network.
- Simple idea:
  - subnetting separates networks into smaller parts.

## ARP — Address Resolution Protocol

- ARP = Address Resolution Protocol.
- ARP is used inside local network.
- It maps IP address to MAC address.
- Correct direction:
  - IP -> MAC

- Example:
  - PC wants to talk to `192.168.1.10`
  - PC knows the IP
  - but to send frame inside LAN, it needs MAC address

- ARP request asks:
  - “Who has 192.168.1.10?”

- Device with that IP replies:
  - “That is me, here is my MAC address.”

- Then the sender can create a frame with correct destination MAC.
- Simple idea:
  - ARP finds MAC address for a local IP address.

## DHCP — Dynamic Host Configuration Protocol

- DHCP automatically gives network configuration to devices.
- Without DHCP, user/admin may need to manually set IP configuration.
- DHCP can assign:
  - IP address
  - subnet mask
  - default gateway
  - DNS server
  - lease time

- DHCP process is called DORA.

### DORA

- Discover
  - device asks if there is a DHCP server
  - “Can someone give me network settings?”

- Offer
  - DHCP server offers available IP/configuration

- Request
  - device requests/accepts offered configuration

- ACK
  - DHCP server confirms and assigns configuration

- Simple idea:
  - DHCP gives devices their network settings automatically.

# OSI Model

## OSI Model basics

- OSI = Open Systems Interconnection Model.
- It is a framework that explains how networked devices communicate.
- It has 7 layers.
- It helps understand what happens when data is sent and received.
- It is a model, not exactly how every real network works internally.

## Encapsulation

- Encapsulation happens when data is sent.
- Data moves down the layers.
- Each layer can add its own header/information.
- Example:
  - Layer 4 adds TCP/UDP information
  - Layer 3 adds IP information
  - Layer 2 adds MAC/frame information

- Simple idea:
  - data gets wrapped with extra information.

## De-encapsulation

- De-encapsulation happens when data is received.
- Data moves back up the layers.
- Each layer removes/uses its own header.
- Simple idea:
  - receiver unwraps the data.

## Layer 7 — Application

- Application layer is closest to the user.
- It is where application protocols work.
- It is not the graphical user interface itself.
- Examples:
  - HTTP
  - HTTPS
  - DNS
  - SMTP
  - FTP
  - SSH

- Simple idea:
  - application protocols used by software/services.

## Layer 6 — Presentation

- Presentation layer is about how data is represented.
- It can involve:
  - encoding
  - formatting
  - compression
  - encryption concepts

- Example:
  - converting data into format the other system understands

- HTTPS uses HTTP over TLS.
- In OSI teaching, encryption is often discussed around Presentation layer.
- In real TCP/IP model, TLS sits between application and transport.
- Simple idea:
  - data format and encryption/encoding concepts.

## Layer 5 — Session

- Session layer manages communication sessions.
- It can involve:
  - starting sessions
  - maintaining sessions
  - ending sessions

- Modern TCP/IP does not map perfectly to this OSI layer.
- Simple idea:
  - manages dialogue/session between systems.

## Layer 4 — Transport

- Transport layer handles communication between applications on hosts.
- Main protocols:
  - TCP
  - UDP

- Uses ports.
- TCP:
  - reliable
  - ordered
  - connection-based
  - can retransmit missing data

- UDP:
  - faster
  - simpler
  - connectionless/stateless
  - no delivery/order guarantee

- Simple idea:
  - TCP/UDP, ports, reliability vs speed.

## Layer 3 — Network

- Network layer handles logical addressing and routing.
- Main protocol:
  - IP

- It helps move packets between networks.
- Routers mainly work here.
- Routing can consider:
  - destination network
  - route/path
  - distance/metric
  - reliability

- Routing protocols can help routers share route information.
- Examples:
  - OSPF
  - RIP

- Simple idea:
  - IP addressing and routing between networks.

## Layer 2 — Data Link

- Data Link layer handles local network communication.
- It uses:
  - frames
  - MAC addresses

- Switches mainly work here.
- NICs have MAC addresses.
- Ethernet is strongly connected to this layer.
- Simple idea:
  - frames and MAC addresses inside LAN.

## Layer 1 — Physical

- Physical layer is about physical transmission of bits.
- Examples:
  - cables
  - radio/Wi-Fi signal
  - electrical signals
  - optical signals
  - bits on the wire/air

- Simple idea:
  - physical media and signals.

# Packets and Frames

## Packet

- Packet is a Layer 3 unit.
- Packet uses IP addresses.
- It has:
  - source IP
  - destination IP

- Main job:
  - move data between networks

- Routers forward packets.
- Simple idea:
  - packet = IP/routing level.

## Frame

- Frame is a Layer 2 unit.
- Frame uses MAC addresses.
- It has:
  - source MAC
  - destination MAC

- Main job:
  - move data inside local network / to next hop

- Switches forward frames.
- Simple idea:
  - frame = MAC/local LAN level.

## Packet vs frame

- Packet works at Layer 3.
- Frame works at Layer 2.
- Packet uses IP.
- Frame uses MAC.
- Frame wraps the packet for local delivery.
- Memory rule:
  - packet = letter/content with IP destination
  - frame = local envelope used to move it across LAN

## Packet header

- Packet header can include:
  - source IP
  - destination IP
  - TTL
  - checksum

### TTL

- TTL = Time To Live.
- TTL stops packet from travelling forever.
- Each router hop usually decreases TTL.
- If TTL reaches 0, packet is dropped.

### Checksum

- Checksum helps detect if header/data was damaged or changed.
- It is not encryption.
- It is for error detection.

## Memory rule

- Layer 3:
  - packet
  - IP address
  - router
  - routing

- Layer 2:
  - frame
  - MAC address
  - switch
  - LAN

# TCP/IP and Three-Way Handshake

## TCP/IP model

- TCP/IP is a protocol suite/model.
- OSI has 7 layers.
- TCP/IP usually has 4 layers.

### TCP/IP layers

- Application
- Transport
- Internet
- Network Interface

### TCP/IP vs OSI

- TCP/IP Application = OSI Layers 7, 6, 5
- TCP/IP Transport = OSI Layer 4
- TCP/IP Internet = OSI Layer 3
- TCP/IP Network Interface = OSI Layers 2, 1

## TCP

- TCP = Transmission Control Protocol.
- TCP is a Transport layer protocol.
- TCP is:
  - connection-based
  - reliable
  - ordered

- TCP checks that data arrived.
- TCP can resend missing data.
- TCP uses sequence numbers to rebuild data in correct order.
- TCP is slower than UDP because it does more work.
- Simple idea:
  - TCP cares about reliability.

## UDP

- UDP = User Datagram Protocol.
- UDP is also a Transport layer protocol.
- UDP is:
  - connectionless
  - stateless
  - faster
  - simpler

- UDP does not guarantee:
  - delivery
  - correct order
  - retransmission

- Simple idea:
  - UDP cares more about speed than reliability.

## TCP header

- TCP header can include:
  - source port
  - destination port
  - sequence number
  - acknowledgement number
  - checksum
  - flags

### Source port

- Source port is opened by sender.
- Usually temporary/random.
- Example:
  - browser uses random source port.

### Destination port

- Destination port is service port on receiving device.
- Examples:
  - HTTP = 80
  - HTTPS = 443

### Sequence number

- Helps put data in correct order.
- Important because data may arrive in pieces.

### Acknowledgement number

- Confirms received data.
- Shows what data is expected next.

### Flags

- Flags control TCP behaviour.
- Examples:
  - SYN
  - ACK
  - FIN
  - RST

## Three-Way Handshake

- TCP uses handshake before sending normal data.
- It establishes a connection and synchronizes sequence numbers.

### Steps

- SYN
  - client asks to start connection

- SYN/ACK
  - server agrees and acknowledges

- ACK
  - client confirms

- After this, connection is established.

## After connection

- DATA can be sent.
- TCP uses sequence numbers.
- ACKs confirm received data.
- Missing data can be resent.

## Closing connection

### FIN

- FIN closes connection properly.
- It should be acknowledged.
- Simple idea:
  - polite close.

### RST

- RST resets/stops connection suddenly.
- Used when something goes wrong or connection should be forcefully closed.
- Simple idea:
  - forced stop/reset.

## Memory rule

- TCP = reliable, ordered, connection-based.
- UDP = fast, simple, no guarantee.
- SYN → SYN/ACK → ACK = open TCP connection.
- FIN = close properly.
- RST = force reset/stop.

# UDP

## UDP basics

- UDP = User Datagram Protocol.
- UDP works at Transport layer.
- Same layer as TCP.
- UDP is stateless/connectionless.
- UDP does not create a connection before sending data.
- UDP does not use Three-Way Handshake.

## UDP vs TCP

- TCP:
  - reliable
  - ordered
  - connection-based
  - slower because of extra work

- UDP:
  - faster
  - simpler
  - no delivery guarantee
  - no order guarantee

## UDP advantages

- Faster than TCP.
- Uses less work/resources.
- Good when speed matters more than perfect reliability.
- Useful when small data loss is acceptable.

## UDP disadvantages

- No acknowledgement by default.
- No automatic retransmission.
- Sender does not automatically know if data arrived.
- Data can arrive out of order or not arrive at all.

## When UDP is useful

- Video calls
- Voice chat
- Online gaming
- Streaming
- DNS
- DHCP
- Situations where small data loss is acceptable

## When TCP is better

- File transfer
- Websites
- Login/session data
- Banking
- Anything where all data must arrive correctly

## UDP information

- UDP communication still uses:
  - source IP
  - destination IP
  - source port
  - destination port
  - data

- Source port is usually temporary/random.
- Destination port is usually service/application port.

## Memory rule

- TCP = safe and ordered.
- UDP = fast and simple.
- File transfer = TCP.
- Video call/game = UDP.

# Ports

## Port basics

- Ports are numbers used to identify applications/services on a device.
- Port value range:
  - 0 to 65535

- IP tells which device/interface.
- Port tells which application/service on that device.
- Simple idea:
  - IP = where is the host?
  - Port = which service on that host?

## Source port

- Source port is opened by sender.
- Usually random/temporary.
- Example:
  - browser opens random source port when connecting to website.

## Destination port

- Destination port is the service port on receiving device.
- Usually standard for known services.
- Example:
  - browser connects to web server destination port 80 or 443.

## TCP and UDP ports

- Both TCP and UDP use ports.
- Same port number can exist for TCP and UDP separately.
- Example:
  - TCP/53 and UDP/53 are different things.

## Well-known ports

- Ports 0-1023 are well-known/common ports.
- Common services usually use standard port numbers.

## Common ports

- FTP = 21
- SSH = 22
- DNS = 53
- HTTP = 80
- HTTPS = 443
- SMB = 445
- RDP = 3389

## Non-standard ports

- Services can run on different ports.
- Example:
  - web server can run on 8080 instead of 80

- Then the port must be specified.
- Example:
  - `example.com:8080`

## Memory rule

- IP = device/interface.
- Port = application/service.
- Browser source port = usually random.
- Web server destination port = usually 80 or 443.

# Port Forwarding

## Port forwarding basics

- Port forwarding allows external traffic to reach a service inside private LAN.
- It is usually configured on a router.
- Example:
  - public IP:8080 on router
  - forwards to private server `192.168.1.50:80`

- Router receives traffic on public port.
- Router forwards it to correct internal IP and port.

## Example

- Someone on internet connects to:
  - `public-ip:8080`

- Router forwards to:
  - `192.168.1.50:80`

- Internal web server receives the request.

## Why it is used

- Host a service from home/office network.
- Allow remote access to internal service.
- Direct traffic to correct internal machine.

## Security note

- Port forwarding can expose internal services to the internet.
- Only forward ports when needed.
- Services should be updated and secured.
- Use firewall rules and strong authentication.

## Simple idea

- Router maps public IP:port to private IP:port.

# Firewalls

## Firewall basics

- Firewall filters network traffic.
- It can allow or deny traffic based on rules.
- Firewall can control:
  - traffic coming in
  - traffic going out
  - traffic between networks

- Firewall can protect networks/devices from unwanted traffic.

## Firewall rules can check

- source IP
- destination IP
- source port
- destination port
- protocol:
  - TCP
  - UDP
  - ICMP

- direction:
  - inbound
  - outbound

- connection state

## Common questions firewall asks

- Where is traffic coming from?
- Where is traffic going?
- What port is being used?
- What protocol is being used?
- Is this part of an existing allowed connection?

## Stateful firewall

- Stateful firewall tracks connection state.
- It remembers if traffic belongs to an existing/allowed connection.
- Example:
  - user inside LAN connects to website
  - firewall allows return traffic because it belongs to that connection

- Simple idea:
  - remembers connection context.

## Stateless firewall

- Stateless firewall checks each packet individually.
- It uses static rules.
- It does not remember connection state.
- Simple idea:
  - checks every packet alone.

## Memory rule

- Stateful = remembers connection state.
- Stateless = checks packets individually.

# VPN

## VPN basics

- VPN = Virtual Private Network.
- VPN creates an encrypted tunnel through the internet.
- It can connect a device to another private network.
- Device can behave like it is inside that remote network.
- Example:
  - student connects to university network from home
  - employee connects to company network remotely

## Why VPN is useful

- Encrypts traffic between device and VPN server.
- Allows access to private/internal resources.
- Can protect traffic on untrusted Wi-Fi.
- Can make device appear as part of remote network.

## Important note

- VPN does not magically make everything safe.
- The VPN provider/network still matters.
- Malware/phishing can still affect user.
- VPN is one security tool, not full protection.

## VPN technologies

### PPP

- PPP = Point-to-Point Protocol.
- Used for point-to-point communication.
- PPP can provide authentication features.
- PPP itself is not the same as modern strong encryption.

### PPTP

- PPTP = Point-to-Point Tunneling Protocol.
- Older VPN protocol.
- It allowed PPP traffic to travel through IP networks.
- It is now considered outdated/weak and should not be preferred for strong security.

### IPsec

- IPsec = Internet Protocol Security.
- It can encrypt and authenticate IP traffic.
- Used in many VPN setups.
- Simple idea:
  - protects IP traffic with encryption/authentication.

## Memory rule

- VPN = encrypted tunnel to another network.
- PPTP = old/weak.
- IPsec = encryption/authentication for IP traffic.

# LAN Networking Devices

## Router

- Router connects LAN to other networks.
- Example:
  - LAN to internet
  - one subnet to another subnet

- Router mainly works at OSI Layer 3.
- Router uses IP addresses.
- Router forwards packets.
- Simple idea:
  - router = between networks.

## Switch

- Switch connects devices inside LAN.
- Switch mainly works at OSI Layer 2.
- It uses MAC addresses.
- It forwards frames to correct port/device.
- Simple idea:
  - switch = inside local network.

## Layer 2 switch

- Layer 2 switch forwards frames using MAC addresses.
- It works inside the same LAN/broadcast domain.
- It does not normally route between different IP networks.

## Layer 3 switch

- Layer 3 switch can do normal switch work and some routing work.
- It can route between VLANs/subnets.
- Common in larger networks.
- It is more advanced than basic Layer 2 switch.
- Simple idea:
  - Layer 3 switch = switch + routing features.

## VLAN

- VLAN = Virtual LAN.
- VLAN separates one physical switch/network into logical networks.
- Devices can be on same physical switch but in different VLANs.
- Different VLANs usually need routing to communicate with each other.
- Layer 3 switch or router can route between VLANs.
- Simple idea:
  - VLAN = logical separation inside network.

## Memory rule

- Router = connects networks, Layer 3, IP, packets.
- Switch = connects devices in LAN, Layer 2, MAC, frames.
- Layer 3 switch = can also route between VLANs/subnets.
