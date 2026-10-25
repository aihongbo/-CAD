doc.Clear()
doc.ResetCaseResult()

doc.RunCommand("cmd_ncti_get_select_data")
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_create_curve_script", sel.ObjectNames, sel.CellIDs, "1", 0)

#同步数据
doc.RunCommand("cmd_ncti_mesh_update_physicalobj")

#生成体网格
sel = NCTI.SelectionManager(doc)
#MeshSize:网格尺寸
#MeshType:网格类型 0:triangle,1:QuadDominant,2:FullQuad
#AngleTol:角度容差
#AutoCurvature:曲率自适应 0-否 1-是
#HighOrder:二阶网格 0-否 1-是
#Parallel:并行计算 0-否 1-是
op = {"MeshSize":1, "MeshType":0, "AngleTol": 0, "AutoCurvature" : 0, "HighOrder":0, "Parallel": 0}
doc.RunCommand("cmd_ncti_create_volume_mesh", sel.ObjectNames, op)

#矩形生成体网格
doc.RunCommand("cmd_ncti_create_box","box1", 10, 20, 30)
#param2:模型名称数组
#param3:网格名称数组
#param4:网格剖分参数
doc.RunCommand("cmd_ncti_create_volume_mesh",["box1"], ["box_grid"],{"MeshSize":1, "MeshType":0,"HighOrder":0})

#生成面网格
sel = NCTI.SelectionManager(doc)
op = {"MeshSize":1, "MeshType":0, "HighOrder":0}
doc.RunCommand("cmd_ncti_create_surface_mesh", sel.ObjectNames, op)

#平面生成面网格
pt = NCTI.Point(0,0,0)
v1 = NCTI.Vector(0,0,1)
v2 = NCTI.Vector(1,0,0)
doc.RunCommand("cmd_ncti_create_plane", "p",pt,v1,v2)
#param2:模型名称数组
#param3:网格名称数组
#param4:网格剖分参数
doc.RunCommand("cmd_ncti_create_surface_mesh",["p"], ["plane_grid"], {"MeshSize":1, "MeshType":0,"HighOrder":0})

#网格set
#param2:set名称
#param3:对象名称
#param4:子单元或类型，子单元有节网格（点、单元、面、线）、几何（点、线、面）  类型有：1(NODE)、2(ELEMENT)、3(SURFACE)
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "Element_part_set1", sel.ObjectNames[0], 2)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "node_set1", sel.ObjectNames[0], sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "node_set2", sel.ObjectNames[0], sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "node_set3", sel.ObjectNames[0], sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "node_set4", sel.ObjectNames[0], sel.CellIDs)
#
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set", "face_set1", sel.ObjectNames[0], sel.CellIDs)

#几何set
#param2:set名称
#param3:对象名称
#param4:类型：1(NODE)、2(ELEMENT)、3(SURFACE)
#param5:子单元，可以传（不传为整个对象）  子单元（点、线、面）  
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Node_Geo_Set2", sel.ObjectNames[0], 1)
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Element_Geo_Set2", sel.ObjectNames[0], 2)
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Face_Geo_Set2", sel.ObjectNames[0], 3)
#
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Node_Geo_Set3", sel.ObjectNames[0], 1, sel.CellIDs)
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Element_Geo_Set3", sel.ObjectNames[0], 2, sel.CellIDs)
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Face_Geo_Set3", sel.ObjectNames[0], 3, sel.CellIDs)

#参考点
ref_pt = NCTI.Point(20,30,30)
doc.RunCommand("cmd_ncti_mesh_add_set_reference", "reference_node_set1", 0, [ref_pt])

#参考线
ref_pt = NCTI.Point(50,50,50)
ref_pt1 = NCTI.Point(50,0,0)
doc.RunCommand("cmd_ncti_mesh_add_set_reference", "reference_line_set1", 1, [ref_pt, ref_pt1])

#命令名称: cmd_ncti_mesh_add_local_coordinate_system
#功能描述: 添加或更新局部坐标系对象
#参数说明:
#param2: 坐标系名称 (字符串，为空时自动生成)
#param3: 原点位置 (NCTI.Point，例如 NCTI.Point(x, y, z))
#param4: X轴方向向量 (NCTI.Vector)
#param5: Y轴方向向量 (NCTI.Vector)
doc.RunCommand("cmd_ncti_mesh_add_local_coordinate_system", "", NCTI.Point(10, 10, 10), NCTI.Vector(1, 0, 0), NCTI.Vector(0, 1, 0))

