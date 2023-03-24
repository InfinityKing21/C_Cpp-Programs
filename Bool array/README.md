# vector_bool
**vector_bool** is an attempt at recreating the functionality offered by `std::vector<bool>` in C++, in the C language. <br />
This implementation uses a dynamic unsigned integer array to track boolean values and by default grows and shrinks by the size of an `unsigned int`.
To keep things simple, any non-zero value is treated as `true`, and zero is treated as `false`.

## Basic fuctionality offered:
  - initialize_vector() : initializes the boolean vector
  - destruct_vector() : to clean up the vector after use
  - get() : get value at index
  - set() : set value at index
  - push_back() : insert a new boolean value
  - pop_back() : remove a value from the back
  
## Important Note
Despite starting this project over a year ago, it had been postponed indefinitely and has been completed only recently. At present, this project is only
for demonstration and lacks thorough testing (testers and fixes are welcome).
  
## Usage
This project was compiled and linked using gcc (GCC) 12.2.1 20230201 on a linux environment[^1]. <br />
Example using the `main.c` file provided:
```
gcc -std=c17 -Wall -c bool_arr.c main.c
gcc -std=c17 -Wall bool_arr.o main.o -o program
./program
```
  
## Project Motivation
I started this project a year ago when I used to get coding assignment in C every other week. Frustrated by re-implementing dynamic arrays for my coding assignement,
I ended up with an implementation of a simple `std::vector<int>` which I then used to ease up implementing other data structures and algorithms.
Trying to keep the implementation close to the original source for both personal convenience and as a challenge,
I searched a lot and stumbled upon the fact that [std::vector\<bool\> uses one bit of space per bool rather than a byte](https://stackoverflow.com/questions/17794569/why-isnt-vectorbool-a-stl-container).
After that I took this project up as a challenge to determine if I was capable of implementing it.

## References
[Bit mainpulation](https://stackoverflow.com/questions/47981/how-do-i-set-clear-and-toggle-a-single-bit)
  
[^1]: I hope not to be `bashed` for using linux and linux/GNU interchangeably.
