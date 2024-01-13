#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define DEFAULT_COL_NUM 200 

typedef struct {
    int columnCount;
    int lastRow;
    char** columns;
} Row;

typedef struct {
    int rowCount;
    char*** file;
} File;

Row parseRow(FILE* fp);
void parseFile(FILE* fp);
