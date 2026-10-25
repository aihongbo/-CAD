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

#ifndef NctiLineEditBoundData_H
#define NctiLineEditBoundData_H

#include "dcl_ncti_qt_pubfun.h"
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QListWidget>
#include "NctiPosition.h"
#include "NctiVector.h"
//#include "NctiPythonShowDlg.h"
#include "NCTIVariant.h"
#include "CallbackInterfaces.h"

namespace NCTI
{
	//typedef std::map<std::string, std::variant<long, double, std::string, std::vector<std::string>, std::vector<long>>> NCTI_Map;  ///< NCTI映射类型
	//typedef std::variant<long, double, std::string, NctiPosition, NctiVector, std::vector<std::string>, NCTI_Map> NCTI_Variant;      ///< NCTI变体类型
	
	/**
	 * @brief 行编辑框绑定数据类
	 * @details 用于绑定行编辑框数据的控件类，支持多种数据类型的绑定和实时更新
	 */
	class DECL_NCTI_QT_PUBFUN NctiLineEditBoundData : public QLineEdit
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		NctiLineEditBoundData(QWidget* parent = nullptr);
		
		/**
		 * @brief 构造函数
		 * @param pStr 字符串指针
		 * @param parent 父窗口指针
		 * @param bRealTimeChange 是否实时改变
		 */
		NctiLineEditBoundData(std::string* pStr, QWidget* parent = nullptr, bool bRealTimeChange = false);
		
		/**
		 * @brief 构造函数
		 * @param iVal 长整型指针
		 * @param parent 父窗口指针
		 * @param bRealTimeChange 是否实时改变
		 */
		NctiLineEditBoundData(long* iVal, QWidget* parent = nullptr, bool bRealTimeChange = false);
		
		/**
		 * @brief 构造函数
		 * @param dVal 双精度浮点数指针
		 * @param parent 父窗口指针
		 * @param bRealTimeChange 是否实时改变
		 */
		NctiLineEditBoundData(double* dVal, QWidget* parent = nullptr, bool bRealTimeChange = false);
		
		/**
		 * @brief 构造函数
		 * @param pArg Python对象指针
		 * @param parent 父窗口指针
		 * @param bRealTimeChange 是否实时改变
		 */
		NctiLineEditBoundData(PyObject* pArg, QWidget* parent = nullptr, bool bRealTimeChange = false);
		
		/**
		 * @brief 构造函数
		 * @param pArg 变体指针
		 * @param parent 父窗口指针
		 * @param bRealTimeChange 是否实时改变
		 */
		NctiLineEditBoundData(NCTI_Variant* pArg, QWidget* parent = nullptr, bool bRealTimeChange = false);
		
		/**
		 * @brief 接受输入
		 */
		void accept();
		
	Q_SIGNALS:
		/**
		 * @brief 变量改变信号
		 * @param newValue 新值
		 */
		void variableChanged(const QString& newValue);

	private Q_SLOTS:
		/**
		 * @brief 文本改变槽函数
		 * @param text 文本内容
		 */
		void onTextChanged(const QString& text);

	private:
		/**
		 * @brief 设置验证器
		 * @param pattern 模式
		 * @param parent 父窗口指针
		 */
        void setupValidator(const QString& pattern, QWidget* parent);
        
        /**
         * @brief 接受改变
         * @param text 文本内容
         */
		void acceptChange(const QString& text);
		
