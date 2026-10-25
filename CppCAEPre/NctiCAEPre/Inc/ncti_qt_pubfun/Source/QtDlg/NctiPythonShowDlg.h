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
#include <QDialog>
#include "NctiVector.h"
#include "NctiPosition.h"
#include "NCTIVariant.h"
#include "CallbackInterfaces.h"

class QTextEdit;
class QCheckBox;
class QLineEdit;
class QComboBox;

namespace NCTI
{
	//typedef std::map<std::string, std::variant<long, double, std::string, std::vector<std::string>, std::vector<long>>> NCTI_Map;  ///< NCTI映射类型
	//typedef std::variant<long, double, std::string, NctiPosition, NctiVector, std::vector<std::string>, NCTI_Map> NCTI_Variant;      ///< NCTI变体类型
	typedef std::vector<NCTI_Variant> Ncti_VariantVec;                                                                              ///< NCTI变体列表类型
	typedef std::vector<Ncti_VariantValue> Ncti_VariantVleVec;                                                                              ///< NCTI变体列表类型
	
	class NctiLineEditBoundData;
	class NctiComboBoxData;
	class NctiCheckBoxData;
	class NctiPushButtonData;
	class CheckedListBox;
	
    /**
     * @brief Python显示对话框类
     * @details 用于显示Python脚本输入参数的对话框
     */
    class NctiPythonShowDlg : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param args 参数对象指针
         * @param oArgs 输出参数向量指针
         * @param bReturn 是否返回
         * @param parent 父窗口指针
         */
        NctiPythonShowDlg(PyObject* args, Ncti_VariantVleVec* oArgs, bool bReturn, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~NctiPythonShowDlg();
        
        /**
         * @brief 初始化对话框
         */
        void init();
        
    private Q_SLOTS:
        /**
         * @brief 点击确定按钮槽函数
         * @param boo 点击状态
         */
        void ClickOk(bool boo);
        
        /**
         * @brief 点击取消按钮槽函数
         * @param boo 点击状态
         */
        void ClickCancel(bool boo);
	
    private:
        PyObject* m_Args;                    ///< 参数对象指针
        Ncti_VariantVleVec* m_ReturnArgs;       ///< 返回参数向量指针
        bool m_bReturn;                      ///< 是否返回
        QPushButton* m_BtnOK;                ///< 确定按钮指针
        QPushButton* m_BtnCancel;            ///< 取消按钮指针
        std::vector<NctiLineEditBoundData*> m_LineEditVec;     ///< 行编辑框数据列表
        std::vector<NctiComboBoxData*> m_ComboBoxVec;          ///< 组合框数据列表
        std::vector<NctiCheckBoxData*> m_CheckBoxVec;          ///< 复选框数据列表
        std::vector<NctiPushButtonData*> m_PushButtonVec;      ///< 按钮数据列表
        std::vector<CheckedListBox*> m_CheckedListBoVec;      ///< 按钮数据列表
    };
}