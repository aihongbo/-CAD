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

#ifndef NctiQTPubFun_H
#define NctiQTPubFun_H

#include "dcl_ncti_qt_pubfun.h"
#include "ncti_base.h"
#include <QWidget>
#include <QTextEdit>
#include <QColor>
#include <set>

namespace NCTI {

class NctiDocument;
class NctiBaseModel;
class NctiWindowPlatform;
class NctiWindowViewManager;
class NctiDisplayObject;
class NctiQtAIModelDataListDlg;
struct DocImage;
class AiLabelTree;
class NctiObjectTree;

/**
 * @brief 对象比较结构体
 * @details 用于存储对象比较的相关数据
 */
struct ObjCompareStruct
{
    std::string strDocName;     ///< 文档名称
    std::string strName;        ///< 对象名称
    std::string strKernel;      ///< 内核类型
    QColor color;               ///< 颜色
    double dLen;                ///< 线长
    double dArea;               ///< 表面积
    double dVolumn;             ///< 体积
    int iVERTEX;                ///< 顶点数
    int iEDGE;                  ///< 边数
    int iWIRE;                  ///< 线框数
    int iFACE;                  ///< 面数
    int iSHELL;                 ///< 壳数
    int iSOLID;                 ///< 实体数
    int iCOMPSOLID;             ///< 复合实体数
    int iCOMPOUND;              ///< 复合体数
    int iSHAPE;                 ///< 形状数
    int iFIN;                   ///< FIN数
    int iLAMINAR_EDGE;          ///< 层状边数
    int iMEM_USAGE;             ///< 内存使用情况
};

/**
 * @brief 内核执行结果结构体
 * @details 用于存储内核执行结果的相关数据
 */
struct KernelExecResult
{
    std::string strDocName;           ///< 文档名称
    std::string strKernel;            ///< 内核类型
    std::string Script;               ///< 脚本内容
    Ncti_Double time;                 ///< 执行时间
    Ncti_Integer result;              ///< 执行结果
    Ncti_Integer funcErrorCode;       ///< 函数错误代码
    std::string error;                ///< 错误信息
    std::string errorArgument;        ///< 错误参数
    std::string info;                 ///< 信息
    Ncti_Boolean Important;           ///< 是否重要
    Ncti_Double cpuUsage;             ///< CPU使用率
    Ncti_LongLong usedPhysicalMemory; ///< 使用的物理内存
};
#define ObjCompareList       std::vector<ObjCompareStruct>              ///< 对象比较列表类型定义
#define KernelExecResultList std::vector<std::vector<KernelExecResult>> ///< 内核执行结果列表类型定义

/**
 * @brief NCTI QT公共功能类
 * @details 提供各种NCTI QT相关的公共功能函数
 */
class DECL_NCTI_QT_PUBFUN NctiQTPubFun
{
public:
    /**
     * @brief 错误信息弹窗显示
     * @param[in] i_errType 错误类型
     */
    static void showErrorMsgBox(NctiErrorType i_errType);

    /**
     * @brief 绑定前处理视图窗口到当前窗口
     * @param[in] i_pQWidget 窗口控件指针
     * @return NctiWindowPlatform指针
     */
    static NctiWindowPlatform* CreateNctiViewWindow(QWidget* i_pQWidget);

    /**
     * @brief 创建装配体文档
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_model 模型文档类型
     * @param[in] i_constraintType 约束文档类型
     * @param[in] i_meshType 网格文档类型
     * @return NctiDocument指针
     */
    static NctiDocument* CreateAssemblyDocument(NctiWindowPlatform* i_pPlatform, 
        EnumModelDoc i_model,
        EnumGCSDoc i_constraintType = NCTI_GCS_DCM,
        EnumMeshDoc i_meshType = NCTI_MESH_GMSH);

    /**
     * @brief 添加装配体
     * @param[in] i_pPlatform 平台指针
     */
    static void AddAssembly(NctiWindowPlatform* i_pPlatform,
        EnumModelDoc i_model,
        EnumGCSDoc i_constraintType = NCTI_GCS_DCM,
        EnumMeshDoc i_meshType = NCTI_MESH_GMSH);
    
