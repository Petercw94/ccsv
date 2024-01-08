#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Line.h"
#include "FileHeaders.h"
#include "FileMeta.h"
#include "utils.h"

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000






// TODO: Looks like there is a bug when the data segment is surrounded by quotes. Probably need to escape those 
// quotes before writing to the array.



/**/







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








// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines




