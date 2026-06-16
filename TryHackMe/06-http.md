# TryHackMe - HTTP in Detail

> Pre-Security path. Covers What is HTTP(S)?, Requests and Responses, HTTP Methods, HTTP Status Codes, Headers, Cookies, Making Requests.

---

## What is HTTP(S)?

**HTTP (HyperText Transfer Protocol)** - developed by Tim Berners-Lee and his team in the early 1990s. It's a set of rules used for communication between web clients (browsers) and web servers. HTTP is a **stateless protocol**, meaning the server does not remember anything between separate requests - every request is treated as brand new.

**HTTPS (HyperText Transfer Protocol Secure)** - encrypted version of HTTP. Uses **TLS (Transport Layer Security)** to encrypt traffic, so packets travelling over the network are not readable in plain text. This protects against attackers intercepting traffic (man-in-the-middle attacks).

**HTTP vs HTTPS - what packets look like:**

```
HTTP (unencrypted) - anyone intercepting the network can read this:
GET /login HTTP/1.1
Host: example.com
Content-Type: application/x-www-form-urlencoded

username=admin&password=mysecretpassword   ← visible in plain text


HTTPS (encrypted with TLS) - intercepted packet looks like this:
�k▒...��.�.▒..▒�fX..��.�..�9.3.2.1...    ← unreadable gibberish
```

