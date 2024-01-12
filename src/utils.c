#include "utils.h"



void appendToString(char* s, char c, int index) {
	int l = strlen(s);
	
	if (index > l) {
		char* temp = realloc(s, (l*2)*sizeof(char));
		if (!temp) {
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
