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

#ifndef OBJECT_TREE_MANAGER_H
#define OBJECT_TREE_MANAGER_H

#pragma once

#include "MainWindowModules.h"
#include "NctiObjectTree.h"
#include "ncti_base.h"

namespace NCTI {

struct NctiTreeModelData;
class DockTitleBar;

/**
* @brief 对象树管理类
*/
class ObjectTreeManager : public MainWindowModule
{
    Q_OBJECT

public:
    /**
	* @brief 构造函数
	* @param mainWindow 主窗口指针
	*/
    explicit ObjectTreeManager(MainWindow* mainWindow);

    /**
	* @brief 模块初始化，在这里处理主窗口的信号
	*/
    void initialize() override;

    /**
     * @brief 更新树
     */
    void UpdateTree();

    /**
     * @brief 初始化对象树
     */
    void initObjectTree();

    /**
     * @brief 选择树项目
     * @param objNames 对象名称列表
     */
    void selectTreeItems(const QStringList& objNames);

    /**
     * @brief 设置UI等待状态
     * @param i_boo 等待状态
     */
    void SetUIWait(Ncti_Boolean i_boo);

    /**
     * @brief 设置树已修改
     */
    void SetTreeModified();

    /**
     * @brief 设置树修改状态
     * @param i_boo 修改状态
     */
    void SetTreeIsModify(Ncti_Boolean i_boo);

    /**
     * @brief 对象树处理
     */
    void onObjectTree();

    /**
    * @brief 获取对象树标题
    * @param index 索引
    * @return 标题字符串
    */
    QString getObjectTreeTitle(int index = -1); 


    /**
    * @brief 显示对象树
    */
    void showObjectTree();

private:

    /**
     * @brief 侧边栏可见性处理
     * @param index 索引
     * @param visible 是否可见
     */
    void onSidePanelVisible(int index, bool visible);

    /**
     * @brief 树项目选择处理
     * @param vObj 选择的对象向量
     */
    void onTreeItemSelected(const std::vector<void*>& vObj);

    /**
     * @brief 树项目点击处理
     * @param objName 对象名称
     * @param pObj 对象指针
     */
    void onTreeItemClicked(const QString& objName, void* pObj);

    /**
     * @brief 上下文菜单请求处理
     * @param objName 对象名称
     * @param pObj 对象指针
     */
    void onContextMenuRequested(const QString& objName, void* pObj);

    /**
    * @brief 获取装配数据
    * @return 装配树模型数据向量
    */
    std::vector<NctiTreeModelData> getAssembleData();

    /**
     * @brief 获取当前对象数据
     * @return 当前对象树模型数据向量
     */
    std::vector<NctiTreeModelData> getCurrentObjectData();

    /**
     * @brief 获取场景数据
     * @return 场景树模型数据向量
     */
    std::vector<NctiTreeModelData> getSceneData();

private:
    bool m_sidePanelVisible{ true };                ///< 侧边栏是否可见
    int m_objectTreeDockWidth{ 200 };               ///< 对象树停靠宽度
    DockTitleBar* m_objectTreeTitleBar{ nullptr };  ///< 对象树标题栏
    QDockWidget* m_objectTreeDockWidget{ nullptr }; ///< 对象树停靠窗口
    NctiObjectTree* m_objectTree{ nullptr };        ///< 对象树窗口
    Ncti_Boolean m_TreeIsModify{ true };            ///< 树是否被修改
    Ncti_Boolean m_bUIWait{ false };                ///< UI是否等待
};

} // namespace NCTI

#endif // OBJECT_TREE_MANAGER_H