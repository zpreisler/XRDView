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
    ui->label->setAlignment(Qt::AlignHCenter);
    //ui->label->setText("");
    ui->SpectraChartView->setAlignment(Qt::AlignHCenter);
    this->setCentralWidget(ui->centralwidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event){
    qDebug()<<"resize";
    qreal width=event->size().width();
    qreal height=(event->size().height()-ui->label->height()-ui->menubar->height()-60)/2;
    qreal x_label=5+((event->size().width()-ui->label->width()-10)/2);
    ui->label->setGeometry(x_label,0,ui->label->width(),ui->label->height());
    ui->XRDGraphicsView->setGeometry(10,ui->label->y()+15+ui->label->height(),event->size().width()-20,height);
    ui->SpectraChartView->setGeometry(10, ui->XRDGraphicsView->y()+ui->XRDGraphicsView->height()+15,width-20,height);




}

void MainWindow::openHDF()
{


     QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Open File"), "", QObject::tr("HDF (*.h5)"));
      if(!fileName.isEmpty()){

          Datacube *datacube = new Datacube(fileName.toLatin1(),"data");

          GraphicsScene *scene = new GraphicsScene(datacube,this);
          ui->XRDGraphicsView->setScene(scene);
          //ui->XRDGraphicsView->resize();

          ChartView *chartView = ui->SpectraChartView;


          Chart *chart = new Chart(datacube);
          chartView->setChart(chart);



         // connect(scene,&GraphicsScene::clicked,
           //           chart,&Chart::newLine);



          connect(chartView,&ChartView::clicked,
                      scene,&GraphicsScene::newChannel);
          connect(chartView,SIGNAL(clicked(qint32)), chart, SLOT(addVerticalLine(qint32)));

          connect(scene,SIGNAL(moving(QPoint)),
                      this,SLOT(updateLabel(QPoint)));
          connect(scene,SIGNAL(clickedPoint(QPoint, QColor)),
                      chart,SLOT(addLine(QPoint, QColor)));
          connect(scene,SIGNAL(removedPoint(QColor)),
                      chart,SLOT(removeLine(QColor)));

      }

}

void MainWindow::updateLabel(QPoint p){
       qDebug()<<p;
       ui->label->setText(QString::number(p.x())+"-"+QString::number(p.y()));

}
