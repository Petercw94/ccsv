#include <stdio.h>

#define DEFAULT_ROW_SIZE 10
#define LINE_ENDING '\n'

#define ON 1;
#define OFF 0;

typedef struct {
	int columns;
	char headers[DEFAULT_ROW_SIZE];
} FileMeta;


// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines

FileMeta parseHeaders(FILE* fp)
{
	int c, colStateQuotes, prevChar;
	colStateQuotes = OFF;

	FileMeta fileMeta;
	fileMeta.columns = 0;
	
	/* NOTE: This conditional will break if a newline 
	character is part of a column string. A new line 
	character is allowed to be part of a col string 
	as long as that col is wrapped in double-quotes, 
	so that will need to be an added check to this. 
	*/
	while ((c=getc(fp)) != LINE_ENDING) {
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
	}
	// add another column to account for the last column
	fileMeta.columns++;
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