#材料属性
#param2:材料名称
#param3:弹性模量
#param4:剪切模量
#param5:泊松比
#param6:密度
#param7:热膨胀
#param8:说明
doc.RunCommand("cmd_ncti_mesh_add_mat", "material1", 210000.0, 0, 0.3, 7.89e-09, None)

#功能描述: 弹性Lamina材料属性
#param1: E1 - 纵向弹性模量 (浮点数，沿纤维方向的弹性模量)
#param2: E2 - 横向弹性模量 (浮点数，垂直于纤维方向的弹性模量)
#param3: NU12 - 主泊松比 (浮点数)
#param4: G12 - 面内剪切模量 (浮点数，1-2平面内剪切刚度)
#param5: G13 - 横向剪切模量 (浮点数，1-3平面内剪切刚度)
#param6: G23 - 横向剪切模量 (浮点数，2-3平面内剪切刚度)
lamina_db = {"Elastic, type=LAMINA":["324000.,  8600.,   0.28,  4400.,  4400., 3071.4"]}
doc.RunCommand("cmd_ncti_mesh_add_mat", "material1", None, None, None, 7.89e-09, None, None, lamina_db)

#section
#param2:section名称
#param3:set名称
#param4:材料名称
#param5:类型 ：SOLID SHELL Surface BEAM
#param6:SHELL Thickness 
#param7:SHELL Sampling （default：5）
doc.RunCommand("cmd_ncti_mesh_add_section", "section1", "Element_Geo_Set2", "material1", "SOLID")

#MassInertia 添加惯性质量（点质量/惯性）
#param2: 惯性对象名称（字符串，如 "Inertia-1"）
#param3: set名称(参考点set)
#param4: 质量类型（布尔，True=各向同性，False=各向异性）
#param5: 各向同性质量值（浮点数或 None）
#param6: 各向异性 M11（浮点数或 None）
#param7: 各向异性 M22（浮点数或 None）
#param8: 转动惯量 I11（浮点数或 None）
#param9: 转动惯量 I22（浮点数或 None）
#param10: 转动惯量 I33（浮点数或 None）
#param11: 是否指定非对角元素（布尔，True=指定，False=不指定）
#param12: I12（浮点数或 None，仅在 param11=True 时有效）
#param13: I13（浮点数或 None，仅在 param11=True 时有效）
#param14: I23（浮点数或 None，仅在 param11=True 时有效）
#param15: 关联坐标系标识符（字符串，如 "Global"，空字符串表示无）
doc.RunCommand("cmd_ncti_add_point_mass_inertia", "Inertia-1","reference_node_set1", True, 0.0045)

#耦合
#param2:耦合名称
#param3:参考点set名称
#param4:面set名称
#param5:耦合类型 0:Kinematic; 1:Continuum distributing 2:Structural distributing
#param6:影响半径 -1:到区域的最外点; >=0:指定
#param7:自由度数组
#param8:各自由度是否使用，1表示使用
#param9:自适应控制点以放置在表面上(0,1)
#param10:热膨胀系数（耦合类型为0 Kinematic 有效）
#param11:连续分布 结构分布 加权法（耦合类型为1 Distributing 有效） 0:Uniforrm; 1:Linear 2:Quadratic 3:Cubic(m_iCouplingType 1:Continuum distributing 2:Structural distributing)
CouplingType = 0
InfluenceRadius = -1
Adjust = 0
Alpha = -1
WeightingMethod = 0
doc.RunCommand("cmd_ncti_mesh_add_coupling", "coupling", "reference_node_set1", "Face_Geo_Set3", CouplingType, InfluenceRadius, [1,2,3,4,5,6], [1,1,1,1,1,1], Adjust, Alpha, WeightingMethod)

#Tie
#param2:Tie名称
#param3:面set名称
#param4:面set名称
#param5:类型 0:default; 1:node to face 2:face to face
#param6:/Exclude shellelement thicknesse 
#param7:Position Tolerance 
#param8:Specify distance
#param9:Adjust secondary surface initial position
#param10:Tie rotational DOFs if applicable
#param11:Constraint Ratio
#param12:Ratio
iMethodType = 0
bThickness = True
bPositionToleranceDefault = True
dDistance = 0.0
bAdjust = True
bTieRotational = True
bConstraintRatioDefault = True
dRatio = 0.0
doc.RunCommand("cmd_ncti_mesh_add_tie", "tie1", "Face_Geo_Set2", "Face_Geo_Set3", iMethodType, bThickness, bPositionToleranceDefault, dDistance, bAdjust, bTieRotational, bConstraintRatioDefault, dRatio)

