#include "mytextedit.h"
#include <QTimer>
#include <QAction>
#include <QStandardItem>
#include <QModelIndex>
#include <QRegExp>
#include <QDebug>

//*********************************************************************************************************
MyTextEdit::MyTextEdit(QWidget* parent) : QPlainTextEdit(parent)
{
    lineNumberArea = QPointer<LineNumberArea>(new LineNumberArea(this));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    updateLineNumberAreaWidth(0);

    highlightCurrentLine();
    label = QPointer<QLabel>(new QLabel(this));
    statusBar = new LineStatusBar(this);

    changed = 0;
    timer = QPointer<QTimer>(new QTimer(this));
    timer->setInterval(1000);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, [&] { emit submit(); });
    connect(this, &QPlainTextEdit::textChanged, this, [=]
    {
        changed++;
        timer->stop();
        timer->start();
    });

    QFontMetrics fm(this->font());
    this->setTabStopWidth(fm.width(' ') * 4);  // 设置\t占用四个空格的宽度
    this->setLineWrapMode(QPlainTextEdit::NoWrap);

    QAction* actionSave = QPointer<QAction>(new QAction(u8"保存", this));
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    connect(actionSave, &QAction::triggered, this, [&]
    {
        if (changed)
            emit submit();
        timer->stop();
    });
    addAction(actionSave);
}

//*********************************************************************************************************
int MyTextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while(max >= 10)
    {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().width('9') * digits;
    return space;
}

//*********************************************************************************************************
int MyTextEdit::lineStatusBarHeight()
{
    int space = fontMetrics().height();
    return space;
}

//*********************************************************************************************************
void MyTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if(dy)
    {
        lineNumberArea->scroll(0, dy);
    }
    else
    {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }
    if(rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth(0);
    }
}

//*********************************************************************************************************
void MyTextEdit::updateLineNumberAreaWidth(int newBlockCount)
{
    Q_UNUSED(newBlockCount);
    setViewportMargins(lineNumberAreaWidth(), lineStatusBarHeight(), 0, 0);
}

//*********************************************************************************************************
void MyTextEdit::setLabelText()
{
    QTextCursor cursor = this->textCursor();
    QTextLayout *layout = cursor.block().layout();
    int col = cursor.position() - cursor.block().position() + 1;
    int line = layout->lineForTextPosition(col).lineNumber() + cursor.block().firstLineNumber() + 1;
    label->setText(QStringLiteral("行: ") % QString::number(line) % QStringLiteral(" , 列: ") % QString::number(col));
    label->setMinimumSize(100, lineStatusBarHeight());
    label->setAlignment(Qt::AlignCenter);
}

//*********************************************************************************************************
void MyTextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    statusBar->setGeometry(QRect(cr.left(), cr.top(), cr.width(), lineStatusBarHeight()));
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top()+lineStatusBarHeight(), lineNumberAreaWidth(), cr.height()));
}

//*********************************************************************************************************
void MyTextEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection>extraSelections;
    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(100);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

//*********************************************************************************************************
void MyTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();
    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible()&&bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            painter.setFont(this->font());
            painter.drawText(-2, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}

//*********************************************************************************************************
void MyTextEdit::lineStatusBarPaintEvent(QPaintEvent *event)
{
    QPainter painter(statusBar);
    painter.fillRect(event->rect(), Qt::white);
    setLabelText();
    statusBar->addPermanentWidget(label);
}

//*********************************************************************************************************
void MyTextEdit::getInput()
{
    input.clear();
    parentStr.clear();
    QTextCursor cursor = this->textCursor();
    QTextDocument *doc = this->document();
    int end = cursor.position();
    int start = end;
    if (doc->characterAt(end).isLetterOrNumber() || doc->characterAt(end) == '_')
    {
        return;
    }
    QString str;

    // 根据变量名定义规则匹配
    while (doc->characterAt(end - 1).isLetterOrNumber() || doc->characterAt(end - 1) == '_' || doc->characterAt(end - 1) == '$')
    {
        str += doc->characterAt(end - 1);
        end--;
        if (end < 1)
        {
            break;
        }
    }
    while (doc->characterAt(end - 1) == '.')
    {
        QString str1;
        str1.clear();
        while (doc->characterAt(end - 2) != '.' && doc->characterAt(end - 2) != ' ' && doc->characterAt(end - 2) != '\\t')
        {
            if (end < 2)
            {
                break;
            }
            str1 += doc->characterAt(end - 2);
            end--;
        }
        if (str1.isEmpty())
        {
            return;
        }
        QString str2;
        for (int i = 1; i <= str1.length(); i++)
        {
            str2 += str1[str1.length() - i];
        }
        parentStr.prepend(str2);
    }
    cursor.setPosition(start);
    QRect rect = this->cursorRect(cursor);
    point = rect.bottomLeft();
    for (int i = 1; i <= str.length(); i++)
    {
        input += str[str.length() - i];
    }
}

