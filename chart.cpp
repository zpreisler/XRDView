#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

}

Chart::Chart(Datacube *datacube, QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent,wFlags)
{

	Chart::datacube = datacube;
    QLineSeries *line = new QLineSeries();
    verticalLine=new QLineSeries();



	drawLine(line,0,0);

	this->addSeries(line);
   this->createDefaultAxes();
	this->legend()->hide();
	this->setTitle("XRD spectra");



   // layout()->setContentsMargins(0, 0, 0, 0);
    setBackgroundRoundness(0);



}

void Chart::drawLine(QLineSeries *line, int x, int y)
{

	float *spectra = datacube->get_pixel(x,y);

	for(int i=0; i < static_cast<int>(datacube->dims[2]); i++){
		line->append(i,*(spectra + i));
	}

}

void Chart::newLine(int x,int y)
{

	this->removeAllSeries();

    QLineSeries *line = new QLineSeries();
	drawLine(line,x,y);

	this->addSeries(line);

}

void Chart::addLine(QPoint point, QColor color){
    qDebug()<<"Add new series";
    QLineSeries *line = new QLineSeries();
     drawLine(line,point.x(),point.y());
     line->setColor(color);
     this->addSeries(line);
     this->createDefaultAxes();
     if(this->verticalLine->count()>0)
                    this->updateVerticalLine();


}
void Chart::removeLine(QColor color){
    qDebug()<<"remove line";
    QList<QAbstractSeries *> lista=this->series();
    for(QAbstractSeries *element:lista){
        QLineSeries *ls= dynamic_cast< QLineSeries *>(element);
        if(ls){
            if(ls->color()==color){

                this->removeSeries(ls);
                return;
            }
        }


    }

}
void Chart::updateVerticalLine()
{
    qint32 x=this->verticalLine->at(0).x();

    this->addVerticalLine(x);
}
void Chart::updateAxes(){
    this->createDefaultAxes();
    QValueAxis *xa=dynamic_cast<QValueAxis *>(this->axes(Qt::Horizontal).first());
    if(xa){
        xa->setTickInterval(100);
    }
   // this->updateVerticalLine();



}
void Chart::addVerticalLine(qint32 channel)
{


    QValueAxis *ya=dynamic_cast<QValueAxis *>(this->axes(Qt::Vertical).first());
    if(ya){
        this->removeSeries(verticalLine);
        qDebug()<<"add vertical line";
        qint32 max=ya->max();
        qDebug()<<max;
        this->verticalLine->clear();
        this->verticalLine->setColor(QColor(255,0,0,255));
        this->verticalLine->append(channel,0);
        this->verticalLine->append(channel,max);
        qDebug()<<verticalLine;
        this->addSeries(verticalLine);
        this->updateAxes();


    }


}
