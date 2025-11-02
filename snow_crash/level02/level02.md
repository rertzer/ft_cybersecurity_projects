# level02 - Wireshark

## Our Home

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

- We found in our home (`level02`) a file belonging to `flag02` on which we have read rights.
- pcap files are binary files used to store packet captures.
- Those files can be read using tools like Wireshark.

- whith a `strings level02.pcap` command, we retrieved the following lines:
  - `wwwbugs login: @f&NV.`
  - `Password: Nf&Nat`
  - `Login incorrect`
  - `wwwbugs login: df&N`
- We can then expect to retrieve some credentials by further invastigating the `level02.pcap` file.
- For this, we first upload the file on our computer with the following command: `scp -P 6666 level02@localhost:level02.pcap` and get read/wirte rights on it: `chmod 644 level02.pcap`

## Wireshark

- Running Wireshark, we find out that the file correspond to a capture of a TCP connection between 59.233.235.218 and 59.233.235.223 who started the 20 july 2011 at 7:23:12 and lasted for 42 seconds.
  ![Wireshark](wireshark_1.png)
- We can retrieve the exchange with: right clic=>Follow=>TCP
  ![Follow TCP](wireshark_2.png)

- Knowing that dots correspond to backslashes we can recontstruct:
  - login: levelX
  - Password: ft_waNDReL0L
- Even if the login `levelX` is not `flag02`, as it is indicated as incorrect, we may hope that it is in fact `flag02`.

# Getflag

- The password found allowed us to connect as `flag02` and to retrive the flag with the `getflag` command.
- flag02 password: `ft_waNDReL0L`
- level03 password (flag): `kooda2puivaav1idi4f57q8iq`
