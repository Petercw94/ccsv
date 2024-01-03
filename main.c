#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ROW_SIZE 5
#define DEFAULT_LINE_SIZE 1000
#define LINE_ENDING '\n'

#define ON 1;
#define OFF 0;


/* Append a new char to the provided array. 
If the array has reached its max capacity, allocate 
more memory, free the first array, copy the new array
to the original pointer and return the new array size
*/




typedef struct {
	int columns;
	char headers[DEFAULT_ROW_SIZE];
} FileMeta;

typedef struct {
	int lineSize;
	char* line;
} Line;

void writeToLine(Line* line, char c, int index)
{
	// allocate new array, copy the current line over, free old array, update pointer
	// account for 0 index
	if (index >= (line->lineSize - 1)) {
		printf("Allocating new memory for line array.\n");
		char* temp = malloc((line->lineSize * 2) * sizeof(char));
		for (int i=0; i < line->lineSize; i++) {
			temp[i] = line->line[i];
		}

		free((*line).line);
		line->lineSize = line->lineSize*2;
		line->line = temp;
		line->line[index] = c;
		
		return;
	}

	else {
		line->line[index] = c;
	}
}

// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines

FileMeta parseHeaders(FILE* fp)
{
	int c, colStateQuotes, prevChar;
	colStateQuotes = OFF;

	// line index
	int index=0;

	FileMeta fileMeta;
	fileMeta.columns = 0;
	Line line;
	line.lineSize = 5;
	line.line = malloc(5 * sizeof(char));
	
	/* NOTE: This conditional will break if a newline 
	character is part of a column string. A new line 
	character is allowed to be part of a col string 
	as long as that col is wrapped in double-quotes, 
	so that will need to be an added check to this. 
	*/
	while ((c=getc(fp)) != LINE_ENDING) {

		writeToLine(&line, c, index);
		// set the colState
		if (colStateQuotes == 0 && c == '"')
			colStateQuotes = ON;

		
		if (c == ',') {
			if (colStateQuotes == 0)
				fileMeta.columns++;
			else if (prevChar == '"') {
				fileMeta.columns++;
				colStateQuotes = OFF; // turn off the quotes state
			}
		}
		prevChar = c;
		index++;
	}
	// add another column to account for the last column
	fileMeta.columns++;
	

	printf("Line: %s\n", line.line);
	return fileMeta;
}


int main() 
{
	FILE* fp = fopen("test.csv", "r");
	FileMeta fileMeta;
	fileMeta = parseHeaders(fp);
	printf("%d\n",fileMeta.columns);
	fclose(fp);
}
