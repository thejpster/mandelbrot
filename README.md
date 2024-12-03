# mandelbrot

> Some mandelbrot benchmarks for the PCs I own.

I have a collection of weird and wonderful computers, and I thought it would be interesting to benchmark them. 
The [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set) seemed like a suitable non-trivial but relatively easy to port problem.
So here in this repo, there is a program which can general an image of the Mandelbrot set, along with the results of running it on some of my computers.

## Source

The code code came from <https://rosettacode.org/wiki/Mandelbrot_set#C>. I've modified it to compile on a wide range of C compilers and platforms.

## Compilation

### (1) Visual Studio 2022

I used Visual Studio 2022 Community Edition, which came with *Microsoft (R) C/C++ Optimizing Compiler Version 19.42.34433 for x86*.

```console
C:\Mandel> CL /O2 mandel.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.42.34433 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

mandel.c
Microsoft (R) Incremental Linker Version 14.42.34433.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:mandel.exe
mandel.obj

C:\Mandel> mandel
Ran at 5693 kpixels per second

C:\Mandel> magick output.ppm -normalize output.png
```

### (2) GCC 12.2 for Linux

I used `gcc version 12.2.0 (Raspbian 12.2.0-14+rpi1)`.

```console
user@host:~/mandelbrot $ gcc -O3 mandel.c -o mandel
user@host:~/mandelbrot $ ./mandel
```

### (3) clang 16 for macOS

I used `Apple clang version 16.0.0 (clang-1600.0.26.4)`.

```console
user@host:~/mandelbrot $ cc -O3 mandel.c -o mandel
user@host:~/mandelbrot $ ./mandel
```

### (4) MIPSpro for IRIX

I used `MIPSpro ANSI C 6.2` on IRIX 6.2.

```console
% cc -O3 -o mandel mandel.c
% ./mandel
```

Because it was compiled on an R8000 machine, the C compiler produced a 64-bit executable using MIPS IV instructions.

## Benchmarks

The benchmark is relatively short on fast machines, and there's a lot of noise. They are really just to give you an order-of-magnitude difference between systems.

| Machine              | CPU                              | OS                | Compilation | kPixels Per Second |
| -------------------- | -------------------------------- | ----------------- | ----------- | ------------------ |
| HP Z1 Entry Tower G5 | Intel Core i9-9900 CPU @ 3.10GHz | Windows 11 x64    | 1           | 5693               |
| Raspberry Pi 4       | Arm Cortex-A72 @ 1.8 GHz         | Debian Linux 12.8 | 2           | 1783               |
| MacBook M1 Pro       | Apple M1 Pro @ 3.2 GHz           | macOS 15.1        | 3           | 6230               |
| SGI POWER Indigo 2   | MIPS R8000                       | IRIX 6.2          | 4           | 57                 |

On the MacBook M1 Pro you have to run it a few times in a row to get the CPU to ramp up to maximum performance.
