#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene{parent}
{

}

GraphicsScene::GraphicsScene(Datacube *datacube, QObject *parent) : QGraphicsScene{parent}
{

	GraphicsScene::datacube = datacube;
	datacube->slicedice(0);
	pix = addPixmap(datacube->pix);
    /*
    scaleFactor=pix->pixmap().width();
    pix->pixmap().scaled(this->width(),this->height(),Qt::KeepAspectRatio);
    scaleFactor=scaleFactor/pix->pixmap().width();
    qDebug()<<scaleFactor;
    */

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //std::cout << "X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";
      qDebug()<<"moving ";

      qDebug()<<convertToPoint(event->scenePos());

      emit moving(convertToPoint(event->scenePos()));
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "Pressed X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";
    stateMachine(event);



}
 
void GraphicsScene::newChannel(int channel)
{

	std::cout << "channel:" << channel << "\n";

	datacube->slicedice(channel);
	pix->setPixmap(datacube->pix);

}
bool GraphicsScene::isInside(QPointF point)
{
    qreal width=pix->pixmap().width();
    qreal height=pix->pixmap().height();
    if ((point.x()<0)||(point.x()>width) ||
        (point.y()<0)||(point.y()>height)) {
        qDebug()<<"outside";
         return false;
    }else
        return true;
}
void GraphicsScene::stateMachine(QGraphicsSceneMouseEvent *e)
{

    if(e->button() != Qt::LeftButton) return;
    QPointF point=e->scenePos();
    if(!isInside(convertToPoint(point))) return;
    QGraphicsRectItem *selectedRectangle= findRectangle(e->scenePos());

    if(selectedRectangle)
    {
        this->removeRect(selectedRectangle);

    }else{
        QColor color=generateColor();
        //QPoint point(e->scenePos().x(),e->scenePos().y());


        QPoint point=convertToPoint(e->scenePos());
        qDebug()<<point;

        qDebug()<<"clicked point";
        qDebug()<<point;
        this->addRect(point.x(), point.y(), 1,1, QPen(QBrush(color),1,Qt::DashLine), QBrush(color));

        qDebug()<<"add rect";
        qDebug()<<point;




        emit clickedPoint(point,color);
    }




}
QGraphicsRectItem *GraphicsScene::findRectangle(QPointF point)
{
    return dynamic_cast<QGraphicsRectItem *>(this->itemAt(point, QTransform()));
}
QColor GraphicsScene::generateColor()
{
   QColor color;

   do{
     color.setRed(QRandomGenerator::global()->bounded(256));
     color.setGreen(QRandomGenerator::global()->bounded(256));
     color.setBlue(QRandomGenerator::global()->bounded(256));
      }while(listColor.contains(color));
    listColor.append(color);

   return color;

}


void GraphicsScene::removeRect(QGraphicsRectItem *rect){
    qDebug()<<"remove point";

    QBrush brush=rect->brush();
   QColor color= brush.color();
    this->removeItem(rect);
   listColor.removeOne(color);

     emit removedPoint(color);


}

QPoint GraphicsScene::convertToPoint(QPointF n){
    qint32 x=floor(n.x());
    qint32 y=floor(n.y());
    QPoint p(x,y);
    return p;
}
