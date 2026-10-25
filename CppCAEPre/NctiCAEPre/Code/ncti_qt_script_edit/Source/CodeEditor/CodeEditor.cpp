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

// CodeEditor
#include "CodeEditor.h"
#include "LineNumberArea.h"
#include "BreakpointArea.h"
#include "CodeCompleter.h"
#include <QSyntaxStyle>
#include <QStyleSyntaxHighlighter>
#include <QFramedTextAttribute>
#include <QCXXHighlighter>
#include <QPythonHighlighter>

// Qt
#include <QTextBlock>
#include <QPaintEvent>
#include <QFontDatabase>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>
#include <QTextCharFormat>
#include <QCompleter>
#include <QAbstractItemView>
#include <QMimeData>
#include <QApplication>
#include <QMenu>
#include <QFile>

static QVector<QPair<QString, QString>> parentheses = {
    /*{"(", ")"},
    {"{", "}"},
    {"[", "]"},
    {"\"", "\""},
    {"'", "'"}*/
};

using namespace NCTI;

CodeEditor::CodeEditor(QWidget* widget) :
    QTextEdit(widget),
    m_highlighter(nullptr),
    m_syntaxStyle(nullptr),
    m_lineNumberArea(new LineNumberArea(this)),
    m_breakpointArea(new BreakpointArea(this)),
    m_completer(new CodeCompleter(":/code_completer.json",this)),
    m_framedAttribute(new QFramedTextAttribute(this)),
    m_autoIndentation(true),
    m_autoParentheses(true),
    m_replaceTab(true),
    m_tabReplace(QString(4, ' '))
{
    //connect(m_breakpointArea, &BreakpointArea::sigClicked, this, &CodeEditor::sigBreakpointClicked);
    initDocumentLayoutHandlers();
    initFont();
    performConnections();

    setSyntaxStyle(QSyntaxStyle::defaultStyle());

    connect(
        m_completer,
        QOverload<QString, int, int>::of(&CodeCompleter::sigActivated),
        this,
        QOverload<QString, int, int>::of(&CodeEditor::insertCompletion)
    );
}

void CodeEditor::initDocumentLayoutHandlers()
{
    document()
        ->documentLayout()
        ->registerHandler(
            QFramedTextAttribute::type(),
            m_framedAttribute
        );
}

void CodeEditor::initFont()
{
    auto fnt = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fnt.setFixedPitch(true);
    fnt.setPointSize(10);

    setFont(fnt);
}

void CodeEditor::performConnections()
{
    connect(
        document(),
        &QTextDocument::blockCountChanged,
        this,
        &CodeEditor::updateLineNumberAreaWidth
    );

    connect(
        verticalScrollBar(),
        &QScrollBar::valueChanged,
        [this](int) { m_lineNumberArea->update(); m_breakpointArea->update(); }
    );

    connect(
        this,
        &QTextEdit::cursorPositionChanged,
        this,
        &CodeEditor::updateExtraSelection
    );

    connect(
        this,
        &QTextEdit::selectionChanged,
        this,
        &CodeEditor::onSelectionChanged
    );

    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CodeEditor::onScrollValueChanged);
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &CodeEditor::onScrollRangeChanged);
}

void CodeEditor::setHighlighter(QStyleSyntaxHighlighter* highlighter)
{
    if (m_highlighter)
    {
        m_highlighter->setDocument(nullptr);
    }

    m_highlighter = highlighter;

    if (m_highlighter)
    {
        m_highlighter->setSyntaxStyle(m_syntaxStyle);
        m_highlighter->setDocument(document());
    }
}

void CodeEditor::setSyntaxStyle(QSyntaxStyle* style)
{
    m_syntaxStyle = style;

    m_framedAttribute->setSyntaxStyle(m_syntaxStyle);
    m_lineNumberArea->setSyntaxStyle(m_syntaxStyle);
    m_breakpointArea->setSyntaxStyle(m_syntaxStyle);

    if (m_highlighter)
    {
        m_highlighter->setSyntaxStyle(m_syntaxStyle);
    }

    updateStyle();
}
void CodeEditor::setDefaultSyntaxStyle(CodeStyle style)
{
    setHighlighter(new QPythonHighlighter);
    QString path;
    if (style == CodeStyle::Dark) {
        path = ":/code_style_dark.xml";
    }
    else if (style == CodeStyle::Light) {
        path = ":/code_style_light.xml";
    }
    else {

    }
    
    QFile file(path);
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        auto style = new QSyntaxStyle(this);
        style->load(file.readAll());
        if (style->isLoaded())
        {
            setSyntaxStyle(style);
        }
        file.close();
    }
}