	private:
		std::string* m_string{ nullptr };          ///< 字符串指针
		bool m_bRealTimeChange{ true };            ///< 是否实时改变
		long* m_iBoundVariable{nullptr};           ///< 长整型变量指针
		double* m_dBoundVariable{ nullptr };       ///< 双精度浮点数变量指针
		PyObject* m_arg{ nullptr };                ///< Python对象指针
		NCTI_Variant* m_any{ nullptr };            ///< 变体指针
	};

	/**
	 * @brief 组合框数据类
	 * @details 用于组合框数据绑定的控件类，支持变体类型数据的绑定和更新
	 */
	class DECL_NCTI_QT_PUBFUN NctiComboBoxData : public QComboBox
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		NctiComboBoxData(QWidget* parent = nullptr);
		
		/**
		 * @brief 构造函数
		 * @param pArg 变体指针
		 * @param parent 父窗口指针
		 */
		NctiComboBoxData(Ncti_VariantValue* pArg, QWidget* parent = nullptr);
		
		/**
		 * @brief 接受输入
		 */
		void accept();
		
	Q_SIGNALS:
		/**
		 * @brief 变量改变信号
		 * @param newValue 新值
		 */
		void variableChanged(const QString& newValue);

	private Q_SLOTS:
		/**
		 * @brief 文本改变槽函数
		 * @param text 文本内容
		 */
		void onTextChanged(const QString& text);

	private:
		/**
		 * @brief 接受改变
		 * @param text 文本内容
		 */
		void acceptChange(const QString& text);
		
	private:
		Ncti_VariantValue* m_any{ nullptr };            ///< 变体指针
	};

	/**
	 * @brief 复选框数据类
	 * @details 用于复选框数据绑定的控件类，支持变体类型数据的绑定和更新
	 */
	class DECL_NCTI_QT_PUBFUN NctiCheckBoxData : public QCheckBox
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		NctiCheckBoxData(QWidget* parent = nullptr);
		
		/**
		 * @brief 构造函数
		 * @param pArg 变体指针
		 * @param parent 父窗口指针
		 */
		NctiCheckBoxData(Ncti_VariantValue* pArg, QWidget* parent = nullptr);
		
		/**
		 * @brief 接受输入
		 */
		void accept();

	private Q_SLOTS:
		/**
		 * @brief 状态改变槽函数
		 * @param text 状态文本
		 */
		void onStateChanged(const int& text);

	private:
		/**
		 * @brief 接受改变
		 * @param text 状态文本
		 */
		void acceptChange(const int& text);
		
	private:
		Ncti_VariantValue* m_any{ nullptr };            ///< 变体指针
	};

	/**
	 * @brief 按钮数据类
	 * @details 用于按钮数据绑定的控件类，支持变体类型数据的绑定和更新
	 */
	class DECL_NCTI_QT_PUBFUN NctiPushButtonData : public QPushButton
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param pArg 变体指针
		 * @param linkLab 标签指针
		 * @param parent 父窗口指针
		 */
		NctiPushButtonData(Ncti_VariantValue* pArg, QLabel* linkLab, QWidget* parent = nullptr);

		NctiPushButtonData(Ncti_VariantValue* pArg, QLineEdit* linkEdit, QWidget* parent = nullptr);
		
		/**
		 * @brief 接受输入
		 */
		void accept();



	private Q_SLOTS:
		/**
		 * @brief 接受点击槽函数
		 */
		void onAcceptClicked();


	private:
		/**
		 * @brief 接受点击
		 */
		void acceptClicked();
		
	private:
		Ncti_VariantValue* m_any{ nullptr };            ///< 变体指针
		QLabel* m_lab{ nullptr };                  ///< 标签指针
		QLineEdit* m_FileLineEdit{ nullptr };
	};

	/**
	 * @brief 复选列表
	 * @details 用于组合框数据绑定的控件类，支持变体类型数据的绑定和更新
	 */
	class DECL_NCTI_QT_PUBFUN CheckedListBox : public QListWidget
	{
		Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param parent 父窗口指针
		 */
		CheckedListBox(QWidget* parent = nullptr);

		/**
		 * @brief 构造函数
		 * @param pArg 变体指针
		 * @param parent 父窗口指针
		 */
		CheckedListBox(Ncti_VariantValue* pArg, QWidget* parent = nullptr);

		std::vector<std::string> checkedItems();
		/**
		 * @brief 接受输入
		 */
		void accept();

	private:
		Ncti_VariantValue* m_any{ nullptr };            ///< 变体指针
	};
};
#endif // NctiLineEditBoundData_H