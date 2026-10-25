import sys
import os
import ctypes
import importlib
import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog

HWND = -1

# 初始化炎核开发引擎
def init_NCTI_Config(dll_path):
    try:
       # 加载炎核开发引擎的建模内核、渲染引擎、Python接口
        sys.path.insert(0, dll_path)
        os.add_dll_directory(dll_path + '/OCC')  # occ_path
        ctypes.CDLL(dll_path + "/ncti_command.dll")
        ctypes.CDLL(dll_path + "/ncti_occ_plugin.dll")
        ctypes.CDLL(dll_path + "/ncti_render_vulkan.dll")
        NCTI = importlib.import_module("ncti_python")
        if 1 != NCTI.Init(dll_path):
            return None
        return NCTI
    except:
        print("System path error or loading dll failure!")
        return None


# 创建和关闭文档
def on_create_doc(NCTI, doc, label):
    if -1 != HWND:
        doc.New("OCC")  # 新建的文档默认调用OCC建模内核
        view = NCTI.View(doc.ID)
        view.CreateWindow(HWND)
        width = label.winfo_width()
        height = label.winfo_height()
        view.SetWindowVis(True,doc.ID)
        view.SetGeometry(0,0, width,height)
        doc.Update()
        doc.Zoom()
def on_close_doc(NCTI, doc):
    doc.Close()


# 导入模型和看图场景
def on_import_file(NCTI, doc):
    if -1 == doc.ID:
        print('请先新建文档！')
        return None
    # 弹出文件选择对话框，选择单个文件
    file_path = filedialog.askopenfilename(
        title="选取导入模型",
        filetypes=[("Stp Files", "*.stp"), ("Step Files", "*.step"), ("IGS Files", "*.igs")]
    )
    if file_path:
        doc.RunCommand("cmd_ncti_import_file", file_path)
        doc.Zoom()
def on_zoom(NCTI, doc):
    doc.Zoom()
    view = NCTI.View(doc.ID)
    view.SetViewMode(0)
def on_clean(NCTI, doc):
    doc.Clear()
    doc.ResetCaseResult()


def CreateMainWindow(root, NCTI, doc):
    # 配置主界面的标题、尺寸等基本信息
    root.title("炎核看图工具V1.0")
    root.geometry("1200x900")
    label = tk.Label(root, text="", width=1200, height=800, bg="lightblue", anchor="center")

    # 创建一个位于顶部的框架，用于放置按钮
    button_frame = tk.Frame(root)
    button_frame.pack(side=tk.TOP, pady=20)
    # 创建按钮
    button0 = tk.Button(button_frame, text="创建文档", command=lambda: on_create_doc(NCTI, doc, label))
    button0.pack(side=tk.LEFT, padx=0)
    button1 = tk.Button(button_frame, text="关闭文档", command=lambda: on_close_doc(NCTI, doc))
    button1.pack(side=tk.LEFT, padx=0)

    button2 = tk.Button(button_frame, text="导入模型", command=lambda: on_import_file(NCTI, doc))
    button2.pack(side=tk.LEFT, padx=(50,0))
    button3 = tk.Button(button_frame, text="复位模型", command=lambda: on_zoom(NCTI, doc))
    button3.pack(side=tk.LEFT, padx=0)
    button4 = tk.Button(button_frame, text="清空文档", command=lambda: on_clean(NCTI, doc))
    button4.pack(side=tk.LEFT, padx=0)

    # 创建标签
    label.place(x=0, y=20)  # 标签位置：x=100, y=100，表示在窗口中的 (100, 100) 位置
    label.pack(side=tk.TOP, pady=5)  # 标签占据剩余空间，居中显示
    global HWND
    HWND = label.winfo_id()
    return root


if __name__ == '__main__':
    # 1，确认炎核开发引擎的安装路径，请按需配置实际路径
    # 以下是当前用户默认设置下安装的路径，一般情况下是可用的：
    dll_path = os.path.join(os.path.expanduser('~'), 'AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo')
    # 以下是admin用户默认设置下安装的参考路径，请根据实际用户名确认该路径有效：
    # dll_path = 'C:/Users/Admin/AppData/Local/Programs/YHCppSDK-Community/SDK/bin/RelWithDebInfo'
    # 如果自行安装至如下所示的其它目录，请自行修改，并将目录分隔符号反斜杠"\"修改为正斜杠"/"：
    # dll_path = 'C:/Program Files (x86)/YHCppSDK-Community/SDK/bin/RelWithDebInfo'

    if not os.path.exists(dll_path):
        messagebox.showerror("安装路径检索错误",
                             "操作失败！请检查炎核开发引擎是否已正确安装、其安装路径与dll_path声明是否匹配。", icon='error')
        sys.exit(1)

    # 2，根据指定路径加载炎核开发引擎
    NCTI = init_NCTI_Config(dll_path)
    if None == NCTI:
        messagebox.showerror("初始化炎核开发引擎错误", "操作失败！请检查是否正确配置授权。", icon='error')
        sys.exit(1)
    doc = NCTI.Document()

    # 3，准备工作完成，启动界面
    root = CreateMainWindow(tk.Tk(), NCTI, doc)
    root.mainloop()