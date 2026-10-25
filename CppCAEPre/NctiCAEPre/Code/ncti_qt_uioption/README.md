# ncti_uioption

> 界面配置器, 通过JSON文件来配置界面

## 界面结构
### 1. 标题栏 UITitleBar
    1.1 图标 UILogo
    1.2 标题 UITitle
    1.3 浏览器栏 UIBrowserBar
      1.3.1 浏览器标签页 UIBrowserTab
      1.3.2 浏览器按钮  UIBrowserBtn
    1.4 系统按钮栏 UISystemBtnBar
      1.4.1 设置按钮 UISystemBtnSetting
      1.4.2 最小化按钮 UISystemBtnMin
      1.4.3 最大化按钮 UISystemBtnMax
      1.4.4 关闭按钮 UISystemBtnClose
### 2. 工具栏
    2.1 快速访问栏 UIQuickAccessBar
    2.2 菜单栏 UIMenuBar
    2.3 标签栏 UITabBar
### 3. 功能面板 UIPannel
    3.1 UIAction
    3.2 UIGroup
    3.3 UIActionGroup
### 4. 内容主体 UIMainArea
    4.1 UILeftSideBar
    4.2 UIMainArea
    4.3 UIRightSideBar
### 5. 状态栏 UIStatusBar

```sh
UIOptionTree结构图
├── UICategory
│   ├── UIPannel
│   │   ├── UIAction
│   │   ├── UIAction
│   │   │    └── ...
│   │   ├── UIGroup
│   │   │   ├── UIGroupItem
│   │   │   ├── UIGroupItem
│   │   │   └── ...
│   │   ├── UIActionGroup
│   │       ├── UIActionGroupItem
│   │       ├── UIActionGroupItem
│   │       └── ...
│   └── ...
└── ...
```
说明：
- 标签栏UITabBar由一个或多个UICategory组成。
- 每个UICategory由一个或多个UIPannel组成。
- 每个UIPannel由一个或多个UIAction组成，或一个或多个UIGroup组成，或一个或多个UIActionGroup组成。
- 每个UIGroup由一个或多个UIGroupItem组成。
- 每个UIActionGroup由一个或多个UIActionGroupItem组成。

## 环境配置

### Qt 版本
Qt5.14.2 msvc2017_64

### C++ 标准
C++20

工程配置： `64位 | Unicode | RelWithDebInfo`

## 开发注意事项

编译默认输出目录设置为`~/NctiCAEPreAPPAndLib/Windows/RelWithDebInfo/`

## 设计思路

> 界面配置器的核心设计理念是实现**界面配置**与**界面功能**的解耦，通过 JSON 格式的配置文件统一管理界面数据。

1. 通过 UIOptionDialog 调整界面参数（如窗口标题、图标、控件属性、响应函数等），配置完成后可将修改内容写入界面配置文件。
2. 当界面配置文件发生变化时，自动重新加载配置文件，并根据新的配置信息更新界面元素，实现界面的动态更新。
3. 版本管理，记录配置文件的版本，实现升级配置操作。

### 界面配置文件

界面配置文件是一个JSON文件，包含以下字段：

- `window`: 窗口配置，包含以下字段：
    - `title`: 窗口标题
    - `logo`: 窗口logo
- ...

## TODOList

### 系统配置
1. 搜索功能
1.1 通过关键字过滤**系统树**中的节点，仅显示匹配的节点。
2. 拖拽功能
2.1 支持节点的拖拽操作，包括选中的节点的复制到**用户树**节点中。
3. 快捷键功能
3.1 支持自定义快捷键，用于快速执行特定的操作，`Ctrl+C`, `Ctrl+V`

### 自定义配置
1. 功能优化
1.1 增加`getMaxIndex()`获取当前节点列表中的最大索引值。 ✔️
1.2 增加UI界面热更新。✔️

2. 增加拖拽功能
2.1 支持节点的拖拽操作，将选中的节点的复制或移动到**用户树**节点中。✔️
2.2 同一父节点下的节点，支持拖拽排序。✔️
2.3 不同父节点下的节点，支持拖拽移动和复制。✔️

3. 增加节点的属性编辑功能
3.1 支持对节点的名称、图标、槽函数等进行编辑。✔️
3.2 增加创建Pannel的UIAction子节点功能。✔️
3.3 增加创建Pannel的UIGroup子节点功能。
3.4 增加创建Pannel的UIActionGroup子节点功能。

7. 将UI数据存储到数据库中
7.1 如果是本地的图标，则需要将图标转为base64编码或以二进制保存在数据库中。

## 进一步改进

### 生成UI头文件
```sh
uic.exe D:\NctiCADTest\Code\ncti_qt_pubfun\Source\UI\AddUIActionContent.ui -o 
D:\NctiCADTest\Inc\ncti_qt_pubfun\Source\UI\ui_AddUIActionContent.h
```
