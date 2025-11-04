# Level 00

- We have a binary file asking for a password:

```console
$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:42

Invalid Password!
```

- By decompiling the code we find that the password is recovered by the program using scanf(%d), who transforms the result into an integer.
- Juste below we find that this integer is 5276 (0x149c) and then execute `system("/bin/sh")` if the password matches.

```asm
   0x080484e7 <+83>:    cmp    $0x149c, %eax
```

```console
$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
```

