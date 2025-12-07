# Codeforces Solutions Archive

> Archive of Codeforces contest solutions — accepted submissions, drafts, and experiments from rated and unrated rounds. Organized by contest for quick reference and revision.

## About

This repository contains my Codeforces contest solutions organized by contest folder. Each contest folder includes problem source files (typically named `A.cpp`, `B.cpp`, etc.), variations (`E1.cpp`, `E2.cpp`), and any notes or experimental code I used while solving problems.

The collection is intended as a study archive for revision, practice, and reference.

## Repository layout

- `CR<contest_number>/` — a folder for each contest. Example:
  - `CR1068d2/`
    - `A.cpp`, `B.cpp`, `C.cpp`, ...
  - `CR1069d2/`
    - `A.cpp`, `B.cpp`, `C.cpp`, `E1.cpp`, `E2.cpp`, ...

Files are generally named by problem letter. When there are multiple attempts or versions, numeric suffixes (e.g. `E1.cpp`, `E2.cpp`) indicate separate attempts/variants.

## How to use

- To find a solution, open the corresponding contest folder and the problem source file (e.g. `CR1068d2/A.cpp`).
- Each file is a standalone C++ source file you can compile and run locally.

### Compile & run (PowerShell / Windows)

Compile a single file:

```powershell
g++ -std=gnu++17 -O2 -pipe .\CR1068d2\A.cpp -o .\CR1068d2\A.exe
.\CR1068d2\A.exe
```

Compile all C++ files in a contest folder (PowerShell):

```powershell
Get-ChildItem -Path .\CR1068d2 -Filter "*.cpp" | ForEach-Object {
  $src = $_.FullName
  $out = Join-Path $_.DirectoryName ($_.BaseName + ".exe")
  g++ -std=gnu++17 -O2 -pipe $src -o $out
}
```

Notes:
- Use a recent `g++` (GNU C++ 17 or later) for best compatibility with common contest code.
- Many solutions read from stdin and write to stdout. Provide input via file redirection if needed: `.\A.exe < input.txt`.

## Contributing / Adding new solutions

- Add new contest folders named consistently (for example `CR1070d1/`).
- Name solution files by problem letter (`A.cpp`, `B.cpp`, ...). Use suffixes (`E1.cpp`, `E2.cpp`) for multiple versions.
- Keep accepted/clean solutions and experimental drafts separate by filename — do not delete earlier drafts unless you mean to.

If you'd like, open a pull request with improvements or organization suggestions.


