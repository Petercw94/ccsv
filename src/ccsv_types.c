#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>



typedef struct {
    PyObject_HEAD
    PyObject* file_name;
} CsvObject;


static void 
Csv_dealloc(CsvObject* self)
{
    Py_XDECREF(self->file_name);
    Py_TYPE(self)->tp_free((PyObject*) self);
}

static PyObject*
Csv_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    CsvObject* self;
    self = (CsvObject*) type->tp_alloc(type, 0);
    if (self !=NULL) {
        self->file_name = PyUnicode_FromString("");
        if (self->file_name == NULL) {
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject*) self;
}

static int
Csv_init(CsvObject* self, PyObject* args, PyObject* kwds)
{
    static char* kwdlist[] = {"file_name", NULL};
    PyObject* file_name = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwdlist, &file_name)) {
        return -1;
    }
}


static PyTypeObject CsvType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "ccsv.Csv",
    .tp_doc = PyDoc_STR("CSV Parser class"),
    .tp_basicsize = sizeof(CsvObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyModuleDef ccsvmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "ccsv",
    .m_doc = "Custom CSV parser that allows sql-like functionality.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_ccsv(void)
{
    PyObject* m;
    if (PyType_Ready(&CsvType) < 0) {
        return NULL;
    }

    m = PyModule_Create(&ccsvmodule);
    if (m == NULL) {
        return NULL;
    }

    Py_INCREF(&CsvType);
    if (PyModule_AddObject(m, "Csv", (PyObject*) &CsvType) < 0) {
        Py_DECREF(&CsvType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
