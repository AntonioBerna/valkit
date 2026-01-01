# valkit

![GitHub License](https://img.shields.io/github/license/AntonioBerna/valkit)
![Docker Image Size](https://img.shields.io/docker/image-size/antonioberna/valkit)
![GitHub Created At](https://img.shields.io/github/created-at/antonioberna/valkit)

## Why?

1. Extend `valgrind` usage to macOS users.
2. Support **amd64 (x86_64)** and **arm64** architectures.
3. Resolve incompatibility issues between Manjaro and Arch Linux regarding `glibc`.

## Overview

When I started working on this project, I had to solve a simple incompatibility issue between Manjaro and Arch Linux regarding the `glibc` library. This was because while developing C code, I needed to use the `valgrind` tool on Manjaro.

Now, I decided to extend the project to use this tool on operating systems not based strictly on the Linux kernel and with architectures other than the classic **x86_64**.

Specifically, I added support for the **arm64** architecture, meaning all users with $M_x$ MacBooks (with $x \in \{ 1, \dots, 5, \dots, n \}$) can effectively use `valgrind` when writing C code.

## Usage

### Download

#### Docker Hub

You need to download my docker image from the `Docker Hub` registry using the following command:

```bash
docker pull antonioberna/valkit
```

#### Build from Source

Use the following command to clone the repository:

```bash
git clone https://github.com/AntonioBerna/valkit.git
```

### Uninstall

If you want to remove the image from your machine, you can use the following command:

```bash
docker rmi antonioberna/valkit
```

## Basic Commands

In the `examples/` directory there are various examples to test Valgrind in a Docker environment.

The basic commands that can be used are the following:

```bash
# memcheck
docker run --rm -v $(pwd):/app antonioberna/valkit \
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out

# memcheck with Makefile
docker run --rm -v $(pwd):/app antonioberna/valkit \
bash -c "make && valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out"

# helgrind
docker run --rm -v $(pwd):/app antonioberna/valkit valgrind \
--tool=helgrind ./a.out

# helgrind with Makefile
docker run --rm -v $(pwd):/app antonioberna/valkit \
bash -c "make && valgrind --tool=helgrind ./a.out"
```

## Bonus

### Build multi-arch Docker image

The following command builds and pushes a **multi-architecture Docker image** for both **x86_64 (amd64)** and **arm64** platforms:

```bash
docker buildx build --platform linux/amd64,linux/arm64 -t antonioberna/valkit --push .
```

### Initial Project Purpose

Lately I'm having problems with the Valgrind tool.
In particular because the version of `glibc` of Linux Manjaro is not the same as that of [Arch Linux](https://archlinux.org/packages/extra/x86_64/valgrind/), namely:

```bash
$ pacman -Q glibc
glibc 2.40+r66+g7d4b6bcae91f-1
```

> [!NOTE]
> The link above refers to `valgrind` package. See dependencies and click on `glibc` package to see the version.

the `valgrind` tool generates the following error:

```
valgrind:  Fatal error at startup: a function redirection
valgrind:  which is mandatory for this platform-tool combination
valgrind:  cannot be set up.  Details of the redirection are:
valgrind:  
valgrind:  A must-be-redirected function
valgrind:  whose name matches the pattern:      strcmp
valgrind:  in an object with soname matching:   ld-linux-x86-64.so.2
valgrind:  was not found whilst processing
valgrind:  symbols from the object with soname: ld-linux-x86-64.so.2
valgrind:  
valgrind:  Possible fixes: (1, short term): install glibc's debuginfo
valgrind:  package on this machine.  (2, longer term): ask the packagers
valgrind:  for your Linux distribution to please in future ship a non-
valgrind:  stripped ld.so (or whatever the dynamic linker .so is called)
valgrind:  that exports the above-named function using the standard
valgrind:  calling conventions for this platform.  The package you need
valgrind:  to install for fix (1) is called
valgrind:  
valgrind:    On Debian, Ubuntu:                 libc6-dbg
valgrind:    On SuSE, openSuSE, Fedora, RHEL:   glibc-debuginfo
valgrind:  
valgrind:  Note that if you are debugging a 32 bit process on a
valgrind:  64 bit system, you will need a corresponding 32 bit debuginfo
valgrind:  package (e.g. libc6-dbg:i386).
valgrind:  
valgrind:  Cannot continue -- exiting now.  Sorry.
```

For this reason I decided to create a Docker image that allows me to easily use the Valgrind tool, thus solving every problem.

> [!NOTE]
> I also opened an issue on [Manjaro forums](https://forum.manjaro.org/t/valgrind-missing-strcmp/173648) and the only alternative is to use a different operating system than Manjaro. So I said to myself: why not use Docker directly? And so it was.
