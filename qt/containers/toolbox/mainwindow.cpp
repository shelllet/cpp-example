#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include <QDir>
#include <QPixmap>
#include <QtWin>
#include <QProcess>

static QPixmap extractIcons(const QString &sourceFile, bool large)
  {
      const QString nativeName = QDir::toNativeSeparators(sourceFile);
      const wchar_t *sourceFileC = reinterpret_cast<const wchar_t *>(nativeName.utf16());
      const UINT iconCount = ExtractIconEx(sourceFileC, -1, 0, 0, 0);
      if (!iconCount) {
          //std::wcerr << sourceFile << " does not appear to contain icons.\n";
          return QPixmap();
      }

      QScopedArrayPointer<HICON> icons(new HICON[iconCount]);
      const UINT extractedIconCount = large ?
          ExtractIconEx(sourceFileC, 0, icons.data(), 0, iconCount) :
          ExtractIconEx(sourceFileC, 0, 0, icons.data(), iconCount);
      if (!extractedIconCount) {
          qErrnoWarning("Failed to extract icons from %s", qPrintable(sourceFile));
          return QPixmap();
      }

      QPixmap result;
      //result.reserve(int(extractedIconCount));

    //  std::wcout << sourceFile << " contains " << extractedIconCount << " icon(s).\n";

      for (UINT i = 0; i < extractedIconCount; ++i) {
         // PixmapEntry entry;
          result = QtWin::fromHICON(icons[i]);
          if (result.isNull()) {
             // std::wcerr << "Error converting icons.\n";
              return QPixmap();
          }
//          entry.name = QString::fromLatin1("%1_%2x%3").arg(i, 3, 10, QLatin1Char('0'))
//              .arg(entry.pixmap.width()).arg(entry.pixmap.height());
//          result.append(entry);
      }
      return result;
  }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap map = extractIcons("C:\\Windows\\System32\\notepad.exe", true);

    map.save("note.png");


   auto* item = ui->listWidget->item(0);

   item->setIcon(map);

   item->setData(0xff + 1, "C:\\Windows\\System32\\notepad.exe");


   ui->toolBox->addItem(new QListWidget(),"third");
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
     auto path = item->data(0xff + 1).toString();

     QProcess::startDetached(path);
}