void CodeEditor::updateStyle()
{
    if (m_highlighter)
    {
        m_highlighter->rehighlight();
    }

    if (m_syntaxStyle)
    {
        auto currentPalette = palette();

        // Setting text format/color
        currentPalette.setColor(
            QPalette::ColorRole::Text,
            m_syntaxStyle->getFormat("Text").foreground().color()
        );

        // Setting common background
        currentPalette.setColor(
            QPalette::Base,
            m_syntaxStyle->getFormat("Text").background().color()
        );

        // Setting selection color
        currentPalette.setColor(
            QPalette::Highlight,
            m_syntaxStyle->getFormat("Selection").background().color()
        );

        setPalette(currentPalette);
    }

    updateExtraSelection();
}

void CodeEditor::onSelectionChanged()
{
    /* 暂不使用 */
    //auto selected = textCursor().selectedText();

    //auto cursor = textCursor();

    //// Cursor is null if setPlainText was called.
    //if (cursor.isNull())
    //{
    //    return;
    //}

    //cursor.movePosition(QTextCursor::MoveOperation::Left);
    //cursor.select(QTextCursor::SelectionType::WordUnderCursor);

    //QSignalBlocker blocker(this);
    //m_framedAttribute->clear(cursor);

    //if (selected.size() > 1 &&
    //    cursor.selectedText() == selected)
    //{
    //    auto backup = textCursor();

    //    // Perform search selecting
    //    handleSelectionQuery(cursor);

    //    setTextCursor(backup);
    //}
}

void CodeEditor::resizeEvent(QResizeEvent* e)
{
    QTextEdit::resizeEvent(e);

    updateLineGeometry();
}

