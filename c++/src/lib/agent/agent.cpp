// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <string>
#include <Python.h>
#include "apm.h"

static PyObject *AgentError;
static PyObject* libagent_setcfg(PyObject *self, PyObject *args);
static PyObject* libagent_request(PyObject *self, PyObject *args);
static PyObject* libagent_response(PyObject *self, PyObject *args);

static std::string cfgfilename("exagent.cfg");

static PyMethodDef AgentMethods[] = {
    {"set_config", libagent_setcfg, METH_VARARGS, "Set the configuration"},
    {"request", libagent_request, METH_VARARGS, "Request handler"},
    {"response", libagent_response, METH_VARARGS, "Response handler"},
    {nullptr, nullptr, 0, nullptr} /* Sentinel */
};

static struct PyModuleDef agentmodule = {
    PyModuleDef_HEAD_INIT,
    "libagent", /* name of module */
    nullptr,    /* module documentation, may be nullptr */
    -1,         /* size of per-interpreter state of the module,
                   or -1 if the module keeps state in global variables. */
    AgentMethods
};

exagent::APM apm;

/////////////////////////////////////////////////////////////

PyMODINIT_FUNC PyInit_libagent(void)
{
    PyObject *module;

    module = PyModule_Create(&agentmodule);
    if (module == nullptr)
        return nullptr;

    AgentError = PyErr_NewException((char*)"libagent.error", nullptr, nullptr);
    Py_INCREF(AgentError);
    PyModule_AddObject(module, "error", AgentError);

    return module;
}

static PyObject* libagent_setcfg(PyObject *self, PyObject *args)
{
    const char* filename = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename))
        Py_RETURN_NONE;
    
    if (nullptr != filename)
        cfgfilename = std::string(filename);
    else
        Py_RETURN_NONE;

    apm.set_filename(cfgfilename);

    Py_RETURN_NONE;
}

static PyObject* libagent_request(PyObject *self, PyObject *args)
{
    const char* json = nullptr;
    const char* id = nullptr;

    if (!PyArg_ParseTuple(args, "ss", &json, &id))
        Py_RETURN_NONE;
    
    if (nullptr != json)
    {
        if (false == apm.process_request(json, id))
        {
            //log the error
        }
    }

    Py_RETURN_NONE;
}

static PyObject* libagent_response(PyObject *self, PyObject *args)
{
    const char* json = nullptr;
    const char* id = nullptr;

    if (!PyArg_ParseTuple(args, "ss", &json, &id))
        Py_RETURN_NONE;
    
    if (nullptr != json || nullptr == id)
    {
        if (false == apm.process_response(json, id))
        {
            //log the error
        }
    }

    Py_RETURN_NONE;
}


