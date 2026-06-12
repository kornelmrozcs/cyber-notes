CS50 Cyber Security Notes

# Lecture 0

## Password rules

- Password rules are meant to make passwords harder to guess.
- Example rules:
  - minimum length
  - uppercase letters
  - lowercase letters
  - numbers
  - symbols

- Problem:
  - too many rules can make passwords harder for humans to remember
  - people may create predictable passwords just to satisfy the rules
  - example: `Password1!`, `Summer2026!`, `Troub4dor&3`

- Better idea:
  - long passwords/passphrases
  - random words
  - password manager generated passwords

- Length and randomness usually matter more than weird substitutions.

## Regular password changes

- Forcing people to change passwords too often can create a security problem.
- Human factor:
  - people want passwords they can remember
  - they may choose simpler passwords
  - they may reuse old patterns
  - they may only change one character

- Example:
  - `Password2025!`
  - `Password2026!`

- This is predictable for attackers.
- It is usually better to change passwords when there is a reason:
  - password leaked
  - account compromised
  - suspicious login
  - employee leaves company
  - weak password discovered

## Brute force attacks

- Brute force means trying many possible passwords until one works.
- Example:
  - trying every 4-digit PIN from `0000` to `9999`

- A 4-digit PIN has:
  - `10^4 = 10,000` possibilities

- More length = more possible combinations.
- More attempts per second = faster cracking.
- Defences:
  - rate limiting
  - account lockout
  - MFA
  - CAPTCHA
  - strong password hashing

## Dictionary attacks

- Dictionary attack uses common words, leaked passwords, names, dates, patterns, etc.
- It does not try every possible combination first.
- It tries likely passwords first.
- Example:
  - `password`
  - `qwerty`
  - `letmein`
  - `summer2026`
  - `football123`

- This works because many humans choose memorable and predictable passwords.

## Credential stuffing

- Credential stuffing uses leaked usernames/emails and passwords from one website.
- The attacker then tries the same login details on other websites.
- Example:
  - email/password leaked from Website A
  - attacker tries same email/password on Gmail, Amazon, Netflix, bank, etc.

- This works because people reuse passwords.
- Defences:
  - unique password for every account
  - password manager
  - MFA
  - breach monitoring
  - rate limiting
  - suspicious login detection

## Password managers

- Password managers store passwords securely.
- They help users create long, random, unique passwords.
- Main benefit:
  - humans do not need to remember every password
  - users can avoid password reuse
  - passwords can be much stronger

- Example:
  - instead of remembering 30 weak passwords, remember one strong master password

- Risks:
  - if the master password is weak, the manager becomes a big target
  - device security still matters

- Good practice:
  - strong master password
  - MFA on password manager account
  - do not reuse master password anywhere else

## Multi-factor authentication

- MFA = multi-factor authentication.
- It means using more than one type of proof to log in.
- Three main factor types:

### Knowledge factor

- Something you know.
- Examples:
  - password
  - PIN
  - security question

- Weakness:
  - can be guessed, stolen, phished, leaked, or reused.

### Possession factor

- Something you have.
- Examples:
  - phone
  - authenticator app
  - hardware security key
  - smart card

- Weakness:
  - phone can be stolen
  - SMS can be attacked with SIM swapping
  - user can approve fake login prompts by mistake

### Inherence factor

- Something you are.
- Examples:
  - fingerprint
  - face scan
  - iris scan

- Weakness:
  - biometric data is difficult to change if compromised
  - sensors can sometimes be fooled
  - still depends on device security

## One-time passwords

- OTP = one-time password.
- It is a temporary code used for login.
- Usually valid only for a short time.
- Examples:
  - SMS code
  - authenticator app code
  - hardware token code

- OTP is usually a possession factor because it proves you have access to a device or token.
- Authenticator app is usually safer than SMS.
- SMS is weaker because of SIM swapping and interception risk.

## SIM swapping

- SIM swapping is when an attacker tricks the mobile provider into moving your phone number to their SIM card.
- Then the attacker receives your SMS messages and verification codes.
- This can break SMS-based MFA.
- Defences:
  - use authenticator app instead of SMS when possible
  - use hardware security key for important accounts
  - add extra security/PIN to mobile provider account
  - watch for sudden loss of phone signal

## Keylogging

- Keylogging is when software or hardware records what a user types.
- It can steal:
  - passwords
  - messages
  - card details
  - search terms

