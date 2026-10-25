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

#include <QObject>

namespace NCTI {
class NctiDocument;

/**
* @brief 选择模式滚动器类
* @details 管理文档元素的选择模式，在对象显示和销毁时自动切换选择模式
*/
class SelectModeRoller : public QObject
{
public:
    /**
	* @brief 构造函数
	* @param i_pDocument 文档指针
	* @param mode 选择模式
	* @param parent 父对象指针
	*/
    SelectModeRoller(NctiDocument* i_pDocument, int mode, QObject* parent);

    /**
	* @brief 析构函数
	*/
    ~SelectModeRoller();

    /**
	* @brief 选择模式枚举
	*/
    enum SelectMode {
        Body   = 1 << 0,                      ///< 体选择模式
        Face   = 1 << 1,                      ///< 面选择模式
        Line   = 1 << 2,                      ///< 线选择模式
        Marker = 1 << 3,                      ///< 点选择模式
        All    = Body | Face | Line | Marker, ///< 全部选择模式
    };

protected:
    /**
	* @brief 事件过滤器
	* @param w 对象指针
	* @param e 事件指针
	* @return 是否处理事件
	*/
    bool eventFilter(QObject* w, QEvent* e) override;

public:
    /**
	* @brief 初始化选择模式
	*/
    void initMode();

    /**
	* @brief 恢复选择模式
	*/
    void restoreMode();

protected:
    NctiDocument* m_doc;     ///< 文档指针
    bool m_selBody{false};   ///< 体选择状态
    bool m_selFace{false};   ///< 面选择状态
    bool m_selLine{false};   ///< 线选择状态
    bool m_selMarker{false}; ///< 点选择状态

private:
    bool m_inited{false};   ///< 是否已初始化
    bool m_restored{false}; ///< 是否已恢复
    int m_mode{-1};         ///< 选择模式
};
}; // namespace NCTI