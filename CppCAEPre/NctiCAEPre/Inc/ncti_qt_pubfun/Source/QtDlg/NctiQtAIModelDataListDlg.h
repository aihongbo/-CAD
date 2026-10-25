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

#ifndef NCTIQTAIMODELDATALIST_H
#define NCTIQTAIMODELDATALIST_H
#include "dcl_ncti_qt_pubfun.h"
#include <QWidget>
#include "ui_NctiAIModelDataList.h"
#include "ncti_base.h"
#include "NctiAiModelSystemObject.h"
#include "NctiBaseUtility.h"
#include "AiLabelTree.h"

#include <unordered_map>
#include <functional>
#include <set>
#include <map>

namespace NCTI
{
    class NctiObjectTree;
    class AiLabelTree;
    /**
     * @brief 判断两个浮点数是否相等（相对误差）
     * @param a 第一个浮点数
     * @param b 第二个浮点数
     * @param epsilon 误差范围
     * @return 相等返回true，否则返回false
     */
    inline bool IsEqualRelative(double a, double b, double epsilon = 1e-9)
    {
        double diff = std::abs(a - b);
        //double maxAbs = std::max(std::abs(a), std::abs(b));
        return diff <= epsilon/* * maxAbs*/;
    }

    /**
     * @brief 判断两个点是否相同
     * @param p1 第一个点
     * @param p2 第二个点
     * @return 相同返回true，否则返回false
     */
    inline bool IsSamePoint(const NctiPosition& p1, const NctiPosition& p2)
    {
        return NctiBaseUtility::same_point(p1, p2, NCTI_RESABS);
        return IsEqualRelative(p1.x(), p2.x())
            && IsEqualRelative(p1.y(), p2.y())
            && IsEqualRelative(p1.z(), p2.z());
    }

    /**
     * @brief 哈希函数结构体
     * @details 用于AiModelData类型的哈希计算
     */
    struct HashFunc
    {
        /**
         * @brief 计算哈希值
         * @param key AiModelData对象
         * @return 哈希值
         */
        size_t operator()(const AiModelData& key) const {
            size_t seed = 0;
            hash_combine(seed, key.ObjName);
            hash_combine(seed, key.type);
            hash_combine(seed, key.faceType);

            for (const NctiPosition& pt : key.pts)
            {
                hash_combine(seed, pt.x());
                hash_combine(seed, pt.y());
                hash_combine(seed, pt.z());
            }
            return seed;
        }
    };

    /**
     * @brief 相等键结构体
     * @details 用于AiModelData类型的相等比较
     */
    struct EqualKey
    {
        /**
         * @brief 比较两个AiModelData对象是否相等
         * @param lhs 左侧对象
         * @param rhs 右侧对象
         * @return 相等返回true，否则返回false
         */
        bool operator () (const AiModelData& lhs, const AiModelData& rhs) const
        {
            bool isSamePoints = lhs.pts.size() == rhs.pts.size();
            if (isSamePoints)
            {
                size_t len = lhs.pts.size();
                for (size_t i = 0; i < len; i++)
                {
                    isSamePoints = isSamePoints && IsSamePoint(lhs.pts[i], rhs.pts[i]);
                    if (!isSamePoints)
                    {
                        break;
                    }
                }
            }
            return lhs.type == rhs.type
                && lhs.ObjName == rhs.ObjName
                && lhs.faceType == rhs.faceType
                && isSamePoints;
        }
    };

    class NctiDocument;
    
    /**
     * @brief AI模型数据列表对话框类
     */
    class DECL_NCTI_QT_PUBFUN NctiQtAIModelDataListDlg : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         * @param i_pDocument 文档指针
         * @param i_parent 父窗口指针
         * @param setAiLabels AI标签集合
         * @param setAiFeatureLabels AI特征标签集合
         */
        explicit NctiQtAIModelDataListDlg(NctiDocument* i_pDocument, QWidget* i_parent, const std::vector<AiLabelTree>& setAiLabels, const std::vector<AiLabelTree>& setAiFeatureLabels, NctiObjectTree* objectTree);
        
        /**
         * @brief 析构函数
         */
        ~NctiQtAIModelDataListDlg();
        
        /**
         * @brief 获取实例
         * @return 实例指针
         */
        static NctiQtAIModelDataListDlg* Instance();
        
        /**
         * @brief 设置实例
         * @param pNctiQtAIModelDataListDlg 实例指针
         */
        static void SetInstance(NctiQtAIModelDataListDlg* pNctiQtAIModelDataListDlg);
        
