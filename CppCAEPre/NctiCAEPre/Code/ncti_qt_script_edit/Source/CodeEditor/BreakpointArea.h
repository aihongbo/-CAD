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

#include <QWidget>

class QSyntaxStyle;

namespace NCTI
{
	class CodeEditor;
	class BreakpointArea : public QWidget
	{
        Q_OBJECT
	public:
        explicit BreakpointArea(CodeEditor *codeEditor);

        QSize sizeHint() const override;

        void setSyntaxStyle(QSyntaxStyle* style);
        QSyntaxStyle* syntaxStyle() const;

        void setCurrentBlockNumber(int blockNumber);
        bool containsBreakpoint(int blockNumber) const;
        void addBreakpoint(int blockNumber, bool enable);
        void removeBreakpoint(int blockNumber);
        void clearBreakpoint();
        void enableBreakpoint(int blockNumber, bool enable);
        void enableAllBreakpoint(bool enable);
        bool isEnableBreakpoint(int blockNumber);
    
    Q_SIGNALS:
        void sigClicked(int blockNumber, int button);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
#if QT_VERSION_MAJOR >= 6
        void enterEvent(QEnterEvent* event) override;
#else
        void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;

        void setHoverBlockNumber(int number);

    private:
        struct Breakpoint
        {
            int blockNumber;
            bool enable;
        };
        QList<Breakpoint>::Iterator findBreakpoint(int blockNumber);

	private:
		Q_DISABLE_COPY_MOVE(BreakpointArea);

		QSyntaxStyle* m_syntaxStyle;
		CodeEditor* m_codeEditParent;
		int m_currentBlockNumber;
        int m_hoverBlockNumber;
        QList<Breakpoint> m_breakpointList;
	};
}