//*********************************************************************************************************
void MyTextEdit::getVariable()
{
    QTextBlock block = firstVisibleBlock();
    QRegExp reg("[ |\\t]*[ |\\t]*local[ |\\t]+[\\w]+");
    int number = 0;
    while (block.isVisible() && number < this->blockCount())
    {
        QString text = block.text();
        QString str;
        if (text.contains(reg))
        {
            int start = reg.indexIn(text) + 6;
            for (int i = start; i < text.length(); i++)
            {
                if (text[i].isLetterOrNumber() || text[i] == '_')
                {
                    str += text[i];
                }
                else if (text[i] == ' ' || text[i] == '\\t')
                {
                    if(str.isEmpty())
                    {
                        continue;
                    }
                    else
                    {
                        variables.insert(str);
                        str.clear();
                        break;
                    }
                }
                else
                {
                    if(!str.isEmpty())
                    {
                        variables.insert(str);
                        str.clear();
                    }
                    break;
                }
            }
        }
        block = block.next();
        number++;
    }
}

//*********************************************************************************************************
void MyTextEdit::getKeywords(QString filename)
{
    keywords.clear();
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }
    if (parentStr.isEmpty())
    {
        while (!file.atEnd())
        {
            QString line = file.readLine();
            if (line.isEmpty())
            {
                continue;
            }
            QRegExp re("^\\s+");
            int nonws = re.indexIn(line);
            if (nonws == -1)
            {
                QString str = line.simplified();
                keywords << str;
            }
        }
    }
    else
    {
        int start = 0;
        int i = 0;
        while (!file.atEnd()) {
            QString line = file.readLine();
            if (line.isEmpty())
            {
                continue;
            }
            QRegExp re("\\w+");
            QString str = line.simplified();
            if (i > 1 && start == 0)
            {
                i = 0;
                continue;
            }
            else
            {
                if ((re.indexIn(line) / 4) < start && i > 0)
                {
                    if (!keywords.isEmpty())
                    {
                        return;
                    }
                    else
                    {
                        i = 0;
                        start = 0;
                       continue;
                    }
                }
                if (i < parentStr.count())
                {
                    if (str == parentStr.at(i))
                    {
                        start = (line.length() - str.length()) / 4 + 1;
                        i++;
                        continue;
                    }
                }
                else if (i = parentStr.count())
                {
                    if ((re.indexIn(line) / 4) == start)
                    {
                        keywords << str;
                    }
                }
                else
                {
                    i = 0;
                    start = 0;
                    continue;
                }
            }
        }
    }
}

//*********************************************************************************************************
void MyTextEdit::marchingWords()
{
    result.clear();
    if(input.isEmpty() && parentStr.isEmpty())
    {
        return;
    }
    if (input.isEmpty())
    {
        for (QString str : keywords)
        {
            result << str;
        }
    }
    else
    {
        for (QString str : keywords)
        {
            if(str.length() > input.length() && str.startsWith(input))
            {
                result << str;
            }
        }
        for (QString str : variables)
        {
            if(str.length() > input.length() && str.startsWith(input))
            {
                result << str;
            }
        }
    }
}

//*********************************************************************************************************
void MyTextEdit::getModel()
{
    model->clear();
    getInput();
    getKeywords(filename);
    getVariable();
    marchingWords();
    if (result.empty())
    {
        return;
    }
    for (int i = 0; i < result.count(); i++)
    {
        QString str = result.at(i);
        QStandardItem *item = new QStandardItem(str);
        item->setFont(this->font());
        model->appendRow(item);
    }
}

//*********************************************************************************************************
int MyTextEdit::intellisenseWidth()
{
    if (result.empty())
    {
        return 0;
    }
    int max = static_cast<QString>(result.at(0)).length();
    for (int i = 0; i < result.count(); i++)
    {
        QString str = result.at(i);
        if (max < str.length())
        {
            max = str.length();
        }
    }
    int width = (max + 10) * fontMetrics().width('9');
    return width;
}

//*********************************************************************************************************
int MyTextEdit::intellisenseHeight()
{
    int height;
    if (model->rowCount() == 0)
    {
        return 0;
    }
    else if (model->rowCount() > 6)
    {
        height = 7 * fontMetrics().height() + 10;
        return height;
    }
    else
    {
        height = (model->rowCount()) * fontMetrics().height() + 10;
        return height;
    }
}

//*********************************************************************************************************
void MyTextEdit::position()
{
    int x = mapTo(this, point).x();
    int y = mapTo(this, point).y();
    QSize size = this->size();
    if (intellisenseWidth() > (size.width() - x))
    {
        intellisense->move(mapToGlobal(QPoint(size.width() - intellisenseWidth() - 10, y + fontMetrics().height())));
    }
    else if (intellisenseHeight() > (size.height() - y))
    {
        intellisense->move(mapToGlobal(QPoint(x, y - intellisenseHeight())));
    }
    else
    {

        intellisense->move(mapToGlobal(QPoint(x, y + fontMetrics().height())));
    }
}

