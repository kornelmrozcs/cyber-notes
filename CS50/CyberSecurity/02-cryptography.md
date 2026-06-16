# CS50 Cybersecurity — Cryptography

> Lecture 1. Covers hashing, encoding, symmetric and asymmetric encryption, digital signatures, passkeys, disk encryption and an introduction to quantum computing.

---

## Encoding, encryption and hashing

These three terms are often confused. They are fundamentally different.

**Encoding** changes the format of data. It is reversible without a key. It is not a security mechanism.

```
"hello" → base64 → "aGVsbG8="
Anyone can decode this without a key.
```

**Encryption** protects data using a key. It is reversible only with the correct key.

```
"hello" + key → ciphertext
'Only' someone with the key can decrypt it.
```

**Hashing** produces a fixed-length one-way fingerprint of data. It is not reversible.

```
"hello" → SHA-256 → "2cf24dba5fb0a30e..."
You cannot get "hello" back from the hash.
```

---

## Password hashing

Storing passwords in plaintext is dangerous. If an attacker accesses the database they have every password immediately.

Hashing stores a fingerprint of the password instead of the password itself.

```
User sets password: "apple123"
System stores:      SHA256("apple123") → "3a7bd3e2..."

At login:
User enters "apple123" → system hashes it → compares to stored hash
Match = correct password. The original password is never stored.
```

When an attacker steals a hash, they guess passwords, hash each guess and compare to the stolen hash. This is why the strength of the original password still matters.

Properties of a good cryptographic hash function:
- **one-way** - cannot be reversed
- **deterministic** - same input always produces the same hash
- **avalanche effect** - a small input change produces a completely different hash
- **collision resistant** - two different inputs should not produce the same hash

---

## Rainbow tables and salting

The same password always produces the same hash. If two users have the same password their hashes are identical, which reveals the pattern.

A **rainbow table** is a precomputed lookup table mapping common passwords to their hashes. An attacker steals a hash and looks it up in the table rather than cracking it from scratch.

**Salting** defeats rainbow tables. A salt is a random value added to the password before hashing.

```
password:  "apple123"
salt:      "xK9#mQ2p"   (random, unique per user)
stored:    SHA256("apple123" + "xK9#mQ2p") → "9f2c1a..."
```

Two users with the same password get different hashes because their salts differ. An attacker would need a separate rainbow table for every salt, which is not practical. The salt is stored alongside the hash; it is not secret. The password remains the secret.

---

## Symmetric encryption

Symmetric encryption uses the same key to encrypt and decrypt. Both parties must share the key in advance.

```
Alice encrypts with key K → sends ciphertext → Bob decrypts with key K
```

The problem is securely distributing the shared key over an untrusted channel. Modern standard: **AES**. Older legacy option: Triple DES, now largely replaced.

---

## Public-key (asymmetric) encryption

Asymmetric encryption uses a key pair: a public key and a private key.

- The **public key** can be shared freely. Others use it to encrypt messages to you.
- The **private key** must stay secret. It is used to decrypt messages encrypted with your public key.

```
Bob encrypts a message using Alice's public key.
Only Alice can decrypt it using her private key.
```

This solves the key distribution problem. No prior secret sharing is needed.

**RSA** is a widely used public-key algorithm. Its security relies on the difficulty of factoring large numbers.

```
n = p × q   where p and q are large primes
Easy: multiply p × q
Hard: given only n, find p and q
```

**Diffie-Hellman key exchange** allows two parties to agree on a shared secret over an insecure channel without ever sending the secret itself.

---

## Digital signatures

Digital signatures prove authenticity and integrity. The direction of keys is the **opposite** of encryption.

```
Signing:     sender hashes the document, then signs the hash with their PRIVATE key
Verifying:   receiver hashes the received document, decrypts the signature with the sender's PUBLIC key, compares
```

Private key signs. Public key verifies.

A valid signature proves the document was not altered and that it came from the holder of the private key.

---

## Passkeys

Passkeys are a passwordless login method built on public-key cryptography.

```
Registration:
  Device generates a key pair.
  Private key stays on device.
  Public key is sent to the service.

Login:
  Service sends a challenge.
  Device signs the challenge with the private key.
  Service verifies the signature using the stored public key.
```

The user unlocks the private key locally with biometrics or a PIN. The service never receives biometric data. Passkeys are phishing-resistant because they are bound to the specific domain; a fake site cannot trigger a valid signature.

---

## Encryption in transit vs end-to-end encryption

**Encryption in transit** (e.g. HTTPS) protects data between the user and the server. The server can read the data after it arrives.

**End-to-end encryption** ensures only the sender and the intended recipient can read the content. The server relays the message but cannot decrypt it.

```
HTTPS:  You ←[encrypted]→ Server   (server sees content)
E2E:    You ←[encrypted]→ Server ←[encrypted]→ Recipient
                           ↑
                    server cannot decrypt
```

---

## File deletion and full-disk encryption

Deleting a file normally removes the reference/pointer to it. The data may remain on disk until overwritten and can often be recovered.

**Secure deletion** overwrites the data with zeros, ones or random patterns, making recovery significantly harder.

**Full-disk encryption (FDE)** encrypts data at rest. Without the correct key or password the data on disk appears as random noise. Useful if a device is lost or stolen. Examples: BitLocker (Windows), FileVault (macOS), LUKS (Linux).

---

## Ransomware

Ransomware is malware that encrypts a victim's files and demands payment for the decryption key. It can affect personal devices, companies and critical infrastructure.

Encryption itself is not harmful. Ransomware abuses it to hold data hostage. The primary defences are offline backups, software updates and endpoint protection.

---

## Quantum computing

Classical computers use bits: 0 or 1. Quantum computers use qubits, which can exist in superposition; not strictly 0 or 1 until measured.

Sufficiently powerful quantum computers could break some current public-key algorithms (RSA, ECC) by solving the underlying mathematical problems much faster. This is why **post-quantum cryptography** is being developed and standardised. NIST published its first post-quantum standards in 2024 (CRYSTALS-Kyber, CRYSTALS-Dilithium).

---

## Key Takeaways

- Encoding is not security - anyone can reverse it
- Hashing is one-way; salting makes rainbow tables useless
- Symmetric encryption: one shared key; problem is distributing it securely
- Asymmetric encryption: public key encrypts, private key decrypts
- Digital signatures: private key signs, public key verifies
- Passkeys are phishing-resistant and replace passwords with cryptography
- E2E encryption means even the server cannot read your messages

---

## References

- [CS50 Cybersecurity Lecture 1](https://cs50.harvard.edu/cybersecurity/)
- [NIST Post-Quantum Cryptography](https://csrc.nist.gov/projects/post-quantum-cryptography)
- [How HTTPS works](https://howhttps.works)
