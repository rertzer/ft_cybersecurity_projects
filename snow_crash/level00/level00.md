# level00 - Ave Casear

## General Reconnaissance

### Operating System

- The SnowCrash machine is an Ubuntu Linux operating system.
- The kernel is 32-bit with Physical Address Extension.

```sh
level00@SnowCrash:~$ uname -a
Linux SnowCrash 3.2.0-89-generic-pae #127-Ubuntu SMP Tue Jul 28 09:52:21 UTC 2015 i686 i686 i386 GNU/Linux
```

### File System:

- We don't have any access to the root folder.
- We don't have read rights to the home directory.
- The selinux folder is empty.
- The rofs directory is a read only copy of the file system, probably to get an immutable system image.

```sh
level00@SnowCrash:~$ ls -al /
total 2
drwxr-xr-x  1 root root  240 Oct 29 10:16 .
drwxr-xr-x  1 root root  240 Oct 29 10:16 ..
drwxr-xr-x  2 root root 2814 Mar  9  2016 bin
drwxr-xr-x  1 root root   60 Aug 30  2015 boot
dr-xr-xr-x  7 root root 2048 Mar 12  2016 cdrom
drwxr-xr-x 15 root root 4040 Oct 29 10:16 dev
drwxr-xr-x  1 root root  260 Oct 29 10:16 etc
d--x--x--x  1 root root   80 Aug 30  2015 home
lrwxrwxrwx  1 root root   37 Aug 29  2015 initrd.img -> /boot/initrd.img-3.2.0-89-generic-pae
drwxr-xr-x 23 root root 1436 Aug 30  2015 lib
drwxr-xr-x  1 root root   60 Mar 12  2016 media
drwxr-xr-x  2 root root    3 Mar 12  2016 mnt
drwxr-xr-x  1 root root   60 Oct 29 10:16 opt
dr-xr-xr-x 83 root root    0 Oct 29 10:16 proc
drwxrwxrwx 21 root root  364 Mar 12  2016 rofs
drwx------  5 root root  165 Mar 12  2016 root
drwxr-xr-x 14 root root  540 Oct 29 11:57 run
drwxr-xr-x  2 root root 3469 Aug 30  2015 sbin
drwxr-xr-x  2 root root    3 Mar  5  2012 selinux
drwxr-xr-x  2 root root    3 Aug 29  2015 srv
drwxr-xr-x 13 root root    0 Oct 29 10:16 sys
d-wx-wx-wx  4 root root   80 Oct 29 13:08 tmp
drwxr-xr-x  1 root root   80 Aug 29  2015 usr
drwxr-xr-x  1 root root  160 Mar 12  2016 var
lrwxrwxrwx  1 root root   33 Aug 29  2015 vmlinuz -> boot/vmlinuz-3.2.0-89-generic-pae
```

### Home Sweet `home`

- By default we do not have write rights on our home.
- Our home contains only default configuration files.

```sh
level00@SnowCrash:~$ pwd
/home/user/level00
level00@SnowCrash:~$ ls -al
total 12
dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
-r-xr-x---+ 1 level00 level00 3518 Aug 30  2015 .bashrc
level00@SnowCrash:~$ getfacl .
# file: .
# owner: level00
# group: level00
user::r-x
user:level00:r-x
group::---
mask::r-x
other::---
default:user::r-x
default:user:level00:r-x
default:group::---
default:mask::r-x
default:other::---
-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
```

## Looking For `flag00`

### `/etc/passwd`

- As we have access to the /etc directory, we try to access to the passwords files in order to gather data on the `flag00` user.

```sh
level00@SnowCrash:~$ ls -al /etc/passwd
-rw-r--r-- 1 root root 2477 Mar  5  2016 /etc/passwd
level00@SnowCrash:~$ ls -al /etc/shadow
-rw-r----- 1 root shadow 4428 Mar  6  2016 /etc/shadow
level00@SnowCrash:~$ .
```

