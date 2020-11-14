#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QPainter>
#include <QTextBlock>
#include <QStatusBar>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QSet>
#include <QPointer>

class MyTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	MyTextEdit(QWidget* parent = NULL);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void lineStatusBarPaintEvent(QPaintEvent *event);
    void intellisenseKeyPressEvent(QKeyEvent *event);
    void intellisenseMouseDoubleClickEvent(QMouseEvent *event);
    int lineStatusBarHeight();
    int intellisenseWidth();
    int intellisenseHeight();
    void setText(const QString &text);

    /**
     * @brief 根据行号位数获取宽度
     * @return 宽度
     */
    int lineNumberAreaWidth();
    QString filename;

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    QListView *intellisense;
    QStandardItemModel *model;
signals:
	void submit();
protected slots:
    void setCompleter();

private slots:
    void updateLineNumberAreaWidth(int);
    void getInput();
    void marchingWords();
    void getModel();

    /**
     * @brief 实现选中行高亮
     */
    void highlightCurrentLine();

    /**
     * @brief 实现滚动后行号更新
     */
    void updateLineNumberArea(const QRect &, int);    

private:
	virtual void focusOutEvent(QFocusEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    void position();
    void getVariable();

    /**
     * @brief 从资源文件中获取关键字
     * @param 资源文件名
     */
    void getKeywords(QString filename);

    /**
     * @brief 设置行列号统计Label
     */
    void setLabelText();

    QPointer<QTimer> timer;
	int changed;
    QPointer<QWidget> lineNumberArea;
    QPointer<QStatusBar> statusBar;
    QPointer<QLabel> label;
    QString input;
    QStringList keywords;
    QStringList result;
    QPoint point;
    QSet<QString>variables;
    QStringList parentStr;
};

/**
 * @brief 行号管理类
 */
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MyTextEdit *editor) : QWidget(editor)
    {
        textEditor = editor;
    }
    QSize sizeHint() const Q_DECL_OVERRIDE
    {
        return QSize(textEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE
    {
        textEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MyTextEdit *textEditor;
};

class LineStatusBar : public QStatusBar
{
public:
    LineStatusBar(MyTextEdit *editor) : QStatusBar(editor)
    {
        textEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE
    {
        return QSize(textEditor->width(), textEditor->lineStatusBarHeight());
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE
    {
        textEditor->lineStatusBarPaintEvent(event);
    }
private:
    QPointer<MyTextEdit> textEditor;
};

class Intellisense : public QListView
{
public:
    Intellisense(MyTextEdit *editor, QString filename) : QListView(editor)
    {
        textEditor = editor;
        textEditor->filename = filename;
    }

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE
    {
        textEditor->intellisenseKeyPressEvent(event);
    }

    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE
    {
        textEditor->intellisenseMouseDoubleClickEvent(event);
    }

private:
    QPointer<MyTextEdit> textEditor;
    QString filename;
};

#endif // MYTEXTEDIT_H
