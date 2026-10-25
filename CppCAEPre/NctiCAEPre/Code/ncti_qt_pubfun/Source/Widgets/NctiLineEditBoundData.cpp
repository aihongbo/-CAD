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

#include "NctiLineEditBoundData.h"

#include <QFileDialog>
#include <QMessageBox>

#if QT_VERSION_MAJOR >= 6
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#else
#include <QRegExp>
#include <QRegExpValidator>
#endif

#include "NctiDocument.h"
#include "NctiDocElementPubFun.h"

#define Ncti_InterPattern "^(-?\\d+)(\\d+)?$"
#define Ncti_FloatPattern "^(-?\\d+)(\\.\\d+)?$"

namespace NCTI
{
	void NctiLineEditBoundData::setupValidator(const QString& pattern, QWidget* parent)
	{
#if QT_VERSION_MAJOR >= 6
		this->setValidator(new QRegularExpressionValidator(QRegularExpression(pattern), parent));
#else
		this->setValidator(new QRegExpValidator(QRegExp(pattern), parent));
#endif
		this->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(QWidget* parent)
		: QLineEdit(parent)
	{
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(std::string* pStr,
		QWidget* parent /*= nullptr*/,
		bool bRealTimeChange /*= false*/)
		: QLineEdit(parent)
		, m_bRealTimeChange(bRealTimeChange)
		, m_string(pStr)
	{
		if (m_string)
			setText(QString::fromUtf8(m_string->c_str()));
		//setupValidator(Ncti_InterPattern, parent);
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(long* iVal,
		QWidget* parent /*= nullptr*/,
		bool bRealTimeChange /* = false*/)
		: QLineEdit(parent)
		, m_bRealTimeChange(bRealTimeChange)
		, m_iBoundVariable(iVal)
	{
		if (m_iBoundVariable)
			setText(QString::number(*m_iBoundVariable));
		setupValidator(Ncti_InterPattern, parent);
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(double* dVal,
		QWidget* parent /*= nullptr*/,
		bool bRealTimeChange /* = false*/)
		: QLineEdit(parent)
		, m_bRealTimeChange(bRealTimeChange)
		, m_dBoundVariable(dVal)
	{
		if (m_dBoundVariable) {
			QString stringValue = QString::number(*m_dBoundVariable, 'g', 16);
			setText(stringValue);
		}
		setupValidator(Ncti_FloatPattern, parent);
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(PyObject* pArg,
		QWidget* parent /*= nullptr*/,
		bool bRealTimeChange /* = false*/)
		: QLineEdit(parent)
		, m_bRealTimeChange(bRealTimeChange)
		, m_arg(pArg)
	{
		if (m_arg != nullptr) {
			if (NctiPyCB.IsLong(m_arg)) {
				long val = NctiPyCB.GetLong(m_arg);
				setText(QString::number(val));
				setupValidator(Ncti_InterPattern, parent);
			}
			else if (NctiPyCB.IsFloat(m_arg)) {
				double val = NctiPyCB.GetDouble(m_arg);
				QString stringValue = QString::number(val, 'g', 16);
				setText(stringValue);
				setupValidator(Ncti_FloatPattern, parent);
			}
		}
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	NctiLineEditBoundData::NctiLineEditBoundData(NCTI_Variant* pArg,
		QWidget* parent /*= nullptr*/,
		bool bRealTimeChange /*= false*/)

		: QLineEdit(parent)
		, m_bRealTimeChange(bRealTimeChange)
		, m_any(pArg)
	{
		if (m_any != nullptr) {
			if (m_any->index() == 0) {
				long val = m_any->get<long>();
				setText(QString::number(val));
				setupValidator(Ncti_InterPattern, parent);
			}
			if (m_any->index() == 1) {
				double val = m_any->get<double>();
				QString stringValue = QString::number(val, 'g', 16);
				setText(stringValue);
				setupValidator(Ncti_FloatPattern, parent);
			}
			if (m_any->index() == 2) {
				std::string val = m_any->get<std::string>();
				setText(QString::fromUtf8(val.c_str()));
				this->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
			}
		}
		connect(this, &QLineEdit::textChanged, this, &NctiLineEditBoundData::onTextChanged);
	}

	void NctiLineEditBoundData::accept()
	{
		acceptChange(text());
	}

	void NctiLineEditBoundData::onTextChanged(const QString& text)
	{
		if (m_bRealTimeChange)
			acceptChange(text);
		//Q_EMIT variableChanged(text);  // 发出信号通知外部变量变化
	}

	void NctiLineEditBoundData::acceptChange(const QString& text)
	{
		if (m_string != nullptr) {
            QByteArray ba = text.toUtf8();
			*m_string = ba.constData();
		}
		if (m_iBoundVariable != nullptr) {
			*m_iBoundVariable = text.toLong();
		}
		if (m_dBoundVariable != nullptr) {
			*m_dBoundVariable = text.toDouble();
		}

		if (m_arg != nullptr) {
			if (NctiPyCB.IsLong(m_arg)) {
				long lVal = text.toLong();
				PyObject* newVal = NctiPyCB.NewLongPyObject(lVal);
				if (newVal != nullptr) {
					NctiPyCB.DecRef(m_arg);
					m_arg = newVal;
				}
			}
			else if (NctiPyCB.IsFloat(m_arg)) {
				double dVal = text.toDouble();
				PyObject* newVal = NctiPyCB.NewLongPyObject(dVal);
				if (newVal != nullptr) {
					NctiPyCB.DecRef(m_arg);
					m_arg = newVal;
				}
			}
		}

		if (m_any != nullptr) {
			if (m_any->holds_alternative<long>()) {
				long& val = m_any->get<long>();
				val = text.toLong();
			}
			else if (m_any->holds_alternative<double>()) {
				double& val = m_any->get<double>();
				val = text.toDouble();
			}
			else if (m_any->holds_alternative<std::string>()) {
				std::string& val = m_any->get<std::string>();
				QByteArray byt = text.toUtf8();
				val = byt.data();
			}
		}
	}

	NctiComboBoxData::NctiComboBoxData(QWidget* parent)
		: QComboBox(parent)
	{
		connect(this, &QComboBox::currentTextChanged, this, &NctiComboBoxData::onTextChanged);
	}

	NctiComboBoxData::NctiComboBoxData(Ncti_VariantValue* pArg, QWidget* parent)
		: QComboBox(parent)
		, m_any(pArg)
	{
		if (m_any != nullptr) {
			if (m_any->isList()) {
				std::vector<Ncti_VariantValue> val = m_any->getList();
				for (size_t i = 0; i < val.size(); i++) {
					addItem(val[i].getString().c_str());
				}
			}
		}
		connect(this, &QComboBox::currentTextChanged, this, &NctiComboBoxData::onTextChanged);
	}
	void NctiComboBoxData::onTextChanged(const QString& text)
	{
		acceptChange(text);
	}
	void NctiComboBoxData::accept()
	{
		acceptChange(currentText());
	}

	void NctiComboBoxData::acceptChange(const QString& text)
	{
		if (m_any != nullptr) {
			if (m_any->isList()) {
				std::vector<Ncti_VariantValue>& val = m_any->getList();
				val.clear();
				val.push_back(Ncti_VariantValue(text.toStdString()));
			}
		}
	}

	NctiCheckBoxData::NctiCheckBoxData(QWidget* parent)
		: QCheckBox(parent)
	{
		connect(this, &QCheckBox::stateChanged, this, &NctiCheckBoxData::onStateChanged);
	}

	NctiCheckBoxData::NctiCheckBoxData(Ncti_VariantValue* pArg, QWidget* parent)
		: QCheckBox(parent)
		, m_any(pArg)
	{
		if (m_any != nullptr) {
			if (m_any->isLong()) {
				long val = m_any->getLong();
				setChecked(val);
			}
		}
		connect(this, &QCheckBox::stateChanged, this, &NctiCheckBoxData::onStateChanged);
	}
	void NctiCheckBoxData::onStateChanged(const int& text)
	{
		acceptChange(text);
	}
	void NctiCheckBoxData::accept()
	{
		acceptChange(isChecked());
	}

	void NctiCheckBoxData::acceptChange(const int& text)
	{
		if (m_any != nullptr) {
			if (m_any->isLong()) {
				long& val = m_any->getLong();
				if (Qt::CheckState::Unchecked == text) {
					val = 0;
				}
				else {
					val = 1;
				}
			}
			if (m_any->isBool()) {
				bool& val = m_any->getBool();
				if (Qt::CheckState::Unchecked == text) {
					val = 0;
				}
				else {
					val = 1;
				}
			}
		}
	}

	NctiPushButtonData::NctiPushButtonData(Ncti_VariantValue* pArg, QLabel* linkLab, QWidget* parent)
		: QPushButton(parent)
		, m_any(pArg)
		, m_lab(linkLab)
	{
		connect(this, &QPushButton::clicked, this, &NctiPushButtonData::onAcceptClicked);
	}

	NctiPushButtonData::NctiPushButtonData(Ncti_VariantValue* pArg, QLineEdit* linkEdit, QWidget* parent /*= nullptr*/)
		: QPushButton(parent)
		, m_any(pArg)
		, m_FileLineEdit(linkEdit)
	{
		connect(this, &QPushButton::clicked, this, &NctiPushButtonData::onAcceptClicked);
	}

	void NctiPushButtonData::onAcceptClicked()
	{
		acceptClicked();
	}
	void NctiPushButtonData::accept()
	{
		if (m_lab != nullptr) {
			if (m_any != nullptr && m_any->isMap()) {
				std::map<std::string, Ncti_VariantValue>& mapValue = m_any->getMap();
				if (m_lab->text() == QString("未选择")) {

					/*mapValue["sel"] = mapValue["sel"].get<std::vector<MapVariant>>();
					mapValue["cellIds"] = mapValue["cellIds"].get<std::vector<MapVariant>>();*/


					//mapValue["sel"] = mapValue["sel"].get<std::vector<std::string>>();
					//if (mapValue.find("sel") != mapValue.end())
					//	/*mapValue.erase("sel");*/
					//	mapValue["sel"] = mapValue["sel"].get<std::vector<std::string>>();
					//if (mapValue.find("cellIds") != mapValue.end())
					//	/*mapValue.erase("cellIds");*/
					//	mapValue["cellIds"] = mapValue["cellIds"].get<std::vector<std::string>>();
					//}
				}
			}
		}
	}

	void NctiPushButtonData::acceptClicked()
	{
		if (m_any != nullptr) {
			if (m_any->isMap()) {
				std::map<std::string, Ncti_VariantValue>& mapValue = m_any->getMap();
				if (mapValue.find("sel") != mapValue.end() && mapValue.find("docID") != mapValue.end()) {
					long nId = mapValue["docID"].getLong();
					NctiDocument* pDocment = NctiDocumentManager::instance()->GetDocument(nId);
					if (pDocment == nullptr)
						return;
					
					std::vector<Ncti_VariantValue> o_ObjNameVarVle;
					std::vector<Ncti_VariantValue> o_CellIdVarVle;
					std::vector<std::string> o_ObjectNameVec; //实体对象的名称列表
					std::vector<Ncti_Long> o_CellIDVec;       //实体对象的点线面ID序号列表
					std::vector<NctiTopoCell*> topo;
					NctiDocElementPubFun::GetNameFromSelManager(pDocment, o_ObjectNameVec, o_CellIDVec, topo);
					if (!o_ObjectNameVec.empty()) {

						std::string ret;
						ret += "sel:[";
						for (auto& name : o_ObjectNameVec) {
							ret += "\"";
							ret += name;
							ret += "\" ";
							o_ObjNameVarVle.push_back(Ncti_VariantValue(name));
						}
						if (ret.back() == ' ')
							ret.pop_back();
						ret += "]\ncellIds:[";
						for (auto id : o_CellIDVec) {
							ret += std::to_string(id);
							ret += " ";
							o_CellIdVarVle.push_back(Ncti_VariantValue(id));
						}
						if (ret.back() == ' ')
							ret.pop_back();
						ret += "]";
						m_lab->setToolTip(QString::fromUtf8(ret.c_str()));
						m_lab->setText(QString("已选择"));

						mapValue["sel"] = Ncti_VariantValue(o_ObjNameVarVle);
						mapValue["cellIds"] = Ncti_VariantValue(o_CellIdVarVle);
					}
					else {
						m_lab->setToolTip("");
						m_lab->setText("未选择");
						/*if (mapValue.find("names") != mapValue.end())
							mapValue.erase("names");
						if (mapValue.find("cellIds") != mapValue.end())
							mapValue.erase("cellIds");*/
						QMessageBox::information(this, QString("提示"), QString("未选择对象"));
					}
				}
				else if ((mapValue.find("selFile") != mapValue.end() || (mapValue.find("selFiles") != mapValue.end()))
					&& mapValue.find("docID") != mapValue.end()) {
					std::string strFilter("Files(*.igs *.stp *.step *.fbx *.prt)");
					if (mapValue.find("filter") != mapValue.end())
						strFilter = mapValue["filter"].getString();

					{
						QString strShowContext;
						if (mapValue.find("selFiles") != mapValue.end()) {
							QStringList filePaths = QFileDialog::getOpenFileNames(
								this, QStringLiteral("选择多个文件"), "", QString::fromStdString(strFilter));

							std::vector<Ncti_VariantValue> vetSelFiles;
							for (const auto& fileName : filePaths) {
								strShowContext += fileName + ",";
								vetSelFiles.push_back(Ncti_VariantValue(fileName.toStdString()));
							}
							mapValue["selFiles"] = Ncti_VariantValue(vetSelFiles);
							strShowContext = strShowContext.left(strShowContext.size() - 1);
						}
						else {
							strShowContext = QFileDialog::getOpenFileName(
								this, QStringLiteral("选择单个文件"), "", QString::fromStdString(strFilter));
							mapValue["selFile"] = Ncti_VariantValue(strShowContext.toStdString());
						}

						m_FileLineEdit->setText(strShowContext);
						m_FileLineEdit->setCursorPosition(m_FileLineEdit->text().length());
						mapValue["filter"] = Ncti_VariantValue(mapValue["filter"].getString());
					}
				}
				else if (mapValue.find("selFolder") != mapValue.end() && mapValue.find("docID") != mapValue.end()) {
					std::string strFolder;
					if (mapValue.find("selFolder") != mapValue.end())
						strFolder = mapValue["selFolder"].getString();
					QString dirPath = QFileDialog::getExistingDirectory(
						this,
						QStringLiteral("选择文件夹"),
						QString::fromStdString(strFolder), // 可以是起始路径，也可以是空字符串，让对话框显示在默认位置
						QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

					if (!dirPath.isEmpty()) {
						m_FileLineEdit->setText(dirPath);
						m_FileLineEdit->setCursorPosition(m_FileLineEdit->text().length());
						mapValue["selFolder"] = Ncti_VariantValue(dirPath.toStdString());
					}
					//else
					//{
					//	//设置默认值
					//	mapValue["selFolder"] = std::get<std::string>(mapValue["selFolder"]);
					//}
				}
				else if (mapValue.find("saveFile") != mapValue.end() && mapValue.find("docID") != mapValue.end()) {
					std::string strFilter("Files(*.*)");
					if (mapValue.find("filter") != mapValue.end())
						strFilter = mapValue["filter"].getString();

					std::string strSaveName;
					if (mapValue.find("filter") != mapValue.end())
						strSaveName = mapValue["saveFile"].getString();
					QString fileName = QFileDialog::getSaveFileName(this,
						QStringLiteral("保存文件"),
						QString::fromStdString(strSaveName),
						QString::fromStdString(strFilter));

					if (!fileName.isEmpty()) {
						m_FileLineEdit->setText(fileName);
						m_FileLineEdit->setCursorPosition(m_FileLineEdit->text().length());

						mapValue["saveFile"] = Ncti_VariantValue(fileName.toStdString());
					}
					mapValue["filter"] = Ncti_VariantValue(strFilter);
				}
			}
		}
	}

	CheckedListBox::CheckedListBox(QWidget* parent /*= nullptr*/)
	{
		//connect(this, &QListWidget::itemChanged, this, &CheckedListBox::itemChanged);
	}

	CheckedListBox::CheckedListBox(Ncti_VariantValue* pArg, QWidget* parent /*= nullptr*/)
		: QListWidget(parent)
		, m_any(pArg)
	{
		if (m_any != nullptr && m_any->isMap()) {
			std::map<std::string, Ncti_VariantValue>& mapValue = m_any->getMap();
			std::vector<Ncti_VariantValue>& val = mapValue["CheckList"].getList();
			for (size_t i = 0; i < val.size(); i++) {
				//addItem(val[i].c_str(), false);
				QListWidgetItem* item = new QListWidgetItem(val[i].getString().c_str());
				item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
				item->setCheckState(false ? Qt::Checked : Qt::Unchecked);
				QListWidget::addItem(item);
			}
		}
		//connect(this, &QListWidget::itemChanged, this, &CheckedListBox::itemChanged);
	}

	std::vector<std::string> CheckedListBox::checkedItems()
	{
		std::vector<std::string> list;
		for (int i = 0; i < count(); ++i) {
			QListWidgetItem* item = this->item(i);
			if (item && item->checkState() == Qt::Checked) {
				list.push_back(item->text().toStdString());
			}
		}
		return list;
	}

	void CheckedListBox::accept()
	{
		if (m_any != nullptr && m_any->isMap()) {
			std::map<std::string, Ncti_VariantValue>& mapValue = m_any->getMap();
			std::vector<Ncti_VariantValue>& val = mapValue["CheckList"].getList();
			val.clear();
			std::vector<std::string> vec = checkedItems();
			for (int i = 0; i < vec.size(); ++i)
			{
				val.push_back(Ncti_VariantValue(vec[i]));
			}
		}
	}
}// namespace NCTI