//*********************************************************************************************************
void MyTextEdit::setCompleter()
{
    getModel();
    if (model->rowCount() == 0)
    {
        intellisense->hide();
        intellisense->releaseKeyboard();
        return;
    }
    intellisense->setFixedSize(intellisenseWidth(), intellisenseHeight());
    position();
    intellisense->setModel(model);
    intellisense->show();
    intellisense->grabKeyboard();
    QModelIndex index = intellisense->model()->index(0, 0);
    intellisense->setCurrentIndex(index);
}

//*********************************************************************************************************
void MyTextEdit::setText(const QString &text)
{
    QTextCursor cursor = this->textCursor();
    QTextDocument *doc = this->document();
    int end = cursor.position();
    int start = end;
    while (doc->characterAt(end - 1).isLetterOrNumber() || doc->characterAt(end - 1) == '_' || doc->characterAt(end - 1) == '$')
    {
        if (end < 1)
        {
            break;
        }
        cursor.setPosition(end - 1);
        cursor.deleteChar();
        end--;

    }
    cursor.insertText(text);
    cursor.setPosition(start);
}

//*********************************************************************************************************
void MyTextEdit::intellisenseKeyPressEvent(QKeyEvent *event)
{
    if (!intellisense->isHidden())
    {
        int count = intellisense->model()->rowCount();
        QModelIndex currentIndex = intellisense->currentIndex();
        if (event->key() == Qt::Key_Down)
        {
            int row = currentIndex.row() + 1;
            if (row >= count)
            {
                row = 0;
            }
            QModelIndex index = intellisense->model()->index(row, 0);
            intellisense->setCurrentIndex(index);
        }
        else if (event->key() == Qt::Key_Up)
        {
            int row = currentIndex.row() - 1;
            if (row < 0)
            {
                row = count - 1;
            }
            QModelIndex index = intellisense->model()->index(row, 0);
            intellisense->setCurrentIndex(index);
        }
        else if (event->key() == Qt::Key_Escape)
        {
            intellisense->hide();
        }
        else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            if (currentIndex.isValid())
            {
                QString text = intellisense->currentIndex().data().toString();
                this->setText(text);
            }
            intellisense->hide();
        }
        else if (event->key() == Qt::Key_Tab)
        {
            if (currentIndex.isValid())
            {
                QString text = intellisense->currentIndex().data().toString();
                this->setText(text);
            }
            intellisense->hide();
        }
        else
        {
            intellisense->hide();
            MyTextEdit::keyPressEvent(event);
        }
    }
    else
    {
        MyTextEdit::keyPressEvent(event);
    }
}

//*********************************************************************************************************
void MyTextEdit::intellisenseMouseDoubleClickEvent(QMouseEvent *event)
{
    if (!intellisense->isHidden())
    {
        if (event->button() == Qt::LeftButton)
        {
            QString text = intellisense->currentIndex().data().toString();
            this->setText(text);
        }
        else
        {
            intellisense->hide();
            MyTextEdit::mouseDoubleClickEvent(event);
        }
    }
    else
    {
        MyTextEdit::mouseDoubleClickEvent(event);
    }
}

//*********************************************************************************************************
void MyTextEdit::focusOutEvent(QFocusEvent* /*e*/)
{
    if (changed)
        emit submit();
    timer->stop();
}

//*********************************************************************************************************
void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    QTextDocument* doc = this->document();
    QTextCursor cursor = this->textCursor();
    if (e->key() == Qt::Key_Tab || e->key() == Qt::Key_Backtab)
    {
        /**
         * 实现按Tab键整体偏移
         */
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();
        cursor.setPosition(start);
        cursor.movePosition(QTextCursor::StartOfLine);
        start = cursor.position();
        int lines = 0;
        while (true)
        {
            int n = cursor.position();
            if (n >= end)
            {
                break;
            }
            lines++;
            cursor.movePosition(QTextCursor::StartOfLine);
            if (!cursor.movePosition(QTextCursor::Down))
                break;
        }

        if (lines > 1)
        {
            cursor.setPosition(start);
            cursor.beginEditBlock();
            while (lines-- > 0)
            {
                if (e->key() == Qt::Key_Backtab)
                {
                    QChar ch = doc->characterAt(cursor.position());
                    if (ch.isSpace())
                        cursor.deleteChar();
                }
                else
                {
                    cursor.insertText("\t");
                }
                cursor.movePosition(QTextCursor::StartOfLine);
                cursor.movePosition(QTextCursor::Down);
            }
            cursor.endEditBlock();
            return;
        }
    }
    else if (e->key() == Qt::Key_Return)
    {
        /**
         * 实现换行后自动对齐上一行
         */
        QString indent;
        int end = cursor.position();
        cursor.movePosition(QTextCursor::StartOfLine);
        int i = cursor.position();
        while (i < end)
        {
            QChar ch = doc->characterAt(i);
            if (ch.isSpace())
            {
                indent.append(ch);
                i++;
            }
            else
            {
                break;
            }
        }
        cursor.setPosition(end);
        QPlainTextEdit::keyPressEvent(e);
        if (indent.size() > 0)
        {
            cursor = this->textCursor();
            cursor.joinPreviousEditBlock();
            cursor.insertText(indent);
            cursor.endEditBlock();
        }
        return;
    }
    QPlainTextEdit::keyPressEvent(e);
}
