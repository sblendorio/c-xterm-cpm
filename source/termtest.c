#include <xterm.h>

int main(int argc, char *argv[]) {
	int ch; bool b;

	AskTermType(argc, argv);
	ResetTerm();

	ClrScr();
	Center(2,"Test XTERM.C library");
	Center(3,"--------------------");
	Home(); printf("(1,1) Position");
	CursorXY(1,3); InsLine(); printf("Line inserted. Press a key to delete");
	ch = ReadChar();
	DelLine();
	CursorXY(1,4); printf("Now cleaning from here: ksdhfskdfhskdfhskdj. Press a key");
	ch = ReadChar();
	CursorXY(24,4); ClrEol();
	CursorXY(1,4); InsLine();
	CursorXY(1,1); PlotBox(30,1,51,4,true,true);
	CursorXY(1,5); printf("Type a number: ");
	ClrEol();
	b = InputCardinal(16,5,&ch,3);
	CursorXY(1,5);
	if (b)
		printf("You typed: %d",ch);
	else
		printf("INPUT INTERRUPTED");
	ClrEol();
	printf("\n\n%s REVERSE %s PLAIN \n",SEQ[REVERSE],SEQ[PLAIN]);
	CursorXY(1,15); printf("Bye.\n");
}
