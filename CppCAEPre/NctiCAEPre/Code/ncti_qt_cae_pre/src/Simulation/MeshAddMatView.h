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

#ifndef MESHADDMATVIEW_H
#define MESHADDMATVIEW_H

#include "ncti_base.h"
#include "NctiBaseDialog.h"

namespace Ui {
class MeshAddMatView;
}

namespace NCTI
{
    class SelectModeRoller;
    class NctiQtScriptExecutor;
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 网格添加材料视图类
     * @details 用于在网格上添加材料属性的对话框窗口
     */
    class MeshAddMatView : public NctiBaseDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param executor 脚本执行器指针
         * @param parent 父窗口指针
         */
        explicit MeshAddMatView(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~MeshAddMatView();

    protected:
        /**
         * @brief 接受前处理函数
         * @return 处理成功返回true，否则返回false
         */
        bool beforeAccpet();

    private:
        /**
         * @brief 设置界面
         */
        void setup();
        
        /**
         * @brief 设置对象选择
         * @param objectList 对象列表
         */
        void setObjectSelection(const std::vector<NctiDisplayObject*>& objectList);

        /**
         * @brief 获取结果名称
         * @param[out] name 名称
         * @return 获取成功返回true，否则返回false
         */
        bool getResultName(QString& name);
        
        /**
         * @brief 获取源名称
         * @param[out] name 名称
         * @return 获取成功返回true，否则返回false
         */
        bool getSourceName(QString& name);
        
        /**
         * @brief 获取弹性模量
         * @param[out] e 弹性模量
         * @return 获取成功返回true，否则返回false
         */
        bool getE(QString &e);
        
        /**
         * @brief 获取剪切模量
         * @param[out] g 剪切模量
         * @return 获取成功返回true，否则返回false
         */
        bool getG(QString& g);
        
        /**
         * @brief 获取泊松比
         * @param[out] nu 泊松比
         * @return 获取成功返回true，否则返回false
         */
        bool getNu(QString& nu);
        
        /**
         * @brief 获取密度
         * @param[out] rho 密度
         * @return 获取成功返回true，否则返回false
         */
        bool getRho(QString& rho);
        
        /**
         * @brief 获取热膨胀系数
         * @param[out] a 热膨胀系数
         * @return 获取成功返回true，否则返回false
         */
        bool getA(QString& a);
        
        /**
         * @brief 获取注释
         * @param[out] comment 注释
         * @return 获取成功返回true，否则返回false
         */
        bool getComment(QString& comment);
        
        /**
         * @brief 转换为脚本字符串
         * @param resultName 结果名称
         * @param sourceName 源名称
         * @param e 弹性模量
         * @param g 剪切模量
         * @param nu 泊松比
         * @param rho 密度
         * @param a 热膨胀系数
         * @param comment 注释
         * @return 脚本字符串
         */
        QString toScriptString(const QString& resultName, const QString& sourceName, const QString &e,
            const QString& g, const QString& nu, const QString& rho, const QString& a, const QString& comment);

        /**
         * @brief 弹出消息框
         * @param message 消息内容
         * @param title 标题
         */
        void popupMessage(const QString& message, const QString& title = QStringLiteral("提示"));

    private:
        Ui::MeshAddMatView* ui;                        ///< UI界面指针

        NctiDocument* m_document;                      ///< 文档指针
        NctiQtScriptExecutor* m_executor;              ///< 脚本执行器指针
        std::vector<NctiDisplayObject*> m_selectObjects; ///< 选择的对象列表
        SelectModeRoller* m_roller;                    ///< 选择模式滚动器
    };
}

#endif // MESHADDMATVIEW_H