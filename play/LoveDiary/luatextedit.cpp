#include "luatextedit.h"
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QList>


//*********************************************************************************************************
class LuaHighLighter : public QSyntaxHighlighter
{
public:
	LuaHighLighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
	{
		QStringList keyword;  // 关键字
		keyword << "\\bfunction"
				<< "\\bprint"
				<< "\\btable"
				<< "\\blocal\\b"
				<< "\\breturn\\b"
				<< "\\bif\\b"
				<< "\\belseif\\b"
				<< "\\belse\\b"
				<< "\\bthen\\b"
				<< "\\bfor\\b"
				<< "\\bin\\b"
				<< "\\bwhile\\b"
				<< "\\bdo\\b"
				<< "\\bbreak\\b"
				<< "\\bend\\b"
				<< "\\band\\b"
				<< "\\bor\\b"
				<< "\\bnot\\b"
				<< "\\bnil\\b"
				<< "\\btrue\\b"
				<< "\\bfalse\\b";
		for (auto key : keyword)
		{
			HighlightRule rule;
			rule.pattern = QRegularExpression(key);
			rule.format.setForeground(Qt::blue);
			rule.format.setFontWeight(QFont::Bold);
			highlightRules.append(rule);
		}
		{
			HighlightRule rule;
			rule.pattern = QRegularExpression("[\\{\\(\\)\\[\\]\\}]");
            rule.format.setForeground(Qt::black);
			rule.format.setFontWeight(QFont::Bold);
			highlightRules.append(rule);
        }
		{
            HighlightRule rule;
            rule.pattern = QRegularExpression("\\-\\-.*");
            rule.format.setForeground(Qt::darkGreen);
            highlightRules.append(rule);
		}
        {
            HighlightRule rule;
            rule.pattern = QRegularExpression("\\'.*\\'");
            rule.pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
            rule.format.setForeground(Qt::gray);
            highlightRules.append(rule);

            rule.pattern = QRegularExpression("\".*\"");
            rule.pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
            rule.format.setForeground(Qt::gray);
            highlightRules.append(rule);
        }
	}

private:
    void highlightBlock(const QString &text)
	{
		// 多行处理，如块注释

        if (previousBlockState() == 255)
        {
            QTextCharFormat format;
            format.setForeground(Qt::darkGreen);

            int last = text.lastIndexOf("]]");
            if (last >= 0)
            {
                setFormat(0, last+2, format);
                setCurrentBlockState(0);
            }
            else
            {
                setFormat(0, text.length(), format);
                setCurrentBlockState(255);
            }
        }
        else if (previousBlockState() == 256)
        {
            QTextCharFormat format;
            format.setForeground(Qt::gray);

            int last = text.lastIndexOf("]]");
            if (last >= 0)
            {
                setFormat(0, last+2, format);
                setCurrentBlockState(0);
            }
            else
            {
                setFormat(0, text.length(), format);
                setCurrentBlockState(256);
            }
        }
        else
        {
            static int index;

            // 块注释符起点判定
            int startL = text.indexOf("--[[");
            startL = startIndex("--[[", text, startL, index);

            // 行注释符起点判定
            int startS = text.indexOf("--");
            startS = startIndex("--", text, startS, index);

            // 字符块起点判定
            int startB = text.indexOf("[[");
            startB = startIndex("[[", text, startB, index);


            if (startS >= 0 && startB >= 0 && startB < startS) // "[["在前面
            {
                QTextCharFormat format;
                format.setForeground(Qt::gray);
                setCurrentBlockState(256);
                setFormat(startB, text.length() - startB, format);
            }
            else if (startB >= 0 && startS < 0)
            {
                QTextCharFormat format;
                format.setForeground(Qt::gray);
                setCurrentBlockState(256);
                setFormat(startB, text.length() - startB, format);
            }
            else
            {
                if (startL >= 0 && startS >= 0)
                {
                    if (startL > startS) // "--"在前面
                    {
                        for (HighlightRule& rule : highlightRules)
                        {
                            if (rule.pattern == QRegularExpression("\\-\\-.*"))
                            {
                                continue;
                            }
                            auto it = rule.pattern.globalMatch(text);
                            while (it.hasNext())
                            {
                                auto match = it.next();
                                auto start = match.capturedStart();
                                auto len = match.capturedLength();
                                setFormat(start, len, rule.format);

                            }
                        }
                        QTextCharFormat format;
                        format.setForeground(Qt::darkGreen);
                        setCurrentBlockState(0);
                        setFormat(startS, text.length() - startS, format);
                    }
                    else // "--[["在前面
                    {
                        for (HighlightRule& rule : highlightRules)
                        {
                            if (rule.pattern == QRegularExpression("\\-\\-.*"))
                            {
                                continue;
                            }
                            auto it = rule.pattern.globalMatch(text);
                            while (it.hasNext())
                            {
                                auto match = it.next();
                                auto start = match.capturedStart();
                                auto len = match.capturedLength();
                                setFormat(start, len, rule.format);
                            }
                        }
                        QTextCharFormat format;
                        format.setForeground(Qt::darkGreen);
                        setCurrentBlockState(255);
                        setFormat(startL, text.length() - startL, format);
                    }
                }
                else if (startS >= 0 && startL < 0)
                {
                    for (HighlightRule& rule : highlightRules)
                    {
                        if (rule.pattern == QRegularExpression("\\-\\-.*"))
                        {
                            continue;
                        }
                        auto it = rule.pattern.globalMatch(text);
                        while (it.hasNext())
                        {
                            auto match = it.next();
                            auto start = match.capturedStart();
                            auto len = match.capturedLength();
                            setFormat(start, len, rule.format);
                        }
                    }
                    QTextCharFormat format;
                    format.setForeground(Qt::darkGreen);
                    setCurrentBlockState(0);
                    setFormat(startS, text.length() - startS, format);
                }
                else
                {
                    setCurrentBlockState(0);
                    for (HighlightRule& rule : highlightRules)
                    {
                        if (rule.pattern == QRegularExpression("\\-\\-.*"))
                        {
                            continue;
                        }
                        auto it = rule.pattern.globalMatch(text);
                        while (it.hasNext())
                        {
                            auto match = it.next();
                            auto start = match.capturedStart();
                            auto len = match.capturedLength();
                            setFormat(start, len, rule.format);
                        }
                    }
                }
            }
        }
    }

//*********************************************************************************************************
    int startIndex(QString str, const QString text, int start, int &index)
    {
        int sQuotes = 0;   // 单引号数量
        int dQuotes = 0;   // 双引号数量
        index = -1;
        for (int i = 0;i <= start; i++)
        {
            if (text[i] == '\'')
            {
                sQuotes++;
            }
            if (text[i] == '\"')
            {
                dQuotes++;
            }
        }
        if (sQuotes % 2 == 0 && dQuotes % 2 == 0)
        {
            index = start;
            return index;
        }
        else
        {
            for (int j = start + str.length(); j <= text.length() - str.length(); j++)
            {
                QString str1 = QString::null;
                for (int k = 0; k < str.length(); k++)
                {
                    str1 += text[j + k];
                }
                if (str1 == str)
                {
                    start = j;
                    startIndex(str, text, start, index);
                    return index;
                }
            }
            return index;
        }
    }

private:
	struct HighlightRule
	{
		QRegularExpression pattern;
		QTextCharFormat format;
	};
	QList<HighlightRule> highlightRules;
};

//*********************************************************************************************************
LuaTextEdit::LuaTextEdit(QWidget* parent) : MyTextEdit(parent)
{
	new LuaHighLighter(this->document());
    intellisense = new Intellisense(this, "");
    model = new QStandardItemModel(this);
    intellisense->setWindowFlags(Qt::ToolTip);
    intellisense->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    connect(this, SIGNAL(textChanged()), this, SLOT(setCompleter()));
}
