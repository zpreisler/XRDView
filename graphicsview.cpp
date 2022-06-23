#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent)
{

}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setStyleSheet("border: 1px solid black");

}

/*
void GraphicsView::resize()
{

  GraphicsScene *scene=dynamic_cast<GraphicsScene *>(this->scene());
    qDebug()<<"Resize GraphicsView0";
  if(scene!=nullptr){
      qDebug()<<"Resize GraphicsView";
//      qreal height=scene->pix->pixmap().height();
  //    qreal width=scene->pix->pixmap().width();
    //  this->setGeometry(this->x(),this->y(),width,height);
  }

}*/



void GraphicsView::wheelEvent( QWheelEvent *e)
{
    qreal scale = (e->angleDelta().ry() > 0) ? 1.2 : 1/1.2;
    this->scaleView(scale);

}

void GraphicsView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.7 || factor > 100)
        return;

    this->scale(scaleFactor, scaleFactor);
     GraphicsScene *scene=dynamic_cast<GraphicsScene *>(this->scene());
     if(scene!=nullptr){
         //scene->scaleFactor=scaleFactor;
     }


}
