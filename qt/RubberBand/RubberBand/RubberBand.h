#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RubberBand.h"
#include "qrubberband.h"
class RubberBand : public QMainWindow
{
    Q_OBJECT

public:
    RubberBand(QWidget *parent = Q_NULLPTR);

private:
    Ui::RubberBandClass ui;
protected:
    void mousePressEvent(QMouseEvent* event) override;


    void mouseReleaseEvent(QMouseEvent* event) override;


    void mouseMoveEvent(QMouseEvent* event) override;
private:
    QRubberBand* rubberBand_ = nullptr;
    QPoint origin_;
};
