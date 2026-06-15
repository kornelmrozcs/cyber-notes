# CS50x — C Basics: Loops, Functions and Luhn's Algorithm

> Personal notes from CS50x problem sets. Covers input/output in C, loop types, functions, digit manipulation and the Credit task.

---

## Headers and libraries

```c
#include <stdio.h>   // printf
#include <cs50.h>    // get_int, get_long, get_string
```

`stdio.h` is part of the C standard library. `cs50.h` is a helper library provided by the course that simplifies user input.

---

## Input and output

```c
// Output
printf("Hello, world\n");
printf("Number: %i\n", 42);
printf("Long: %li\n", 1234567890L);

// Input (cs50.h)
int n        = get_int("Enter a number: ");
long card    = get_long("Card number: ");
string name  = get_string("Name: ");
```

Common format specifiers: `%i` or `%d` for int, `%li` for long, `%f` for float, `%s` for string.

`get_long` is necessary for credit card numbers. An `int` holds a maximum of around 2 billion. Card numbers have 13–16 digits, which requires a `long`.

---

## Loops

### for — when the number of iterations is known

```c
for (int i = 0; i < height; i++)
{
    printf("#\n");
}
```

### while — check condition before each iteration

```c
int i = 0;
while (i < height)
{
    printf("#\n");
    i++;
}
```

### do while — runs at least once, then checks condition

```c
int n;
do
{
    n = get_int("Enter a positive number: ");
}
while (n <= 0);
```

`do while` is the right choice for input validation. You always need to ask at least once before you can check whether the answer is valid.

### Nested loops — the Mario pyramid

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

Outer loop controls rows. Inner loops control characters within each row. For a pyramid of height 4:

```
   #
  ##
 ###
####
```

Row `i` has `x - i - 1` spaces and `i + 1` hashes.

---

## Functions

### Function prototype

A prototype tells the compiler a function exists before `main` uses it. Without it the compiler does not know what to expect when it encounters the call.

```c
// Prototypes above main
int count_digits(long n);
int luhn_check(long n);

int main(void)
{
    // can call count_digits and luhn_check here
}

// Definitions below main
int count_digits(long n) { ... }
int luhn_check(long n)   { ... }
```

### void functions

A `void` function performs an action and returns nothing.

```c
void print_row(int hashes)
{
    for (int i = 0; i < hashes; i++)
        printf("#");
    printf("\n");
}
```

Each function should do one clearly defined thing. If a function name contains "and", consider splitting it.

---

## Digit manipulation

These two operations are the foundation of working with individual digits in a number.

```c
int last_digit = n % 10;    // modulo: gives the last digit
n = n / 10;                  // integer division: removes the last digit
```

```
1234 % 10  = 4      last digit
1234 / 10  = 123    removed last digit
123  / 10  = 12
12   / 10  = 1
1    / 10  = 0      done
```

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

### Processing digits right to left

```c
while (n > 0)
{
    int digit = n % 10;   // get last digit
    // do something with digit
    n /= 10;               // remove last digit
}
```

---

## The Credit task — Luhn's algorithm

The task is to validate a credit card number using Luhn's algorithm and then identify the card provider.

### Luhn's algorithm

1. Starting from the second-to-last digit, take every other digit and multiply by 2.
2. If any product is greater than 9, add its digits together (or equivalently subtract 9).
3. Sum all the resulting digits.
4. Add the digits that were not multiplied (starting from the last digit).
5. If the total modulo 10 equals 0, the number is valid.

```c
int luhn_check(long card)
{
    int sum = 0;
    int position = 0;

    while (card > 0)
    {
        int digit = card % 10;

        if (position % 2 == 1)   // every other digit from second-to-last
        {
            digit *= 2;
            if (digit > 9)
                digit -= 9;      // same as summing the two digits
        }

        sum += digit;
        card /= 10;
        position++;
    }

    return (sum % 10 == 0);
}
```

### Card provider identification

```c
// get first two digits
long first_two = card;
while (first_two >= 100)
    first_two /= 10;

// get first digit
long first_one = card;
while (first_one >= 10)
    first_one /= 10;
```

| Provider | Starting digits | Length |
|----------|----------------|--------|
| AMEX | 34 or 37 | 15 |
| Mastercard | 51–55 | 16 |
| Visa | 4 | 13 or 16 |

### Notes from my own solution

What I did well: used modulo and integer division correctly, split logic into functions, understood the algorithm rather than copying it.

What to improve next time: `check_valid_provider` was doing too much — separating Luhn validation from provider identification would be cleaner. Variable names like `amount` should be `digit_count`. Debug `printf` statements should be removed before submission.

---

## Key Takeaways

- `do while` is the correct loop for input validation — it always runs at least once
- `n % 10` gives the last digit; `n / 10` removes it — these two together let you walk through any number digit by digit
- Function prototypes allow you to define functions below `main` while still calling them from it
- `get_long` is required for credit card numbers because `int` is too small

---

## References

- [CS50x](https://cs50.harvard.edu/x/)
- [Luhn algorithm — Wikipedia](https://en.wikipedia.org/wiki/Luhn_algorithm)
