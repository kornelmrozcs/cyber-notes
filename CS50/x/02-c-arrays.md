# CS50x - C Basics: Arrays

> Notes from CS50x Week 2. Covers how `make` compiles code (preprocess, compile, assemble, link), compilers and CPU architectures, decompiling, data types and their sizes, arrays, and command-line arguments.

---

## How CS50 `make` compiles your code

`make` is not a compiler. It is a build tool that runs the actual compiler (`clang`) for you with the right flags. A simplified version of what runs under the hood:

```bash
clang -o hello hello.c -lcs50
```

- `-o hello` sets the output file name (the executable).
- `hello.c` is your source code.
- `-lcs50` links the cs50 library (the real CS50 command adds more flags, but this is the core).

Turning `hello.c` into a runnable program happens in four steps:

```
preprocessing  → handles the # lines (#include, #define).
                 #include <stdio.h> is replaced with the actual contents of stdio.h.
                 Output: expanded C source, ready for the compiler.

compiling      → turns the preprocessed C into assembly code.

assembling     → turns assembly into machine code (object files, .o).
                 This is the binary the CPU can actually run.

linking        → combines your object code with the library code
                 (cs50, the C standard library) into one final executable.
```

A common mix-up: linking does not "combine code from preprocessing". It combines your compiled code with precompiled library code. When you write `-lcs50`, the linker pulls in the cs50 library's machine code and stitches it to yours. That is how a call to `get_int` ends up working even though you never wrote it.

### `-l` is not `#include`

These are two different things at two different stages, easy to confuse:

- `#include <cs50.h>` is a preprocessor directive. It brings in the declarations (what functions exist and how to call them).
- `-lcs50` is a linker flag. It brings in the compiled code (what those functions actually do).
- `-I` (capital i) is a third thing: it adds a folder to the search path for header files.

So a header tells the compiler the function exists, and `-l` gives the linker the real implementation. You usually need both.

---

## Compilers, architectures and decompiling

A compiler targets a specific CPU architecture (instruction set):

- x86-64 for Intel and AMD
- ARM for Apple Silicon and most phones

Same C source, different machine code per architecture. That is the point of a compiled language: write once in C, compile a separate binary for each target. It is also why a binary built for Intel does not run natively on Apple Silicon without translation (Rosetta 2 on Mac).

**Your question: is there also a compiler for GPUs?** Yes, but it is a separate world. You do not compile normal C to a GPU. GPU code is written in CUDA (NVIDIA), OpenCL, or Metal (Apple) and compiled with those toolchains. So "different processors need different compilers" is true, but CPU and GPU are different ecosystems, not the same `clang` command.

**Decompiling** is trying to reconstruct higher-level source from a compiled binary. Your instinct was right, it is a form of reverse engineering. Two related but different things:

- Disassembly: binary back to assembly. Reliable, near one-to-one mapping.
- Decompilation: binary back to C-like pseudocode. Lossy. You lose variable names, comments, and the original structure, so the output is readable but not the original source.

Tools: Ghidra, IDA Pro. This matters for the security path, malware analysis and CTF reversing both rely on it.

---

## Data types and sizes

