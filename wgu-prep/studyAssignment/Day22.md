## Day 22 — Files, permissions, users

Study:

- `ls`, `find`, `stat`
- `chmod`, `chown`
- users/groups
- octal permissions
- sticky bit
- setuid/setgid

From memory:

```
Explain 755, 644, 700, 600, 4755.
```

Lab:

```
mkdir linux/lab-permissions
touch a.txt script.sh
chmod 644 a.txt
chmod 755 script.sh
stat script.sh
```
