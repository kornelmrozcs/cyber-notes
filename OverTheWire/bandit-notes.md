OverTheWire Bandit Notes

Level 0 -> 1

- ssh bandit.labs.overthewire.org -p 2220 -l bandit1
- ls
- cat readme
- ssh connects to a remote Linux server.
- ls lists files and folders.
- cat shows the content of a file.

Level 1 -> 2

- Problem: File was named "-"
- Wrong command: cat -
- Correct command: cat ./-
- Correct command: cat -- "name"
- What I learned: ./ means current directory, and "-" can be treated as stdin by commands.

Level 2 -> 3

- Same as about use ./
- I tried " "
- but problem with - still occurred
- use name\ bla\ bla after words or 'name bla bla'

Level 3 -> 4

- password in hidden file i found it by using find commend
- ls -a can be use also -a for all

Level 4 -> 5

- password in one of files, only one contains human readable data
- to check it I google for the answer the best approach was find ./\*
- find ./\* iterate though all files in directory like ls -a

Level 5 -> 6

- Password file was somewhere under inhere.
- It had to be human-readable, 1033 bytes, and not executable.
- I first checked directory sizes with du, but that was not the right approach.

- find . -type f -size 1033c ! -executable

- du shows disk usage, often for directories.
- ls -al shows hidden files.
- Hidden files start with .
- In ls -l output, no x in permissions means not executable.
- 1033 in ls -l output is file size in bytes.
- file checks whether a file is human-readable/ASCII text.

Level 6 -> 7

- Find a file somewhere on the server.
- File properties:
  - owned by user bandit7
  - owned by group bandit6
  - 33 bytes in size

- I confused -name bandit7 with -user bandit7.
- -name searches by filename.
- -user searches by file owner.
- -group searches by group owner.

- find / -user bandit7 -group bandit6 -size 33c 2>/dev/null

- / means the root of the whole filesystem.
- find can search by owner, group, and size.
- Permission denied is normal when searching the whole system.
- 2>/dev/null hides error messages.
- /etc/bandit_pass contains password files, but I can only read the one I have permission for.

Level 7 -> 8

- Find the password next to the word "millionth" in data.txt.
- grep millionth data.txt

- grep '^millionth' data.txt

- grep 'millionth$' data.txt did not work because $ means end of line.
- The line did not end with millionth; it started with millionth.

- find . -exec grep -H 'millionth' {} \;

- find . searches from the current directory.
- -exec runs a command on every result.
- grep -H searches text and prints the filename.
- {} is replaced by each found file/path.
- \; ends the -exec command.
- -type f would make it search only files.

- grep searches inside files.
- ^ means start of line.
- $ means end of line.
- For this level, grep millionth data.txt was enough.

Level 8 -> 9

- password is the only line of text that occurs only once

- uniq -u file.txt doesnt work as I expected
- uniq only compares neighbouring/adjacent lines.
- data.txt was not sorted, so duplicates were not always next to each other.
- uniq -u data.txt showed many lines because repeated lines were in different places.

- sort data.txt | uniq -u

- sort data.txt puts identical lines next to each other.
- | passes sorted output into uniq.
- uniq -u prints only lines that appear once.

- uniq -c counts adjacent repeated lines.
- uniq -d shows duplicated adjacent lines.
- uniq -D shows all copies of duplicated adjacent lines.
- uniq -f 2 skips first 2 fields, not useful here because each password line is one field.

Level 9 -> 10

- password in one of the few human-readable strings, preceded by several ‘=’ characters

- data.txt behaves like a binary file.
- grep "==" data.txt only said: binary file matches.
- I needed to extract readable strings first.

- strings data.txt | grep '=='

- strings data.txt extracts printable/human-readable strings from the file.
- | passes output to grep.
- grep '==' filters lines containing ==.

- grep may not print lines normally if the file looks binary.
- strings is useful for finding readable text inside binary/non-text files.
- type checks shell command/type, not file type.
- file checks file type.
- sort/uniq was not needed here; that was previous level logic.

Level 10 -> 11

- Password was stored in data.txt encoded with Base64.

- base64 -d data.txt

- base64 encodes/decodes Base64 data.
- -d means decode.
- cat data.txt shows the encoded Base64 string.
- Base64 often ends with = or == padding.
- base64 -i data.txt without -d encodes the text again, so it is not the solution.

- Encoding is not encryption.
- Base64 is reversible representation of data, not a security protection.

Level 11 -> 12

- Password was stored in data.txt using ROT13.
- ROT13 shifts letters by 13 places in the alphabet.
- Example:
  - A becomes N
  - N becomes A
  - a becomes n
  - n becomes a
- cat data.txt showed encoded text.
- Text started with "Gur cnffjbeq vf", which after ROT13 means "The password is".
- Correct command:
- cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'
- Alternative command:
- tr 'A-Za-z' 'N-ZA-Mn-za-m' < data.txt
- tr translates characters from one set to another.
- 'A-Za-z' means all uppercase and lowercase letters.
- 'N-ZA-Mn-za-m' means rotated uppercase and lowercase letters by 13.
- Numbers and symbols are not changed by this command.
- I first tried only changing lowercase or uppercase letters, but ROT13 needs both.
- I tried tr [n-z] [a-m], but it only translated part of lowercase alphabet.
- I tried &&, but && is shell operator, not part of tr character sets.
- I tried redirecting output to first.txt, but got permission denied because I could not write in that directory.
- Important:
  - use quotes around tr character sets.
  - ROT13 is encoding/simple substitution, not real encryption.
- tr [A-MN-Za-mn-z] [N-ZA-Mn-za-m]
