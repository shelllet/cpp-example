#ifndef COLUMNVIEW_H
#define COLUMNVIEW_H

#include <QColumnView>

class ColumnView : public QColumnView
{
    Q_OBJECT
public:
    explicit ColumnView(QWidget *parent = nullptr);

signals:

public slots:

    // QColumnView interface
protected:
    QAbstractItemView *createColumn(const QModelIndex &rootIndex);
};

#endif // COLUMNVIEW_H
