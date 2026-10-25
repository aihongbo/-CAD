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

#ifdef NCTI_ENABLE_AIQA_SERVICE

#include "NctiQtWebPubFun.h"
#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include "NctiQtWebPubFunDelegate.h"

namespace NCTI
{
	NctiQtWebPubFun::NctiQtWebPubFun(QObject* parent)
		: QObject(parent)
        , m_MessageJson(new QJsonArray())
        , m_CodeJson(new QJsonObject())
	{
		QString dirPath = QDir(QCoreApplication::applicationDirPath()).absolutePath();
		m_MessagePath = QDir(dirPath).filePath("output.json");
		m_CodePath = QDir(dirPath).filePath("codeStore.json");

	}
	NctiQtWebPubFun::~NctiQtWebPubFun()
	{}

	void NctiQtWebPubFun::setDelegate(NctiQtWebPubFunDelegate* delegate)
	{
		m_Delegate = delegate;
	}

	void NctiQtWebPubFun::updateCodeStore()
	{
		QString jsonData;
		QJsonDocument jsonDoc;
		loadJsonData(m_CodePath, jsonData, jsonDoc);
		m_CodeStorePage->runJavaScript(QString("updateCodeStorePage(%1);").arg(jsonData));
	}

	bool NctiQtWebPubFun::loadJsonData(const QString& jsonPath, QString& jsonStr, QJsonDocument& jsonDoc)
	{
		QFile file(jsonPath);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "无法打开 " << jsonPath << " 文件进行读取！";
			return false;
		}

