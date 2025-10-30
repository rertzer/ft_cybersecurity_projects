# Goal

find flag02 password

# Reconnaissance

## Lookaround

```
level02@SnowCrash:~$ pwd
/home/user/level02
level02@SnowCrash:~$ ls -al
total 24
dr-x------ 1 level02 level02  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level02 level02  220 Apr  3  2012 .bash_logout
-r-x------ 1 level02 level02 3518 Aug 30  2015 .bashrc
----r--r-- 1 flag02  level02 8302 Aug 30  2015 level02.pcap
-r-x------ 1 level02 level02  675 Apr  3  2012 .profile
level02@SnowCrash:~$ find / -user flag02 2>/dev/null
level02@SnowCrash:~$

```

pcap files are binary files used to store packet captures.

- strings level02.pcap:
- wwwbugs login: @f&NV.
- Password: Nf&Nat
- Login incorrect
- wwwbugs login: df&N

It is possible that we can find some credentials in it.

We can further investigate using Wireshark

1. download locally
   scp -P 6666 level02@localhost:level02.pcap .
   chmod 666 level02.pcap
2. run Wireshark - the file correspond to a capture of a TCP connection between 59.233.235.218 and 59.233.235.223 who started the 20 july 2011 at 7:23:12 and lasted 42 seconds.
   We can retrieve the exchange wiht (right clic=>Follow=>TCP)

```
..wwwbugs login: l.le.ev.ve.el.lX.X
..
Password: ft_wandr...NDRel.L0L
Login incorrect
```

Knowing that dots correspond to backslashes we can recontstruct:
login: levelX
password: ft_waNDReL0L

# Exploitation

As the login levelX is incorrect or perhaps he mixed up the password, we can try whether the password wouldn't be the flag02 one ... and it is!
flag:kooda2puivaav1idi4f57q8iq
