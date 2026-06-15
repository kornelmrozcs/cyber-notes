# TryHackMe — How the Web Works: DNS

> Pre-Security path. Covers DNS, the domain hierarchy, record types, the full DNS resolution process, and packets vs frames.

---

## What is DNS

DNS (Domain Name System) translates human-readable domain names into IP addresses.

```
google.com → 142.250.185.78
```

Without DNS, accessing websites would require remembering IP addresses. DNS also handles more than just website addresses — it routes email, verifies domain ownership and more.

---

## Domain hierarchy

Domains have a hierarchical structure, read right to left.

```
admin.test.com.
              └── root (.)
           └────── TLD: .com
      └──────────── second-level: test
└──────────────────── subdomain: admin
```

**Root** — the invisible dot at the end of every fully qualified domain name. Managed by root DNS servers.

**TLD (Top-Level Domain)** — the rightmost part after the final dot.
- Generic (gTLD): `.com`, `.org`, `.gov`, `.edu`, `.net`
- Country code (ccTLD): `.pl`, `.uk`, `.de`
- Newer: `.io`, `.tech`, `.shop`

**Second-level domain** — the part registered by a user or organisation. In `test.com`, `test` is the second-level domain. Maximum 63 characters, using `a-z`, `0-9` and hyphens.

**Subdomain** — everything to the left of the second-level domain. `admin.test.com` — `admin` is the subdomain. Not to be confused with a URL path: `test.com/admin` is a path, not a subdomain.

Maximum full domain name length: 253 characters.

---

## DNS record types

| Record | Purpose | Example |
|--------|---------|---------|
| A | maps a domain to an IPv4 address | `test.com → 93.184.216.34` |
| AAAA | maps a domain to an IPv6 address | `test.com → 2606:2800::1` |
| CNAME | alias from one domain to another | `www.test.com → test.com` |
| MX | specifies the mail server for a domain | `test.com → mail.test.com` |
| TXT | stores arbitrary text; used for verification, SPF, DKIM | `"v=spf1 ..."` |

---

## DNS resolution process

When you type `www.test.com` in a browser:

**1. Local cache** — the device checks whether it has a recent DNS answer cached. If yes, it uses it immediately.

**2. Recursive resolver** — if not cached, the device queries a recursive resolver (usually provided by the ISP or a public service like 8.8.8.8). The resolver acts as the agent that does the work of finding the answer.

**3. Root server** — if the resolver does not have the answer cached, it asks a root DNS server. The root server does not know the IP for `test.com` but it knows which servers are authoritative for `.com`.

**4. TLD server** — the resolver asks the `.com` TLD server. It does not know the final IP either but it knows which server is authoritative for `test.com` specifically.

**5. Authoritative server** — the resolver asks the authoritative DNS server for `test.com`. This server holds the actual DNS records and returns the answer.

**6. Response** — the resolver returns the IP to the device. The device connects. The resolver caches the answer for future queries according to the record's TTL.

```
Device → Recursive Resolver → Root → TLD (.com) → Authoritative → answer
```

If the owner of `test.com` updates their DNS records, the authoritative server has the new answer immediately. Resolvers will continue returning the old cached answer until the TTL expires.

---

## Packets and frames

### Packet — Layer 3

A packet is the Layer 3 unit of data. It uses IP addresses.

Key fields in an IP packet header:
- source IP address
- destination IP address
- TTL (Time To Live)
- checksum

**TTL** — decremented by one at each router hop. When it reaches zero the packet is dropped. This prevents packets from circulating forever due to routing loops.

**Checksum** — used for error detection, not encryption. It verifies the header has not been corrupted in transit.

### Frame — Layer 2

A frame is the Layer 2 unit of data. It uses MAC addresses and handles local delivery.

Key fields: source MAC, destination MAC, EtherType, FCS (frame check sequence for error detection).

### Packet vs frame

| | Packet | Frame |
|--|--------|-------|
| Layer | L3 | L2 |
| Address | IP | MAC |
| Device | router | switch |
| Changes in transit | IP addresses stay the same end-to-end | MAC addresses change at every hop |

The IP addresses in a packet remain constant from source to destination. The MAC addresses in the frame change at every router — each router strips the frame, reads the IP destination, builds a new frame addressed to the next hop, and sends it.

```
Packet = the letter with the final address
Frame  = the envelope used to carry it to the next post office
         Each post office opens the envelope, reads the letter's address,
         puts it in a new envelope addressed to the next stop.
```

---

## Key Takeaways

- DNS translates domain names to IP addresses; the process is: cache → resolver → root → TLD → authoritative
- Subdomains are part of the domain name (`admin.test.com`); URL paths are not (`test.com/admin`)
- CNAME creates an alias; MX directs email; TXT holds verification data
- TTL in a DNS record controls how long resolvers cache the answer
- Packets carry IP addresses (unchanged end-to-end); frames carry MAC addresses (replaced at every hop)
- TTL in a packet header prevents infinite routing loops

---

## References

- [TryHackMe Pre-Security Path](https://tryhackme.com/path/outline/presecurity)
- [How DNS Works — comic](https://howdns.works)