- Example:
  - malware records keystrokes when user logs into a bank account.

- Defences:
  - avoid malware
  - update OS/software
  - use antivirus/EDR
  - use MFA
  - use password managers/passkeys where possible

## Social engineering

- Social engineering attacks the human, not only the technical system.
- The attacker manipulates people into doing something unsafe.
- Examples:
  - giving password
  - clicking malicious link
  - opening attachment
  - transferring money
  - approving login request

- It works because humans are busy, stressed, helpful, scared, curious, or trusting.

## Phishing

- Phishing is a type of social engineering.
- The attacker sends a fake message that looks trusted.
- Goal:
  - steal login details
  - install malware
  - trick user into payment
  - trick user into giving sensitive data

- Examples:
  - fake bank email
  - fake Microsoft login page
  - fake delivery text
  - fake boss message

- Why it is hard to prevent:
  - targets humans directly
  - uses urgency and emotions
  - can look very realistic
  - one user mistake can bypass strong technical systems

- Defences:
  - user training
  - MFA
  - email filtering
  - report suspicious emails
  - check URLs carefully
  - do not trust unexpected attachments/links

## Machine-in-the-middle / on-path attacks

- Machine-in-the-middle means the attacker positions themselves between two communicating parties.
- Better modern term: on-path attacker.
- Example:
  - user connects through compromised Wi-Fi/router
  - attacker can observe or modify traffic

- Risks:
  - stealing credentials
  - redirecting user
  - reading unencrypted traffic
  - modifying data in transit

- Defences:
  - HTTPS/TLS
  - VPN on untrusted networks
  - avoid suspicious Wi-Fi
  - certificate warnings should not be ignored
  - secure router configuration

## Single Sign-On

- SSO = Single Sign-On.
- It lets users log into many services using one identity provider.
- Example:
  - “Sign in with Google”
  - “Sign in with Microsoft”
  - university login used for many systems

- Benefits:
  - fewer passwords to remember
  - easier account management
  - easier to disable access when someone leaves
  - can enforce MFA centrally

- Risk:
  - if the main SSO account is compromised, attacker may access many connected services.

- Good practice:
  - strong password
  - MFA
  - monitor suspicious logins
  - do not use SSO on untrusted websites without thinking

## Passkeys

- Passkeys are a newer login method designed to replace passwords.
- They use public-key cryptography.
- The private key stays on your device.
- The website gets the public key.
- User unlocks the passkey with:
  - fingerprint
  - face scan
  - device PIN

- Benefits:
  - resistant to phishing
  - no password to reuse
  - no password to type
  - harder for attackers to steal through fake login pages

- Important idea:
  - the website does not receive your actual fingerprint/face
  - biometric unlocks the key on your device

## Password usability vs security

- Very complex passwords can be hard for humans to remember.
- If a password is hard to remember, users may:
  - write it down insecurely
  - reuse it
  - use predictable substitutions
  - forget it often

- Good security must consider humans.
- Better approach:
  - long passphrases
  - password managers
  - MFA
  - passkeys
  - rate limiting and lockout
  - security training

## Quick examples

- Brute force:
  - trying every possible PIN/password combination.

- Dictionary attack:
  - trying common passwords and words first.

- Credential stuffing:
  - using leaked login details from one site on another site.

- Phishing:
  - fake email asking user to log in through fake page.

- Keylogging:
  - malware recording what the user types.

- SIM swapping:
  - attacker takes control of victim’s phone number.

- MFA:
  - password + authenticator app.

- SSO:
  - using university/Microsoft/Google login to access multiple services.

- Passkey:
  - logging in with device-held cryptographic key unlocked by fingerprint/PIN.

# Lecture 1

## Hashing - Storing passwords/data

- alice:apple
  easy to read if adversary somehow gets access to database.

- Hashing
  converts input like password into hash value.
  Hash should be one-way, so it should not be reversible.
  It is not encoding and not encryption.

- How attacker checks password
  attacker guesses password, hashes it, and compares result with stolen hash.
  If hashes match, guessed password was correct.

- One-way hash function / cryptographic hash function
  function that produces fixed hash output from input.
  Good hash function should be hard to reverse.

- disadvantage of plain hash
  same password always gives same hash.
  If two users have same password, their hashes will also be same.

- Rainbow Tables
  precomputed tables of passwords and their hashes.
  Helps attacker compare stolen hashes faster.
  Requires a lot of storage and preparation.

