#include "FileHeaders.h"
#include "Line.h"
#include "utils.h"

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