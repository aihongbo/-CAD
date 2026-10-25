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

#include "OptionsDlg.h"
#include "NctiDebug.h"

#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QListWidget>
#include <QStringListModel>
#include <QButtonGroup>
#include <QFormLayout>
#include <QGroupBox>
#include <QTimer>
#include <QCoreApplication>

#include "PreferenceSettings.h"
#include "ModelColorPreviewWidget.h"
#include "SelectColorWidget.h"
#include "AddLoadingDLLWidget.h"
#include "CustomDelegate.h"
#include "LineTypeDelegate.h"
#include "NctiConfig.h"
#include "NctiInitializeTool.h"

using namespace NCTI;

namespace {
    bool checkPluginExists(QTreeWidget* treeWidget, const QString& target)
    {
        for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
            QTreeWidgetItem* parent = treeWidget->topLevelItem(i);
            for (int j = 0; j < parent->childCount(); ++j) {
                QTreeWidgetItem* child = parent->child(j);
                if (child->text(0).compare(target, Qt::CaseInsensitive) == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    std::string toStdString(const QString& value)
    {
        QByteArray ba = value.toUtf8();
        return std::string(ba.constData());
    }

    int getBtnColor(QPushButton* button)
    {
        if (button) {
            return button->property("buttonColor").value<QColor>().rgb();
        }
        return 0;
    }

}

class OptionsDlg::OptionsDlgPrivate
{
public:
    OptionsDlg* q_ptr{nullptr};
    QLabel* floatingLabel{nullptr};
    QComboBox* themeColorComboBox{nullptr};
    QComboBox* languageComboBox{nullptr};

    QPushButton* topColorBtn{nullptr};
    QPushButton* bottomColorBtn{nullptr};
    QPushButton* faceColorBtn{nullptr};
    QPushButton* edgeColorBtn{nullptr};
    QPushButton* vertexColorBtn{nullptr};

    QPushButton* highLightColorBtn{nullptr};
    QPushButton* lineSegmentColorBtn{nullptr};
    QPushButton* dimensionLineColorBtn{nullptr};
    QPushButton* gridLineColorBtn{nullptr};

    QLineEdit* backgroundGradientColorLabel{nullptr};
    ModelColorPreviewWidget* modelColorPreviewWidget{nullptr};
    SelectColorWidget* colorWidget{nullptr};

    QPushButton* currentActiveBtn{nullptr};

    QPushButton* faceBtn{nullptr};
    QPushButton* edgeBtn{nullptr};
    QPushButton* vertexBtn{nullptr};
    QLabel* faceIconLabel{nullptr};
    QLabel* edgeIconLabel{nullptr};
    QLabel* vertexIconLabel{nullptr};

    QRadioButton* showManipulatorAxisBtn{nullptr};
    QRadioButton* hideManipulatorAxisBtn{nullptr};

    QRadioButton* realtimeHighlightingBtn{nullptr};
    QRadioButton* disableRealtimeHighlightingBtn{nullptr};

    QRadioButton* boxSelectAllBtn{nullptr};
    QRadioButton* disableBoxSelectAllBtn{nullptr};

    QComboBox* lineTypeComBox{nullptr};
    QLineEdit* lineWidthLineEdit{nullptr};
    QCheckBox* modelFaceCheckBox{nullptr};
    QCheckBox* highlightContourCheckBox{nullptr};
    QPushButton* backFaceColorSettingBtn{nullptr};

    QRadioButton* showFPSBtn{nullptr};
    QRadioButton* hideFPSBtn{nullptr};

    QListWidget* testCasePathListWidget{nullptr};
    QPushButton* addTestCasePathBtn{nullptr};
    QPushButton* deleteTestCasePathBtn{nullptr};
    QLineEdit* pythonScriptPathLineEdit{nullptr};
    QPushButton* pythonScriptPathBtn{nullptr};
    QLineEdit* pythonPathLineEdit{nullptr};
    QPushButton* pythonPathBtn{nullptr};

    QTreeWidget* treeWidget{nullptr};
    QPushButton* addLoadingPluginBtn{nullptr};
    QPushButton* deleteLoadingPluginBtn{nullptr};

    QRadioButton* showConsoleBtn{nullptr};
    QRadioButton* hideConsoleBtn{nullptr};
    QRadioButton* showScriptEditorBtn{nullptr};
    QRadioButton* hideScriptEditorBtn{nullptr};

    QRadioButton* backupBtn{nullptr};
    QRadioButton* disableBackupBtn{nullptr};

    QLineEdit* timeLineEdit{nullptr};
    QLineEdit* backupPathLineEdit{nullptr};
    QPushButton* backupPathBtn{nullptr};

    std::array<bool, 3> objectDisplayState{true, true, false};

    explicit OptionsDlgPrivate(OptionsDlg* q) : q_ptr(q) {}
};

OptionsDlg::OptionsDlg(QWidget* parent)
    : NctiBaseDialog(parent)
    , d_ptr(new OptionsDlgPrivate(this))
{
    setupUI();
    initConnects();
    auto cfg = AppConfig::GetConfig();
    if (cfg->Environment.AutoSaveFolder.empty()) {
        QDir tempDir(QDir::tempPath());
        if (tempDir.mkpath("NCTI")) {
            cfg->Environment.AutoSaveFolder = toStdString(tempDir.filePath("NCTI"));
        }
    }

    loadAppConfig();
    d_ptr->modelColorPreviewWidget->installEventFilter(this);
}

OptionsDlg::~OptionsDlg()
{
    delete d_ptr;
}

void OptionsDlg::setupUI()
{
    initWidgets();

    setTitle("选项卡");
    this->layout()->setContentsMargins(0, 0, 0, 0);

    auto widget = new QFrame(this);
    widget->setObjectName("newOptionsDlg");

    QVBoxLayout* vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->addSpacing(2);
    vBoxLayout->addLayout(hBoxLayout);

    QFrame* itemFrame = new QFrame;
    itemFrame->setObjectName("optionsItem_Frame");
    itemFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    itemFrame->setMinimumSize(QSize(150, 0));
    itemFrame->setMaximumSize(QSize(150, 16777215));
    hBoxLayout->addWidget(itemFrame);

    QVBoxLayout* itemLayout = new QVBoxLayout(itemFrame);
    itemLayout->setContentsMargins(6, 0, 6, 0);
    hBoxLayout->addSpacing(10);

    QStackedWidget* stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(CreateSettingWidget());
    stackedWidget->addWidget(CreateCADEnvironmentSettingsWidget());
    stackedWidget->addWidget(CreatePathSettingsWidget());
    stackedWidget->addWidget(CreateLoadingPluginsWidget());
    stackedWidget->addWidget(CreateWindowWidget());
    stackedWidget->addWidget(CreateBackupsWidget());
    hBoxLayout->addWidget(stackedWidget);

    itemLayout->addWidget(CreateItemListView(stackedWidget));

    QVBoxLayout* functionLayout = new QVBoxLayout;
    functionLayout->setContentsMargins(0, 0, 0, 0);
    functionLayout->addWidget(stackedWidget);
    functionLayout->addSpacing(2);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(CreateDefaultBtn());
    buttonLayout->addWidget(CreateSaveBtn());
    functionLayout->addLayout(buttonLayout);
    hBoxLayout->addLayout(functionLayout);
    
    setWidget(widget);
}

QListView* OptionsDlg::CreateItemListView(QStackedWidget* stackedWidget)
{
    auto itemListView = new QListView(this);
    itemListView->setObjectName("optionsItem_ListView");
    itemListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringListModel* model = new QStringListModel;
    model->setStringList({ "基本设置", "环境设置", "路径设置", "加载插件", "窗口", "备份" });
    itemListView->setModel(model);

    CustomDelegate* delegate = new CustomDelegate(itemListView);
    itemListView->setItemDelegate(delegate);
    itemListView->setCurrentIndex(model->index(0));

    connect(itemListView->selectionModel(), &QItemSelectionModel::currentRowChanged,
        [this, stackedWidget](const QModelIndex& current) {
            if (current.isValid()) {
                stackedWidget->setCurrentIndex(current.row());
            }
        });
    return itemListView;
}

QPushButton* OptionsDlg::CreateDefaultBtn()
{
    auto btn = new QPushButton();
    btn->setObjectName("pushButton_restore_default");
    btn->setText("恢复默认");
    btn->setFixedSize(90, 30);
    connect(btn, &QPushButton::clicked, this, [this] { 
        PreferenceSettings::initDefaultCAE();
        loadAppConfig();
        showFloatingLabel("已恢复默认！");
    });
    return btn;
}

QPushButton* OptionsDlg::CreateSaveBtn()
{
    auto btn = new QPushButton();
    btn->setObjectName("pushButton_save");
    btn->setText("保存");
    btn->setFixedSize(90, 30);
    
    connect(btn, &QPushButton::clicked, this, [this] { 
        if (updateAppConfig()) {
            showFloatingLabel("已保存！");
            Q_EMIT this->savePushButtonClicked();
        }
    });
    return btn;
}

QLabel* OptionsDlg::CreateFloatingLabel()
{
    QString styleSheet = QString(R"(
            background-color: rgb(229, 232, 241);
            border-radius: 5px;
            color: rgb(0, 0, 0);
        )");
    auto label = new QLabel(this);
    label->setStyleSheet(styleSheet);
    label->setAlignment(Qt::AlignCenter);
    label->hide();
    return label;
}

QPushButton* OptionsDlg::CreateColorBtn(const QString& objName)
{
    auto btn = new QPushButton;
    btn->setObjectName(objName);
    btn->setFixedSize(23, 23);
    return btn;
}

std::pair<QRadioButton*, QRadioButton*> OptionsDlg::createRadioButtonPair(QWidget* parent, const QString& showText, const QString& hideText, int width)
{
    QRadioButton* showBtn = new QRadioButton(parent);
    showBtn->setText(showText);
    showBtn->setFixedSize(width, 30);

    QRadioButton* hideBtn = new QRadioButton(parent);
    hideBtn->setText(hideText);
    hideBtn->setFixedSize(width, 30);

    return {showBtn, hideBtn};
}

void OptionsDlg::initWidgets()
{
    d_ptr->floatingLabel = CreateFloatingLabel();

    d_ptr->colorWidget = new SelectColorWidget(this);
    d_ptr->colorWidget->setFixedSize(254, 120);
    d_ptr->colorWidget->hide();

    d_ptr->backgroundGradientColorLabel = new QLineEdit;
    d_ptr->backgroundGradientColorLabel->setObjectName("backgroundGradientColor_LineEdit");
    d_ptr->backgroundGradientColorLabel->setReadOnly(true);
    d_ptr->backgroundGradientColorLabel->setFixedSize(70, 23);

    std::array<std::pair<QPushButton**, QString>, 10> colorButtons = {
        std::make_pair(&d_ptr->topColorBtn, QString("topColor_Button")),
        std::make_pair(&d_ptr->bottomColorBtn, QString("bottomColor_Button")),
        std::make_pair(&d_ptr->faceColorBtn, QString("faceColor_Button")),
        std::make_pair(&d_ptr->edgeColorBtn, QString("edgeColor_Button")),
        std::make_pair(&d_ptr->vertexColorBtn, QString("vertexColor_Button")),
        std::make_pair(&d_ptr->highLightColorBtn, QString("highlightColor_Button")),
        std::make_pair(&d_ptr->lineSegmentColorBtn, QString("lineSegmentsColor_Button")),
        std::make_pair(&d_ptr->dimensionLineColorBtn, QString("dimensionLinesColor_Button")),
        std::make_pair(&d_ptr->gridLineColorBtn, QString("gridLineColor_Button")),
        std::make_pair(&d_ptr->backFaceColorSettingBtn, QString("backFaceColorSetting_Btn"))
    };

    for (auto& item : colorButtons) {
        *item.first = CreateColorBtn(item.second);
    }
}

void OptionsDlg::initColorConnections()
{
    std::array<std::pair<QPushButton*, ColorWidgetType>, 10> colorButtonTypes = {
        std::make_pair(d_ptr->topColorBtn, ColorWidgetType::General),
        std::make_pair(d_ptr->bottomColorBtn, ColorWidgetType::General),
        std::make_pair(d_ptr->faceColorBtn, ColorWidgetType::Model),
        std::make_pair(d_ptr->edgeColorBtn, ColorWidgetType::Model),
        std::make_pair(d_ptr->vertexColorBtn, ColorWidgetType::Model),
        std::make_pair(d_ptr->highLightColorBtn, ColorWidgetType::Model),
        std::make_pair(d_ptr->lineSegmentColorBtn, ColorWidgetType::Sketch),
        std::make_pair(d_ptr->dimensionLineColorBtn, ColorWidgetType::Sketch),
        std::make_pair(d_ptr->gridLineColorBtn, ColorWidgetType::Sketch),
        std::make_pair(d_ptr->backFaceColorSettingBtn, ColorWidgetType::Render)
    };

    for (const auto& item : colorButtonTypes) {
        connect(item.first, &QPushButton::clicked, [this, button = item.first, type = item.second]() {
            onShowColorWidgetBelowButton(button, type);
        });
    }

    connect(d_ptr->colorWidget->getSelectColorLabel(),
        &ColorLabel::colorPicked, [this](const QColor& color) { setButtonColor(color); });

    connect(d_ptr->colorWidget, &SelectColorWidget::inputColor, [this](const QColor& color) { onUpdateColor(color); });
}

void OptionsDlg::initPathConnections()
{
    connect(d_ptr->addTestCasePathBtn, &QPushButton::clicked, [this] { onAddTestCasePathClicked(); });
    connect(d_ptr->deleteTestCasePathBtn, &QPushButton::clicked, [this] { onDeleteTestCasePathClicked(); });
    
    connect(d_ptr->pythonScriptPathBtn, &QPushButton::clicked, [this] { 
        selectDir(d_ptr->pythonScriptPathLineEdit); 
    });
    
    connect(d_ptr->pythonPathBtn, &QPushButton::clicked, [this] { 
        selectDir(d_ptr->pythonPathLineEdit);    
    });
}

void OptionsDlg::initPluginConnections()
{
    connect(d_ptr->addLoadingPluginBtn, &QPushButton::clicked, [this] { onAddLoadingPluginsClicked(); });
    connect(d_ptr->deleteLoadingPluginBtn, &QPushButton::clicked, [this] { onDeleteLoadingPluginsClicked(); });
}

void OptionsDlg::initBackupConnections()
{
    connect(d_ptr->backupBtn, &QPushButton::clicked, [this] { onEnableBackup(true); });
    connect(d_ptr->disableBackupBtn, &QPushButton::clicked, [this] { onEnableBackup(false); });
    
    connect(d_ptr->backupPathBtn, &QPushButton::clicked, [this] { 
        selectDir(d_ptr->backupPathLineEdit);    
    });
}

void OptionsDlg::initConnects()
{
    initColorConnections();

    connect(d_ptr->modelFaceCheckBox, &QCheckBox::toggled, [this] { 
        d_ptr->backFaceColorSettingBtn->setEnabled(d_ptr->modelFaceCheckBox->isChecked());
    });

    connect(d_ptr->faceBtn, &QPushButton::toggled, [this] { onFaceButtonToggled(); });
    connect(d_ptr->edgeBtn, &QPushButton::toggled, [this] { onEdgeButtonToggled(); });
    connect(d_ptr->vertexBtn, &QPushButton::toggled, [this] { onVertexButtonToggled(); });

    initPathConnections();
    initPluginConnections();
    initBackupConnections();
}

void OptionsDlg::loadAppConfig()
{
    auto cfg = AppConfig::GetConfig();
    //环境设置
    d_ptr->themeColorComboBox->setCurrentIndex(cfg->Environment.ThemeColor == "dark" ? 0 : 1);
    d_ptr->languageComboBox->setCurrentIndex(cfg->Environment.Language == "chinese" ? 0 : 1);
    QStringList importPathList;
    importPathList.reserve(cfg->Environment.ImportPath.size());
    for (const auto& path : cfg->Environment.ImportPath) {
        importPathList.append(QString::fromStdString(path));
    }
    d_ptr->testCasePathListWidget->clear();
    d_ptr->testCasePathListWidget->addItems(importPathList);

    d_ptr->pythonScriptPathLineEdit->setText(QString::fromUtf8(cfg->Environment.FunctionPath.c_str()));
    d_ptr->pythonPathLineEdit->setText(QString::fromUtf8(cfg->Environment.PythonPath.c_str()));

    setRadioButtonPair(d_ptr->showConsoleBtn, d_ptr->hideConsoleBtn, cfg->Environment.Console);
    setRadioButtonPair(d_ptr->showScriptEditorBtn, d_ptr->hideScriptEditorBtn, cfg->Environment.ScriptEditor);
    setRadioButtonPair(d_ptr->backupBtn, d_ptr->disableBackupBtn, cfg->Environment.AutoSaveValid);

    d_ptr->timeLineEdit->setText(QString::number(cfg->Environment.AutoSaveTime / 60));
    d_ptr->backupPathLineEdit->setText(QString::fromUtf8(cfg->Environment.AutoSaveFolder.c_str()));

    //模型设置
    std::array<int, 8> colors = {
        cfg->Model.FaceColor,
        cfg->Model.EdgeColor,
        cfg->Model.VertexColor,
        cfg->Model.HighlightColor,
        cfg->Model.LineSegmentColor,
        cfg->Model.DimensionLineColor,
        cfg->Model.GridLineColor,
        cfg->Model.BackColor
    };

    std::array<QPushButton*, 8> colorButtons = {
        d_ptr->faceColorBtn, d_ptr->edgeColorBtn, d_ptr->vertexColorBtn,
        d_ptr->highLightColorBtn, d_ptr->lineSegmentColorBtn, d_ptr->dimensionLineColorBtn,
        d_ptr->gridLineColorBtn, d_ptr->backFaceColorSettingBtn
    };

    setColorButtons(colorButtons, colors);
    d_ptr->modelColorPreviewWidget->set_faceColor(colors[0]);
    d_ptr->modelColorPreviewWidget->set_lineColor(colors[1]);
    d_ptr->modelColorPreviewWidget->set_pointColor(colors[2]);
    d_ptr->modelColorPreviewWidget->set_selectColor(colors[3]);

    d_ptr->lineTypeComBox->setCurrentIndex(cfg->Model.LineType);
    d_ptr->lineWidthLineEdit->setText(QString::number(cfg->Model.LineWidth, 'g', 6));
    d_ptr->modelFaceCheckBox->setChecked(cfg->Model.ShowBackColor);
    d_ptr->highlightContourCheckBox->setChecked(cfg->Model.ShowContour);

    setColorButtonStyleSheet(d_ptr->topColorBtn, QColor(cfg->Model.BackgroundColor0));
    setColorButtonStyleSheet(d_ptr->bottomColorBtn, QColor(cfg->Model.BackgroundColor1));
    updateBackgroundColor();


    //渲染设置
    d_ptr->faceBtn->setChecked(cfg->Renderer.ObjectDisplayMode[0]);
    d_ptr->edgeBtn->setChecked(cfg->Renderer.ObjectDisplayMode[1]);
    d_ptr->vertexBtn->setChecked(cfg->Renderer.ObjectDisplayMode[2]);
    setRadioButtonPair(d_ptr->showManipulatorAxisBtn, d_ptr->hideManipulatorAxisBtn, cfg->Renderer.OperatingAxis);
    setRadioButtonPair(d_ptr->showFPSBtn, d_ptr->hideFPSBtn, cfg->Renderer.OpenRenderDisplayTime);
    setRadioButtonPair(d_ptr->realtimeHighlightingBtn, d_ptr->disableRealtimeHighlightingBtn, cfg->Renderer.RenderPreHighlight);
    setRadioButtonPair(d_ptr->boxSelectAllBtn, d_ptr->disableBoxSelectAllBtn, cfg->Renderer.RenderBoxSelctAll);


    //加载插件设置
    initPlugins();
}

void OptionsDlg::initPlugins()
{
    d_ptr->treeWidget->clear();

    auto cfg = AppConfig::GetConfig();
    for (int i = 0; i < cfg->Plugin.PluginCount();++i) {
        std::vector<std::string> dll;
        std::string path;
        cfg->Plugin.GetPlugin(i, dll, path);

        QTreeWidgetItem* parentItem = new QTreeWidgetItem(d_ptr->treeWidget);
        parentItem->setText(0, QString::fromUtf8(path.c_str()));
        for (size_t n = 0; n < dll.size(); n++) {
            QString childName = QString::fromUtf8(dll[n].c_str());
            auto childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, childName);
        }
    }
    d_ptr->treeWidget->expandAll();
}

void OptionsDlg::getPluginsData()
{
    auto cfg = AppConfig::GetConfig();
    cfg->Plugin.ClearPlugin();
    for (int i = 0; i < d_ptr->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem* topLevelItem = d_ptr->treeWidget->topLevelItem(i);
        auto path = toStdString(topLevelItem->text(0));
        std::vector<std::string> dll;
        for (int j = 0; j < topLevelItem->childCount(); ++j) {
            QTreeWidgetItem* childItem = topLevelItem->child(j);
            if (!childItem->text(0).isEmpty()) {
                dll.push_back(toStdString(childItem->text(0)));
            }
        }
        cfg->Plugin.AddPlugin(dll, path);
    }
}

void OptionsDlg::setColorButtonStyleSheet(QPushButton* button, const QColor& color)
{
    QString styleSheet = QString(R"(
            QPushButton {
            border: 1px solid #8f8f91;
            border-radius: 4px;
            background: %1;
        }
        )").arg(color.name());
    button->setProperty("buttonColor", color);
    button->setStyleSheet(styleSheet);
}

void OptionsDlg::updateBackgroundColor()
{
    QColor topColor = d_ptr->topColorBtn->property("buttonColor").value<QColor>();
    QColor bottomColor = d_ptr->bottomColorBtn->property("buttonColor").value<QColor>();

    QString styleSheet_backgroundColor = QString(R"(
        QLineEdit {
            border: 1px solid #8f8f91;
            border-radius: 4px;
            padding: 5px;
            background: qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1,
                stop: 0 %1,
                stop: 1 %2);
        })").arg(topColor.name()).arg(bottomColor.name());
    d_ptr->backgroundGradientColorLabel->setStyleSheet(styleSheet_backgroundColor);
}

// clang-format off
void OptionsDlg::setPreviewModelWidgetColor(QPushButton* button, const QColor& color)
{
    if (button == d_ptr->edgeColorBtn)           { d_ptr->modelColorPreviewWidget->set_lineColor(color);  }
    else if (button == d_ptr->vertexColorBtn)    { d_ptr->modelColorPreviewWidget->set_pointColor(color); }
    else if (button == d_ptr->faceColorBtn)      { d_ptr->modelColorPreviewWidget->set_faceColor(color);  }
    else if (button == d_ptr->highLightColorBtn) { d_ptr->modelColorPreviewWidget->set_selectColor(color);}
}
// clang-format on

void OptionsDlg::setColorButtons(const std::array<QPushButton*, 8>& buttons, const std::array<int, 8>& colors)
{
    for (size_t i = 0; i < buttons.size() && i < colors.size(); ++i) {
        if (buttons[i]) {
            setColorButtonStyleSheet(buttons[i], QColor(colors[i]));
        }
    }
}

void OptionsDlg::setRadioButtonPair(QRadioButton* showBtn, QRadioButton* hideBtn, bool show)
{
    if (showBtn && hideBtn) {
        showBtn->setChecked(show);
        hideBtn->setChecked(!show);
    }
}

void OptionsDlg::saveColorConfigs(const std::array<QPushButton*, 8>& buttons, std::array<int, 8>& configColors)
{
    for (size_t i = 0; i < buttons.size() && i < configColors.size(); ++i) {
        if (buttons[i]) {
            configColors[i] = getBtnColor(buttons[i]);
        }
    }
}

bool OptionsDlg::updateAppConfig()
{
    auto cfg = AppConfig::GetConfig();

    //环境设置
    cfg->Environment.ThemeColor = (d_ptr->themeColorComboBox->currentIndex() == 0) ? "dark" : "light";
    cfg->Environment.Language = (d_ptr->languageComboBox->currentIndex() == 0) ? "chinese" : "english";
    cfg->Environment.ImportPath.clear();
    for (int i = 0; i < d_ptr->testCasePathListWidget->count(); ++i) {
        QListWidgetItem* item = d_ptr->testCasePathListWidget->item(i);
        if (item) {
            cfg->Environment.ImportPath.push_back(toStdString(item->text()));
        }
    }

    cfg->Environment.FunctionPath = toStdString(d_ptr->pythonScriptPathLineEdit->text());
    cfg->Environment.PythonPath = toStdString(d_ptr->pythonPathLineEdit->text());
    cfg->Environment.Console = d_ptr->showConsoleBtn->isChecked();
    cfg->Environment.ScriptEditor = d_ptr->showScriptEditorBtn->isChecked();
    cfg->Environment.AutoSaveValid = d_ptr->backupBtn->isChecked();

    bool ok{ false };
    int autoSaveTime = d_ptr->timeLineEdit->text().toInt(&ok, 10);
    autoSaveTime = ok ? autoSaveTime * 60 : 300;
    cfg->Environment.AutoSaveTime = autoSaveTime;
    cfg->Environment.AutoSaveFolder = toStdString(d_ptr->backupPathLineEdit->text());


    //模型设置
    cfg->Model.BackgroundColor0 = getBtnColor(d_ptr->topColorBtn);
    cfg->Model.BackgroundColor1 = getBtnColor(d_ptr->bottomColorBtn);
    std::array<QPushButton*, 8> colorButtons = {
        d_ptr->faceColorBtn,
        d_ptr->edgeColorBtn,
        d_ptr->vertexColorBtn,
        d_ptr->highLightColorBtn,
        d_ptr->lineSegmentColorBtn,
        d_ptr->dimensionLineColorBtn,
        d_ptr->gridLineColorBtn,
        d_ptr->backFaceColorSettingBtn
    };
    std::array<int, 8> colorConfigs;
    saveColorConfigs(colorButtons, colorConfigs);

    double dLineWidth = d_ptr->lineWidthLineEdit->text().toDouble(&ok);
    dLineWidth = ok ? dLineWidth : 1.0;
    cfg->Model.FaceColor = colorConfigs[0];
    cfg->Model.EdgeColor = colorConfigs[1];
    cfg->Model.VertexColor = colorConfigs[2];
    cfg->Model.HighlightColor = colorConfigs[3];
    cfg->Model.LineSegmentColor = colorConfigs[4];
    cfg->Model.DimensionLineColor = colorConfigs[5];
    cfg->Model.GridLineColor = colorConfigs[6];
    cfg->Model.BackColor = colorConfigs[7];

    cfg->Model.LineType = d_ptr->lineTypeComBox->currentIndex();
    cfg->Model.LineWidth = dLineWidth;
    cfg->Model.ShowBackColor = d_ptr->modelFaceCheckBox->isChecked();
    cfg->Model.ShowContour = d_ptr->highlightContourCheckBox->isChecked();

    //渲染设置
    cfg->Renderer.ObjectDisplayMode = {d_ptr->objectDisplayState[0], d_ptr->objectDisplayState[1], d_ptr->objectDisplayState[2]};
    cfg->Renderer.OperatingAxis = d_ptr->showManipulatorAxisBtn->isChecked();
    cfg->Renderer.OpenRenderDisplayTime = d_ptr->showFPSBtn->isChecked();
    cfg->Renderer.RenderPreHighlight = d_ptr->realtimeHighlightingBtn->isChecked();
    cfg->Renderer.RenderBoxSelctAll = d_ptr->boxSelectAllBtn->isChecked();
    getPluginsData();

    return NctiInitializeTool().saveToFile(PreferenceSettings::getConfigFile().c_str());
}

void OptionsDlg::updateDisplayModeIcon()
{
    static QPixmap checkedPixmap;
    static QPixmap uncheckedPixmap;
    static bool initialized = false;

    if (!initialized) {
        QPixmap checked(":/Option/checked.png");
        QPixmap unchecked(":/Option/unchecked.png");
        checkedPixmap = checked.scaled(QSize(18, 18), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        uncheckedPixmap = unchecked.scaled(QSize(18, 18), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        initialized = true;
    }

    d_ptr->faceIconLabel->setPixmap(d_ptr->objectDisplayState[0] ? checkedPixmap : uncheckedPixmap);
    d_ptr->edgeIconLabel->setPixmap(d_ptr->objectDisplayState[1] ? checkedPixmap : uncheckedPixmap);
    d_ptr->vertexIconLabel->setPixmap(d_ptr->objectDisplayState[2] ? checkedPixmap : uncheckedPixmap);
}

void OptionsDlg::deleteItemRecursive(QTreeWidgetItem* item)
{
    if (!item) {
        return;
    }

    for (int i = 0; i < item->childCount(); ++i) {
        deleteItemRecursive(item->child(i));
    }

    QTreeWidgetItem* parent = item->parent();
    if (parent) {
        parent->removeChild(item);
        if (parent->text(0).isEmpty()) {
            deleteItemRecursive(parent);
        }
        else if (parent->childCount() == 0) {
            parent->setText(0, "");
            deleteItemRecursive(parent);
        }
    }
    else {
        d_ptr->treeWidget->takeTopLevelItem(d_ptr->treeWidget->indexOfTopLevelItem(item));
    }
}

void OptionsDlg::showFloatingLabel(const QString& text)
{
    if (!d_ptr->floatingLabel) { return; }
    d_ptr->floatingLabel->setText(text);
    QPoint center = this->rect().center() - d_ptr->floatingLabel->rect().center();
    d_ptr->floatingLabel->move(center);
    d_ptr->floatingLabel->show();
    QTimer::singleShot(2000, this, [this]() {
        d_ptr->floatingLabel->clear();
        d_ptr->floatingLabel->hide();
    });
}

void OptionsDlg::showSelectColorWidget(const QColor& color, const QPoint& pos)
{
    d_ptr->colorWidget->updateColor(color);
    d_ptr->colorWidget->move(pos);
    d_ptr->colorWidget->show();
}

QTreeWidgetItem* OptionsDlg::addPluginInApplicationDir(const QString& appDir, const QString& pluginName)
{
    QTreeWidgetItem* parentItem = nullptr;
    
    QStringList parts = pluginName.split('_');
    if (parts.size() < 2) {
        return nullptr;
    }
    QString target = parts[1];

    QDir dir{appDir};
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    bool found = false;
    Q_FOREACH (const QFileInfo& entry, entries) {
        if (entry.isDir() && QString::compare(entry.fileName(), target, Qt::CaseInsensitive) == 0) {
            bool pluginExists = false;
            for (int i = 0; i < d_ptr->treeWidget->topLevelItemCount(); ++i) {
                QTreeWidgetItem* pParent = d_ptr->treeWidget->topLevelItem(i);
                if (QString::compare(pParent->text(0), target, Qt::CaseInsensitive) == 0) {
                    parentItem   = pParent;
                    pluginExists = true;
                    break;
                }
                if (pluginExists) {
                    break;
                }
            }

            if (!pluginExists) {
                parentItem = new QTreeWidgetItem(d_ptr->treeWidget);
                parentItem->setText(0, entry.fileName());
            }
            found = true;
        }
    }
    if (!found) {
        parentItem = new QTreeWidgetItem(d_ptr->treeWidget);
        parentItem->setText(0, "");
    }
    return parentItem;
}

QTreeWidgetItem* OptionsDlg::addPluginInOutsideDir(const QString& pluginName)
{
    for (int i = 0; i < d_ptr->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = d_ptr->treeWidget->topLevelItem(i);
        if (item->text(0).compare(pluginName, Qt::CaseInsensitive) == 0) {
            return item;
        }
    }
    QTreeWidgetItem* parentItem = new QTreeWidgetItem(d_ptr->treeWidget);
    parentItem->setText(0, pluginName);
    return parentItem;
}

void OptionsDlg::onAddPlugin(const QString pluginPath, const QString plugin)
{
    QStringList parentNames = pluginPath.split(';');
    QStringList pluginNames = plugin.split(';');
    if (parentNames.size() != pluginNames.size()) {
        return;
    }
    QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    QString applicationDir = fileInfo.absolutePath();
    for (int i = 0; i < parentNames.size(); ++i) {
        if (checkPluginExists(d_ptr->treeWidget, pluginNames[i])) {
            QMessageBox::information(this, "提示", QString("插件%1已存在").arg(pluginNames[i]));
            continue;
        }
        QTreeWidgetItem* parentItem = nullptr;
        if (applicationDir == parentNames[i]) {
            parentItem = addPluginInApplicationDir(applicationDir, pluginNames[i]);
        }
        else {
            parentItem = addPluginInOutsideDir(pluginNames[i]);
        }
        if (parentItem) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, pluginNames[i]);
        }
    }
    d_ptr->treeWidget->expandAll();
}

void OptionsDlg::onFaceButtonToggled()
{
    d_ptr->objectDisplayState[0] = d_ptr->faceBtn->isChecked();
    updateDisplayModeIcon();
}

void OptionsDlg::onEdgeButtonToggled()
{
    d_ptr->objectDisplayState[1] = d_ptr->edgeBtn->isChecked();
    updateDisplayModeIcon();
}

void OptionsDlg::onVertexButtonToggled()
{
    d_ptr->objectDisplayState[2] = d_ptr->vertexBtn->isChecked();
    updateDisplayModeIcon();
}

void OptionsDlg::setButtonColor(const QColor& color)
{
    setColorButtonStyleSheet(d_ptr->currentActiveBtn, color);
    
    d_ptr->colorWidget->updateColor(color);

    if (d_ptr->currentActiveBtn == d_ptr->topColorBtn || d_ptr->currentActiveBtn == d_ptr->bottomColorBtn) {
        updateBackgroundColor();
    }
    else {
        setPreviewModelWidgetColor(d_ptr->currentActiveBtn, color);
    }
}

void OptionsDlg::onDeleteTestCasePathClicked()
{
    QListWidgetItem* selectedItem = d_ptr->testCasePathListWidget->currentItem();
    if (selectedItem) {
        int row = d_ptr->testCasePathListWidget->row(selectedItem);
        delete d_ptr->testCasePathListWidget->takeItem(row);
    }
    else {
        QMessageBox::information(this, "No Selection", "No item selected.");
    }
}

void OptionsDlg::onAddTestCasePathClicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this, "选择文件夹", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dirPath.isEmpty()) {
        return;
    }

    bool exists = false;
    for (int i = 0; i < d_ptr->testCasePathListWidget->count(); ++i) {
        if (d_ptr->testCasePathListWidget->item(i)->text() == dirPath) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        QListWidgetItem* newItem = new QListWidgetItem(dirPath);
        d_ptr->testCasePathListWidget->addItem(newItem);
    }
    else {
        QMessageBox::information(this, "Folder Already Exists", "The selected folder is already in the list.");
    }
}

