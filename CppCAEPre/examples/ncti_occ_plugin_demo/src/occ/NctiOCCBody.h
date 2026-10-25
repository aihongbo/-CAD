#ifndef NctiOCCBody_H
#define NctiOCCBody_H

#include "ncti_dcl_gm_model_function.h"
#include "ncti_base.h"
#include <vector>
#include <map>

class TopoDS_Shape;

namespace NCTI {
class NctiTopoShape;
class NctiTopoEdge;
class NctiTopoVertex;
class NctiTopoFace;
class NctiRenderSegmentItem;

/**
 * @brief OCC实体类
 * @details 封装了OpenCASCADE的TopoDS_Shape对象，提供了对OCC几何体的操作接口
 * 
 * @ingroup OCCModel
 */
class DECL_NCTI_GM_MODEL_PUBFUN NctiOCCBody
{
public:
    /**
	 * @brief 构造函数
	 * @param i_pTopoDS_Shape TopoDS_Shape指针
	 */
    NctiOCCBody(TopoDS_Shape* i_pTopoDS_Shape);

    /**
	 * @brief 析构函数
	 */
    virtual ~NctiOCCBody();

public:
    /**
	 * @brief 获取形状对象
	 * @return TopoDS_Shape指针
	 */
    TopoDS_Shape* GetShape();

    /**
	 * @brief 判断是否为体积体
	 * @return true表示是体积体，false表示不是
	 */
    Ncti_Boolean IsVolume();

    /**
	 * @brief 根据dimTag获取可视化索引
	 * @param o_ModelBody 模型体对象
	 * @param dimTag 维度标签
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_persistent_from_dimtag(int& o_ModelBody, std::pair<int, int> dimTag) const;

    /**
	 * @brief 获取可视化索引
	 * @param i_ModelBody 模型体对象
	 * @param o_id 输出的ID
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_persistent_tag(NCTI_MODEL_TAG i_ModelBody, Ncti_Long& o_id);

    /**
	 * @brief 根据标签获取几何体
	 * @param o_ModelBody 输出的模型体对象
	 * @param i_id 输入的ID
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_void_from_tag(NCTI_MODEL_TAG& o_ModelBody, Ncti_Long i_id);

    /**
	 * @brief 根据标签获取单元
	 * @param i_ModelBody 模型体对象
	 * @param o_cell 输出的单元
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_cell_from_tag(NCTI_MODEL_TAG i_ModelBody, TopoDS_Shape& o_cell);

    /**
	 * @brief 根据单元获取标签
	 * @param o_ModelBody 输出的模型体对象
	 * @param i_cell 输入的单元
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_tag_from_cell(NCTI_MODEL_TAG& o_ModelBody, const TopoDS_Shape& i_cell);

    /**
	 * @brief 根据模型体获取几何单元
	 * @param i_ModelBody 模型体对象
	 * @param o_pGEShape 输出的几何形状对象
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_gecell_from_cell(NCTI_MODEL_TAG i_ModelBody, NCTI_MODEL_TAG& o_pGEShape);

    /**
	 * @brief 根据OCC形状获取NCTI单元
	 * @param i_shape 输入的OCC形状
	 * @param o_pOCCCell 输出的OCC单元
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_ncti_cell_by_occ_shape(const TopoDS_Shape& i_shape, NCTI_MODEL_TAG& o_pOCCCell);

    /**
	 * @brief 根据NCTI单元获取OCC形状
	 * @param i_pOCCCell 输入的OCC单元
	 * @param i_shapeType 形状类型
	 * @param o_shape 输出的OCC形状
	 * @return true表示成功，false表示失败
	 */
    Ncti_Boolean get_occ_shape_by_ncti_cell(const NCTI_MODEL_TAG i_pOCCCell, int i_shapeType, TopoDS_Shape& o_shape);

    /**
	 * @brief 获取面单元列表
	 * @return 面单元列表
	 */
    const std::vector<Ncti_Integer*>& get_face_cell();

    /**
	 * @brief 获取边单元列表
	 * @return 边单元列表
	 */
    const std::vector<Ncti_Integer*>& get_edge_cell();

    /**
	 * @brief 获取顶点单元列表
	 * @return 顶点单元列表
	 */
    const std::vector<Ncti_Integer*>& get_vertex_cell();

    /**
	 * @brief 获取面标签映射
	 * @return 面标签到TopoDS_Shape的映射
	 */
    const std::map<Ncti_Integer, TopoDS_Shape>& get_face_tags();

    /**
	 * @brief 获取边标签映射
	 * @return 边标签到TopoDS_Shape的映射
	 */
    const std::map<Ncti_Integer, TopoDS_Shape>& get_edge_tags();

    /**
	 * @brief 获取顶点标签映射
	 * @return 顶点标签到TopoDS_Shape的映射
	 */
    const std::map<Ncti_Integer, TopoDS_Shape>& get_vertex_tags();

    /**
	 * @brief 添加属性段
	 * @param i_pSegment 渲染段对象指针
	 */
    void add_attribute_segment(NctiRenderSegmentItem* i_pSegment);

    /**
	 * @brief 获取属性段
	 * @param i_Cell 单元对象
	 * @param o_pSegment 输出的渲染段对象指针
	 */
    void get_attribute_segment(NCTI_MODEL_TAG i_Cell, NctiRenderSegmentItem*& o_pSegment);

    /**
	 * @brief 设置标签
	 * @param i_label 标签字符串
	 */
    void SetLable(const char* i_label);

    /**
	 * @brief 获取标签
	 * @return 标签字符串
	 */
    const char* GetLable() { return m_Label; }

public:
    /**
	 * @brief 初始化几何对象
	 */
    void init_geobject();

    /**
	 * @brief 对实体进行离散化
	 */
    void tessellation_body();

private:
    TopoDS_Shape* m_TopoDS_Shape;                          ///< TopoDS_Shape对象指针
    std::vector<Ncti_Integer*> m_FaceList;                 ///< 面列表
    std::vector<Ncti_Integer*> m_EdgeList;                 ///< 边列表
    std::vector<Ncti_Integer*> m_VertexList;               ///< 顶点列表
    NctiTopoShape* m_GEShape;                              ///< TopoShape对象
    std::map<Ncti_Integer, NctiTopoFace*> m_GEFaceMap;     ///< 面映射
    std::map<Ncti_Integer, NctiTopoEdge*> m_GEEdgeMap;     ///< 边映射
    std::map<Ncti_Integer, NctiTopoVertex*> m_GEVertexMap; ///< 顶点映射
    char* m_Label;                                         ///< 标签字符串
    std::map<Ncti_Integer, TopoDS_Shape> m_FaceTag;        ///< 面标签映射
    std::map<Ncti_Integer, TopoDS_Shape> m_EdgeTag;        ///< 边标签映射
    std::map<Ncti_Integer, TopoDS_Shape> m_VertexTag;      ///< 顶点标签映射

private:
    /**
	 * @brief 初始化函数
	 */
    void Init();
};
} // namespace NCTI

#endif