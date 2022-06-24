#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include <QRandomGenerator>
#include <QHash>
#include <QLineSeries>



#include "h5data.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT


	public:

         QGraphicsPixmapItem *pix;


		 explicit GraphicsScene(QObject *parent = nullptr);
		 explicit GraphicsScene(Datacube *datacube, QObject *parent = nullptr);


    private:
      Datacube *datacube;
     //Scale factor to identify the correspondence between the image point and the real pixel
       //qreal scaleFactor=1;

      QList<QColor> listColor;


      void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
      void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
      void stateMachine(QGraphicsSceneMouseEvent *e);
      bool isInside(QPointF point);
      QGraphicsRectItem *findRectangle(QPointF point);
      QColor generateColor();
      void removeRect(QGraphicsRectItem *rect);

     //this method is necessary because if the decimal part is greater than .50 with 'toPont' method, conversion is wrong
      QPoint convertToPoint(QPointF n);

	signals:
        void clicked(int x, int y);
        void clickedPoint(QPoint point, QColor color);
        void removedPoint( QColor color);
        void moving(QPoint point);


	public slots:
		void newChannel(int channel);

};

#endif // GRAPHICSSCENE_H
