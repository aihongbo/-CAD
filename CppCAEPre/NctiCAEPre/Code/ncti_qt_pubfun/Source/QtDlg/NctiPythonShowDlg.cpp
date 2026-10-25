/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#include "NctiPythonShowDlg.h"

#include <QGroupBox>
#include <QBoxLayout>
#include <QFormLayout>
#include <QTextStream>


#include "NctiQtCommandConsole.h"

#include "ncti_base.h"
#include "NctiLineEditBoundData.h"
#include "NctiPyArgObject.h"
using namespace NCTI;

namespace {
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__LP64__)
	typedef long long ncti_Py_ssize_t;   // 64-bit: 8 bytes
#define NCTI_PY_SSIZE_T_MAX  LLONG_MAX
#else
	typedef long ncti_Py_ssize_t;        // 32-bit fallback: 4 bytes (matches CPython)
#define NCTI_PY_SSIZE_T_MAX  LONG_MAX
#endif

#define NCTI_PYOBJECT_HEAD \
    ncti_Py_ssize_t ob_refcnt; \
    void* ob_type;

#define NCTI_PYOBJECT_VAR_HEAD \
    NCTI_PYOBJECT_HEAD \
    ncti_Py_ssize_t ob_size;

    typedef struct {
		NCTI_PYOBJECT_HEAD
        Ncti_Double x;
        Ncti_Double y;
        Ncti_Double z;
    } NctiPyPointStr;

    typedef struct {
		NCTI_PYOBJECT_HEAD
        Ncti_Double x;
        Ncti_Double y;
        Ncti_Double z;
    } NctiPyVectorStr;
}

namespace NCTI
{
    NctiPythonShowDlg::NctiPythonShowDlg(PyObject* args, Ncti_VariantVleVec* oArgs, bool bReturn, QWidget* parent)
        : QDialog(parent)
		, m_Args(args)
		, m_bReturn(bReturn)
		, m_ReturnArgs(oArgs)
    {
        init();
    }

    NctiPythonShowDlg::~NctiPythonShowDlg()
    {
    }

