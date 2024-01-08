#include "FileMeta.h"
#include "Line.h"

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