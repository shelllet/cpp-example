#include "MyHighlighter.h"
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

MyHighlighter::MyHighlighter(QObject *parent)
	: QSyntaxHighlighter(parent)
{
}

MyHighlighter::~MyHighlighter()
{
}



void MyHighlighter::highlightBlock(const QString& text)
{
	QTextCharFormat myClassFormat;
	myClassFormat.setFontWeight(QFont::Bold);
	myClassFormat.setForeground(Qt::darkMagenta);

	QRegularExpression expression("\\bQt\\b");
	QRegularExpressionMatchIterator i = expression.globalMatch(text);
	while (i.hasNext())
	{
		QRegularExpressionMatch match = i.next();
		setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
	}
}
