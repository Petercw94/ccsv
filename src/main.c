#include <stdio.h>
#include <time.h>

#include "../include/ccsv.h"

#define DEFAULT_ROW_SIZE 100
#define DEFAULT_LINE_SIZE 1000






// TODO: Looks like there is a bug when the data segment is surrounded by quotes. Probably need to escape those 
// quotes before writing to the array.



/**/

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

int main() 
{
	float startTime = (float)clock()/CLOCKS_PER_SEC;
    

    float endTime = (float)clock()/CLOCKS_PER_SEC;

	float timeElapsed = endTime - startTime;

	printf("Execution time: %2.8f seconds\n", timeElapsed);

}





// TODO: create a column state to identify when in a new col
// 			if in a column, determine if the column is wrapped in double quotes
//			if wrapped in double quotes, ignore any comma, new line characters and double quotes
// 			if not wrapped in double quotes
//				ignore any commas or new lines




