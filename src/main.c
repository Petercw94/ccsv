#include <stdio.h>
#include <time.h>

#include "../include/Parser.h"

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000






// TODO: Looks like there is a bug when the data segment is surrounded by quotes. Probably need to escape those 
// quotes before writing to the array.



/**/



int main() 
{
	float startTime = (float)clock()/CLOCKS_PER_SEC;
	char* filepath = "../test/test.csv";
	FILE* fp = fopen(filepath, "r");
    
    parseFile(fp); 

    fclose(fp);
    float endTime = (float)clock()/CLOCKS_PER_SEC;

	float timeElapsed = endTime - startTime;

	printf("Execution time: %2.8f seconds\n", timeElapsed);

}





// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines




