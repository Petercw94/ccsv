

typedef struct {
	int rowCount;
	int longestRow;
	int longestCol;
} FileMeta;

FileMeta scanFile(char* s);