		QTextStream stream(&file);
#if QT_VERSION_MAJOR >= 6
        stream.setEncoding(QStringConverter::Utf8);
#else
        stream.setCodec("UTF-8");
#endif
		jsonStr = stream.readAll();
		file.close();
		QJsonParseError parseError;
		jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
		return true;
	}

	void NctiQtWebPubFun::saveJsonData(const QJsonDocument& jsonDoc, const QString& path)
	{
		QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);
		QFile file(path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			file.write(jsonData);
			file.close();
			qDebug() << "JSON 文件保存成功！";
		}
		else {
			qDebug() << "无法打开文件进行写入！";
		}
	}


	void NctiQtWebPubFun::receiveDataFromWeb(const QString& data)
	{
		qDebug() << "Received data from web:" << data;
	}

	QVariantMap NctiQtWebPubFun::runScript(const QString& content)
	{
		if (m_Delegate) {
			return m_Delegate->runScript(content);
		}
		return createResult(-1, "", QVariantMap());
	}

	QVariantMap NctiQtWebPubFun::getChatMessage(int pageIndex, int countPerPage)
	{
		if (m_Delegate) {
			return m_Delegate->getChatMessage(pageIndex, countPerPage);
		}
		return createResult(-1, "", QVariantList());
	}
	QVariantMap NctiQtWebPubFun::saveChatMessage(const QVariantList& data)
	{
		if (m_Delegate) {
			return m_Delegate->saveChatMessage(data);
		}
		return createResult(-1, "", QVariantMap());
	}

	QVariantMap NctiQtWebPubFun::getChatFavorites(int pageIndex, int countPerPage)
	{
		if (m_Delegate) {
			return m_Delegate->getChatFavorites(pageIndex, countPerPage);
		}
		return createResult(-1, "", QVariantList());
	}

	QVariantMap NctiQtWebPubFun::saveChatFavorites(const QVariantList& data)
	{
		if (m_Delegate) {
			return m_Delegate->saveChatFavorites(data);
		}
		return createResult(-1, "", QVariantMap());
	}

	void NctiQtWebPubFun::runCode(const QString& data)
	{
		if (m_Delegate)
			m_Delegate->runScript(data);		
	}

	void NctiQtWebPubFun::storeCode(const QString& codeData)
	{
		QJsonParseError parseError;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(codeData.toUtf8().data(), &parseError);
		QJsonObject jsonObj = jsonDoc.object();
		const QString& timeStemp = jsonObj["time"].toString();
		const QString& code = jsonObj["code"].toString();
		const QString& codeIndex = jsonObj["codeIndex"].toString();
		const QString& question = jsonObj["question"].toString();
		if (m_CodeJson->contains(timeStemp)) {
			QJsonObject codeStoreObj = (*m_CodeJson)[timeStemp].toObject();
			QJsonObject codesObj = codeStoreObj["codes"].toObject();
			codesObj[codeIndex] = code;

			codeStoreObj["codes"] = codesObj;
			(*m_CodeJson)[timeStemp] = codeStoreObj;
		}
		else {
			QJsonObject codesObj = QJsonObject();
			codesObj[codeIndex] = code;

			QJsonObject codeStoreObj = QJsonObject();
			codeStoreObj["question"] = question;
			codeStoreObj["codes"] = codesObj;
			(*m_CodeJson)[timeStemp] = codeStoreObj;

		}

		saveJsonData(QJsonDocument(*m_CodeJson), m_CodePath);
	}

	void NctiQtWebPubFun::bindCode(const QString& codeData)
	{
		QJsonParseError parseError;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(codeData.toUtf8().data(), &parseError);
		QJsonObject jsonObj = jsonDoc.object();
		const QString& timeStemp = jsonObj["index"].toString();
		const QString& codeIndex = jsonObj["codeIndex"].toString();

		if (m_CodeJson->contains(timeStemp)) {
			QJsonObject codeStoreObj = (*m_CodeJson)[timeStemp].toObject();
			QJsonObject codesObj = codeStoreObj["codes"].toObject();
			qDebug() << "名称" << codeStoreObj["question"].toString();
			qDebug() << "代码" << codesObj[codeIndex].toString();
		}

	}

	void NctiQtWebPubFun::removeStore(const QString& codeData)
	{
		QJsonParseError parseError;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(codeData.toUtf8().data(), &parseError);
		QJsonObject jsonObj = jsonDoc.object();
		const QString& qestionIndex = jsonObj["qestionIndex"].toString();
		const QString& index = jsonObj["index"].toString();

		QJsonObject codeStoreObj = (*m_CodeJson)[qestionIndex].toObject();
		QJsonObject codesObj = codeStoreObj["codes"].toObject();
		codesObj.remove(index);

		if (codesObj.count() == 0) {
			m_CodeJson->remove(qestionIndex);
		}
		else {
			codeStoreObj["codes"] = codesObj;
			(*m_CodeJson)[qestionIndex] = codeStoreObj;
		}

		saveJsonData(QJsonDocument(*m_CodeJson), m_CodePath);
		m_AiAssistentPage->runJavaScript(QString("updateCodeStatus(%1);").arg(codeData));
	}

	void NctiQtWebPubFun::updateAiAssitent(const QString& message)
	{
	}

	void NctiQtWebPubFun::onAiAnswered(const QString& message)
	{
		QJsonParseError parseError;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8().data(), &parseError);

		m_MessageJson->append(jsonDoc.object());

		saveJsonData(QJsonDocument(*m_MessageJson), m_MessagePath);
	}

	void NctiQtWebPubFun::clearDialog()
	{
		m_MessageJson = new QJsonArray();

		saveJsonData(QJsonDocument(*m_MessageJson), m_MessagePath);
	}

	QString NctiQtWebPubFun::getJsonData(const QString& message)
	{
		qDebug() << "=====page loaded======";

		if (message.compare("/AiAssistant") == 0)
		{
			QString jsonData;
			QJsonDocument jsonDoc;
			bool success = loadJsonData(m_CodePath, jsonData, jsonDoc);
			if (success)
			{
				m_CodeJson = new QJsonObject(jsonDoc.object());
			}

			success = loadJsonData(m_MessagePath, jsonData, jsonDoc);
			if (success)
			{
				m_MessageJson = new QJsonArray(jsonDoc.array());
			}

			return QString(jsonData);
		}
		else if (message.compare("/AiCodeStore") == 0) {
			QString jsonData;
			QJsonDocument jsonDoc;
			loadJsonData(m_CodePath, jsonData, jsonDoc);
			m_CodeJson = new QJsonObject(jsonDoc.object());

			return QString(jsonData);
		}
		return "";
	}

	QString NctiQtWebPubFun::loadAiMessage()
	{
		QString jsonData;
		QJsonDocument jsonDoc;
		bool success = loadJsonData(m_MessagePath, jsonData, jsonDoc);
		if (success)
		{
			m_MessageJson = new QJsonArray(jsonDoc.array());
		}

		return QString(jsonData);
	}

	QString NctiQtWebPubFun::loadCodeSore()
	{
		QString jsonData;
		QJsonDocument jsonDoc;
		bool success = loadJsonData(m_CodePath, jsonData, jsonDoc);
		if (success)
		{
			m_CodeJson = new QJsonObject(jsonDoc.object());

			qDebug() << m_CodeJson->size();
		}

		return QString(jsonData);
	}
};
#endif