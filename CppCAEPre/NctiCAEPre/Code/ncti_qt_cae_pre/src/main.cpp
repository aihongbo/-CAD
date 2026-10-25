/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#include "mainwindow.h"
#include "SARibbonBar.h"
#include "PreferenceSettings.h"
#include "NctiConfig.h"
#include <QApplication>
#include <QElapsedTimer>
#include <QFontDatabase>
#include <QString>
#include <QByteArray>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#include <winver.h>
#endif

#ifdef NCTI_ENABLE_GRPC_SERVICE
#include <filesystem>
namespace fs = std::filesystem;

#include "utils/Logger.hpp"
#include "utils/String.hpp"
#endif

#include "NctiQTPubFun.h"
#include <NctiPluginsManager.h>
#include <NctiInitializeTool.h>
#include <NctiDebug.h>
#include <NctiString.h>

#include "QBreakpadHandler.h"
#include "argparse/argparse.hpp"
using namespace NCTI;

//重定向qDebug的打印
static void logMsgOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (!AppConfig::GetConfig()->Renderer.OpenDebugInfo)
        return;
    QByteArray localMsg = msg.toLocal8Bit();

    const char* typeStrings[] = {
        "[Debug]",
        "[Warning]",
        "[Critical]",
        "[Fatal]"
    };

    const char* logType = (type >= QtDebugMsg && type <= QtFatalMsg) ?
        typeStrings[type] : "[Debug]";

    fprintf(stdout, "%s |%s (%s[%u],%s)\n",
        localMsg.constData(), logType,
        context.function, context.line, context.file);

    if (type == QtFatalMsg) {
        abort();
    }

#ifndef QT_NO_DEBUG_OUTPUT
    fflush(stdout);
#endif
}

static void addApplicationFonts(QApplication& app)
{
    int font_id = QFontDatabase::addApplicationFont(":/Fonts/HarmonyOS_SansSC_Regular.ttf");
    if (font_id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(font_id);
        if (!fontFamilies.empty()) {
            QFont font(fontFamilies.at(0), 12);
            app.setFont(font);
        }
    }
}

static void setApplicationBaseInfo(QApplication& a)
{
    a.setOrganizationName("YanHe");
    a.setApplicationName("GMDE");
    a.setApplicationDisplayName(QStringLiteral("CAE前处理应用平台"));
}

static void outputErrorAsJson(const NCTI::ErrorInfo& error)
{
    std::cout << "{"
        << " \"code\": \"" << error.code << "\","
        << " \"message\": \"" << error.message << "\","
        << " \"detail\": \"" << error.detail << "\""
        << "}"
        << std::endl;
}

static void handleSubProcessArguments(argparse::ArgumentParser& subProc, NCTI::AppArguments& args)
{
    NctiPrintf("sub process running");
    std::string sServer  = subProc.get<std::string>("--server");
    std::string sType    = subProc.get<std::string>("--type");
    std::string sFile    = subProc.get<std::string>("--file");
    args.server          = sServer.c_str();
    args.type            = sType.c_str();
    args.file            = QString::fromLocal8Bit(sFile.c_str()).toUtf8();//将GBK转为Utf-8编码;
    args.geometry        = subProc.get<int>("--geometry");
    args.constraint      = subProc.get<int>("--constraint");
    args.mesh            = subProc.get<int>("--mesh");
    args.titlebarVisible = sServer.empty();
}

static int handleMainProcessArguments(argparse::ArgumentParser& program, NCTI::AppArguments& args)
{
    std::string sFile = program.get<std::string>("--file");
    if (!sFile.empty()) {
        args.file = QString::fromLocal8Bit(sFile.c_str()).toUtf8();
    }
    std::string sPyFile = program.get<std::string>("--pyfile");
    if (!sPyFile.empty()) {
        args.pyFile = QString::fromLocal8Bit(sPyFile.c_str()).toUtf8();
        NctiPrintf("run py script file: %s", sPyFile.c_str());
        args.geometry   = program.get<int>("--geometry");
        args.constraint = program.get<int>("--constraint");
        args.mesh       = program.get<int>("--mesh");
    }
#ifdef NCTI_ENABLE_GRPC_SERVICE
    // 检查gRPC端口是否有服务在运行
    args.port = program.get<int>("--port");
    if (args.port > 0) {
        auto mClient = std::make_unique<CAEPreServiceClient>();

        std::string address = "localhost:" + std::to_string(args.port);

        if (mClient->CheckServiceRunning(address)) {
            std::string errDetail = std::to_string(args.port)+"is already used by a service.";
            NCTI::ErrorInfo error = {1, "PortOccupied", errDetail};
            outputErrorAsJson(error);
            return error.code;
        }
    }
#endif
    return 0;
}

/**
 * @brief 获取文件版本
 * @param exePath 可执行文件路径
 * @return 版本字符串
 */
static QString getFileVersion(const QString& exePath)
{
#ifdef Q_OS_WIN
    DWORD dwHandle = 0;
    DWORD dwLen = GetFileVersionInfoSize(exePath.toStdWString().c_str(), &dwHandle);
    if (dwLen == 0) {
        return QString();
    }

    dwHandle = 0;
    std::wstring wstrPath = exePath.toStdWString();
    QByteArray buffer(dwLen, 0);
    if (!GetFileVersionInfo(wstrPath.c_str(), dwHandle, dwLen, buffer.data())) {
        return QString();
    }

    VS_FIXEDFILEINFO* pFileInfo = nullptr;
    UINT uLen = 0;
    if (!VerQueryValue(buffer.data(), L"\\", reinterpret_cast<LPVOID*>(&pFileInfo), &uLen)) {
        return QString();
    }

    if (!pFileInfo) {
        return QString();
    }

    QString version = QString("%1.%2.%3.%4")
        .arg(HIWORD(pFileInfo->dwFileVersionMS))
        .arg(LOWORD(pFileInfo->dwFileVersionMS))
        .arg(HIWORD(pFileInfo->dwFileVersionLS))
        .arg(LOWORD(pFileInfo->dwFileVersionLS));

    return version;
#else
    return QString();
#endif
}