#固定约束
#param2:约束名称
#param3:set名称
#param4:自由度数组
#param5:各自由度的值，0表示固定
doc.RunCommand("cmd_ncti_mesh_add_spc", "cons", "Node_Geo_Set3", [1,2,3,4,5,6], [0,0,0,0,0,0])

#位移：沿x和y方向分别平移10m和20m
#param2:约束名称
#param3:set名称
#param4:自由度数组
#param5:各自由度的值
doc.RunCommand("cmd_ncti_mesh_add_spc", "cons2", "Node_Geo_Set3", [1,2], [10,20])


#集中力
#param2:力的名称
#param3:set名称
#param4:力的方向
#param5:力的大小
doc.RunCommand("cmd_ncti_mesh_add_force", "force", "Node_Geo_Set3", NCTI.Vector(1, 0, 0), 100)

#压力
#param2:压力的名称
#param3:set名称
#param4:力的大小
doc.RunCommand("cmd_ncti_mesh_add_pressure", "Pressure", "Face_Geo_Set3", 100)

#力矩
#param2:力矩的名称
#param3:set名称
#param4:力的方向
#param5:力的大小
doc.RunCommand("cmd_ncti_mesh_add_moment", "moment", "Node_Geo_Set3", NCTI.Vector(1, 0, 0), 100)


#重力加速度
#param2:名称
#param3:set名称
#param4:方向
#param5:加速度大小
doc.RunCommand("cmd_ncti_mesh_add_gravity", "graviry", "Element_Geo_Set2", NCTI.Vector(0, 0, -1), 9.8)


#惯性释放
#param2:力的名称
#param3:set名称
#param4:自由度数组，可选
#param5:各方向惯性释放的权重，可选
doc.RunCommand("cmd_ncti_mesh_add_inertia_relief", "relief", "Element_part_set1", [1,2,3,4,5,6], NCTI.Vector(10,20,30))

#输出
output = 1
node_vars = ["U", "UR", "UT", "V", "VR", "VT"]
element_vars =  ["E", "S"]
output_options = {}
node_options = {}
element_options = {"directions": "YES"}
#param2:输出的名称
#param3:输出类型，0-历史变量输出（history），1-场变量输出（field）
#param4:节点变量输出数组
#param5:单元变量输出数组
#param6:输出设置，可选
#param7:节点输出设置，可选
#param8:单元输出设置，可选
doc.RunCommand("cmd_ncti_mesh_add_output", "field", output, node_vars, element_vars, output_options, node_options, element_options)

output = 0
node_vars = ["ALLIE", "ALLIE"]
doc.RunCommand("cmd_ncti_mesh_add_output", "field", output , node_vars, [], {}, {}, {})

#创建模态分析步
options = {"eigensolver":"Lanczos", "acoustic_coupling": "projection", "normalization": "mass"}
#重载1：按阶提取
#param2:分析步名称
#param3:边界条件名称数组
#param4:变量输出名称数组
#param5:频率取值方式，0-按阶提取，1-按范围提取
#param6:模态的阶数
#param7:频率输出设置,省略则为默认值
doc.RunCommand("cmd_ncti_mesh_create_frequency_step", "Step_1",  ["cons1"], ["field"], 0, 25,options)
#重载2：按范围提取
#param2:分析步名称
#param3:边界条件名称数组
#param4:变量输出名称数组
#param5:频率取值方式，0-按阶提取，1-按范围提取
#param6:频率下限
#param7:频率上限
#param8:频率输出设置,省略则为默认值
doc.RunCommand("cmd_ncti_mesh_create_frequency_step", "Step_2",  ["cons1"], ["field"], 1, 10000., 200000.,options)

