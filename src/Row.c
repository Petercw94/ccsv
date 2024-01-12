#include "Row.h"
#include "Line.h"
#include "utils.h"

Row parseRow(FILE* fp)
{
	// read the first line 
	// count the non-data commas 
	Row row;
	row.columnCount = 0;
	row.lastRow = 0;
	Line line = readLine(fp);
	row.columns = malloc(200 * sizeof(char*));
	if (row.columns == NULL) {
		fprintf(stderr, "Error: error allocating memory for header array.\n");
		exit(EXIT_FAILURE);
	}
	row.columns[row.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
	if (row.columns[row.columnCount] == NULL) {
		fprintf(stderr, "Error: error allocating memory for header column.\n");
		exit(EXIT_FAILURE);
	}

	int colStateQuotes, prevChar, strIndex;
	colStateQuotes = OFF;
	
	strIndex = 0;
	

	for (int i=0; i<line.lineSize; i++) {
		
		if (line.line[i] == '"' && colStateQuotes == 0) {
			colStateQuotes = ON; 
		}

		else if (line.line[i] == ',') {
			if (colStateQuotes == 0) {
				// Null terminate the 
				row.columns[row.columnCount][strIndex++] = '\0';
				row.columnCount++;
				// get the next pointer for the sting
				row.columns[row.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
				if (row.columns[row.columnCount] == NULL) {
					fprintf(stderr, "Error: error allocating memory for header column.\n");
					exit(EXIT_FAILURE);
				}
				// reset the str index
				strIndex = 0;
			}
			else if (prevChar == '"') {
				// Null terminate the 
				row.columns[row.columnCount][strIndex++] = '\0';
				row.columnCount++;
				// get the next pointer for the sting
				row.columns[row.columnCount] = malloc(DEFAULT_ROW_SIZE * sizeof(char));
				if (row.columns[row.columnCount] == NULL) {
					fprintf(stderr, "Error: error allocating memory for header column.\n");
					exit(EXIT_FAILURE);
				}
				// reset the str index
				strIndex = 0;
			}
			else {
				appendToString(row.columns[row.columnCount], line.line[i], strIndex++);
			}
		}
		
		else {
			appendToString(row.columns[row.columnCount], line.line[i], strIndex++);
		}

		// if (colStateQuotes == 0) {
		// 	fm.row[]
		// }

		prevChar = line.line[i];
	}
	row.columnCount++;
	if (line.lastLine == 1) {
		row.lastRow = 1;
	}
    return row;
}
