#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000
#define LINE_ENDING '\n'

#define ON 1;
#define OFF 0;



// TODO: Looks like there is a bug when the data segment is surrounded by quotes. Probably need to escape those 
// quotes before writing to the array.



typedef struct {
	int columnCount;
	char** headers;
} FileHeaders;

typedef struct {
	int rowCount;
	int longestRow;
	int longestCol;
} FileMeta;

typedef struct {
	int lineSize;
	int lastLine;
	char* line;
} Line;

/**/
void appendToString(char* s, char c, int index);
void resetStringArray(char* s);
void appendToLine(Line* line, char c, int index);
void appendToStringArray(char*array[], char c, int index);
FileMeta scanFile(char* s);
Line readLine(FILE* fp);
FileHeaders parseHeaders(FILE* fp);






int main() 
{
	char* filepath = "test.csv";
	FILE* fp = fopen(filepath, "r");
	FileHeaders fh; 
	fh = parseHeaders(fp);
	printf("Header Count: %d\n", fh.columnCount);
	for (int i=0; i<fh.columnCount; i++)
		printf("%s\n", fh.headers[i]);
}







FileMeta scanFile(char* filepath)
{
	FILE* fp = fopen(filepath, "r");
	FileMeta fm;
	fm.longestRow = 0;
	fm.rowCount = 0;

	Line line;

	do {
		line = readLine(fp);
		fm.rowCount++;
		if (line.lineSize > fm.longestRow) 
			fm.longestRow = line.lineSize;
			
	} while (line.lastLine != 1);

	fclose(fp);
	return fm;
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


FileHeaders parseHeaders(FILE* fp)
{
	// read the first line 
	// count the non-data commas 
	FileHeaders fileHeaders;
	fileHeaders.columnCount = 0;
	Line line = readLine(fp);
	printf("%s\n", line.line);
	fileHeaders.headers = malloc(200 * sizeof(char*));
	if (fileHeaders.headers == NULL) {
		fprintf(stderr, "Error: error allocating memory for header array.\n");
		exit(EXIT_FAILURE);
	}
	fileHeaders.headers[fileHeaders.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
	if (fileHeaders.headers[fileHeaders.columnCount] == NULL) {
		fprintf(stderr, "Error: error allocating memory for header column.\n");
		exit(EXIT_FAILURE);
	}

	int colStateQuotes, prevChar, strIndex;
	colStateQuotes = OFF;
	
	strIndex = 0;
	

	for (int i=0; i<line.lineSize; i++) {
		
		if (colStateQuotes == 0 && line.line[i] == '"')
			colStateQuotes = ON; 

		if (line.line[i] == ',') {
			if (colStateQuotes == 0) {
				// Null terminate the 
				fileHeaders.headers[fileHeaders.columnCount][strIndex++] = '\0';
				fileHeaders.columnCount++;
				// get the next pointer for the sting
				fileHeaders.headers[fileHeaders.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
				if (fileHeaders.headers[fileHeaders.columnCount] == NULL) {
					fprintf(stderr, "Error: error allocating memory for header column.\n");
					exit(EXIT_FAILURE);
				}
				// reset the str index
				strIndex = 0;
			}
			else if (prevChar == '"') {
				// Null terminate the 
				fileHeaders.headers[fileHeaders.columnCount][strIndex++] = '\0';
				fileHeaders.columnCount++;
				// get the next pointer for the sting
				fileHeaders.headers[fileHeaders.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
				if (fileHeaders.headers[fileHeaders.columnCount] == NULL) {
					fprintf(stderr, "Error: error allocating memory for header column.\n");
					exit(EXIT_FAILURE);
				}
				// reset the str index
				strIndex = 0;
			}
			else {
				appendToString(fileHeaders.headers[fileHeaders.columnCount], line.line[i], strIndex++);
			}
		}
		
		else {
			appendToString(fileHeaders.headers[fileHeaders.columnCount], line.line[i], strIndex++);
		}

		// if (colStateQuotes == 0) {
		// 	fm.headers[]
		// }

		prevChar = line.line[i];
	}
	fileHeaders.columnCount++;
	return fileHeaders;
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

void resetStringArray(char* s)
{
	int l = strlen(s);
	char* temp = malloc(l * sizeof(char));
	if (temp == NULL) {
		printf("Error: error allocating new str in resetStringArray.\n");
		free(s);
		exit(EXIT_FAILURE);
	}
	free(s);
	s = temp;
}