    /**
     * @brief 添加零件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_model 模型文档类型
     * @param[in] i_constraintType 约束文档类型
     * @param[in] i_meshType 网格文档类型
     */
    static void AddPart(NctiWindowPlatform* i_pPlatform,
                        EnumModelDoc i_model,
                        EnumGCSDoc i_constraintType = NCTI_GCS_DCM,
                        EnumMeshDoc i_meshType      = NCTI_MESH_GMSH);
    
    /**
     * @brief 创建模型文档
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_model 模型文档类型
     * @param[in] i_constraintType 约束文档类型
     * @param[in] i_meshType 网格文档类型
     * @return NctiDocument指针
     */
    static NctiDocument* CreateModelDocument(NctiWindowPlatform* i_pPlatform,
                                             EnumModelDoc i_model,
                                             EnumGCSDoc i_constraintType = NCTI_GCS_DCM,
                                             EnumMeshDoc i_meshType      = NCTI_MESH_GMSH);
    
    /**
     * @brief 导入装配体或零件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @return 导入成功返回true，否则返回false
     */
    static Ncti_Boolean ImportAssemblyOrPart(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 移除装配体或零件
     * @param[in] i_pPlatform 平台指针
     * @return 移除成功返回true，否则返回false
     */
    static Ncti_Boolean RemoveAssemblyOrPart(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 关闭模型文档
     * @param[in] i_pPlatform 平台指针
     */
    static void CloseModelDocument(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 获取当前视图的文档对象
     * @param[in] i_pPlatform 平台指针
     * @return NctiDocument指针
     */
    static NctiDocument* GetCurrentViewDocment(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 执行Python脚本
     * @param[in] i_pQWidget 窗口控件指针
     */
    static void ExecutePython(QWidget* i_pQWidget);

    /**
     * @brief 判断文档是否已经打开
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @return NctiDocument指针
     */
    static NctiDocument* CheckDocumentAlreadyOpen(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 加载NCTI文件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @return NctiDocument指针
     */
    static NctiDocument* LoadNctiFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 生成缩略图
     * @param[in] i_Buffer 输入图像数据缓冲区
     * @param[in] i_w 输入图像宽度
     * @param[in] i_h 输入图像高度
     * @param[in] i_rowPitch 输入图像行间距
     * @param[in] i_wThumbnail 缩略图宽度
     * @param[in] i_hThumbnail 缩略图高度
     * @param[out] ImageResult 输出图像结果
     * @return 生成成功返回true，否则返回false
     */
    static bool GetThumbnail(const std::vector<unsigned char>& i_Buffer,
                             Ncti_Integer i_w,
                             Ncti_Integer i_h,
                             Ncti_Integer i_rowPitch,
                             Ncti_Integer i_wThumbnail,
                             Ncti_Integer i_hThumbnail,
                             NCTI::DocImage& ImageResult);

    /**
     * @brief 保存为NCTI文件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     */
    static void SaveAsNctiFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath, Ncti_Boolean i_SaveAs = false);

    /**
     * @brief 导入模型文件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePaths 文件路径列表
     * @param[in] iImportMode 导入模式 0：不生成组合体；1：生成组合体；2：炸开并且分组显示；
     */
    static void ImportModelFile(NctiWindowPlatform* i_pPlatform, const QStringList& i_filePaths, int iImportMode = 0);

    /**
     * @brief 导出模型文件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     */
    static void ExportModelFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 导出文件
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     */
    static void ExportFile(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 撤销操作
     * @param[in] i_pDocument 文档指针
     */
    static void onUndo(NctiDocument* i_pDocument);

    /**
     * @brief 恢复上一次操作
     * @param[in] i_pDocument 文档指针
     */
    static void onRedo(NctiDocument* i_pDocument);

    /**
     * @brief 删除操作
     * @param[in] i_pDocument 文档指针
     */
    static void onDelete(NctiDocument* i_pDocument);

    /**
     * @brief 设置视图
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_viewtype 视图类型
     */
    static void SetView(NctiWindowPlatform* i_pPlatform, EnumNctiViewMode i_viewtype);

    /**
     * @brief 选择体
     * @param[in] i_pPlatform 平台指针
     * @param[in] bChecked 是否选中
     */
    static void SelBody(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked);

    /**
     * @brief 选择面
     * @param[in] i_pPlatform 平台指针
     * @param[in] bChecked 是否选中
     */
    static void SelFace(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked);

    /**
     * @brief 选择边
     * @param[in] i_pPlatform 平台指针
     * @param[in] bChecked 是否选中
     */
    static void SelEdge(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked);

    /**
     * @brief 选择顶点
     * @param[in] i_pPlatform 平台指针
     * @param[in] bChecked 是否选中
     */
    static void SelVertex(NctiWindowPlatform* i_pPlatform, Ncti_Boolean bChecked);

    /**
     * @brief 获取选择状态
     * @param[in] i_pPlatform 平台指针
     * @param[out] o_body 体选择状态
     * @param[out] o_face 面选择状态
     * @param[out] o_edge 边选择状态
     * @param[out] o_vertex 顶点选择状态
     */
    static void GetSel(NctiWindowPlatform* i_pPlatform,
                       Ncti_Boolean& o_body,
                       Ncti_Boolean& o_face,
                       Ncti_Boolean& o_edge,
                       Ncti_Boolean& o_vertex);

    /**
     * @brief 设置显示模式
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_face 面显示状态
     * @param[in] i_edge 边显示状态
     * @param[in] i_vertex 顶点显示状态
     */
    static void SetVisualMode(NctiWindowPlatform* i_pPlatform,
                              Ncti_Boolean i_face,
                              Ncti_Boolean i_edge,
                              Ncti_Boolean i_vertex);

    /**
     * @brief 全部显示
     * @param[in] i_pPlatform 平台指针
     */
    static void ShowAll(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 隐藏选中对象
     * @param[in] i_pPlatform 平台指针
     */
    static void HideSel(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 仅显示选中对象
     * @param[in] i_pPlatform 平台指针
     */
    static void OnlySelShow(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 最大化视图
     * @param[in] i_pPlatform 平台指针
     */
    static void MaxView(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 打开帮助文档
     */
    static void HelpDoc();
    
    /**
     * @brief 刷新视图
     * @param[in] i_pPlatform 平台指针
     */
    static void RefreshViews(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 查找内环面
     * @param[in] i_pPlatform 平台指针
     */
    static void SearchLoopFace(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 查找连接面
     * @param[in] i_pPlatform 平台指针
     */
    static void SearchConnectFace(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 查找相同连接面
     * @param[in] i_pPlatform 平台指针
     */
    static void SearchSameConnectFace(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 查找非平面连接面
     * @param[in] i_pPlatform 平台指针
     */
    static void SearchNoPlaneConnectFace(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 导出关联面
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     */
    static void ExportLinkFace(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);

    /**
     * @brief 特征识别
     * @param[in] i_pPlatform 平台指针
     */
    static void FeatureRecognition(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 拉伸识别
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_pCommandEdit 命令编辑框指针
     */
    static void StretchRecognition(NctiWindowPlatform* i_pPlatform, QTextEdit* i_pCommandEdit);
    
    /**
     * @brief 获取公共边
     * @param[in] pObj 显示对象指针
     * @param[in] CellID 单元ID
     * @return 公共边ID列表
     */
    static std::vector<Ncti_Long> GetCommonEdge(NctiDisplayObject* pObj, Ncti_Long CellID);

    /**
     * @brief AI孔识别
     * @param[in] i_pPlatform 平台指针
     */
    static void AIHoleRecognition(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 输出逆向
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_pCommandEdit 命令编辑框指针
     */
    static void OutputReversal(NctiWindowPlatform* i_pPlatform, QTextEdit* i_pCommandEdit);

    /**
     * @brief 圆角识别
     * @param[in] i_pDocument 文档指针
     */
    static void RoundRecognition(NctiDocument* i_pDocument);

    /**
     * @brief 倒角识别
     * @param[in] i_pDocument 文档指针
     */
    static void ChamferRecognition(NctiDocument* i_pDocument);

    /**
     * @brief 圆通孔识别
     * @param[in] i_pDocument 文档指针
     */
    static void ThroughHoleRecognition(NctiDocument* i_pDocument);

    /**
     * @brief 孔识别
     * @param[in] i_pPlatform 平台指针
     */
    static void HoleRecognition(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 显示拉伸标识对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @param[in] i_pPlatform 平台指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowExtrusionIdentifierDlg(NctiDocument* i_pDocument,
                                                   QWidget* i_pQWidget,
                                                   NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 显示创建长方体对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowCreateBoxDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示创建圆柱体对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowCreateCylinderDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示布尔并集对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowBooleanUnitDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示布尔差集对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowBooleanCutDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示布尔交集对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowBooleanCommonDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示移动对象对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowMoveObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示缩放对象对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowScaleObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示旋转对象对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowRotateObjectDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示倒圆角对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowFilletDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示移除特征对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowRemoveFeaturesDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示移除面对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowRemoveFacesDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示填充环对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowFillLoopDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示选择模式对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowSelectModeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示可视化模式对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowVisualModeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示AI模型添加标签对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowAIModelAddLabelDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示圆角识别列表对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowRoundRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示倒角识别列表对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowChamferRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示圆通孔识别列表对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowThroughHoleRecognitionListDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示AI模型数据列表对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @param[in] setAiLabels AI标签集合
     * @param[in] setAiFeatureLabels AI特征标签集合
     * @return NctiQtAIModelDataListDlg指针
     */
    static NctiQtAIModelDataListDlg* ShowAIModelDataListDlg(NctiDocument* i_pDocument,
                                                            QWidget* i_pQWidget,
                                                            const std::vector<AiLabelTree>& setAiLabels,
                                                            const std::vector<AiLabelTree>& setAiFeatureLabels,
                                                            NctiObjectTree* objectTree);

    /**
     * @brief 显示网格单点约束对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowMeshSinglePointConstraintDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示网格添加集中力对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowMeshAddCentralizeForceDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示网格添加材料对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowMeshAddMaterialDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示面属性对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowFaceAttributeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示边属性对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowEdgeAttributeDlg(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 圆角识别
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean RCornerRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief 孔识别
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean HoleRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief Logo识别
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean LogoRecognition(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 显示圆角提取对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowRCornerExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief 显示孔提取对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowHoleExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief 显示Logo提取对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowLogoExtract(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief 显示拉伸面对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowExtendFace(NctiDocument* i_pDocument, QWidget* i_pQWidget);
    
    /**
     * @brief 显示分离面对话框
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowSplitFace(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 全选
     * @param[in] i_pDocument 文档指针
     * @param[in] i_pQWidget 窗口控件指针
     * @return 操作是否成功
     */
    static Ncti_Boolean SelectAll(NctiDocument* i_pDocument, QWidget* i_pQWidget);

    /**
     * @brief 运行Python脚本
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @return 操作是否成功
     */
    static Ncti_Boolean RunPyScript(NctiWindowPlatform* i_pPlatform, const QString& i_filePath = "");
    
    /**
     * @brief 运行Python脚本
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @param[out] o_errMsg 错误消息
     * @return 操作是否成功
     */
    static Ncti_Boolean RunPyScript(NctiWindowPlatform* i_pPlatform, const QString& i_filePath, QString& o_errMsg);

    /**
     * @brief 批量运行Python脚本
     * @param[in] i_pPlatform 平台指针
     * @param[in] dirPath 目录路径
     * @param[in] i_model 模型文档类型
     * @param[in] i_constraintType 约束文档类型
     * @param[in] i_meshType 网格文档类型
     * @return 操作是否成功
     */
    static Ncti_Boolean RunBatchPyScript(NctiWindowPlatform* i_pPlatform,
                                         const QString& dirPath,
                                         EnumModelDoc i_model        = NCTI_GEOM_OCC,
                                         EnumGCSDoc i_constraintType = NCTI_GCS_DCM,
                                         EnumMeshDoc i_meshType      = NCTI_MESH_GMSH);
    
    /**
     * @brief 多核批量脚本运行
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_filePath 文件路径
     * @return 操作是否成功
     */
    static Ncti_Boolean MulticoreBatchScriptRun(NctiWindowPlatform* i_pPlatform, const QString& i_filePath);
    
    /**
     * @brief 获取对象名称
     * @param[in] pObject 显示对象指针
     * @param[in] iType 类型
     * @return 对象名称
     */
    static QString GetObjectName(NctiDisplayObject* pObject, int iType);
    
    /**
     * @brief 获取显示文本
     * @param[in] pObject 显示对象指针
     * @param[in] iType 类型
     * @return 显示文本
     */
    static QString GetDisplayStr(NctiDisplayObject* pObject, int iType);
    /**
     * @brief 爆炸显示
     * @param[in] i_pPlatform 平台指针
     * @return 操作是否成功
     */
    static bool Explosion(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 恢复对象显示
     * @param[in] i_pPlatform 平台指针
     */
    static void RecoverObject(NctiWindowPlatform* i_pPlatform);
    
    /**
     * @brief 文档爆炸显示
     * @param[in] i_pPlatform 平台指针
     * @param[in] iType 类型 0：所有文档炸开；1：当前激活的所有子文档炸开；2：当前激活的一级子文档炸开；
     * @return 操作是否成功
     */
    static bool DocExplosion(NctiWindowPlatform* i_pPlatform, int iType);
    
    /**
     * @brief 文档恢复对象显示
     * @param[in] i_pPlatform 平台指针
     */
    static void DocRecoverObject(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 获取对象比较数据库
     * @param[in] i_pDocument 文档指针
     * @return 对象比较列表
     */
    static ObjCompareList GetObjectCompareDB(NctiDocument* i_pDocument);
    
    /**
     * @brief 获取接口结果
     * @param[in] i_pDocument 文档指针
     * @return 内核执行结果列表
     */
    static KernelExecResultList GetInterfaceResult(NctiDocument* i_pDocument);

    /**
     * @brief 显示比较对话框
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_pQWidget 窗口控件指针
     */
    static void ShowCompareDlg(NctiWindowPlatform* i_pPlatform, QWidget* i_pQWidget);
    
    /**
     * @brief 显示多核批量脚本比较
     * @param[in] i_pPlatform 平台指针
     * @param[in] i_pQWidget 窗口控件指针
     */
    static void ShowMulticoreBatchScriptCompare(NctiWindowPlatform* i_pPlatform, QWidget* i_pQWidget);

    /**
     * @brief 刷新AI模型数据列表对话框
     * @param[in] i_pPlatform 平台指针
     */
    static void RefreshAIModelDataListDlg(NctiWindowPlatform* i_pPlatform);

    /**
     * @brief 添加渲染视图
     * @param[in] pPlatform 平台指针
     * @param[in] renderModelType 渲染模型类型
     */
    static void AddRenderView(NctiWindowViewManager* pPlatform, EnumRenderType renderModelType);
    
    /**
     * @brief Python显示对话框
     * @param[in] args 参数
     * @param[in] o_args 输出参数
     * @param[in] bReturn 是否返回
     * @param[in] mainWindow 主窗口指针
     * @return 操作是否成功
     */
    static Ncti_Boolean PythonShowDlg(void* args, void* o_args, bool bReturn, void* mainWindow);
    
    /**
     * @brief Python显示自定义对话框
     * @param[in] args 参数
     * @param[in] o_args 输出参数
     * @param[in] bReturn 是否返回
     * @param[in] mainWindow 主窗口指针
     * @return 操作是否成功
     */
    static Ncti_Boolean PythonShowCustomDlg(void* args, void* o_args, bool bReturn, void* mainWindow);
    
    /**
     * @brief 参数测试
     * @param[in] i_pDocument 文档指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ParamTest(NctiDocument* i_pDocument);

    /**
     * @brief 显示网格质量对话框
     * @param[in] nMode 模式
     * @param[in] sTextList 文本列表
     * @param[in] dValueList 值列表
     * @param[in] func 回调函数
     * @param[in] mainWindow 主窗口指针
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowMeshQualistyDlg(int nMode,
                                            std::vector<std::string> sTextList,
                                            const std::vector<double>& dValueList,
                                            std::function<void()> func,
                                            void* mainWindow);

    /**
     * @brief 显示保存对话框
     * @param[in] i_title 对话框标题
     * @param[in] i_filter 文件格式过滤器
     * @param[out] o_filename 保存的文件名
     * @return 操作是否成功
     */
    static Ncti_Boolean ShowSaveDialog(QWidget* i_parent, const QString& i_title, const QString& i_filter, QString& o_filename);
};
} // namespace NCTI
#endif