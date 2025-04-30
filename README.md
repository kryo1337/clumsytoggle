# Clumsy Toggle

A lightweight Windows utility to toggle Clumsy's Start/Stop button with Alt key.

## Features
- Toggle Clumsy's Start/Stop button with Alt key
- Works globally (no focus needed)
- Supports Clumsy 0.2 and 0.3

## Requirements
- Windows 10/11
- Clumsy 0.2 or 0.3
- Run both as admin

## Usage
1. Run Clumsy as admin
2. Run `clumsytoggle.exe` as admin
3. Press Alt to toggle

Exit with Ctrl+C

## Build
```bash
gcc -o clumsytoggle.exe clumsytoggle.c -luser32
```