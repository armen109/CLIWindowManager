# CLI Window Manager

A simple **Command Line Interface (CLI)** program to manage windows, tables, texts, and buttons in a hierarchical layout.

---

## Features

- Create windows, tables, texts, and buttons.
- Only windows can have child objects.
- Child objects must fit inside the parent window and cannot overlap.
- Print the full object hierarchy showing IDs, types, parent IDs, positions, and sizes.
- Interactive CLI with commands to manage your objects.

---

## Commands

add_window <id> <rowCount> <colCount> [parentWindowId=-1] [row=-1] [col=-1]
add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>
add_text <id> <text> <parentWindowId> <row> <col>
add_button <id> <text> <parentWindowId> <row> <col>
printAll
break


- `printAll` → Prints the hierarchy of all objects.
- `break` → Exits the program.

**Notes:**
- Only windows can have children.
- Child objects must be inside the bounds of the parent window.
- Children cannot occupy the same `(row, col)` position.

---

## Build Instructions

1. Open a terminal in the project folder.
2. Compile the program using:
```bash
make
