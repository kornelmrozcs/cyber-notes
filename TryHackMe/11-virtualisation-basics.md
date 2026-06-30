# Virtualisation Basics

> Learn why virtualisation powers modern IT, improving efficiency and safely isolating environments.

---

## Overview

In the early days, the rule was **one server = one application**. That was expensive and wasteful: most servers ran far below full capacity, setup was slow, and scaling was hard. You bought a whole physical machine just to run one app, then watched it sit mostly idle.

Virtualisation fixed this by adding a software layer called a **hypervisor** that splits one physical machine into many virtual ones. Now a single server runs many isolated systems at once, using its hardware properly.

Analogy (apartment building):

- building = physical server
- apartments = virtual machines
- tenants = applications or operating systems
- building manager = hypervisor

Each virtual computer is a **virtual machine (VM)**. On TryHackMe these deployable VMs are called "lab machines", but VM is the general term.

**When did this start?** The concept is old. IBM ran virtualisation on mainframes in the 1960s and 70s, and the word "hypervisor" comes from that era. The modern version that powers today's data centers took off around 1999 to 2001, when VMware brought virtualisation to ordinary x86 servers.

---

## Hypervisor

The core technology behind virtualisation. It:

- divides one set of hardware into multiple virtual machines
- gives each VM its own slice of CPU, memory, storage, network
- keeps VMs isolated from each other (one crashing does not touch the others)
- manages the VM lifecycle (create, start, stop, snapshot, delete)

### Two types

| | Type 1 | Type 2 |
|---|---|---|
| Also called | bare-metal | hosted |
| Runs on | the physical hardware directly | inside an existing OS, like an app |
| Speed | faster, more efficient | slower, extra layer |
| Setup | harder | easier |
| Examples | VMware ESXi, Microsoft Hyper-V, KVM, Xen, Proxmox | VirtualBox, VMware Workstation, Parallels |

### Which type for which job

| Use case | Type |
|---|---|
| Test malicious files | Type 2 |
| Production server | Type 1 |
| Database server | Type 1 |
| Software testing | Type 2 |
| Running Kali on your laptop | Type 2 |
| Data center | Type 1 |

The pattern: **Type 1 for production, performance, and scale** (servers, databases, data centers). **Type 2 for your own machine** (learning, software testing, running Kali, detonating malware in a throwaway VM you can snapshot and revert).

---

## Containers and Docker

A **container** is a lightweight isolated environment that packages a single application with everything it needs to run (libraries, dependencies). **Docker** is the dominant tool for building and running them.

The key difference from a VM is what gets virtualised:

- A **VM virtualises hardware**. Each VM runs a full guest OS on top of the hypervisor. Strong isolation, but heavy, and slow to boot (loads a whole OS).
- A **container virtualises the OS**. Containers share the host machine's kernel and carry only the app plus its dependencies. Light, and starts in seconds.

```
VM                          Container
-----------------           -----------------
| App           |           | App           |
| Guest OS      |           | Dependencies  |
| Virtual HW    |           -----------------
-----------------           | Docker Engine |
| Hypervisor    |           | Host OS kernel|
| Host OS / HW  |           | Physical HW   |
-----------------           -----------------
```

When to use which:

- **Container** for speed, scaling, and portability (microservices, "runs the same everywhere").
- **VM** for strong isolation, running different operating systems, or legacy systems.

Security note for the pentest path: because containers share the host kernel, isolation is weaker than a VM. A kernel exploit can break out of a container. That is exactly why you detonate malware in a Type 2 **VM**, not a container. (Kubernetes is the tool that manages many containers at scale, worth knowing the name for later.)

---

## Key Takeaways

- Old model was one server per app, wasteful and slow; virtualisation runs many isolated systems on one machine
- The hypervisor splits hardware, allocates resources, isolates VMs, and manages their lifecycle
- Type 1 (bare-metal) for production and scale; Type 2 (hosted) for your own machine and testing
- A VM virtualises hardware and runs a full guest OS; a container virtualises the OS and shares the host kernel
- Containers are lighter and faster; VMs give stronger isolation, so use a VM for malware analysis
- Docker runs containers, Kubernetes orchestrates many of them

---

## References

- [TryHackMe - Virtualisation Basics](https://tryhackme.com/room/virtualisationbasics)
- [AWS - Docker vs VM (difference explained)](https://aws.amazon.com/compare/the-difference-between-docker-vm/)
- [IBM Technology - Virtual Machine (VM) vs Docker (YouTube)](https://www.youtube.com/watch?v=a1M_thDTqmU)
