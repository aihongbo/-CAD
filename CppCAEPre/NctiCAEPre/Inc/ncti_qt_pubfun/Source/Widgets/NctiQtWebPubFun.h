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

#pragma once

#ifdef NCTI_ENABLE_AIQA_SERVICE

#include <QObject>
#include <QtGlobal>
#include <QWebEnginePage>

namespace NCTI
{
	enum PageTypea
	{
		AiAssistant,
		AiCodeStore
	};
	class NctiQtWebPubFunDelegate;
	class NctiQtWebPubFun : public QObject
	{
		Q_OBJECT 
	public:
		NctiQtWebPubFun(QObject* parent = nullptr);
		virtual ~NctiQtWebPubFun();

		Q_DISABLE_COPY_MOVE(NctiQtWebPubFun);

		template <typename T1, typename T2>
		static QVariantMap createResult(int code, T1&& msg, T2&& data)
		{
			return {
				{"code", code},
				{"msg", std::forward<T1>(msg)},
				{"data", std::forward<T2>(data)}
			};
		}

		void setDelegate(NctiQtWebPubFunDelegate* delegate);
		void updateCodeStore();

		void SetAiAssistentPage(QWebEnginePage* page) { m_AiAssistentPage = page; }
		void SetCodeStorePage(QWebEnginePage* page) { m_CodeStorePage = page; }
	
	private:
		bool loadJsonData(const QString& jsonPath, QString& jsonStr, QJsonDocument& jsonDoc);
		void saveJsonData(const QJsonDocument& jsonDoc, const QString& path);

	private:
		NctiQtWebPubFunDelegate* m_Delegate{ nullptr };
		QJsonArray* m_MessageJson{ nullptr };
		QJsonObject* m_CodeJson{ nullptr };
		QString m_MessagePath;
		QString m_CodePath;
		QWebEnginePage* m_AiAssistentPage{ nullptr };
		QWebEnginePage* m_CodeStorePage{ nullptr };

	public Q_SLOTS:
		void receiveDataFromWeb(const QString& data);

		/*
		* @brief 执行脚本
		*/
		QVariantMap runScript(const QString& content);

		/*
		* @brief 获取对话，默认以时间戳降序
		* @param pageIndex 分页编号
		* @parem countPerPage 每一页最大数量
		* 
		* 返回字典
		* {
		*	code: 1成功
		*	msg:  
		*	data: [{
		*			ts: 时间戳 
		*			msgID:	消息id（时间戳）
		*			isAsk: 是否为提问
		*			askID: 消息对应的提问ID，如果消息为提问消息，则为自身msgID
		*			content: 对话内容
		*		},
		*		...
		*	]
		* }
		*/
		QVariantMap getChatMessage(int pageIndex, int countPerPage);

		/*
		* @brief 保存对话
		* [
		*	{
		*		ts:时间戳, 
		*		isAsk: 是否为提问
		*		msgID:	消息id（时间戳）
		*		askID: 消息对应的提问ID，如果消息为提问消息，则为自身msgID
		*		content: 内容
		*	}
		* ]
		* 
		* 返回字典
		* {
		*	code:
		*	msg:
		*	data:
		* }
		*/
		QVariantMap saveChatMessage(const QVariantList & data);

		/*
		* @brief 获取收藏
		* @param pageIndex 分页编号
		* @parem countPerPage 每一页最大收藏条目数量，
		*	如果当页最后一个所有收藏超过当前页最大收藏条目数，则会被分割，下一页开始是上一页的一部分
		* 
		* 返回字典
		* {
		*	code:
		*	msg:
		*	data:[
		*			{
		*				askID: 提问的msgID
		*				askTs: 提问的时间戳
		*				askContent: 提问的内容
		*				content:[script1, script2, script3....] 提问对应的收藏
		*			},
		*			...
		*	]
		* }
		*/
		QVariantMap getChatFavorites(int pageIndex, int countPerPage);


		/*
		* @brief 收藏
		* [
		*	{
		*		askID: 收藏对应提问的msgID
		*		favID: 收藏ID（点击收藏的时间戳）
		*		content: 收藏内容
		*	},
		*	...
		* ]
		* 
		* 返回字典
		* {
		*	code:
		*	msg:
		*	data:
		* }
		*/
		QVariantMap saveChatFavorites(const QVariantList& data);

		void runCode(const QString& data);
		void storeCode(const QString& data);
		void bindCode(const QString& data);
		void removeStore(const QString& message);
		void updateAiAssitent(const QString& message);
		void onAiAnswered(const QString& message);
		void clearDialog();
		QString getJsonData(const QString& message);
		QString loadAiMessage();
		QString loadCodeSore();
	};
}
#endif