//
// Created by sorana on 1/12/2023.
//

#ifndef MCIA_PYOBJECTWRAPPER_H
#define MCIA_PYOBJECTWRAPPER_H
#include <Python.h>

class PyObjectWrapper {
public:
    PyObjectWrapper();
    PyObjectWrapper(PyObject* pyObject);
    ~PyObjectWrapper();

    PyObject *GetPyObj() const;
    void SetPyObj(PyObject* pyObject);

    operator PyObject*() const;
private:
    PyObject* m_pobj;
};


#endif //MCIA_PYOBJECTWRAPPER_H
