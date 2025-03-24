# Clumsy Toggle Utility

This is a lightweight Windows utility that allows you to toggle the "Start" button in Clumsy (versions 0.2 and 0.3) using the Alt key, even when the Clumsy window is not in focus.

## Features
- Toggles Clumsy's "Start" button with the Alt key.
- Works globally, no need to focus on the Clumsy window.
- Supports both Clumsy 0.2 and 0.3.

## Requirements
- Windows operating system (tested on Windows 10/11).
- Clumsy 0.2 or 0.3 installed (download from [jagt/clumsy](https://github.com/jagt/clumsy)).
- Administrator privileges (both Clumsy and this utility must run as admin).

## Usage
1. Download the precompiled `clumsytoggle.exe` from the [Releases](https://github.com/kryo1337/clumsytoggle/releases) page, or build it yourself (see below).
2. Run Clumsy (0.2 or 0.3) as administrator.
3. Run `clumsytoggle.exe` as administrator.
4. Press the Alt key to toggle Clumsy's "Start" button (starts/stops network effects).

To exit the program, close the console window or press Ctrl+C.

### Using MinGW (GCC)
1. Clone the repository:
```bash
git clone https://github.com/kryo1337/clumsytoggle.git
cd clumsy-toggle
```
2. Compile the code:
```bash
gcc -o clumsytoggle.exe clumsytoggle.c -luser32
```