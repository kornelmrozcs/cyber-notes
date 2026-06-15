# TryHackMe — The OSI Model

> Pre-Security path. Covers the seven layers of the OSI model, encapsulation, de-encapsulation and what each layer is responsible for.

---

## What is the OSI model

The OSI (Open Systems Interconnection) model is a conceptual framework that describes how network communication works across seven layers. It is a model, not a strict implementation — real protocols do not always map cleanly to a single layer. Its value is in giving a shared vocabulary for understanding and troubleshooting networks.

```
Layer 7 — Application
Layer 6 — Presentation
Layer 5 — Session
Layer 4 — Transport
Layer 3 — Network
Layer 2 — Data Link
Layer 1 — Physical
```

Mnemonic top to bottom: **All People Seem To Need Data Processing**
Mnemonic bottom to top: **Please Do Not Throw Sausage Pizza Away**

---

## Encapsulation and de-encapsulation

When data is sent it travels down the layers. Each layer adds its own header (and sometimes a trailer).

```
Application data
↓ + TCP/UDP header   → Segment / Datagram
↓ + IP header        → Packet
↓ + MAC header       → Frame
↓ converted to bits  → transmitted
```

When data is received it travels up the layers. Each layer reads and removes its own header.

```
bits received → Frame → Packet → Segment → Application data
```

Encapsulation wraps data on the way out. De-encapsulation unwraps it on the way in.

---

## Layer 7 — Application

Closest to the user. This is where application-level protocols operate. It is not the graphical interface — it is the protocol the application uses to communicate.

Examples: HTTP, HTTPS, DNS, SMTP, FTP, SSH.

---

## Layer 6 — Presentation

Handles data format, encoding, compression and encryption concepts. Ensures data sent from one system can be understood by another.

In practice, TLS (used by HTTPS) sits between the application and transport layers in TCP/IP. OSI assigns encryption discussion to this layer for teaching purposes.

---

## Layer 5 — Session

Manages communication sessions between systems — opening, maintaining and closing them. The TCP/IP model does not have a direct equivalent; this layer is mostly conceptual in OSI.

---

## Layer 4 — Transport

Handles end-to-end communication between applications on different hosts. Uses ports to identify which application on a device should receive the data.

**TCP** — reliable, ordered, connection-based. Retransmits lost data. Slower due to overhead.

**UDP** — fast, connectionless, no delivery guarantee. Used where speed matters more than reliability.

---

## Layer 3 — Network

Handles logical addressing and routing between networks. The primary protocol is IP. Routers operate here.

Routing protocols such as OSPF and RIP allow routers to share route information and build routing tables.

---

## Layer 2 — Data Link

Handles local delivery within a network using frames and MAC addresses. Switches operate here. Ethernet is the dominant protocol at this layer.

---

## Layer 1 — Physical

The physical transmission of bits. Includes cables, electrical signals, optical fibre signals and radio waves (Wi-Fi).

---

## Layer summary

| Layer | Name | Unit | Key protocols / devices |
|-------|------|------|------------------------|
| 7 | Application | Data | HTTP, HTTPS, DNS, SSH, FTP |
| 6 | Presentation | Data | TLS, encoding, compression |
| 5 | Session | Data | session management |
| 4 | Transport | Segment / Datagram | TCP, UDP, ports |
| 3 | Network | Packet | IP, OSPF, RIP — router |
| 2 | Data Link | Frame | Ethernet, MAC — switch |
| 1 | Physical | Bits | cables, Wi-Fi, signals |

---

## Key Takeaways

- Encapsulation adds headers going down; de-encapsulation removes them going up
- Layer 3 uses IP and moves packets between networks via routers
- Layer 2 uses MAC and moves frames within a LAN via switches
- The OSI model is a teaching tool; TCP/IP is the model that real implementations follow

---

## References

- [TryHackMe Pre-Security Path](https://tryhackme.com/path/outline/presecurity)
