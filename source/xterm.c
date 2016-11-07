#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef CPM
#include <conio.h>
#else
#ifdef __SASC
#else
#include <unistd.h>
#include <termios.h>
#endif
#endif
#include "xterm.h"

char *SEQ[LAST_STRINGSEQ];
void (*CursorXY)(int x, int y);
bool HasColors;

int Term=ANSI;

void InitWithNoColors(void);
void InitVT100base(void);
void InitVT100(void);
void InitANSI(void);
void InitKayPro(void);
void InitC128(bool withColors);
void InitMemotech(void);
void InitVT52(void);
void InitCPC(void);
void CursorXYVT52(int x, int y);
void CursorXYVT100(int x, int y);
void CursorXYKAYPRO(int x, int y);
void CursorXYMemotech(int x, int y);

int String2TermType(char *name) {
	if (!strcmp(name,"VT52"))
		return VT52;
	else if (!strcmp(name,"VT100"))
		return VT100;
	else if (!strcmp(name,"ANSI"))
		return ANSI;
	else if (!strcmp(name,"KAYPRO"))
		return KAYPRO;
	else if (!strcmp(name,"ADM31"))
		return ADM31;
	else if (!strcmp(name,"C128"))
		return C128;
	else if (!strcmp(name,"MEMOTECH"))
		return MEMOTECH;
	else if (!strcmp(name,"CPC"))
		return CPC;
	else
		return INVALID;
}

void PrintTermType(int t) {
	switch(t) {
		case VT52    : printf("%s","VT52      (B&W)"); break;
		case VT100   : printf("%s","VT100     (B&W)"); break;
		case ANSI    : printf("%s","ANSI      (Color)"); break;
		case KAYPRO  : printf("%s","KayPro    (B&W)"); break;
		case ADM31   : printf("%s","ADM31     (B&W)"); break;
		case C128    : printf("%s","C128      (Color)"); break;
		case MEMOTECH: printf("%s","MEMOTECH  (B&W)"); break;
		case CPC     : printf("%s","CPC / Z19 (B&W)"); break;
		default      : printf("%s","INVALID VALUE");
	}
}

void PrintLnTermType(int t) {
	PrintTermType(t);
	putchar('\n');
}

int GetTermType() {
	return Term;
}

void PrintTermTypeList() {
	int i;
	for (i=INVALID+1; i<LAST; ++i) {
		printf("%d) ",i);
		PrintLnTermType(i);
	}
}

void InitWithNoColors() {
	int i;
	for (i=BLACK; i<=LIGHTGREY; ++i) SEQ[i]="";
}

void CursorXYVT52(int x, int y) {
	printf("\033Y%c%c", y+31, x+31);
}

