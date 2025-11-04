# level 07

## The Code

- We have to enter a login string and a serial number.
- If a series of complicated calculations done on login gives serial, the authentication is granted.

## The Hack

- The code was copied/pasted into another program on our local computer and `printf` added in order to print the computed value to whom serial will be compared.
- Entering a login (`rototo`) prints the expected serial (6232795).
- We just have to enter those values in the real `level07` program.

```console
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: rototo
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial:  6232795
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
