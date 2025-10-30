# Goal

find flag01 password

# Preliminary data

- during previous level we found the hashed password:
  flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash

# Reconnaissance

```
level01@SnowCrash:~$ pwd
/home/user/level01
level01@SnowCrash:~$ ls -al
total 12
dr-x------ 1 level01 level01  100 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level01 level01  220 Apr  3  2012 .bash_logout
-r-x------ 1 level01 level01 3518 Aug 30  2015 .bashrc
-r-x------ 1 level01 level01  675 Apr  3  2012 .profile
level01@SnowCrash:~$
```

files belonging to flag01:

- find / -user flag01 2>/dev/null
- nothing
  files mentionning flag01:
  find / -path /dev -prune -o -exec grep -Hn "flag01" {} \; 2>/dev/null

# Exploitation

On Linux machines passwords are usually stored in /etc/password or /etc/shadow as a SHA-512 hash.
If it is not to complicated we can crack it using John The Ripper tool.

## Installing John

```
wget https://www.openwall.com/john/k/john-1.9.0-jumbo-1.tar.xz
tar -xJf john-1.9.0-jumbo-1.tar.xz
cd john-1.9.0-jumbo-1/src/
./configure && make -s clean && make -sj4
```

## Running John

```
cat 42hDRfypTqqnw > hash
./src/john hash
```

password is abcdefg
flag f2av5il02puano7naaf6adaaf