int main(int argc, char* argv[])
{    
    // 参数解析
    argparse::ArgumentParser program("ncti_qt_caepre_processing", "2.0");

    // 主进程参数
    program.add_argument("-f", "--file").default_value(std::string{}).help("ncti file path");
    program.add_argument("-py","--pyfile").default_value(std::string{}).help("python script file");
    program.add_argument("-g", "--geometry").default_value(0).help("geometry type").scan<'i', int>();
    program.add_argument("-c", "--constraint").default_value(0).help("constraint type").scan<'i', int>();
    program.add_argument("-m", "--mesh").default_value(0).help("mesh type").scan<'i', int>();
    program.add_argument("-p", "--port").default_value(0).help("gRPC port").scan<'i', int>();

    // 子进程参数
    argparse::ArgumentParser subProc("sub_proc");
    subProc.add_argument("-s", "--server").default_value(std::string{}).help("server name");
    subProc.add_argument("-t", "--type").default_value(std::string{}).help("task type");
    subProc.add_argument("-f", "--file").default_value(std::string{}).help("ncti file path");
    subProc.add_argument("-g", "--geometry").default_value(0).help("geometry type").scan<'i', int>();
    subProc.add_argument("-c", "--constraint").default_value(0).help("constraint type").scan<'i', int>();
    subProc.add_argument("-m", "--mesh").default_value(0).help("mesh type").scan<'i', int>();
    subProc.set_suppress(true);
    program.add_subparser(subProc);

    // 解析命令行参数
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl << program;
        std::exit(1);
    }

    NCTI::AppArguments args;
    if (program.is_subcommand_used("sub_proc")) {
        handleSubProcessArguments(subProc, args);
    }
    else {
        int ret = handleMainProcessArguments(program, args);
        if (ret != 0) {
            return ret;
        }
    }

#ifdef NCTI_CAE_PRE_BUILD_DLL
    args.titlebarVisible = false;
#endif

    auto flag = args.titlebarVisible 
        ? SARibbonMainWindowStyleFlag::UseRibbonFrame
        : SARibbonMainWindowStyleFlag::UseNativeFrame;

    QElapsedTimer cost;
    cost.start();

    //在创建QApplication实例之前调用
    SARibbonBar::initHighDpi();

#ifdef _MSC_VER
    //设置Windows消息过滤器
    ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
    ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
    ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); //WM_COPYGLOBALDATA
#else
    qputenv("QT_QPA_PLATFORM", "xcb");
    qputenv("GDK_BACKEND", "x11");
    qputenv("EGL_PLATFORM", "x11");
#endif

    QApplication app(argc, argv);
	// 获取程序版本
	QString version = getFileVersion(QCoreApplication::applicationFilePath());
	if (!version.isEmpty()) {
		NctiPrintf("当前程序版本: %s", version.toUtf8().data());
	}

#if QT_VERSION_MAJOR < 6 || QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
    //设置生成dump的文件路径（Qt 5 或 Qt 6.4+ 支持）
    QString dumpPath = "crashDumps";
    QBreakpadInstance.setDumpPath(dumpPath);
#endif
    // 设置应用的基本信息
    setApplicationBaseInfo(app);

    // 安装自定义的日志处理函数
    qInstallMessageHandler(logMsgOutput);

    // 加载字体
    addApplicationFonts(app);

    // 初始化应用配置
    PreferenceSettings::initDefaultCAE();

    auto cfgDir = PreferenceSettings::getConfigDir();
    auto cfgFile = PreferenceSettings::getConfigFile();
    auto appPath = QCoreApplication::applicationDirPath().toStdString();

#ifdef NCTI_ENABLE_GRPC_SERVICE
    fs::path logPath(cfgDir);
    logPath = logPath / L"caepre_service_server.log";
    std::string strLogPath = String::GetStringFromU8(logPath.u8string());
    NCTI::Logger::enableFileLogging(strLogPath);
    NCTI::Logger::setLevel(NCTI::Log_Level::DEBUG);
    NCTI::Logger::flushEvery(std::chrono::seconds(3));
#endif
    int ret = 0;
    NCTI::NctiErrorType iRes = NCTI::NctiInitializeTool().InitNcti(appPath.c_str(), cfgFile.c_str(), cfgDir.c_str());
    if (iRes != NCTI::NctiErrorType::Success) {
        NCTI::NctiQTPubFun::showErrorMsgBox(iRes);
        ret = -1;
    }
    else {
        //窗口析构后再调用ReleaseNctiLicense
        NCTI::MainWindow mainWindow(flag, args);
        mainWindow.show();
        //NctiPrintf("window build cost:%I64d ms", cost.elapsed());
        ret = app.exec();
    }
    NCTI::NctiInitializeTool().ReleaseNcti();

#ifdef NCTI_ENABLE_GRPC_SERVICE
    NCTI::Logger::shutdown();
#endif
    return ret;
}
