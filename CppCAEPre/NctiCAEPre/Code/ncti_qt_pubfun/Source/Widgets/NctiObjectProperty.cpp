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

#include "NctiObjectProperty.h"

#include <QVBoxLayout>
#include <QtVariantProperty>
#include <QtTreePropertyBrowser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "NctiDocTreePubFun.h"
#include "NctiObjectTree.h"

namespace NCTI
{
    NctiObjectProperty::NctiObjectProperty( QWidget* p_parent)
        : QFrame(p_parent)
    {
        setupUI();
    }

	void NctiObjectProperty::SetModelObject(void* pObj, const NctiTreeViewType& viewType)
	{
		if (m_PropertyBrowser == nullptr)
			return;
		QList<QtProperty*> properties = m_PropertyBrowser->properties();
		for(int i = 0; i < properties.size(); i++)
		{
			m_PropertyBrowser->removeProperty(properties[i]);
		}
		if (pObj == nullptr)
			return;
		std::string jsonDB;
		if (viewType == NctiTreeViewType::Scene)
		{
			if (!NctiDocTreePubFun::GetRenderPropData(pObj, jsonDB))
				return;
		}
		else
		{
			if (!NctiDocTreePubFun::GetObjectPropData(pObj, jsonDB))
				return;
		}
		QJsonParseError jsonError;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonDB.c_str(), &jsonError));
		if (jsonError.error != QJsonParseError::NoError)
		{
			return;
		}
		QJsonObject root = jsonDoc.object();
		QString strName = "PropData";
		if (!root.contains(strName))
			return;
		QJsonValue rootNext = root.value(strName);
		QJsonObject jsonObject = rootNext.toObject();

		QJsonObject::Iterator it;
		for (it = jsonObject.begin(); it != jsonObject.end(); it++)
		{
			QString name = it.key();
			QJsonValue valueObj = it.value();
			//qDebug() << name;
			QtProperty* groupItem = m_PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(),
				name);
			ParameterJson(groupItem, valueObj);
			if (groupItem->subProperties().size() > 0)
				m_PropertyBrowser->addProperty(groupItem);
			else
				delete groupItem;
		}
	}

	void NctiObjectProperty::ParameterJson(QtProperty* groupItem, QJsonValue& jsonVal)
	{
		std::function<void(QString, QtVariantProperty*&, QJsonValue&, bool&)> CreateProperty = [&]
		(QString name, QtVariantProperty*& item, QJsonValue& valueObj, bool& bSub)
			{
				if (valueObj.isObject())
				{
					item = m_PropertyManager->addProperty(QtVariantPropertyManager::groupTypeId(),
						name);
					bSub = true;
				}
				else
				{
#if QT_VERSION_MAJOR >= 6
                    item = m_PropertyManager->addProperty(QMetaType::QString, name);
#else
                    item = m_PropertyManager->addProperty(QVariant::String, name);
#endif
					QString str;
					if (valueObj.isBool())
						str = QStringLiteral("%1").arg(valueObj.toBool());
					else if (valueObj.isDouble())
						str = QStringLiteral("%1").arg(valueObj.toDouble());
					else if (valueObj.isString())
						str = QStringLiteral("%1").arg(valueObj.toString());
					item->setValue(str);
					item->setAttribute(QLatin1String("readOnly"), true);
					bSub = false;
				}
			};
		std::function<void(QJsonObject&, QtProperty*&)> DisObject = [&]
		(QJsonObject& jsonObj, QtProperty*& groupItem)
			{
				QJsonObject::Iterator it;
				for (it = jsonObj.begin(); it != jsonObj.end(); it++)
				{
					QString name = it.key();
					QJsonValue valueObj = it.value();
					QtVariantProperty* item;
					bool bSub = false;
					CreateProperty(name, item, valueObj, bSub);
					if (bSub)
					{
						ParameterJson(item, valueObj);
						groupItem->addSubProperty(item);
					}
					else
						groupItem->addSubProperty(item);
				}
			};
		if (jsonVal.isArray())
		{
			QJsonArray jsonArray = jsonVal.toArray();

			for (auto iter = jsonArray.constBegin(); iter != jsonArray.constEnd(); ++iter)
			{
				QJsonObject jsonObj = (*iter).toObject();
				DisObject(jsonObj, groupItem);
			}
		}
		else if (jsonVal.isObject())
		{
			QJsonObject jsonObj = jsonVal.toObject();
			DisObject(jsonObj, groupItem);
			/*QJsonObject::Iterator it;
			for (it = jsonObj.begin(); it != jsonObj.end(); it++)
			{
				QString name = it.key();
				QJsonValue valueObj = it.value();
				QtVariantProperty* item;
				bool bSub = false;
				CreateProperty(name, item, valueObj, bSub);
				if (bSub)
				{
					ParameterJson(item, valueObj);
					groupItem->addSubProperty(item);
				}
				else
					groupItem->addSubProperty(item);
			}*/
		}
	}

	void NctiObjectProperty::setupUI()
	{
		auto mainLayout = new QVBoxLayout(this);
		m_PropertyBrowser = new QtTreePropertyBrowser();
		m_PropertyManager = new QtVariantPropertyManager();

		QFont font;
		font.setPointSize(8);
        m_PropertyBrowser->setFont(font);
		QtVariantEditorFactory* pPropertyFactory= new QtVariantEditorFactory();
		m_PropertyBrowser->setFactoryForManager(m_PropertyManager, pPropertyFactory);
        QStringList head; 
        head << QStringLiteral("属性") << QStringLiteral("值");
		m_PropertyBrowser->setHeaderLabels(head);
		mainLayout->addWidget(m_PropertyBrowser);
	}
}

