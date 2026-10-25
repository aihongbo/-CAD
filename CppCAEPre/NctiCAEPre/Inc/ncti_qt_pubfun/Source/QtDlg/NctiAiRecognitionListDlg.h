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

#ifndef NctiAiRecognitionListDlg_H
#define NctiAiRecognitionListDlg_H

#include "dcl_ncti_qt_pubfun.h"
#include "ui_NctiAiRecognitionList.h"
#include "ncti_base.h"
#include <QWidget>

namespace NCTI {
    /**
     * @brief AI识别对象结构体
     * @details 存储AI识别的对象信息
     */
    struct AiRecogObject
    {
        std::string m_ObjectName;              ///< 对象名称
        std::vector<Ncti_Long> m_CellId;       ///< cellID数组
    };
    
    /**
     * @brief AI识别数据结构体
     * @details 存储AI识别的标签和对象信息
     */
    struct AiRecognitionData
    {
        std::string m_LabelName;                     ///< 标签名称
        std::vector<AiRecogObject> m_Objects;        ///< 对象列表
    };

    struct AiModelData; 
    struct AiFaceAttr;
    class NctiDocument;
    class NctiPosition;
    class NctiDisplayAiAttriTopoMesh;
    
    /**
     * @brief AI识别列表对话框类
     * @details 用于显示AI识别结果列表的对话框
     */
    class DECL_NCTI_QT_PUBFUN NctiAiRecognitionListDlg : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         */
        explicit NctiAiRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_parent, const std::string& i_recogType);
        
        /**
         * @brief 析构函数
         */
        ~NctiAiRecognitionListDlg();

    private Q_SLOTS:
        /**
         * @brief 识别项点击槽函数
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void onRecogItemClicked(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 刷新按钮点击槽函数
         */
        void RefreshButtonClick();
        
        /**
         * @brief 搜索按钮点击槽函数
         */
        void SearchButtonClick();

    private:
        /**
         * @brief 单元属性数据结构体
         * @details 存储单元的属性数据
         */
        struct CellAttribData
        {
            Ncti_Long cellId;                              ///< 单元ID
            std::vector<NctiPosition> attribPoints;        ///< 属性点列表
            bool hasUsed;                                  ///< 是否已使用
        };

        /**
         * @brief 初始化
         */
        void Init();
        
        /**
         * @brief 初始化树形控件
         */
        void InitTree();
        
        /**
         * @brief 初始化数据
         */
        void InitData();
        
        /**
         * @brief 更新对象单元ID
         * @param aiModelDatas AI模型数据列表
         * @param o_objectCellMap 对象单元映射
         */
        void UpdateObjectCellId(const std::vector<AiModelData>& aiModelDatas, std::map<std::string, std::vector<CellAttribData>>& o_objectCellMap);
        
        /**
         * @brief 更新父项状态
         * @param item 树形控件项指针
         */
        void UpdateParentItemState(QTreeWidgetItem* item);
        
        /**
         * @brief 高亮显示单元
         */
        void HighLightCells();

        /**
         * @brief 按拓扑关系分组单元ID
         * @param cellIds cellID数组
         * @param topIds 拓扑ID对数组
         * @param o_cellGroups 输出的单元组数组
         */
        void GroupCellIdByTopo(const std::vector<Ncti_Long>& cellIds, 
            const std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& topIds, 
            std::vector<std::vector<Ncti_Long>>& o_cellGroups);
            
        /**
         * @brief 按面积分组单元ID
         * @param faceAttrs 面属性列表
         * @param cellGroups 单元组列表
         * @param o_cellGroups 输出的单元组列表
         */
        void GroupCellIdByArea(const std::vector<AiFaceAttr>& faceAttrs, 
            const std::vector<std::vector<Ncti_Long>>& cellGroups,
            std::vector<std::map<std::string, std::vector<Ncti_Long>>>& o_cellGroups);
            
        /**
         * @brief 按半径分组单元ID
         * @param c_ObjName 对象名称
         * @param cellGroups 单元组列表
         * @param o_cellGroups 输出的单元组列表
         */
        void GroupCellIdByRadius(const char* c_ObjName, const std::vector<std::vector<Ncti_Long>>& cellGroups,
            std::vector<std::map<std::string, std::vector<Ncti_Long>>>& o_cellGroups);
            
        /**
         * @brief 更新选中状态
         * @param item 树形控件项指针
         * @param state 选中状态
         */
        void UpdateCheckState(QTreeWidgetItem* item, Qt::CheckState state);
        
        /**
         * @brief 获取拓扑关系
         * @param c_ObjName 对象名称
         * @param faceTopoIDs 面拓扑ID对列表
         */
        void GetTopoRelation(const char* c_ObjName, std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& faceTopoIDs);

    private:
        Ui::NctiQtAiRecognitionListDlg* m_ui;                ///< UI界面指针
        NctiDocument* m_pDocument = nullptr;                 ///< 文档指针
        std::vector<AiRecognitionData> m_AiRecogDatas;       ///< AI识别数据列表
        std::vector<QTreeWidgetItem*> m_TreeItem;            ///< 树形控件项列表
        std::vector<NctiDisplayAiAttriTopoMesh*> m_topoMeshes;  ///< 拓扑网格对象列表
        std::string m_recogType;
    };
}

#endif // !NctiAiRecognitionListDlg_H