import pyNastran
from pyNastran.bdf.bdf import BDF, CaseControlDeck

doc.ResetCaseResult()
sel = NCTI.SelectionManager(doc)
outputBDF(NCTI,doc,"D:\\FreqRespon.bdf",sel.ObjectNames[0],16)

def outputBDF(NCTI,doc,bdfFileName,meshName,bit_Len = 8):
    model = BDF(debug=False)
    model.punch = False
    model.sol = 111 #频响模态法
    model.echo = None
    
    #获取网格与节点
    mesh = NCTI.GridMesh(doc,meshName)
    add_node(NCTI,doc,model,meshName)
    
    #获取集合
    pyObj = NCTI.Object(doc)
    setVals = pyObj.GetObjectData(doc.GetSets())
    element_index_sets = []
    for idx,val in enumerate(setVals):
        element_indexs = val[2]['element_index']
        element_index_sets += element_indexs
    #添加非集合的单元，去除集合中的单元，集合中的单元会在后续单独添加到BDF中
    elementNumbers = mesh.GetAllElements()
    B_set = set(element_index_sets)
    elementNumbers = [item for item in elementNumbers if item not in B_set]
    #添加占位材料、占位壳、占位实体属性
    if len(elementNumbers) > 0:
        for eleNum in elementNumbers:
            element = NCTI.MeshElement(eleNum)
            nodes = element.AllNode()
            elemType = element.ElementType()
            model.add_mat1(mid=999, E=1.0, G=None, nu=0.3)
            if elemType > 7:
                model.add_psolid(pid=999,midl=999)
            elif elemType > 2 and elemType < 8:
                model.add_pshell(pid=999, mid1=999, t=1.0)
        add_element(NCTI,doc, model, elementNumbers, 999)

    spcMap = SetModelSPCData(NCTI,doc,model)
    matMap = SetModelMaterialData(NCTI,doc,model)
    SetModelSets(NCTI,doc,model)
    SetSection(NCTI,doc,model,matMap)
    focMaps = SetForce(NCTI,doc,model)
    #模态分析设置
    #SetModalStepAndField(NCTI,doc,model,meshName,spcMap)
    #频响分析设置
    SetFeqResAnaly(NCTI,doc,model,spcMap,focMaps)
    model.write_bdf(bdfFileName, size=bit_Len)
    print("BDF 写入完成")
    
def add_node(NCTI, doc, model,meshName):
    mesh = NCTI.GridMesh(doc,meshName)
    nodeNumbers = mesh.GetAllVertexs()
    positions = mesh.GetVertexPosition(nodeNumbers)
    for i,val in enumerate(nodeNumbers):
        pt = positions[i]
        model.add_grid(val,[pt.X,pt.Y,pt.Z])
        
def add_element(NCTI, doc, model, elementNumbers, ppid):
    for eleNum in elementNumbers:
        element = NCTI.MeshElement(eleNum)
        nodes = element.AllNode()
        elemType = element.ElementType()
        if elemType == 3:
            model.add_ctria3(eid=eleNum, pid=ppid, nids=nodes)
        if elemType == 5:
            model.add_cquad4(eid=eleNum, pid=ppid, nids=nodes)       
        if elemType == 8:
            model.add_ctetra(eid=eleNum, pid=ppid, nids=nodes)
        if elemType == 10:
            model.add_chexa(eid=eleNum, pid=ppid, nids=nodes)
        if elemType == 13:
            model.add_cpenta(eid=eleNum, pid=ppid, nids=nodes)
        if elemType == 16:
            model.add_cpyram(eid=eleNum, pid=ppid, nids=nodes)


#固定约束只对节点进行约束
def SetModelSPCData(NCTI,doc,model):
    spcNames = doc.GetSPCs()
    pyObj = NCTI.Object(doc)
    conid=1
    sid = 101
    spcMap = {} #{"spcName": conid}
    spcTuple = pyObj.GetObjectData(spcNames)
    for idx,sub_tuple in enumerate(spcTuple):
        if sub_tuple[0] == 'Constraint':
            xyz = sub_tuple[1]
            vals = sub_tuple[2]
            numbers = sub_tuple[3]
            strxyz = mask_join(xyz,vals)
            model.add_spc1(conid=conid, components=strxyz, nodes=numbers)
            #非0则为位移约束
            # for ii,val in enumerate(vals):
                # if int(val) == 0:
                    # continue
                # for node in numbers:
                    # model.add_spcd(sid=sid, nodes=node, components=str(ii+1), enforced=int(val))
            # sid += 1
            spcMap[spcNames[idx]] = conid
            conid += 1
        elif sub_tuple[0] == 'Tie':
            continue
    return spcMap
    
def mask_join(arr1, arr2):
    return ''.join(str(a) for a, b in zip(arr1, arr2) if b == 0.0)
    
