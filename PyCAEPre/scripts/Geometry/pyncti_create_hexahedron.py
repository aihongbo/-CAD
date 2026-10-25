#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
PyCAEPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""

import math

 #几何参数结构
class CavityDB:
    def __init__(self, cavity_width, cavity_height, embeddedNeck_diameter, 
    embeddedNeck_length, rubber_thickness, cavity_thickness, embeddedNeck_thickness):
        self.cavity_width = cavity_width #腔体宽度
        self.cavity_height = cavity_height #腔体高度
        self.embeddedNeck_diameter = embeddedNeck_diameter #内嵌颈内径
        self.embeddedNeck_length = embeddedNeck_length #内嵌颈长度
        self.rubber_thickness = rubber_thickness #橡胶层厚度
        self.cavity_thickness = cavity_thickness #腔体厚度
        self.embeddedNeck_thickness = embeddedNeck_thickness #内嵌颈厚度
        
#正多边形
def calculate_polygon_vertices(NCTI,doc,center_x, center_y, center_z, side_length, N):
    # 计算外接圆的半径
    radius = side_length / (2 * math.sin(math.pi / N))
    
    # 存储顶点坐标
    vertices = []
    
    # 角度增量
    angle_increment = 2 * math.pi / N
    
    for i in range(N):
        angle = i * angle_increment
        x = center_x + radius * math.cos(angle)
        y = center_y + radius * math.sin(angle)
        vertices.append(NCTI.Point(x, y, center_z)) 
    return vertices

#正六边形
def calculate_hexagon_vertices(NCTI,doc,center_x, center_y, center_z, side_length):
    # 六个顶点的角度（单位：弧度）
    angle_increment = math.pi / 3  # 60度 = pi / 3 弧度
    
    vertices = []
    for i in range(6):
        angle = i * angle_increment
        x = center_x + side_length * math.cos(angle)
        y = center_y + side_length * math.sin(angle)
        vertices.append(NCTI.Point(x, y, center_z))
    
    #for i, vertex in enumerate(cavity_vertices):
    #    print(f"顶点 {i + 1}: ({vertex.X:.2f}, {vertex.Y:.2f}, {vertex.Z:.2f})")    
    return vertices

#六棱柱
def hexagonal_prism(NCTI,doc,name, vertices, height,iNum):
    num = len(vertices)
    lineNmaes = []
    #for i, vertex in enumerate(vertices):
    for i, vertex in enumerate(vertices):
        pt = vertex
        if i + 1 == iNum:
            pt = vertices[0]
        else:
            pt = vertices[i + 1]
        lineName = "line_" + str(i)
        lineNmaes.append(lineName)
        doc.RunCommand("cmd_ncti_create_line", lineName, vertex, pt)
    
    vector = NCTI.Vector(0, 0, height)
    doc.RunCommand("cmd_ncti_create_wire", "wire", lineNmaes)
    doc.RunCommand("cmd_ncti_create_plane", "plan", "wire")
    lineNmaes.append("wire")
    doc.RunCommand("cmd_ncti_prism", name, "plan", vector)
    lineNmaes.append("plan")
    doc.RunCommand("cmd_ncti_delete", lineNmaes)

