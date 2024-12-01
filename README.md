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
Ran at 5985 kpixels per second

C:\Mandel> magick output.ppm -normalize output.png
```

## Benchmarks

| Machine              | CPU                                     | OS             | Binary | kPixels Per Second |
| -------------------- | --------------------------------------- | -------------- | ------ | ------------------ |
| HP Z1 Entry Tower G5 | Intel(R) Core(TM) i9-9900 CPU @ 3.10GHz | Windows 11 x64 | 1      | 5693               |
