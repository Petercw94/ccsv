#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000
#define LINE_ENDING '\n'

#define ON 1;
#define OFF 0;



// TODO: parse the headers out of the first line of the csv
// TODO: find out how many lines there are in the csv
// create an array of string literals char *[]



typedef struct {
	int columnCount;
	char* headers[DEFAULT_ROW_SIZE];
} FileMeta;

typedef struct {
	int lineSize;
	int lastLine;
	char* line;
} Line;

/**/
void appendToString(char* s, char c, int index) {
	int l = strlen(s);
	
	if (index > l) {
		char* temp = realloc(s, (l*2)*sizeof(char));
		if (temp == NULL) {
			printf("Error: error reallocating memory in appendToLine.\n");
			free(s);
			exit(EXIT_FAILURE);
		}

		s = temp;
		s[index] = c;

		return;
	}

	else {
		s[index] = c;
	}
}

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

void resetStringArray(char* s)
{
	int l = strlen(s);
	char* temp = malloc(l);
	if (temp == NULL) {
		printf("Error: error allocating new str in resetStringArray.\n");
		free(s);
		exit(EXIT_FAILURE);
	}
	free(s);
	s = temp;
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
	char header[DEFAULT_ROW_SIZE];

	for (int i=0; i<line.lineSize; i++) {
		
		if (colStateQuotes == 0 && line.line[i] == '"')
			colStateQuotes = ON; 

		if (line.line[i] == ',') {
			if (colStateQuotes == 0) {
				// add the string to the header array
				fm.headers[fm.columnCount] = header;

				fm.columnCount++;
				resetStringArray(header);
				strIndex = 0;
			}
			else if (prevChar == '"') {
				fm.headers[fm.columnCount] = header;

				fm.columnCount++;
				colStateQuotes = OFF;
				// add the string to the header array
				resetStringArray(header);
				strIndex = 0;
			}
			else {
				appendToString(header, line.line[i], strIndex);
			}
		}
		
		else {
			appendToString(header, line.line[i], strIndex);
		}

		// if (colStateQuotes == 0) {
		// 	fm.headers[]
		// }

		prevChar = line.line[i];
	}

	return fm;
}


int main() 
{
	FILE* fp = fopen("PC_Report_Master.csv", "r");
	FileMeta fm;
	fm = parseHeaders(fp);
	for (int i=0; i<fm.columnCount; i++)
		printf("%s\n", fm.headers[i]);
	fclose(fp);
}
