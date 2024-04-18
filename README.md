# Lab Assignment 0xA (Lab 10)
##### Implemented by: Will Serface
##### Assigned by: Prof. N. Torosdagli
##### Course: COP3502C.0012
##### Due Date: 18 April 2024

---

## Initial Commit contains Project Files provided by Assignment
- Project Code: [`lab10.c`](./lab10.c)
- Input File: [`dictionary.txt`](./dictionary.txt)

Later Commits implement project structures and functions

---

## Specific Build Instructions

After compiling [`lab10.c`](./lab10.c), the resulting executable is designed to run
using the following inputs.

### Default Mode (No Arguments)

###### Console Command: `lab10.exe`

If the executable is given no arguments upon runtime, it will assume there is a copy of 
the input file named [`dictionary.txt`](./dictionary.txt) in the working directory.
The executable will read its contents, and output the program results to the console.

### Custom Input Mode (1 Argument)

###### Console Command: `lab10.exe "dictionary.txt"`

If the executable is given one argument upon runtime, it will proceed with the input
sequence, but using the name of the file provided by the argument.
The executable will read its contents, and output the program results to the console.