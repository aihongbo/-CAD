#include "NctiPyObjectDemo.h"

using namespace NCTI;

NCTI::NctiPyObjectDemo::NctiPyObjectDemo()
    : m_TypeObject(PyTypeObject())
{
}

NCTI::NctiPyObjectDemo::~NctiPyObjectDemo()
{
}

void NCTI::NctiPyObjectDemo::Init()
{
}

PyTypeObject* NctiPyObjectDemo::GetTypeObject()
{
    return &m_TypeObject;
}
