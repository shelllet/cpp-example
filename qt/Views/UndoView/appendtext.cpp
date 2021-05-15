#include "appendtext.h"


AppendText::AppendText(QLabel *doc, QString txt)
    : label(doc), text(txt)
{

    setText("Apend Text");
}

void AppendText::undo()
{
    QString s =  label->text();
    s.chop(text.length());

    label->setText(s);
}

void AppendText::redo()
{
    label->setText(label->text()+ text);
}
