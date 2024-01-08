#include <stdio.h>
#define LINE_ENDING '\n'

typedef struct {
	int lineSize;
	int lastLine;
	char* line;
} Line;

void appendToLine(Line* line, char c, int index);
Line readLine(FILE* fp);