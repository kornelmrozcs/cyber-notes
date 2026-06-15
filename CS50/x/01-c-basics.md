# CS50x — C Basics: Loops, Functions and Algorithms

> Notes from CS50x. Covers the building blocks you need before tackling problem sets — input/output, loops, functions, how to pull digits out of a number, and how greedy algorithms think.

---

## Headers and libraries

```c
#include <stdio.h>   // printf
#include <cs50.h>    // get_int, get_long, get_string
```

`stdio.h` is standard C. `cs50.h` is a course helper that wraps input functions so you do not have to deal with `scanf` right away. Worth knowing that in real C you would handle input yourself — but for now it keeps things clean.

---

## Input and output

```c
printf("Hello, world\n");
printf("Number: %i\n", 42);
printf("Long: %li\n", 1234567890L);

int n     = get_int("Enter a number: ");
long card = get_long("Card number: ");
```

Format specifiers to remember: `%i` for int, `%li` for long, `%f` for float, `%s` for string.

One thing that caught me early — using `int` for a credit card number does not work. An `int` maxes out around 2 billion, and card numbers have 13–16 digits. You need `long`.

---

## Loops

Three types, each with a specific use case. Knowing which one to reach for matters more than it seems at first.

### for

Use when you know in advance how many iterations you need.

```c
for (int i = 0; i < height; i++)
{
    printf("#\n");
}
```

### while

Use when you are waiting for a condition to become false. Number of iterations is not known upfront.

```c
int i = 0;
while (i < height)
{
    printf("#\n");
    i++;
}
```

### do while

Use for input validation. The body runs at least once — you need to ask the question before you can check whether the answer is acceptable.

```c
int n;
do
{
    n = get_int("Enter a positive number: ");
}
while (n <= 0);
```

This is the one I kept getting wrong early on. The instinct is to use `while`, but then you have to initialise `n` to some dummy value just to get into the loop. `do while` is cleaner here.

### Nested loops — the Mario pyramid

A good exercise for building intuition about how nested loops interact.

```c
int x = get_int("Height: ");

for (int i = 0; i < x; i++)
{
    for (int j = 0; j < x - i - 1; j++)
        printf(" ");

    for (int j = 0; j <= i; j++)
        printf("#");

    printf("\n");
}
```

Output for height 4:

```
   #
  ##
 ###
####
```

The outer loop controls which row you are on. The two inner loops handle spaces and hashes separately. Row `i` gets `x - i - 1` spaces and `i + 1` hashes. Writing it out on paper first helps a lot.

---

## Functions

### Prototypes

A prototype declares that a function exists before `main` sees it. Without one, the compiler complains when it hits a call to a function it has not seen yet.

```c
// prototypes at the top
int count_digits(long n);
void print_row(int width);

int main(void)
{
    // both functions usable here
}

// actual definitions below
int count_digits(long n) { ... }
void print_row(int width) { ... }
```

The pattern I use: prototypes at the top, `main` in the middle, everything else below. Keeps `main` readable at a glance.

### void functions

When a function does something but does not need to return a value.

```c
void print_row(int hashes)
{
    for (int i = 0; i < hashes; i++)
        printf("#");
    printf("\n");
}
```

A rule worth following: one function, one job. If you find yourself writing a function that validates input _and_ prints results _and_ calculates something — split it.

---

## Digit manipulation

This is the core mechanic behind several CS50 tasks. Two operations, used together in a loop.

```c
int last_digit = n % 10;   // remainder = last digit
n = n / 10;                 // integer division = remove last digit
```

```
1234 % 10 = 4      → last digit is 4
1234 / 10 = 123    → shift right, 4 is gone
123  / 10 = 12
12   / 10 = 1
1    / 10 = 0      → nothing left, loop ends
```

### Walking through a number digit by digit

```c
while (n > 0)
{
    int digit = n % 10;
    // do something with digit
    n /= 10;
}
```

This processes digits from right to left. If you need left to right, you either count digits first and use powers of 10, or reverse the order after. Right to left is usually enough.

### Counting digits

```c
int count_digits(long n)
{
    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}
```

---

## Luhn's algorithm

Used in the Credit problem set to validate whether a card number is plausible before checking the provider. The algorithm was designed so that a single digit transcription error almost always produces an invalid result.

How it works at a high level:

1. Starting from the **second-to-last** digit, take every other digit and double it.
2. If doubling gives you a number greater than 9, add its two digits together (which is the same as subtracting 9).
3. Sum those results.
4. Add to that sum all the digits you did **not** double, starting from the last digit.
5. If the total ends in zero — the number is valid.

The digit manipulation tools above (`% 10` and `/ 10`) are exactly what you need to implement this. Think about how to track position as you walk through the number right to left, and how to handle the case where doubling a digit gives you a two-digit result.

I am not including the full implementation here — working through it yourself is the point.

---

## Greedy algorithms

A greedy algorithm always makes the locally optimal choice at each step. It takes the biggest possible "bite" out of the problem, then the next biggest, and so on.

The CS50 example is giving change with the fewest coins possible.

```c
int greedy(int amount)
{
    int coins = 0;

    while (amount >= 25) { amount -= 25; coins++; }
    while (amount >= 10) { amount -= 10; coins++; }
    while (amount >= 5)  { amount -= 5;  coins++; }
    while (amount >= 1)  { amount -= 1;  coins++; }

    return coins;
}
```

Start with quarters, take as many as fit, move to dimes, and so on. Each loop is one denomination.

**Why this works here but not everywhere.** US coin denominations (25, 10, 5, 1) happen to have a mathematical property that makes greedy always produce the optimal result. If the denominations were different — say 1, 3, 4 — greedy would fail. Targeting 6 cents, greedy picks 4+1+1 (3 coins). The optimal is 3+3 (2 coins). For those cases you need dynamic programming instead.

Greedy is fast and simple when it applies. The hard part is knowing whether it actually applies to your problem.

---

## Key Takeaways

- Use `do while` for input validation — it is cleaner than faking an initial value to get into a `while` loop
- `% 10` and `/ 10` together let you walk any number digit by digit from right to left
- Prototypes let you organise your file so `main` stays at the top and readable
- Greedy algorithms work by always taking the best immediate option — but this only produces the globally optimal result for certain problem types
- `get_long` is not optional for credit card numbers — `int` is too small

---

## References

- [CS50x](https://cs50.harvard.edu/x/)
- [Luhn algorithm — Wikipedia](https://en.wikipedia.org/wiki/Luhn_algorithm)
- [Greedy algorithm — Wikipedia](https://en.wikipedia.org/wiki/Greedy_algorithm)
