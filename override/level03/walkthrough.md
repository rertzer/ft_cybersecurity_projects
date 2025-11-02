# Level 03

We still have a program asking for a password:
```sh
$ ./level03
***********************************
*               level03         **
***********************************
Password:42

Invalid Password
```

Decompiling the code, we find a "decrypt()" function performing an operation on each character with the "^=" operator, which is a bitwise XOR.

The variable enabling this offset comes from the "test()" function, which runs decrypt with arguments subtracted from each other, only if the result of this subtraction is between 1 and 21, otherwise the value used for the offset is random. And the variables used in this subtraction come from main, one is retrieved by scanf and the other is 322424845.


Let's start by finding the necessary offset. I'm only going to look at the first character as it doesn't change. The first of the ciphered line is Q and we're looking for a C.
```sh
$ python -c "print ord('Q') ^ ord('C')"
18
```

Now we want:
322424845 - x = 18
x = 322424845 - 18
x = 322424827

We have our password, let's finish:
```sh
$ ./level03
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
```