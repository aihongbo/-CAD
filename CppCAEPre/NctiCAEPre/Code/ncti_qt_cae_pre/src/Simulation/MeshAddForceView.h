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

#ifndef MESHADDFORCEVIEW_H
#define MESHADDFORCEVIEW_H

#include "NctiVector.h"
#include "ncti_base.h"
#include "NctiBaseDialog.h"

namespace Ui {
class MeshAddForceView;
}

namespace NCTI
{
    class SelectModeRoller;
    class NctiQtScriptExecutor;
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 网格添加力视图类
     * @details 用于在网格上添加力边界条件的对话框窗口
     */
    class MeshAddForceView : public NctiBaseDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param executor 脚本执行器指针
         * @param parent 父窗口指针
         */
        explicit MeshAddForceView(NctiDocument* i_pDocument, NctiQtScriptExecutor* executor, QWidget* parent = nullptr);
        
        /**
         * @brief 析构函数
         */
        ~MeshAddForceView();

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
         * @param cellIDList cellID列表
         */
        void setObjectSelection(const std::vector<NctiDisplayObject*>& objectList, const std::vector<void*> &cellIDList);

        /**
         * @brief 获取源名称
         * @param[out] name 名称
         * @param[out] cellIDList cellID列表
         * @return 获取成功返回true，否则返回false
         */
        bool getSourceName(QString& name, QList<Ncti_LongLong>& cellIDList);
        
        /**
         * @brief 获取结果名称
         * @param[out] name 名称
         * @return 获取成功返回true，否则返回false
         */
        bool getResultName(QString& name);
        
        /**
         * @brief 获取方向向量
         * @param[out] vector 方向向量
         * @return 获取成功返回true，否则返回false
         */
        bool getDirect(NctiVector& vector);
        
        /**
         * @brief 获取大小
         * @param[out] magnitude 大小
         * @return 获取成功返回true，否则返回false
         */
        bool getMagnitude(Ncti_Double& magnitude);
        
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
         * @param cellIDList cellID列表
         * @param direct 方向向量
         * @param magnitude 大小
         * @param comment 注释
         * @return 脚本字符串
         */
        QString toScriptString(const QString &resultName, const QString& sourceName, const QList<Ncti_LongLong> &cellIDList,
            const NctiVector &direct, Ncti_Double magnitude, const QString &comment);

        /**
         * @brief 弹出消息框
         * @param message 消息内容
         * @param title 标题
         */
        void popupMessage(const QString& message, const QString& title = QStringLiteral("提示"));

    private:
        Ui::MeshAddForceView* ui;                      ///< UI界面指针
        NctiDocument* m_document;                      ///< 文档指针
        NctiQtScriptExecutor* m_executor;              ///< 脚本执行器指针
        std::vector<NctiDisplayObject*> m_selectObjects; ///< 选择的对象列表
        std::vector<void*> m_selectCells;              ///< 选择的单元列表
        SelectModeRoller* m_roller;                    ///< 选择模式滚动器
        std::vector<Ncti_LongLong> m_NodeIdx;          ///< 节点索引列表
    };
};

#endif // MESHADDFORCEVIEW_H