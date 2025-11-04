# Level 14 - Traceme If You Can

## Hacking `getflag`

0. Well, last level. It's time to be serious and straightforward. So why not hack the `getfalg` directly?
1. To do this, we upload `getflag`,

```sh
$ scp -P 6666 level14@localhost:/bin/getflag .
```

2. and revert it on [dogbolt.com](https://dogbolt.com).

```c
if (eax_9 != 0xbc6)         //0xbc6 == 3014
{
    goto label_8048e29;
}
fputs(ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrv…"), stdout);
```

3. 0xbc6 (3014) is `flag14` uid.

```console
level14@SnowCrash:~$ id flag14
uid=3014(flag14) gid=3014(flag14) groups=3014(flag14),1001(flag)
```

4. By changing the `eax_9` value directly at run time, using gdb, we could bypbass the test and let `getflag` provide us the flag.

5. But `getflag` is protected against such kind of trick.

```c
 if (ptrace(PTRACE_TRACEME, 0, 1, 0, 0) < 0)
    {
        puts("You should not reverse this");
        eax_3 = 1;
    }
```

### gdb and ptrace

- `gdb` uses `ptrace` to track the program to debug.
- `gdb` do a fork and the child process use `ptrace(PTRACE_TRACEME...)` to be traced by the parent process (`gdb`).
- the child process then execute the program to debug (here `getflag`).
- When `getflag` run again `ptrace(PTRACE_TRACEME...)`, the function returns an error value as it is already traced.

6. That protection can also be bypassed by changing the register value at run time.

### gdb commands

```gdb
catch syscall ptrace
commands 1
set ($eax) = 0
continue
end

b *0x8048b02 (break one step after getuid call)
run
p $eax (= 2014) (user level14)
set $eax=3014 (set to flag14)
continue
```

> It has not escapted our notice that this hack could have been used for all previous levels.

# Flag

- final flag: `7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ`

<p align="center"><a href="../level13/level13.md"><= Previous</a></p>
