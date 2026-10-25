/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and cditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#ifndef MAINWINDOWSIGNALS_H
#define MAINWINDOWSIGNALS_H

#include <QObject>

namespace NCTI {
/**
 * @brief MainWindow的信号集合类
 */
class MainWindowSignals : public QObject
{
    Q_OBJECT

public:
Q_SIGNALS:
    /**
     * @brief 打开自定义配置窗口
     */
    void openCustomSetting();

    /**
     * @brief 打开UI配置窗口
     */
    void openUIOption();

    /*********************文件相关信号*********************/
    /**
     * @brief 打开NCTI文件
     * @param filePath 文件路径
     */
    void openNcti(const QString& filePath = "");

    /**
     * @brief 保存NCTI文件
     */
    void saveNcti();

    /**
     * @brief 另存为NCTI文件
     */
    void saveAsNcti();

    /**
     * @brief 关闭文档
     */
    void closeDocument();

    /**
     * @brief 新建装配体
     */
    void newAssembly();

    /**
     * @brief 添加装配体
     */
    void addAssembly();

    /**
     * @brief 添加零件
     */
    void addPart();

    /**
     * @brief 导入装配体或零件
     */
    void importAssemblyOrPart();

    /**
     * @brief 移除装配体或零件
     */
    void removeAssemblyOrPart();

    /**
     * @brief 新建零件
     */
    void newPart();

    /**
     * @brief 导入模型
     */
    void importModel();

    /**
     * @brief 导出模型
     */
    void exportModel();

    /**
     * @brief 撤销操作
     */
    void undo();

    /**
     * @brief 重做操作
     */
    void redo();

    /**
     * @brief 删除对象
     */
    void deleteObject();

    /**
     * @brief 运行脚本
     */
    void scriptRun();

    /**
     * @brief 批量运行脚本
     */
    void batchScriptRun();

    /**
     * @brief 多核批量运行脚本
     */
    void multicoreBatchScriptRun();

    /*********************视图相关信号*********************/
    /**
     * @brief 等轴测视图
     */
    void isometricView();

    /**
     * @brief 缩放全部
     */
    void zoomAll();

    /**
     * @brief 最大化视图
     */
    void maxView();

    /**
     * @brief 显示全部
     */
    void showAll();

    /**
     * @brief 隐藏选中对象
     */
    void hideSel();

    /**
     * @brief 显示选中对象
     */
    void showSel();

    /**
     * @brief 设置视图方向
     * @param objName 视图方向名称
     */
    void setView(const QString& objName);

    /**
     * @brief 全选
     */
    void selectAll();

    /**
     * @brief 添加VTK视图
     */
    void addVtkView();

    /**
     * @brief 添加Vulkan视图
     */
    void addVulkanView();

    /**
     * @brief 设置选择模式
     * @param objName 选择模式名称
     */
    void selectMode(const QString& objName);

    /**
     * @brief 设置显示模式
     * @param objName 显示模式名称
     */
    void visualMode(const QString& objName);

    /*********************几何相关信号*********************/
    /**
     * @brief 执行创建立方体操作
     */
    void executeBox();

    /**
     * @brief 执行创建圆柱体操作
     */
    void executeCylinder();

    /**
     * @brief 执行布尔运算操作
     */
    void executeBoolean();

    /**
     * @brief 执行圆角操作
     */
    void executeFillet();

    /**
     * @brief 执行倒角操作
     */
    void executeChamfer();

    /**
     * @brief 几何平移操作
     */
    void geoPan();

    /**
     * @brief 几何缩放操作
     */
    void geoZoom();

    /**
     * @brief 几何旋转操作
     */
    void geoRotate();

    /**
     * @brief 移除特征
     */
    void removeFeature();

    /**
     * @brief 移除面
     */
    void removeFace();

    /**
     * @brief 提取子对象
     */
    void executeExtractSubObj();

    /**
     * @brief 填充环
     */
    void executeFillLoop();

    /**
     * @brief 组合操作
     */
    void executeCompound();

    /**
     * @brief 爆炸体
     */
    void executeExplodeBody();

    /**
     * @brief 缝合操作
     */
    void executeSewing();

    /**
     * @brief 分离面
     */
    void executeSeparatFace();

    /**
     * @brief 创建延伸面
     */
    void createExtendFace();

    /**
     * @brief 线性阵列
     */
    void linearArray();

    /**
     * @brief 旋转阵列
     */
    void rotateArray();

    /**
     * @brief 曲线阵列
     */
    void curveArray();

    /**
     * @brief 曲线偏移
     */
    void curveOffset();

    /*********************草图相关信号*********************/
    /**
     * @brief 新建草图
     */
    void draftNew();

    /**
     * @brief 草图坐标
     */
    void draftCoord();

    /**
     * @brief 删除草图
     */
    void deleteDraft();

    /**
     * @brief 重建草图
     */
    void draftRebuild();

    /**
     * @brief 草图矩形
     */
    void draftRectangle();

    /**
     * @brief 草图圆形
     */
    void draftCircle();

    /**
     * @brief 草图多边形
     */
    void draftPolygon();

    /**
     * @brief 草图椭圆
     */
    void draftEllipse();

    /**
     * @brief 草图圆到圆
     */
    void draftCircleToCircle();

    /**
     * @brief 草图直线
     */
    void draftLine();

