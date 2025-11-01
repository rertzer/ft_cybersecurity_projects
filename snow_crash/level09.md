# Level 09

## Token

- Our folder contains the usual executable `level09` and a `token` file.

```sh
$ ls -l
total 12
-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09 level09   26 Mar  5  2016 token
```

- This time we can read the content of `token` but... it does not help..

```sh
$ cat token
f4kmm6p|=�p�n��DB�Du{��
```

## Encryption

- By decompiling the `level09` executable we understand that the returned value is encrypted with a progressive shift. The first letter have a shift of 0, the second of +1, the third of +2...

```sh
$ scp -P 4243 level09@localhost:/home/user/level09/token .
$ chmod +r ./token
```

## Decryption

- We can get the token on our pc and execute our script who's doing the reverse process. The first letter have a shift of 0, the second of -1, the third of -2...

```sh
$ c++ level09/ressources/level09_decrypt.cpp -o decode
$ ./decode ./token
f3iji1ju5yuevaus41q1afiuq
```

# Flag

- `flag` password: `f3iji1ju5yuevaus41q1afiuq`
- `level10` password: `s5cAJpM8ev6XHw998pRWG728z`