void CodeEditor::updateLineGeometry()
{
    QRect cr = contentsRect();
    m_breakpointArea->setGeometry(
        QRect(cr.left(),
            cr.top(),
            m_breakpointArea->sizeHint().width(),
            cr.height()
        )
    );
    m_lineNumberArea->setGeometry(
        QRect(cr.left()+ m_breakpointArea->sizeHint().width(),
            cr.top(),
            m_lineNumberArea->sizeHint().width(),
            cr.height()
        )
    );
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(m_breakpointArea->sizeHint().width()+m_lineNumberArea->sizeHint().width(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect)
{
    m_breakpointArea->update(
        0,
        rect.y(),
        m_breakpointArea->sizeHint().width(),
        rect.height()
    );

    m_lineNumberArea->update(
        0,
        rect.y(),
        m_lineNumberArea->sizeHint().width(),
        rect.height()
    );
    updateLineGeometry();

    if (rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth(0);
    }
}

void CodeEditor::handleSelectionQuery(QTextCursor cursor)
{

    auto searchIterator = cursor;
    searchIterator.movePosition(QTextCursor::Start);
    searchIterator = document()->find(cursor.selectedText(), searchIterator);
    while (searchIterator.hasSelection())
    {
        m_framedAttribute->frame(searchIterator);

        searchIterator = document()->find(cursor.selectedText(), searchIterator);
    }
}

void CodeEditor::updateExtraSelection()
{
    QList<QTextEdit::ExtraSelection> extra;

    highlightCurrentLine(extra);
    highlightParenthesis(extra);

    setExtraSelections(extra);
}

void CodeEditor::highlightParenthesis(QList<QTextEdit::ExtraSelection>& extraSelection)
{
    auto currentSymbol = charUnderCursor();
    auto prevSymbol = charUnderCursor(-1);

    for (auto& pair : parentheses)
    {
        int direction;

        QChar counterSymbol;
        QChar activeSymbol;
        auto position = textCursor().position();

        if (pair.first == currentSymbol)
        {
            direction = 1;
            counterSymbol = pair.second[0];
            activeSymbol = currentSymbol;
        }
        else if (pair.second == prevSymbol)
        {
            direction = -1;
            counterSymbol = pair.first[0];
            activeSymbol = prevSymbol;
            position--;
        }
        else
        {
            continue;
        }

        auto counter = 1;

        while (counter != 0 &&
            position > 0 &&
            position < (document()->characterCount() - 1))
        {
            // Moving position
            position += direction;

            auto character = document()->characterAt(position);
            // Checking symbol under position
            if (character == activeSymbol)
            {
                ++counter;
            }
            else if (character == counterSymbol)
            {
                --counter;
            }
        }

        auto format = m_syntaxStyle->getFormat("Parentheses");

        // Found
        if (counter == 0)
        {
            ExtraSelection selection{};

            auto directionEnum =
                direction < 0 ?
                QTextCursor::MoveOperation::Left
                :
                QTextCursor::MoveOperation::Right;

            selection.format = format;
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            selection.cursor.movePosition(
                directionEnum,
                QTextCursor::MoveMode::MoveAnchor,
                std::abs(textCursor().position() - position)
            );

            selection.cursor.movePosition(
                QTextCursor::MoveOperation::Right,
                QTextCursor::MoveMode::KeepAnchor,
                1
            );

            extraSelection.append(selection);

            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            selection.cursor.movePosition(
                directionEnum,
                QTextCursor::MoveMode::KeepAnchor,
                1
            );

            extraSelection.append(selection);
        }

        break;
    }
}

void CodeEditor::highlightCurrentLine(QList<QTextEdit::ExtraSelection>& extraSelection)
{
    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection{};

        selection.format = m_syntaxStyle->getFormat("CurrentLine");
        selection.format.setForeground(QBrush());
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();

        extraSelection.append(selection);
    }
}

void CodeEditor::paintEvent(QPaintEvent* e)
{
    updateLineNumberArea(e->rect());
    QTextEdit::paintEvent(e);
}

int CodeEditor::getFirstVisibleBlock()
{
    // Detect the first block for which bounding rect - once translated
    // in absolute coordinated - is contained by the editor's text area

    // Costly way of doing but since "blockBoundingGeometry(...)" doesn't
    // exists for "QTextEdit"...

    QTextCursor curs = QTextCursor(document());
    curs.movePosition(QTextCursor::Start);
    for (int i = 0; i < document()->blockCount(); ++i)
    {
        QTextBlock block = curs.block();

        QRect r1 = viewport()->geometry();
        QRect r2 = document()
            ->documentLayout()
            ->blockBoundingRect(block)
            .translated(
                viewport()->geometry().x(),
                viewport()->geometry().y() - verticalScrollBar()->sliderPosition()
            ).toRect();

        if (r1.intersects(r2))
        {
            return i;
        }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}

void CodeEditor::keyPressEvent(QKeyEvent* e) {
#if QT_VERSION >= 0x050A00
    const int defaultIndent = tabStopDistance() / fontMetrics().averageCharWidth();
#else
    const int defaultIndent = tabStopWidth() / fontMetrics().averageCharWidth();
#endif


    if (m_replaceTab && e->key() == Qt::Key_Tab &&
        e->modifiers() == Qt::NoModifier) {
        insertPlainText(m_tabReplace);
        return;
    }

    // Auto indentation
    int indentationLevel = getIndentationSpaces();

#if QT_VERSION >= 0x050A00
    int tabCounts =
        indentationLevel * fontMetrics().averageCharWidth() / tabStopDistance();
#else
    int tabCounts =
        indentationLevel * fontMetrics().averageCharWidth() / tabStopWidth();
#endif

    // Have Qt Edior like behaviour, if {|} and enter is pressed indent the two
    // parenthesis
    if (m_autoIndentation &&
        (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) &&
        charUnderCursor() == '}' && charUnderCursor(-1) == '{')
    {
        int charsBack = 0;
        insertPlainText("\n");

        if (m_replaceTab)
            insertPlainText(QString(indentationLevel + defaultIndent, ' '));
        else
            insertPlainText(QString(tabCounts + 1, '\t'));

        insertPlainText("\n");
        charsBack++;

        if (m_replaceTab)
        {
            insertPlainText(QString(indentationLevel, ' '));
            charsBack += indentationLevel;
        }
        else
        {
            insertPlainText(QString(tabCounts, '\t'));
            charsBack += tabCounts;
        }

        while (charsBack--)
            moveCursor(QTextCursor::MoveOperation::Left);
        return;
    }

    // Shortcut for moving line to left
    if (m_replaceTab && e->key() == Qt::Key_Backtab) {
        indentationLevel = std::min<int>(indentationLevel, m_tabReplace.size());

        auto cursor = textCursor();

        cursor.movePosition(QTextCursor::MoveOperation::StartOfLine);
        cursor.movePosition(QTextCursor::MoveOperation::Right,
            QTextCursor::MoveMode::KeepAnchor, indentationLevel);

        cursor.removeSelectedText();
        return;
    }

    QTextEdit::keyPressEvent(e);

    if (m_autoIndentation && (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)) {
        if (m_replaceTab)
            insertPlainText(QString(indentationLevel, ' '));
        else
            insertPlainText(QString(tabCounts, '\t'));
    }

    if (m_autoParentheses)
    {
        for (auto&& el : parentheses)
        {
            // Inserting closed brace
            if (el.first == e->text())
            {
                insertPlainText(el.second);
                moveCursor(QTextCursor::MoveOperation::Left);
                break;
            }

            // If it's close brace - check parentheses
            if (el.second == e->text())
            {
                auto symbol = charUnderCursor();

                if (symbol == el.second)
                {
                    textCursor().deletePreviousChar();
                    moveCursor(QTextCursor::MoveOperation::Right);
                }

                break;
            }
        }
    }
}

void CodeEditor::setAutoIndentation(bool enabled)
{
    m_autoIndentation = enabled;
}

bool CodeEditor::autoIndentation() const
{
    return m_autoIndentation;
}

void CodeEditor::setAutoParentheses(bool enabled)
{
    m_autoParentheses = enabled;
}

bool CodeEditor::autoParentheses() const
{
    return m_autoParentheses;
}

void CodeEditor::setTabReplace(bool enabled)
{
    m_replaceTab = enabled;
}

bool CodeEditor::tabReplace() const
{
    return m_replaceTab;
}

void CodeEditor::setTabReplaceSize(int val)
{
    m_tabReplace.clear();

    m_tabReplace.fill(' ', val);
}

int CodeEditor::tabReplaceSize() const
{
    return m_tabReplace.size();
}

void CodeEditor::focusInEvent(QFocusEvent* e)
{
    QTextEdit::focusInEvent(e);
}

void CodeEditor::wheelEvent(QWheelEvent* e)
{
    if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        int delta = e->angleDelta().y();
        if (delta > 0) {
            zoomIn();
        }
        else {
            zoomOut();
        }
        e->accept();
    }
    else {
        QTextEdit::wheelEvent(e);
    }
}

void CodeEditor::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    QAction* action1 = menu.addAction(QStringLiteral("清空"));
    connect(action1, &QAction::triggered, this, &CodeEditor::clear);
    menu.exec(event->globalPos());
}

