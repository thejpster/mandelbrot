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

### (2) GCC for Linux

On Arm Debian I used `gcc version 12.2.0 (Raspbian 12.2.0-14+rpi1)`.

On x86-64 Pop OS! I used `gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04)`

Either way I ran:

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

### (5) GCC for SPARC Solaris

I used `gcc 3.4.3` on Solaris 7 for SPARC.

```console
$ gcc -O3 -o mandel mandel.c -mcpu=v9
$ ./mandel
```

This particular C compiler produced 32-bit SPARC ELF files. I wasn't able to get it to produce 64-bit SPARC ELF code.

### (6) GCC for PA-RISC HP-UX

I used `gcc 3.2` on HP-UX 11.00 for PA-RISC.

```console
$ gcc -O3 -o mandel mandel.c
$ ./mandel
```

This particular C compiler produced 64-bit PA-RISC 2.0 ELF files.

### (7) GCC for NEXTSTEP 3.3

I used `cc-437.2.6, gcc version 2.5.8` from the NEXTSTEP 3.3 Developer CD. When ran it on an HP 9000 712/60 it produced PA-RISC 1.1 Mach-O files. When I ran it on a SPARCstation 20 it produced SPARC Mach-O files.

```console
hp712> cc -O3 -o mandel mandel.c
hp712> ./mandel
```

### (8) DEC C V5.2-030 for Digital UNIX V4.0

```console
alpha> cc -fast -o mandel mandel.c
alpha> ./mandel
```

This compiler produced a 64-bit Alpha ECOFF file.

### (9) HP ANSI C

```console
$ cc -Ae mandel.c -O -lm
$ ./a.out
```

This compiler produced a `PA-RISC 1.1 shared executable`. Some hacking on the `time.h` file was required as I was unable to work out precisely what (if any) predefined macros HP ANSI C defined such that I could identify it.

## Benchmarks

The benchmark is relatively short on fast machines, and there's a lot of noise. They are really just to give you an order-of-magnitude difference between systems.

| Machine                | CPU                              | OS                | Compilation | kPixels Per Second | Cycles/pixel |
| ---------------------- | -------------------------------- | ----------------- | ----------- | ------------------ | ------------ |
| HP Z1 Entry Tower G5   | Intel Core i9-9900 CPU @ 3.10GHz | Pop OS! 22.04     | 2           | 6675               | 464          |
| MacBook M1 Pro         | Apple M1 Pro @ 3.2 GHz           | macOS 15.1        | 3           | 6230               | 513          |
| HP Z1 Entry Tower G5   | Intel Core i9-9900 CPU @ 3.10GHz | Windows 11 x64    | 1           | 5693               | 544          |
| Raspberry Pi 5         | Arm Cortex-A76 @ 2.4 GHz         | Debian Linux 12.8 | 2           | 5300               | 452          |
| Raspberry Pi 4         | Arm Cortex-A72 @ 1.8 GHz         | Debian Linux 12.8 | 2           | 1783               | 1009         |
| HP Visualize C3000     | HP PA-RISC 8500 @ 400 MHz        | HP-UX 11.00       | 6           | 534                | 749          |
| Sun Ultra 80           | UltraSPARC II @ 450 MHz          | Solaris 7         | 5           | 421                | 1068         |
| DEC 3000 Model 800 AXP | DEC Alpha 21064 @ 200 MHz        | Digital UNIX V4.0 | 8           | 95                 | 2105         |
| SGI POWER Indigo 2     | MIPS R8000 @ 75 MHz              | IRIX 6.2          | 4           | 57.2               | 1311         |
| Sun SPARCstation 20    | SuperSPARC-II @ 60 MHz           | NEXTSTEP 3.3      | 7           | 51.4               | 1167         |
| HP 9000 712            | HP PA-RISC 7100LC @ 60 MHz       | NEXTSTEP 3.3      | 7           | 49.3               | 1217         |
| Sun SPARCstation 5     | microSPARC-II @ 110 MHz          | Solaris 2.6       | 5           | 47.6               | 2310         |
| HP 9000 705            | HP PA-RISC 7000 @ 35 MHz         | HP-UX 9.0         | 9           | 24.7               | 1417         |

Notes:

* On the MacBook M1 Pro you have to run it a few times in a row to get the CPU to ramp up to maximum performance.
* Some of these systems have multiple processors, or multiple cores within a processor, or multiple hardware threads within a core. This benchmark is strictly single-threaded though.
* Some of these systems have variable clock frequencies, and so for 'Cycles/pixel' we've assumed the system is running at its nominal clock speed, which might be wrong.