void CursorXYVT100(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

void CursorXYKAYPRO(int x, int y) {
	printf("\033=%c%c", y+31, x+31);
}

void CursorXYMemotech(int x, int y) {
	printf("\003%c%c", x+31, y+31);
}

void InitVT100base() {
	CursorXY=CursorXYVT100;
	SEQ[REVERSE]="\033[7m";
	SEQ[PLAIN]="\033[27m";
	SEQ[BLINK]="\033[5m";
	SEQ[NOBLINK]="\033[25m";
	SEQ[UNDERLINE]="\033[4m";
	SEQ[NOUNDERLINE]="\033[24m";
	SEQ[DARK]="\033[2m";
	SEQ[NODARK]="\033[22m";
	SEQ[BEEP]="\007";
	SEQ[CLS]="\033[2J\033[H";
	SEQ[HOME]="\033[H";
	SEQ[CLREOL]="\033[K";
	SEQ[INSLINE]="\033[L";
	SEQ[DELLINE]="\033[M";
	SEQ[CURSORON]="\033[?25h";
	SEQ[CURSOROFF]="\033[?25l";
	SEQ[TERMRESET]="\033c";
}

void InitVT100() {
	HasColors=false;
	InitWithNoColors();
	InitVT100base();
}

void InitANSI() {
	HasColors=true;
	InitVT100base();
	SEQ[BLACK]="\033[30m\033[2m";
	SEQ[WHITE]="\033[37m\033[22m";
	SEQ[RED]="\033[31m\033[2m";
	SEQ[CYAN]="\033[36m\033[22m";
	SEQ[PURPLE]="\033[35m\033[22m";
	SEQ[GREEN]="\033[32m\033[2m";
	SEQ[BLUE]="\033[34m\033[2m";
	SEQ[YELLOW]="\033[33m\033[22m";
	SEQ[DARKPURPLE]="\033[35m\033[2m";
	SEQ[BROWN]="\033[33m\033[2m";
	SEQ[LIGHTRED]="\033[31m\033[22m";
	SEQ[DARKGREY]="\033[37m\033[2m";
	SEQ[DARKCYAN]="\033[36m\033[2m";
	SEQ[LIGHTGREEN]="\033[32m\033[22m";
	SEQ[LIGHTBLUE]="\033[34m\033[22m";
	SEQ[LIGHTGREY]="\033[37m\033[2m";
}

void InitKayPro() {
	HasColors=false;
	CursorXY=CursorXYKAYPRO;
	InitWithNoColors();
	SEQ[REVERSE]="\033B0";
	SEQ[PLAIN]="\033C0";
	SEQ[BLINK]="\033B2";
	SEQ[NOBLINK]="\033C2";
	SEQ[UNDERLINE]="\033B3";
	SEQ[NOUNDERLINE]="\033C3";
	SEQ[DARK]="\033B1";
	SEQ[NODARK]="\033C1";
	SEQ[BEEP]="\007";
	SEQ[CLS]="\032";
	SEQ[HOME]="\036";
	SEQ[CLREOL]="\030";
	SEQ[INSLINE]="\033E";
	SEQ[DELLINE]="\033R";
	SEQ[CURSORON]="\033B4";
	SEQ[CURSOROFF]="\033C4";
	SEQ[TERMRESET]="";
}

void InitC128(bool withColors) {
	HasColors=false;
	CursorXY=CursorXYKAYPRO;
	SEQ[REVERSE]="\033G4";
	SEQ[PLAIN]="\033G0";
	SEQ[BLINK]="\033G2";
	SEQ[NOBLINK]="\033G0";
	SEQ[UNDERLINE]="\033G3";
	SEQ[NOUNDERLINE]="\033G0";
	SEQ[DARK]="\033)";
	SEQ[NODARK]="\033(";
	SEQ[BEEP]="\007";
	SEQ[CLS]="\032";
	SEQ[HOME]="\036";
	SEQ[CLREOL]="\033T";
	SEQ[INSLINE]="\033E";
	SEQ[DELLINE]="\033R";
	SEQ[CURSORON]="";
	SEQ[CURSOROFF]="";
	SEQ[TERMRESET]="\033G0";
	if (withColors) {
		SEQ[BLACK]     ="\033\033\033\040";
		SEQ[WHITE]     ="\033\033\033\041";
		SEQ[RED]       ="\033\033\033\042";
		SEQ[CYAN]      ="\033\033\033\043";
		SEQ[PURPLE]    ="\033\033\033\044";
		SEQ[GREEN]     ="\033\033\033\045";
		SEQ[BLUE]      ="\033\033\033\046";
		SEQ[YELLOW]    ="\033\033\033\047";
		SEQ[DARKPURPLE]="\033\033\033\050";
		SEQ[BROWN]     ="\033\033\033\051";
		SEQ[LIGHTRED]  ="\033\033\033\052";
		SEQ[DARKCYAN]  ="\033\033\033\053";
		SEQ[DARKGREY]  ="\033\033\033\054";
		SEQ[LIGHTGREEN]="\033\033\033\055";
		SEQ[LIGHTBLUE] ="\033\033\033\056";
		SEQ[LIGHTGREY] ="\033\033\033\057";
	} else InitWithNoColors();
}

void InitMemotech() {
	HasColors=false;
	CursorXY=CursorXYMemotech;
	InitWithNoColors();
	SEQ[PLAIN]="\006\004";
	SEQ[REVERSE]="\006\070";
	SEQ[BLINK]="\016";
	SEQ[NOBLINK]="\017";
	SEQ[UNDERLINE]="\006\005";
	SEQ[NOUNDERLINE]=SEQ[PLAIN];
	SEQ[DARK]="\006\002";
	SEQ[NODARK]=SEQ[PLAIN];
	SEQ[CLS]="\014";
	SEQ[HOME]="\026";
	SEQ[CLREOL]="\005";
	SEQ[INSLINE]="\033I";
	SEQ[DELLINE]="\033J";
	SEQ[BEEP]="\007";
	SEQ[CURSORON]="\036";
	SEQ[CURSOROFF]="\037";
	SEQ[TERMRESET]="\030\006\004";
}

void InitVT52() {
	HasColors=false;
	CursorXY=CursorXYVT52;
	InitWithNoColors();
	SEQ[PLAIN]="";
	SEQ[REVERSE]="";
	SEQ[BLINK]="";
	SEQ[NOBLINK]="";
	SEQ[UNDERLINE]="";
	SEQ[NOUNDERLINE]="";
	SEQ[DARK]="";
	SEQ[NODARK]="";
	SEQ[CLS]="\033H\033J";
	SEQ[HOME]="\033H";
	SEQ[CLREOL]="\033K";
	SEQ[INSLINE]="\033L";
	SEQ[DELLINE]="\033M";
	SEQ[BEEP]="\007";
	SEQ[CURSORON]="";
	SEQ[CURSOROFF]="";
	SEQ[TERMRESET]="";
}

void InitCPC() {
	InitVT52();
	SEQ[PLAIN]="\033q";
	SEQ[REVERSE]="\033p";
	SEQ[CURSORON]="\033e";
	SEQ[CURSOROFF]="\033f";
}

void SetTermType(int t) {
	Term=t;
	switch(Term) {
		case VT52: InitVT52(); break;
		case VT100: InitVT100(); break;
		case ANSI: InitANSI(); break;
		case KAYPRO: InitKayPro(); break;
		case ADM31: InitC128(false); break;
		case C128: InitC128(true); break;
		case MEMOTECH: InitMemotech(); break;
		case CPC: InitCPC(); break;
	}
}

int ReadChar() {
#if defined(CPM) || defined(__SASC)
	return getch();
#else
	char buf=0;
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0) perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0) perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0) perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0) perror ("tcsetattr ~ICANON");
	return buf;
