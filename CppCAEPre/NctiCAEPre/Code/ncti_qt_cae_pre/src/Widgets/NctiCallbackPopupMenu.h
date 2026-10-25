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

#ifndef NctiCallbackPopupMenu_H
#define NctiCallbackPopupMenu_H

#include "NctiUserPopupMenu.h"
#include <utility>

#include <QString>
#include <QObject>

class QWidget;
class QMenu;

namespace NCTI
{
    class NctiDisplayObject;
    
    /**
     * @brief 回调菜单数据结构体
     * @details 存储菜单项的相关信息
     */
    struct CallbackMenuData
    {
        int id = -1;                              ///< 菜单项ID
        int parent_id = -1;                       ///< 父菜单项ID
        QString text;                             ///< 菜单项文本
        std::vector<CallbackMenuData> menuData;   ///< 子菜单数据
    };

    class NctiDocument;
    
    /**
     * @brief 回调弹出菜单类
     * @details 处理用户自定义弹出菜单的类
     */
	class NctiCallbackPopupMenu : public QObject, public NctiUserPopupMenu
	{
        Q_OBJECT
	public:
		/**
		 * @brief 构造函数
		 * @param i_pQWidget Qt控件指针
		 * @param pDoc 文档指针
		 */
		NctiCallbackPopupMenu(QWidget* i_pQWidget, NctiDocument* pDoc);
		
		/**
		 * @brief 析构函数
		 */
		virtual ~NctiCallbackPopupMenu();
		
		/**
		 * @brief 执行菜单
		 */
		virtual void Execute() override;
		
		/**
		 * @brief 运行菜单
		 * @param psMenuName 菜单名称
		 */
		virtual void RunMenu(const char* psMenuName) override;
		
		/**
		 * @brief 获取菜单信息
		 * @return 菜单信息指针
		 */
		NctiMenuInfo** GetMenuInfo();
		
		/**
		 * @brief 获取菜单项数量
		 * @return 菜单项数量
		 */
		int GetNumItems();
		
		/**
		 * @brief 设置显示对象
		 * @param i_pObj 显示对象指针
		 */
        void SetDisplayObj(NctiDisplayObject* i_pObj) { m_DisplayObj = i_pObj; }
        
    protected Q_SLOTS:
        /**
         * @brief 菜单项点击槽函数
         */
        void onMenuItemClicked();
        
	private:
        QWidget* m_QWidget{ nullptr };              ///< Qt控件指针
        NctiDocument* m_pDocument{ nullptr };       ///< 文档指针
        bool insertMenuData(std::vector<CallbackMenuData>& vMenuData, const CallbackMenuData& menuData);
        void createPopupMenu(QMenu* menu, const std::vector<CallbackMenuData>& vMenuData);
        
    private:
        NctiDisplayObject* m_DisplayObj;            ///< 显示对象指针
        QString getMenuItemIconUrl(Ncti_Integer i_id);
    };
}
#endif