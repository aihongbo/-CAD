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

// Qt
#include <QTextEdit> // Required for inheritance

class QCompleter;
class QSyntaxStyle;
class QStyleSyntaxHighlighter;
class QFramedTextAttribute;

namespace NCTI
{

    /**
     * @brief Class, that describes code editor.
     */
    class LineNumberArea;
    class BreakpointArea;
    class CodeCompleter;
    class CodeEditor : public QTextEdit
    {
        Q_OBJECT

    public:
        /**
         * @brief Constructor.
         * @param widget Pointer to parent widget.
         */
        explicit CodeEditor(QWidget* widget = nullptr);

        // Disable copying
        CodeEditor(const CodeEditor&) = delete;
        CodeEditor& operator=(const CodeEditor&) = delete;
       
        Q_SIGNAL void sigScrollToTopStateChanged(bool available);
        Q_SIGNAL void sigScrollToBottomStateChanged(bool available);
        Q_SLOT void scrollToTop();
        Q_SLOT void scrollToBottom();

        /**
         * @brief Method for getting first visible block
         * index.
         * @return Index.
         */
        int getFirstVisibleBlock();

        /**
         * @brief Method for setting highlighter.
         * @param highlighter Pointer to syntax highlighter.
         */
        void setHighlighter(QStyleSyntaxHighlighter* highlighter);

        /**
         * @brief Method for setting syntax sty.e.
         * @param style Pointer to syntax style.
         */
        void setSyntaxStyle(QSyntaxStyle* style);
        enum CodeStyle {
            Dark,
            Light,
        };
        void setDefaultSyntaxStyle(CodeStyle style);

        /**
         * @brief Method setting auto parentheses enabled.
         */
        void setAutoParentheses(bool enabled);

        /**
         * @brief Method for getting is auto parentheses enabled.
         * Default value: true
         */
        bool autoParentheses() const;

        /**
         * @brief Method for setting tab replacing
         * enabled.
         */
        void setTabReplace(bool enabled);

        /**
         * @brief Method for getting is tab replacing enabled.
         * Default value: true
         */
        bool tabReplace() const;

        /**
         * @brief Method for setting amount of spaces, that will
         * replace tab.
         * @param val Number of spaces.
         */
        void setTabReplaceSize(int val);

        /**
         * @brief Method for getting number of spaces, that will
         * replace tab if `tabReplace` is true.
         * Default: 4
         */
        int tabReplaceSize() const;

        /**
         * @brief Method for setting auto indentation enabled.
         */
        void setAutoIndentation(bool enabled);

        /**
         * @brief Method for getting is auto indentation enabled.
         * Default: true
         */
        bool autoIndentation() const;

        /*Q_SIGNAL void sigBreakpointClicked(int blockNumber);
        void setCurrentBreakpoint(int number);
        void addBreakpoint(int blockNumber);
        void removeBreakpoint(int blockNumber);
        void clearBreakpoint();*/
        BreakpointArea* getBreakpointArea() { return m_breakpointArea; }



    public Q_SLOTS:

        /**
         * @brief Slot, that performs insertion of
         * completion info into code.
         * @param s Data.
         */
        void insertCompletion(QString s);
        void insertCompletion(QString s, int from, int len);

        /**
         * @brief Slot, that performs update of
         * internal editor viewport based on line
         * number area width.
         */
        void updateLineNumberAreaWidth(int);

        /**
         * @brief Slot, that performs update of some
         * part of line number area.
         * @param rect Area that has to be updated.
         */
        void updateLineNumberArea(const QRect& rect);

        /**
         * @brief Slot, that will proceed extra selection
         * for current cursor position.
         */
        void updateExtraSelection();

        /**
         * @brief Slot, that will update editor style.
         */
        void updateStyle();

        /**
         * @brief Slot, that will be called on selection
         * change.
         */
        void onSelectionChanged();

    protected:
        /**
         * @brief Method, that's called on any text insertion of
         * mimedata into editor. If it's text - it inserts text
         * as plain text.
         */
        void insertFromMimeData(const QMimeData* source) override;

        /**
         * @brief Method, that's called on editor painting. This
         * method if overloaded for line number area redraw.
         */
        void paintEvent(QPaintEvent* e) override;

        /**
         * @brief Method, that's called on any widget resize.
         * This method if overloaded for line number area
         * resizing.
         */
        void resizeEvent(QResizeEvent* e) override;

        /**
         * @brief Method, that's called on any key press, posted
         * into code editor widget. This method is overloaded for:
         *
         * 1. Completion
         * 2. Tab to spaces
         * 3. Low indentation
         * 4. Auto parenthesis
         */
        void keyPressEvent(QKeyEvent* e) override;

        /**
         * @brief Method, that's called on focus into widget.
         * It's required for setting this widget to set
         * completer.
         */
        void focusInEvent(QFocusEvent* e) override;

        void wheelEvent(QWheelEvent* e) override;
        void contextMenuEvent(QContextMenuEvent* event) override;

    private:

        /**
         * @brief Method for initializing document
         * layout handlers.
         */
        void initDocumentLayoutHandlers();

        /**
         * @brief Method for initializing default
         * monospace font.
         */
        void initFont();

        /**
         * @brief Method for performing connection
         * of objects.
         */
        void performConnections();

        /**
         * @brief Method, that performs selection
         * frame selection.
         */
        void handleSelectionQuery(QTextCursor cursor);

        /**
         * @brief Method for updating geometry of line number area.
         */
        void updateLineGeometry();

        /**
         * @brief Method for getting character under
         * cursor.
         * @param offset Offset to cursor.
         */
        QChar charUnderCursor(int offset = 0) const;

        /**
         * @brief Method for getting word under
         * cursor.
         * @return Word under cursor.
         */
        QString wordUnderCursor() const;

        /**
         * @brief Method, that adds highlighting of
         * currently selected line to extra selection list.
         */
        void highlightCurrentLine(QList<QTextEdit::ExtraSelection>& extraSelection);

        /**
         * @brief Method, that adds highlighting of
         * parenthesis if available.
         */
        void highlightParenthesis(QList<QTextEdit::ExtraSelection>& extraSelection);

        /**
         * @brief Method for getting number of indentation
         * spaces in current line. Tabs will be treated
         * as `tabWidth / spaceWidth`
         */
        int getIndentationSpaces();

        Q_SLOT void onScrollRangeChanged(int min, int max);
        Q_SLOT void onScrollValueChanged(int value);

        QStyleSyntaxHighlighter* m_highlighter;
        QSyntaxStyle* m_syntaxStyle;
        LineNumberArea* m_lineNumberArea;
        BreakpointArea* m_breakpointArea;
        CodeCompleter* m_completer;
        //QCompleter* m_completer;

        QFramedTextAttribute* m_framedAttribute;

        bool m_autoIndentation;
        bool m_autoParentheses;
        bool m_replaceTab;
        QString m_tabReplace;
    };
};

