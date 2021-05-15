#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QItemDelegate>
#include <QtDebug>
#include <QCompleter>
class ItemDelegate : public QItemDelegate{


    // QAbstractItemDelegate interface
public:


    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {

//                 auto text = index.data().toString();

//                 QStyleOptionButton buttonOption;
//                 buttonOption.rect = option.rect;

//                 buttonOption.text = text + "%";


//                 QApplication::style()->drawControl(QStyle::CE_PushButton,
//                                                    &buttonOption, painter);
        QItemDelegate::paint(painter, option, index);

    }
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const{
        return  QSize(100, 20);
    }

    // QAbstractItemDelegate interface
public:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        return true;
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->comboBox->setModel(ui->treeWidget->model());
    //ui->comboBox->setView(ui->treeWidget);

    ui->comboBox->view()->setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);


    QStringList wordList;
      wordList << "alpha" << "omega" << "omicron" << "zeta";


      QCompleter *completer = new QCompleter(wordList, this);
      completer->setCaseSensitivity(Qt::CaseInsensitive);
      ui->comboBox->setCompleter(completer);

    ui->comboBox->setItemDelegate(new ItemDelegate);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->comboBox->showPopup();
}
