# Inside a Computer System

> What is actually inside a computer, how the components work together, what happens when you press the power button, and how different types of computers differ.

---

## Computer components

### Motherboard

The motherboard is the backbone that connects everything else. Every other component either plugs into it directly or connects through it. It contains the **chipset**; a set of chips that manage communication between the CPU, RAM, storage and peripherals. It also has heatsinks in places that generate heat passively, and slots for RAM, GPU and storage.

Think of it as the city infrastructure; roads, power lines, communication cables; that everything else depends on.

---

### CPU

The CPU (Central Processing Unit) is the brain of the computer. It executes instructions one at a time, but does it extremely fast.

Inside a CPU:

**ALU (Arithmetic Logic Unit)** - the part that actually does the maths. Addition, subtraction, comparisons, logical operations. Every calculation your program makes goes through here.

**Control Unit** - reads instructions from memory and tells the rest of the CPU what to do with them. It orchestrates the whole process.

**Registers** - tiny, extremely fast storage built directly into the CPU. We are talking bytes, not gigabytes. The CPU uses registers to hold the values it is currently working with.

**Cache** - slightly larger than registers but still very fast. Since accessing RAM takes comparatively long, the CPU keeps frequently used data in cache to avoid going back to RAM constantly. There are usually three levels - L1 (smallest, fastest, closest to the core), L2, and L3 (shared between cores, larger but slower).

**The pipeline** - modern CPUs do not wait for one instruction to finish before starting the next. They overlap stages: while one instruction is being executed, the next is being decoded, and the one after that is being fetched from memory. This is called pipelining.

**How a CPU processes an instruction (simplified):**

```
Fetch    → retrieve the instruction from memory
Decode   → figure out what the instruction means
Execute  → ALU does the actual work
Store    → write the result back to a register or memory
```

Common CPU technologies worth knowing: hyper-threading (one physical core pretending to be two logical ones), multiple cores (actual separate processing units on one chip), clock speed (how many cycles per second, measured in GHz), and TDP (how much heat it generates).

---

### GPU

The GPU (Graphics Processing Unit) contains thousands of smaller, simpler cores compared to a CPU. A modern CPU might have 8-16 powerful cores. A GPU might have thousands of weaker ones.

This makes them good at completely different things. A CPU is good at complex sequential tasks. A GPU is good at doing many simple calculations simultaneously; originally for rendering pixels (every pixel on screen needs to be calculated), now also for machine learning, crypto mining and scientific simulations.

GPUs also have their own cache and their own memory (VRAM), separate from system RAM.

---

### PSU

The PSU (Power Supply Unit) converts AC power from the wall outlet into the DC voltages that computer components need (typically 12V, 5V, 3.3V). Every component draws power from it. The wattage rating tells you the maximum power it can deliver; underspeccing the PSU for the components you have is a common build mistake.

---

### RAM

RAM (Random Access Memory) is temporary, fast storage. When you open a program, it gets loaded from long-term storage into RAM so the CPU can access it quickly. When you close it or shut down, that data is gone.

"Random access" means any location in RAM can be read just as fast as any other - unlike a hard drive where physical seek time matters.

The CPU cannot realistically run programs directly from a hard drive - it is too slow. RAM is the middle layer that bridges fast CPU operations and slower permanent storage.

---

### Long-term memory

Hard drives (HDD) and solid state drives (SSD) store data permanently - it survives a shutdown.

HDDs use spinning magnetic platters and a read/write head that physically moves. Slower, mechanical, but cheap per gigabyte.

SSDs use flash memory chips with no moving parts. Much faster, more durable, but more expensive per gigabyte.

Both are many times slower than RAM. This is why what is currently in use lives in RAM and everything else waits on disk.

---

## What happens when you press the power button

**Step 1 - Power button** triggers the PSU to start delivering power to all components.

**Step 2 - Firmware starts.** The CPU immediately begins executing instructions stored in firmware (BIOS or UEFI) on a small chip on the motherboard. This is the first software that runs. It does not come from the hard drive - it is built into the board.

**Step 3 - POST (Power-On Self Test).** The firmware checks that essential hardware is present and working - CPU, RAM, storage. If something is wrong it usually signals this with beep codes or an error screen. This is why a broken RAM stick can prevent a computer from booting at all.

**Step 4 - Select boot device.** The firmware looks for a bootable device - usually the SSD/HDD, but can be a USB drive. The order is configurable in BIOS/UEFI settings.

**Step 5 - Bootloader.** The firmware hands control to the bootloader (for example GRUB on Linux or the Windows Boot Manager). The bootloader's job is to load the operating system kernel into RAM.

**After that - the kernel takes over.** The kernel initialises hardware drivers, mounts the file system, starts system processes and eventually brings up the user environment you see.

---

## Firmware, BIOS and the kernel

These three are related but different things that are easy to conflate.

**Firmware** is the low-level software stored on a chip on the motherboard. It runs before anything else. BIOS (Basic Input/Output System) is the older standard. UEFI (Unified Extensible Firmware Interface) is the modern replacement - it supports larger drives, has a graphical interface and boots faster.

**The kernel** is not stored in the firmware. It lives on the hard drive or SSD and is loaded into RAM by the bootloader. The kernel is the core of the operating system - it manages hardware access, memory, processes and everything in between. Linux, Windows and macOS all have their own kernels.

So the order is: firmware (on chip) → bootloader (on drive) → kernel (loaded into RAM).

---

## Computer types

**Desktop** - full-size components, easy to upgrade, not portable. Best performance per pound spent.

**Laptop** - portable, integrated components (screen, battery, keyboard), harder to upgrade, generally less powerful than equivalent-priced desktop.

**Workstation** - high-end desktop or laptop built for professional workloads. More RAM capacity, ECC memory support, professional GPUs, higher reliability standards.

**Server** - designed to run continuously, prioritises reliability and throughput over single-task performance. Rack-mounted, redundant power supplies, remote management capabilities.

**Embedded systems** - computers built into a specific device to do one job. Your router, smart TV, car's ECU, industrial controller. Usually low-power, fixed hardware, often running a stripped-down OS or no OS at all.

**IoT (Internet of Things)** - embedded systems with network connectivity. Sensors, smart home devices, wearables. Resource-constrained and often a security nightmare because firmware updates are rare and security was an afterthought.

---

## Key Takeaways

- The CPU fetches, decodes and executes instructions - the ALU does the actual calculations, cache reduces how often it needs to go back to RAM
- GPU has many weak cores for parallel tasks; CPU has few powerful cores for complex sequential tasks
- RAM is fast and temporary; long-term storage is slow and permanent - the CPU works primarily out of RAM
- Boot sequence: PSU → firmware (BIOS/UEFI) → POST → bootloader → kernel
- Firmware lives on a chip on the motherboard; the kernel lives on disk and gets loaded into RAM at boot

---

## References

- [TryHackMe - Inside a Computer](https://tryhackme.com/room/insideacomputer)
- [TryHackMe - Computer Types](https://tryhackme.com/room/computertypes)
