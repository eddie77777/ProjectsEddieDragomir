//
// Created by sorana on 1/12/2023.
//

#include "../include/PyObjectWrapper.h"

PyObjectWrapper::PyObjectWrapper(PyObject *pyObject) { m_pobj = pyObject; }

PyObjectWrapper::~PyObjectWrapper() {
    //Py_DECREF(m_pobj);
}

PyObject *PyObjectWrapper::GetPyObj() const {
    return m_pobj;
}
void PyObjectWrapper::SetPyObj(PyObject* pyObject) {
    m_pobj = pyObject;
}

PyObjectWrapper::PyObjectWrapper() {

}

PyObjectWrapper::operator PyObject *() const {
    return m_pobj;
}
