#pragma once

#include "ncti_base.h"
#include "NctiFunctionInterface.h"
#include "dcl_ncti_plugin.h"
#include "NctiModelFunctionResult.h"
#include "NctiGPropDef.h"
#include "NctiGBoundsDef.h"
#include "NctiGeoDataDef.h"
#include "chrono"
#include <map>

namespace NCTI {
class NctiDisplayDocCustomContainer;
class NctiBaseModel;
class NctiVector;
class NctiAxis;
class NctiGeometryResult;

/**
 * @brief 几何功能接口演示类
 * @details 该类继承自[NctiFunctionInterface]，作为几何功能接口的基类，
 * 提供了几何功能的接口定义，用于插件系统的功能扩展
 * 
 * @ingroup PluginDemo
 */
class DECL_NCTI_PLUGIN GeometryFunctionInterfaceDemo : public NctiFunctionInterface
{
    NCTI_PLUGIN_FUNCTIONS(GeometryFunctionInterfaceDemo)
public:
    /**
     * @brief 构造函数
     */
    GeometryFunctionInterfaceDemo();

    /**
     * @brief 析构函数
     */
    virtual ~GeometryFunctionInterfaceDemo();

    /**
     * @brief 创建长方体的接口函数
     * @details 该函数定义了创建长方体的接口规范，具体实现在各插件中完成
     * 
     * @param i_pCustomContainer 文档容器指针
     * @param i_pos 长方体的坐标点位置
     * @param i_len 长度
     * @param i_width 宽度
     * @param i_height 高度
     * @param o_ModelBody 输出的模型体对象
     * @return 几何操作结果
     */
    virtual NctiGeometryResult create_box_demo(NctiDisplayDocCustomContainer* i_pCustomContainer,
                                               const NctiPosition& i_pos,
                                               Ncti_Double i_len,
                                               Ncti_Double i_width,
                                               Ncti_Double i_height,
                                               NCTI_MODEL_TAG& o_ModelBody);
};
} // namespace NCTI