        /**
         * @brief 刷新模型数据
         * @param i_pDocument 文档指针
         */
        void RefreshModelData(NctiDocument* i_pDocument);
        
        Q_SIGNALS:
        /**
         * @brief 移除标签项信号
         * @param showName 显示名称
         */
        void sigRemoveLabelItem(const QString& showName);
        
    private Q_SLOTS:
        /**
         * @brief 对象项点击槽函数
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void onObjectItemClicked(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 形状项点击槽函数
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void onShapeItemClicked(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 特征项点击槽函数
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void onFeatureItemClicked(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 形状项菜单显示槽函数
         * @param point 点击位置
         */
        void onShapeItemMenuShow(const QPoint& point);
        
        /**
         * @brief 刷新按钮点击槽函数
         */
        void onRefreshButtonClick();
        
        /**
         * @brief 形状项重命名槽函数
         */
        void onShapeItemRename();
        
        /**
         * @brief 形状项移除槽函数
         */
        void onShapeItemRemove();
        
        /**
         * @brief 导出模型槽函数
         */
        void onExportModels();
        
        /**
         * @brief 移除子标签槽函数
         */
        void onRemoveSubLabels();
        
        /**
         * @brief 全选标签槽函数
         */
        void onSelectAllLabels();

        /**
         * @brief 取消全选标签槽函数
         */
        void onDeselectAllLabels();

    private:
        /**
         * @brief 初始化对话框
         */
        void Init();
        
        /**
         * @brief 显示体列表
         */
        void ShowBodyList();
        
        /**
         * @brief 显示形状列表
         */
        void ShowShapeList();
        
        /**
         * @brief 添加树形控件项
         * @param key 键值
         * @param vModelData 模型数据列表
         * @param objectType 对象类型
         */
        void AddTreeItem(const QString& key, const std::vector<AiModelData>& vModelData, const int objectType);
        
        /**
         * @brief 更新父项状态
         * @param item 树形控件项指针
         */
        void UpdateParentItemState(QTreeWidgetItem* item);
        
        /**
         * @brief 高亮显示形状
         */
        void HighLightShapes();
        
        /**
         * @brief 高亮显示体
         */
        void SetHighLightBodys(QTreeWidgetItem*);

        void HighLightBodys();
        
        /**
         * @brief 高亮显示特征
         */
        void HighLightFeatures();
        
        /**
         * @brief 根据模型数据获取cellID
         * @param data 模型数据
         * @return cellID
         */
        Ncti_Long GetCellIdByModelData(const AiModelData& data);
        
        /**
         * @brief 创建顶点
         * @param segItemName 项名称
         * @param pos 位置
         * @return 创建成功返回true，否则返回false
         */
        bool CreateVertex(const QString& segItemName, const NctiPosition& pos);
        
        /**
         * @brief 显示顶点
         * @param segItemName 项名称
         * @param bShow 是否显示
         * @return 显示成功返回true，否则返回false
         */
        bool ShowVertex(const QString& segItemName, bool bShow);

        /**
         * @brief 初始化单元映射
         */
        void InitCellMap();
        
        /**
         * @brief 清除顶点
         */
        void ClearVertex();

        /**
         * @brief 重命名形状项
         * @param newLabel 新标签
         */
        void RenameShapeItem(std::string& newLabel);
        
        /**
         * @brief 选中形状项
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void CheckedShapeItem(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 选中特征项
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void CheckedFeatureItem(QTreeWidgetItem* item, int column);
        
        /**
         * @brief 获取文档模型容器
         * @return 文档自定义容器指针
         */
        NctiDisplayDocCustomContainer* GetDocModelContainer();
        
        /**
         * @brief 获得所有object对象，不包含group
         */
        void GetAllBodyNames();
        
        /**
         * @brief 统计打标签的所有object
         */
        void GetAllLabledObjectNames();
        
        /**
         * @brief 清除AI标签类型
         */
        void ClearAiLabelType();
        
        /**
         * @brief 刷新AI标签类型
         */
        void RefreshAiLabelType();
        
        /**
         * @brief 选中体项
         * @param item 树形控件项指针
         * @param column 列索引
         */
        void CheckedBodyItem(QTreeWidgetItem* item, int column);

        /**
         * @brief 初始化AI标签树
         */
        void InitAiLabelTree();
        
        /**
         * @brief 遍历项导出
         * @param item 树形控件项指针
		 * @param selectedPath 选择路径
		 * @param selectedPath 文件前缀
         * @param useType 使用类型 0:统计已经打标签的object 1:导出已经打标签的object
         */
        void TraverseItemToExport(QTreeWidgetItem* item, const QString& selectedPath, const QString& prefix, const int useType);
        
