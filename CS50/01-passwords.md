# CS50 Cybersecurity — Passwords, Attacks and Authentication

> Lecture 0. Covers how passwords work, common attacks against them, and the defences and alternatives that exist.

---

## Password rules

Password rules are intended to make passwords harder to guess. Common requirements include minimum length, uppercase letters, numbers and symbols.

The problem is that too many rules push users toward predictable patterns that technically satisfy the requirements.

```
Password1!
Summer2026!
Troub4dor&3
```

These pass most rule checks but are weak because they are predictable. **Length and randomness matter more than character substitutions.** A long passphrase or a password manager generated string is stronger than a short complex one.

---

## Regular password rotation

Forcing frequent password changes tends to make security worse, not better. Users respond by making small predictable changes.

```
Password2025! → Password2026!
```

An attacker who knows the old password or the pattern can guess the new one. It is better to change passwords when there is an actual reason:

- the password was leaked
- the account was compromised
- a suspicious login was detected
- an employee left the organisation
- the password was found to be weak

---

## Brute force attacks

A brute force attack tries every possible combination until one works.

```
4-digit PIN: 0000, 0001, 0002 ... 9999
Total combinations: 10^4 = 10,000
```

Longer passwords increase the number of combinations exponentially. Defences include rate limiting, account lockout after failed attempts, MFA, CAPTCHA and strong password hashing on the server side.

---

## Dictionary attacks

A dictionary attack does not try every combination. It tries likely passwords first — common words, leaked password lists, names, dates and known patterns.

```
password, qwerty, letmein, summer2026, football123
```

This works because humans tend to choose memorable and therefore predictable passwords.

---

## Credential stuffing

Credential stuffing takes leaked username and password pairs from one breach and tries them on other services.

```
Breach on Service A leaks: user@email.com / hunter2
Attacker tries same credentials on Gmail, Amazon, banks...
```

It works because people reuse passwords. The primary defence is using a unique password for every account, combined with MFA.

---

## Password managers

A password manager stores passwords securely and generates long, random, unique passwords for each account. The user only needs to remember one strong master password.

Risks:
- a weak master password makes the manager a single high-value target
- device security still matters

Good practice is a strong master password, MFA on the manager account itself, and never reusing the master password anywhere else.

---

## Multi-factor authentication (MFA)

MFA requires more than one type of proof to log in. There are three factor types.

**Knowledge** — something you know: password, PIN, security question. Can be guessed, stolen, phished or leaked.

**Possession** — something you have: phone, authenticator app, hardware security key, smart card. Phone can be stolen; SMS is vulnerable to SIM swapping.

**Inherence** — something you are: fingerprint, face scan, iris scan. Biometric data is difficult to change if compromised.

MFA requires at least two different factor types. Password + PIN is not MFA — both are knowledge factors.

---

## One-time passwords (OTP) and SIM swapping

An OTP is a temporary code valid for a short period. Examples include SMS codes, authenticator app codes and hardware tokens. OTP is a possession factor because it proves access to a device.

Authenticator apps are safer than SMS. SMS is weaker because of SIM swapping.

**SIM swapping** is when an attacker convinces a mobile carrier to transfer a victim's phone number to a SIM card the attacker controls. They then receive SMS messages and MFA codes intended for the victim.

Defences:
- use an authenticator app instead of SMS where possible
- use a hardware key for high-value accounts
- add a PIN or passphrase to your mobile carrier account
- watch for sudden loss of signal

---

## Social engineering and phishing

Social engineering attacks the human rather than the technical system. The attacker manipulates people into doing something unsafe — giving up a password, clicking a link, approving a login request, or transferring money.

**Phishing** is a social engineering attack delivered as a fake message that appears to come from a trusted source.

```
Fake bank email → steals login credentials
Fake Microsoft login page → captures password
Fake delivery SMS → installs malware
```

It is effective because it targets humans directly, uses urgency and emotion, and can look very convincing. One mistake by one user can bypass strong technical controls. Defences include user training, MFA, email filtering and careful URL inspection.

---

## On-path attacks (machine-in-the-middle)

An on-path attacker positions themselves between two communicating parties. Traffic passes through them, giving them the ability to observe or modify it.

```
User ←→ [attacker] ←→ Server
```

A common scenario is a compromised Wi-Fi access point or router. Defences include HTTPS/TLS, VPN on untrusted networks and not ignoring certificate warnings.

---

## Single Sign-On (SSO)

SSO lets a user log in once with an identity provider and access multiple services without logging in again.

```
"Sign in with Google" / "Sign in with Microsoft"
```

Benefits include fewer passwords, easier access management and the ability to enforce MFA centrally. The risk is that compromising the SSO account gives an attacker access to all connected services.

---

## Passkeys

Passkeys are a passwordless login method based on public-key cryptography. The private key stays on the user's device. The service stores the public key. At login, the service sends a challenge and the device signs it with the private key. The service verifies the signature using the public key.

The user unlocks the private key locally with a fingerprint, face scan or device PIN. The service never receives biometric data.

Passkeys are resistant to phishing because they are bound to the legitimate domain. A fake login page cannot use the passkey — it would not match the expected domain.

---

## Key Takeaways

- Length and randomness beat complexity rules for password strength
- Reused passwords make credential stuffing effective — unique password per account is the single most important defence
- MFA requires two different factor types; SMS is the weakest option
- Passkeys solve phishing and reuse at the same time
- Social engineering targets humans; technical controls alone cannot stop it

---

## References

- [CS50 Cybersecurity Lecture 0](https://cs50.harvard.edu/cybersecurity/)
- [NIST SP 800-63B — Digital Identity Guidelines](https://pages.nist.gov/800-63-3/sp800-63b.html)
- [Have I Been Pwned](https://haveibeenpwned.com)