Typical sizes on a 64-bit system (CS50's setup). Not identical on every platform, but safe to assume here.

|Type|Size|Notes|
|---|---|---|
|`bool`|1 byte|only needs 1 bit, but memory is addressed in bytes (see below)|
|`char`|1 byte|one character, stored as its ASCII code|
|`int`|4 bytes|32 bits, signed range about -2.1 billion to +2.1 billion|
|`float`|4 bytes|decimal number, about 6-7 significant digits|
|`long`|8 bytes|bigger whole numbers, needed for things like credit card numbers|
|`double`|8 bytes|decimal number, about 15-16 significant digits, more precise|
|`string`|8 bytes (a pointer)|really the address of the first char, the text itself is length + 1|

**`int` and 2^32.** 4 bytes is 32 bits, which gives 2^32 distinct values (about 4.3 billion). Because `int` is signed (it stores negatives too), that range is split roughly in half: about -2.1 billion to +2.1 billion. A 16-digit card number is far bigger than 2.1 billion, so it does not fit in an `int`. That is why CS50 uses `long` (and `get_long`) for card numbers.

**Why `bool` is 1 byte and not 1 bit.** A bool only carries 1 bit of information (true or false). It still takes a full byte because memory is byte-addressable: the smallest unit the CPU can give an address to is a byte. You cannot point at a single bit. So a standalone bool wastes 7 of its 8 bits. (Inside a struct you can pack bits with bit-fields, but that is a special case.)

**`float` vs `double`.** Both store decimals. The difference is precision: float holds ~7 significant digits, double holds ~16. Use double when precision matters. Neither is exact, because some decimals like 0.1 cannot be represented perfectly in binary. This is why `0.1 + 0.2` does not give exactly `0.3` (Computerphile video in References).

**`string` and the null terminator.** In CS50, `string` is the cs50 library's name for `char *`, a pointer. The `string` variable itself holds an address (8 bytes on a 64-bit system). The actual text is stored as an array of chars ending in a null terminator `\0`. So storing `"cat"` takes 4 bytes:

```
'c'  'a'  't'  '\0'
 1    2    3    4
```

The `\0` marks where the string ends. That is how functions like `strlen` know when to stop counting. You will see the pointer side properly in the pointers week. For now the key point is the +1 byte for the `\0`.

---

## Arrays

An array is a chunk of contiguous memory holding multiple values of the same type. Contiguous means back to back with no gaps.

```c
int scores[3] = {72, 85, 91};
// scores[0] = 72, scores[1] = 85, scores[2] = 91
```

Indexing starts at 0, so `scores[0]` is the first element. Because every element is the same size and laid out in order, the program can jump straight to any index with simple maths (start address + index * element size). That is why array access is fast, and also why C does not stop you from reading `scores[3]` here, it just reads whatever memory sits next, which is a bug waiting to happen.

---

## Command-line arguments: `argc` and `argv`

```c
int main(int argc, string argv[])
```

This lets a program take input from the command line when you run it, the same way `cat file.txt` takes `file.txt`.

- `argc` = argument count. How many arguments were passed, including the program name itself.
- `argv` = argument vector. The array of arguments, each one a string. `argv[0]` is always the program name. `argv[1]` onward are the arguments you typed.

```bash
./greet Kornel
# argc = 2
# argv[0] = "./greet"
# argv[1] = "Kornel"
```

### How this connects to Linux commands

This is the full-circle moment between CS50x and the Bandit / Linux work.

1. **It is the exact same mechanism.** When you type `cat -n file.txt`, the `cat` program receives `argc = 3` and `argv = ["cat", "-n", "file.txt"]`. `cat` reads `argv` to see what you asked for. Every command-line tool works this way. So writing a C program with `argc`/`argv` is building the same kind of tool as `cat`, `ls`, or `grep`.
    
2. **The `-flags` are just a convention.** There is nothing special about `-`. The program looks through `argv`, and if an argument starts with `-`, it chooses to treat it as an option instead of a filename. The shell does not enforce this, the program decides. In C this is usually done with a helper like `getopt` so you do not parse `argv` by hand.
    
3. **The shell and core commands are written in C.** The classic Unix shell and tools (`cat`, `ls`, `grep`, `cp`) are C programs. The commands you use in Bandit are themselves C programs using `argc`/`argv`, exactly what you are learning now. Some modern versions are rewritten in other languages like Rust, but the originals are C.
    

---

## Exercise: Scrabble

Score two words by Scrabble letter values, higher total wins.

Core trick, mapping a letter to its score:

```c
char c = toupper(player[i]);   // normalise case
if (isupper(c))                // skip spaces, digits, punctuation
{
    total += points[c - 'A'];  // 'A'->0, 'B'->1, ... 'Z'->25
}
```

- `letter - 'A'` turns a letter into an array index 0-25
- `toupper()` handles mixed case, `isupper()` keeps only letters
- Compute `strlen` once before the loop, not inside the condition (avoids O(n^2))
- Use `'A'`, not `65`. Same value, reads clearly

---

## Character checks: ctype.h vs manual ranges

Both Scrabble and Readability come down to classifying characters. There are two ways to do it and they are equivalent. `ctype.h` is shorter, the manual range shows what is happening underneath. Both are valid, pick whichever reads clearer.

|ctype.h|manual range (same check)|
|---|---|
|`isupper(c)`|`c >= 'A' && c <= 'Z'`|
|`islower(c)`|`c >= 'a' && c <= 'z'`|
|`isalpha(c)`|`(c >= 'A' && c <= 'Z') \| (c >= 'a' && c <= 'z')`|
|`isdigit(c)`|`c >= '0' && c <= '9'`|
|`isspace(c)`|space, tab, newline ( , `\t`, `\n`)|

```c
// these two lines do exactly the same check
if (isalpha(text[i])) { ... }
if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) { ... }
```

Readability used these to count letters (`isalpha`, or the explicit range), words (`isspace`), and sentences (`.` `!` `?`). The `ctype.h` functions need `#include <ctype.h>`.

---

## Key Takeaways

- The four build steps are preprocess, compile, assemble, link. `make` (clang) runs all four for you
- `-l` links a library (`-lcs50`); it is not the same as `#include`, which is a preprocessor directive
- A compiler targets a CPU architecture, the same C compiles to different machine code for Intel vs Apple Silicon
- `int` is 4 bytes (about -2.1 to +2.1 billion); use `long` when that is too small
- `bool` is 1 byte not 1 bit because memory is addressed in bytes, not bits
- `float` is ~7 significant digits, `double` is ~16; reach for `double` when precision matters
- A string is a char array ending in `\0`, so storing n characters takes n + 1 bytes
- `argc`/`argv` is how a program reads command-line input, the same mechanism `cat` and `grep` use
- Map a letter to an array index with `letter - 'A'` (0-25); normalise with `toupper`, filter with `isupper`
- Character checks two ways: `isalpha`/`isupper`/`isdigit` (ctype.h) equal explicit ASCII range checks, both valid

---

## References

- [CS50x](https://cs50.harvard.edu/x/)
- [CS50x Week 2 Notes](https://cs50.harvard.edu/x/notes/2/)
- [cppreference - arithmetic types and sizes](https://en.cppreference.com/w/c/language/arithmetic_types)
- [cppreference - main function (argc / argv)](https://en.cppreference.com/w/c/language/main_function)
- [Computerphile - Floating Point Numbers](https://www.youtube.com/watch?v=PZRI1IfStY0)
- [Computerphile - Where GREP Came From (Brian Kernighan)](https://www.youtube.com/watch?v=NTfOnGZUZDk)