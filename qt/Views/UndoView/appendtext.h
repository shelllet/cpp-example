#ifndef APPENDTEXT_H
#define APPENDTEXT_H

#include <QUndoCommand>
#include <QLabel>
class AppendText : public QUndoCommand
{
public:
    AppendText(QLabel *doc, QString txt);



private:
    QLabel* label;
    QString text;

    // QUndoCommand interface
public:
    void undo();
    void redo();
};

#endif // APPENDTEXT_H
