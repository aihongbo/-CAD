#pragma once

#include "ncti_base.h"
#include "dcl_ncti_plugin.h"
#include "NctiModelFunctionResult.h"
#include "GeometryFunctionInterfaceDemo.h"

namespace NCTI {
class NctiDisplayDocCustomContainer;
class NctiBaseModel;
class NctiVector;

/**
 * @brief 几何功能演示类
 * @details 该类提供了几何功能的静态方法，用于调用插件系统中实现的具体几何功能
 * 
 * @ingroup PluginDemo
 */
class DECL_NCTI_PLUGIN GeometryFunctionDemo
{
public:
    /**
	 * @brief 构造函数
	 */
    GeometryFunctionDemo();

    /**
	 * @brief 析构函数
	 */
    virtual ~GeometryFunctionDemo();

public:
    /**
	 * @brief 创建长方体的静态函数
	 * @details 该静态函数通过插件接口调用具体的几何功能实现来创建长方体
	 * 
	 * @param i_pCustomContainer 文档容器指针
	 * @param i_pos 长方体的坐标点位置
	 * @param i_len 长度
	 * @param i_width 宽度
	 * @param i_height 高度
	 * @param o_ModelBody 输出的模型体对象
	 * @return 几何操作结果
	 */
    static NctiGeometryResult create_box_demo(NctiDisplayDocCustomContainer* i_pCustomContainer,
                                              const NctiPosition& i_pos,
                                              Ncti_Double i_len,
                                              Ncti_Double i_width,
                                              Ncti_Double i_height,
                                              NCTI_MODEL_TAG& o_ModelBody);
};
} // namespace NCTI