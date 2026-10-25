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

#include "mainwindow_container.h"
#include <QSharedMemory>

#include <QFontDatabase>
#include <QApplication>
#include <QFile>

#include "SARibbonBar.h"


#ifdef _WIN32
  #include <windows.h>
#endif

static void addApplicationFonts(QApplication& app)
{
    int font_id = QFontDatabase::addApplicationFont(":/fonts/HarmonyOS_SansSC_Regular.ttf");
    if (font_id != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(font_id);
        if (!fontFamilies.empty()) {
            QFont font(fontFamilies.at(0), 12);
            app.setFont(font);
        }
    }
}

// 设置组织名称和应用名称
static void setApplicationBaseInfo(QApplication& a)
{
    a.setOrganizationName("YanHe");
    a.setApplicationDisplayName(QStringLiteral("多文档启动器"));

    QString preExePath = QCoreApplication::applicationDirPath() + "/ncti_qt_cae_pre.exe";
    bool preExeExists = QFile::exists(preExePath);
    if (preExeExists) {
        a.setApplicationName("GMDE");
    }
    else {
        a.setApplicationName("KernelLab");
    }
}

int main(int argc, char* argv[])
{
    SARibbonBar::initHighDpi();
    
    QApplication app(argc, argv);
    
    static QSharedMemory sharedMemory("{66E79DE5-94D0-49E0-A3F5-DA0DEB8B57C1}");
    if (!sharedMemory.create(1)) {
        qWarning() << "an instance of the ncti_qt_launcher is already running.";
        return -1;
    }

    // 设置应用的基本信息
    setApplicationBaseInfo(app);

    // 设置字体
    addApplicationFonts(app);
    
    NCTI::MainwindowContainer container;
    container.show();
    return app.exec();
}
