#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define DEFAULT_COL_NUM 200 

typedef struct {
    int columnCount;
    int lastRow;
    char** columns;
} Row;

Row parseRow(FILE* fp);
