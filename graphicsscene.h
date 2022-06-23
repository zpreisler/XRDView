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

    const QPen dashed = QPen(QBrush(QColor(255,255,255,180)),1,Qt::DashLine);
    const QPen normal = QPen(QBrush(QColor(0,0,0,180)),1);
    const QPen seleceted = QPen(QBrush(QColor(0,0,0,180)),2);
    const QBrush brush = QBrush(QColor(255,255,255,120));





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

	signals:
        void clicked(int x, int y);
        void clickedPoint(QPoint point, QColor color);
        void removedPoint( QColor color);
        void moving(QPoint point);


	public slots:
		void newChannel(int channel);

};

#endif // GRAPHICSSCENE_H
