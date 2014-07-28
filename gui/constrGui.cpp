#include "constrGui.h"
#include <iostream>

constrGui::constrGui(boost::shared_ptr<constr> c) {
  _frameGui = boost::shared_ptr<QPolygonF> (new QPolygonF());
  
  for (unsigned int i = 0 ; i < c->nodeSize(); i++) {
    *_frameGui << QPointF(c->nodeGet(i)->c()[0], -c->nodeGet(i)->c()[1]);
  }
}

void constrGui::paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget) {
  painter->setBrush(Qt::red);
  painter->drawConvexPolygon(*_frameGui);
}

QRectF constrGui::boundingRect() const{
  return _frameGui->boundingRect();
}
