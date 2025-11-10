# GCC Stack Protector Support

- A stack-smashing protection using canaries.
- Emits extra code to check for buffer overflows.
- Adds a guard variable initialized when a function is entered and checked when the function exits.
- If a guard check fails, an error message is printed and the program exits.

## gcc flags:

- `-fstack-protector`: Protects functions calling `alloca` and functions with buffers larger than 8 bytes.
- `-fstack-protector-all`: The same as `-fstack-protector` except that all functions are protected.
- `-fstack-protector-strong`: A compromise between the two previous options.
- `-Wstack-protector`: Gives warning for all non-protected function.

# Restrict access to `/dev/mem` and `/dev/kmem`

- `/dev/mem` and `/dev/kmem` are character devices allowing a direct access to physically addressable memory.
- `/dev/mem` provides access to the physical memory of a running system.
- `/dev/kmem provides` access to kernel virtual memory.
- It is possible to disable those character devices through kernel configuration options.
  - `CONFIG_DEVKMEM`: Determines whether `/dev/kmem` is created on boot.
  - `CONFIG_DEVMEM`: Determines whether `/dev/mem` is created on boot.
  - `CONFIG_STRICT_DEVMEM`: If `/dev/mem` exists, determines whether access to it is restricted.

# Stack Canary

- A stack canary is a random value placed on the stack below the frame pointers in such a way that a buffer overflow attempt will overwrite it.
- Prior to a function return, the canary is compared to a reference value stored somewhere else in the process memory. If they do not match, the program exits immeadiately.
- The canary value changes at each program run.

## Linux gcc Implementation

- On a 32-bit architecture, the canary ist 4 bytes long. 3 bytes hold a random number provided by the `execve()` system call (a 16 bytes random number is put above the argument and environment strings), and the least significant byte is replaced by 0.
- This 0 byte works as a terminator. The idee is that most functions diverted to perform a buffer overflow will stop when writing a null byte. The attacker will therefore be unable to mimic a 0 byte containing canary.
- `- stack-protector`: Default option. Enable the canary protection.
- `-fno-stack-protector`: Option to disable the canary protection.

# Strict User Copy Check

- Strict user copy check is a Linux kernel configuration option.
- It is used to harden memory copies between user and kernel space.
- If enabled, it performs sanity checks at compilation time focussing on strcpy(), memcpy() functions families.
- Those tests focusses on the length argument of the copy function, by having gcc prove that the argument is within bounds.

# Grsecurity

- Grsecurity is a set of patches for the Linux kernel designed to strenghten security.
- It includes the PaX kernel patch and implements a wide range of security mechanisms including a Role-based Access Control.

# KERNHEAP

- KERNHEAP is a set of kernel protections preventing heap overflows in the kernel space.

# System-wide ASLR (kernel.randomize_va_space)

## Address Space Layout Randomization (ASLR)

- ASLR is a security protection aimed to prevent memory corruption vulnerabilities.
- It provides random addresses for the heap, the stack and shared libraries. Sometimes the code base address is randomized too.
- Code segment randomization requires that the code is compiled as position-independent code (PIE).
- This makes it harder for an attacker to predict their target addresses.
- Each run of the program has a different memory layout.
- The default Linux kernel ASLR shifts values with a random multiple of the page size (typically 4 kb).

## `kernel.randomize_va_space`

- By default, Linux randomizes the address space of all programs when they start.
- Setting `proc/sys/kernel/randomize_va_space` to `0` disable this feature.

# Relocation Read-Only (RELRO)

- ELF files uses a lookup table, the Global Offset Table (GOT), to dynamically resolve functions.
- The GOT is writable by default.
- RELRO makes the GOT read-only, preventing some attacks.
- The Linker needs then to resolve all dynamically linked functions at the beginning of execution, before the table is marked as read-only.
- RELRO also reorder the ELF internal data sections to protect them from of a buffer-overflow.
- RELRO could be partial or full. Partial RELRO sets only the non-PLT part of the GOT as read-only. A full RELRO marks the whole GOT as read-only.

## GCC Flags

- `-Wl,-z,relro`: partial RELRO
- `-Wl,-z,relro,-z,now`: full RELRO

# Dynamic Linkage

- To dynamically resolve functions located in shared libraries, an ELF binary uses two tables, the Global Offset Table (GOT) and the Procedure Linkage Table (TLB).
- A call to a shared library function points to the TLB which itself jumps to an address stored in the corresponding GOT entry.
- The GOT table is populated dynamically. When a function is called for the first time, the GOT points by default back to the PLT to the instruction following the JMP instruction. The dynamic linker is then called by the PLT code in order to find the actual location of the function.
- This location is then written to the GOT.
- The next time the function is called, the GOT hold the shared library function address. The function is directly called.
- Dynamic linkage helps to allow Position Independent Code (PIC), which addresses changes at each run, and can't therefore be hard coded at compilation time.

## Global Offset Table (GOT)

- The GOT is an ELF file section (`.got` and `.got.plt`). It is writable but non-executable.
- It maps symbols (global variable and shared library functions) to their absolute memory addresses.
- GOT allows shared libraries (`.so`) to be relocated to a different memory address at startup.
- It is represented as `.got` and `.got.plt` sections in the ELF file.
- The GOT needs to be located at a known fixed address.
- As the GOT is writable, it may be exploited by an attacker.

## Procedure Linkage Table (PLT)

- The Procedure Linkage Table is a non-writable executable section (`.plt`).
- It converts position-independent function calls to absolute locations.
- Each entry in the PLT correspond to a `JMP` instruction to the corresponding GOT entry.
- The PLT needs to be set at a fixed offset from the `.text` section.

# References

- [Stack Smashing Protector](https://wiki.osdev.org/Stack_Smashing_Protector)
- [Stack Canaries](https://cseweb.ucsd.edu/~efernandes/teaching/res/how-canaries-work.pdf)
- [Code Injection Via /dev/mem](https://blackhat.com/presentations/bh-europe-09/Lineberry/BlackHat-Europe-2009-Lineberry-code-injection-via-dev-mem.pdf)
- [Checksec](https://medium.com/@slimm609/checksec-d4131dff0fca)
- [Debug Strict User Copy](https://cateee.net/lkddb/web-lkddb/DEBUG_STRICT_USER_COPY_CHECKS.html)
- [Hardened User Copy](https://medium.com/@boutnaru/the-linux-security-journey-hardened-user-copy-f637f2eca69e)
- [Grsecurity](https://en.wikibooks.org/wiki/Grsecurity/Overview)
- [KERNHEAP](https://phrack.org/issues/66/15)
- [ASLR](https://securitymaven.medium.com/demystifying-aslr-understanding-exploiting-and-defending-against-memory-randomization-4dd8fe648345)
- [Linux Kernel ASLR](https://xorl.wordpress.com/2011/01/16/linux-kernel-aslr-implementation/)
- [RELRO](https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro)
- [PIC, GOT and PLT (video)](https://www.youtube.com/watch?v=Ss2e6JauS0Y)
