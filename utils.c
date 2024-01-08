#include "utils.h"



void appendToString(char* s, char c, int index) {
	int l = strlen(s);
	
	if (index > l) {
		char* temp = realloc(s, (l*2)*sizeof(char));
		if (temp == NULL) {
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

void resetStringArray(char* s)
{
	int l = strlen(s);
	char* temp = malloc(l * sizeof(char));
	if (temp == NULL) {
		printf("Error: error allocating new str in resetStringArray.\n");
		free(s);
		exit(EXIT_FAILURE);
	}
	free(s);
	s = temp;
}