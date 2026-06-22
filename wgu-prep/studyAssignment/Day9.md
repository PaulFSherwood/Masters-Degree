## Day 9 — Syntax, grammar, parsing

Study:

- Tokens
- Lexing
- Parsing
- Grammar
- Context-free grammar
- AST
- Ambiguity
- Operator precedence

Write a grammar:

```
expr   -> term ((+ | -) term)*
term   -> factor ((* | /) factor)*
factor -> NUMBER | "(" expr ")"
```

Build:

```
# Tiny expression parser:
# input: "2 + 3 * 4"
# output: AST
```


