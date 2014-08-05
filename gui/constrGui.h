#pragma once
 
#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QLineF>

#include "constr.h"

#include <boost/shared_ptr.hpp>

class constrGui : public QGraphicsItem {
  public:
    //constrGui(QGraphicsItem* parent=NULL) {};
    constrGui(boost::shared_ptr<constr> c);
  
  protected:
    void paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget = 0) ;
    QRectF boundingRect() const;
    boost::shared_ptr<QPolygonF> _frameGui;
    boost::shared_ptr<QPolygonF> _frameInternAGui;
    QVector<QLineF> _frameInternASeal;
    
};
