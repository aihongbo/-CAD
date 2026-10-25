#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

File: SenseDrawCmd.py
Desc: Function to create sense object,point,line,face,and other...
Author: lixk
Date: 2026-1-28
"""
import random


from mathAlgorithm.mathTool import vector_cross_product,vector_magnitude,normalize_vector,point_add_vector,multi_vector
lineR=float(2.0)
lineLength=float(60.0)
headR=float(4)
headLength=float(20.0)
class SenseDrawCmd():
    def __init__(self,global_scope):
        self.NCTI=global_scope["NCTI"]
        self.doc=global_scope["doc"]
        self.nameIdx=0
        self.baseName="entity"
        self.edgeCount=3
        self.cadView=None
    def setCadView(self,curView):
        self.cadView=curView
    def on_draw_point(self,event = None):
        if	self.cadView is None:
            return
        seg0 = self.cadView.SceneSegment().Subsegment(self.getRandomName())
        pts=self.generate_random_points(4,(0,100),(0,100),(0,100))
        cl= self.NCTI.Color(0,125,125)
        for pt in pts:
            curPt= self.NCTI.Point(pt[0],pt[1],pt[2])
            mesh0= seg0.InsertMarker(curPt)
        seg0.SetMarkerSize(8.0)
        seg0.SetMarkerColor(cl)
        seg0.SetMarkerStyle(0)
        seg0.SetVisibilityMarker(1)
        self.doc.SetVisualMode(1,1,1)

        self.cadView.Refresh(True)
    def on_draw_line(self,event = None):
        if	self.cadView is None:
            return
        seg0 = self.cadView.SceneSegment().Subsegment(self.getRandomName())
        pts=self.generate_random_points(4,(100,200),(0,100),(0,100))
        cl= self.NCTI.Color(125,0,0)
        ptsNcti=[]
        for pt in pts:
            ptsNcti.append(self.NCTI.Point(pt[0],pt[1],pt[2]))
        # TODO：请在下方完成绘制绘制线的函数实现，要求在seg0场景下应用坐标点列表ptsNcti进行绘制，完成后可删除当前行

    def on_draw_face(self,event = None):
        if	self.cadView is None:
            return

        seg0 = self.cadView.SceneSegment().Subsegment(self.getRandomName())
        pts=self.generate_random_points(1,(100,200),(100,200),(0,100))
        cl= self.NCTI.Color(0,255,0)
        ptsNcti=[]
        for pt in pts:
            ptsNcti.append(self.NCTI.Point(pt[0],pt[1],pt[2]))
        
        # self.doc.SetVisualMode(1,1,1)
        polygonName=self.getRandomName()

        self.doc.RunCommand("cmd_ncti_create_cone",polygonName,20,0,60,ptsNcti[0],self.NCTI.Vector(0,0,1),self.NCTI.Vector(1,0,0))
        ptsNctiTri,triangles =self.facetBodyAndDelete(polygonName)
        seg0.InsertTriangle(ptsNctiTri,triangles,[])
        seg0.SetFaceColor(cl)
        # seg0.SetVisibilityMarker(1)
        self.cadView.Refresh(True)
        # self.edgeCount+=1
    def facetBodyAndDelete(self,bodyName):
        vertexes,triangles,normals,uvs=self.doc.GetMesh(bodyName)
        self.doc.RunCommand("cmd_ncti_delete",[bodyName])
        ptCount=int(len(vertexes)/3)
        ptsNctiTri=[]
        for i in range(ptCount):
            curIdx=3*i
            ptsNctiTri.append(self.NCTI.Point(vertexes[curIdx],vertexes[curIdx+1],vertexes[curIdx+2]))
        return ptsNctiTri,triangles
    def on_draw_axis(self,event = None):
        if	self.cadView is None:
            return
        #总节点
        seg0 = self.cadView.SceneSegment().Subsegment(self.getRandomName())
        pts=self.generate_random_points(3,(0,100),(100,200),(0,100))
        cl= self.NCTI.Color(0,0,0)
        ptsNcti=[]
        for pt in pts:
            ptsNcti.append(self.NCTI.Point(pt[0],pt[1],pt[2]))
        
        self.doc.SetVisualMode(1,1,1)
        #绘制原点节点
        segOrientPt = seg0.Subsegment("orientPoint")
        segOrientPt.InsertMarker(ptsNcti[0])
        segOrientPt.SetMarkerSize(16.0)
        segOrientPt.SetMarkerColor(cl)
        segOrientPt.SetMarkerStyle(0)
        segOrientPt.SetVisibilityMarker(1)
        

        #根据随机点计算三个轴方向
        xVec=[ptsNcti[1].X,ptsNcti[1].Y,ptsNcti[1].Z]
        xDir=normalize_vector(xVec)

        yVec=[ptsNcti[2].X,ptsNcti[2].Y,ptsNcti[2].Z]
        yDir=normalize_vector(yVec)

        zVec=vector_cross_product(xDir,yDir)
        zDir=normalize_vector(zVec)

        yVecNew=vector_cross_product(xDir,zDir)
        yDirNew=normalize_vector(yVecNew)

        axisX= self.NCTI.Vector(xDir[0],xDir[1],xDir[2])
        axisY= self.NCTI.Vector(yDirNew[0],yDirNew[1],yDirNew[2])
        axisZ= self.NCTI.Vector(zDir[0],zDir[1],zDir[2])

        #绘制X轴
        segX = seg0.Subsegment("X_AXIS")
        self.addAxisSegment(segX,ptsNcti[0],axisX,axisY,self.NCTI.Color(255,0,0))
        #绘制Y轴
        segY = seg0.Subsegment("Y_AXIS")
        self.addAxisSegment(segY,ptsNcti[0],axisY,axisX,self.NCTI.Color(0,255,0))
        #绘制Z轴
        segZ = seg0.Subsegment("Z_AXIS")
        self.addAxisSegment(segZ,ptsNcti[0],axisZ,axisX,self.NCTI.Color(0,0,255))

        self.cadView.Refresh(True)
    def addAxisSegment(self,parentSeg,basePt,curAxis,ortherDir,axisColor):
        bpt=[basePt.X,basePt.Y,basePt.Z]
        newBaseVec=multi_vector(lineLength,curAxis)
        newBasePt=point_add_vector(bpt,newBaseVec)
        subBody = parentSeg.Subsegment("subAxisBody")
        subHead = parentSeg.Subsegment("subAxisHead")
        subCyd=self.getRandomName()
        subCn=self.getRandomName()
        self.doc.RunCommand("cmd_ncti_create_cylinder",subCyd,lineR,lineLength,basePt,curAxis,ortherDir)
        self.doc.RunCommand("cmd_ncti_create_cone",subCn,headR,0,headLength,self.NCTI.Point(newBasePt[0],newBasePt[1],newBasePt[2]),curAxis,ortherDir)
        ptsNctiTriBody,trianglesBody =self.facetBodyAndDelete(subCyd)
        ptsNctiTriHead,trianglesHead =self.facetBodyAndDelete(subCn)
        subBody.InsertTriangle(ptsNctiTriBody,trianglesBody,[])
        subBody.SetFaceColor(axisColor)
        subHead.InsertTriangle(ptsNctiTriHead,trianglesHead,[])
        subHead.SetFaceColor(axisColor)

    def getRandomName(self):
        self.nameIdx+=1
        return self.baseName+str(self.nameIdx)
    def generate_random_points(self,num_points, x_range=(0, 100), y_range=(0, 100),z_range=(0, 100)):
        points = []
        for _ in range(num_points):
            x = random.uniform(x_range[0], x_range[1])
            y = random.uniform(y_range[0], y_range[1])
            z = random.uniform(z_range[0], z_range[1])
            points.append([x, y,z])
        return points