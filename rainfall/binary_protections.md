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
- `CONFIG_DEVKMEM`: determines whether `/dev/kmem` is created on boot
- `CONFIG_DEVMEM`: determines whether `/dev/mem` is created on boot
- `CONFIG_STRICT_DEVMEM`: if `/dev/mem` exists, determines whether access to it is restricted

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

# System-wide ASLR (kernel.randomize_va_space

## Address Space Layout Randomization (ASLR)

- ASLR is a security protection aimed to prevent memory corruption vulnerabilities.
- It provides random addresses for the heap, the stack and shared libraries. Sometimes the code base address is randomized too.
- Code segment randomization require that the code is compiled as position-independent code (PIE).
- This make it harder for an attacker to predict their target addresses.
- Each run of the program has a different memory layout.
- The default Linux kernel ASLR shifts values with a random multiple of the page size (typically 4 kb).

## `randomize_va_space`

- By default, Linux randomizes the address space of all programs when they start.
- setting `proc/sys/kernel/randomize_va_space` to `0` disable this feature.

# References

- [Stack Smashing Protector](https://wiki.osdev.org/Stack_Smashing_Protector)
- [Code Injection Via /dev/mem](https://blackhat.com/presentations/bh-europe-09/Lineberry/BlackHat-Europe-2009-Lineberry-code-injection-via-dev-mem.pdf)
- [Checksec](https://medium.com/@slimm609/checksec-d4131dff0fca)
- [Debug Strict User Copy](https://cateee.net/lkddb/web-lkddb/DEBUG_STRICT_USER_COPY_CHECKS.html)
- [Hardened User Copy](https://medium.com/@boutnaru/the-linux-security-journey-hardened-user-copy-f637f2eca69e)
- [Grsecurity](https://en.wikibooks.org/wiki/Grsecurity/Overview)
- [KERNHEAP](https://phrack.org/issues/66/15)
- [ASLR](https://securitymaven.medium.com/demystifying-aslr-understanding-exploiting-and-defending-against-memory-randomization-4dd8fe648345)
- [Linux Kernel ASLR](https://xorl.wordpress.com/2011/01/16/linux-kernel-aslr-implementation/)
