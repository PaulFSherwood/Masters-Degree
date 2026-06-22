## Day 26 — Bash scripting

Study:

- variables
- arguments
- exit codes
- if statements
- loops
- functions
- traps

Write:

```
linux/system_health.sh
```

It should print:

```
hostname
uptime
disk usage
memory usage
top 5 CPU processes
top 5 memory processes
network addresses
failed systemd services
```

Run ShellCheck:

```
shellcheck linux/system_health.sh
```
