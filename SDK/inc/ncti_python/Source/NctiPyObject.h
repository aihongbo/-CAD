#ifndef NctiPyObject_H
#define NctiPyObject_H
#include "ncti_base.h"
#include <Python.h>
#include <vector>
#include "NctiPythonInterface.h"

namespace NCTI
{
	class NctiPyObject : public NCTI_BASE_CLASS
	{
	public:
		NctiPyObject();
		virtual ~NctiPyObject();

		virtual void Init();
		PyTypeObject* GetTypeObject();

        static void SetInterface(NctiPythonInterface*);

	protected:
        static NctiPythonInterface* m_PythonInterface;
		std::vector<PyMethodDef> m_MethodVec;
		PyTypeObject m_TypeObject;
		std::vector<PyGetSetDef> m_AttVec;
	};
}
#endif
