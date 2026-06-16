# TryHackMe - Putting It All Together

> Pre-Security path. Covers the full request lifecycle, Load Balancers, CDN, Databases, WAF, Web Servers, Virtual Hosts, Static vs Dynamic Content, Backend Languages.

---

## The Full Request Lifecycle

When you type a URL into your browser and hit enter, a lot happens before the page appears. The diagram below shows the full order of events:

```
1. You request tryhackme.com in your browser
2. Browser checks local cache for the IP address
3. If not cached, asks your recursive DNS server
4. Recursive DNS queries the root DNS server
5. Root server points to the authoritative DNS server
6. Authoritative DNS returns the IP address for tryhackme.com
7. Request passes through a WAF (Web Application Firewall)
8. Request passes through a Load Balancer
9. Browser connects to the web server on port 80 (HTTP) or 443 (HTTPS)
10. Web server receives the GET request
11. Web server talks to the database if needed
12. Server sends back HTML, CSS, JavaScript
13. Your browser renders it into a viewable webpage
```

To summarise: your computer uses DNS to find the server IP, then communicates using HTTP/HTTPS. The web server returns HTML, JavaScript, CSS and images which your browser uses to display the page.

---

## Other Components

### Load Balancers

When a website gets huge amounts of traffic, one server cannot handle it all. A load balancer sits in front of multiple servers and distributes incoming requests across them so no single server gets overwhelmed.

Load balancers use algorithms to decide where to send requests, for example:

- **Round-robin** - sends each new request to the next server in rotation (server 1, server 2, server 3, server 1, server 2...)
- **Weighted** - sends more traffic to more powerful servers

Load balancers also perform **health checks** - they regularly ping each server to check it is still responding. If a server goes down, the load balancer stops sending traffic to it until it recovers.

### CDN (Content Delivery Network)

A CDN stores copies of static files (images, JavaScript, CSS, videos) across servers distributed all around the world. When a user requests one of those files, the CDN automatically serves it from the nearest server geographically.

This means a user in Poland does not have to wait for files to travel from a server in the US. Result: faster load times and less load on the origin server.

CDNs only serve **static** content. Dynamic content still comes from the origin server.

### Databases

Websites need somewhere to store and retrieve data. Web servers communicate with databases to read and write information like user accounts, posts, orders and settings.

Common databases:

|Database|Type|
|---|---|
|MySQL|Relational (SQL)|
|PostgreSQL|Relational (SQL)|
|MongoDB|Non-relational (NoSQL)|
|MariaDB|Relational (SQL)|
|Microsoft SQL Server|Relational (SQL)|

> In security, databases are a primary target. SQL Injection is one of the most common web vulnerabilities and it directly attacks the database through unsanitized input.

### WAF (Web Application Firewall)

A WAF sits between the internet and the web server and inspects every incoming request before it reaches the server. Its job is to detect and block malicious traffic.

A WAF protects against:

- Common attack patterns like SQL Injection and XSS
- Bot traffic and automated scanning tools
- Rate limit abuse (too many requests from one IP)
- Known exploit signatures

If a request looks suspicious, the WAF drops it before it ever reaches the web server. Unlike a regular network firewall that works at the network level, a WAF understands HTTP and can inspect the actual content of requests.

---

## How Web Servers Work

A web server is software that listens for incoming HTTP connections and serves files back to the client. It uses the HTTP protocol to communicate.

Common web server software:

|Software|Notes|
|---|---|
|**Apache**|Open source, very widely used on Linux|
|**Nginx**|Known for high performance and handling many connections|
|**IIS**|Microsoft's web server, runs on Windows|
|**NodeJS**|JavaScript runtime used as a web server|

Web servers serve files from a **root directory**, a designated folder on the server. On Linux with Apache this is typically `/var/www/html`. So a request for `http://example.com/image.png` would look for the file at `/var/www/html/image.png` on the server.

### Virtual Hosts

A single physical server can host many different websites at the same time using **virtual hosts**.

When a request comes in, the web server reads the `Host` header from the HTTP request to see which domain is being requested. It then matches that against its list of configured virtual hosts and serves the correct website.

```
Request Host: example1.com  -->  serves from /var/www/website_one
Request Host: example2.com  -->  serves from /var/www/website_two
Request Host: unknown.com   -->  serves a default page
```

There is no limit to how many virtual hosts a server can have. Each domain just maps to a different folder on the same machine.

### Static vs Dynamic Content

**Static content** does not change between requests. It is a fixed file sitting on the server that gets served as-is every time someone requests it.

Examples: images, CSS files, JavaScript files, plain HTML pages, videos

**Dynamic content** is generated on demand by the server each time someone requests it. The result can change based on who is asking, what they searched for, or what is in the database.

Examples: a blog homepage that updates when a new post is added, search results, a personalised dashboard after login

Dynamic content requires backend processing. This is where backend languages come in.

### Scripting and Backend Languages

Backend languages run on the server, process logic and generate the HTML that gets sent back to the browser. The user never sees this code, only the output it produces.

Common backend languages:

|Language|Common use|
|---|---|
|**PHP**|One of the most widely used, powers WordPress|
|**Python**|Popular for web apps (Django, Flask frameworks)|
|**Ruby**|Ruby on Rails framework|
|**NodeJS**|JavaScript on the server side|
|**Perl**|Older, still found in legacy systems|

Example of what backend code does vs what the user sees:

```php
Backend code (user never sees this):
<?php echo "Hello " . $_GET["name"]; ?>

URL requested: /greeting?name=Kornel

What the user sees in their browser:
Hello Kornel
```

> Backend code is not visible when you view page source. This is why sensitive logic, credentials and database queries belong in the backend, not in JavaScript or HTML.

---

## Key Takeaways

- A full website request goes through DNS, WAF, Load Balancer, Web Server and often a Database before anything reaches your browser
- Load balancers distribute traffic and perform health checks on servers
- CDNs serve static files from the closest server to the user for speed
- WAFs inspect HTTP requests and block malicious traffic before it hits the server
- Virtual hosts allow one server to serve many different websites based on the Host header
- Static content never changes, dynamic content is generated per request by backend code
- Backend code runs on the server and is never visible to the user

---

## References

- [TryHackMe - Putting It All Together](https://tryhackme.com/room/puttingitalltogether)
- [MDN - How the web works](https://developer.mozilla.org/en-US/docs/Learn_web_development/Getting_started/Web_standards/How_the_web_works)
- [Cloudflare - What is a WAF](https://www.cloudflare.com/learning/ddos/glossary/web-application-firewall-waf/)
- [Cloudflare - What is a CDN](https://www.cloudflare.com/learning/cdn/what-is-a-cdn/)