#endif
}

void ResetTerm() {
	printf("%s",SEQ[TERMRESET]);
}

void AskTermType(int argc, char *argv[]) {
	int t = INVALID;
	int c;
	if (argc>1 && strlen(argv[1])==1)
		t = argv[1][0] - '0';
	else if (argc>1 && strlen(argv[1])>1)
		t = String2TermType(argv[1]);

	if (t<=INVALID || t>=LAST) {
		printf("Select a terminal type (or specify it on command line):\n");
		PrintTermTypeList();
		printf("\n>");
		do {
			c = ReadChar();
			t = c-'0';
		} while (t<=INVALID || t>=LAST);
	}
	printf("%c\n",c);
	SetTermType(t);
}

void ShowCursor() {
	printf("%s",SEQ[CURSORON]);
}

void HideCursor() {
	printf("%s",SEQ[CURSOROFF]);
}

void ClrScr() {
	printf("%s",SEQ[CLS]);
}

void Home() {
	printf("%s",SEQ[HOME]);
}

void ClrEol() {
	printf("%s",SEQ[CLREOL]);
}

void InsLine() {
	printf("%s",SEQ[INSLINE]);
}

void DelLine() {
	printf("%s",SEQ[DELLINE]);
}

void PlotBox(int x1, int y1, int x2, int y2, bool h, bool v) {
	char s[90];
	int i,j;
	strcpy(s,"                                                                                ");
	s[x2-x1+1]='\0';
	printf("%s",SEQ[REVERSE]);
	if (v)
		for (i=1; i<=2; ++i)
			for (j=y1; j<=y2; ++j) {
				if (i==1) CursorXY(x1,j); else CursorXY(x2,j);
				putchar(' ');
			}
	if (h) {
		CursorXY(x1,y1); printf("%s",s);
		CursorXY(x1,y2); printf("%s",s);
	}
	printf("%s",SEQ[PLAIN]);
}

void Center(int y, char *s) {
	CursorXY((80-strlen(s))/2+1,y); puts(s);
}

bool InputCardinal(int x, int y, int *pNumber, int l) {
	int i=0;
	char ch;
	char s[31];
	do {
		CursorXY(x+i,y);
		ch=ReadChar();
		if (ch>='0' && ch<='9' && i<l) {
			s[i++]=ch;
			s[i]='\0';
			putchar(ch);
		} else if ((ch=='\010' || ch=='\177') && i>0) {
			s[--i]='\0';
			CursorXY(x+i,y); printf(" ");
		} else if (ch=='\033' || ch=='\003') {
			s[0]='\0';
		}
	} while (ch!='\033' && ch!='\003' && (ch!='\015' || i==0) && (ch!='\012' || i==0));
	if (ch=='\033' || ch=='\003') return false;
	*pNumber = atoi(s);
	return true;
}

void RandomizeShuffle() {
	srand(time(NULL));
}
