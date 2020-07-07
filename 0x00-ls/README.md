### ls
Custom implementation of the `ls` command.

#### Installation
Install using GCC on an Ubuntu system.
```
$ gcc -Wall -Werror -Wextra -pedantic *.c -o ls
```
#### Usage
Available options:
- `-l` prints each file in long format
- `-1` prints one file per line
- `-a` prints entries starting with `.`
- `-A` same as `-a` but ignores the `.` and `..` entries

Accepts multiple options at once, e.g.:
```
$ ./ls -lA
```
In a directory containing two files, `.test` and `test.c`, the above command should output:
```
-rw-rw-r-- 1 mp mp 0 Jul 6 11:52:46 2020 .test
-rw-rw-r-- 1 mp mp 0 Jul 6 11:54:00 2020 test.c
```