> Source: [MDN - HTTP Overview](https://developer.mozilla.org/en-US/docs/Web/HTTP)

---

## Requests and Responses

When accessing a website, the browser needs to request assets like HTML, images, and scripts from a web server. Before that, it needs a URL to know where to go.

### URL (Uniform Resource Locator)

A URL is an instruction that tells the browser how to access a specific resource on the internet.

```
        USER    PASS        PORT   PATH        FRAGMENT
          ||      ||          ||     ||             ||
http://user:password@tryhackme.com:80/view-room?id=1#task3
  ||                      ||                  ||
SCHEME               HOST/DOMAIN         QUERY STRING
```

**Each part explained:**

| Part              | Example                 | What it does                                                                              |
| ----------------- | ----------------------- | ----------------------------------------------------------------------------------------- |
| **Scheme**        | `http://` or `https://` | Defines which protocol to use                                                             |
| **User:Password** | `user:password@`        | Optional credentials for authentication                                                   |
| **Host/Domain**   | `tryhackme.com`         | The address of the server                                                                 |
| **Port**          | `:80`                   | Which door to knock on (80 = HTTP, 443 = HTTPS). If not specified, defaults are used      |
| **Path**          | `/view-room`            | The specific resource or page being requested                                             |
| **Query String**  | `?id=1`                 | Extra data passed to the server (e.g. search terms, filters)                              |
| **Fragment**      | `#task3`                | Points to a specific section on the page - handled by the browser, not sent to the server |

### HTTP Request

When the browser sends a request, it looks like this:

```
GET /index.html HTTP/1.1
Host: tryhackme.com
User-Agent: Mozilla/5.0
Accept-Language: en-US
```

- First line = method + path + HTTP version
- Following lines = headers with additional info

### HTTP Response

The server replies with:

```
HTTP/1.1 200 OK
Server: nginx/1.15.8
Date: Fri, 09 Apr 2021 13:34:03 GMT
Content-Type: text/html
Content-Length: 98

<html>
...page content here...
</html>
```

- First line = HTTP version + status code
- Following lines = response headers
- Empty line separates headers from the body
- Body = the actual content (HTML, JSON, image data, etc.)

---

## HTTP Methods

HTTP methods define what action the client wants to perform. They are included in every request.

| Method     | Purpose                                         | Example use                                              |
| ---------- | ----------------------------------------------- | -------------------------------------------------------- |
| **GET**    | Retrieve data from the server                   | Loading a webpage, fetching an image                     |
| **POST**   | Send data to the server / create a new record   | Submitting a login form, creating a new user account     |
| **PUT**    | Send data to update an existing record          | Updating an email address in your profile                |
| **DELETE** | Delete a record from the server                 | Removing a profile picture                               |
| **PATCH**  | Partially update a record (only changed fields) | Changing just the username without touching other fields |

> GET and POST are the most common. In security testing, understanding what data is sent via POST is important - it often contains credentials or sensitive info.

---

## HTTP Status Codes

The first line of every HTTP response contains a status code telling the client what happened with the request.

### Status Code Ranges

| Range   | Category      | Meaning                                                |
| ------- | ------------- | ------------------------------------------------------ |
| **1xx** | Informational | Request received, still processing                     |
| **2xx** | Success       | Request was received, understood and completed         |
| **3xx** | Redirection   | Further action needed - client is redirected elsewhere |
| **4xx** | Client Error  | The request had an error on the client's side          |
| **5xx** | Server Error  | The server failed to handle a valid request            |

### Common Status Codes

| Code    | Name                  | What it means                                              |
| ------- | --------------------- | ---------------------------------------------------------- |
| **200** | OK                    | Request succeeded, content is returned                     |
| **201** | Created               | A new resource was successfully created (e.g. new account) |
| **301** | Moved Permanently     | Resource has permanently moved to a new URL                |
| **302** | Found                 | Temporary redirect to another URL                          |
| **304** | Not Modified          | Cached version is still valid, no new data sent            |
| **400** | Bad Request           | The request was malformed or missing required data         |
| **401** | Unauthorized          | Authentication required - not logged in                    |
| **403** | Forbidden             | Authenticated but no permission to access this resource    |
| **404** | Not Found             | The requested resource does not exist                      |
| **405** | Method Not Allowed    | HTTP method not supported for this endpoint                |
| **429** | Too Many Requests     | Rate limit hit - slow down                                 |
| **500** | Internal Server Error | Something broke on the server side                         |
| **503** | Service Unavailable   | Server is down or overloaded                               |

> 401 vs 403 is a common exam/interview question: **401 = not logged in**, **403 = logged in but no access**.

---

## Headers

Headers are additional pieces of data sent with HTTP requests and responses. They provide context about the request or response - things like who is making the request, what format is expected, or how long to cache the response.

### Common Request Headers (sent by client)

| Header              | What it does                                                                                     |
| ------------------- | ------------------------------------------------------------------------------------------------ |
| **Host**            | Specifies which domain is being requested (important when one server hosts multiple sites)       |
| **User-Agent**      | Identifies the browser and OS making the request (e.g. `Mozilla/5.0 Windows...`)                 |
| **Accept**          | Tells the server what content types the client can handle (e.g. `text/html`, `application/json`) |
| **Accept-Encoding** | Lists compression methods the client supports (e.g. `gzip`, `deflate`)                           |
| **Cookie**          | Sends stored cookies back to the server on every request                                         |
| **Referer**         | The URL of the page that linked to the current request                                           |
| **Authorization**   | Carries authentication credentials (e.g. tokens, API keys)                                       |

### Common Response Headers (sent by server)

| Header             | What it does                                                                            |
| ------------------ | --------------------------------------------------------------------------------------- |
| **Content-Type**   | Tells the client what type of data is being sent (e.g. `text/html`, `image/png`)        |
| **Content-Length** | Size of the response body in bytes                                                      |
| **Server**         | Identifies the web server software (e.g. `Apache`, `nginx`) - useful info for attackers |
| **Set-Cookie**     | Instructs the browser to store a cookie                                                 |
| **Cache-Control**  | Defines how long the browser should cache the response                                  |
| **Location**       | Used in redirects - tells the browser where to go next                                  |

> In security, response headers like `Server` can leak useful information about the server setup. A well-configured server should hide or obscure these.

---

## Cookies

Cookies are small pieces of data stored by the browser and sent back to the server with every subsequent request. They exist because HTTP is **stateless** - without cookies, the server would not know who you are between requests.

**How the cookie flow works:**

```
1. You log in → server sends back: Set-Cookie: session=abc123; HttpOnly
2. Browser stores the cookie locally
3. Every future request to that site includes: Cookie: session=abc123
4. Server reads the cookie and knows it's you
```

### Cookie Attributes

| Attribute             | What it does                                                                                         |
| --------------------- | ---------------------------------------------------------------------------------------------------- |
| **HttpOnly**          | Cookie cannot be accessed by JavaScript - protects against XSS attacks stealing session cookies      |
| **Secure**            | Cookie is only sent over HTTPS connections                                                           |
| **SameSite**          | Controls whether cookies are sent with cross-site requests - helps prevent CSRF attacks              |
| **Expires / Max-Age** | Defines how long the cookie lasts. Without this, it's a session cookie (deleted when browser closes) |
| **Path**              | Limits which paths on the site can receive the cookie                                                |

> In security testing, cookies are a primary target. Session hijacking works by stealing a valid session cookie and replaying it to impersonate the victim.

---

## Key Takeaways

- HTTP is stateless - cookies are what add "memory" to web sessions
- HTTPS encrypts traffic using TLS - always use it, HTTP sends everything in plain text
- Every HTTP request has a method (GET, POST, etc.) and every response has a status code
- Headers carry metadata about requests and responses - in pentesting they often reveal useful server info
- Cookie flags like `HttpOnly` and `Secure` are security features - their absence is a vulnerability

---

## References

- [TryHackMe - HTTP in Detail](https://tryhackme.com/room/httpindetail)
- [MDN - HTTP Overview](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [MDN - HTTP Headers](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers)
- [MDN - Using HTTP Cookies](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Cookies)
- [MDN - HTTP Status Codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status)
