#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "h5data.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *action= new QAction("Open HDF");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(openHDF()));
    ui->menuFile->addAction(action);
    this->setCentralWidget(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openHDF()
{


     QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Open File"), "", QObject::tr("HDF (*.h5)"));
      if(!fileName.isEmpty()){
          Datacube *datacube = new Datacube(fileName.toLatin1(),"data");
          GraphicsScene *scene = new GraphicsScene(datacube,this);
          ui->XRDGraphicsView->setScene(scene);
          ChartView *chartView = ui->SpectraChartView;
          Chart *chart = new Chart(datacube);
          chartView->setChart(chart);

          connect(scene,&GraphicsScene::clicked,
                      chart,&Chart::newLine);

          connect(chartView,&ChartView::clicked,
                      scene,&GraphicsScene::newChannel);

      }

}
