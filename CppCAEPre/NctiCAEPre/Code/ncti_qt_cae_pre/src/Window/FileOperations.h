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

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#pragma once

#include "MainWindowModules.h"
#include "ncti_base.h"

class QFileDialog;
namespace NCTI {

    /**
     * @brief 文件对话框类型枚举
     */
        enum DialogType {
            Unknown,
            OpenDialog,      ///< 打开文件对话框
            SaveDialog,      ///< 保存文件对话框
            SaveAsDialog,    ///< 另存为对话框
            ImportDialog,    ///< 导入文件对话框
            ExportDialog,    ///< 导出文件对话框
            ScriptSaveDialog ///< 脚本保存对话框
        };

	/**
	 * @brief 文件操作类
	 * @details 处理文件相关的操作，包括打开、保存、导入、导出等
	 */
	class FileOperations : public MainWindowModule
	{
		Q_OBJECT

	public:
		/**
		 * @brief 构造函数
		 * @param mainWindow 主窗口指针
		 */
		explicit FileOperations(MainWindow* mainWindow);

		/**
		 * @brief 模块初始化，在这里处理主窗口的信号
		 */
		void initialize() override;

	public Q_SLOTS:
		/**
		 * @brief 打开NCTI文件槽函数
		 * @param filePath 文件路径
		 */
		void onOpenNcti(const QString& filePath = "");
		
		/**
		 * @brief 保存NCTI文件槽函数
		 */
		void onSaveNcti();
		
		/**
		 * @brief 另存为NCTI文件槽函数
		 */
        void onSaveAsNcti();

		/**
		 * @brief 关闭文档槽函数
		 */
		void onCloseDocument();
		
		/**
		 * @brief 新建装配体槽函数
		 */
        void onNewAssembly();
        void newAssembly(EnumModelDoc geo, EnumGCSDoc cs, EnumMeshDoc mesh);
		
		/**
		 * @brief 添加装配体槽函数
		 */
		void onAddAssembly();
		
		/**
		 * @brief 添加零件槽函数
		 */
		void onAddPart();
		
		/**
		 * @brief 导入装配体或零件槽函数
		 */
		void onImportAssemblyOrPart();
		
		/**
		 * @brief 移除装配体或零件槽函数
		 */
		void onRemoveAssemblyOrPart();
		
        /**
		 * @brief 新建零件槽函数
		 */
        void onNewPart();
        void newPart(EnumModelDoc geo, EnumGCSDoc cs, EnumMeshDoc mesh);
		
		/**
		 * @brief 导入模型槽函数
		 */
		void onImportModel();

        void importModels(const QStringList& filePaths);
		
		/**
		 * @brief 导出模型槽函数
		 */
		void onExportModel();

		/**
		 * @brief 撤销操作槽函数
		 */
		void onUndo();
		
		/**
		 * @brief 重做操作槽函数
		 */
		void onRedo();
		
		/**
		 * @brief 删除操作槽函数
		 */
		void onDelete();
		
		/**
		 * @brief 开始录制槽函数
		 */
		void onStartRecord();
		
		/**
		 * @brief 结束录制槽函数
		 */
		void onEndRecord();

		/**
		 * @brief 运行脚本槽函数
		 */
		void onScriptRun();
		
		/**
		 * @brief 批量运行脚本槽函数
		 */
		void onBatchScriptRun();
		
		/**
		 * @brief 多核批量运行脚本槽函数
		 */
		void onMulticoreBatchScriptRun();

		/**
		 * @brief 参数测试槽函数
		 */
		void onParamTest();

	private:
        /**
         * @brief 获取打开文件路径
         * @return 文件路径
         */
        QString getFilePathOnOpen();

        /**
         * @brief 获取保存文件路径
         * @return 文件路径
         */
        QString getFilePathOnSave();

        /**
         * @brief 获取另存为文件路径
         * @return 文件路径
         */
        QString getFilePathOnSaveAs();

        /**
         * @brief 获取导入文件路径
         * @return 文件路径列表
         */
        QStringList getFilePathOnImport();

        /**
         * @brief 获取导出文件路径
         * @return 文件路径
         */
        QString getFilePathOnExport();

        /**
        * @brief 显示模态文件对话框
        */
        void showModelDialog(DialogType type, const QString& key, const QString& title, const QString& filter);

	    /**
	     * @brief 显示非模态文件对话框
	     */
	    void showModelessDialog(DialogType type, const QString& key, const QString& title, const QString& filter);

	    /**
	     * @brief 处理选择的文件
	     */
	    void handleSelectedFiles(DialogType dialogType, const QStringList& files);

        /**
         * @brief 加载ncti文件
         */
        void loadNctiFile(const QString& filePath);
    private Q_SLOTS:
	    /**
	     * @brief 处理文件对话框完成信号
	     */
	    void onFileDialogFinished(int result);

    private:
        DialogType m_currentDialogType{DialogType::Unknown}; ///< 当前对话框类型
	    QString m_currentDirectoryKey;      ///< 当前目录键名
	    QFileDialog* m_fileDialog{nullptr}; ///< 文件对话框指针
	
	    bool m_isRecording{false}; ///< 是否录制中标记
        QString m_statusText;
};

} // namespace NCTI

#endif // FILE_OPERATIONS_H