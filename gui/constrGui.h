#pragma once
 
#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class SuperItem : public QGraphicsItem {
  public:
    SuperItem(QGraphicsItem* parent=NULL);
  
  protected:
    void paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget = 0) ;
  
  QRectF boundingRect() const;
};