    void NctiPythonShowDlg::init()
	{
		//this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);
        auto widget = new QFrame(this);
		widget->setObjectName("NctiPythonShowDlg");
		this->setWindowTitle(QStringLiteral("Input Dialog"));
		resize(400, 200);

		m_BtnOK = new QPushButton(this);
		m_BtnCancel = new QPushButton(this);
        m_BtnOK->setText(QStringLiteral("确定"));
		m_BtnCancel->setText(QStringLiteral("退出"));

		m_BtnOK->setObjectName("modetails-ok-button");
		m_BtnCancel->setObjectName("modetails-ok-button");

		if (m_Args == nullptr)
			return;

		QVBoxLayout* layoutMain = new QVBoxLayout(widget);
		QFormLayout* layout = new QFormLayout();
		layout->setLabelAlignment(Qt::AlignRight);
		layout->setFormAlignment(Qt::AlignLeft);
		layoutMain->addLayout(layout);

		Ncti_Integer num_args = NctiPyCB.Size(m_Args);//PyTuple_Size(m_Args);
		if (num_args > 1)
		{
			PyObject* argObj = NctiPyCB.GetTupleItem(m_Args, 1);//PyTuple_GetItem(m_Args, 1);
			//if (!PyUnicode_Check(argObj))
			if (!NctiPyCB.IsUnicode(argObj))
				return;
			const char* name = NctiPyCB.GetUnicodeStr(argObj);//PyUnicode_AsUTF8(argObj);
			this->setWindowTitle(QString::fromUtf8(name));
		}
		if (m_bReturn)
		{
			if (m_ReturnArgs == nullptr)
				return;
			//Ncti_Integer num_out = PyTuple_Size(m_ReturnArgs);
			Ncti_Integer num_out = (*m_ReturnArgs).size();
			if (2 * num_out != num_args - 2)
				return;
		}
		NctiPyArgObject argList(m_Args);
		std::vector<std::string> captions;
		for (int i = 2; i < num_args; i += 2)
		{
			int index = i + 1;
			int outIndex = i;
			PyObject* argObj1 = NctiPyCB.GetTupleItem(m_Args, i);//PyTuple_GetItem(m_Args, i);
			PyObject* argObj2 = NctiPyCB.GetTupleItem(m_Args, index);//PyTuple_GetItem(m_Args, index);
			const Ncti_Char* assembleName = nullptr;
			std::string caption;
			//if (PyUnicode_Check(argObj1))
			if (NctiPyCB.IsUnicode(argObj1))
			{
				const char* name = NctiPyCB.GetUnicodeStr(argObj1);//PyUnicode_AsUTF8(argObj1);
				captions.push_back(name);
				caption = name;
			}
			else
			{
				continue;
			}

			QLabel* label = new QLabel(QString::fromUtf8(caption.c_str()) + ":", this);
			label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
			/*if (PyUnicode_Check(argObj2))
			{
				//argObj2 = PyLong_from("sdfsdfs");
				if (PyUnicode_IS_COMPACT_ASCII(argObj2))
				{
					PyASCIIObject* val = (PyASCIIObject*)argObj2;
					val->wstr = L"234234";
				}
				else
				{
					PyCompactUnicodeObject* val = (PyCompactUnicodeObject*)argObj2;
					val->_base.wstr = L"234234";
				}
			}
			else */

			//if (PyBool_Check(argObj2) && m_bReturn)
			if (NctiPyCB.IsBool(argObj2) && m_bReturn)
			{
				label->setText("");
				NctiCheckBoxData* pCheckBox = new NctiCheckBoxData(&(*m_ReturnArgs)[outIndex / 2 - 1], this);
				pCheckBox->setText(QString::fromUtf8(caption.c_str()));
				layout->addRow(pCheckBox);
				m_CheckBoxVec.push_back(pCheckBox);
			}
			//else if (PyDict_Check(argObj2) && m_bReturn)
			else if (NctiPyCB.IsDict(argObj2) && m_bReturn)
			{
				//PyObjectRef objRef = PyObjectRef::newRef(PyUnicode_FromString("sel"));
				//if (PyDict_Contains(argObj2, objRef.get()))
				if (NctiPyCB.isDictContains(argObj2, "sel"))
				{
					QLabel* labHint = new QLabel(QString("未选择"), this);
					NctiPushButtonData* btn = new NctiPushButtonData(&(*m_ReturnArgs)[outIndex / 2 - 1], labHint, this);
					btn->setText(QString("选取"));
					QHBoxLayout* layoutRow = new QHBoxLayout(widget);
					layoutRow->addWidget(labHint);
					layoutRow->addWidget(btn);
					layout->addRow(label, layoutRow);
					m_PushButtonVec.push_back(btn);
					continue;
				}
				//objRef = PyObjectRef::newRef(PyUnicode_FromString("selFile"));
				//PyObjectRef selFilesRef = PyObjectRef::newRef(PyUnicode_FromString("selFiles"));
				//if (PyDict_Contains(argObj2, objRef.get()) || PyDict_Contains(argObj2, selFilesRef.get()))
				if (NctiPyCB.isDictContains(argObj2, "selFile") || NctiPyCB.isDictContains(argObj2, "selFiles"))
				{
					QLineEdit* labLineEdit = new QLineEdit(QStringLiteral("选择文件"), this);
					NctiPushButtonData* btn = new NctiPushButtonData(&(*m_ReturnArgs)[outIndex / 2 - 1], labLineEdit, this);
					btn->setText(QString("选取"));
					QHBoxLayout* layoutRow = new QHBoxLayout(widget);
					labLineEdit->setReadOnly(true);
					layoutRow->addWidget(labLineEdit);
					layoutRow->addWidget(btn);
					layout->addRow(label, layoutRow);
					m_PushButtonVec.push_back(btn);
					continue;
				}
				//objRef = PyObjectRef::newRef(PyUnicode_FromString("selFolder"));
				//if (PyDict_Contains(argObj2, objRef.get()))
				if (NctiPyCB.isDictContains(argObj2, "selFolder"))
				{
					QLineEdit* labLineEdit = new QLineEdit(QStringLiteral("选择文件夹"), this);
					NctiPushButtonData* btn = new NctiPushButtonData(&(*m_ReturnArgs)[outIndex / 2 - 1], labLineEdit, this);
					btn->setText(QString("选取"));
					QHBoxLayout* layoutRow = new QHBoxLayout(widget);
					labLineEdit->setReadOnly(true);
					layoutRow->addWidget(labLineEdit);
					layoutRow->addWidget(btn);
					layout->addRow(label, layoutRow);
					m_PushButtonVec.push_back(btn);
					continue;
				}
				//objRef = PyObjectRef::newRef(PyUnicode_FromString("saveFile"));
				//if (PyDict_Contains(argObj2, objRef.get()))
				if (NctiPyCB.isDictContains(argObj2, "saveFile"))
				{
					QLineEdit* labLineEdit = new QLineEdit(QStringLiteral("保存文件"), this);
					NctiPushButtonData* btn = new NctiPushButtonData(&(*m_ReturnArgs)[outIndex / 2 - 1], labLineEdit, this);
					btn->setText(QStringLiteral("打开目录"));
					QHBoxLayout* layoutRow = new QHBoxLayout(widget);
					labLineEdit->setReadOnly(true);
					layoutRow->addWidget(labLineEdit);
					layoutRow->addWidget(btn);
					layout->addRow(label, layoutRow);
					m_PushButtonVec.push_back(btn);
					continue;
				}
				//objRef = PyObjectRef::newRef(PyUnicode_FromString("CheckList"));
				//if (PyDict_Contains(argObj2, objRef.get()))
				if (NctiPyCB.isDictContains(argObj2, "CheckList"))
				{
					CheckedListBox* pComboBox = new CheckedListBox(&(*m_ReturnArgs)[outIndex / 2 - 1], this);
					layout->addRow(label, pComboBox);
					m_CheckedListBoVec.push_back(pComboBox);
					continue;
				}
				else
				{
					label->hide();
				}
			}
			else if (NctiPyCB.IsLong(argObj2))
			{
				//long val = PyLong_AsLong(argObj2);				
				PyObject* pObj = argObj2;
				NctiLineEditBoundData* pEditLength = nullptr;
				if(m_bReturn)
				{
					long val = -1;
					if ((*m_ReturnArgs)[outIndex / 2 - 1].isLong())
						val = (*m_ReturnArgs)[outIndex / 2 - 1].getLong();
					else if ((*m_ReturnArgs)[outIndex / 2 - 1].isInt())
						val = (*m_ReturnArgs)[outIndex / 2 - 1].getInt();
					else if ((*m_ReturnArgs)[outIndex / 2 - 1].isInt64())
						val = (*m_ReturnArgs)[outIndex / 2 - 1].getInt64();
					else
					{
						//
					}
					(*m_ReturnArgs)[outIndex / 2 - 1] = Ncti_VariantValue(val);
					pEditLength = new NctiLineEditBoundData(&(*m_ReturnArgs)[outIndex / 2 - 1].getLong(), this);
				}
				else
				{
					pEditLength = new NctiLineEditBoundData(pObj, this);
				}
				layout->addRow(label, pEditLength);
				m_LineEditVec.push_back(pEditLength);
			}
			else if (NctiPyCB.IsFloat(argObj2))
			{
				//double val = PyFloat_AsDouble(argObj2);
				PyObject* pObj = argObj2;
				NctiLineEditBoundData* pEditLength = nullptr;
				if (m_bReturn)
				{
					pEditLength = new NctiLineEditBoundData(&(*m_ReturnArgs)[outIndex / 2 - 1].getDouble(), this);
				}
				else
				{
					pEditLength = new NctiLineEditBoundData(pObj, this);
				}
				layout->addRow(label, pEditLength);
				m_LineEditVec.push_back(pEditLength);
			}
			else if (NctiPyCB.IsUnicode(argObj2) && m_bReturn)
			{
				//const char* name = PyUnicode_AsUTF8(argObj2);
				NctiLineEditBoundData* pEditLength = new NctiLineEditBoundData(&(*m_ReturnArgs)[outIndex / 2 - 1].getString(), this);
				layout->addRow(label, pEditLength);
				m_LineEditVec.push_back(pEditLength);
			}
			else if (NctiPyCB.IsList(argObj2) && m_bReturn)
			{
				NctiComboBoxData* pComboBox = new NctiComboBoxData(&(*m_ReturnArgs)[outIndex / 2 - 1], this);
				layout->addRow(label, pComboBox);
				m_ComboBoxVec.push_back(pComboBox);
			}
			else
			{
				NctiPosition pt;
				NctiVector vec;
				if (argList.GetPosition(index, pt))
				{
					PyObject* argValue = argObj2;
					NctiLineEditBoundData* pEditX = nullptr;
					NctiLineEditBoundData* pEditY = nullptr;
					NctiLineEditBoundData* pEditZ = nullptr;
					if (m_bReturn) 
					{
						NctiPosition& point = (*m_ReturnArgs)[outIndex / 2 - 1].getPosition();
						pEditX = new NctiLineEditBoundData(&point.x(), this);
						pEditY = new NctiLineEditBoundData(&point.y(), this);
						pEditZ = new NctiLineEditBoundData(&point.z(), this);
					}
					else
					{
						NctiPyPointStr* pPyPointStr = (NctiPyPointStr*)argValue;
						pEditX = new NctiLineEditBoundData(&pPyPointStr->x, this);
						pEditY = new NctiLineEditBoundData(&pPyPointStr->y, this);
						pEditZ = new NctiLineEditBoundData(&pPyPointStr->z, this);
					}
					QHBoxLayout* HLayout = new QHBoxLayout();
					HLayout->addWidget(pEditX);HLayout->addWidget(pEditY);HLayout->addWidget(pEditZ);
					layout->addRow(label, HLayout);
					m_LineEditVec.push_back(pEditX);
					m_LineEditVec.push_back(pEditY);
					m_LineEditVec.push_back(pEditZ);
				}
				else if (argList.GetVector(index, vec))
				{
					PyObject* argValue = argObj2;
					NctiLineEditBoundData* pEditX = nullptr;
					NctiLineEditBoundData* pEditY = nullptr;
					NctiLineEditBoundData* pEditZ = nullptr;
					if (m_bReturn) 
					{
						NctiVector& pv = (*m_ReturnArgs)[outIndex / 2 - 1].getVector();
						pEditX = new NctiLineEditBoundData(&pv.x(), this);
						pEditY = new NctiLineEditBoundData(&pv.y(), this);
						pEditZ = new NctiLineEditBoundData(&pv.z(), this);
					}
					else
					{
						NctiPyVectorStr* pPyVectorStr = (NctiPyVectorStr*)argValue;
						QString stringX, stringY, stringZ;
						QTextStream(&stringX) << pPyVectorStr->x;
						QTextStream(&stringY) << pPyVectorStr->y;
						QTextStream(&stringZ) << pPyVectorStr->z;
						pEditX = new NctiLineEditBoundData(&pPyVectorStr->x, this);
						pEditY = new NctiLineEditBoundData(&pPyVectorStr->y, this);
						pEditZ = new NctiLineEditBoundData(&pPyVectorStr->z, this);
					}
					m_LineEditVec.push_back(pEditX);
					m_LineEditVec.push_back(pEditY);
					m_LineEditVec.push_back(pEditZ);

					QHBoxLayout* HLayout = new QHBoxLayout();
					HLayout->addWidget(pEditX);HLayout->addWidget(pEditY);HLayout->addWidget(pEditZ);
					layout->addRow(label, HLayout);
				}
				else
				{
					delete label;
				}
			}
		}
		QHBoxLayout* HLayout3 = new QHBoxLayout();
		HLayout3->addWidget(m_BtnCancel);
		HLayout3->addWidget(m_BtnOK);
		layoutMain->addLayout(HLayout3);
		setLayout(layoutMain);
		connect(m_BtnOK, SIGNAL(clicked(bool)), this, SLOT(ClickOk(bool)));
		connect(m_BtnCancel, SIGNAL(clicked(bool)), this, SLOT(ClickCancel(bool)));
	}

	void NctiPythonShowDlg::ClickCancel(bool boo)
	{
		reject();
	}

	void NctiPythonShowDlg::ClickOk(bool boo)
	{
		for (size_t i =0; i < m_LineEditVec.size(); i++)
		{
			m_LineEditVec[i]->accept();
		}
		for (size_t i = 0; i < m_ComboBoxVec.size(); i++)
		{
			m_ComboBoxVec[i]->accept();
		}
		for (size_t i = 0; i < m_CheckBoxVec.size(); i++)
		{
			m_CheckBoxVec[i]->accept();
		}
		for (size_t i = 0; i < m_PushButtonVec.size(); i++)
		{
			m_PushButtonVec[i]->accept();
		}
		for (size_t i = 0; i < m_CheckedListBoVec.size(); i++)
		{
			m_CheckedListBoVec[i]->accept();
		}

		accept();
	}

}