void OptionsDlg::selectDir(QLineEdit* lineEdit)
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this, "选择文件夹", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isEmpty()) {
        lineEdit->setText(dirPath);
    }
}

void OptionsDlg::onDeleteLoadingPluginsClicked()
{
    QTreeWidgetItem* current_item = d_ptr->treeWidget->currentItem();
    if (!current_item) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "提示", "确定删除？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        deleteItemRecursive(current_item);
    }
}

void OptionsDlg::onEnableBackup(bool enable)
{
    d_ptr->timeLineEdit->setEnabled(enable);
    d_ptr->backupPathLineEdit->setEnabled(enable);
    d_ptr->backupPathBtn->setEnabled(enable);
}

void OptionsDlg::onUpdateColor(const QColor& color)
{
    setButtonColor(color);
}

void OptionsDlg::onShowColorWidgetBelowButton(QPushButton* button, ColorWidgetType type)
{
    if (!button || !d_ptr->colorWidget) {
        return;
    }

    QPoint buttonTopLeftGlobal = button->mapToGlobal(QPoint(0, 0));
    QRect buttonRectGlobal(buttonTopLeftGlobal, button->size());
    int buttonCenterX = buttonRectGlobal.center().x();
    int widgetLeftX = buttonCenterX - d_ptr->colorWidget->width() / 2;
    int widgetTopY = buttonRectGlobal.bottom() + 10;

    QPoint pos = this->mapFromGlobal(QPoint(widgetLeftX, widgetTopY));

    QRect dlgGeometry = this->geometry();
    if (pos.x() < 0) {
        pos.setX(0);
    }
    if (pos.x() + d_ptr->colorWidget->width() > dlgGeometry.width()) {
        pos.setX(dlgGeometry.width() - d_ptr->colorWidget->width());
    }

    QColor color = button->property("buttonColor").value<QColor>();
    showSelectColorWidget(color, pos);
    d_ptr->currentActiveBtn = button;
}

