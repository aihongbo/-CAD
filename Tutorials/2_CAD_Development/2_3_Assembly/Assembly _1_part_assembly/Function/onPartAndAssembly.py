def pyncti_new_assembly(NCTI,doc,hwnd):
    doc.ResetCaseResult()
    doc.NewAssemble("OCC")
    view = NCTI.View(doc.ID)
    doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
    view.CreateWindow(hwnd)
    view.SetWindowVis(True,doc.ID)
    doc.Zoom()
    return view

def pyncti_new_document(NCTI,doc,hwnd):   
    doc.ResetCaseResult()
    doc.New("OCC")
    view = NCTI.View(doc.ID)
    view.CreateWindow(hwnd)
    view.SetWindowVis(True,doc.ID)
    doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
    doc.Zoom()
    return view

    
def pyncti_add_assembly(NCTI,doc):   
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "添加装配文档","对象名称","assemble", "显示名称", "装配")
    if len(res) > 0:
        doc.AddAssemble(res[0], res[1])
        doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
        doc.Zoom()

def pyncti_add_part(NCTI, doc):
    doc.ResetCaseResult()
    res  = doc.ReturnDialogData(-1, "添加零件文档","文档名称","零件")
    if len(res) > 0:
        doc.AddPart(res[0], "OCC")
        doc.SetCreateGeGeom(1)  # 不生成平台对象（不生成会快）
        doc.Zoom()
