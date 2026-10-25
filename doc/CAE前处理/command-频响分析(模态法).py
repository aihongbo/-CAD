doc.Clear()
doc.ResetCaseResult()
sel = NCTI.SelectionManager(doc)


#1  
#几何set
#param2:set名称
#param3:对象名称
#param4:类型：1(NODE)、2(ELEMENT)、3(SURFACE)
#param5:子单元，可以传（不传为整个对象）  子单元（点、线、面）  
sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Element_Geo_Set1", sel.ObjectNames[0], 2, sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Element_Geo_Set2", sel.ObjectNames[0], 2, sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Node_Geo_Set1", sel.ObjectNames[0], 1, sel.CellIDs)

sel = NCTI.SelectionManager(doc)
doc.RunCommand("cmd_ncti_mesh_add_set_geometry", "Node_Geo_Set2", sel.ObjectNames[0], 1, sel.CellIDs)

#参考点
ref_pt = NCTI.Point(5,10,-5)
doc.RunCommand("cmd_ncti_mesh_add_set_reference", "reference_node_set1", 0, [ref_pt])


#2
#材料属性
#param2:材料名称
#param3:网格名称
#param4:弹性模量
#param5:剪切模量
#param6:泊松比
#param7:密度
#param8:热膨胀
#param9:说明
doc.RunCommand("cmd_ncti_mesh_add_mat", "material1", 72000.0, 0, 0.3, 2.7e-09, None)

#3
#section
#param2:section名称
#param3:set名称
#param4:材料名称
#param5:类型 ：SOLID SHELL Surface BEAM
doc.RunCommand("cmd_ncti_mesh_add_section", "section1", "Element_Geo_Set1", "material1", "SOLID")


#4
#固定约束
#param2:约束名称
#param3:set名称
#param4:自由度数组
#param5:各自由度的值，0表示固定
doc.RunCommand("cmd_ncti_mesh_add_spc", "cons1", "reference_node_set1", [1,2,3,4,5,6], [0,0,0,0,0,0])

#5
#添加集中力
doc.RunCommand("cmd_ncti_mesh_add_force", "f1", "Element_Geo_Set1", NCTI.Vector(0, 0, -1), 100)

#6
#输出
field_output = 1
node_vars = ["U", "V", "A","RF"]
element_vars =  ["S","E","F"]
output_options = {}
node_options = {}
element_options = {}
#param2:输出的名称
#param3:输出类型，0-历史变量输出，1-场变量输出
#param4:节点变量输出数组
#param5:单元变量输出数组
#param6:输出设置，可选
#param7:节点输出设置，可选
#param8:单元输出设置，可选
doc.RunCommand("cmd_ncti_mesh_add_output", "field", field_output, node_vars, element_vars, output_options, node_options, element_options)


#7
#创建频响分析步
#param2:频响分析的名称
#param3:约束条件
#param4:场变量名称
#param5:载荷名称
#param6:输出设置，包含”dload“,"freq","eigrl"
table = [-4.0, 10.0, 0.0, 10.0, 10.0, 50.0, 20.0, 100.0, 30.0, 200.0, 40.0, 500.0, 44.0, 500.0]
freqParam = {"f1":0.0,"df":0.0,"ndf":1,"comment":""}
rload = {"delay":0.0,"dphase":0.0,"tc":table,"td":[],"type":0,"comment":""}
dloadParam = {"scale":1.0,"scale_factors":[1.0],"rloads":[rload],"comment":""}
eigrlParam = {"nd":10,"msglvl":0,"comment":""}
doc.RunCommand("cmd_ncti_mesh_create_frequency_respon_step","feqrsp",["cons1"],["field"],["f1"],{"dload":dloadParam,"freq":freqParam,"eigrl":eigrlParam})

#8
#生成体网格
sel = NCTI.SelectionManager(doc)
op = {"MeshSize":2, "MeshType":2, "HighOrder":0}
doc.RunCommand("cmd_ncti_create_volume_mesh",sel.ObjectNames,[sel.ObjectNames[0]+"_mesh"], op)

