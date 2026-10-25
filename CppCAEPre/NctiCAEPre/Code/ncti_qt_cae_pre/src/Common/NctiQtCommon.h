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

#ifndef NCTIQTCOMMOM_H
#define NCTIQTCOMMOM_H

/**
 * @brief 声明定义单例函数
 * @param _type_ 单例的类型
 */
#define CLASS_INSTANCE(_type_)                                                                                         \
public:                                                                                                                \
    static _type_* getInstance()                                                                                       \
    {                                                                                                                  \
        static _type_ _instance;                                                                                       \
        return &_instance;                                                                                             \
    }

/**
 * @brief 声明定义变量
 * @param _type_ 变量类型
 * @param _name_ 变量命名
 * @param _Name_ 函数命名
 */
#define CLASS_MEMBER_GET_SET(_type_, _name_, _Name_)                                                                   \
private:                                                                                                               \
    _type_ m_##_name_;                                                                                                 \
                                                                                                                       \
public:                                                                                                                \
    const _type_& get##_Name_() const                                                                                  \
    {                                                                                                                  \
        return m_##_name_;                                                                                             \
    }                                                                                                                  \
    void set##_Name_(const _type_& value)                                                                              \
    {                                                                                                                  \
        m_##_name_ = value;                                                                                            \
    }

/**
 * @brief 声明定义变量，指针的特化情况
 * @param _type_ 变量类型
 * @param _name_ 变量命名
 * @param _Name_ 函数命名
 */
#define CLASS_MEMBER_P_GET_SET(_type_, _name_, _Name_)                                                                 \
private:                                                                                                               \
    _type_ m_##_name_;                                                                                                 \
                                                                                                                       \
public:                                                                                                                \
    _type_ get##_Name_() const                                                                                         \
    {                                                                                                                  \
        return m_##_name_;                                                                                             \
    }                                                                                                                  \
    void set##_Name_(_type_ value)                                                                                     \
    {                                                                                                                  \
        m_##_name_ = value;                                                                                            \
    }

/**
 * @brief 声明定义变量，修改值时发出对应信号的特化情况
 * @param _type_ 变量类型
 * @param _name_ 变量命名
 * @param _Name_ 函数命名
 */
#define CLASS_MEMBER_GET_SET_SIGNAL(_type_, _name_, _Name_)                                                            \
private:                                                                                                               \
    _type_ m_##_name_;                                                                                                 \
                                                                                                                       \
public:                                                                                                                \
    Q_SIGNAL void sig##_Name_##Changed();                                                                              \
    const _type_& get##_Name_() const                                                                                  \
    {                                                                                                                  \
        return m_##_name_;                                                                                             \
    }                                                                                                                  \
    void set##_Name_(const _type_& value)                                                                              \
    {                                                                                                                  \
        if (value == m_##_name_)                                                                                       \
            return;                                                                                                    \
        m_##_name_ = value;                                                                                            \
        Q_EMIT sig##_Name_##Changed();                                                                                   \
    }

/**
 * @brief 判断序号在指定列表是否有效
 * @param _index_ 序号
 * @param _list_ 容器列表
 * @return 有效返回true
 */
#define INDEX_VALID_IN_LIST(_index_, _list_) (_index_ >= 0 && _index_ < _list_.size())

/**
 * @brief 判断序号在指定列表是否无效
 * @param _index_ 序号
 * @param _list_ 容器列表
 * @return 无效返回true
 */
#define INDEX_INVALID_IN_LIST(_index_, _list_) (!INDEX_VALID_IN_LIST(_index_, _list_))

/**
 * @brief 判断序号在指定列表是否无效
 * @param _index_ 序号
 * @param _list_ 容器列表
 * @return 无效返回true
 */
#define INDEX_FIXED(_index_, _list_)                                                                                   \
    if (-1 == _index_)                                                                                                 \
        _index_ = _list_.size() - 1;

/**
 * @brief 类的内部类声明
 */
#ifndef NCTI_QT_PUBFUNC_DECLARE_PRIVATE
#define NCTI_QT_PUBFUNC_DECLARE_PRIVATE(classname)                                                                     \
    class PrivateData;                                                                                                 \
    friend class classname::PrivateData;                                                                               \
    std::unique_ptr<PrivateData> d_ptr;
#endif

#ifndef NCTI_QT_PUBFUNC_DECLARE_PUBLIC
#define NCTI_QT_PUBFUNC_DECLARE_PUBLIC(classname)                                                                      \
    friend class classname;                                                                                            \
    classname* q_ptr{nullptr};                                                                                         \
    PrivateData(const PrivateData&)            = delete;                                                               \
    PrivateData& operator=(const PrivateData&) = delete;
#endif

#endif // !NCTIQTCOMMOM_H