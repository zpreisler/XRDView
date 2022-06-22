#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QAction>

#include "chart.h"
#include "chartview.h"
#include "graphicsview.h"
#include "graphicsscene.h"

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphicsView *view;
    GraphicsScene *scene;
    QLabel *label;


protected:
  void resizeEvent(QResizeEvent* event) override;
private slots:
  void updateLabel(QPointF p);









private slots:
    void openHDF();

};
#endif // MAINWINDOW_H
