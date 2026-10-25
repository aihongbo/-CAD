# GMDE-CppSDK

## General Multi-kernel Development Engine - C++ Software Development Kit

## 一、项目简介

欢迎使用炎核通用多内核开发引擎（General Multi-kernel Development Engine）——GMDE-CppSDK。粤港澳大湾区（广东）国创中心（以下简称 "国创中心"）拥有 GMDE-CppSDK 完全自主可控的产权。

GMDE-CppSDK 是一款为 CAD/CAE 领域打造的高效开发工具，集成了丰富的功能模块。其中，CppCAEPre 应用软件开源源码作为 GMDE-CppSDK 的重要组成部分，采用木兰宽松许可证开源，方便开发者自由使用、修改和分发；而 SDK 开发工具包则提供个人免费非商业许可（商业许可证需向国创中心单独申请），为个人非商业场景下的开发工作提供支持。

## 二、功能特点

- **多内核支持**：提供对多种几何内核、约束内核和网格内核的集成支持
- **CAD/CAE 专用**：针对计算机辅助设计与工程领域优化
- **Qt 集成**：基于 Qt 框架开发，支持跨平台应用
- **Python 绑定**：提供 Python 接口，支持通过脚本自动化操作和自定义功能开发
- **插件系统**：支持动态插件加载，易于扩展功能
- **完整 SDK**：提供丰富的 API 和开发工具

## 三、系统要求与依赖环境

### 3.1 硬件要求
- 操作系统：最低支持的操作系统：Windows 10(64-bit)
- 处理器：Intel Core i5 或 AMD Ryzen 5 以上
- 内存：8GB 以上
- 存储空间：至少 5GB 可用磁盘空间
- 显卡：支持 OpenGL 4.5 以上的独立显卡（推荐）

### 3.2 软件依赖
1. **编程语言环境**
   - C++ 20 及以上
   - Python 3.8 及以上版本
2. **开发框架与库**
   - Qt 5.14 及以上 或 Qt 6.2 及以上
   - CMake 3.16 及以上
4. **构建工具**
   - Visual Studio 2019 及以上（推荐 2022）

## 四、SDK获取与安装

### 3.1 SDK获取
从国创中心提供的炎核官网下载GMDE-CppSDK安装程序。

### 3.2 SDK安装
下载完安装程序后，双击启动向导，同意许可协议后，选择安装路径，点击安装，最后点 "完成" 即可。
默认安装路径为`%LOCALAPPDATA%\Programs\GMDECpp`

### 3.3 SDK编译

使用CMake图形界面工具(CMake GUI)来生成Visual Studio工程文件。具体步骤如下：

1. **设置源代码和构建目录**
   - **Where is the source code**: 点击"Browse Source..."按钮，选择GMDE-CppSDK的根目录
     （例如：`D:\GMDE-CppSDK\CppCAEPre`）
   - **Where to build the binaries**: 点击"Browse Build..."按钮，选择一个构建目录（建议在源代码目录外创建一个`build`文件夹，例如：`D:\GMDE-CppSDK\build`）
3. **配置项目**
   - 点击"Configure"按钮
   - 在弹出的对话框中，选择你安装的Visual Studio版本（例如："Visual Studio 17 2022"）
   - 选择平台（选择"x64"）
   - 点击"Finish"按钮开始配置
4. **设置Qt路径**
   - 配置完成后，在变量列表中找到`CMAKE_PREFIX_PATH`或`QT_DIR`
   - 双击该变量，输入Qt的安装路径（例如：`C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5`）
   - 确保路径正确指向Qt的安装目录
5. **设置构建类型**
   - 找到`NCTI_BUILD_TYPE`变量
   - 设置为`RelWithDebInfo`（保持默认即可）
6. **再次配置**
   - 点击"Configure"按钮，确保所有变量都已正确设置
   - 解决可能出现的配置错误（通常是缺少依赖项）
7. **生成工程文件**
   - 当配置完成且没有错误时，点击"Generate"按钮
   - CMake将在指定的构建目录中生成Visual Studio工程文件（`.sln`文件）