- We have read rights to `/etc/passwd` but not to `/etc/shadow` (which contains the hashed passwords).
- The `passwd` file contains the following lines:

```sh
level00:x:2000:2000::/home/user/level00:/bin/bash
level01:x:2001:2001::/home/user/level01:/bin/bash
level02:x:2002:2002::/home/user/level02:/bin/bash
level03:x:2003:2003::/home/user/level03:/bin/bash
level04:x:2004:2004::/home/user/level04:/bin/bash
level05:x:2005:2005::/home/user/level05:/bin/bash
level06:x:2006:2006::/home/user/level06:/bin/bash
level07:x:2007:2007::/home/user/level07:/bin/bash
level08:x:2008:2008::/home/user/level08:/bin/bash
level09:x:2009:2009::/home/user/level09:/bin/bash
level10:x:2010:2010::/home/user/level10:/bin/bash
level11:x:2011:2011::/home/user/level11:/bin/bash
level12:x:2012:2012::/home/user/level12:/bin/bash
level13:x:2013:2013::/home/user/level13:/bin/bash
level14:x:2014:2014::/home/user/level14:/bin/bash
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
flag04:x:3004:3004::/home/flag/flag04:/bin/bash
flag05:x:3005:3005::/home/flag/flag05:/bin/bash
flag06:x:3006:3006::/home/flag/flag06:/bin/bash
flag07:x:3007:3007::/home/flag/flag07:/bin/bash
flag08:x:3008:3008::/home/flag/flag08:/bin/bash
flag09:x:3009:3009::/home/flag/flag09:/bin/bash
flag10:x:3010:3010::/home/flag/flag10:/bin/bash
flag11:x:3011:3011::/home/flag/flag11:/bin/bash
flag12:x:3012:3012::/home/flag/flag12:/bin/bash
flag13:x:3013:3013::/home/flag/flag13:/bin/bash
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
```

- We learn that `flag00` home is `/home/flag/flag00`.
  > Notice that an hashed password is stored for `flag01`. This information will be usefull at the next level.

### No Direction `home`

- We can't read `flag00` home's content and will have to find another way to gather informations.

```sh
level00@SnowCrash:~$ ls -al /home/flag/flag00
ls: cannot open directory /home/flag/flag00: Permission denied
```

### Finding `flag00`

- We are now looking for any file related to `flag00` user, or containing the `flag00` string.

```sh
level00@SnowCrash:~$ find / -user flag00 2>/dev/null
/usr/sbin/john
/rofs/usr/sbin/john
level00@SnowCrash:~$ ls -al /usr/sbin/john
----r--r-- 1 flag00 flag00 15 Mar  5  2016 /usr/sbin/john
level00@SnowCrash:~$ file /usr/sbin/john
/usr/sbin/john: ASCII text
cat /usr/sbin/john
cdiidwpgswtgt
find / -path /dev -prune -o -exec grep -Hn "flag00" {} \; 2>/dev/null
...
```

- We found a file belonging to `flag00` which contains this mysterious string: `ciidwpgswtgt`
- The search for files containing the string `flag00` didn't provide any extra information.

### Ave Caesar

- Our working hypothesis is that the string found in the `john` file could be the `flag00` password, but it didn't work.
- It could be that the string is encrypted.
- We then check for common basic encryption using [CacheSleuth](https://www.cachesleuth.com/multidecoder/), an online tool.
- It appears that the string is Rot15 encrypted (a Caesear cypher).
- The decoded string is: `nottohardhere`.

## Getflag

- Using `nottohardhere` as a password, we manage to connect as `flag00` and launch the `getflag` command, retrieving the flag.

- `flag00` password: `nottoohardhere`
- `level01` password (flag): `x24ti5gi3x0ol2eh4esiuxias`

`        `[<= Previous](../snow_crash.md)`                                                   `[Next =>](../level01/level01.md)
