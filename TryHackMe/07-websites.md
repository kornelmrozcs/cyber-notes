# TryHackMe - How Websites Work

> Pre-Security path. Covers Front End vs Back End, HTML basics, JavaScript basics, Sensitive Data Exposure, HTML Injection.

---

## How Websites Work

When you visit a website, your browser sends a request to a web server somewhere in the world. That server processes the request and sends back data that the browser uses to display the page.

Every website has two sides:

**Front End (Client-Side)** - what the browser renders and what the user sees. Built with HTML, CSS and JavaScript. Anyone can inspect it by viewing the page source.

**Back End (Server-Side)** - the server that processes requests, talks to databases, runs logic and returns responses. Users cannot see this directly.

---

## HTML

HTML (HyperText Markup Language) is the basic building block of every webpage. It defines the structure and content using elements called tags.

```html
<!DOCTYPE html>
<html>
    <head>
        <title>Page Title</title>
    </head>
    <body>
        <h1>Main Heading</h1>
        <p>A paragraph of text.</p>
        <img src="img/dog.png">
        <a href="https://tryhackme.com">Click here</a>
    </body>
</html>
```

**Common HTML tags:**

|Tag|What it does|
|---|---|
|`<h1>` to `<h6>`|Headings, h1 being the largest|
|`<p>`|Paragraph of text|
|`<a href="">`|Hyperlink to another page or URL|
|`<img src="">`|Displays an image|
|`<div>`|A container block used for grouping and layout|
|`<button>`|A clickable button|
|`<!-- comment -->`|Comment, not displayed on the page but visible in source code|

> Comments are invisible on the page but fully visible when anyone views the page source. Developers sometimes accidentally leave sensitive data inside comments.

---

## CSS

CSS (Cascading Style Sheets) is used to style and visually design HTML elements. It controls colors, fonts, layout, spacing and more.

```css
h1 {
    color: red;
    font-size: 32px;
}

p {
    font-family: Arial;
    color: grey;
}
```

CSS does not affect functionality or security directly but understanding it helps when reading page source during recon.

---

## JavaScript

JavaScript (JS) adds interactivity and dynamic behavior to a webpage. It runs in the browser on the client side and can modify the page content in real time without needing to reload.

```javascript
// Change the content of an HTML element
document.getElementById("demo").innerHTML = "Hack the Planet";

// Basic if/else logic
var age = 18;
if (age >= 18) {
    alert("Access granted");
} else {
    alert("Access denied");
}
```

**Why JavaScript matters in security:**

JavaScript runs client-side, meaning the user has full access to it. Attackers can read it, modify it in browser DevTools and use it to understand how the application works. Sensitive logic or credentials should never live in JavaScript.

---

## Sensitive Data Exposure

Sensitive Data Exposure happens when a website does not properly protect or remove sensitive information from its front end source code, leaving it visible to anyone who views the page source.

Developers sometimes forget to remove:

- Temporary login credentials left in HTML comments
- API keys or tokens in JavaScript files
- Hidden links to private parts of the application
- Internal server paths or configuration details

**How to find it:**

Right click on any webpage and select "View Page Source" (or press `Ctrl+U`). Search through the HTML and JavaScript for comments, hardcoded values and anything that looks out of place.

```html
<!-- TODO: remove before production -->
<!-- admin login: username=admin password=testpasswd -->
```

This is a real example of the type of thing left behind. If you find credentials like this you can try them on login pages, admin panels or other parts of the application.

> From a security standpoint, anything in the front end is public. Treat it as if an attacker will read every line because they will.

---

## HTML Injection

HTML Injection is a vulnerability where an attacker is able to inject their own HTML code into a webpage because the website fails to sanitize user input.

**How it works:**

If a website takes user input and displays it directly on the page without filtering it, the browser will render whatever HTML the user submitted as if it were part of the original page.

```
Normal input:  John
Page displays: Hello, John!

Injected input:  <h1>Hacked</h1>
Page displays:   Hello, (large heading) Hacked
```

**A real example of an injection payload:**

```html
<a href="http://hacker.com">Click here to win a prize</a>
```

If submitted into a vulnerable input field, this would render a clickable malicious link on the page for other users to see.

**Why it matters:**

HTML injection on its own may seem low severity but it is a stepping stone. If JavaScript execution is also possible it escalates into **XSS (Cross-Site Scripting)**, which is a much more serious vulnerability that can steal session cookies, redirect users or perform actions on their behalf.

**How to prevent it:**

Input sanitization. The developer must filter and escape any user input before displaying it on the page, replacing characters like `<`, `>`, `"` with their safe HTML equivalents so they display as text and are never executed as code.

---

## Key Takeaways

- Front end is everything the browser renders. It is fully visible to anyone. Never store sensitive data there.
- HTML structures the page, CSS styles it, JavaScript makes it dynamic.
- Sensitive Data Exposure is one of the easiest things to check manually. Always view page source during recon.
- HTML Injection happens when user input is not sanitized before being displayed. Unsanitized input is a root cause of many web vulnerabilities.
- Input sanitization is the defense. Escape or filter everything that comes from a user before touching the page or a database.

---

## References

- [TryHackMe - How Websites Work](https://tryhackme.com/room/howwebsiteswork)
- [MDN - Getting started with HTML](https://developer.mozilla.org/en-US/docs/Learn_web_development/Core/Structuring_content/Basic_HTML_syntax)
- [MDN - JavaScript basics](https://developer.mozilla.org/en-US/docs/Learn_web_development/Getting_started/Your_first_website/Adding_interactivity)
- [OWASP - HTML Injection](https://owasp.org/www-project-web-security-testing-guide/latest/4-Web_Application_Security_Testing/11-Client-side_Testing/03-Testing_for_HTML_Injection)