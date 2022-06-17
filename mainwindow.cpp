#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "h5data.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Datacube *datacube = new Datacube("xrd.h5","data");

	GraphicsScene *scene = new GraphicsScene(this);
	ui->XRDGraphicsView->setScene(scene);

	SliceAndDice *slice = new SliceAndDice(datacube);

	slice->slicedice(590);
	QGraphicsPixmapItem *pix = scene->addPixmap(slice->pix);

	slice->slicedice(190);
	pix->setPixmap(slice->pix);

	ChartView *chartView = ui->SpectraChartView;

	Chart *chart = new Chart(slice);
	chartView->setChart(chart);

	QObject::connect(scene,&GraphicsScene::clicked,
			chart,&Chart::clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

