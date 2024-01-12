#include "Line.h"
#include <stdlib.h>

void appendToLine(Line* line, char c, int index)
{
	// allocate new array, copy the current line over, free old array, update pointer
	// account for 0 index
	if (index >= (line->lineSize - 1)) {
		
		char* temp = realloc(line->line, (line->lineSize*2)*sizeof(char));
		if (!temp) {
			printf("Error: error reallocating memory in appendToLine.\n");
			free(line->line);
			exit(EXIT_FAILURE);
		}

		line->lineSize = line->lineSize*2;
		line->line = temp;
		line->line[index] = c;
		
		return;
	}

	else {
		line->line[index] = c;
	}
}


Line readLine(FILE* fp)
{
	int c, index;
	index = 0;


	Line line;
	line.lineSize = 5;
	line.lastLine = 0;
	line.line = malloc(5 * sizeof(char));
	if (line.line == NULL){
		printf("Error: malloc failed to allocate a new line.\n");
		exit(EXIT_FAILURE);
	}

		
	while ((c=getc(fp)) != LINE_ENDING) {
		if (c == EOF) {
			line.lastLine = 1;
			return line;
		}
		appendToLine(&line, c, index++);

	}

	return line;
}

