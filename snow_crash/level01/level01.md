# level01 - Meeting John

## Summary of Previous Level

- During the previous level we found a hashed password stored in `/etc/password` for user `flag01`:

```
  flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

- `flag01` hashed password: `42hDRfypTqqnw`

## Empty Home

- Our home contains no interesting information.
- Searching for files related to `flag01` didn't provide any suplementary information.
- We will then go forward exploiting the hashed password.

## John The Reapper

- On Linux machines passwords are usually stored in `/etc/password` or `/etc/shadow` as a `SHA-512` hash.
- If the password isn't to complicated it can be cracked using a tool like John The Ripper.

### Installing John

```
wget https://www.openwall.com/john/k/john-1.9.0-jumbo-1.tar.xz
tar -xJf john-1.9.0-jumbo-1.tar.xz
cd john-1.9.0-jumbo-1/src/
./configure && make -s clean && make -sj4
```

### Running John

```
cat 42hDRfypTqqnw > hash
./src/john hash
```

- password is `abcdefg`

## Getflag

- Using the found password, we manage to connect as `flag01` and run the `getflag` command.
- `flag01` password: `abcdefg`
- `level02` password (flag): `f2av5il02puano7naaf6adaaf`

<p align="center"><a href="../level00/level00.md"><= Previous</a>&ensp;&ensp;&ensp;&ensp;<a href="../level02/level02.md">Next =></a></p>