void OptionsDlg::onAddLoadingPluginsClicked()
{
    auto addDLLWidget = new AddLoadingDLLWidget(this);
    addDLLWidget->setObjectName("addDLL_Widget");

    connect(addDLLWidget, &AddLoadingDLLWidget::selectPluginConfirmed,
            [this](const QString pluginPath, const QString plugin) { 
            onAddPlugin(pluginPath, plugin); 
        });
}

void OptionsDlg::setObjectDisplayMode(bool face, bool edge, bool vertex)
{
    d_ptr->objectDisplayState = {face, edge, vertex};
}

void OptionsDlg::setConsoleVisible(bool consoleState)
{
    d_ptr->showConsoleBtn->setChecked(consoleState);
}

void OptionsDlg::setScriptEditorVisible(bool scriptEditorState)
{
    d_ptr->showScriptEditorBtn->setChecked(scriptEditorState);
}

QWidget* OptionsDlg::CreateSettingWidget()
{
    QWidget* widget = new QWidget;

    QLabel* themeColorLabel = new QLabel(tr("主题颜色："), widget);
    themeColorLabel->setObjectName("select_Theme_Label");

    d_ptr->themeColorComboBox = new QComboBox(widget);
    d_ptr->themeColorComboBox->setObjectName("select_Theme_ComboBox");
    d_ptr->themeColorComboBox->addItem(tr("深色"));
    d_ptr->themeColorComboBox->addItem(tr("浅色"));
    d_ptr->themeColorComboBox->setView(new QListView);

    QLabel* languageLabel = new QLabel(tr("语言设置："), widget);
    languageLabel->setObjectName("select_Language_Label");

    d_ptr->languageComboBox = new QComboBox(widget);
    d_ptr->languageComboBox->setObjectName("select_Language_ComboBox");
    d_ptr->languageComboBox->addItem(tr("中文"));
    d_ptr->languageComboBox->addItem(tr("英文"));
    d_ptr->languageComboBox->setView(new QListView);

    QFormLayout* formLayout = new QFormLayout(widget);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->addRow(themeColorLabel, d_ptr->themeColorComboBox);
    formLayout->setVerticalSpacing(20);
    formLayout->addRow(languageLabel, d_ptr->languageComboBox);

    return widget;
}

