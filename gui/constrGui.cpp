#include "constrGui.h"
#include <iostream>
SuperItem::SuperItem(QGraphicsItem* parent) {
  setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF SuperItem::boundingRect() const {
  return QRectF(0,0,30,30);
}

void  SuperItem::paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget) {
  painter->setBrush(Qt::red);
  painter->drawRoundedRect(0, 0, 30, 30, 5, 5);
}
