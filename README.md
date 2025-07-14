#  Asmulator - Assembly Language Simulator

A simple yet powerful tool that simulates how an assembler processes code into machine-level output.  
This project was created as part of my academic studies in computer engineering.

----

##  Features

- Full support for `.as` and `.am` files
- Two-pass assembler implementation
- Handles macros, symbols, and label resolution
- Generates output files: `.ob`, `.ent`, `.ext`
- Detects syntax and semantic errors
- Modular architecture: easy to navigate and debug

---
## 📂 Project Structure

main.c → Main entry point
first_pass.c → First scan to gather symbols and macros
second_pass.c → Resolves instructions and addresses
label_table.c → Symbol table handling
macro expansion → Pre-processing macros (.am → .as)
output generation → Writing final machine code and metadata
tests/*.as → Input test files for validation

## Educational Goals
Understand how two-pass assembly works,
Practice memory management in C,
Gain experience building compilers and preprocessors,