QWidget* OptionsDlg::CreateCADEnvironmentSettingsWidget()
{
    auto* widget = new QWidget;
    widget->setObjectName("CADEnvironmentSettingsWidget");
    widget->installEventFilter(this);
    auto* vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->addWidget(CreateColorSettingWidget());
    vBoxLayout->addWidget(CreateModeAndLightingSettingWidget());
    vBoxLayout->addWidget(SketchDrawingAndModeAxiseSettingWidget());
    vBoxLayout->addStretch();
    return widget;
}

QWidget* OptionsDlg::CreateColorSettingWidget()
{
    auto* widget = new QWidget;
    widget->setObjectName("colorSetting_Widget");
    auto* mainLayout = new QVBoxLayout(widget);

    auto* titleWidget = new QWidget;
    titleWidget->setFixedHeight(15);
    auto* titleLayout = new QHBoxLayout(titleWidget);
    titleLayout->setContentsMargins(0, 0, 0, 0);

    auto* titleLabel = new QLabel;
    titleLabel->setObjectName("colorTitle_Label");
    titleLabel->setText("颜色");
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();

    auto* contentWidget = new QWidget;
    auto* contentLayout = new QHBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    auto* label = new QLabel;
    label->setObjectName("backgroundColor_Label");
    label->setText("背景渐变色：");
    contentLayout->addWidget(label);
    contentLayout->addSpacing(10);
    contentLayout->addWidget(d_ptr->topColorBtn);
    contentLayout->addSpacing(8);
    contentLayout->addWidget(d_ptr->bottomColorBtn);
    contentLayout->addStretch();

    auto* previewLabel = new QLabel;
    previewLabel->setObjectName("backgroundColorPreview_Label");
    previewLabel->setText("预览");
    contentLayout->addWidget(previewLabel);
    contentLayout->addWidget(d_ptr->backgroundGradientColorLabel);
    contentLayout->addSpacing(40);

    mainLayout->addWidget(titleWidget);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(contentWidget);

    return widget;
}

