#include "../include/ccsv.h"


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
