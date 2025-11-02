# Snow Crash

Snow Crash is a introductory project to cybersecurity from the 42 school. It aims to make us discover, through several little challenges, cybersecurity in various fields.

It takes the form of a virtual machine to which you log in as user level00. Solving each problem will provide you with the password for the next higher-level user, up to level14.

## Connection to Snow Crash

- It is recommended to connect to the SnowCrash VM via ssh on port 4242.
- As port 4242 is already used on the school computers, use port forwarding
- On Virtual Box: settings=>network=>advanced=>port forwarding and add a new rule.
  [Port Forwarding](VM_port_forwarding.png)
- starting credentials:
  - user: level00
  - password: level00
- command:`ssh level00@localhost -p6666`

## Instructions

- At each level, you will have to catch the flag, which is also the password for the next level user account.
- Flags will be displayed by running the `getflag` command as flagXX user (XX being your current user level).
- Your goal is then to gain flagXX user rights.

## 14 Shades of Hack

0. [level00 - Ave Caesar](level00/level00.md)
1. [level01 - Meeting John](level01/level.01md)
2. [level02- Wireshark](level02/level02.md)
3. [level03 - PATH Way To The Flag](level03/level03.md)
4. [level04 - Hack Perl](level04/level04.md)
5. [level05 - Daily Mail](level05/level05.md)
6. [level06 - Irregular Expression](level06/level06.md)
7. [level07 - Flag On Command](level07/level07.md)
8. [level08 - This Is Not A Token](level08/level08.md)
9. [level09 - f4kmm6p|=�p�n��DB�Du{��](level09/level09.md)
10. [level10 - You TOCTOU Me?](level10/level10.md)
11. [level11 - Lua ? Erf nope..](level11/level11.md)
12. [level12 - A FILE NAMED HACK ](level12/level12.md)
13. [level13 - LD_PRELOAD](level13/level13.md)
14. [level14 - Traceme If You Can](level14/level14.md)
