
#导出bdf文件
from pyNastran.bdf.bdf import BDF
from typing import List
class OutPutBDF:
    def __init__(self, fileName, objName, parent=None):
        self.doc = parent.doc
        self.NCTI = parent.NCTI
        self.filename = fileName
        self.objName = objName

    def case_Point1(self, model:BDF, meshID, eid) -> None:
        pass

    def case_Edge2(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_crod(eid, meshID, nids)

    def case_Edge3(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cbar(eid, meshID, nids, None, None)

    def case_Triangle3(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctria3(eid, meshID, nids)

    def case_Triangle6(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctria6(eid, meshID, nids)

    def case_Quadrangle4(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cquad4(eid, meshID, nids)

    def case_Quadrangle8(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cquad8(eid, meshID, nids)

    def case_Quadrangle9(self, model:BDF, meshID, eid) -> None:
        pass

    def case_Tetrahedron4(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctetra(eid, meshID, nids)

    def case_Tetrahedron10(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctetra(eid, meshID, nids)

    def case_Hexahedron8(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctetra(eid, meshID, nids)

    def case_Hexahedron20(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctetra(eid, meshID, nids)

    def case_Hexahedron27(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_ctetra(eid, meshID, nids)

    def case_Prism6(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpenta(eid, meshID, nids)

    def case_Prism15(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpenta(eid, meshID, nids)

    def case_Prism18(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpenta(eid, meshID, nids)

    def case_Pyramid5(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpyram(eid, meshID, nids)

    def case_Pyramid13(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpyram(eid, meshID, nids)

    def case_Pyramid14(self, model:BDF, meshID, eid) -> None:
        element = self.NCTI.MeshElement(eid)
        nids = element.AllNode()
        model.add_cpyram(eid, meshID, nids)

    def GetElementFunc(self, type):
        if type == 0:
            return self.case_Point1
        elif type == 1:
            return self.case_Edge2
        elif type == 2:
            return self.case_Edge3
        elif type == 3:
            return self.case_Triangle3
        elif type == 4:
            return self.case_Triangle6
        elif type == 5:
            return self.case_Quadrangle4
        elif type == 6:
            return self.case_Quadrangle8
        elif type == 7:
            return self.case_Quadrangle9
        elif type == 8:
            return self.case_Tetrahedron4
        elif type == 9:
            return self.case_Hexahedron8
        elif type == 10:
            return self.case_Hexahedron20
        elif type == 11:
            return self.case_Hexahedron27
        elif type == 12:
            return self.case_Prism6
        elif type == 13:
            return self.case_Prism15
        elif type == 14:
            return self.case_Prism18
        elif type == 15:
            return self.case_Pyramid5
        elif type == 16:
            return self.case_Pyramid13
        elif type == 17:
            return self.case_Pyramid14

    def case_Unknown_Load(self, model:BDF, load, count) -> List[int]:
        return []

    def case_Concentrated_Force(self, model:BDF, load, count)  -> List[int]:
        # 集中力
        vector = load[1]
        magnitude = load[2]
        nids = load[3]
        sids  = []
        for i in range(len(nids)):
            sid = count + i + 1
            sids.append(sid)
            x = vector.X
            y = vector.Y
            z = vector.Z
            model.add_force(sid, nids[i], magnitude,  [x, y, z])
        return sids

    def case_Pressure(self, model:BDF, load, count) -> List[int]:
        # 压力
        return []

    def case_Moment(self, model:BDF, load, count) -> List[int]:
        # 力矩
        magnitude = load[1]
        vector = load[2]
        nids = load[3]
        sids  = []
        for i in range(len(nids)):
            sid = count + i + 1
            sids.append(sid)
            x = vector.X
            y = vector.Y
            z = vector.Z
            model.add_moment(sid, nids[i], magnitude, [x, y, z])
        return sids

    def case_Gravity(self, model:BDF, load, count) -> List[int]:
        # 重力
        magnitude = load[1]
        vector = load[2]
        sids  = []
        sid = count + 1
        sids.append(sid)
        x = vector.X
        y = vector.Y
        z = vector.Z
        model.add_grav(sid, magnitude, [x, y, z])
        return sids

    def case_Inertia_Relief(self, model:BDF, load, count) -> List[int]:
        # 惯性释放
        components = load[1]
        weights = load[2]
        if len(components) > 0:
            # 定义节点和虚支座
            model.add_param("INREL", -1)
            nodes = []
            model.get_point_grids(nodes)
            model.add_suport(nodes, components) 
            #？？？
        else:
            model.add_param("INREL", -2)
        return []

    def GetLoadFunc(self, type):
        if type == 0:
            return self.case_Unknown_Load
        elif type == 1:
            return self.case_Concentrated_Force
        elif type == 2:
            return self.case_Pressure
        elif type == 3:
            return self.case_Moment
        elif type == 4:
            return self.case_Gravity
        elif type == 5:
            return self.case_Inertia_Relief

    def case_U(self, subcase):
        subcase.add('DISPLACEMENT', 'ALL', [], 'STRING-type')

    def case_UR(self, subcase):
        subcase.add('ROTATION', 'ALL', [], 'STRING-type')

    def case_UT(self, subcase):
        pass

    def case_V(self, subcase):
        subcase.add('VELOCITY', 'ALL', [], 'STRING-type')

    def case_VR(self, subcase):
        subcase.add('ANGULAR VEL', 'ALL', [], 'STRING-type')

    def case_VT(self, subcase):
        pass

    def case_E(self, subcase):
        subcase.add('STRAIN', 'ALL', [], 'STRING-type') 

    def case_S(self, subcase):
        subcase.add('STRESS', 'ALL', [], 'STRING-type') 

    def case_Other(self, model):
        pass

    def GetOutputFunc(self, field):
        if field == "U":
            return self.case_U
        elif field == "UR":
            return self.case_UR
        elif field == "UT":
            return self.case_UT
        elif field == "V":
            return self.case_V
        elif field == "VR":
            return self.case_VR
        elif field == "VT":
            return self.case_VT
        elif field == "E":
            return self.case_E
        elif field == "S":
            return self.case_S
        else:
            return self.case_Other
        
    def outputBDFFile(self):
        objects = []
        if self.objName == None or self.objName == "":
            objects = self.doc.AllNames()
        else:
            objects.append(self.objName)
        model = BDF()
        matData = {}
        meshID = 0

        pyhObj = self.NCTI.Object(self.doc)    
        for objName in objects:
            if objName == None or objName == "":
                continue
            mesh = self.NCTI.GridMesh(self.doc, objName)#self.objName
            
            #输出节点
            nodeNumbers = mesh.GetAllVertexs()#顶点编号
            if nodeNumbers == None or len(nodeNumbers) == 0:
                continue
            meshID += 1
            #顶点位置
            positions = mesh.GetVertexPosition(nodeNumbers)
            for i in range(len(positions)):
                nid = nodeNumbers[i]
                pos = positions[i]
                model.add_grid(nid, [pos.X, pos.Y, pos.Z])

            #输出单元
            elementNumbers = mesh.GetAllElements()
            for i in range(len(elementNumbers)):
                eid = elementNumbers[i]
                print(eid)
                element = self.NCTI.MeshElement(eid)
                elemType = element.ElementType()
                self.GetElementFunc(elemType)(model, meshID, eid)  

            if(1 == 1):
                #输出材料
                matNames = mesh.GetMaterials()
                if matNames != None and len(matNames) > 0:
                    #没有添加的材料
                    noneNames = []
                    for matName in matNames:
                        if matName not in matData:
                            noneNames.append(matName)
                        else:                        
                            model.add_psolid(meshID, matData[matName])

                    mats = pyhObj.GetObjectData(noneNames)
                    for i in range(len(noneNames)):
                        mid=len(matData) + 1
                        matData[noneNames[i]] = mid
                        mat = mats[i]
                        dE = mat[1][1]#弹性模量
                        dG = mat[2][1]#剪切模量
                        dNU = mat[3][1]#泊松比
                        dRHO = mat[4][1]#密度
                        dA = mat[5][1]#热膨胀
                        model.add_mat1(mid, E=dE, G=dG, nu=dNU, rho=dRHO, a=dA)
                        model.add_psolid(meshID, mid)
                                
        if(1 == 1):
            stepNames = self.doc.GetSteps()#分析步名称
            if stepNames != None and len(stepNames) > 0:
                subcases = model.create_subcases(list(range(1, len(stepNames) + 1)))
                spcCount = 0
                loadCount = 0
                for i in range(len(stepNames)):
                    stepName = stepNames[i]
                    step = self.NCTI.StepObject(self.doc, stepName)
                    stepType = step.GetStepType()
                    if stepType == 1:
                        model.sol = 101#静态分析步
                        subcases[i+1].add('ANALYSIS', "STATICS", [], 'STRING-type')
                    elif stepType == 2:
                        model.sol = 103#模态分析步
                    else:
                        print("Unknown step type")
                        continue    
                    subcases[i+1].add('SUBTITLE', stepName, [], 'STRING-type')
                    

                    #输出边界条件
                    spcNames = step.GetSPCs()
                    spcs = pyhObj.GetObjectData(spcNames)
                    for ii in range(len(spcs)):
                        spc = spcs[ii]
                        components = spc[1]
                        values = spc[2]
                        nids = spc[3]
                        spcCount += 1
                        sid = spcCount
                        if all(v == 0 for v in values):
                            model.add_spc1(sid, "".join(map(str, components)), nids)
                        else:
                            model.add_spcd(sid, nids, list(map(str, components)), values)
                        subcases[i + 1].add("SPC", sid, [], 'STRESS-type')

                    if stepType == 1:  # 静态分析
                        # 输出力
                        loadNames = step.GetLoads()
                        loads = pyhObj.GetObjectData(loadNames)
                        loadids = []
                        for ii in range(len(loads)):
                            loadType = step.GetLoadType(loadNames[ii])
                            sids = self.GetLoadFunc(loadType)(model, loads[ii], loadCount)
                            loadCount += len(sids)
                            loadids.extend(sids)
                        load_comb_id = loadCount + 1
                        loadCount += 1
                        model.add_load(load_comb_id, 1.0, [1.0] * len(loadids), loadids)
                        subcases[i + 1].add("LOAD", load_comb_id, [], 'STRESS-type')

                    #输出场变量
                    outputNames = step.GetOutputs()
                    outputs = pyhObj.GetObjectData(outputNames)
                    for ii in range(len(spcs)):
                        output = outputs[ii]
                        outputType = output[1]
                        nodeVars = output[2]
                        elemVars = output[3]
                        opts = output[4]
                        nodeOpts = output[5]
                        elemOpts = output[6]
                        vars = nodeVars + elemVars
                        for var in vars:
                            self.GetOutputFunc(var)(subcases[i + 1])
                
        #导出bdf文件
        filename = self.filename
        model.write_bdf(filename)