#创建屈曲分析步
options = {"eigensolver":"Lanczos", "acoustic_coupling": "projection", "normalization": "mass"}
#重载1：按阶提取
#param2:分析步名称
#param3:边界条件名称数组
#param4:力名称数组
#param5:变量输出名称数组
#param6:频率取值方式，0-按阶提取，1-按范围提取
#param7:模态的阶数
#param8:频率输出设置,省略则为默认值
doc.RunCommand("cmd_ncti_mesh_create_buckle_step", "Step_1",  ["cons1"], ["force","pressure", "moment", "graviry", "relief"], ["field"], 0, 5,options)
#重载2：按范围提取
#param2:分析步名称
#param3:边界条件名称数组
#param4:变量输出名称数组
#param5:频率取值方式，0-按阶提取，1-按范围提取
#param6:频率下限
#param7:频率上限
#param8:频率输出设置,省略则为默认值
doc.RunCommand("cmd_ncti_mesh_create_buckle_step", "Step_2",  ["cons1"], ["field"], 1, 10000., 200000.,options)

#创建静态分析步
#param2:分析步名称
#param3:边界条件名称数组
#param4:力名称数组
#param5:变量输出名称数组
#param6:分析参数(1、初始增量步，2、分析步时间，3、最小增量步，4、最大增量步) :[1., 1., 1e-05, 1.]
#param7:是否考虑大变形，False-不考虑，True-考虑
doc.RunCommand("cmd_ncti_mesh_create_static_step", "Step_3",  ["cons1", "cons2", ], ["force","pressure", "moment", "graviry", "relief"], ["field"],[1., 1., 1e-05, 1.])

#section 添加复合材料铺层（Composite Layup）
#param2: 铺层对象名称
#param3: 单元类型（0=ConventionalShell 1=SolidShell 2=Surface 3=Beam）
#param4: 方向参考坐标系名称
#param5: 法向轴（1/2/3）
#param6: 附加旋转类型（0=None 1=Angle 2=Distribution）
#param7: 附加角度
#param8: 附加分布
#param9: 截面积分（0=DuringAnalysis 1=BeforeAnalysis）
#param10: 厚度积分规则（0=Simpson 1=Gauss）
#param11: 是否对称铺层（True/False）
#param12: 铺层列表
#         每个子列表必须包含 **7 个元素**，顺序固定如下：
#         
#         索引 | 参数名            | 类型            | 说明
#         -----|------------------|----------------|------------------------------------------
#         0    | 铺层名称          | 字符串          | 铺层的唯一标识名，例如 "Ply-1"
#         1    | 集合名称          | 字符串          | 铺层应用的几何区域集合名称（如 "geometry_set"）
#         2    | 材料名称          | 字符串          | 已定义的复合材料材料名称（如 "M55J"）
#         3    | 厚度              | 浮点数          | 铺层厚度（长度单位，如 0.125）
#         4    | 参考坐标系名称     | 字符串          | 铺层方向参考坐标系，可为 "" 表示跟随层合板方向(abaqus界面默认<Layup>)
#         5    | 旋转角度          | 浮点数          | 铺层角度（度），相对于参考坐标系的旋转角
#         6    | 积分点数          | 整数            | 厚度方向高斯积分点数（通常为 3、5 等）
# 
#         示例子列表：
#             ["Ply-1", "geometry_set1", "M55J", 0.125, "", 15, 3]
# 
#         注意：
#             - 所有铺层按列表顺序从上到下叠加（第一层为最外层或最内层，取决于定义）。
#             - 集合名称、材料名称、坐标系名称必须与当前模型中已有对象名称匹配。
#             - 厚度、角度、积分点数应使用数字类型（整数或浮点数），不要用字符串。
#             - 铺层列表为空时，层合板无铺层（通常无效）。
doc.RunCommand("cmd_ncti_mesh_add_composite_layup",
               "CompositeLayup-3",
               0,
               "R1",
               1,
               1,
               90.0,
               "",
               0,
               0,
               False,
               [
                   ["Ply-1", "_Geo_Set_", "material1", 0.125, "", 15, 3],
                   ["Ply-2", "_Geo_Set_", "material1", 0.125, "", 45, 3],
               ])


#删除对象
doc.RunCommand("cmd_ncti_delete", "Pressure")


#导出inp文件
sel = NCTI.SelectionManager(doc)
#param2:inp文件路径
#param3:网格名称数组
#param4:是否使用缩减积分，默认不使用：0-不使用，1-使用
filename = "E:\\Work\\Model\\inp\\ncti_box20250912_1.inp"
doc.RunCommand("cmd_ncti_mesh_export_inp_file",  filename, ["box_grid"])