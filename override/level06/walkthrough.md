# level 07

## the code

We have to enter a login string and a serial number. If a series of complicated calculations done on login gives serial, the authentication is granted.

## the hack

the code was copied/pasted into another program on our local computer and printf added in order to print the computed value to whom serial will be compared.
Entering a login (rototo) print the expected serial (6232795).
We just have to enter those values in the real level07 program.

```sh
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
