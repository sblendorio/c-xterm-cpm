### News
Have a look to [**Hangman-CPM**](https://github.com/sblendorio/hangman-cpm), a C game for **CP/M** using XTerm

# XTerm for CP/M

## Description
**XTerm** stands for "Cross-Terminal". It's a **C** library for CP/M.
It handles different kinds of terminals for easy cursor positioning, colors (when available), and screen handling.

## Supported compilers
**XTerm** has been developed with HI-TECH C Compiler, but it has been
written to be also source-level compatible with:

- gcc (all platforms)
- SAS/C 6.58 (for Amiga)

## Supported terminal types
* **VT52** (monochrome, no text effects)
* **VT100** (monochrome)
* **ANSI** (colors)
* **KayPro** (monochrome)
* **ADM-31** (monochrome)
* **C128** (colors)
* **Memotech** (monochrome)
* Amstrad **CPC** 6128 / Zenith Z19 (monochrome)

##Contents of package
- **source** - Source code in **Turbo Modula-2** (Borland)
 - [**xterm.h**](https://github.com/sblendorio/c-xterm-cpm/blob/master/source/xterm.h) - Header file
 - [**xterm.c**](https://github.com/sblendorio/c-xterm-cpm/blob/master/source/xterm.c) - Implementation.
 - [**termtest.c**](https://github.com/sblendorio/c-xterm-cpm/blob/master/source/xterm.c) - Test for main functionalities
