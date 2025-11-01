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
