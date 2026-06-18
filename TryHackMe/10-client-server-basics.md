# Client-Server Basics

> How clients and servers communicate, what HTTP actually does, why the web is stateless by design, and how modern sites work around that.

---

## The big picture

Everything in this room is a recap of concepts from earlier rooms, but now looked at together as one system. The pizza analogy from the room is genuinely useful so I will keep it.

When you order a pizza:

- you need to know **where** the place is - that is **DNS**
- you need to speak the same language as the person taking the order - that is the **protocol**
- you go through a specific entrance for orders, not the back door - that is the **port**
- you make a **request**, they send back a **response**

That is the entire client-server model. You (client) ask for something specific in a format the server understands, through the right channel, and the server responds.

---

## Web communication

HTTP (HyperText Transfer Protocol) is the protocol the web runs on. HTTPS is the same thing but with TLS encryption on top - the S stands for Secure.

**HTTP is stateless.** The server treats every request as completely independent. It has no memory of previous requests from the same client. Send two requests back to back and as far as the server is concerned, they could be from two different strangers.

This is a deliberate design choice - it keeps servers simple and scalable. But it creates an obvious problem: how does a website remember that you are logged in?

**The workaround is statefulness through cookies and tokens.** When you log in, the server creates a session identifier and sends it back to your browser as a cookie. Every subsequent request your browser makes includes that cookie. The server reads it and knows who you are. The protocol itself is still stateless - the state is just being carried along manually in each request.

See [06-http.md](https://github.com/kornelmrozcs/cyber-notes/blob/main/TryHackMe/06-http.md) for a deeper look at HTTP.

---

## HTTP methods

HTTP methods tell the server what you want to do with a resource. The full list:

| Method  | Purpose                                       |
| ------- | --------------------------------------------- |
| GET     | retrieve a resource                           |
| POST    | send data to create something                 |
| PUT     | replace a resource entirely                   |
| PATCH   | partially update a resource                   |
| DELETE  | remove a resource                             |
| HEAD    | same as GET but returns headers only, no body |
| OPTIONS | ask the server what methods it supports       |
| CONNECT | open a tunnel, used for HTTPS through proxies |
| TRACE   | diagnostic - echoes the request back          |

In practice, GET and POST cover the vast majority of web traffic. GET fetches a page or resource. POST submits a form, logs you in, sends data.

---

## Browser developer tools

The browser inspector is one of the most useful tools for understanding how web communication actually works. Open it with F12 on most browsers, go to the Network tab, and reload a page.

For every request you can see:

- **scheme** - http or https
- **host** - the domain being contacted
- **path** - the specific resource requested
- **status code** - whether it worked (200), redirected (301/302), not found (404), server error (500)
- **request headers** - what the browser sent to the server
- **response headers** - what the server sent back, including content type and length
- **cookies** - session identifiers and other stored values
- **response body** - the actual content returned

Getting comfortable reading this panel is worth the time. It makes debugging and learning how specific sites work much faster.

---

## Key Takeaways

- Client sends a request, server sends a response - every web interaction follows this pattern
- DNS resolves the domain to an IP, ports direct traffic to the right service, the protocol defines the format
- HTTP is stateless by design - cookies and tokens are the mechanism that adds statefulness on top
- GET retrieves, POST submits - these two methods cover most of what you will see
- The browser network inspector shows the full picture of every request and response in real time

---

## References

- [TryHackMe - Client-Server Basics](https://tryhackme.com/room/clientserverbasics)
- [06-http.md](https://github.com/kornelmrozcs/cyber-notes/blob/main/TryHackMe/06-http.md)