        /**
         * @brief 遍历特征项导出
         * @param item 树形控件项指针
         * @param vModels 模型列表
         */
        void TraverseFeatureItemToExport(QTreeWidgetItem*, std::vector<NCTI_MODEL_TAG>&, std::vector<AiModelData>&);
        
        /**
         * @brief 遍历特征项导出
         * @param item 树形控件项指针
         * @param <object实体名称, <对象树的节点名称, object实体对象指针>
         */
        void TraverseFeatureItemBodyToExport(QTreeWidgetItem*, std::map<QString, std::pair<QString, NCTI_MODEL_TAG>>&);

        /**
         * @brief 导出模型
         * @param directory 目录
         * @param i_vModels 模型列表
         * @param modelName 模型名称
         */
        void ExportModels(const QString& directory, std::vector<NCTI_MODEL_TAG>& i_vModels, const QString& modelName);
        
        /**
         * @brief 遍历项全选
         * @param item 树形控件项指
         * @param useType 使用类型 0:取消选中 1:选中 
         */
        void TraverseItemToSelect(QTreeWidgetItem* item, const int useType);

        /**
         * @brief 移除选中的体项
         */
        void RemoveCheckedBodyItem();
        
        /**
         * @brief 判断体是否已标记
         * @param i_modelData 模型数据
         * @return 已标记返回true，否则返回false
         */
        bool BodyIsLabeled(const AiModelData& i_modelData);
        
        /**
         * @brief 移除AI模型数据
         * @param i_label 标签
         * @param i_modelData 模型数据
         */
        void RemoveAiModelData(const QString& i_label, const AiModelData& i_modelData);
        
        /**
         * @brief 显示确认对话框
         * @param parent 父窗口指针
         * @param title 标题
         * @param text 文本
         * @return 确认返回true，否则返回false
         */
        bool ShowConfirmDialog(QWidget* parent, const QString& title, const QString& text);
        
        /**
         * @brief ID集合转字符串
         * @param ids ID集合
         * @return 字符串
         */
        std::string IdsToString(const std::set<Ncti_Integer>& ids);
        
        /**
         * @brief 写字符串文件
         * @param content 内容
         * @param directory 目录
         * @param fileName 文件名
         * @return 写入成功返回true，否则返回false
         */
        bool WriteStringFile(const QString& content, const QString& directory, const QString& fileName);

        QString GetObjectTreeItemName(QStringList&);
        
    private:
        /**
         * @brief 单元属性数据结构体
         * @details 存储单元的属性数据
         */
        struct CellAttribData
        {
            Ncti_Long cellId;                              ///< cellID
            std::vector<NctiPosition> attribPoints;        ///< 属性点向列表
            bool hasUsed;                                  ///< 是否已使用
        };

        NctiDocument* m_pDocument = nullptr;                                ///< 文档指针
        Ui::NctiAIModelDataList* m_ui;                                      ///< UI界面指针
        std::vector<QTreeWidgetItem*> m_vShapeTreeItem;                     ///< 形状树项列表，存储了模型
        std::vector<QString> m_vVertexName;                                 ///< 顶点名称列表
        std::vector<NctiRenderSegmentItem*> m_vSegmentItem;                 ///< 段项列表
        std::unordered_map<AiModelData, Ncti_Long, HashFunc, EqualKey> m_mapModelCellID;  ///< 模型cellID映射
        std::unordered_map<std::string, std::vector<CellAttribData>> m_cellAttribDataMap; ///< 单元属性数据映射
        std::map<std::string, std::vector<AiModelData>> m_AiModelDataMap;   ///< AI模型数据映射 <标签名, 模型>
        std::map<std::string, int> m_mapAiLabelType;                        ///< AI标签类型映射 <标签名, 类型>
        std::vector<AiLabelTree> m_setAiLabels;                                    ///< AI标签集合
        std::vector<AiLabelTree> m_setAiFeatureLabels;                             ///< AI特征标签集合

        std::string m_oldName;                                              ///< 旧名称
        std::string m_oldNameBody;                                          ///< 旧体名称
        static NctiQtAIModelDataListDlg* m_instance;                        ///< 实例指针
        std::set<std::string> m_setAllBodyNames;                            ///< 所有体名称集合
        std::set<std::string> m_setOutputBodyNames;                         ///< 输出体名称集合
        std::set<NctiDisplayObject*> m_highlighObjectSet;
        NctiObjectTree* m_objectTree{};
    };
}

#endif // NCTIQTAIMODELDATALIST_H