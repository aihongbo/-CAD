#pragma once

#include "ncti_dcl_base.h"
#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>

#define ParamsColor(r,g,b) ((r<<16)+(g<<8)+(b))

namespace NCTI
{
    class NctiDebug;
    /**
    * @brief 渲染器配置类
    */
    struct DECL_NCTI_BASE RendererConfig
    {
    public:
        ~RendererConfig();

        /**
        * @brief 对象显示模式数组
        * @details 包含三个布尔值，分别控制面、边、顶点的显示状态
        */
        std::vector<bool> ObjectDisplayMode = { true, true, false };
        bool OpenRenderDisplayTime = false;  ///< 是否显示渲染时间
        bool RenderPreHighlight = true;  ///< 是否实时高亮
        bool RenderBoxSelctAll = false;  ///< 是否框选所有
        bool OperatingAxis = false;  ///< 是否显示操作轴
        bool OpenDebugInfo = true;  ///< 是否开启调试信息
        bool OpenCalTime = false;//时间统计
        int DebugLevel = 0;//调试级别LogLevel,仅输出大于等于该级别的日志
        int GpuIndex = -1;//gpu索引

        /**
         * @brief DebugMod>=1时，获取文件调试对象
         */
        NctiDebug* GetFileDebug()const;

        /**
         * @brief setDebugMod
         * @param[in] i_mod 0:输出控制台,1:输出控制台和文件,2:输出文件
         */
        void setDebugMod(int i_mod);

        /**
         * @brief 获取调试模式
         * @return 调试模式
         */
        int getDebugMod() const;

    private:
        int DebugMod = 0;
        NctiDebug* m_file_debug{nullptr};
    };

    /**
    * @brief 模型配置项
    * @details 包含颜色设置等
    */
    struct DECL_NCTI_BASE ModelConfig
    {
        bool ShowBackColor = true;                   ///< 是否显示反面
        bool ShowContour = true;                     ///< 是否显示轮廓
        int LineType{ 0 };                           ///< 线型
        double LineWidth = 1.0;                      ///< 线宽
        int BackColor{ 0x919eba };          ///< 背景颜色
        int FaceColor{ 0x919eba };          ///< 面颜色
        int EdgeColor{ 0x000000 };          ///< 边颜色
        int VertexColor{ 0xf8cb16 };        ///< 顶点颜色
        int HighlightColor{ 0xf5800f };     ///< 高亮颜色
        int LineSegmentColor{ 0xffffff };   ///< 线段颜色
        int DimensionLineColor{ 0x1eb341 }; ///< 尺寸线颜色
        int GridLineColor{ 0x4d5d80 };      ///< 网格线颜色
        int BackgroundColor0{ 0x4e4e4e};      ///< 渐变背景左上角
        int BackgroundColor1{ 0xd3d3d3 };      ///< 渐变背景右下角
    };

    /**
    * @brief 环境配置项
    * @details 包含主题、语言、设置等
    */
    struct DECL_NCTI_BASE EnvConfig
    {
        std::string ThemeColor{ "light" };           ///< 主题颜色
        std::string Language{ "chinese" };           ///< 语言
        std::string AutoSaveFolder; ///< 自动保存文件夹
        int AutoSaveTime = 300;     ///< 自动保存时间（秒），默认为300秒
        bool AutoSaveValid = true;  ///< 是否启用自动保存
        bool Console = true;        ///< 是否显示控制台
        bool ScriptEditor = false;  ///< 是否使用脚本编辑器
        std::string FunctionPath; ///< Python函数路径
        std::string PythonPath;   ///< Python路径
        std::vector<std::string> ImportPath;//导入路径数组
    };

    /**
    * @brief 插件配置项
    * @details 包含插件相关的设置
    */
    struct DECL_NCTI_BASE PluginConfig
    {
        int PluginCount() const;

        bool GetPlugin(int index, std::vector<std::string>& dll, std::string& path) const;
        void AddPlugin(const std::vector<std::string>&dll, const std::string &path = "");

        void AddVulkanPlugin();
        void ClearPlugin();
    private:
        std::map<std::string, std::set<std::string>> LoadDLL;
        std::vector<std::string> LoadDLLPath;
    };

    /**
    * @brief 应用配置类
    */
    struct DECL_NCTI_BASE AppConfig
    {
    public:
        static AppConfig* GetConfig();
        void ResetToDefault();

        ModelConfig Model;       ///< 模型配置
        EnvConfig Environment;   ///< 环境配置
        RendererConfig Renderer; ///< 渲染器配置
        PluginConfig Plugin; ///< 插件配置
    private:
        AppConfig() = default;
    };
};

