#include "constrGui.h"
#include <iostream>
#include <boost/foreach.hpp>

constrGui::constrGui(boost::shared_ptr<constr> c) {
  _frameGui = boost::shared_ptr<QPolygonF> (new QPolygonF());
  
  std::vector<boost::shared_ptr<node> > nodesV = c->mainFrameNodes();
    BOOST_FOREACH(const boost::shared_ptr<node> &nd, nodesV) {
    *_frameGui << QPointF(nd->c()[0], -nd->c()[1]);
  }
}

void constrGui::paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget) {
  painter->setBrush(Qt::white);
  
  QPen* penFrame = new QPen();
  penFrame->setWidth(15.0);
  painter->setPen(*penFrame);
  
  painter->drawConvexPolygon(*_frameGui);
}

QRectF constrGui::boundingRect() const{
  return _frameGui->boundingRect();
}
