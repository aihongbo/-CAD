#ifndef NCTI_OCC_INTERFACE_DEMO_H
#define NCTI_OCC_INTERFACE_DEMO_H

#pragma once

#include "ncti_base.h"
#include "GeometryFunctionInterfaceDemo.h"
#include "NctiGeoDataDef.h"
#include "NctiAxis.h"

namespace NCTI {
/**
 * @brief OCC几何功能接口演示类
 * @details 该类提供了使用OpenCASCADE库创建和操作几何体的功能演示
 * @ingroup OCCPlugin
 */
class OCCInterfaceDemo : public GeometryFunctionInterfaceDemo
{
    NCTI_PLUGIN_FUNCTIONS(OCCInterfaceDemo)
public:
    /**
     * @brief 构造函数
     */
    OCCInterfaceDemo();

    /**
     * @brief 析构函数
     */
    virtual ~OCCInterfaceDemo();

public:
    /**
     * @brief 创建长方体的演示函数
     * @details 使用OpenCASCADE库创建一个长方体，并将其添加到文档容器中
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
                                               NCTI_MODEL_TAG& o_ModelBody) override;
};
} // namespace NCTI

#endif //!NCTI_OCC_INTERFACE_DEMO_H