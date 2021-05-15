#pragma once
#include "qsplitter.h"

class MySplitter :
    public QSplitter
{
public:
    MySplitter(QWidget* parent);
protected:
  /*  void mousePressEvent(QMouseEvent* event) override;


    void mouseReleaseEvent(QMouseEvent* event) override;


    void mouseMoveEvent(QMouseEvent* event) override;*/


    class MySplitterHandle : public QSplitterHandle {
    public:
        MySplitterHandle(QSplitter* parent);


		void mouseReleaseEvent(QMouseEvent* event) override;


		void mouseMoveEvent(QMouseEvent* event) override;

        MySplitter* splitter();
    };

    QSplitterHandle* createHandle() override;

};

