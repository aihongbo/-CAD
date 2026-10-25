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

#pragma once

#include <QWidget> // Required for inheritance

class QSyntaxStyle;

namespace NCTI
{
    class CodeEditor;
    class LineNumberArea : public QWidget
	{
		Q_OBJECT
    public:
        /**
            * @brief Constructor.
            * @param parent Pointer to parent QTextEdit widget.
            */
        explicit LineNumberArea(CodeEditor* parent = nullptr);

        // Disable copying
        LineNumberArea(const LineNumberArea&) = delete;
        LineNumberArea& operator=(const LineNumberArea&) = delete;

        /**
         * @brief Overridden method for getting line number area
         * size.
         */
        QSize sizeHint() const override;

        /**
         * @brief Method for setting syntax style object.
         * @param style Pointer to syntax style.
         */
        void setSyntaxStyle(QSyntaxStyle* style);

        /**
         * @brief Method for getting syntax style.
         * @return Pointer to syntax style.
         */
        QSyntaxStyle* syntaxStyle() const;

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        void setCurrentBlockNumber(int number);

    private:

        QSyntaxStyle* m_syntaxStyle;

        CodeEditor* m_codeEditParent;

        int m_currentBlockNumber;
	};
};