#include <iostream>
#include <Python.h>

static PyObject *AgentError;
static PyObject* agent_setcfg(PyObject *self, PyObject *args);
static PyObject* agent_request(PyObject *self, PyObject *args);
static PyObject* agent_response(PyObject *self, PyObject *args);

static std::string cfgfilename("geard.cfg");

static PyMethodDef AgentMethods[] = {
    {"set_config", agent_setcfg, METH_VARARGS, "Set the configuration"},
    {"request", agent_request, METH_VARARGS, "Request handler"},
    {"response", agent_response, METH_VARARGS, "Response handler"},
    {nullptr, nullptr, 0, nullptr} /* Sentinel */
};

static struct PyModuleDef agentmodule = {
    PyModuleDef_HEAD_INIT,
    "agent", /* name of module */
    nullptr, /* module documentation, may be nullptr */
    -1, /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
    AgentMethods
};

/////////////////////////////////////////////////////////////

PyMODINIT_FUNC PyInit_agent(void)
{
    PyObject *module;

    module = PyModule_Create(&agentmodule);
    if (module == nullptr)
        return nullptr;

    AgentError = PyErr_NewException((char*)"agent.error", nullptr, nullptr);
    Py_INCREF(AgentError);
    PyModule_AddObject(module, "error", AgentError);

    return module;
}

static PyObject* agent_setcfg(PyObject *self, PyObject *args)
{
    const char* filename = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename))
        Py_RETURN_NONE;
    
    if (nullptr != filename)
        cfgfilename = std::string(filename);

    Py_RETURN_NONE;
}

static PyObject* agent_request(PyObject *self, PyObject *args)
{
    Py_RETURN_NONE;
}

static PyObject* agent_response(PyObject *self, PyObject *args)
{
    Py_RETURN_NONE;
}


