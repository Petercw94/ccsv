#include "../include/ccsv.h"

static PyMethodDef CCSVMethods[] = {
    {"get_headers", get_headers, METH_VARARGS, 
        "return the first row (header row) of the file at the provided file path."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ccsvmodule = {
    PyModuleDef_HEAD_INIT,
    "ccsv", 
    "Perform SQL like query operations on csv files.",
    -1,
    CCSVMethods
};

PyMODINIT_FUNC
PyInit_ccsv(void)
{
    return PyModule_Create(&ccsvmodule);
}
/* TODO: 
 * 1. take the string from the python args
 * 2. open a new file descriptor
 * 3. parse the header row
 * 4. convert the returned array into a python tuple
 * 5. Return the python tuple back to python
 * */ 
static PyObject* 
get_headers(PyObject* self, PyObject* args)
{
    // 1.
    char* file_path;
    
    if (!PyArg_ParseTuple(args, "s", &file_path)) {
        return NULL;
    }

    // 2.
    FILE* fp = fopen(file_path, "r");
    // TODO: check that the file opened properly
    
    // 3.
    Row row;
    row = parseRow(fp);
    fclose(fp);
    // TODO check that the file closed properly
    
    // 4. 
    PyObject* py_tuple = PyTuple_New(row.columnCount);

    /* Loop through the array and: 
     * - convert each string into a python string PyObject* 
     * - add the string object to the tuple. */
    PyObject* column_string;

    for (int i = 0; i < row.columnCount; ++i) {
        column_string = PyUnicode_FromString(row.columns[i]); // create a PyObject Unicode type from the string literals
        int error = PyTuple_SetItem(py_tuple, i, column_string);
        if (error != 0) {
            fprintf(stderr, "Error adding PyUnicode Object to PyTuple.\n");
            exit(EXIT_FAILURE);
       }
    }

    return py_tuple;

}


#define LINE_ENDING '\n'
#define ON 1
#define OFF 0

/*
 * c_count -> the character count of the column
 * c_string -> a pointer to the character string representation of
 * */ 
char* parseColumn(FILE* fp, int c_count)
{
    int c;
    int offset = -c_count;
    offset--; // remove one from the offset to move cursor correctly

    // allocate memory for the column string
    char* s = (char*) malloc((c_count + 1) * sizeof(char));
    if (s == NULL) {
        fprintf(stderr, "Error allocating memory for column string.\n");
    }
    int error = fseek(fp, offset, SEEK_CUR);
    if (error != 0) {
        fprintf(stderr, "Error adjusting the File Pointer while parsing the column\n");
        exit(EXIT_FAILURE);
    }
    // TODO : replace the printing of the column with writing that column to a string 
    // literal stored in column array (requires a new parameter: string literal pointer)
    for (int i = 0; i<c_count; ++i) {
        c = fgetc(fp);
        s[i] = c;
    }
    s[c_count] = '\0'; // terminate the string
    return s;
}

/* Parse the columns for the next row in the file buffer.
 * Column values parsed as strings and written in order to the provided row array
 * Returns: an integer indicating the total number of columns in the provided row */
Row parseRow(FILE* fp)
{
    
    int c, colStateQuotes, prevChar, colCharCount, error, colCount;
    colStateQuotes = OFF;
    
    colCount = colCharCount = prevChar = 0;
    Row row;

    // allocate an array of the default column size
    row.columns = malloc(DEFAULT_COL_NUM * sizeof(char*));
    if (row.columns == NULL) {
        fprintf(stderr, "Error: There was an error allocating memory for the row array.\n");
    }

    
	while ((c=fgetc(fp)) != LINE_ENDING) {
		

        /* if line ending or end of file hit, parse the column then break the loop */
        if (c == EOF) {
            row.columns[colCount++] = parseColumn(fp, colCharCount);
            row.lastRow = 1;
            break;
        }
        /* If a " appears and we aren't currently in a 
         * column quote state, it indicates that its the 
         * beginning of a new col that is surrounded by
         * quotes. See RFC standards for explanation */
        else if (c == '"' && colStateQuotes == 0) {
            colStateQuotes = ON; // this state indicates whether we are currently in a data state or not
        }

        else if (c == ',') {
            /* if a comma appears and we aren't in a quoted data column,
             * it would indicate that its the end of the column */
            if (colStateQuotes == 0) {
                row.columns[colCount++] = parseColumn(fp, colCharCount);
                colCharCount = 0; // reset the char counter for the next col
                error = fseek(fp, 1, SEEK_CUR);
                if (error != 0) {
                    fprintf(stderr, "Error advancing file pointer after parsing column.\n");
                    exit(EXIT_FAILURE);
                }
            }

            /* If a comma appears and the program is in the quoted 
             * data col state, a check needs to be made to the previous
             * character. If the previous character is a double quote, it would 
             * signify the end of the data state, which would also
             * indicate the end of the column. */
            else if (prevChar == '"') {
                row.columns[colCount++] = parseColumn(fp, colCharCount);
                colCharCount = 0; // reset the char counter for the next col
                error = fseek(fp, 1, SEEK_CUR);
                if (error != 0) {
                    fprintf(stderr, "Error advancing file pointer after parsing column.\n");
                    exit(EXIT_FAILURE);
                }
            }
        
            
            /* If the character does not signify the end of the column
             * it needs to be counted so the parseCol function knows how 
             * far back it needs to move the file pointer to allocate enough
             * memory and parse the column value*/
            else {
                ++colCharCount;
            }
        }

        else {
            ++colCharCount;
        }
        prevChar = c;
	}
    row.columns[colCount++] = parseColumn(fp, colCharCount);
    row.columnCount = colCount;

    // advance the cursor to the next line
    error = fseek(fp, 1, SEEK_CUR);
    if (error != 0) {
        fprintf(stderr, "Error advancing file pointer after parsing column.\n");
        exit(EXIT_FAILURE);
    }
    return row;
}

void parseFile(FILE* fp)
{
    Row row;
    // loop through the whole file
    for (;;) {
    
        row = parseRow(fp);

        for (int i=0; i<row.columnCount; ++i) {
            printf("%s", row.columns[i]);
        }
        printf("\n");
        

        free(row.columns);     
        
        if (row.lastRow == 1) {
            break;
        }
    }    
}
