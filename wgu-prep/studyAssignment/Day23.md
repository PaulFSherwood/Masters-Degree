## Day 23 — Text processing

Study:

- `cat`, `less`, `head`, `tail`
- `grep`
- `awk`
- `sed`
- pipes
- redirects

Lab:

```
journalctl --no-pager | grep -i error | head
ps aux | awk '{print $1}' | sort | uniq -c | sort -nr | head
```

Write:

```
linux/log_summary.sh
```
