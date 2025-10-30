```
level06@SnowCrash:~$ pwd
/home/user/level06
level06@SnowCrash:~$ ls -al
total 24
dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
-r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
-r-x------  1 level06 level06  675 Apr  3  2012 .profile
level06@SnowCrash:~$ getfacl .
# file: .
# owner: level06
# group: level06
user::r-x
user:flag06:r-x
group::---
mask::r-x
other::---
default:user::r-x
default:user:flag06:r-x
default:group::---
default:mask::r-x
default:other::---

level06@SnowCrash:~$ getfacl level06
# file: level06
# owner: flag06
# group: level06
# flags: s--
user::rwx
group::---
group:level06:r-x
mask::r-x
other::---

```

strings -a level06
...
strdup
setresgid
setresuid
execve
getegid
geteuid
...
fr/usr/bin/php
/home/user/level06/level06.php
...

We may supposte that level06 will allow us to run level06.php as flag06.

```
level06@SnowCrash:~$ php -v
PHP 5.3.10-1ubuntu3.19 with Suhosin-Patch (cli) (built: Jul  2 2015 15:05:54)
Copyright (c) 1997-2012 The PHP Group
Zend Engine v2.3.0, Copyright (c) 1998-2012 Zend Technologies
```

#!/usr/bin/php

<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>

program receive 2 arguments a1 and a2

transmitted to function $x as y and $z

content of file $y is stored in variable $a

first regex result will be executable (/e)

1. first regex

a pattern like `[x SOMETHING ]` will be replaced by `y("SOMETHING")`.
As y is a function, if `SOMETHING` is like `${SOMETHING}`, it will be
executed by the y function and we will get the `SOMETHING` string, as long as it do not contain and `.` nor `@`.

first regex:
according to pattern
regex pattern "/(\[x (.\*)\])/e"
a will be replaced by "y(\"\\2\")"
input like:

y function is then called with the string SOMETHING as parameter

next regex:
"/\./", " x ", dots are replaced by " x "
next regex: @ are replaced by " y"

/e will allow to execute the parsed string

we want it to be exec(getflag)

next regex: [ replaced by (
next regex: ] replaced by )
wiok45aaoguiboiki2tuin6ub
https://wiki.php.net/rfc/remove_preg_replace_eval_modifier
https://stackoverflow.com/questions/65024562/how-can-e-regex-expression-be-misused-on-a-php-code-snippet-running-on-my-ser