void CodeEditor::insertCompletion(QString s)
{
    auto tc = textCursor();
    tc.select(QTextCursor::SelectionType::WordUnderCursor);
    tc.insertText(s);
    setTextCursor(tc);
}

void CodeEditor::insertCompletion(QString s, int from, int len)
{
    auto tc = textCursor();
    tc.setPosition(from);
    tc.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, len);
    tc.insertText(s);
    setTextCursor(tc);
}

QChar CodeEditor::charUnderCursor(int offset) const
{
    auto block = textCursor().blockNumber();
    auto index = textCursor().positionInBlock();
    auto text = document()->findBlockByNumber(block).text();

    index += offset;

    if (index < 0 || index >= text.size())
    {
        return {};
    }

    return text[index];
}

QString CodeEditor::wordUnderCursor() const
{
    auto tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::insertFromMimeData(const QMimeData* source)
{
    insertPlainText(source->text());
}

int CodeEditor::getIndentationSpaces()
{
    auto blockText = textCursor().block().text();

    int indentationLevel = 0;

    for (auto i = 0;
        i < blockText.size() && QString("\t ").contains(blockText[i]);
        ++i)
    {
        if (blockText[i] == ' ')
        {
            indentationLevel++;
        }
        else
        {
#if QT_VERSION >= 0x050A00
            indentationLevel += tabStopDistance() / fontMetrics().averageCharWidth();
#else
            indentationLevel += tabStopWidth() / fontMetrics().averageCharWidth();
#endif
        }
    }

    return indentationLevel;
}

void CodeEditor::onScrollRangeChanged(int min, int max)
{
    auto value = verticalScrollBar()->value();
    Q_EMIT sigScrollToTopStateChanged(value != min);
    Q_EMIT sigScrollToBottomStateChanged(value != max);
}

void CodeEditor::onScrollValueChanged(int value)
{
    Q_EMIT sigScrollToTopStateChanged(value != verticalScrollBar()->minimum());
    Q_EMIT sigScrollToBottomStateChanged(value != verticalScrollBar()->maximum());
}

void CodeEditor::scrollToTop()
{
   /* QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    setTextCursor(cursor);*/
    verticalScrollBar()->setValue(verticalScrollBar()->minimum());
}

void CodeEditor::scrollToBottom()
{
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    /*QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    setTextCursor(cursor);*/
}
