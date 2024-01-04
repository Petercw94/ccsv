#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000
#define LINE_ENDING '\n'

#define ON 1;
#define OFF 0;



// TODO: parse the headers out of the first line of the csv



typedef struct {
	int columnCount;
	char* headers[DEFAULT_ROW_SIZE];
} FileMeta;

typedef struct {
	int lineSize;
	int lastLine;
	char* line;
} Line;

// void appendToString(char* s, char c, int index) {

// }

void appendToLine(Line* line, char c, int index)
{
	// allocate new array, copy the current line over, free old array, update pointer
	// account for 0 index
	if (index >= (line->lineSize - 1)) {
		
		char* temp = realloc(line->line, (line->lineSize*2)*sizeof(char));
		if (temp == NULL) {
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

// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines

FileMeta parseHeaders(FILE* fp)
{
	// read the first line 
	// count the non-data commas 
	FileMeta fm;
	fm.columnCount = 0;
	Line line = readLine(fp);
	
	int colStateQuotes, prevChar, strIndex;
	strIndex = 0;

	for (int i=0; i<line.lineSize; i++) {
		
		if (colStateQuotes == 0 && line.line[i] == '"')
			colStateQuotes = ON; 

		if (line.line[i] == ',') {
			if (colStateQuotes == 0)
				fm.columnCount++;
			else if (prevChar == '"') {
				fm.columnCount++;
				colStateQuotes = OFF;
				strIndex = 0;
			}
		}

		// if (colStateQuotes == 0) {
		// 	fm.headers[]
		// }

		prevChar = line.line[i];
	}
}


int main() 
{
	FILE* fp = fopen("PC_Report_Master.csv", "r");
	Line line;

	do {
		line = readLine(fp);
		printf("%s\n", line.line);
	} while (line.lastLine != 1);
	fclose(fp);
}
