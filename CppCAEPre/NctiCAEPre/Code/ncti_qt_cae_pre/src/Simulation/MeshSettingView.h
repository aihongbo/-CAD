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

#ifndef MESHSETTINGVIEW_H
#define MESHSETTINGVIEW_H

#include "ncti_base.h"
#include "NctiBaseDialog.h"
#include "NctiMeshDataDef.h"

namespace Ui {
class MeshSettingView;
}

namespace NCTI
{
    class NctiQtPythonScript;
    class NctiDisplayObject;
    class NctiDocument;
    
    /**
     * @brief 网格设置视图类
     * @details 用于设置和配置网格生成参数的对话框窗口
     */
    class MeshSettingView : public NctiBaseDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief 构造函数
         * @param option 网格选项参数
         * @param i_pDocument 文档指针
         * @param parent 父窗口指针
         * @param sel 是否选择模式
         * @param meshType 网格类型
         */
        explicit MeshSettingView(Ncti_Mesh_Option option, NctiDocument* i_pDocument, QWidget* parent, bool sel, int meshType);
        
        /**
         * @brief 析构函数
         */
        ~MeshSettingView();
        
        /**
         * @brief 获取对象列表
         */
        std::vector<NctiDisplayObject*> getObjects() const;
        
        /**
         * @brief 获取网格选项
         * @return 网格选项引用
         */
        const Ncti_Mesh_Option& getMeshOption() const;

    Q_SIGNALS:
         
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
         * @brief 获取最大值
         * @param[out] max 最大值
         * @return 获取成功返回true，否则返回false
         */
        bool getMax(Ncti_Double& max);
        
        /**
         * @brief 更新选择项
         */
        void updateSelected();

        /**
         * @brief 弹出消息框
         * @param message 消息内容
         * @param title 标题
         */
        void popupMessage(const QString& message, const QString& title = QStringLiteral("提示"));

    private:
        Ui::MeshSettingView* ui;      ///< UI界面指针
        NctiDocument* m_document;      ///< 文档指针
        std::vector<NctiDisplayObject*> m_objs;  ///< 对象列表
        bool m_sel;                   ///< 是否选择模式
        Ncti_Mesh_Option m_option;    ///< 网格选项
        int m_meshType;               ///< 网格类型
    };
}

#endif // MESHSETTINGVIEW_H
