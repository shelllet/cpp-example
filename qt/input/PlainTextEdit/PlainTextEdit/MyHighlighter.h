#pragma once

#include <QSyntaxHighlighter>

class MyHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	MyHighlighter(QObject *parent);
	~MyHighlighter();


protected:
	void highlightBlock(const QString& text) override;

};
