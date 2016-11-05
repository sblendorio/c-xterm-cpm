#ifndef _XTERM_H
#define _XTERM_H

#define INVALID  0
#define VT52     1
#define VT100    2
#define ANSI     3
#define KAYPRO   4
#define ADM31    5
#define C128     6
#define MEMOTECH 7
#define CPC      8
#define LAST     9

#define PLAIN       0
#define REVERSE     1
#define BLINK       2
#define NOBLINK     3
#define UNDERLINE   4
#define NOUNDERLINE 5
#define DARK        6
#define NODARK      7
#define CLS         8
#define HOME        9
#define CLREOL      10
#define INSLINE     11
#define DELLINE     12
#define BEEP        13
#define CURSORON    14
#define CURSOROFF   15
#define TERMRESET   16
#define BLACK       17
#define WHITE       18
#define RED         19
#define CYAN        20
#define PURPLE      21
#define GREEN       22
#define BLUE        23
#define YELLOW      24
#define DARKPURPLE  25
#define BROWN       26
#define LIGHTRED    27
#define DARKCYAN    28
#define DARKGREY    29
#define LIGHTGREEN  30
#define LIGHTBLUE   31
#define LIGHTGREY   32
#define LAST_STRINGSEQ 33

#define bool int
#define true 1
#define false 0

extern char *SEQ[LAST_STRINGSEQ];
extern void (*CursorXY)(int x, int y);
extern bool HasColors;

int String2TermType(char *name);
int GetTermType(void);
void SetTermType(int t);
void PrintTermType(int t);
void PrintLnTermType(int t);
void PrintTermTypeList(void);
void AskTermType(int argc, char *argv[]);
void ResetTerm(void);

void ClrScr(void);
void Home(void);
void InsLine(void);
void DelLine(void);
void ClrEol(void);
void ShowCursor(void);
void HideCursor(void);
void PlotBox(int x1, int y1, int x2, int y2, bool h, bool v);
void Center(int y, char *s);
int ReadChar(void);
bool InputCardinal(int x, int y, int *pNumber, int l);

void RandomizeShuffle(void);

#endif