8. **打开并编译工程**
   - 点击"Open Project"按钮，CMake将自动启动Visual Studio并打开生成的工程
   - 在Visual Studio中，设置解决方案配置为**`RelWithDebInfo`**（与`NCTI_BUILD_TYPE`保持一致）
   - 右键点击"ALL_BUILD"项目，选择"生成"开始编译 
   
### 3.4 下载授权凭证
软件运行依赖授权凭证，打开炎核官网的申请许可页面，输入机器码（由机器码工具生成），点击生成许可证，将生成的许可证（`gmde.lic`）放置到软件运行所在目录。


## 五、使用指南

### 5.1 快速开始
```cpp
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QString appPath = QCoreApplication::applicationFilePath();
    QByteArray ba = appPath.toUtf8();
   
    // Python解释器初始化
    if (!NCTI::NctiMainPubFun::NctiPythonInit(ba.constData())) {
        qWarning() << "NctiPythonInit Failed";
        return -1;
    }

    //平台资源初始化
    NCTI::NctiQTPubFun::NctiWindowPlatformInit(ba.constData());

    NCTI::MainWindow mainWindow;
    mainWindow.show();
    app.exec();

    //平台资源释放
    NCTI::NctiMainPubFun::NctiWindowPlatformRelease();
    return 0;
}
```

### 5.2 项目结构

#### 5.2.1 CppCAEPre 结构说明
- **3rdparty**: 第三方库

- **cmake**: CMake自定义宏函数

- **doc**: 包含项目文档，协议说明等

- **NctiCAEPre**: 主应用程序目录，包含核心功能实现
  
  - **Code**: 项目源码文件
  - **Inc**: 项目头文件
  
- **ncti_*_demo**: 各种功能演示程序，展示SDK的不同功能和用法。
  - `ncti_cmd_demo`：命令行演示
  
  - `ncti_plugin_demo`：插件系统演示
  
  - `ncti_python_demo`：Python 绑定演示
  
  - `ncti_occ_plugin_demo`：OpenCASCADE 插件演示
  
- **CMakeLists.txt**：项目构建文件


#### 5.2.2 SDK 结构说明
- **bin**: 包含 SDK 的 dll 文件，配置等文件（程序运行依赖该目录中的dll，编译完成后，拷贝该目录的所有文件到应用程序所在目录）
- **inc**: 包含 SDK 的头文件，按功能模块组织
- **lib**: 包含 SDK 的 库文件

## 六、许可信息

- **CppCAEPre 应用相关源码**：木兰MulanPSL v2（开源许可证）
- **SDK 开发工具包**：个人免费非商业许可（商业许可证需向国创中心单独申请）

详细许可条款请参阅《炎核通用多内核开发引擎 GMDE-CppSDK 软件许可协议》文件。

## 七、贡献指南

我们欢迎并鼓励社区贡献！如果您有兴趣为 GMDE-CppSDK 贡献代码、文档或提出建议，请遵循以下步骤：

1. **提交 Issue**：通过炎核官网或 GitHub 提交问题或功能建议
2. **克隆代码**：获取最新代码并创建自己的分支
3. **开发改进**：实现功能或修复问题
4. **提交 PR**：提交 pull request，描述您的更改
5. **代码审核**：等待项目维护者审核您的代码
6. **合并代码**：审核通过后，您的更改将被合并到主分支

## 八、第三方组件声明

本项目（包括 CppCAEPre 和 GMDE-SDK）的开发与运行依赖部分第三方库及组件，相关第三方库的名称、版本、许可证类型、来源链接及在本项目中的使用位置等信息，已在《THIRD-PARTY-NOTICES》（第三方声明）文件中详细列明。

该文件与本项目源码 / 安装包一同提供，使用本项目时，除遵守本项目的许可条款外，请同时严格遵守《THIRD-PARTY-NOTICES》中所列全部第三方库的许可要求。

## 九、支持与反馈

如果您在使用 GMDE-CppSDK 过程中遇到任何问题，如安装失败、功能异常、授权问题等，或有相关的功能建议、优化意见，可通过炎核官方网站联系我们进行反馈。

