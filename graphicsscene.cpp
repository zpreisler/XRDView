#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene{parent}
{

}

GraphicsScene::GraphicsScene(Datacube *datacube, QObject *parent) : QGraphicsScene{parent}
{

	GraphicsScene::datacube = datacube;
	datacube->slicedice(0);
	pix = addPixmap(datacube->pix);
    scaleFactor=pix->pixmap().width();
    pix->pixmap().scaled(this->width(),this->height(),Qt::KeepAspectRatio);
    scaleFactor=scaleFactor/pix->pixmap().width();
    qDebug()<<scaleFactor;

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";
      emit moving(event->scenePos().toPoint());
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout << "Pressed X: " << event->scenePos().x() << " Y: " << event->scenePos().y() << "\n";
    stateMachine(event);
	emit clicked(event->scenePos().x(),event->scenePos().y());


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
    if(!isInside(point.toPoint())) return;
    QGraphicsRectItem *selectedRectangle= findRectangle(e->scenePos());

    if(selectedRectangle)
    {
        this->removeItem(selectedRectangle);
    }else{
        this->addRect(e->scenePos().x(), e->scenePos().y(), 1, 1, dashed, brush);
        qDebug()<<"add rect";
    }




}
QGraphicsRectItem *GraphicsScene::findRectangle(QPointF point)
{
    return dynamic_cast<QGraphicsRectItem *>(this->itemAt(point, QTransform()));
}
