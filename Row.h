#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000
#define ON 1;
#define OFF 0;

typedef struct {
	int columnCount;
	int lastRow; // indicates the last row in the file
	char** columns;
} Row;

Row parseRow(FILE* fp);