- Salting
  salt is random extra value added to password before hashing.
  same password + different salt = different hash.
  This makes rainbow tables much less useful.
  Salt is usually stored together with hash, but password is not stored.

## Encoding / Encryption / Hashing

- Encoding
  changes data format.
  Reversible without secret key.
  Example: Base64.
  Encoding is not security.

- Encryption
  protects data using a key.
  Reversible only with correct key.
  Plaintext -> ciphertext.

- Hashing
  one-way fingerprint of data.
  Not reversible.
  Used for password storage and integrity checks.

## Cryptography

- Cryptography
  science/practice of protecting information.

- Code
  word/symbol/number assigned to a different meaning.

- Encode
  take plaintext/input and produce encoded output.

- Decode
  take encoded output and convert it back to plaintext.

- Cipher
  algorithmic method for encrypting/decrypting message.

- Encipher / Encrypt
  plaintext to ciphertext.

- Decipher / Decrypt
  ciphertext to plaintext.

- Enigma machine
  mechanical cipher machine used by Germany in World War II.

- Key
  secret value used by cipher to encrypt or decrypt data.
  In symmetric encryption, sender and receiver need same secret key.

- Cryptanalysis
  analysing or trying to break cryptography/ciphers.
  Cryptanalyst tries to find weakness in encryption, not just encrypt messages.

## Symmetric-key encryption

- Symmetric-key encryption
  same key is used to encrypt and decrypt.
  Both sides need to know the same secret key.

- problem with symmetric key
  sender and receiver need to share key safely first.
  If connection is not secure, sending the key can be dangerous.

- AES
  modern symmetric encryption standard.

- Triple DES
  older/legacy symmetric encryption method.
  Mostly replaced by AES.

## Public-key encryption

- Public-key encryption
  uses public key and private key.

- Public key
  can be shared with others.
  Others can use it to encrypt message to me.

- Private key
  must stay secret.
  Used to decrypt message encrypted with my public key.

- main idea
  public-key encryption helps solve key sharing problem.
  Someone can send encrypted data to me without first sharing secret key.

- RSA
  public-key algorithm.
  Based on difficulty of factoring large numbers.
  Basic idea: n = p \* q.

- Diffie-Hellman key exchange
  method for two sides to agree on shared secret over insecure channel.
  Basic idea uses maths like A = g^a mod p and B = g^b mod p.

## Digital Signatures

- Digital signature
  used to prove authenticity and integrity of data/document.

- signing
  sender makes hash of document.
  sender uses private key to create signature.

- verifying
  receiver makes hash of received document.
  receiver uses sender public key and signature to check if document matches.

- important rule
  private key signs.
  public key verifies.

- digital signature proves
  document was not changed.
  signature came from holder of private key.

## Passkeys

- Passkeys
  passwordless login method.
  Uses public/private key pair instead of password.

- passkey login
  private key stays on user device.
  website/service stores public key.
  service sends challenge.
  user device signs challenge with private key.
  service verifies using public key.

- main benefit
  password is not typed or sent.
  helps reduce phishing and password reuse problems.

## Encryption in transit vs End-to-End Encryption

- Encryption in Transit
  data is encrypted while travelling between user and server.
  Example: HTTPS.
  Server/service may still be able to read data after it arrives.

- End-to-End Encryption
  data should only be readable by sender and receiver.
  Server/service should not be able to read message content.

- simple difference
  encryption in transit protects data on the way.
  end-to-end encryption protects data from everyone except endpoints.

## Deletion and disk encryption

- Deletion
  deleting file usually removes reference to file.
  Data may still exist on drive until overwritten.

- Secure Deletion
  overwrites data with zeros, ones or random patterns.
  Makes recovery much harder.

- Full-Disk Encryption
  encryption for data at rest.
  Without key/password, data on disk looks random.
  Useful if device is lost or stolen.

## Ransomware

- Ransomware
  malware/extortion attack.
  Attacker encrypts victim data and demands payment.
  Can affect personal devices, companies, servers and services.

- important idea
  encryption itself is not bad.
  ransomware abuses encryption to lock victim data.

## Quantum Computing

- normal bit
  classical computers use bits.
  Bit is 0 or 1.

- qubit
  quantum bit.
  Can be in superposition, not just simple 0 or 1 like normal bit.

- security concern
  powerful quantum computers could break some current public-key cryptography.
  This is why post-quantum cryptography is important for future.
