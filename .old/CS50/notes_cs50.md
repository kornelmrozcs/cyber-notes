CS50x Notes

- includes
  - stdio.h gives access to printf
  - cs50.h gives access to get_int, get_long etc

- get_int
  - asks user for integer input

- get_long
  - asks user for long number input
  - useful for credit card numbers because int is too small

- printf
  - prints output to terminal

- do while
  - runs at least once
  - useful for asking input until it is valid

- for loop
  - repeats code fixed number of times
  - useful when I know how many rows/chars I want

- nested loops
  - loop inside another loop
  - outer loop usually controls rows
  - inner loop usually controls characters inside row

- Mario pyramid
  - x = user height
  - i = current row
  - j = character counter inside row
  - spaces = x - i - 1
  - hashes = j <= i or j < i + 1
  - row logic: spaces, left hashes, gap, right hashes, new line

- function prototype
  - tells compiler that function exists before main uses it
  - example idea: void builder(int x);
  - useful when function is written below main

- void function
  - function does something but returns nothing

- custom function
  - useful to split program into smaller parts
  - each function should ideally do one clear job

- modulo %
  - gives remainder
  - number % 10 gives last digit

- integer division /
  - with whole numbers it removes decimal part
  - number / 10 removes last digit

- Credit task
  - use Luhn’s algorithm to check if card number is valid
  - then check length and starting digits to find provider

- Luhn’s algorithm
  - start from second-to-last digit
  - multiply every other digit by 2
  - add digits of those products
  - add digits that were not multiplied
  - if total % 10 == 0 then checksum is valid

- Credit card providers
  - AMEX starts with 34 or 37 and has 15 digits
  - Mastercard starts with 51-55 and has 16 digits
  - Visa starts with 4 and has 13 or 16 digits

- digit counting
  - repeatedly divide number by 10
  - count how many times until number becomes 0

- extracting digits
  - number % 10 gets last digit
  - number / 10 removes last digit
  - this lets me process number from right to left

- my Credit solution notes
  - good: I used modulo and division correctly
  - good: I split some logic into functions
  - good: I understood Luhn instead of only copying
  - improve: function check_valid_provider does too many things
  - improve: better split Luhn check and provider check
  - improve: use clearer names like digit_count instead of amount
  - improve: remove debug comments before final submit