QWidget* OptionsDlg::CreateModeAndLightingSettingWidget()
{
    auto* widget = new QWidget;
    auto* mainLayout = new QHBoxLayout(widget);

    auto* previewWidget = new QWidget;
    auto* previewLayout = new QVBoxLayout(previewWidget);
    previewLayout->setContentsMargins(0, 0, 0, 0);

    d_ptr->modelColorPreviewWidget = new ModelColorPreviewWidget;
    d_ptr->modelColorPreviewWidget->setObjectName("modelColorPreviewWidget");
    previewLayout->addWidget(d_ptr->modelColorPreviewWidget);

    auto* leftLayout = new QVBoxLayout;

    auto* modelTitleLabel = new QLabel;
    modelTitleLabel->setObjectName("modeTitle_Label");
    modelTitleLabel->setText("模型");
    auto* modelTitleLayout = new QHBoxLayout;
    modelTitleLayout->addWidget(modelTitleLabel);
    modelTitleLayout->addStretch();

    auto* faceLabel = new QLabel;
    faceLabel->setObjectName("modeColor_Label");
    faceLabel->setText("面：");

    auto* edgeLabel = new QLabel;
    edgeLabel->setObjectName("modeColor_Label");
    edgeLabel->setText("线：");

    auto* vertexLabel = new QLabel;
    vertexLabel->setObjectName("modeColor_Label");
    vertexLabel->setText("点：");

    auto* modelColorLayout = new QHBoxLayout;
    modelColorLayout->addWidget(faceLabel);
    modelColorLayout->addSpacing(12);
    modelColorLayout->addWidget(d_ptr->faceColorBtn);
    modelColorLayout->addSpacing(15);
    modelColorLayout->addWidget(edgeLabel);
    modelColorLayout->addSpacing(12);
    modelColorLayout->addWidget(d_ptr->edgeColorBtn);
    modelColorLayout->addSpacing(15);
    modelColorLayout->addWidget(vertexLabel);
    modelColorLayout->addSpacing(12);
    modelColorLayout->addWidget(d_ptr->vertexColorBtn);
    modelColorLayout->addStretch();

    auto* lightingTitleLabel = new QLabel;
    lightingTitleLabel->setObjectName("LightingTitle_Label");
    lightingTitleLabel->setText("灯光");
    auto* lightingTitleLayout = new QHBoxLayout;
    lightingTitleLayout->addWidget(lightingTitleLabel);
    lightingTitleLayout->addStretch();

    auto* highlightLabel = new QLabel;
    highlightLabel->setObjectName("LightingColor_Label");
    highlightLabel->setText("选中后高亮：");

    auto* lightingLayout = new QHBoxLayout;
    lightingLayout->addWidget(highlightLabel);
    lightingLayout->addWidget(d_ptr->highLightColorBtn);
    lightingLayout->addStretch();

    leftLayout->addLayout(modelTitleLayout);
    leftLayout->addSpacing(10);
    leftLayout->addLayout(modelColorLayout);
    leftLayout->addSpacing(15);
    leftLayout->addLayout(lightingTitleLayout);
    leftLayout->addSpacing(10);
    leftLayout->addLayout(lightingLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(previewWidget);
    mainLayout->addSpacing(30);

    return widget;
}

QWidget* OptionsDlg::SketchDrawingAndModeAxiseSettingWidget()
{
    auto* widget = new QWidget;
    auto* mainLayout = new QVBoxLayout(widget);

    auto* sketchWidget = new QWidget;
    auto* sketchLayout = new QVBoxLayout(sketchWidget);
    sketchLayout->setContentsMargins(0, 0, 0, 0);

    auto* sketchTitleWidget = new QWidget;
    sketchTitleWidget->setFixedHeight(30);
    auto* sketchTitleLayout = new QHBoxLayout(sketchTitleWidget);
    sketchTitleLayout->setContentsMargins(0, 0, 0, 0);

    auto* sketchTitleLabel = new QLabel;
    sketchTitleLabel->setObjectName("sketchDrawingTitle_Label");
    sketchTitleLabel->setText("草图绘制");
    sketchTitleLayout->addWidget(sketchTitleLabel);
    sketchTitleLayout->addStretch();

    auto* sketchSettingWidget = new QWidget;
    auto* sketchSettingLayout = new QHBoxLayout(sketchSettingWidget);
    sketchSettingLayout->setContentsMargins(0, 0, 0, 0);

    auto* lineSegmentLabel = new QLabel;
    lineSegmentLabel->setObjectName("sketchDrawingColor_Label");
    lineSegmentLabel->setText("草图绘制线段：");

    auto* dimensionLineLabel = new QLabel;
    dimensionLineLabel->setObjectName("sketchDrawingColor_Label");
    dimensionLineLabel->setText("草图尺寸线：");

    auto* gridLineLabel = new QLabel;
    gridLineLabel->setObjectName("sketchDrawingColor_Label");
    gridLineLabel->setText("网格线：");

    sketchSettingLayout->addWidget(lineSegmentLabel);
    sketchSettingLayout->addWidget(d_ptr->lineSegmentColorBtn);
    sketchSettingLayout->addSpacing(20);
    sketchSettingLayout->addWidget(dimensionLineLabel);
    sketchSettingLayout->addWidget(d_ptr->dimensionLineColorBtn);
    sketchSettingLayout->addSpacing(20);
    sketchSettingLayout->addWidget(gridLineLabel);
    sketchSettingLayout->addWidget(d_ptr->gridLineColorBtn);
    sketchSettingLayout->addStretch();

    sketchLayout->addWidget(sketchTitleWidget);
    sketchLayout->addWidget(sketchSettingWidget);

    auto* renderLayout = new QHBoxLayout;
    auto* renderGridLayout = new QGridLayout;
    renderGridLayout->setContentsMargins(0, 0, 0, 0);
    renderGridLayout->setHorizontalSpacing(20);
    renderGridLayout->setVerticalSpacing(5);

    auto* renderTitleLabel = new QLabel(QStringLiteral("渲染设置"));
    renderTitleLabel->setObjectName(QStringLiteral("renderSetting_Lab"));

    auto* lineSettingLabel = new QLabel(QStringLiteral("模型线设置"));
    lineSettingLabel->setObjectName(QStringLiteral("modelLineSetting_Lab"));

    auto* lineTypeLabel = new QLabel(QStringLiteral("线型："));
    lineTypeLabel->setObjectName(QStringLiteral("modelLineType_Lab"));

    d_ptr->lineTypeComBox = new QComboBox;
    d_ptr->lineTypeComBox->setObjectName(QStringLiteral("lineType_ComBox"));
    d_ptr->lineTypeComBox->addItems(QStringList() << "实线" << "点线" << "点划线" << "中心线" << "虚线" << "双点线" << "三点线");
    d_ptr->lineTypeComBox->setItemDelegate(new LineTypeDelegate(d_ptr->lineTypeComBox));

    auto* lineTypeWidget = new QWidget;
    auto* lineTypeLayout = new QHBoxLayout(lineTypeWidget);
    lineTypeLayout->setContentsMargins(0, 0, 0, 0);
    lineTypeLayout->addWidget(lineTypeLabel);
    lineTypeLayout->addSpacing(5);
    lineTypeLayout->addWidget(d_ptr->lineTypeComBox);
    lineTypeLayout->addStretch();

    auto* lineWidthLabel = new QLabel(QStringLiteral("线宽："));
    lineWidthLabel->setObjectName(QStringLiteral("modelLineWidth_Lab"));

    d_ptr->lineWidthLineEdit = new QLineEdit;
    d_ptr->lineWidthLineEdit->setFixedSize(70, 23);

    auto* backFaceLabel = new QLabel(QStringLiteral("背面颜色设置"));
    backFaceLabel->setObjectName(QStringLiteral("modelFaceSetting_Lab"));

    d_ptr->modelFaceCheckBox = new QCheckBox(QStringLiteral("启用设置"));
    d_ptr->modelFaceCheckBox->setObjectName(QStringLiteral("modelFace_CheckBox"));
    d_ptr->modelFaceCheckBox->setFixedSize(75, 25);

    auto* backFaceColorLabel = new QLabel(QStringLiteral("背面颜色："));
    backFaceColorLabel->setObjectName(QStringLiteral("modelBackFaceColorSetting_Lab"));

    auto* backFaceColorWidget = new QWidget;
    auto* backFaceColorLayout = new QHBoxLayout(backFaceColorWidget);
    backFaceColorLayout->setContentsMargins(0, 0, 0, 0);
    backFaceColorLayout->addWidget(backFaceColorLabel);
    backFaceColorLayout->addSpacing(5);
    backFaceColorLayout->addWidget(d_ptr->backFaceColorSettingBtn);
    backFaceColorLayout->addStretch();

    auto* highlightContourLabel = new QLabel(QStringLiteral("高亮轮廓设置"));
    highlightContourLabel->setObjectName(QStringLiteral("HighlightContourSetting_Lab"));

    d_ptr->highlightContourCheckBox = new QCheckBox(QStringLiteral("启用设置"));
    d_ptr->highlightContourCheckBox->setObjectName(QStringLiteral("highlightContour_CheckBox"));
    d_ptr->highlightContourCheckBox->setFixedSize(75, 25);

    //auto* highlightContourColorLabel = new QLabel(QStringLiteral("轮廓颜色："));
    //highlightContourColorLabel->setObjectName(QStringLiteral("HighlightContourColor_Lab"));

    auto* fpsLabel = new QLabel(QStringLiteral("帧率显示"));
    fpsLabel->setObjectName(QStringLiteral("DisplayFrameRate_Lab"));

    d_ptr->showFPSBtn = new QRadioButton(QStringLiteral("显示"));
    d_ptr->showFPSBtn->setObjectName(QStringLiteral("displayFrameRate_Button"));
    d_ptr->showFPSBtn->setFixedSize(65, 25);

    d_ptr->hideFPSBtn = new QRadioButton(QStringLiteral("不显示"));
    d_ptr->hideFPSBtn->setObjectName(QStringLiteral("hideFrameRate_Button"));
    d_ptr->hideFPSBtn->setFixedSize(65, 25);

    renderGridLayout->addWidget(renderTitleLabel, 0, 0);
    renderGridLayout->addWidget(lineSettingLabel, 1, 0);
    renderGridLayout->addWidget(lineTypeWidget, 1, 1, 1, 2);
    renderGridLayout->addWidget(lineWidthLabel, 1, 3);
    renderGridLayout->addWidget(d_ptr->lineWidthLineEdit, 1, 4);
    renderGridLayout->addWidget(backFaceLabel, 2, 0);
    renderGridLayout->addWidget(d_ptr->modelFaceCheckBox, 2, 1);
    renderGridLayout->addWidget(backFaceColorWidget, 2, 2, 1, 2);
    renderGridLayout->addWidget(highlightContourLabel, 3, 0);
    renderGridLayout->addWidget(d_ptr->highlightContourCheckBox, 3, 1);
    //renderGridLayout->addWidget(highlightContourColorLabel, 3, 2);
    renderGridLayout->addWidget(fpsLabel, 4, 0);

    auto* fpsWidget = new QWidget(widget);
    auto* fpsLayout = new QHBoxLayout(fpsWidget);
    fpsLayout->setContentsMargins(0, 0, 0, 0);
    fpsLayout->addWidget(d_ptr->showFPSBtn);
    fpsLayout->addSpacing(5);
    fpsLayout->addWidget(d_ptr->hideFPSBtn);
    fpsLayout->addStretch();
    renderGridLayout->addWidget(fpsWidget, 4, 1, 1, 2);

    renderLayout->addLayout(renderGridLayout);
    renderLayout->addStretch();

    auto* objectDisplayWidget = new QWidget;
    auto* objectDisplayLayout = new QHBoxLayout(objectDisplayWidget);
    objectDisplayLayout->setContentsMargins(0, 0, 0, 0);

    auto* objectDisplayLabel = new QLabel(tr("对象显示模式"));
    objectDisplayLabel->setObjectName("objectDisplayMode_Label");

    d_ptr->faceBtn = new QPushButton;
    d_ptr->faceBtn->setObjectName("face_Button");
    d_ptr->faceBtn->setCheckable(true);
    d_ptr->faceBtn->setChecked(true);

    d_ptr->edgeBtn = new QPushButton;
    d_ptr->edgeBtn->setObjectName("edge_Button");
    d_ptr->edgeBtn->setCheckable(true);
    d_ptr->edgeBtn->setChecked(true);

    d_ptr->vertexBtn = new QPushButton;
    d_ptr->vertexBtn->setObjectName("vertex_Button");
    d_ptr->vertexBtn->setCheckable(true);
    d_ptr->vertexBtn->setChecked(false);

    objectDisplayLayout->addWidget(objectDisplayLabel);
    objectDisplayLayout->addSpacing(13);
    objectDisplayLayout->addWidget(d_ptr->faceBtn);
    objectDisplayLayout->addSpacing(5);
    objectDisplayLayout->addWidget(d_ptr->edgeBtn);
    objectDisplayLayout->addSpacing(5);
    objectDisplayLayout->addWidget(d_ptr->vertexBtn);
    objectDisplayLayout->addStretch();

    d_ptr->faceIconLabel = new QLabel(d_ptr->faceBtn);
    d_ptr->edgeIconLabel = new QLabel(d_ptr->edgeBtn);
    d_ptr->vertexIconLabel = new QLabel(d_ptr->vertexBtn);

    auto* faceTextLabel = new QLabel(d_ptr->faceBtn);
    faceTextLabel->setText(tr("面"));
    faceTextLabel->setObjectName("DisplayMode_Label");

    auto* edgeTextLabel = new QLabel(d_ptr->edgeBtn);
    edgeTextLabel->setText(tr("线"));
    edgeTextLabel->setObjectName("DisplayMode_Label");

    auto* vertexTextLabel = new QLabel(d_ptr->vertexBtn);
    vertexTextLabel->setText(tr("点"));
    vertexTextLabel->setObjectName("DisplayMode_Label");

    auto* faceButtonLayout = new QHBoxLayout(d_ptr->faceBtn);
    auto* edgeButtonLayout = new QHBoxLayout(d_ptr->edgeBtn);
    auto* vertexButtonLayout = new QHBoxLayout(d_ptr->vertexBtn);
    faceButtonLayout->setContentsMargins(0, 0, 0, 0);
    edgeButtonLayout->setContentsMargins(0, 0, 0, 0);
    vertexButtonLayout->setContentsMargins(0, 0, 0, 0);

    updateDisplayModeIcon();

    faceButtonLayout->addWidget(d_ptr->faceIconLabel);
    faceButtonLayout->addWidget(faceTextLabel);
    edgeButtonLayout->addWidget(d_ptr->edgeIconLabel);
    edgeButtonLayout->addWidget(edgeTextLabel);
    vertexButtonLayout->addWidget(d_ptr->vertexIconLabel);
    vertexButtonLayout->addWidget(vertexTextLabel);

    auto* axisWidget = new QWidget;
    auto* axisLayout = new QHBoxLayout(axisWidget);
    axisLayout->setContentsMargins(0, 0, 0, 0);

    auto* axisLabel = new QLabel(tr("操作轴"));
    axisLabel->setObjectName("operatingAxise_Label");

    d_ptr->showManipulatorAxisBtn = new QRadioButton;
    d_ptr->showManipulatorAxisBtn->setObjectName("displayOperatingAxise_Button");
    d_ptr->showManipulatorAxisBtn->setText(tr("显示"));
    d_ptr->showManipulatorAxisBtn->setFixedSize(65, 25);
    d_ptr->showManipulatorAxisBtn->setChecked(true);

    d_ptr->hideManipulatorAxisBtn = new QRadioButton;
    d_ptr->hideManipulatorAxisBtn->setObjectName("hideOperatingAxise_Button");
    d_ptr->hideManipulatorAxisBtn->setText(tr("隐藏"));
    d_ptr->hideManipulatorAxisBtn->setFixedSize(65, 25);

    auto* axisButtonGroup = new QButtonGroup(axisWidget);
    axisButtonGroup->addButton(d_ptr->showManipulatorAxisBtn);
    axisButtonGroup->addButton(d_ptr->hideManipulatorAxisBtn);

    axisLayout->addWidget(axisLabel);
    axisLayout->addSpacing(55);
    axisLayout->addWidget(d_ptr->showManipulatorAxisBtn);
    axisLayout->addSpacing(5);
    axisLayout->addWidget(d_ptr->hideManipulatorAxisBtn);
    axisLayout->addStretch();

    auto* highlightWidget = new QWidget;
    auto* highlightLayout = new QHBoxLayout(highlightWidget);
    highlightLayout->setContentsMargins(0, 0, 0, 0);

    auto* highlightTitleLabel = new QLabel(tr("实时高亮"));
    highlightTitleLabel->setObjectName("operatingAxise_Label");

    d_ptr->realtimeHighlightingBtn = new QRadioButton;
    d_ptr->realtimeHighlightingBtn->setObjectName("displayOperatingAxise_Button");
    d_ptr->realtimeHighlightingBtn->setText(tr("是"));
    d_ptr->realtimeHighlightingBtn->setFixedSize(65, 25);
    d_ptr->realtimeHighlightingBtn->setChecked(true);

    d_ptr->disableRealtimeHighlightingBtn = new QRadioButton;
    d_ptr->disableRealtimeHighlightingBtn->setObjectName("hideOperatingAxise_Button");
    d_ptr->disableRealtimeHighlightingBtn->setText(tr("否"));
    d_ptr->disableRealtimeHighlightingBtn->setFixedSize(65, 25);

    auto* highlightButtonGroup = new QButtonGroup(highlightWidget);
    highlightButtonGroup->addButton(d_ptr->realtimeHighlightingBtn);
    highlightButtonGroup->addButton(d_ptr->disableRealtimeHighlightingBtn);

    highlightLayout->addWidget(highlightTitleLabel);
    highlightLayout->addSpacing(40);
    highlightLayout->addWidget(d_ptr->realtimeHighlightingBtn);
    highlightLayout->addSpacing(5);
    highlightLayout->addWidget(d_ptr->disableRealtimeHighlightingBtn);
    highlightLayout->addStretch();

    auto* selectAllWidget = new QWidget;
    auto* selectAllLayout = new QHBoxLayout(selectAllWidget);
    selectAllLayout->setContentsMargins(0, 0, 0, 0);

    auto* selectAllLabel = new QLabel(tr("框选所有"));
    selectAllLabel->setObjectName("operatingAxise_Label");

    d_ptr->boxSelectAllBtn = new QRadioButton;
    d_ptr->boxSelectAllBtn->setObjectName("displayOperatingAxise_Button");
    d_ptr->boxSelectAllBtn->setText(tr("是"));
    d_ptr->boxSelectAllBtn->setFixedSize(65, 25);

    d_ptr->disableBoxSelectAllBtn = new QRadioButton;
    d_ptr->disableBoxSelectAllBtn->setObjectName("hideOperatingAxise_Button");
    d_ptr->disableBoxSelectAllBtn->setText(tr("否"));
    d_ptr->disableBoxSelectAllBtn->setFixedSize(65, 25);
    d_ptr->disableBoxSelectAllBtn->setChecked(true);

    auto* selectAllButtonGroup = new QButtonGroup(selectAllWidget);
    selectAllButtonGroup->addButton(d_ptr->boxSelectAllBtn);
    selectAllButtonGroup->addButton(d_ptr->disableBoxSelectAllBtn);

    selectAllLayout->addWidget(selectAllLabel);
    selectAllLayout->addSpacing(40);
    selectAllLayout->addWidget(d_ptr->boxSelectAllBtn);
    selectAllLayout->addSpacing(5);
    selectAllLayout->addWidget(d_ptr->disableBoxSelectAllBtn);
    selectAllLayout->addStretch();

    mainLayout->addWidget(sketchWidget);
    mainLayout->addSpacing(15);
    mainLayout->addLayout(renderLayout);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(objectDisplayWidget);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(axisWidget);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(highlightWidget);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(selectAllWidget);
    mainLayout->addSpacing(15);

    return widget;
}

QWidget* OptionsDlg::CreatePathSettingsWidget()
{
    QWidget* widget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(widget);

    QGroupBox* testCaseGroup = new QGroupBox(tr("测试用例模型路径"));
    testCaseGroup->setObjectName("testCaseModePathGroup");
    QVBoxLayout* testCaseLayout = new QVBoxLayout(testCaseGroup);

    d_ptr->testCasePathListWidget = new QListWidget;
    d_ptr->testCasePathListWidget->setObjectName("testCasePath_ListWidget");
    d_ptr->testCasePathListWidget->setFixedHeight(160);

    QHBoxLayout* testCaseButtonLayout = new QHBoxLayout;
    d_ptr->addTestCasePathBtn = new QPushButton(tr("新增"));
    d_ptr->addTestCasePathBtn->setObjectName("browseButton_addTestCasePath");
    d_ptr->addTestCasePathBtn->setIcon(QIcon(":/Option/add.png"));
    d_ptr->addTestCasePathBtn->setFixedSize(65, 25);
    d_ptr->deleteTestCasePathBtn = new QPushButton(tr("删除"));
    d_ptr->deleteTestCasePathBtn->setObjectName("browseButton_deleteTestCasePath");
    d_ptr->deleteTestCasePathBtn->setIcon(QIcon(":/Option/delete.png"));
    d_ptr->deleteTestCasePathBtn->setFixedSize(65, 25);
    testCaseButtonLayout->addWidget(d_ptr->addTestCasePathBtn);
    testCaseButtonLayout->addWidget(d_ptr->deleteTestCasePathBtn);
    testCaseButtonLayout->addStretch();

    testCaseLayout->addWidget(d_ptr->testCasePathListWidget);
    testCaseLayout->addLayout(testCaseButtonLayout);

    QGroupBox* pythonGroup = new QGroupBox(tr("Python 脚本设置"));
    pythonGroup->setObjectName("pythonScriptPathGroup");
    QFormLayout* pythonLayout = new QFormLayout(pythonGroup);

    QLabel* pythonScriptLabel = new QLabel(tr("Python脚本路径："), widget);
    pythonScriptLabel->setObjectName("pythonScriptPath_Label");

    QLabel* pythonPathLabel = new QLabel(tr("Python路径："), widget);
    pythonPathLabel->setObjectName("pythonPath_Label");

    d_ptr->pythonScriptPathLineEdit = new QLineEdit;
    d_ptr->pythonScriptPathLineEdit->setObjectName("pythonScriptPath_LineEdit");
    d_ptr->pythonScriptPathLineEdit->setReadOnly(true);
    d_ptr->pythonScriptPathBtn = new QPushButton(tr("浏览"));
    d_ptr->pythonScriptPathBtn->setObjectName("browseButton_pythonScriptPath");
    d_ptr->pythonScriptPathBtn->setFixedSize(65, 25);
    QHBoxLayout* scriptPathLayout = new QHBoxLayout;
    scriptPathLayout->addWidget(d_ptr->pythonScriptPathLineEdit);
    scriptPathLayout->addWidget(d_ptr->pythonScriptPathBtn);
    pythonLayout->addRow(pythonScriptLabel, scriptPathLayout);

    d_ptr->pythonPathLineEdit = new QLineEdit;
    d_ptr->pythonPathLineEdit->setObjectName("pythonPath_LineEdit");
    d_ptr->pythonPathLineEdit->setReadOnly(true);
    d_ptr->pythonPathBtn = new QPushButton(tr("浏览"));
    d_ptr->pythonPathBtn->setObjectName("browseButton_pythonPath");
    d_ptr->pythonPathBtn->setFixedSize(65, 25);
    QHBoxLayout* pythonPathLayout = new QHBoxLayout;
    pythonPathLayout->addWidget(d_ptr->pythonPathLineEdit);
    pythonPathLayout->addWidget(d_ptr->pythonPathBtn);
    pythonLayout->addRow(pythonPathLabel, pythonPathLayout);

    mainLayout->addWidget(testCaseGroup);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(pythonGroup);
    mainLayout->addStretch();

    return widget;
}

QWidget* OptionsDlg::CreateLoadingPluginsWidget()
{
    QWidget* widget         = new QWidget();
    QVBoxLayout* vBoxLayout = new QVBoxLayout(widget);
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(21);
    vBoxLayout->addLayout(gridLayout);

    QLabel* loadingPluginsLabel = new QLabel(tr("加载插件"), widget);
    loadingPluginsLabel->setObjectName("loadingPlugins_Label");

    d_ptr->treeWidget = new QTreeWidget(widget);
    d_ptr->treeWidget->setObjectName("tree_Widget");
    d_ptr->treeWidget->setColumnCount(1);
    d_ptr->treeWidget->setHeaderLabel("插件");
    d_ptr->treeWidget->header()->hide();

    QWidget* actionWidget         = new QWidget(widget);
    QVBoxLayout* vBoxActionLayout = new QVBoxLayout(actionWidget);
    vBoxActionLayout->setContentsMargins(6, 0, 6, 6);
    
    d_ptr->addLoadingPluginBtn    = new QPushButton(tr("新增"), widget);
    d_ptr->addLoadingPluginBtn->setObjectName("browseButton_addLoadingPlugins");
    d_ptr->addLoadingPluginBtn->setIcon(QIcon(":/Option/add.png"));
    d_ptr->addLoadingPluginBtn->setFixedSize(65, 25);

    d_ptr->deleteLoadingPluginBtn = new QPushButton(tr("删除"), widget);
    d_ptr->deleteLoadingPluginBtn->setObjectName("browseButton_deleteLoadingPlugins");
    d_ptr->deleteLoadingPluginBtn->setIcon(QIcon(":/Option/delete.png"));
    d_ptr->deleteLoadingPluginBtn->setFixedSize(65, 25);

    vBoxActionLayout->addWidget(d_ptr->addLoadingPluginBtn);
    vBoxActionLayout->addWidget(d_ptr->deleteLoadingPluginBtn);
    vBoxActionLayout->addStretch();

    gridLayout->addWidget(loadingPluginsLabel, 0, 0);
    gridLayout->addWidget(d_ptr->treeWidget, 1, 0);
    gridLayout->addWidget(actionWidget, 1, 1);

    return widget;
}

QWidget* OptionsDlg::CreateWindowWidget()
{
    QWidget* widget = new QWidget();
    QVBoxLayout* vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(8, 0, 0, 0);
    vBoxLayout->addSpacing(7);

    QLabel* consoleLabel = new QLabel(tr("控制台"), widget);
    consoleLabel->setObjectName("console_Label");
    consoleLabel->resize(100, 30);
    vBoxLayout->addWidget(consoleLabel);

    auto consoleBtnPair = createRadioButtonPair(widget, tr("显示"), tr("隐藏"));
    d_ptr->showConsoleBtn = consoleBtnPair.first;
    d_ptr->hideConsoleBtn = consoleBtnPair.second;
    auto consoleButtonGroup = new QButtonGroup(this);
    consoleButtonGroup->addButton(d_ptr->showConsoleBtn);
    consoleButtonGroup->addButton(d_ptr->hideConsoleBtn);

    QHBoxLayout* showConsoleHLayout = new QHBoxLayout;
    showConsoleHLayout->addWidget(d_ptr->showConsoleBtn);
    showConsoleHLayout->addWidget(d_ptr->hideConsoleBtn);
    showConsoleHLayout->addStretch();
    vBoxLayout->addLayout(showConsoleHLayout);

    QLabel* scriptEditorLabel = new QLabel(tr("脚本编辑器"), widget);
    scriptEditorLabel->setObjectName("scriptEditor_Label");
    scriptEditorLabel->resize(100, 30);
    vBoxLayout->addWidget(scriptEditorLabel);

    auto scriptEditorBtnPair = createRadioButtonPair(widget, tr("显示"), tr("隐藏"));
    d_ptr->showScriptEditorBtn = scriptEditorBtnPair.first;
    d_ptr->hideScriptEditorBtn = scriptEditorBtnPair.second;
    auto editorButtonGroup = new QButtonGroup(this);
    editorButtonGroup->addButton(d_ptr->showScriptEditorBtn);
    editorButtonGroup->addButton(d_ptr->hideScriptEditorBtn);
    QHBoxLayout* showEditorHLayout = new QHBoxLayout;
    showEditorHLayout->addWidget(d_ptr->showScriptEditorBtn);
    showEditorHLayout->addWidget(d_ptr->hideScriptEditorBtn);
    showEditorHLayout->addStretch();
    vBoxLayout->addLayout(showEditorHLayout);

    vBoxLayout->addStretch();
    return widget;
}

QWidget* OptionsDlg::CreateBackupsWidget()
{
    QWidget* backupsWidget = new QWidget();
    QVBoxLayout* vBoxLayout = new QVBoxLayout(backupsWidget);
    vBoxLayout->setContentsMargins(8, 0, 0, 0);

    QHBoxLayout* enableBackupHLayout = new QHBoxLayout;
    vBoxLayout->addLayout(enableBackupHLayout);
    QLabel* backupsLabel = new QLabel(tr("是否开启备份："), backupsWidget);
    backupsLabel->setObjectName("openOrCloseBackups_Label");
    backupsLabel->resize(100, 30);
    auto buttonPair = createRadioButtonPair(backupsWidget, tr("开启"), tr("不开启"), 70);
    d_ptr->backupBtn = buttonPair.first;
    d_ptr->disableBackupBtn = buttonPair.second;
    d_ptr->backupBtn->setObjectName("openBackups_Button");
    d_ptr->disableBackupBtn->setObjectName("closeBackups_Button");
    enableBackupHLayout->addWidget(backupsLabel);
    enableBackupHLayout->addWidget(d_ptr->backupBtn);
    enableBackupHLayout->addWidget(d_ptr->disableBackupBtn);
    enableBackupHLayout->addStretch();

    QLabel* backupIntervalLabel = new QLabel(tr("备份时间间隔"), backupsWidget);
    backupIntervalLabel->setObjectName("backupInterval_Label");
    backupIntervalLabel->setFixedSize(100, 40);
    vBoxLayout->addWidget(backupIntervalLabel);

    d_ptr->timeLineEdit = new QLineEdit(backupsWidget);
    d_ptr->timeLineEdit->setObjectName("time_LineEdit");
    d_ptr->timeLineEdit->setFixedSize(50, 25);
    QLabel* timeLabel = new QLabel(backupsWidget);
    timeLabel->setObjectName("time_Label");
    timeLabel->setText(tr("分钟"));

    QHBoxLayout* backupIntervalSettingHLayout = new QHBoxLayout;
    backupIntervalSettingHLayout->addWidget(d_ptr->timeLineEdit);
    backupIntervalSettingHLayout->addWidget(timeLabel);
    backupIntervalSettingHLayout->addStretch();
    vBoxLayout->addLayout(backupIntervalSettingHLayout);

    QLabel* backupPathLabel = new QLabel(tr("备份路径"), backupsWidget);
    backupPathLabel->setObjectName("backupPath_Label");
    backupPathLabel->setFixedSize(100, 40);
    vBoxLayout->addWidget(backupPathLabel);

    QLabel* pathLabel = new QLabel(tr("路径选择："), backupsWidget);
    pathLabel->setObjectName("PathSelect_Label");
    pathLabel->resize(100, 30);
    d_ptr->backupPathLineEdit = new QLineEdit(backupsWidget);
    d_ptr->backupPathLineEdit->setObjectName("backupPath_LineEdit");
    d_ptr->backupPathLineEdit->setReadOnly(true);
    d_ptr->backupPathBtn = new QPushButton(tr("浏览"), backupsWidget);
    d_ptr->backupPathBtn->setFixedSize(55, 25);
    d_ptr->backupPathBtn->setObjectName("browseButton_backupPath");
    QHBoxLayout* pathSelectHLayout = new QHBoxLayout;
    pathSelectHLayout->addWidget(pathLabel);
    pathSelectHLayout->addWidget(d_ptr->backupPathLineEdit);
    pathSelectHLayout->addWidget(d_ptr->backupPathBtn);
    vBoxLayout->addLayout(pathSelectHLayout);
    vBoxLayout->addStretch();
    return backupsWidget;
}

bool OptionsDlg::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        auto* mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint clickPos = mouseEvent->globalPos();
        QPoint widgetPos = d_ptr->colorWidget->mapToGlobal(QPoint(0, 0));
        QRect widgetRect = QRect(widgetPos, d_ptr->colorWidget->size());

        if (obj == d_ptr->modelColorPreviewWidget && d_ptr->colorWidget->isVisible()) {
            return true;
        }

        if (obj->objectName() == "CADEnvironmentSettingsWidget" && !widgetRect.contains(clickPos)) {
            d_ptr->colorWidget->hide();
        }

        if (!widgetRect.contains(clickPos)) {
            d_ptr->colorWidget->hide();
        }
    }
    return QDialog::eventFilter(obj, event);
}