    /**
     * @brief 草图圆弧
     */
    void draftArc();

    /**
     * @brief 草图线框
     */
    void draftWire();

    /**
     * @brief 草图B样条曲线
     */
    void draftBspline();

    /**
     * @brief 草图中心线
     */
    void draftCenterline();

    /**
     * @brief 草图点
     */
    void draftPoint();

    /**
     * @brief 草图重置视图
     */
    void draftResetView();

    /**
     * @brief 退出草图
     */
    void draftExit();

    /**
     * @brief 草图拉伸
     */
    void draftExtrude();

    /**
     * @brief 草图旋转
     */
    void draftRotate();

    /**
     * @brief 草图特征布尔运算
     */
    void draftFeatureBoolean();

    /**
     * @brief 编辑草图
     */
    void draftEdit();

    /**
     * @brief 草图模型化
     */
    void draftModelization();

    /**
     * @brief 草图移到顶层
     */
    void draftMoveToTop();

    /**
     * @brief 草图移到底层
     */
    void draftMoveToBottom();

    /**
     * @brief 草图上移
     */
    void draftUpside();

    /**
     * @brief 草图下移
     */
    void draftDownside();

    /**
     * @brief 草图并集
     */
    void draftUnit();

    /**
     * @brief 草图差集
     */
    void draftCut();

    /**
     * @brief 草图内爆
     */
    void draftImplode();

    /**
     * @brief 草图外爆
     */
    void draftExplode();

    /*********************草图约束相关信号*********************/
    /**
     * @brief 草图平行
     */
    void draftParallel();

    /**
     * @brief 草图垂直
     */
    void draftPerpendicular();

    /**
     * @brief 草图相切
     */
    void draftTangent();

    /**
         * @brief 草图固定约束
         */
    void draftFix();

    /**
     * @brief 草图重合约束
     */
    void draftCoincident();

    /**
     * @brief 草图同心约束
     */
    void draftConcentric();

    /**
    * @brief 草图等半径约束
    */
    void draftEqualRadius();

    /**
     * @brief 草图对称约束
     */
    void draftSymmetric();

    /**
     * @brief 草图距离约束
     */
    void draftDistance();

    /**
     * @brief 草图角度约束
     */
    void draftAngle();

    /**
     * @brief 草图半径约束
     */
    void draftRadius();

    /*********************AI相关信号*********************/
    /**
     * @brief 特征识别
     */
    void featureIdentifier();

    /**
     * @brief 特征列表
     */
    void featureList();

    /**
     * @brief 圆角识别
     */
    void filletIdentifier();

    /**
     * @brief 孔识别
     */
    void holeIdentifier();

    /**
     * @brief Logo识别
     */
    void logoIdentifier();

    /**
     * @brief 圆角提取
     */
    void filletExtract();

    /**
     * @brief 孔提取
     */
    void holeExtract();

    /**
     * @brief Logo提取
     */
    void logoExtract();

    /**
     * @brief AI识别列表
     */
    void roundRecognition();

    /**
     * @brief 倒角识别
     */
    void chamferRecognition();

    /**
     * @brief 孔识别
     */
    void throughHoleRecognition();

    /**
     * @brief 拓扑结构显示
     */
    void topoStructure();

    /**
     * @brief 边属性
     */
    void edgeAttribute();

    /**
     * @brief 面属性
     */
    void faceAttribute();

    /**
     * @brief UV网格显示
     */
    void uvGrid();

    /**
     * @brief 导出链接面
     */
    void exportLinkFace();

    /*********************仿真相关信号*********************/
    /**
     * @brief 添加力
     */
    void meshAddForce();

    /**
     * @brief 添加约束
     */
    void meshAddSpc();

    /**
     * @brief 添加材料
     */
    void meshAddMat();

    /**
     * @brief 从表面生成网格
     */
    void meshFromSurface();

    /**
     * @brief 从体积生成网格
     */
    void meshFromVolume();

    /**
     * @brief 显示网格质量
     */
    void meshShowMeshQuality();

    /**
     * @brief 网格选择
     * @param objectName 网格对象名称
     */
    void meshGridSelect(const QString& objectName);

    /**
     * @brief 快速选择
     */
    void meshQuickSelect();

    /**
     * @brief 切换网格引擎
     */
    void meshModifyMeshType();

    /*********************设置相关信号*********************/
    /**
     * @brief 打开系统配置窗口
     */
    void onOptions();

    /**
     * @brief 控制台
     */
    void console();

    /**
     * @brief 脚本编辑器
     */
    void scriptEdit();

    /**
     * @brief 对象树
     */
    void objectTree();

    /*********************装配相关信号*********************/
    /**
     * @brief 固定
     */
    void consFix();

    /**
     * @brief 重合
     */
    void consCoincident();

    /**
     * @brief 平行
     */
    void consParallel();

    /**
     * @brief 同心
     */
    void consConcentric();

    /**
     * @brief 重合
     */
    void consPerpendicular();

    /**
     * @brief 距离
     */
    void consDistance();

    /**
     * @brief 角度
     */
    void consAngle();

    /**
     * @brief 等距
     */
    void consEqualDistance();

    /**
     * @brief 导出装配约束脚本
     */
    void assExport();

};

} // namespace NCTI
#endif // MAINWINDOWSIGNALS_H