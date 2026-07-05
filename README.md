# myhexdump
This is my implementation of hexdump, for learning and hobby only.

```sh
➜  gcc -Wall -Wextra -o myhexdump myhexdump.c
```

```sh
➜  echo "Hello World, Hiago De Franco, Hello :)" | ./myhexdump
00000000  48 65 6c 6c 6f 20 57 6f  72 6c 64 2c 20 48 69 61 |Hello World, Hia|
00000010  67 6f 20 44 65 20 46 72  61 6e 63 6f 2c 20 48 65 |go De Franco, He|
00000020  6c 6c 6f 20 3a 29 0a                             |llo :).         |
00000027
```
