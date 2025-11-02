# Level 13 - LD_PRELOAD

## The challenge:

In the current directory there is an executable named level13 owned by flag13 with the setuid/setgid bits set.
The program ask to be run under user_id 4242

```sh
level13@SnowCrash:~$ ls -al
total 20
dr-x------ 1 level13 level13  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level13 level13  220 Apr  3  2012 .bash_logout
-r-x------ 1 level13 level13 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
-r-x------ 1 level13 level13  675 Apr  3  2012 .profile
level13@SnowCrash:~$ ./level13
UID 2013 started us but we we expect 4242
level13@SnowCrash:~$
```

## Decompile the code:

level 13 use the lib function getuid() to retrieve the user id and compares it to the value 4242 (0x192). The token it returned if the uid match.

```c
int32_t main(int32_t argc, char** argv, char** envp)
{
    if (getuid() == 0x1092)
    {
        return printf("your token is %s\n", ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"));
    }
    printf("UID %d started us but we we expe…", getuid(), 0x1092);
    exit(1);
    /* no return */
}
```

## First hack:

Use gdb to change the value getuid() returned.

The line of interest is :

```gdb
0x0804859a <+14>: 3d 92 10 00 00 cmp $0x1092,%eax
```

gdb commands:

```gdb
b *0x804859a
run
set $eax=0x1092
continue
```

## Second hack:

getuid() is dynamically linked at run time. We can force level13 to use our own getuid() with the LD_PRELOAD env variable.

LD_PRELOAD allow to set libraries in which the linker search for library functions prior to any other.

The executable and the library needs to be in the same directory.

```sh
$ cp level13 /tmp/
$ cd /tmp
$ vim getuid_level13.c
$ gcc -shared -o libhack.so getuid_13.c
$ LD_PRELOAD=./libhack.so ./level13
```