#腔体
def create_object(NCTI,doc,cavity_vertices, rubber_vertices, ollowing_out_vertices, ptCenter, cavityDB, row, cel, iNum):
    objectNmae = "hexagon"
    cavity = "cavity1"
    cavity_result = "cavity"
    rubber = "rubber"
    embeddedNeck = "embeddedNeck"
    ollowingOut = "ollowingOut"
    
    #腔体六棱柱
    hexagonal_prism(NCTI,doc,cavity, cavity_vertices, cavityDB.cavity_height,iNum)
    doc.Zoom()
    #橡胶六棱柱
    hexagonal_prism(NCTI,doc,rubber, rubber_vertices, cavityDB.cavity_height - 2 * cavityDB.cavity_thickness,iNum)
    #挖空六棱柱
    hexagonal_prism(NCTI,doc,ollowingOut, ollowing_out_vertices, cavityDB.cavity_height - cavityDB.rubber_thickness,iNum)
    #腔体
    doc.RunCommand("cmd_ncti_boolean_cut", cavity, rubber)
    #橡胶
    doc.RunCommand("cmd_ncti_boolean_cut", rubber, ollowingOut)
    
    doc.RunCommand("cmd_ncti_delete", ollowingOut)
    
    #内嵌颈顶部中心
    embeddedNeck_center = ptCenter
    embeddedNeck_center.Z += cavityDB.cavity_height - cavityDB.embeddedNeck_length
    #
    doc.RunCommand("cmd_ncti_create_cylinder", embeddedNeck, 0.5 * cavityDB.embeddedNeck_diameter, cavityDB.embeddedNeck_length, embeddedNeck_center, NCTI.Vector(0, 0, 1))
    doc.RunCommand("cmd_ncti_create_cylinder", ollowingOut, 0.5 * cavityDB.embeddedNeck_diameter - cavityDB.embeddedNeck_thickness, cavityDB.embeddedNeck_length, embeddedNeck_center, NCTI.Vector(0, 0, 1))
    doc.RunCommand("cmd_ncti_boolean_cut", cavity, ollowingOut)
    doc.RunCommand("cmd_ncti_boolean_cut", embeddedNeck, ollowingOut)
    doc.RunCommand("cmd_ncti_delete", ollowingOut)
    doc.RunCommand("cmd_ncti_boolean_unit", cavity_result, cavity, embeddedNeck)
    doc.RunCommand("cmd_ncti_delete", cavity, embeddedNeck)
    doc.RunCommand("cmd_ncti_delete", embeddedNeck)
    
    #阵列
    offset_distance = math.sqrt(3) * cavityDB.cavity_width
    #原始向量
    x, y, z = math.sqrt(3), 1, 0
    #向量的模长
    magnitude = math.sqrt(x**2 + y**2 + z**2)
    #单位向量
    unit_vector = (x / magnitude, y / magnitude, z / magnitude)
    
    for r in range(0, int(cel)):
        name1 = cavity_result + "_" + str(r + 1) 
        name2 = rubber + "_" + str(r + 1) 
        gCName = "c" + str(r + 1) 
        #doc.RunCommand("cmd_add_new_body_group", gCName)
        
        for c in range(0, int(row)):
            if r == 0 and c == 0:
                continue
            c1 = name1 + "_" + str(c + 1)
            c2 = name2 + "_" + str(c + 1)
            gRName = gCName +  "_" + str(c + 1)
            
            #doc.RunCommand("cmd_add_new_body_group",  gRName)
            #doc.RunCommand("cmd_move_body_group", gRName, gCName)
            
            doc.RunCommand("cmd_ncti_copy_body", c1, cavity_result)
            doc.RunCommand("cmd_ncti_copy_body", c2, rubber)
            vec = NCTI.Vector(unit_vector[0] * r * offset_distance, unit_vector[1] *( r * offset_distance + c * offset_distance * 2), 0)
            doc.RunCommand("cmd_ncti_pan", [c1,c2], vec)
            
            #doc.RunCommand("cmd_move_body_group", c1, gRName)
            #doc.RunCommand("cmd_move_body_group", c2, gRName)
        doc.Zoom()
 


def pyncti_create_hexahedron(NCTI,doc):
    iNum = 6
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "六棱柱参数", "底部中心点坐标", NCTI.Point(0, 0, 0), "腔体宽度", 30.0, "腔体高度", 50.0, "内嵌颈内径",  4.3, "内嵌颈长度", 30.0, "橡胶层厚度", 10.0, "腔体厚度", 1.0, "内嵌颈厚度", 1.0, "行数", 1.0, "列数", 1.0)
    if len(res) > 0:
        ptCenter = res[0]
        cavity_width = res[1]
        cavity_height = res[2]
        embeddedNeck_diameter = res[3]
        embeddedNeck_length = res[4]
        rubber_thickness = res[5]
        cavity_thickness = res[6]
        embeddedNeck_thickness = res[7]
        row = res[8]
        cel = res[9]
        #几何参数
        cavityDB = CavityDB(cavity_width, cavity_height, embeddedNeck_diameter, 
        embeddedNeck_length, rubber_thickness, cavity_thickness, embeddedNeck_thickness)
        # 计算六个顶点的坐标
        #vertices = calculate_hexagon_vertices(NCTI,doc,center_x, center_y, center_z, side_length)
        #腔体
        cavity_vertices = calculate_polygon_vertices(NCTI,doc,ptCenter.X, ptCenter.Y, ptCenter.Z, cavity_width, iNum)
        #橡胶
        rubber_vertices = calculate_polygon_vertices(NCTI,doc,ptCenter.X, ptCenter.Y, ptCenter.Z + cavity_thickness, cavity_width - 2 * cavity_thickness, iNum)
        #挖空
        ollowing_out_vertices = calculate_polygon_vertices(NCTI,doc,ptCenter.X, ptCenter.Y, ptCenter.Z + cavity_thickness + rubber_thickness, cavity_width - 2 * cavity_thickness - 2 * rubber_thickness, iNum)
        
        seg = doc.Scene()
        seg.SetPetranent(0.1)
        #创建六棱柱腔体
        create_object(NCTI,doc,cavity_vertices, rubber_vertices, ollowing_out_vertices, ptCenter, cavityDB, row, cel,iNum)
        #seg.SetPetranent(0)
    else:
        print("取消")

pyncti_create_hexahedron(NCTI,doc)