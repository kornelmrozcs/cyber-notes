# TryHackMe - TCP, UDP and the Three-Way Handshake

> Pre-Security path. Covers TCP and UDP, the three-way handshake, TCP headers, connection teardown and ports.

---

## TCP vs UDP

Both protocols operate at Layer 4 (Transport). They differ fundamentally in what they guarantee.

| | TCP | UDP |
|--|-----|-----|
| Connection | required (handshake) | none |
| Reliability | guaranteed | no guarantee |
| Order | preserved | not guaranteed |
| Retransmission | yes | no |
| Speed | slower | faster |
| Use cases | files, web, login, email | streaming, VoIP, gaming, DNS |

---

## TCP

TCP (Transmission Control Protocol) is connection-based and reliable. Before any data is exchanged a connection must be established. TCP uses sequence numbers to ensure data arrives in order and retransmits any segment that is not acknowledged.

---

## TCP header fields

| Field                  | Description                                                |
| ---------------------- | ---------------------------------------------------------- |
| Source port            | port opened by the sender, usually random/ephemeral        |
| Destination port       | port of the service on the receiving end                   |
| Sequence number        | used to order data and detect missing segments             |
| Acknowledgement number | confirms received data and indicates what is expected next |
| Flags                  | SYN, ACK, FIN, RST - control TCP behaviour                 |
| Checksum               | error detection                                            |

### TCP flags

**SYN** - synchronise; used to initiate a connection.
**ACK** - acknowledge; confirms receipt.
**FIN** - finish; initiates a clean connection close.
**RST** - reset; abruptly terminates a connection.

---

## Three-way handshake

TCP requires a handshake before data can be sent. It synchronises sequence numbers between both sides.

```
Client                        Server
  |                              |
  |──── SYN ────────────────────>|   "I want to connect. My SEQ=x."
  |                              |
  |<─── SYN/ACK ─────────────────|   "Agreed. My SEQ=y. I acknowledge your SEQ." 
  |                              |
  |──── ACK ────────────────────>|   "Confirmed. Connection open."
  |                              |
  |──── DATA ───────────────────>|
```

SYN → SYN/ACK → ACK. Three steps, three-way.

---

## Closing a connection

**FIN** - clean close. One side sends FIN, the other acknowledges, then sends its own FIN, which is acknowledged in return. All four steps complete cleanly.

**RST** - immediate reset. Abruptly ends the connection without the normal teardown sequence. Used when something has gone wrong or the connection is rejected outright.

---

## UDP

UDP (User Datagram Protocol) is connectionless and stateless. There is no handshake, no acknowledgement and no retransmission. Data is sent and the sender does not know whether it arrived.

```
Client                        Server
  |──── Datagram ───────────────>|   (may or may not arrive)
  |──── Datagram ───────────────>|   (may arrive out of order)
```

UDP is faster and uses fewer resources. It is appropriate when small data loss is acceptable or when the application handles reliability itself.

---

## Ports

Ports identify which application on a device should receive traffic. IP identifies the device; the port identifies the service.

Port ranges:
- 0–1023: well-known ports, reserved for standard services
- 1024–49151: registered ports
- 49152–65535: ephemeral/dynamic ports used by clients as source ports

### Common ports to know

| Port | Protocol | Service |
|------|----------|---------|
| 21 | TCP | FTP |
| 22 | TCP | SSH |
| 53 | TCP/UDP | DNS |
| 80 | TCP | HTTP |
| 443 | TCP | HTTPS |
| 445 | TCP | SMB |
| 3389 | TCP | RDP |

A service can run on a non-standard port. In that case the port must be specified explicitly in the URL, for example `http://example.com:8080`.

---

## TCP/IP model vs OSI

The TCP/IP model has four layers rather than seven.

| TCP/IP | OSI equivalent |
|--------|---------------|
| Application | Layers 7, 6, 5 |
| Transport | Layer 4 |
| Internet | Layer 3 |
| Network Interface | Layers 2, 1 |

---

## Key Takeaways

- TCP is reliable and ordered; it requires a handshake and uses acknowledgements
- UDP is fast and connectionless; no delivery or order guarantee
- The three-way handshake is SYN → SYN/ACK → ACK
- FIN closes cleanly; RST terminates immediately
- Ports identify services; 22=SSH, 80=HTTP, 443=HTTPS, 53=DNS are essential to know

---

## References

- [TryHackMe Pre-Security Path](https://tryhackme.com/path/outline/presecurity)