def SetModelMaterialData(NCTI,doc,model):
    matNames = doc.GetMaterials()
    pyObj = NCTI.Object(doc)
    matTuples = pyObj.GetObjectData(matNames)
    matMap = {} #{"matName": mid}
    mid = 1
    for idx,matTuple in enumerate(matTuples):
        ElasticModulus = 0.0
        ShearModulus = 0.0
        PoissonsRatio = 0.0
        Density = 0.0
        if  matTuple[1] != None:
            ElasticModulus = matTuple[1][1]
        if  matTuple[2] != None:
            ShearModulus = matTuple[2][1]
        if  matTuple[3] != None:
            PoissonsRatio = matTuple[3][1]
        if  matTuple[4] != None:
            Density = matTuple[4][1]
        print(matTuple)
        model.add_mat1(mid=mid, E=ElasticModulus, G=ShearModulus, nu=PoissonsRatio, rho=Density)
        matMap[matNames[idx]] = mid
        mid += 1
    return matMap

def SetModelSets(NCTI,doc,model):
    setNames = doc.GetSets()
    pyObj = NCTI.Object(doc)
    setTuples = pyObj.GetObjectData(setNames)
    nd_id = 101
    em_id = 201
    for idx,setTuple in enumerate(setTuples):
        setName = setTuple[0]
        type = setTuple[1]['set_type']
        element_indexs = setTuple[2]['element_index']
        if type == 1:
            model.add_set1(sid=nd_id, ids=element_indexs)
            nd_id += 1
        elif type == 2:
            model.add_set1(sid=em_id, ids=element_indexs)
            em_id += 1
    
def SetSection(NCTI,doc,model,matMap):
    pyObj = NCTI.Object(doc)
    #doc.GetSections() 是5.28新增的接口
    sections = pyObj.GetObjectData(doc.GetSections())
    pshid = 1001
    psoid = 2001
    setNames = doc.GetSets()
    indexss = []
    for setName in setNames:
        val = pyObj.GetObjectData(setName)
        element_indexs = val[0][2]['element_index']
        indexss.append(element_indexs)  

    for section in sections:
        setName = section[1]['set']
        matName = section[2]['material']
        sectionType = section[3]['section_type']
        setNameIdx = setNames.index(setName)
        matId = matMap.get(matName, 1)
        #处理SHELL或SOLID
        if sectionType.strip().upper() == "SHELL":
            thickness = section[4]['thickness']
            model.add_pshell(pid=pshid, mid1=matId, t=thickness)
            add_element(NCTI,doc, model, indexss[setNameIdx], pshid)
            pshid += 1
        elif sectionType.strip().upper() == "SOLID":
            model.add_psolid(pid=psoid, mid=matId)
            add_element(NCTI,doc, model, indexss[setNameIdx], psoid)
            psoid += 1
            
def SetForce(NCTI,doc,model):
    pyObj = NCTI.Object(doc)
    loadNames = doc.GetLoads()
    loads = pyObj.GetObjectData(loadNames)
    focMaps = {} #{"forceName":forceID}
    sid = 101
    for idx,val in enumerate(loads):
        if val[0] == "Forces":
            vec = val[1]
            fval = val[2]
            nodes = val[3]
            for node in nodes:
                model.add_force(sid=sid, node=node, mag=fval, xyz=[vec.X,vec.Y,vec.Z],cid=0,comment=" Modal Forces of Load Set : force")
            focMaps[loadNames[idx]] = sid
            
        if val[0] == "Pressure":
            magnitude = val[1]
            elementIds = val[2]
            model.add_pload4(sid=sid,eids=elementIds,pressures=magnitude)
            focMaps[loadNames[idx]] = sid
        sid += 1
    return focMaps


