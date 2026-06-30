# Cloud Computing Fundamentals

> Discover how cloud computing helps businesses move faster, do more, and scale with less effort.

---

## Overview

Cloud computing is built on the same ideas as the previous note: **virtualisation and containers**. Instead of buying and running your own servers, you rent computing resources from a provider over the internet and pay for what you use.

How it evolved:

1. Physical servers era (buy and run your own hardware)
2. Virtualisation (many VMs per machine)
3. Automation and remote management
4. Cloud computing (AWS launches, 2006)
5. Modern cloud era (containers, serverless, global scale)

What the cloud gives you (these line up with the official NIST characteristics):

- **On-demand self-service**: spin up resources yourself, no waiting on an IT department
- **Scalability and rapid elasticity**: grow or shrink capacity as load changes
- **Pay only for what you use**: no big upfront hardware cost
- **Broad network access**: reach it from anywhere
- **Availability** and **global reach**

---

## Deployment models (where the cloud lives)

- **Public cloud**: shared infrastructure owned by a provider (AWS, Azure). Multi-tenant.
- **Private cloud**: dedicated to one organisation. More control, more cost.
- **Hybrid cloud**: a mix of public and private, moving workloads between them.
- (NIST also lists **community cloud**, shared by organisations with common needs. Less common.)

---

## Service models (who manages what)

The three core models, from least to most managed by the provider:

| Model | You manage | Provider manages | Example |
|---|---|---|---|
| **IaaS** (Infrastructure) | OS, apps, data | hardware, network, virtualisation | AWS EC2, Azure VMs |
| **PaaS** (Platform) | your app and data | infrastructure + OS + runtime | Heroku, App Engine, Elastic Beanstalk |
| **SaaS** (Software) | nothing, you just use it | everything | Gmail, Office 365, Dropbox |

The higher up you go, the less you manage and the less you control. IaaS gives you a bare virtual machine to do anything with. SaaS gives you a finished app in the browser.

---

## Vendors and real-world use

Market leader is **AWS** (Amazon Web Services). Others: Microsoft Azure, Google Cloud, Alibaba Cloud, IBM Cloud, Oracle Cloud.

Real examples:

- **Netflix** runs on AWS, the classic large-scale case.
- **Spotify** actually runs on **Google Cloud**, not AWS (it migrated from AWS to GCP in 2016). Good reminder that "big company = AWS" is not always true.
- **Instagram** was built on AWS, later moved onto Meta's own data centers after the acquisition.
- Most online stores and SaaS products run on one of these clouds.

---

## AWS core building blocks

- **EC2** (Elastic Compute Cloud): a virtual computer (server) in the cloud. This is AWS's IaaS compute.
- **Instance type** (for example t2, t3, m5): describes how powerful that virtual computer is (CPU, memory, network profile). Different families suit different workloads, t-series for general burstable use, m-series for balanced general purpose.

---

## Key Takeaways

- Cloud = renting computing over the internet, built on virtualisation and containers, pay per use
- Evolution: physical servers, then virtualisation, then automation, then cloud (AWS 2006), then modern era
- Deployment models: public (shared), private (dedicated), hybrid (mix), plus community
- Service models: IaaS (you manage OS up), PaaS (you manage the app), SaaS (you manage nothing)
- Higher service model = less you manage and less you control
- AWS leads the market; EC2 is a cloud virtual machine, instance type sets its power
- Not every big company is on AWS, Spotify runs on Google Cloud

---

## References

- [TryHackMe - Cloud Computing Fundamentals](https://tryhackme.com/room/cloudcomputingfundamentals)
- [NIST SP 800-145 - The Definition of Cloud Computing](https://csrc.nist.gov/pubs/sp/800/145/final)
- [AWS - Docker vs VM (virtualisation background)](https://aws.amazon.com/compare/the-difference-between-docker-vm/)
