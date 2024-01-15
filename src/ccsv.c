#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../include/Parser.h"

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



}