def SetFeqResAnaly(NCTI,doc,model,spcMap,focMaps):
    pyObj = NCTI.Object(doc)
    outputs = pyObj.GetObjectData(doc.GetOutputs())
    steps = pyObj.GetObjectData(doc.GetSteps())
    spc_ids = []
    #mat_ids = []
    foc_ids = []
    if len(steps) == 1:
        #非频响分析，退出
        if steps[0][0] != "frequency_respon_step":
            return False
        #2026.5.28：steps[0][1]['SPC']值由字符串改为列表
        spcNames = steps[0][1]['SPC']
        opName = steps[0][1]["output"]
        loadName = steps[0][1]["load"]
        dload = steps[0][1]["dload"]
        freq = steps[0][1]["freq"]
        bHasEigrl = False
        if "eigrl" in steps[0][1]:
            bHasEigrl = True
            eigrl = steps[0][1]["eigrl"]
        for key,val in spcMap.items():
            if key in spcNames:
                spc_ids.append(val)
        for key,val in focMaps.items():
            if key in loadName:
                foc_ids.append(val)
              
    model.add_param('POST', 1)
    model.add_param('PRTMAXIM', 'YES')
    #添加频率
    fs_id = 1
    freq_id = fs_id
    model.add_freq1(sid=freq_id,f1=freq["f1"],df=freq["df"],ndf=freq["ndf"])
    fs_id += 1
    #Eigrl
    if bHasEigrl == True:
        eigrlId = fs_id
        fs_id += 1
        model.add_eigrl(sid=eigrlId,nd=eigrl["nd"],msglvl=eigrl["msglvl"],comment=eigrl["comment"])
    #定义约束集合ID
    spcSetId = fs_id
    model.add_spcadd(spcSetId,spc_ids)
    fs_id += 1
    
    #添加Table
    tablec_ids = []
    tabled_ids = []
    for rload in dload["rloads"]:
        tablec = rload["tc"]
        tabled = rload["td"]
        if len(tablec) > 0:
            xc_list = tablec[::2]   # 索引 0, 2, 4
            yc_list = tablec[1::2]  # 索引 1, 3, 5
            model.add_tabled1(tid=fs_id,x=xc_list,y=yc_list)
            tablec_ids.append(fs_id)
            fs_id += 1
        else:
            tablec_ids.append(0)
            
        if len(tabled) > 0:  
            xd_list = tabled[::2]   # 索引 0, 2, 4
            yd_list = tabled[1::2]  # 索引 1, 3, 5
            model.add_tabled1(tid=fs_id,x=xd_list,y=yd_list)
            tabled_ids.append(fs_id)
            fs_id += 1
        else:
            tabled_ids.append(0)
    
    #频率依赖荷载
    #sid：load id
    #excite_id：node id where the load is applied
    #tc : TABLEDi id that defines C(f) for all degrees of freedom in EXCITEID entry
    excite_ids = []
    rload_ids = []
    for idx, rload in enumerate(dload["rloads"]):
        rload1_id = fs_id
        fs_id += 1
        tablec = rload["tc"]
        tabled = rload["td"]
        delay = rload["delay"]
        dphase = rload["dphase"]
        ex_id = fs_id
        model.add_rload1(sid=rload1_id,excite_id=ex_id,delay=delay,dphase=dphase,tc=tablec_ids[idx],td=tabled_ids[idx],Type='LOAD')
        excite_ids.append(ex_id)
        rload_ids.append(rload1_id)
        fs_id += 1
    
    lid = fs_id
    fs_id += 1
    lseq_id = fs_id
    fs_id += 1
    #sfs = [1.0 for _ in range(len(foc_ids))]
    #model.add_load(sid=lid,scale=1.0,scale_factors=sfs,load_ids=foc_ids)
    for ex_id in excite_ids:
        #sid：loadset id; LOADSET points to this
        #excite_id：set id assigned to this static load vector
        #lid：load set id of a set of static load entries;
        for forid in foc_ids:
            model.add_lseq(sid=lseq_id,excite_id=ex_id,lid=forid)
        #model.add_lseq(sid=lseq_id,excite_id=ex_id,lid=lid)
    #load_ids对应rload1的sid
    dload_id = fs_id
    fs_id += 1
    model.add_dload(sid=dload_id, scale=dload["scale"], scale_factors=dload["scale_factors"], load_ids=rload_ids)

    #add SUBCASE
    cc = []
    cc.append("ECHO = None")
    cc.append(f"LOADSET = {lseq_id}")
    cc.append("SUBCASE 1")
    if bHasEigrl == True:
        cc.append(f"  METHOD = {eigrlId}")
    outputNames = doc.GetOutputs()
    for idx,op in enumerate(outputNames):
        if op in opName:
            output = outputs[idx]
            #场变量输出
            if output[1] != 1:
                continue
            if 'U' in output[2]:
                cc.append("  DISPLACEMENT(SORT1,REAL)=ALL")
            if 'V' in output[2]:
                cc.append("  VELOCITY(SORT1,REAL)=ALL")
            if 'A' in output[2]:
                cc.append("  ACCELERATION(SORT1,REAL)=ALL")
            if 'RF' in output[2]:
                cc.append("  SPCFORCES(SORT1,REAL)=ALL")
            if "S" in output[3]:
                cc.append("  STRESS(SORT1,REAL)=ALL")
            if "E" in output[3]:
                cc.append("  STRAIN(SORT1,REAL)=ALL")
            if "F" in output[3]:
                cc.append("  FORCE(SORT1,REAL)=ALL")
    cc.append(f"  DLOAD = {dload_id}")
    cc.append(f"  SPC = {spcSetId}")
    cc.append(f"  FREQUENCY = {freq_id}")
    cc.append(f"  SUBTITLE = LOADSTEP1.SC1")
    model.case_control_deck = CaseControlDeck(cc)

    
    