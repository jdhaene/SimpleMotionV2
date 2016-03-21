#include <Python.h>
#include <stdio.h>
#include "simplemotion.h"


static PyObject* openBus(PyObject *self, PyObject *args, PyObject *kwargs)
{
	const char* device = "/dev/asdf/asdf/asdf";
	if (!PyArg_ParseTuple(args, "s", &device)) return NULL;
	return PyInt_FromLong((long)smOpenBus(device));
}

static PyObject* setParameter(PyObject *self, PyObject *args, PyObject *kwargs)
{
	smbus handle;
	smaddr node;
	smint16 param;
	smint32 data;
	SM_STATUS status;
	if (!PyArg_ParseTuple(args, "iiii", &handle, &node, &param, &data)) return NULL;
	//printf("SetParameter %i %i %i %i\n",handle,node,param,data);
	status = smSetParameter(handle,node,param,data);
	if (status != 1)
		PyErr_Format(PyExc_ValueError, "Return code 0x%04x",status);
	return PyInt_FromLong((long)0);
}

static PyObject* getParameter(PyObject *self, PyObject *args, PyObject *kwargs)
{
	smbus handle;
	smaddr node;
	smint16 param;
	smint32 data=0;
	SM_STATUS status;
	if (!PyArg_ParseTuple(args, "iii", &handle, &node, &param)) return NULL;
	//printf("Read1Parameter %i %i %i\n",handle,node,param);
	status = smRead1Parameter(handle,node,param,&data);
	if (status != 1)
		PyErr_Format(PyExc_ValueError, "Return code 0x%04x",status);
	return PyInt_FromLong((long)data);
}


static PyMethodDef SimpleMotionMethods[] =
{
	{"openBus", (PyCFunction)openBus, METH_VARARGS, "Open SimpleMotion Bus."},
	{"setParameter", (PyCFunction)setParameter, METH_VARARGS, "Set SimpleMotion Parameter."},
	{"getParameter", (PyCFunction)getParameter, METH_VARARGS, "Get SimpleMotion Parameter."},
	{NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "simplemotion",     /* m_name */
        "simplemotion library",  /* m_doc */
        -1,                  /* m_size */
        SimpleMotionMethods,    /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };
#endif

PyMODINIT_FUNC

#if PY_MAJOR_VERSION >= 3
PyInit_simplemotion(void)
#else
initsimplemotion(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
        PyObject *module = PyModule_Create(&moduledef);
#else
	(void) Py_InitModule("simplemotion", SimpleMotionMethods);
#endif

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
