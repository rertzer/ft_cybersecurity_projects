# Level 0

```console
	  _____       _       ______    _ _
	 |  __ \     (_)     |  ____|  | | |
	 | |__) |__ _ _ _ __ | |__ __ _| | |
	 |  _  /  _` | | '_ \|  __/ _` | | |
	 | | \ \ (_| | | | | | | | (_| | | |
	 |_|  \_\__,_|_|_| |_|_|  \__,_|_|_|

                 Good luck & Have fun

  To start, ssh with level0/level0 on 10.0.2.15:4242
level0@localhost's password:
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/user/level0/level0
```

## Enabled Binary Protections

- We can find a `./level0` executable at the root of the user root owned by `level1`.
- It is statically linked.

```console
$ ls -l
total 732
-rwsr-x---+ 1 level1 users 747441 Mar  6  2016 level0

$ ldd ./level0
	not a dynamic executable
```

- We can decompile it with Ghidra.

```c
TODO: Ghidra
```

- We can see that `./level0` gives access to a shell as `level1` if the first argument is equal to 423.

```console
$ whoami
level0
$ ./level0 423
$ whoami
level1
$ cd ../level1
$ cat .pass
```
