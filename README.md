
# Tree

This is my own implementation of the [Tree](https://en.wikipedia.org/wiki/Tree_(command)) command in C and Python!


The main goal of this repository is to showcase a memory-efficient implementation of the command that does
not use any recursion to find the underlying files and subdirectories. Naturally, it is not meant to be an extensive implementation that covers all use cases, but it still provides depth control and can flexibly adjust the working directory.


## Demo

![Demo](https://raw.githubusercontent.com/RafaelAmauri/Projects/master/demos/tree.gif)


## Installation

No need to install anything!

This implementation works by only using standard libraries in both C and Python. The C version uses [LibGCC](https://gcc.gnu.org/onlinedocs/gccint/Libgcc.html) from the GNU project to run, and was made with Linux in mind!

### Running  (C Version)

```bash
  gcc tree.c -o tree
  ./tree
```


### Running  (Python Version)

```bash
  python3 tree.py [-h] [-d DIRECTORY] [-maxdepth MAXDEPTH]
```